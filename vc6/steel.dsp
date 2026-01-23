# Microsoft Developer Studio Project File - Name="steel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=steel - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "steel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "steel.mak" CFG="steel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "steel - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "steel - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "steel - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O1 /I "../lib/irrlicht131/include" /I "../lib/lua" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0xc0a /d "NDEBUG"
# ADD RSC /l 0xc0a /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 Irrlicht.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"../lib/irrlicht131/lib"

!ELSEIF  "$(CFG)" == "steel - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../lib/irrlicht131/include" /I "../lib/lua" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0xc0a /d "_DEBUG"
# ADD RSC /l 0xc0a /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Irrlicht.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"../lib/irrlicht131/lib"

!ENDIF 

# Begin Target

# Name "steel - Win32 Release"
# Name "steel - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "procedural"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\procedural\color.cpp
# End Source File
# Begin Source File

SOURCE=..\src\procedural\drawing.cpp
# End Source File
# Begin Source File

SOURCE=..\src\procedural\engine.cpp
# End Source File
# Begin Source File

SOURCE=..\src\procedural\math.cpp
# End Source File
# Begin Source File

SOURCE=..\src\procedural\memblock.cpp
# End Source File
# Begin Source File

SOURCE=..\src\procedural\screen.cpp
# End Source File
# End Group
# Begin Group "lua"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\lua\lapi.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lauxlib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lbaselib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lcode.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\ldblib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\ldebug.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\ldo.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\ldump.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lfunc.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lgc.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\linit.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\liolib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\llex.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lmathlib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lmem.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\loadlib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lobject.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lopcodes.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\loslib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lparser.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lstate.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lstring.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lstrlib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\ltable.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\ltablib.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\ltm.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lundump.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lvm.c
# End Source File
# Begin Source File

SOURCE=..\lib\lua\lzio.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\error.cpp
# End Source File
# Begin Source File

SOURCE=..\src\lua_wrapper.cpp
# End Source File
# Begin Source File

SOURCE=..\src\main.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
