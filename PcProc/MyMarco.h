/*
*	公共变量,函数定义
*/
#pragma once
#include "resource.h"

//私有定义
#define WM_USERRCLICKPROCESS	WM_USER + 901		//用户击右键(进程)
#define WM_SETMYCURSOR			WM_USER + 902		//光标控制

//公共定义

#define TRAN_DATA_LEN			2048 * 1024			//数据交换长度

#define CLIENT_PROCESS_KILL		5010				//终止用户进程
#define CLIENT_PROCESS_LIST		5018				//刷新进程列表

#define NOT_FIND_ANY_FILE		7000				//找不到任何文件
#define GET_PROCESS_LIST_ERR	7006				//取进程列表失败
#define KILL_PROCESS_ERR		7007				//终止进程失败

#define TRANS_DATA_ERR			8000				//通信错误

#define CONN_FILE_PROC_SEND		4009				//进程管理发送管道
#define CONN_FILE_PROC_RECV		4010				//进程管理接收管道

typedef struct _PROCESSLIST_
{
	char  szExeFile[256]; 
	DWORD th32ProcessID; 
	LONG  pcPriClassBase; 
	DWORD cntThreads; 
}PROCESSLIST,*LPPROCESSLIST;


typedef struct _CLIENTDATA_
{
	char*	m_TransData;
	DWORD	m_TransLen;
	HANDLE  m_WorkEvent;
	UINT	m_Command;
	HANDLE	m_ThreadHandle;
	SOCKET	m_SendSocket;
	SOCKET	m_RecvSocket;
	HWND	hParent;
	BOOL	m_IsWork;
}CLIENTDATA,*LPCLIENTDATA;

void TransBagThread(LPVOID lPvoid);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);
BOOL ProcessOneTrans(LPCLIENTDATA pData);
BOOL SendBag(SOCKET s,char *Data,DWORD &len,UINT &command);
BOOL ReadBag(SOCKET s,char *Data,DWORD &len,UINT &command);
void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen);
void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen);
