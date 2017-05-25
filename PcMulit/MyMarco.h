/*
*	公共变量,函数定义
*/
#pragma once
#include "resource.h"

#define CONN_FILE_MULT_SEND		4015				//视频监控发送管道
#define CONN_FILE_MULT_RECV		4016				//视频监控接收管道

#define WM_GETONEFRAME		WM_USER + 401 

//公共定义

typedef struct _THREADINFO_
{
	HWND	hWnd;
	SOCKET	soRecv;
	SOCKET  soSend;
	char*	pSrcData;
	char*	pDesData;
}THREADINFO,*LPTHREADINFO;

void TransMuiltThread(LPVOID lPvoid);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);


