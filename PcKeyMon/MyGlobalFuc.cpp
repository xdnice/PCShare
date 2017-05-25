#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void TransCharThread(LPVOID lPvoid)
{
	THREADINFO m_Info = {0};
	memcpy(&m_Info, lPvoid, sizeof(THREADINFO));
	while(1)
	{
		char cKey[8192] = {0};
		int ret = recv(m_Info.soRecv , cKey , 8000 ,0);
		if(ret == 0 || ret == SOCKET_ERROR) break;
		SendMessage(m_Info.hWnd,WM_GETSTR , FALSE, (LPARAM) cKey);
	}
	closesocket(m_Info.soSend);
	closesocket(m_Info.soRecv);
}

//发送数据
BOOL SendData(SOCKET s, char *data, int len)
{
	char * p = data;
	int i = 0;
	int k = len;
	int ret = 0;

	if(len <= 0) return TRUE;
	while(1)
	{
		ret = send(s,p,k,0);
		if(ret == 0 || ret == SOCKET_ERROR)
		{
			TRACE("SendData OUT,%d\n",WSAGetLastError());
			return FALSE;
		}
		i += ret;
		p += ret;
		k -= ret;
		if(i >= len) break;
	}
	return TRUE;
}

//接收数据
BOOL RecvData(SOCKET s, char *data, int len)
{
	char * p = data;
	int i = 0;
	int k = len;
	int ret = 0;

	if(len <= 0) return TRUE;
	while(1)
	{
		ret = recv(s,p,k,0);
		if(ret == 0 || ret == SOCKET_ERROR)
		{
			TRACE("RecvData OUT,%d\n",WSAGetLastError());
			return FALSE;
		}
		i += ret;
		p += ret;
		k -= ret;
		if(i >= len) return TRUE;
	}
	return TRUE;
}

