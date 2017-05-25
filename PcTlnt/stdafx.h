// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once



#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将为显式的

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 头中排除极少使用的资料
#endif

#include <afx.h>
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxdtctl.h>		// MFC 对 Internet Explorer 4 公共控件的支持
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <iostream>
#include <Winsock2.h>
#include <afxsock.h>
#include <conio.h>
#include <signal.h>
#include <Shlwapi.h>
#include <iostream>
#include <tchar.h>

#pragma comment(lib,"ws2_32.lib")

#define CONN_FILE_TLNT_SEND		4005				//超级终端发送管道
#define CONN_FILE_TLNT_RECV		4006				//超级终端接收管道

// TODO: 在此处引用程序要求的附加头文件
