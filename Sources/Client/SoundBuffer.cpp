// SoundBuffer.cpp: implementation of the CSoundBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>


#include "dsound.h"
#include "SoundBuffer.h"

struct Waveheader
{
	BYTE        RIFF[4];          // "RIFF"
	DWORD       dwSize;           // Size of data to follow
	BYTE        WAVE[4];          // "WAVE"
	BYTE        fmt_[4];          // "fmt "
	DWORD       dw16;             // 16
	WORD        wOne_0;           // 1
	WORD        wChnls;           // Number of Channels
	DWORD       dwSRate;          // Sample Rate
	DWORD       BytesPerSec;      // Sample Rate
	WORD        wBlkAlign;        // 1
	WORD        BitsPerSample;    // Sample size
	BYTE        DATA[4];          // "DATA"
	DWORD       dwDSize;          // Number of Samples
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoundBuffer::CSoundBuffer(LPDIRECTSOUND lpDS, DSCAPS DSCaps, char * pWavFileName, BOOL bIsSingleLoad)
{
 int i;

	m_lpDS		= lpDS;
	m_DSCaps	= DSCaps;

	ZeroMemory(m_cWavFileName, sizeof(m_cWavFileName));
	strcpy(m_cWavFileName, pWavFileName);

	if (bIsSingleLoad == TRUE) {
		//m_lpDSB[0] = NULL;
		//bCreateBuffer_LoadWavFileContents(0);
	}
	else {
		/*
		for (i = 0; i < DEF_MAXSOUNDBUFFERS; i++) {
			m_lpDSB[i] = NULL;
			bCreateBuffer_LoadWavFileContents(i);
		}
		*/
	}

	for (i = 0; i < DEF_MAXSOUNDBUFFERS; i++) m_lpDSB[i] = NULL;
	
	m_cCurrentBufferIndex = 0;
	m_bIsSingleLoad = bIsSingleLoad;

	m_dwTime = NULL;

	m_bIsLooping = FALSE;
}

CSoundBuffer::~CSoundBuffer()
{
	for (int i = 0; i < DEF_MAXSOUNDBUFFERS; i++)
	{
		if (m_lpDSB[i] != NULL)
		{
			m_lpDSB[i]->Release();
			m_lpDSB[i] = NULL;
		}
	}
}

BOOL CSoundBuffer::_bCreateSoundBuffer(char cBufferIndex, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo)
{
	PCMWAVEFORMAT pcmwf;
	DSBUFFERDESC dsbdesc;
	if (m_lpDSB[cBufferIndex] != NULL) return FALSE;

	memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT));
	pcmwf.wf.wFormatTag         = WAVE_FORMAT_PCM;
	pcmwf.wf.nChannels          = bStereo ? 2 : 1;
	pcmwf.wf.nSamplesPerSec     = dwFreq;
	pcmwf.wf.nBlockAlign        = (WORD)dwBlkAlign;
	pcmwf.wf.nAvgBytesPerSec    = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
	pcmwf.wBitsPerSample        = (WORD)dwBitsPerSample;

	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize              = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags             = DSBCAPS_STATIC | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME;
	dsbdesc.dwBufferBytes       = dwBufSize; 
	dsbdesc.lpwfxFormat         = (LPWAVEFORMATEX)&pcmwf;

	if (m_lpDS->CreateSoundBuffer(&dsbdesc, &m_lpDSB[cBufferIndex], NULL) != DS_OK) return FALSE;
		
	return TRUE;
}

BOOL CSoundBuffer::bCreateBuffer_LoadWavFileContents(char cBufferIndex)
{
 FILE		*	pFile;
 Waveheader		Wavhdr;
 DWORD			dwSize;
 BOOL			bStereo;
	
	if (m_lpDSB[cBufferIndex] != NULL) return FALSE;

	pFile = fopen(m_cWavFileName, "rb");
	if (pFile == NULL) return FALSE;
		
	if (fread(&Wavhdr, sizeof(Wavhdr), 1, pFile) != 1) 
	{
		fclose(pFile);
		return FALSE;
	}

	dwSize = Wavhdr.dwDSize;
   	bStereo = Wavhdr.wChnls > 1 ? TRUE : FALSE;

	if (_bCreateSoundBuffer(cBufferIndex, dwSize, Wavhdr.dwSRate, Wavhdr.BitsPerSample, Wavhdr.wBlkAlign, bStereo) == FALSE)
	{
		fclose(pFile);
    	return FALSE;
	}

	if (!_LoadWavContents(cBufferIndex, pFile, dwSize, sizeof(Wavhdr))) 
	{
		fclose(pFile);
		return FALSE;
	}

	fclose(pFile);
	return TRUE;
}

BOOL CSoundBuffer::_LoadWavContents(char cBufferIndex, FILE * pFile, DWORD dwSize, DWORD dwPos)
{
 LPVOID  pData1;
 DWORD   dwData1Size;
 LPVOID  pData2;
 DWORD   dwData2Size;
 HRESULT rval;
	
	if (m_lpDSB[cBufferIndex] == NULL) return FALSE;
	if (dwPos == 0xffffffff) return FALSE;
	if (fseek(pFile, dwPos, SEEK_SET) != 0) return FALSE;

	rval = m_lpDSB[cBufferIndex]->Lock(0, dwSize, &pData1, &dwData1Size, &pData2, &dwData2Size, DSBLOCK_ENTIREBUFFER);
	//DSBLOCK_FROMWRITECURSOR); // DSBLOCK_ENTIREBUFFER
	if (rval != DS_OK) return FALSE;

	if (dwData1Size > 0) 
	if (fread(pData1, dwData1Size, 1, pFile) != 1) 
		return FALSE;
		
	if (dwData2Size > 0) 
	if (fread(pData2, dwData2Size, 1, pFile) != 1) 
		return FALSE;
	
	rval = m_lpDSB[cBufferIndex]->Unlock(pData1, dwData1Size, pData2, dwData2Size);
	if (rval != DS_OK) return FALSE;
 
	// v1.3
	m_lpDSB[cBufferIndex]->SetFrequency(DSBFREQUENCY_ORIGINAL);

	return TRUE;
}


BOOL CSoundBuffer::Play(BOOL bLoop, long lPan, int iVol)
{
 HRESULT rval;
 LPDIRECTSOUNDBUFFER Buffer = NULL;
 
	if(m_lpDS == NULL) return FALSE;

	Buffer = GetIdleBuffer();
	if(Buffer == NULL) return FALSE;
	
	SetVolume(iVol);

	if (lPan < DSBPAN_LEFT) lPan = DSBPAN_LEFT;
	else if (lPan > DSBPAN_RIGHT) lPan = DSBPAN_RIGHT; 
	Buffer->SetPan(lPan);

	m_bIsLooping = bLoop;

	if (bLoop == FALSE)
		 rval = Buffer->Play(0, 0, 0);
	else rval = Buffer->Play(0, 0, DSBPLAY_LOOPING );
	if(rval != DS_OK) return FALSE;

	return TRUE;
} 


LPDIRECTSOUNDBUFFER CSoundBuffer::GetIdleBuffer(void)
{
 DWORD Status;
 HRESULT rval;
 LPDIRECTSOUNDBUFFER Buffer;
	
	Buffer = NULL;
	if (m_lpDSB[m_cCurrentBufferIndex] != NULL) {
		rval = m_lpDSB[m_cCurrentBufferIndex]->GetStatus(&Status);
		if (rval < 0) Status = 0;

		if (Status & DSBSTATUS_BUFFERLOST) {
			m_lpDSB[m_cCurrentBufferIndex]->Release();
			m_lpDSB[m_cCurrentBufferIndex] = NULL;
			bCreateBuffer_LoadWavFileContents(m_cCurrentBufferIndex);
		}
		else if ((Status & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING) {
			if (m_bIsSingleLoad == TRUE) {
				m_lpDSB[m_cCurrentBufferIndex]->Stop();
				m_lpDSB[m_cCurrentBufferIndex]->SetCurrentPosition(0);
				Buffer = m_lpDSB[m_cCurrentBufferIndex];
				m_dwTime = timeGetTime();
				return Buffer;
			}
			
			m_cCurrentBufferIndex++;
			if (m_cCurrentBufferIndex >= DEF_MAXSOUNDBUFFERS) m_cCurrentBufferIndex = 0;
			
			if (m_lpDSB[m_cCurrentBufferIndex] != NULL) {
				rval = m_lpDSB[m_cCurrentBufferIndex]->GetStatus(&Status);
				if (rval < 0) Status = 0;
				if (Status & DSBSTATUS_BUFFERLOST) {
					m_lpDSB[m_cCurrentBufferIndex]->Release();
					m_lpDSB[m_cCurrentBufferIndex] = NULL;
					bCreateBuffer_LoadWavFileContents(m_cCurrentBufferIndex);
				}
				else if ((Status & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING) {
					m_lpDSB[m_cCurrentBufferIndex]->Stop();
					m_lpDSB[m_cCurrentBufferIndex]->SetCurrentPosition(0);
				}
			}
			else {
				bCreateBuffer_LoadWavFileContents(m_cCurrentBufferIndex);
			}
			
			//m_lpDSB[m_cCurrentBufferIndex]->Stop();
			//m_lpDSB[m_cCurrentBufferIndex]->SetCurrentPosition(0);
		}

		Buffer = m_lpDSB[m_cCurrentBufferIndex];
	}
	else {
		bCreateBuffer_LoadWavFileContents(m_cCurrentBufferIndex);
		Buffer = m_lpDSB[m_cCurrentBufferIndex];
	}	

	m_dwTime = timeGetTime();
	return Buffer;
}

void CSoundBuffer::SetVolume(LONG Volume)
{
 int i;

	for (i = 0; i < DEF_MAXSOUNDBUFFERS; i++)
	if (m_lpDSB[i] != NULL) m_lpDSB[i]->SetVolume(Volume);
}

void CSoundBuffer::bStop(BOOL bIsNoRewind)
{
	for (int i = 0; i < DEF_MAXSOUNDBUFFERS; i++)
	{
		if (m_lpDSB[i] != NULL)
		{
			if( m_lpDSB[i]->Stop() != DS_OK ) return;
			if (bIsNoRewind == FALSE) m_lpDSB[i]->SetCurrentPosition(0);
		}
	}
}

void CSoundBuffer::_ReleaseSoundBuffer()
{
 int i;

	for (i = 0; i < DEF_MAXSOUNDBUFFERS; i++) 
	if (m_lpDSB[i] != NULL) {
		m_lpDSB[i]->Release();
		m_lpDSB[i] = NULL;
	}
}
