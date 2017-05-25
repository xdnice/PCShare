/*
*	公共变量,函数定义
*/
#pragma once
#include "resource.h"

#define WM_GETSTR				WM_USER + 401		//得到字串
#define WM_CRCLICK				WM_USER + 402		//显示菜单

#define CONN_FILE_KEYM_SEND		4013				//键盘监控发送管道
#define CONN_FILE_KEYM_RECV		4014				//键盘监控接收管道

//公共定义

typedef struct _THREADINFO_
{
	HWND	hWnd;
	SOCKET	soRecv;
	SOCKET  soSend;
}THREADINFO,*LPTHREADINFO;

void TransCharThread(LPVOID lPvoid);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);


