//////////////////////////////////////////////////////////////////////////
/// 
/// \file	MP3.cpp
/// \author	Rob Bateman
///	\brief	This file uses DirectShow to load and play an Mp3 file. Err, 
///			in fact, playback is not limited to just mp3's, but also :
/// 
///			*.avi
///			*.qt
///			*.mov
///			*.mpg
///			*.mpeg
///			*.m1v
///			*.wav
///			*.mpa
///			*.mp2
///			*.mp3
///			*.au
///			*.aif
///			*.aiff
///			*.snd
///			*.mid
///			*.midi
///			*.rmi
///			
///			The video formats will be sound only! I may impliment some
///			form of vieo feedback if pestered enough.....
/// 
///			You must ensure that you call Mp3Init() when your application
///			starts, and Mp3Cleanup() when your app finishes. 
/// 
///			In order to play an mp3 file, call the function Mp3Load()
///			specifying the name of the mp3 file to play.
/// 
///			You can then control playback with 
/// 
///			void Mp3Play()
///			void Mp3Pause()
///			void Mp3Stop()
/// 
///			You can set certain playback parameters with the functions :
/// 
///			void Mp3SetVolume(long)
///			long Mp3GetVolume()
///			void Mp3SetBalance(long)
///			long Mp3GetBalance()
/// 
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//	Includes
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//	Includes 
//
//////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <strmif.h>
#include <control.h>
#include <uuids.h>
#include <evcode.h> // Codes events DirectX 
#include "MP3.h"

// force the DirectShow libs to be linked
#pragma comment(lib,"strmiids.lib")


/// used to build our 'media' graph that processes the file.
///	Essentually DirectShow will take something such as an mpeg
///	or mp3, and will split the file into a series of nodes
///	and connections. ie, two nodes may be created that represent the
///	left and right stereo sound channels, and an additional stereo
///	mixer control added for playback. 
/// 
///	This is very similar to the node layout of say the hypergraph
///	in Maya. Fortunately, DirectShow will build this graph for us.
///	If we wanted to, we could additional nodes such as filters or
///	Digital FX (ie reverb) to the sound, but thats not really part
///	of this basic example.
///
IGraphBuilder* g_pGraphBuilder = NULL;

/// used to control playback of the file. The level of control over
///	the specific Media file is determined by the interfaces to the
///	media that you request. For example, if we want to be able to 
///	start, pause and stop playback of the file, we need to get 
///	a pointer to an IMediaControl interface. If we want basic control
///	over things such as volume and panning, then we need to get a 
///	pointer to an IBasicAudio interface. We can choose which interfaces
///	to use, so it should be fairly easy to extend this code for other
///	purposes...
///
IMediaControl* g_pPlaybackControl = NULL;

/// provides a handle to basic volume and balance controls.
///
IBasicAudio*   g_pVolumeControl = NULL;


// Snoopy:
//#include "game.h"
IMediaEventEx*	g_pMediaEvent = NULL;
IMediaPosition*	g_pMediaPosition = NULL;


extern HWND G_hWnd;
char cMP3FileName[32];
#define WM_USER_MP3_EVENT		WM_USER + 2002

//#define EC_COMPLETE                         0x01
//#define EC_USERABORT                        0x02
//#define EC_ERRORABORT                       0x03

/// is the file ready for playback?
int			   g_bReady = 0;
int			   g_bPaused = 0;


//////////////////////////////////////////////////////////////////////////
/// \brief	ctor
///
void Mp3Init(void) 
{	ZeroMemory(cMP3FileName , sizeof(cMP3FileName) );
	CoInitialize(NULL);
}

//////////////////////////////////////////////////////////////////////////
/// \brief	call this to pause playback of the mp3
/// \param	szFile	-	the name of the file to load
///
void Mp3Load(char filename[])
{
	// DirectShow requires unicode (16bit) characters rather than 8bit ascii
	WCHAR wFile[MAX_PATH];

	// convert ascii to unicode
	MultiByteToWideChar(CP_ACP, 0, filename, -1, wFile, MAX_PATH);
	

	// create a graph build to allow us to make the audio signal path
	if( SUCCEEDED(CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void**)&g_pGraphBuilder)))
	{
		// create a simple controller for the sound file
		g_pGraphBuilder->QueryInterface( IID_IMediaControl, (void **)&g_pPlaybackControl );

		// create a simple interface for volume and balance
		g_pGraphBuilder->QueryInterface( IID_IBasicAudio  , (void **)&g_pVolumeControl );

		// Snoopy loop control
		g_pGraphBuilder->QueryInterface(IID_IMediaEvent   , (void **)&g_pMediaEvent);
		g_pGraphBuilder->QueryInterface(IID_IMediaPosition, (void **)&g_pMediaPosition);		

		// load and start playback of the specified sound file
		if( SUCCEEDED( g_pGraphBuilder->RenderFile(wFile, NULL) ) )
		{
			g_bReady = 1;
			strcpy(cMP3FileName, filename);
			g_pMediaEvent->SetNotifyWindow((OAHWND)G_hWnd, WM_USER_MP3_EVENT, 0);
			g_pMediaEvent->SetNotifyFlags(0);	// turn on event notifications
			
		}
	}
}


//////////////////////////////////////////////////////////////////////////
/// \brief	This function is used to cleanup DirectShow 
///			and release any interfaces we have gathered
///
void Mp3Cleanup(void)
{
	
	// stop playback of file if playing
	if( g_pPlaybackControl )
	{	g_pPlaybackControl->Stop();
	}

	// release the volume controller
	if( g_pVolumeControl )
	{	g_pVolumeControl->Release();
		g_pVolumeControl = NULL;
	}
	
	// release the playback controller
	if( g_pPlaybackControl )
	{	g_pPlaybackControl->Release();
		g_pPlaybackControl = NULL;
	}

	// release the g_pMediaEvent
	if( g_pMediaEvent )
	{	g_pMediaEvent->Release();
		g_pMediaEvent = NULL;
	}
	
	// release the g_pMediaPosition
	if( g_pMediaPosition )
	{	g_pMediaPosition->Release();
		g_pMediaPosition = NULL;
	}

	// release the graph builder 
	if( g_pGraphBuilder )
	{	g_pGraphBuilder->Release();
		g_pGraphBuilder = NULL;
	}
	
	// Unload DirectShow
	CoUninitialize();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//	Snoopy added functions

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/// Loop the music
void Mp3Event(void)
{long EventCode, Param1, Param2;

	while (g_pMediaEvent->GetEvent(&EventCode, &Param1, &Param2, 0) != E_ABORT)
	{	switch (EventCode) {		
        case EC_COMPLETE:  // here when media is completely done playing               
            g_pMediaPosition->put_CurrentPosition(0);   // reset to beginning
            break;
		default:
			break;
		}	
		g_pMediaEvent->FreeEventParams(EventCode, Param1, Param2);
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/// Ask is a file is already playing
bool Mp3Playing(char * filename)
{	if (strcmp (cMP3FileName, "") == 0)
	{	//playing no file
		return (false);

	}else

	if (strcmp (cMP3FileName, filename) == 0)
	{	//Already playing this file
		return (true);

	}else
	{	// No playing this file
		ZeroMemory(cMP3FileName , sizeof(cMP3FileName) );
		return (false);
	}
}

//////////////////////////////////////////////////////////////////////////
/// Ccall this to resume playback of the mp3
void Mp3Resume(void)
{
	if((g_bReady) && (g_bPaused == 1))
	{	g_pPlaybackControl->Run();
	}
}

/*HWND Mp3Debug(void)
{	return (G_hWnd);
}*/

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//	Functionality Given by the IMediaControl Interface

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// \brief	call this to start playback of the mp3
void Mp3Play(void)
{
	if(g_bReady)
	{	g_bPaused = 0;
		g_pPlaybackControl->Run();
	}
}
//////////////////////////////////////////////////////////////////////////
/// \brief	call this to pause playback of the mp3
void Mp3Pause(void)
{
	if(g_bReady)
	{	g_bPaused = 1;
		g_pPlaybackControl->Pause();
	}
}

//////////////////////////////////////////////////////////////////////////
/// \brief	call this to stop playback of the mp3
void Mp3Stop(void)
{
	if(g_bReady)
	{	g_bPaused = 0;
		g_pPlaybackControl->Stop();
		ZeroMemory(cMP3FileName , sizeof(cMP3FileName) );
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//	Functionality Given by the IBasicAudio Interface

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// \brief	call this to set the current volume level. Valid values are 
///			between -10000 and 0.
///
void Mp3SetVolume(long val)
{
	if(g_bReady)
	{
		g_pVolumeControl->put_Volume(val);
	}
}


//////////////////////////////////////////////////////////////////////////
/// \brief	call this to get the current volume level. Valid values are 
///			between -10000 and 0.
///
long Mp3GetVolume(void)
{
	long val=0;
	if(g_bReady)
	{
		g_pVolumeControl->get_Volume(&val);
	}
	return val;
}

//////////////////////////////////////////////////////////////////////////
/// \brief	call this to set the current balance. Valid values are 
///			between -10000 and 10000.
///
void Mp3SetBalance(long val)
{
	if(g_bReady)
	{
		g_pVolumeControl->put_Balance(val);
	}
}


//////////////////////////////////////////////////////////////////////////
/// \brief	call this to get the current balance. Valid values are 
///			between -10000 and 10000.
///
long Mp3GetBalance(void)
{
	long val=0;
	if(g_bReady)
	{
		g_pVolumeControl->get_Balance(&val);
	}
	return val;
}

