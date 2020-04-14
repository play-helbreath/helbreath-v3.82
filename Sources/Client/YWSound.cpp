// YWSound.cpp: implementation of the YWSound class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "dsound.h"
#include "YWSound.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

YWSound::YWSound()
{
	m_lpDS = NULL;
}

YWSound::~YWSound()
{
	if(m_lpDS) m_lpDS->Release();
}

//////////////////////////////////////////////////////////////////////////////////
// YWSound Create
//////////////////////////////////////////////////////////////////////////////////
bool YWSound::Create(HWND hWnd)
{
	HRESULT rval;
	LPDIRECTSOUNDBUFFER lpDsb;
	DSBUFFERDESC dsbdesc;
	WAVEFORMATEX wfm;

	rval = DirectSoundCreate(NULL, &m_lpDS, NULL);
	if(rval != DS_OK)
	{
		OutputDebugString("DirectSoundCreate error...\n");
		return FALSE;
	}
	
	rval = m_lpDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if(rval != DS_OK)
	{
		OutputDebugString("DirectSoundCreate error...\n");
		return FALSE;
	}
	
	memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	memset(&wfm, 0, sizeof(WAVEFORMATEX));
	wfm.wFormatTag = WAVE_FORMAT_PCM;
	wfm.nChannels = 2;
	wfm.nSamplesPerSec = 44100;
	wfm.wBitsPerSample = 16;
	wfm.nBlockAlign = wfm.wBitsPerSample / 8 *wfm.nChannels;
	wfm.nAvgBytesPerSec = wfm.nSamplesPerSec * wfm.nBlockAlign;

	rval = m_lpDS->CreateSoundBuffer(&dsbdesc, &lpDsb, NULL);
	if (rval != DS_OK) return FALSE;
	
	lpDsb->SetFormat(&wfm);

	rval = m_lpDS->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	if(rval != DS_OK)
	{
		OutputDebugString("DirectSoundCreate error...\n");
		return FALSE;
	}
	
	return TRUE;
}
