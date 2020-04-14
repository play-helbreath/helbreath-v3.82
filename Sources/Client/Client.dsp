# Microsoft Developer Studio Project File - Name="Game" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Game - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak" CFG="Game - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Game - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 search.lib wsock32.lib DINPUT.LIB DSOUND.LIB DXGUID.LIB ddraw.lib IMM32.LIB winmm.lib Cint.lib cximage/release/cximage.lib jpeg/release/Jpeg.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /pdb:none /machine:I386 /nodefaultlib:"MSVCRTD" /nodefaultlib:"LIBC" /release
# SUBTRACT LINK32 /nodefaultlib
# Begin Target

# Name "Game - Win32 Release"
# Begin Group "Library"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Cint.h
# End Source File
# Begin Source File

SOURCE=.\CNTREVNT.H
# End Source File
# Begin Source File

SOURCE=.\DDRAW.H
# End Source File
# Begin Source File

SOURCE=.\DINPUT.H
# End Source File
# Begin Source File

SOURCE=.\DSOUND.H
# End Source File
# Begin Source File

SOURCE=.\YWSound.cpp
# End Source File
# Begin Source File

SOURCE=.\YWSound.h
# End Source File
# End Group
# Begin Group "Language"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lan_eng.h
# End Source File
# End Group
# Begin Group "Ressources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AIcon.ico
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# End Group
# Begin Group "classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BuildItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildItem.h
# End Source File
# Begin Source File

SOURCE=.\CharInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CharInfo.h
# End Source File
# Begin Source File

SOURCE=.\Curse.cpp
# End Source File
# Begin Source File

SOURCE=.\Curse.h
# End Source File
# Begin Source File

SOURCE=.\DXC_ddraw.cpp
# End Source File
# Begin Source File

SOURCE=.\DXC_ddraw.h
# End Source File
# Begin Source File

SOURCE=.\DXC_dinput.cpp
# End Source File
# Begin Source File

SOURCE=.\DXC_dinput.h
# End Source File
# Begin Source File

SOURCE=.\DXC_dsound.cpp
# End Source File
# Begin Source File

SOURCE=.\DXC_dsound.h
# End Source File
# Begin Source File

SOURCE=.\Effect.cpp
# End Source File
# Begin Source File

SOURCE=.\Effect.h
# End Source File
# Begin Source File

SOURCE=.\GameMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\GameMonitor.h
# End Source File
# Begin Source File

SOURCE=.\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\Item.h
# End Source File
# Begin Source File

SOURCE=.\ItemName.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemName.h
# End Source File
# Begin Source File

SOURCE=.\Magic.cpp
# End Source File
# Begin Source File

SOURCE=.\Magic.h
# End Source File
# Begin Source File

SOURCE=.\MapData.cpp
# End Source File
# Begin Source File

SOURCE=.\MapData.h
# End Source File
# Begin Source File

SOURCE=.\Misc.cpp
# End Source File
# Begin Source File

SOURCE=.\Misc.h
# End Source File
# Begin Source File

SOURCE=.\MouseInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\MouseInterface.h
# End Source File
# Begin Source File

SOURCE=.\Msg.cpp
# End Source File
# Begin Source File

SOURCE=.\Msg.h
# End Source File
# Begin Source File

SOURCE=.\Mydib.cpp
# End Source File
# Begin Source File

SOURCE=.\Mydib.h
# End Source File
# Begin Source File

SOURCE=.\Skill.cpp
# End Source File
# Begin Source File

SOURCE=.\Skill.h
# End Source File
# Begin Source File

SOURCE=.\SoundBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundBuffer.h
# End Source File
# Begin Source File

SOURCE=.\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\StrTok.cpp
# End Source File
# Begin Source File

SOURCE=.\StrTok.h
# End Source File
# Begin Source File

SOURCE=.\Tile.cpp
# End Source File
# Begin Source File

SOURCE=.\Tile.h
# End Source File
# Begin Source File

SOURCE=.\TileSpr.cpp
# End Source File
# Begin Source File

SOURCE=.\TileSpr.h
# End Source File
# Begin Source File

SOURCE=.\XSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\XSocket.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ActionID.h
# End Source File
# Begin Source File

SOURCE=.\crcdemo.cpp
# End Source File
# Begin Source File

SOURCE=.\crcdemo.h
# End Source File
# Begin Source File

SOURCE=.\DynamicObjectID.h
# End Source File
# Begin Source File

SOURCE=.\Game.cpp
# End Source File
# Begin Source File

SOURCE=.\Game.h
# End Source File
# Begin Source File

SOURCE=.\GlobalDef.h
# End Source File
# Begin Source File

SOURCE=.\MP3.cpp
# End Source File
# Begin Source File

SOURCE=.\MP3.h
# End Source File
# Begin Source File

SOURCE=.\NetMessages.h
# End Source File
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# Begin Source File

SOURCE=.\SpriteID.h
# End Source File
# Begin Source File

SOURCE=.\Winmain.h
# End Source File
# Begin Source File

SOURCE=.\Wmain.cpp
# End Source File
# End Target
# End Project
