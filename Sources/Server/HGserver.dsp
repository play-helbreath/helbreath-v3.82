# Microsoft Developer Studio Project File - Name="HGserver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HGserver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HGserver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HGserver.mak" CFG="HGserver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HGserver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HGserver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/HGserver", KDAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HGserver - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "HGserver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# SUBTRACT CPP /WX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /stack:0x2000000 /subsystem:windows /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "HGserver - Win32 Release"
# Name "HGserver - Win32 Debug"
# Begin Group "other classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ActionID.h
# End Source File
# Begin Source File

SOURCE=.\BuildItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BuildItem.h
# End Source File
# Begin Source File

SOURCE=.\Client.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.h
# End Source File
# Begin Source File

SOURCE=.\DelayEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DelayEvent.h
# End Source File
# Begin Source File

SOURCE=.\DynamicObject.cpp
# End Source File
# Begin Source File

SOURCE=.\DynamicObject.h
# End Source File
# Begin Source File

SOURCE=.\Fish.cpp
# End Source File
# Begin Source File

SOURCE=.\Fish.h
# End Source File
# Begin Source File

SOURCE=.\GuildsMan.cpp
# End Source File
# Begin Source File

SOURCE=.\GuildsMan.h
# End Source File
# Begin Source File

SOURCE=.\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\Item.h
# End Source File
# Begin Source File

SOURCE=.\Magic.cpp
# End Source File
# Begin Source File

SOURCE=.\Magic.h
# End Source File
# Begin Source File

SOURCE=.\Map.cpp
# End Source File
# Begin Source File

SOURCE=.\Map.h
# End Source File
# Begin Source File

SOURCE=.\Mineral.cpp
# End Source File
# Begin Source File

SOURCE=.\Mineral.h
# End Source File
# Begin Source File

SOURCE=.\Misc.cpp
# End Source File
# Begin Source File

SOURCE=.\Misc.h
# End Source File
# Begin Source File

SOURCE=.\Msg.cpp
# End Source File
# Begin Source File

SOURCE=.\Msg.h
# End Source File
# Begin Source File

SOURCE=.\Npc.cpp
# End Source File
# Begin Source File

SOURCE=.\Npc.h
# End Source File
# Begin Source File

SOURCE=.\OccupyFlag.cpp
# End Source File
# Begin Source File

SOURCE=.\OccupyFlag.h
# End Source File
# Begin Source File

SOURCE=.\Portion.cpp
# End Source File
# Begin Source File

SOURCE=.\Portion.h
# End Source File
# Begin Source File

SOURCE=.\Quest.cpp
# End Source File
# Begin Source File

SOURCE=.\Quest.h
# End Source File
# Begin Source File

SOURCE=.\Skill.cpp
# End Source File
# Begin Source File

SOURCE=.\Skill.h
# End Source File
# Begin Source File

SOURCE=.\StrategicPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\StrategicPoint.h
# End Source File
# Begin Source File

SOURCE=.\StrTok.cpp
# End Source File
# Begin Source File

SOURCE=.\StrTok.h
# End Source File
# Begin Source File

SOURCE=.\Teleport.cpp
# End Source File
# Begin Source File

SOURCE=.\Teleport.h
# End Source File
# Begin Source File

SOURCE=.\TeleportLoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TeleportLoc.h
# End Source File
# Begin Source File

SOURCE=.\TempNpcItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TempNpcItem.h
# End Source File
# Begin Source File

SOURCE=.\Tile.cpp
# End Source File
# Begin Source File

SOURCE=.\Tile.h
# End Source File
# Begin Source File

SOURCE=.\XSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\XSocket.h
# End Source File
# Begin Source File

SOURCE=.\Winmm.lib
# End Source File
# Begin Source File

SOURCE=.\Ws2_32.lib
# End Source File
# End Group
# Begin Group "ressources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\HGserver.rc
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\logo.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DebugDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugDialog.h
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

SOURCE=.\MessageIndex.h
# End Source File
# Begin Source File

SOURCE=.\NetMessages.h
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\UserMessages.h
# End Source File
# Begin Source File

SOURCE=.\winmain.h
# End Source File
# Begin Source File

SOURCE=.\wmain.cpp
# End Source File
# End Target
# End Project
