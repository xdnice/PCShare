/*
*	公共变量,函数定义
*/
#pragma once

#include "resource.h"

#define WM_ONEFRAME				WM_USER + 915		//一帧图象

#define CONN_FILE_FRAM_SEND		4003				//屏幕监控发送管道
#define CONN_FILE_FRAM_RECV		4004				//屏幕监控接收管道

#define CMD_FRAME_MOUSE_STATE	1					//鼠标状态
#define CMD_FRAME_KEY_STATE		2					//键盘状态
#define CMD_FRAME_KEY_ALL		3					//发送CTRL+ALT+DEL

//公共定义

typedef struct _FRAMINFO_
{
	HWND	hWnd;
	SOCKET	soRecv;
	SOCKET	soSend;
	char*	pDesData;
	char*	pSrcData;
}FRAMINFO,*LPFRAMINFO;

typedef struct _MOUSEINFO_
{
	WORD x;
	WORD y;
	WORD state;
	char ch;
	char cmd;
}MOUSEINFO,*LPMOUSEINFO;

void TransFrameThread(LPVOID lPvoid);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);


