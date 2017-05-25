// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__FF92BA34_7FC7_4854_9C78_0F5924613CDD__INCLUDED_)
#define AFX_STDAFX_H__FF92BA34_7FC7_4854_9C78_0F5924613CDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER 0x602
#define _WIN32_IE 0x0600

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Advapi32.lib")


// TODO: reference additional headers your program requires here
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__FF92BA34_7FC7_4854_9C78_0F5924613CDD__INCLUDED_)
