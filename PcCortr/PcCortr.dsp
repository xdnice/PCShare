# Microsoft Developer Studio Project File - Name="PcCortr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PcCortr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PcCortr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PcCortr.mak" CFG="PcCortr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PcCortr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PcCortr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PcCortr - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Wininet.lib shlwapi.lib ZLIB.LIB Ws2_32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\Bin\PcCortr.dll"

!ELSEIF  "$(CFG)" == "PcCortr - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib ZLIB.LIB wininet.lib Ws2_32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"MSVCRT.lib" /def:".\PcCortr.def" /out:"../Bin/PcCortr.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "PcCortr - Win32 Release"
# Name "PcCortr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MyAdminTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\MyFrameTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\MyHttpBase.cpp
# End Source File
# Begin Source File

SOURCE=.\MyHttpPipeBase.cpp
# End Source File
# Begin Source File

SOURCE=.\MyKeyMonTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMainTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMulitTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTlntTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\PcCortr.cpp
# End Source File
# Begin Source File

SOURCE=.\PcCortr.def

!IF  "$(CFG)" == "PcCortr - Win32 Release"

!ELSEIF  "$(CFG)" == "PcCortr - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PcCortr.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\XGina.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MyAdminTrans.h
# End Source File
# Begin Source File

SOURCE=.\MyFrameTrans.h
# End Source File
# Begin Source File

SOURCE=.\MyHttpBase.h
# End Source File
# Begin Source File

SOURCE=.\MyHttpPipeBase.h
# End Source File
# Begin Source File

SOURCE=.\MyKeyMonTrans.h
# End Source File
# Begin Source File

SOURCE=.\MyMainTrans.h
# End Source File
# Begin Source File

SOURCE=.\MyMulitTrans.h
# End Source File
# Begin Source File

SOURCE=.\MyTlntTrans.h
# End Source File
# Begin Source File

SOURCE=.\PcCortr.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XGina.h
# End Source File
# Begin Source File

SOURCE=.\ZCONF.H
# End Source File
# Begin Source File

SOURCE=.\ZLIB.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\PcCortr.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
