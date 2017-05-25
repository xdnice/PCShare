// MyFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MyFrameWnd.h"
#include ".\myframewnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFrameWnd

IMPLEMENT_DYNCREATE(CMyFrameWnd, CFrameWnd)

CMyFrameWnd::CMyFrameWnd()
{
	m_WaitCur = AfxGetApp()->LoadCursor(IDC_CURSOR_WAIT);
	m_CurSorStatus = TRUE;
	pFrameView = NULL;
	memset(&m_FrameInfo, 0, sizeof(m_FrameInfo));
	m_FrameInfo.pDesData = new char[3670017];
	m_FrameInfo.pSrcData = new char[3145729];
}

CMyFrameWnd::~CMyFrameWnd()
{
	delete [] m_FrameInfo.pSrcData;
	delete [] m_FrameInfo.pDesData;
}

BEGIN_MESSAGE_MAP(CMyFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CMyFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FRAME_CONTROL, OnFrameControl)
	ON_COMMAND(ID_FRAME_SAVE, OnFrameSave)
	ON_COMMAND(ID_FRAME_CTRL, OnFrameCtrl)
	ON_WM_COPYDATA()
	ON_UPDATE_COMMAND_UI (ID_FRAME_INFO,OnUpdatePane )
	ON_UPDATE_COMMAND_UI(ID_FRAME_CONTROL, OnUpdateFrameControl)
	ON_UPDATE_COMMAND_UI(ID_FRAME_SAVE, OnUpdateFrameSave)
	ON_UPDATE_COMMAND_UI(ID_FRAME_CTRL, OnUpdateFrameCtrl)
	//}}AFX_MSG_MAP
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFrameWnd message handlers

static UINT indicatorsframe[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_FRAME_INFO,
};

int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT|TBSTYLE_LIST, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC|WS_EX_RTLREADING   ) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR_FRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicatorsframe,
		  sizeof(indicatorsframe)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	m_ImageList.Create(16, 16, TRUE | ILC_COLOR8, 4, 0);
	HICON hIcon = NULL;
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_INPUT), IMAGE_ICON, 16, 16, 0);
	m_ImageList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_SAVE), IMAGE_ICON, 16, 16, 0);
	m_ImageList.Add(hIcon);
//	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
//		MAKEINTRESOURCE(IDI_ICON_CTRL), IMAGE_ICON, 16, 16, 0);
//	m_ImageList.Add(hIcon);

	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_wndToolBar.SetButtonStyle(0,TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonStyle(1,TBBS_AUTOSIZE);
//	m_wndToolBar.SetButtonStyle(2,TBBS_AUTOSIZE);
	m_wndToolBar.SetButtonInfo(0,ID_FRAME_CONTROL,TBBS_CHECKBOX,0);
	m_wndToolBar.SetButtonText(0,"控制鼠标和键盘输入");
	m_wndToolBar.SetButtonText(1,"保存当前屏幕内容");
//	m_wndToolBar.SetButtonText(2,"发送CTRL+ALT+DEL");
	return 0;
}

void CMyFrameWnd::OnFrameSave()
{
	pFrameView->SaveFrame();
}

void CMyFrameWnd::OnFrameControl()
{
	if(m_wndToolBar.GetToolBarCtrl().IsButtonChecked(ID_FRAME_CONTROL))
	{
		pFrameView->m_MouseSocket = m_FrameInfo.soSend;
	}
	else
		pFrameView->m_MouseSocket = 0;
}

BOOL CMyFrameWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CCreateContext pCreateContext; 
	pCreateContext.m_pCurrentFrame = this;
	pCreateContext.m_pCurrentDoc = NULL;
	pCreateContext.m_pNewViewClass = 
		RUNTIME_CLASS(CMyFrameView);
	pFrameView = (CMyFrameView*) 
		CreateView(&pCreateContext,AFX_IDW_PANE_FIRST);
	return TRUE;
}

BOOL CMyFrameWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	CFrameWnd::PreCreateWindow(cs);
	cs.style ^= WS_MAXIMIZE;   
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(
		CS_VREDRAW | CS_HREDRAW,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH) GetStockObject(WHITE_BRUSH),
		AfxGetApp()->LoadIcon(IDI_ICON_FRAME));
	return TRUE;	
}

void CMyFrameWnd::OnClose() 
{
	//通知对方断线
	closesocket(m_FrameInfo.soSend);
	closesocket(m_FrameInfo.soRecv);
	CFrameWnd::OnClose();
}

void CMyFrameWnd::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	if(pFrameView != NULL && cx > 0)
	{
		UINT nID,nStyle;
		int Width;
		m_wndStatusBar.GetPaneInfo(1,nID,nStyle,Width);
		Width = cx * 1/6 - 15;
		m_wndStatusBar.SetPaneInfo(1,nID,nStyle,Width);
	}	
}

BOOL CMyFrameWnd::StartWork()
{
	m_FrameInfo.hWnd = pFrameView->GetSafeHwnd();
	_beginthread(TransFrameThread,0,&m_FrameInfo);
	return TRUE;
}

BOOL CMyFrameWnd::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	//接收套接字信息
	LPWSAPROTOCOL_INFO pInfo = 
		(LPWSAPROTOCOL_INFO) pCopyDataStruct->lpData;

	if(pCopyDataStruct->dwData == CONN_FILE_FRAM_RECV)
	{
		//发送信息套接字
		m_FrameInfo.soSend = WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
	}
	else if(pCopyDataStruct->dwData == CONN_FILE_FRAM_SEND)
	{
		//接收信息套接字
		m_FrameInfo.soRecv = WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		m_CurSorStatus = FALSE;
		PostMessage(WM_SETCURSOR);
		StartWork();
	}
	else
		return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
	return TRUE;
}

void CMyFrameWnd::OnFrameCtrl()
{
	MOUSEINFO m_MouseInfo = {0};
	m_MouseInfo.cmd = CMD_FRAME_KEY_ALL;
	pFrameView->ExecCmd(&m_MouseInfo);
}

void CMyFrameWnd::OnUpdatePane(CCmdUI *pCmdUI)  
{
	char m_Text[256];
	pFrameView->GetSize(m_Text);
	pCmdUI->SetText(m_Text);
}

void CMyFrameWnd::OnUpdateFrameControl(CCmdUI *pCmdUI)  
{
	pCmdUI->Enable(m_FrameInfo.soRecv);
}

void CMyFrameWnd::OnUpdateFrameSave(CCmdUI *pCmdUI)  
{
	pCmdUI->Enable(m_FrameInfo.soRecv);
}

void CMyFrameWnd::OnUpdateFrameCtrl(CCmdUI *pCmdUI)  
{
	pCmdUI->Enable(m_FrameInfo.soRecv);
}

BOOL CMyFrameWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(m_CurSorStatus)
	{
		SetCursor(m_WaitCur);
		return TRUE;
	}
	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}
