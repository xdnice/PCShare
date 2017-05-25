# Microsoft Developer Studio Project File - Name="PcFile" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PcFile - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PcFile.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PcFile.mak" CFG="PcFile - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PcFile - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "PcFile - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib zlib.lib Ws2_32.lib /nologo /subsystem:windows /incremental:no /debug /machine:IX86 /out:"e:\pcshare\PcFile.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 zlib.lib Ws2_32.lib /nologo /subsystem:windows /pdb:"Debug/PcFile.pdb" /debug /machine:IX86 /nodefaultlib:"msvcrt.lib" /out:"../Bin/PcFile.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GF /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib zlib.lib /nologo /subsystem:windows /machine:IX86 /out:"e:\pcshare\PcFile.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib zlib.lib Ws2_32.lib /nologo /subsystem:windows /machine:IX86 /out:"..\Bin\PcFile.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "PcFile - Win32 Debug"
# Name "PcFile - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=DirDialog.cpp
DEP_CPP_DIRDI=\
	".\DirDialog.h"\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ManaFrame.cpp
DEP_CPP_MANAF=\
	".\DirDialog.h"\
	".\ManaFrame.h"\
	".\MyDirInfoDlg.h"\
	".\mydirlistview.h"\
	".\MyDirTreeView.h"\
	".\mydirview.h"\
	".\MyDiskInfo.h"\
	".\MyFileInfo.h"\
	".\MyFileTransDlg.h"\
	".\MyFileTransView.h"\
	".\MyFindFileDlg.h"\
	".\MyMarco.h"\
	".\MyRenameDlg.h"\
	".\NewMenu.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyDirInfoDlg.cpp
DEP_CPP_MYDIR=\
	".\MyDirInfoDlg.h"\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyDirListView.cpp
DEP_CPP_MYDIRL=\
	".\mydirlistview.h"\
	".\MyMarco.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyDirTreeView.cpp
DEP_CPP_MYDIRT=\
	".\MyDirTreeView.h"\
	".\MyMarco.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=mydirview.cpp
DEP_CPP_MYDIRV=\
	".\mydirlistview.h"\
	".\MyDirTreeView.h"\
	".\mydirview.h"\
	".\MyMarco.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyDiskInfo.cpp
DEP_CPP_MYDIS=\
	".\MyDiskInfo.h"\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyFileInfo.cpp
DEP_CPP_MYFIL=\
	".\MyFileInfo.h"\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyFileTransDlg.cpp
DEP_CPP_MYFILE=\
	".\MyFileTransDlg.h"\
	".\MyMarco.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyFileTransView.cpp
DEP_CPP_MYFILET=\
	".\MyFileTransView.h"\
	".\MyMarco.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyFindFileDlg.cpp
DEP_CPP_MYFIN=\
	".\DirDialog.h"\
	".\ManaFrame.h"\
	".\mydirlistview.h"\
	".\MyDirTreeView.h"\
	".\mydirview.h"\
	".\MyFileInfo.h"\
	".\MyFileTransDlg.h"\
	".\MyFileTransView.h"\
	".\MyFindFileDlg.h"\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=MyGlobalFuc.cpp
DEP_CPP_MYGLO=\
	".\MyMarco.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	".\ZCONF.H"\
	".\ZLIB.H"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyRenameDlg.cpp
DEP_CPP_MYREN=\
	".\MyMarco.h"\
	".\MyRenameDlg.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\MyTrace.cpp
DEP_CPP_MYTRA=\
	".\MyMarco.h"\
	".\MyTrace.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\NewMenu.cpp
DEP_CPP_NEWME=\
	".\MyMarco.h"\
	".\MyTrace.h"\
	".\NewMenu.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"FC\src\afximpl.h"\
	
# End Source File
# Begin Source File

SOURCE=PcFile.cpp
DEP_CPP_PCFIL=\
	".\ManaFrame.h"\
	".\mydirlistview.h"\
	".\MyDirTreeView.h"\
	".\mydirview.h"\
	".\MyFileTransView.h"\
	".\MyMarco.h"\
	".\PcFile.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=PcFile.rc
# End Source File
# Begin Source File

SOURCE=StdAfx.cpp
DEP_CPP_STDAF=\
	".\MyMarco.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PcFile - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yc"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "PcFile - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yc"stdafx.h"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=DirDialog.h
# End Source File
# Begin Source File

SOURCE=ManaFrame.h
# End Source File
# Begin Source File

SOURCE=MyDirInfoDlg.h
# End Source File
# Begin Source File

SOURCE=mydirlistview.h
# End Source File
# Begin Source File

SOURCE=MyDirTreeView.h
# End Source File
# Begin Source File

SOURCE=mydirview.h
# End Source File
# Begin Source File

SOURCE=MyDiskInfo.h
# End Source File
# Begin Source File

SOURCE=MyFileInfo.h
# End Source File
# Begin Source File

SOURCE=MyFileTransDlg.h
# End Source File
# Begin Source File

SOURCE=MyFileTransView.h
# End Source File
# Begin Source File

SOURCE=MyFindFileDlg.h
# End Source File
# Begin Source File

SOURCE=MyMarco.h
# End Source File
# Begin Source File

SOURCE=.\MyRenameDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyTrace.h
# End Source File
# Begin Source File

SOURCE=.\NewMenu.h
# End Source File
# Begin Source File

SOURCE=PcFile.h
# End Source File
# Begin Source File

SOURCE=Resource.h
# End Source File
# Begin Source File

SOURCE=StdAfx.h
# End Source File
# Begin Source File

SOURCE=ZCONF.H
# End Source File
# Begin Source File

SOURCE=ZLIB.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=res\avi1.bin
# End Source File
# Begin Source File

SOURCE=res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=res\CDDRIVE.ICO
# End Source File
# Begin Source File

SOURCE=res\CLSDFOLD.ICO
# End Source File
# Begin Source File

SOURCE=res\DirOpen.ico
# End Source File
# Begin Source File

SOURCE=res\Downing.ico
# End Source File
# Begin Source File

SOURCE=res\DRIVE.ICO
# End Source File
# Begin Source File

SOURCE=res\EXPLORER.ICO
# End Source File
# Begin Source File

SOURCE=res\fail.ico
# End Source File
# Begin Source File

SOURCE=res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon9.ico
# End Source File
# Begin Source File

SOURCE=res\icon_com.ico
# End Source File
# Begin Source File

SOURCE=res\icon_fin.ico
# End Source File
# Begin Source File

SOURCE=res\NoFix.ico
# End Source File
# Begin Source File

SOURCE=res\PcFile.ico
# End Source File
# Begin Source File

SOURCE=res\PcFile.rc2
# End Source File
# Begin Source File

SOURCE=res\RemoteDisk.ico
# End Source File
# Begin Source File

SOURCE=res\success.ico
# End Source File
# Begin Source File

SOURCE=res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=res\WAIT07.CUR
# End Source File
# Begin Source File

SOURCE=res\Waitdown.ico
# End Source File
# End Group
# Begin Source File

SOURCE=ReadMe.txt
# End Source File
# End Target
# End Project
