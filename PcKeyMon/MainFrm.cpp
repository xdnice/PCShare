// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PcKeyMon.h"
#include "MyEditView.h"
#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_COPYDATA()
	ON_WM_CLOSE()

	ON_WM_RBUTTONUP()

	
	ON_COMMAND(WM_CRCLICK, OnCRclick)
	ON_COMMAND(ID_EMPTY, OnEmpty)
	ON_COMMAND(ID_SAVE, OnSave)
	ON_UPDATE_COMMAND_UI(ID_EMPTY, OnUpdateEmpty)
	ON_UPDATE_COMMAND_UI(ID_SAVE, OnUpdateSave)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构
CMainFrame::CMainFrame()
{
	pKeyView = NULL;
	m_WaitCur = AfxGetApp()->LoadCursor(IDC_CURSOR_WAIT);
	m_CurSorStatus = TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	CFrameWnd::PreCreateWindow(cs);
	cs.style ^= WS_MAXIMIZE;   
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(
		CS_VREDRAW | CS_HREDRAW,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH) GetStockObject(WHITE_BRUSH),
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CCreateContext pCreateContext; 
	pCreateContext.m_pCurrentFrame = this;
	pCreateContext.m_pCurrentDoc = NULL;
	pCreateContext.m_pNewViewClass = RUNTIME_CLASS(CMyEditView);
	pKeyView = (CMyEditView*) CreateView(&pCreateContext,AFX_IDW_PANE_FIRST);
	return TRUE;
}

BOOL CMainFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(m_CurSorStatus)
	{
		SetCursor(m_WaitCur);
		return TRUE;
	}
	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//接收套接字信息
	LPWSAPROTOCOL_INFO pInfo = 
		(LPWSAPROTOCOL_INFO) pCopyDataStruct->lpData;

	if(pCopyDataStruct->dwData == CONN_FILE_KEYM_RECV)
	{
		//发送信息套接字
		m_Info.soSend = WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
	}
	else if(pCopyDataStruct->dwData == CONN_FILE_KEYM_SEND)
	{
		//接收信息套接字
		m_Info.soRecv = WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		m_CurSorStatus = FALSE;
		PostMessage(WM_SETCURSOR);
		StartWork();
	}
	else
		return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
	return TRUE;
}

void CMainFrame::OnClose()
{
	//通知对方断线
	closesocket(m_Info.soSend);
	closesocket(m_Info.soRecv);
	CFrameWnd::OnClose();
}

void CMainFrame::StartWork(void)
{
	m_Info.hWnd = pKeyView->GetSafeHwnd();
	_beginthread(TransCharThread, 0, &m_Info);
}

void CMainFrame::OnEmpty()
{
	pKeyView->GetEditCtrl().SetWindowText("");
}

void CMainFrame::OnSave()
{
	pKeyView->SaveChar();
}

void CMainFrame::OnUpdateEmpty(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pKeyView->GetEditCtrl().LineLength(0) > 0);
}

void CMainFrame::OnUpdateSave(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pKeyView->GetEditCtrl().LineLength(0) > 0);
}

void CMainFrame::OnEditCopy() 
{
	pKeyView->GetEditCtrl().Copy();
}

void CMainFrame::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	int nStart = 0, nEnd = 0;
	pKeyView->GetEditCtrl().GetSel(nStart, nEnd);
	pCmdUI->Enable(nStart != nEnd);
}

void CMainFrame::OnCRclick() 
{
	CPoint m_point;
	CMenu m_menu;
	m_menu.LoadMenu(IDR_RIGHT);
	GetCursorPos(&m_point);
	SetForegroundWindow();   
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
		TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
	m_menu.DestroyMenu();
}

