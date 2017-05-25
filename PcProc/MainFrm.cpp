// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PcProc.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_COPYDATA()

	ON_UPDATE_COMMAND_UI(IDS_MYDIRFILES, OnUpdateMyFiles)
	ON_COMMAND(ID_PROCESS_KILL, OnProcessKill)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_KILL, OnUpdateProcessKill)
	ON_COMMAND(ID_PROCESS_FLUSH, OnProcessFlush)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_FLUSH, OnUpdateProcessFlush)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_USERRCLICKPROCESS,OnUserRClickProcess)
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_SETMYCURSOR,OnSetMyCursor)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_MYDIRFILES,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	m_WaitCur = AfxGetApp()->LoadCursor(IDC_CURSOR_WAIT);
	m_CurSorStatus = TRUE;
	memset(&m_MissionData,0,sizeof(CLIENTDATA));
	m_MissionData.m_WorkEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_MissionData.m_TransData = new char[TRAN_DATA_LEN + 100];
}

CMainFrame::~CMainFrame()
{
	if(m_MissionData.m_TransData)
	{
		CloseHandle(m_MissionData.m_WorkEvent);
		delete [] m_MissionData.m_TransData;
	}
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

	m_MissionData.hParent = GetSafeHwnd();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
		if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式
	cs.style ^= WS_MAXIMIZE;   
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(
		CS_VREDRAW | CS_HREDRAW,
		::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH) ::GetStockObject(WHITE_BRUSH),
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




BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//接收套接字信息
	LPWSAPROTOCOL_INFO pInfo = 
		(LPWSAPROTOCOL_INFO) pCopyDataStruct->lpData;

	if(pCopyDataStruct->dwData == CONN_FILE_PROC_RECV)
	{
		m_MissionData.m_SendSocket = 
			WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		return TRUE;
	}
	if(pCopyDataStruct->dwData == CONN_FILE_PROC_SEND)
	{
		m_MissionData.m_RecvSocket = 
			WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		
		m_CurSorStatus = FALSE;
		PostMessage(WM_SETCURSOR);
		OnProcessFlush();
		return TRUE;
	}
	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	CCreateContext pCreateContext; 
	pCreateContext.m_pCurrentFrame = this;
	pCreateContext.m_pCurrentDoc = NULL;
	
	//进程列表视
	pCreateContext.m_pNewViewClass = RUNTIME_CLASS(CMyProcessListView);
	pProcessListView = (CMyProcessListView *) CreateView(&pCreateContext,AFX_IDW_PANE_FIRST);
	ASSERT(pProcessListView);
	return TRUE;
}

void CMainFrame::ShowResponse(UINT m_Response)
{
	char m_Text[4096] = {0};
	switch(m_Response)
	{
		case GET_PROCESS_LIST_ERR		:	strcpy(m_Text,"取进程列表失败");break;
		case KILL_PROCESS_ERR			:	strcpy(m_Text,"终止进程失败");break;
		case TRANS_DATA_ERR				:	strcpy(m_Text,"通信失败");break;
		default							:	return;
	}
	m_wndStatusBar.SetPaneText(0,m_Text);
}

void CMainFrame::OnProcessKill() 
{
	int nItem = pProcessListView->GetListCtrl().GetNextItem(-1, LVNI_SELECTED);
	char m_TmpBuf[2048];
	memset(m_TmpBuf,0,sizeof(m_TmpBuf));
	strcpy(m_TmpBuf,(LPCTSTR) pProcessListView->GetListCtrl().GetItemText(nItem,0));
	*((DWORD*) m_MissionData.m_TransData) = atol(m_TmpBuf);
	m_MissionData.m_TransLen = sizeof(DWORD);
	m_MissionData.m_Command = CLIENT_PROCESS_KILL;
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}	
	pProcessListView->GetListCtrl().DeleteItem(nItem);
}

void CMainFrame::OnUpdateProcessKill(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pProcessListView->GetListCtrl().GetSelectedCount() == 1
		&& !m_MissionData.m_IsWork);
}

void CMainFrame::OnProcessFlush() 
{
	m_MissionData.m_TransLen = 0;
	m_MissionData.m_Command = CLIENT_PROCESS_LIST;
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	if(m_MissionData.m_Command == NOT_FIND_ANY_FILE)
	{
		pProcessListView->GetListCtrl().DeleteAllItems();
		return ;
	}
	if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	DWORD dwFileSize = m_MissionData.m_TransLen;
	BYTE * m_DesBuf = (LPBYTE) m_MissionData.m_TransData;
	pProcessListView->GetListCtrl().DeleteAllItems();
	LPPROCESSLIST pList = (LPPROCESSLIST) m_DesBuf;
	for(DWORD i = 0; i < (dwFileSize/sizeof(PROCESSLIST)); i++)
	{
		pProcessListView->InsertMyItem(&pList[i]);
	}
}

void CMainFrame::OnUpdateProcessFlush(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_MissionData.m_IsWork);
}

void CMainFrame::OnUpdateMyFiles(CCmdUI* pCmdUI) 
{
	char m_Text[256] = {0};
	sprintf(m_Text,"共有%d个进程",pProcessListView->GetListCtrl().GetItemCount());
	pCmdUI->SetText(m_Text);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	if(m_wndStatusBar.GetSafeHwnd())
	{
		UINT nID,nStyle;
		int Width;
		m_wndStatusBar.GetPaneInfo(1,nID,nStyle,Width);
		Width = cx/4;
		m_wndStatusBar.SetPaneInfo(1,nID,nStyle,Width);
	}
}
void CMainFrame::OnClose()
{
	SetEvent(m_MissionData.m_WorkEvent);
	closesocket(m_MissionData.m_SendSocket);
	closesocket(m_MissionData.m_RecvSocket);
	CFrameWnd::OnClose();
}

LRESULT CMainFrame::OnUserRClickProcess(WPARAM wParam,LPARAM lParam)
{
	CPoint m_point;
 	CMenu m_menu;
 	m_menu.LoadMenu(IDR_MENU_PROCESS_LIST);
 	GetCursorPos(&m_point);
 	SetForegroundWindow();   
 	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
 		TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
 	m_menu.DestroyMenu();	
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

LRESULT CMainFrame::OnSetMyCursor(WPARAM wParam,LPARAM lParam)
{
	if(wParam)
	{
		m_CurSorStatus = TRUE;
		PostMessage(WM_SETCURSOR);
	}
	else
	{
		m_CurSorStatus = FALSE;
		PostMessage(WM_SETCURSOR);
	}
	return TRUE;
}