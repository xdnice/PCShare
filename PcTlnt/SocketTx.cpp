// SocketTx.cpp: implementation of the CSocketTx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcTlnt.h"
#include "SocketTx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HANDLE stdin1;
extern HANDLE stdout1;
extern HANDLE stderr1;

CSocketTx::CSocketTx(SOCKET hSocket,HANDLE &hThread)
{
DWORD dwRet;

	m_nExit = 0;
	m_hThread = NULL;
	m_hSocket = hSocket;

	m_hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE) SendTh,(LPVOID)this,0,&dwRet);
	if ( m_hThread == NULL ) return;
	hThread = m_hThread;
}
CSocketTx::~CSocketTx()
{
	m_nExit = 1;
}

void GetTxLine(char* pBuf)
{
	CONSOLE_SCREEN_BUFFER_INFO m_InitInfo = {0};
	GetConsoleScreenBufferInfo(stdout1,&m_InitInfo);

	int i = 0;
	while(1)
	{
		INPUT_RECORD keyRec;
		DWORD state=0, res;
		char ch = 0;

		ReadConsoleInput(stdin1, &keyRec, 1, &res);
		if (keyRec.EventType == KEY_EVENT)
		{
			if(!keyRec.Event.KeyEvent.bKeyDown) 
			{
				continue;
			}
			ch = keyRec.Event.KeyEvent.uChar.AsciiChar;
		}

		CONSOLE_SCREEN_BUFFER_INFO m_Info = {0};
		GetConsoleScreenBufferInfo(stdout1,&m_Info);

		if(ch == '\r') break;
		if(ch == '\b')
		{
			if(i > 0)
			{
				COORD co = {0};
				co.X = m_Info.dwCursorPosition.X;
				co.Y = m_Info.dwCursorPosition.Y;
				pBuf[i] = 0;
				i--;
				co.X -= 1;
				SetConsoleCursorPosition(stdout1,co);
				DWORD dwrite = 0;
				WriteConsoleOutputCharacter(stdout1," ",1,co,&dwrite);
			}
			continue;
		}
		
		if(ch < 30 || ch > 126) continue;
		if(m_Info.dwCursorPosition.X == m_Info.dwMaximumWindowSize.X - 1)
			continue;
		
		COORD co = {0};
		co.X = m_Info.dwCursorPosition.X;
		co.Y = m_Info.dwCursorPosition.Y;
		DWORD dwrite = 0;
		WriteConsoleOutputCharacter(stdout1,&ch,1,co,&dwrite);
		pBuf[i] = ch;
		i++;
		co.X += 1;
		SetConsoleCursorPosition(stdout1,co);
	}
	strcat(pBuf,"\r\n");
}

DWORD CSocketTx::SendTh(CSocketTx *pSocketTx)
{
	unsigned long dwLen;
	int nRet;
	dwLen = 1;
	while(1)
	{
		if (pSocketTx->m_nExit == 1 ) 
		{
			ExitThread(0); 
			return 0; 
		}

		WaitForSingleObject(stdin1,INFINITE);
		char m_Text[1024] = {0};
		GetTxLine(m_Text);
		if(StrCmpNI(m_Text,"exit",4) == 0)
		{
			ExitThread(0); 
			return 0; 
		}

		CONSOLE_SCREEN_BUFFER_INFO m_Info = {0};
		GetConsoleScreenBufferInfo(stdout1,&m_Info);
		COORD co = {0};
		co.X = m_Info.dwCursorPosition.X;
		co.Y = m_Info.dwCursorPosition.Y;
		co.X -= (SHORT) strlen(m_Text) - 2;
		SetConsoleCursorPosition(stdout1,co);

		nRet = send(pSocketTx->m_hSocket,m_Text,strlen(m_Text),0);
		if ( nRet == SOCKET_ERROR ) 
		{ 
			pSocketTx->m_nExit = 0; 
			continue;
		}
	}
	return 0;
}
