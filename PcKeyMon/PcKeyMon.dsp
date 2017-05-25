# Microsoft Developer Studio Project File - Name="PcKeyMon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PcKeyMon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PcKeyMon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PcKeyMon.mak" CFG="PcKeyMon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PcKeyMon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "PcKeyMon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PcKeyMon - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /out:"e:\pcshare\PcKeyMon.exe" /pdbtype:sept
# ADD LINK32 Ws2_32.lib /nologo /subsystem:windows /debug /machine:IX86 /out:"../Bin/PcKeyMon.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "PcKeyMon - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x804
# ADD RSC /l 0x804
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:IX86 /out:"e:\pcshare\PcKeyMon.exe" /pdbtype:sept /opt:ref /opt:icf
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib /nologo /subsystem:windows /machine:IX86 /out:"..\Bin\PcKeyMon.exe" /pdbtype:sept /opt:ref /opt:icf
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "PcKeyMon - Win32 Debug"
# Name "PcKeyMon - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\MyEditView.h"\
	".\MyMarco.h"\
	".\PcKeyMon.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MyEditView.cpp
DEP_CPP_MYEDI=\
	".\MainFrm.h"\
	".\MyEditView.h"\
	".\MyMarco.h"\
	".\PcKeyMon.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MyGlobalFuc.cpp
DEP_CPP_MYGLO=\
	".\MyMarco.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\PcKeyMon.cpp
DEP_CPP_PCKEY=\
	".\MainFrm.h"\
	".\MyEditView.h"\
	".\MyMarco.h"\
	".\PcKeyMon.h"\
	".\stdafx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\MyMarco.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "PcKeyMon - Win32 Debug"

# ADD CPP /nologo /GX /Yc"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcKeyMon - Win32 Release"

# ADD CPP /nologo /GX /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyEditView.h
# End Source File
# Begin Source File

SOURCE=.\MyMarco.h
# End Source File
# Begin Source File

SOURCE=.\PcKeyMon.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\PcKeyMon.ico
# End Source File
# Begin Source File

SOURCE=.\PcKeyMon.rc
# End Source File
# Begin Source File

SOURCE=.\res\PcKeyMon.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PcKeyMonDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Wait07.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\PcKeyMon.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
