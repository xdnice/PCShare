// MyFrameTrans.h: interface for the CMyFrameTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFRAMETRANS_H__67FF906E_4BD3_43EB_A125_84D827CA3C95__INCLUDED_)
#define AFX_MYFRAMETRANS_H__67FF906E_4BD3_43EB_A125_84D827CA3C95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHttpPipeBase.h"

#define CMD_FRAME_MOUSE_STATE		1					//Êó±ê×´Ì¬
#define CMD_FRAME_KEY_STATE			2					//¼üÅÌ×´Ì¬
#define CMD_FRAME_KEY_ALL			3					//·¢ËÍCTRL+ALT+DEL

typedef struct _MOUSEINFO_
{
	WORD x;
	WORD y;
	WORD state;
	char ch;
	char cmd;
}MOUSEINFO,*LPMOUSEINFO;

class CMyFrameTrans : public CMyHttpPipeBase  
{
public:
	
	CMyFrameTrans();
	virtual ~CMyFrameTrans();
	virtual BOOL StartWork(char* m_ServerAddr, int m_ServerPort, 
							int nSend, int nRecv);
	void ProcessCmd();

private:
	SIZE	GetFrameSize();
	HBITMAP GetFrameCopy();
	void	GetOneFrame(BYTE* pFrameData,
						BYTE* pOldFrameData,
						BYTE* pTmpFrameData , 
						DWORD &m_FrameLen);
	void	InitBitmapInfo();
	void	MoveCursor(LPMOUSEINFO pInfo);
	void	HitKeyState(LPMOUSEINFO pInfo);
	BOOL	InitData();
	
	LPBITMAPINFOHEADER	lpbi;

	SIZE		m_FrameSize;
	DWORD		dBitSize;
	BYTE*		pOldData;
	BYTE*		pTmpData;
	BYTE*		pCurData;
	BYTE*		pHeadInfo;
	DWORD		m_LineBitmapSize;
	DWORD		dwPaletteSize;
	DWORD		m_SrcFrameLen;
	DWORD		m_FrameHeadLen;
	HANDLE		hExitEvent;

	static void MouseThread(LPVOID);
};

#endif // !defined(AFX_MYFRAMETRANS_H__67FF906E_4BD3_43EB_A125_84D827CA3C95__INCLUDED_)
