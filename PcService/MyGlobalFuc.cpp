
#include "stdafx.h"
#include "zlib.h"
#include "MyMarco.h"
#include <process.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//客户管理数据传输
void TransBagThread(LPVOID lPvoid)
{
	LPCLIENTDATA pData = (LPCLIENTDATA) lPvoid;

	//数据传输
	if(!SendBag(pData->m_SendSocket,pData->m_TransData,
		pData->m_TransLen,pData->m_Command) ||
		!ReadBag(pData->m_RecvSocket,pData->m_TransData,
		pData->m_TransLen,pData->m_Command))
	{
		//数据传输失败
		pData->m_Command = TRANS_DATA_ERR;
		SetEvent(pData->m_WorkEvent);
		return ;
	}
	
	//查看数据类型
	if(pData->m_TransLen == 0)
	{
		//无回带数据
		SetEvent(pData->m_WorkEvent);
		return ;
	}

	//解压缩数据
	DWORD m_TmpLen = pData->m_TransLen;
	BYTE* pTmpData = new BYTE[m_TmpLen];
	memcpy(pTmpData,pData->m_TransData,m_TmpLen);
	pData->m_TransLen = TRAN_DATA_LEN;
	uncompress((LPBYTE) pData->m_TransData,
		&pData->m_TransLen,pTmpData,m_TmpLen);
	delete [] pTmpData;
	SetEvent(pData->m_WorkEvent);
}

BOOL WaitForTrans(HANDLE m_WaitEvent, HWND hWnd)
{
	MSG  msg; 
	while (1) 
	{ 
		if(WaitForSingleObject(m_WaitEvent,1) 
			!= WAIT_TIMEOUT)
			break;
	
		while(PeekMessage(&msg, NULL,  0, 0, PM_REMOVE)) 
		{ 
			if(msg.message == WM_CHAR && msg.wParam == 'q')
			{
				return FALSE;
			}

			//处理消息
			if(((msg.message<WM_MOUSEFIRST) ||
				(msg.message > WM_MOUSELAST)) &&
				(!AfxGetApp()->PreTranslateMessage(&msg) &&
				msg.message != WM_TIMER))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} 
	} 
	return TRUE;
}

//界面完成一次控制任务
BOOL ProcessOneTrans(LPCLIENTDATA pData)
{
	if(pData->m_IsWork) return FALSE;

	//启动命令执行线程
	pData->m_IsWork = TRUE;
	PostMessage(pData->hParent,WM_SETMYCURSOR,(WPARAM) TRUE,NULL);
	ResetEvent(pData->m_WorkEvent);
	_beginthread(TransBagThread, 0, pData);

	//等待任务完成
	if(!WaitForTrans(pData->m_WorkEvent,pData->hParent) ||
		pData->m_Command == TRANS_DATA_ERR)
	{
		pData->m_IsWork = FALSE;
		pData->m_TransLen = 0;
		return FALSE;
	}

	//命令执行成功
	PostMessage(pData->hParent,WM_SETMYCURSOR,(WPARAM) FALSE,NULL);
	pData->m_IsWork = FALSE;
	return TRUE;
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

BOOL ReadBag(SOCKET s, char *Data,DWORD &len,UINT &command)
{
	//接收命令
	if(!RecvData(s, (char*) &command, sizeof(UINT)))
		return FALSE;

	//接收长度
	if(!RecvData(s, (char*) &len, sizeof(DWORD)))
		return FALSE;

	TRACE("ReadBag : len = %d,command = %d\n",len,command);

	//查看数据长度
	if(len <= 0) return TRUE;

	//接收数据
	if(!RecvData(s, Data, len)) return FALSE;

	return TRUE;
}

BOOL SendBag(SOCKET s, char *Data, DWORD &len,UINT &command)
{
	//发送命令
	if(!SendData(s, (char*) &command, sizeof(UINT)))
		return FALSE;

	//发送长度
	if(!SendData(s, (char*) &len, sizeof(DWORD)))
		return FALSE;

	TRACE("SendBag : len = %d,command = %d\n",len,command);

	//查看数据长度
	if(len <= 0) return TRUE;

	//发送数据
	if(!SendData(s, Data, len)) return FALSE;

	return TRUE;
}

void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen)
{
	int i, j;

		for(i = 0; i < BcdStrLen; i++)
		{
			j = (BcdStr[i] >> 4) & 0x0f;
                	
			if(j > 9)
				AscStr[2 * i] = j + 'A' - 10;
			else
				AscStr[2 * i] = j + '0';

			j = BcdStr[i] & 0x0f;

			if(j > 9)
				AscStr[2 * i + 1 ] = j + 'A' - 10;
			else
				AscStr[2 * i + 1] = j + '0';

		}

}

void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen)
{
	
	int i, j, k;

		for(i = 0; i < AscStrLen; i++)
		{
        	
			if( ( AscStr[i] >= '0' ) && ( AscStr[i] <= '9' ) )

				j = AscStr[i] - '0';

			else if ( ( AscStr[i] >= 'a' ) && ( AscStr[i] <= 'z' ) )

				j = AscStr[i] - 'a' + 0x0a;

			else 

				j = AscStr[i] - 'A' + 0x0a;

			i++;

			if( ( AscStr[i] >= '0' ) && ( AscStr[i] <= '9' ) )

				k = AscStr[i] - '0';

			else if ( ( AscStr[i] >= 'a' ) && ( AscStr[i] <= 'z' ) )

				k = AscStr[i] - 'a' + 0x0a;

			else

				k = AscStr[i] - 'A' + 0x0a;

			BcdStr[i / 2] = (j << 4) | k;

		}
} 



