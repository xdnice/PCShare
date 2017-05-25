// MyMulitTrans.h: interface for the CMyMulitTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMULITTRANS_H__CE3018B2_F422_49BA_852C_30C980BA6B2A__INCLUDED_)
#define AFX_MYMULITTRANS_H__CE3018B2_F422_49BA_852C_30C980BA6B2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHttpPipeBase.h"
#include <vfw.h>

#define IMAGE_WIDTH       176
#define IMAGE_HEIGHT      144

class CMyMulitTrans : public CMyHttpPipeBase  
{
public:
	CMyMulitTrans();
	virtual ~CMyMulitTrans();

	virtual BOOL StartWork(char* m_ServerAddr, int m_ServerPort, 
							int nSend, int nRecv);
	HWND hCaphWnd;
	BITMAPINFO m_BmpInfo;

	BOOL Initialize();
	BOOL SetCapturePara();
	void Destroy();
	void GetDriverCaps();
	void SetAudioFormat();
 
	BOOL StartCapture();
	BOOL StopCapture();

	BYTE*	pDesData;
	HANDLE	hExitEvent;
	void	ProcessCmd();
	BOOL	SleepWait();
	static void RecvThread(LPVOID);
	static LRESULT CALLBACK OnCaptureVideo(HWND hWnd, LPVIDEOHDR lpheader) ;
};

#endif // !defined(AFX_MYMULITTRANS_H__CE3018B2_F422_49BA_852C_30C980BA6B2A__INCLUDED_)
