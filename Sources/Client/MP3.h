//////////////////////////////////////////////////////////////////////////
/// 
/// \file	MP3.h
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
//	Sentry  (prevents header being included twice)
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _MP3_PLAYER_H_
#define _MP3_PLAYER_H_

//////////////////////////////////////////////////////////////////////////
//
//	DirectShow Initialisation / Uninitialisation
//
//////////////////////////////////////////////////////////////////////////

/// \brief	You must call this function before calling any other Mp3 function
///
extern void Mp3Init(void);


/// \brief	This function is called to kill the DirectShow interface
///
extern void Mp3Cleanup(void);



//////////////////////////////////////////////////////////////////////////
//
//	Load an Mp3 File
//
//////////////////////////////////////////////////////////////////////////

/// \brief	this function loads the specified file for playback
/// \param	filename	-	the name of the file to load
///
extern void Mp3Load(char filename[]);



//////////////////////////////////////////////////////////////////////////
//
//	Mp3 Playback Controls
//
//////////////////////////////////////////////////////////////////////////


/// \brief	call this to start playback of the mp3
///
extern void Mp3Play(void);



/// \brief	call this to pause playback of the mp3
///
extern void Mp3Pause(void);


/// \brief	call this to stop the playback of the mp3
///
extern void Mp3Stop(void);




//////////////////////////////////////////////////////////////////////////
//
//	Snoopy functions
//
//////////////////////////////////////////////////////////////////////////
///
/// Event handler to loop the music
extern void Mp3Event(void);

/// Ask is a file is already playing
extern bool Mp3Playing(char * filename);

/// Call this to resume playback of the mp3
extern void Mp3Resume(void);

/// Debug function
//extern HWND Mp3Debug(void);


//////////////////////////////////////////////////////////////////////////
//
//	Audio Controls
//
//////////////////////////////////////////////////////////////////////////

/// \brief	call this to set the current volume level. Valid values are 
///			between -10000 and 0.
///
extern void Mp3SetVolume(long);


/// \brief	call this to get the current volume level. Valid values are 
///			between -10000 and 0.
///
extern long Mp3GetVolume(void);


/// \brief	call this to set the current balance. Valid values are 
///			between -10000 and 10000.
///
extern void Mp3SetBalance(long);


/// \brief	call this to get the current balance. Valid values are 
///			between -10000 and 10000.
///
extern long Mp3GetBalance(void);



#endif
