// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PcService.h"
#include "MyServicesDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_COPYDATA()

	ON_COMMAND(ID_SERVICES_ENUM, OnEnumServices)
	ON_UPDATE_COMMAND_UI(ID_SERVICES_ENUM, OnUpdateEnumServices)
	ON_COMMAND(ID_SERVICES_START, OnServicesStart)
	ON_COMMAND(ID_SERVICES_STOP, OnServicesStop)
	ON_UPDATE_COMMAND_UI(ID_SERVICES_START, OnUpdateServicesStart)
	ON_UPDATE_COMMAND_UI(ID_SERVICES_STOP, OnUpdateServicesStop)
	ON_COMMAND(ID_SERVICES_ATTRIB, OnServicesAttrib)
	ON_UPDATE_COMMAND_UI(ID_SERVICES_ATTRIB, OnUpdateServicesAttrib)
	ON_COMMAND(ID_SERVICES_DELETE, OnServicesDelete)
	ON_UPDATE_COMMAND_UI(ID_SERVICES_DELETE, OnUpdateServicesDelete)

	ON_UPDATE_COMMAND_UI(IDS_MYDIRFILES, OnUpdateMyFiles)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_USERRCLICKSERVICES,OnUserRClickProcess)
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

	if(pCopyDataStruct->dwData == CONN_FILE_SERV_RECV)
	{
		m_MissionData.m_SendSocket = 
			WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		return TRUE;
	}
	if(pCopyDataStruct->dwData == CONN_FILE_SERV_SEND)
	{
		m_MissionData.m_RecvSocket = 
			WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		m_CurSorStatus = FALSE;
		PostMessage(WM_SETCURSOR);
		OnEnumServices();
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
	pCreateContext.m_pNewViewClass = RUNTIME_CLASS(CMyServicesView);
	pServicesView = (CMyServicesView *) CreateView(&pCreateContext,AFX_IDW_PANE_FIRST);
	ASSERT(pServicesView);
	return TRUE;
}

void CMainFrame::ShowResponse(UINT m_Response)
{
	char m_Text[4096] = {0};
	switch(m_Response)
	{
		case ENUM_SERVICES_FAIL			:	strcpy(m_Text,"取服务列表失败");break;
		case CONTROL_SERVICES_FAIL		:	strcpy(m_Text,"控制服务失败");break;
		case TRANS_DATA_ERR				:	strcpy(m_Text,"通信失败");break;
		default							:	return;
	}
	m_wndStatusBar.SetPaneText(0,m_Text);
}


void CMainFrame::OnUpdateMyFiles(CCmdUI* pCmdUI) 
{
	char m_Text[256] = {0};
	sprintf(m_Text,"共有%d个服务",pServicesView->GetListCtrl().GetItemCount());
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
 	m_menu.LoadMenu(IDR_MENU_SERVICES);
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

void CMainFrame::OnEnumServices()
{
	m_MissionData.m_TransLen = 0;
	m_MissionData.m_Command = CLIENT_ENUM_SERVICES;
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	if(m_MissionData.m_Command == NOT_FIND_ANY_FILE)
	{
		pServicesView->DeleteAllItems();
		return ;
	}
	if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}

	DWORD dwFileSize = m_MissionData.m_TransLen;
	BYTE * m_DesBuf = (LPBYTE) m_MissionData.m_TransData;
	pServicesView->DeleteAllItems();
	LPMYSERVICES pData = (LPMYSERVICES) m_DesBuf;
	DWORD m_Status = 0;
	for(DWORD i = 0; i < dwFileSize/sizeof(MYSERVICES);i++)
	{
		pServicesView->InsertItem(&pData[i]);
	}
}

void CMainFrame::OnServicesStart() 
{
	MyControlServices(0);
}

void CMainFrame::OnServicesStop() 
{
	MyControlServices(1);
}

void CMainFrame::OnServicesDelete() 
{
	if(MessageBox("真要删除?","删除服务",
		MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
		return;

	int nItem = pServicesView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	if(nItem == -1) return;
	LPMYSERVICES pServices = 
		(LPMYSERVICES) pServicesView->GetListCtrl().GetItemData(nItem);
	strcpy(m_MissionData.m_TransData,pServices->m_Name);
	m_MissionData.m_TransLen = strlen(m_MissionData.m_TransData);
	m_MissionData.m_Command = CLIENT_DELETE_SERVICE;
	if(!ProcessOneTrans(&m_MissionData) ||
		m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	pServicesView->GetListCtrl().DeleteItem(nItem);
}

void CMainFrame::OnUpdateServicesDelete(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	if(pServicesView->GetListCtrl().
		GetSelectedCount() == 1)
		IsEnable = TRUE;
	pCmdUI->Enable(IsEnable	&& !m_MissionData.m_IsWork);
}

void CMainFrame::MyControlServices(BYTE flag)
{
	int nItem = pServicesView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	if(nItem == -1)	return;
	
	LPMYSERVICES pServices = 
		(LPMYSERVICES) pServicesView->GetListCtrl().GetItemData(nItem);
	strcpy(m_MissionData.m_TransData + 1,pServices->m_Name);
	m_MissionData.m_TransData[0] = flag;
	m_MissionData.m_TransLen = 1 + strlen(m_MissionData.m_TransData + 1);
	m_MissionData.m_Command = CLIENT_CONTROL_SERVICES;
	if(!ProcessOneTrans(&m_MissionData) ||
		m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	switch(flag)
	{
		case 0 : pServicesView->GetListCtrl().SetItemText(nItem,2,"已运行");break;
		case 1 : pServicesView->GetListCtrl().SetItemText(nItem,2,"已停止");break;
		case 2 : pServicesView->GetListCtrl().DeleteItem(nItem);break;
		default: break;
	}
}

void CMainFrame::OnUpdateEnumServices(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_MissionData.m_IsWork );
}

void CMainFrame::OnUpdateServicesStart(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	if(pServicesView->GetListCtrl().GetSelectedCount() == 1)
	{
		int nItem = pServicesView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		if(pServicesView->GetListCtrl().GetItemText(nItem,2) == "已停止")
		{
			IsEnable = TRUE;
		}
	}
	pCmdUI->Enable(IsEnable	&& !m_MissionData.m_IsWork );
}

void CMainFrame::OnUpdateServicesStop(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	if(pServicesView->GetListCtrl().GetSelectedCount() == 1)
	{
		int nItem = pServicesView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		if(pServicesView->GetListCtrl().GetItemText(nItem,2) == "已运行")
		{
			IsEnable = TRUE;
		}
	}
	pCmdUI->Enable(IsEnable	&& !m_MissionData.m_IsWork );
}

void CMainFrame::OnServicesAttrib() 
{
	int nItem = pServicesView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	if(nItem == -1) return;
	LPMYSERVICES pServices =
		(LPMYSERVICES) pServicesView->GetListCtrl().GetItemData(nItem);

	CMyServicesDlg dlg(pServices);
	if(dlg.DoModal() != IDOK || !dlg.m_IsModify)
		return;

	LPMYSERVICES pTmpServices = (LPMYSERVICES) m_MissionData.m_TransData;
	memcpy(pTmpServices,pServices,sizeof(MYSERVICES));
	pTmpServices->dwStartType = dlg.m_Type;
	m_MissionData.m_TransLen = sizeof(MYSERVICES);
	m_MissionData.m_Command = CLIENT_CONFIG_SERVICES;
	if(!ProcessOneTrans(&m_MissionData) ||
		m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	pServices->dwStartType = dlg.m_Type;
	pServicesView->UpDateItem(nItem,pServices);
}

void CMainFrame::OnUpdateServicesAttrib(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pServicesView->GetListCtrl().GetSelectedCount() == 1
		&& !m_MissionData.m_IsWork);
}