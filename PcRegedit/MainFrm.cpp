// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PcRegedit.h"
#include "MyRegEditValue.h"
#include "MainFrm.h"
#include ".\mainfrm.h"
#include "MyRenameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()

	ON_COMMAND(ID_REG_RIGHT_DELETE, OnRegRightDelete)
	ON_UPDATE_COMMAND_UI(ID_REG_RIGHT_DELETE, OnUpdateRegRightDelete)
	ON_COMMAND(ID_REG_LEFT_DELETE, OnRegLeftDelete)
	ON_COMMAND(ID_REG_RIGHT_CREATE_BIN, OnRegRightCreateBin)
	ON_COMMAND(ID_REG_RIGHT_CREATE_STR, OnRegRightCreateStr)
	ON_COMMAND(ID_REG_RIGHT_FLUSH, OnRegRightFlush)
	ON_COMMAND(ID_REG_RIGHT_MODIFY, OnRegRightModify)
	ON_UPDATE_COMMAND_UI(ID_REG_RIGHT_MODIFY, OnUpdateRegRightModify)
	ON_COMMAND(ID_REG_RIGHT_RENAME, OnRegRightRename)
	ON_UPDATE_COMMAND_UI(ID_REG_RIGHT_RENAME, OnUpdateRegRightRename)
	ON_COMMAND(ID_REG_RIGHT_CREATE_INT, OnRegRightCreateInt)
	ON_MESSAGE(WM_REGLEFTDBCLICK,OnRegLeftDbClick)
	ON_MESSAGE(WM_REGLEFTRCLICK,OnRegLeftRClick)
	ON_MESSAGE(WM_REGRIGHTRBCLICK,OnRegRightRClick)
	ON_MESSAGE(WM_SETMYCURSOR,OnSetMyCursor)
	ON_MESSAGE(WM_REGRIGHTRENAMEOK, OnRegRightRenameOk)
	ON_UPDATE_COMMAND_UI(IDS_MYDIRFILES, OnUpdateMyFiles)
	ON_WM_COPYDATA()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_CLOSE()
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
		!m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
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


void CMainFrame::ShowResponse(UINT m_Response)
{
	char m_Text[4096] = {0};
	switch(m_Response)
	{
		
		case INVALID_COMMAND			:	strcpy(m_Text,"无效命令");break;
		case REG_DELETE_KEY_ERR			:	strcpy(m_Text,"删除子键失败");break;
		case REG_RENAME_VALUE_ERR		:	strcpy(m_Text,"更名键值名失败");break;
		case REG_CREATE_VALUE_ERR		:	strcpy(m_Text,"创建新键值失败");break;
		case REG_EDIT_VALUE_ERR			:	strcpy(m_Text,"更改键值失败");break;
		case TRANS_DATA_ERR				:	strcpy(m_Text,"通信失败");break;
		default							:	return;
	}
	m_wndStatusBar.SetPaneText(0,m_Text);
}

LRESULT CMainFrame::OnRegLeftRClick(WPARAM wParam,LPARAM lParam)
{
	CTreeCtrl * pList = &pRegTreeView->GetTreeCtrl();
	HTREEITEM hItem = pList->GetSelectedItem();
	if(hItem == NULL || hItem == pList->GetRootItem())
	{
		return FALSE;
	}
	CPoint m_point;
	CMenu m_menu;
	m_menu.LoadMenu(IDR_MENU_REGEDIT_LEFT);
	GetCursorPos(&m_point);
	SetForegroundWindow();   
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
		TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
	m_menu.DestroyMenu();
	return TRUE;
}

void CMainFrame::DisplayButton(CTreeCtrl *pTree,HTREEITEM hti,int nChild)
{
	TVITEM tvi;
	tvi.mask = TVIF_CHILDREN;
	tvi.hItem = hti;
	tvi.cChildren = nChild;
	pTree->SetItem(&tvi);
}

LRESULT CMainFrame::OnRegLeftDbClick(WPARAM wParam,LPARAM lParam)
{
	HTREEITEM hItem = (HTREEITEM) wParam;
	if(hItem == NULL || 
		hItem == pRegTreeView->GetTreeCtrl().GetRootItem() ||
		m_MissionData.m_RecvSocket == 0)
		return FALSE;

	char m_KeyName[1024] = {0};
	if(!GetMyRegLeftPath(hItem,m_KeyName))
		return FALSE;
	
	m_MissionData.m_Command = CLIENT_REG_QUERY;
	strcpy(m_MissionData.m_TransData,m_KeyName);
	m_MissionData.m_TransLen = strlen(m_KeyName);
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		return FALSE;
	}
	if(m_MissionData.m_Command == NOT_FIND_ANY_FILE)
	{
		pRegListView->GetListCtrl().DeleteAllItems();
		pRegListView->GetListCtrl().InsertItem(0,"(默认)",1);
		pRegListView->GetListCtrl().SetItemText(0,1,"REG_SZ");
		pRegListView->GetListCtrl().SetItemText(0,2,"(数值未设置)");
		DisplayButton(&pRegTreeView->GetTreeCtrl(),hItem,0);
		return FALSE;
	}
	else if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		DisplayButton(&pRegTreeView->GetTreeCtrl(),hItem,0);
		return FALSE;
	}

	DWORD dwFileSize = m_MissionData.m_TransLen;
	BYTE * m_DesBuf = (LPBYTE) m_MissionData.m_TransData;
	if (pRegTreeView->GetTreeCtrl().ItemHasChildren(hItem))
	{
	   HTREEITEM hNextItem;
	   HTREEITEM hChildItem = pRegTreeView->GetTreeCtrl().GetChildItem(hItem);
	   while (hChildItem != NULL)
	   {
		  hNextItem = pRegTreeView->GetTreeCtrl().GetNextItem(hChildItem,TVGN_NEXT);
		  pRegTreeView->GetTreeCtrl().DeleteItem(hChildItem);
		  hChildItem = hNextItem;
	   }
	}

	pRegListView->GetListCtrl().DeleteAllItems();
	REGINFO m_RegInfo = {0};
	TV_INSERTSTRUCT tvstruct;
	int nItem = 0;
	BOOL IsHasChild = FALSE;
	for(ULONG i = 0; i < (dwFileSize/sizeof(REGINFO)); i++)
	{
		memset(&m_RegInfo,0,sizeof(REGINFO));
		memcpy(&m_RegInfo,m_DesBuf + i * sizeof(REGINFO),sizeof(REGINFO));
		m_RegInfo.m_Name[m_RegInfo.m_NameLen] = 0;
		if(!m_RegInfo.m_IsKey)
		{
			if(m_RegInfo.m_DataType == REG_SZ)
			{
				nItem = pRegListView->GetListCtrl().InsertItem
					(pRegListView->GetListCtrl().GetItemCount(),m_RegInfo.m_Name,1);
				pRegListView->GetListCtrl().SetItemText(nItem,1,"REG_SZ");
				m_RegInfo.m_Data[m_RegInfo.m_Datalen] = 0;
				pRegListView->GetListCtrl().SetItemText(nItem,2,m_RegInfo.m_Data);
			}
			else if(m_RegInfo.m_DataType == REG_BINARY)
			{
				nItem = pRegListView->GetListCtrl().InsertItem
					(pRegListView->GetListCtrl().GetItemCount(),m_RegInfo.m_Name,0);
				pRegListView->GetListCtrl().SetItemText(nItem,1,"REG_BINARY");
				char m_Tmpbuf[4096] = {0};
				BcdToAsc((BYTE*) m_RegInfo.m_Data,(BYTE*) m_Tmpbuf,m_RegInfo.m_Datalen);
				pRegListView->GetListCtrl().SetItemText(nItem,2,m_Tmpbuf);
			}
			else
			{
				nItem = pRegListView->GetListCtrl().InsertItem
					(pRegListView->GetListCtrl().GetItemCount(),m_RegInfo.m_Name,0);
				pRegListView->GetListCtrl().SetItemText(nItem,1,"REG_DWORD");
				char m_Tmpbuf[40] = {0};
				sprintf(m_Tmpbuf,"0x%08lx(%ld)",(UINT) *((DWORD*) m_RegInfo.m_Data),
					(UINT) *((DWORD*) m_RegInfo.m_Data));
				pRegListView->GetListCtrl().SetItemText(nItem,2,m_Tmpbuf);
			}
		}
		else
		{
			tvstruct.hParent = hItem;
			tvstruct.hInsertAfter = TVI_LAST;
			tvstruct.item.iImage = 0;
			tvstruct.item.iSelectedImage = 1;
			tvstruct.item.pszText = m_RegInfo.m_Name;
			tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
			HTREEITEM m_Parent = pRegTreeView->GetTreeCtrl().InsertItem(&tvstruct);
			DisplayButton(&pRegTreeView->GetTreeCtrl(),m_Parent,1);
			pRegTreeView->GetTreeCtrl().SetItemData(m_Parent,0);
			IsHasChild = TRUE;
		}
	}
	if(!IsHasChild)
	{
		DisplayButton(&pRegTreeView->GetTreeCtrl(),hItem,0);
	}
	pRegTreeView->GetTreeCtrl().Expand(hItem,TVE_EXPAND);
	return TRUE;
}

LRESULT CMainFrame::OnRegRightRClick(WPARAM wParam,LPARAM lParam)
{
	CPoint m_point;
	CMenu m_menu;

	if(pRegTreeView->GetTreeCtrl().GetSelectedItem()
		== pRegTreeView->GetTreeCtrl().GetRootItem() ||
		pRegTreeView->GetTreeCtrl().GetSelectedItem() == NULL)
		return FALSE;

	CListCtrl * pRightList = &pRegListView->GetListCtrl();
	if(pRightList->GetSelectedCount() > 0)
		m_menu.LoadMenu(IDR_MENU_REGEDIT_RIGHT);
	else
		m_menu.LoadMenu(IDR_MENU_REGEDIT_RIGHT_EMPTY);
	GetCursorPos(&m_point);
	SetForegroundWindow();   
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
		TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
	m_menu.DestroyMenu();	
	return TRUE;
}

LRESULT CMainFrame::OnRegRightRenameOk(WPARAM wParam,LPARAM lParam)
{
	char m_KeyName[2048] = {0};
	if(!GetMyRegLeftPath(pRegTreeView->GetTreeCtrl().GetSelectedItem()
		,m_KeyName)) return FALSE;

	char m_ItemName[2048] = {0};
	char m_NewKeyName[2048] = {0};
	char m_OldKeyName[2048] = {0};
	strcpy(m_NewKeyName,m_KeyName);
	strcpy(m_OldKeyName,m_KeyName);

	int nItem = (int) lParam;
	wsprintf(m_ItemName,"%s",pRegListView->GetListCtrl().GetItemText(nItem,0));
	strcat(m_NewKeyName,m_ItemName);
	strcat(m_OldKeyName,(char*) wParam);

	m_MissionData.m_Command = CLIENT_REG_RENAME_VALUE;
	memset(m_MissionData.m_TransData,0,2048);
	memcpy(m_MissionData.m_TransData,m_NewKeyName,strlen(m_NewKeyName));
	memcpy(&m_MissionData.m_TransData[1024],m_OldKeyName,strlen(m_OldKeyName));
	m_MissionData.m_TransLen = 2048;
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		pRegListView->GetListCtrl().SetItemText(nItem,0,(char*) wParam);
		return FALSE;
	}
	if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		pRegListView->GetListCtrl().SetItemText(nItem,0,(char*) wParam);
	}
	return TRUE;
}

BOOL CMainFrame::GetMyRegLeftPath(HTREEITEM hItem,char *Path)
{
	CTreeCtrl * pList = &pRegTreeView->GetTreeCtrl();
	if(hItem == NULL || hItem == pList->GetRootItem())
		return FALSE;
	
	char m_ItemName[512] = {0};
	char m_KeyName[2048] = {0};
	char m_TmpName[2048] = {0};
	HTREEITEM hCurItem = hItem;
	HTREEITEM hParent = NULL;

	while(1)
	{
		wsprintf(m_ItemName,"%s\\",pList->GetItemText(hCurItem));
		sprintf(m_TmpName,"%s%s",m_ItemName,m_KeyName);
		strcpy(m_KeyName,m_TmpName);
		hCurItem = pList->GetParentItem(hCurItem);
		if(hCurItem == pList->GetRootItem())
			break;
	}
	memcpy(Path,m_KeyName,strlen(m_KeyName));
	Path[strlen(m_KeyName)] = 0;
	return TRUE;
}

int CMainFrame::OnRegRightNewValue(int IsSz)
{
	CMyRenameDlg dlg;
	if(dlg.DoModal() != IDOK) return 0;

	int nItem = 0;
	if(IsSz == REG_VALUE_STR)
	{
		nItem = pRegListView->GetListCtrl().InsertItem
			(pRegListView->GetListCtrl().GetItemCount(),dlg.m_RegName,1);
		pRegListView->GetListCtrl().SetItemText(nItem,1,"REG_SZ");
		pRegListView->GetListCtrl().SetItemText(nItem,2,"");
	}
	else if(IsSz == REG_VALUE_INT)
	{
		nItem = pRegListView->GetListCtrl().InsertItem
			(pRegListView->GetListCtrl().GetItemCount(),dlg.m_RegName,0);
		pRegListView->GetListCtrl().SetItemText(nItem,1,"REG_DWORD");
		pRegListView->GetListCtrl().SetItemText(nItem,2,"0x00000000(0)");
	}
	else
	{
		nItem = pRegListView->GetListCtrl().InsertItem
			(pRegListView->GetListCtrl().GetItemCount(),dlg.m_RegName,0);
		pRegListView->GetListCtrl().SetItemText(nItem,1,"REG_BINARY");
		pRegListView->GetListCtrl().SetItemText(nItem,2,"00");
	}

	char m_KeyName[1024] = {0};
	if(!GetMyRegLeftPath(pRegTreeView->GetTreeCtrl().GetSelectedItem()
		,m_KeyName)) return -1;

	m_MissionData.m_Command = CLIENT_REG_CREATE_VALUE;
	memset(m_MissionData.m_TransData,0,2048);
	memcpy(m_MissionData.m_TransData,m_KeyName,strlen(m_KeyName));
	m_MissionData.m_TransData[1024] = IsSz;
	strcpy(&m_MissionData.m_TransData[1025], dlg.m_RegName);
	m_MissionData.m_TransLen = 1025 + strlen(dlg.m_RegName);
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		pRegListView->GetListCtrl().DeleteItem(nItem);
		return -1;
	}
	if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		pRegListView->GetListCtrl().DeleteItem(nItem);
		return -1;
	}
	return nItem;
}

void CMainFrame::OnRegrightRename() 
{
	CListCtrl * pList = &pRegListView->GetListCtrl();
	int nItem = pList->GetNextItem(-1,LVNI_SELECTED);
	pRegListView->PostMessage(WM_EDITLABLE,(WPARAM) nItem,NULL);		
}

void CMainFrame::OnUpdateRegRightRename(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	int nItem = -1;
	CTreeCtrl * pList = &pRegTreeView->GetTreeCtrl();
	CListCtrl * pRightList = &pRegListView->GetListCtrl();
	HTREEITEM hItem = pList->GetSelectedItem();
	nItem = pRightList->GetNextItem(nItem,LVNI_SELECTED);
	if(hItem != NULL && 
		hItem != pList->GetRootItem() &&
		pRightList->GetSelectedCount() == 1 &&
		pRightList->GetItemText(nItem,0) != "(默认)")
		IsEnable = TRUE;
	pCmdUI->Enable(IsEnable);	
}

void CMainFrame::OnRegRightDelete() 
{
	char m_KeyName[1024] = {0};
	if(!GetMyRegLeftPath(pRegTreeView->GetTreeCtrl().GetSelectedItem()
		,m_KeyName)) return;

	int nItem = pRegListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	m_MissionData.m_Command = CLIENT_REG_DELETE_VALUE;
	wsprintf(m_MissionData.m_TransData,"%s%s",
		m_KeyName,pRegListView->GetListCtrl().GetItemText(nItem,0));
	m_MissionData.m_TransLen = strlen(m_MissionData.m_TransData);
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
	pRegListView->GetListCtrl().DeleteItem(nItem);
}

void CMainFrame::OnUpdateRegRightDelete(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	int nItem = -1;
	CTreeCtrl * pList = &pRegTreeView->GetTreeCtrl();
	CListCtrl * pRightList = &pRegListView->GetListCtrl();
	HTREEITEM hItem = pList->GetSelectedItem();
	nItem = pRightList->GetNextItem(nItem,LVNI_SELECTED);
	if(hItem != NULL && hItem != pList->GetRootItem() &&
		pRightList->GetSelectedCount() == 1 &&
		pRightList->GetItemText(nItem,0) != "(默认)")
		IsEnable = TRUE;
	pCmdUI->Enable(IsEnable);	
}

void CMainFrame::OnRegLeftDelete() 
{
	HTREEITEM hItem = pRegTreeView->GetTreeCtrl().GetSelectedItem();
	char m_KeyName[1024] = {0};
	if(!GetMyRegLeftPath(hItem,m_KeyName))
		return;

	m_MissionData.m_Command = CLIENT_REG_DELETE_KEY;
	strcpy(m_MissionData.m_TransData,m_KeyName);
	m_MissionData.m_TransLen = strlen(m_MissionData.m_TransData);
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
	pRegTreeView->GetTreeCtrl().DeleteItem(hItem);
}

void CMainFrame::OnRegRightCreateBin() 
{
	int nItem = OnRegRightNewValue(REG_VALUE_BIN);
}

void CMainFrame::OnRegRightCreateStr() 
{
	int nItem = OnRegRightNewValue(REG_VALUE_STR);
}

void CMainFrame::OnRegRightCreateInt() 
{
	int nItem = OnRegRightNewValue(REG_VALUE_INT);
}

void CMainFrame::OnRegRightFlush() 
{
	CTreeCtrl * pList = &pRegTreeView->GetTreeCtrl();
	HTREEITEM hItem = pList->GetSelectedItem();
	if(hItem == NULL) return;
	PostMessage(WM_REGLEFTDBCLICK,(WPARAM) hItem,NULL);
}

void CMainFrame::OnRegRightModify() 
{
 	char m_KeyName[1024] = {0};
 	if(!GetMyRegLeftPath(pRegTreeView->GetTreeCtrl().
		GetSelectedItem(),m_KeyName))
  		return;
  
 	int nItem = -1;
 	nItem = pRegListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
 
 	char m_Name[1024] = {0};
 	char m_Value[1024] = {0};
 	char m_OldValue[1024] = {0};
 	BOOL m_IsDigital = FALSE;
 
 	strcpy(m_Name,(LPCTSTR) pRegListView->GetListCtrl().GetItemText(nItem,0));
 	strcpy(m_Value,(LPCTSTR) pRegListView->GetListCtrl().GetItemText(nItem,2));
 	strcpy(m_OldValue,m_Value);
 	if(pRegListView->GetListCtrl().GetItemText(nItem,1) == "REG_DWORD")
  		m_IsDigital = REG_VALUE_INT;
  	else if(pRegListView->GetListCtrl().GetItemText(nItem,1) == "REG_SZ")
  		m_IsDigital = REG_VALUE_STR;
  	else
  		m_IsDigital = REG_VALUE_BIN;
  
 	CMyRegEditValue dlg(m_Name,m_Value,m_IsDigital);
 	if(dlg.DoModal() != IDOK) return;
  	strcpy(m_Value,(LPCTSTR) dlg.m_Value);
 	m_MissionData.m_Command = CLIENT_REG_EDIT_VALUE;
 	memset(m_MissionData.m_TransData,0,2048);
 	strcat(m_KeyName,m_Name);
 	memcpy(m_MissionData.m_TransData,m_KeyName,1024);
 	if(m_IsDigital == REG_VALUE_BIN)
  		AscToBcd((BYTE*) m_Value,(BYTE*) 
		&m_MissionData.m_TransData[1024] , strlen(m_Value));
  	else
  		memcpy(&m_MissionData.m_TransData[1024],m_Value,1024);
  
 	m_MissionData.m_TransData[2048] = m_IsDigital;
 	m_MissionData.m_TransData[2049] = strlen(m_Value)/2;
 	m_MissionData.m_TransLen = 2050;
 	if(!ProcessOneTrans(&m_MissionData))
 	{
 		ShowResponse(m_MissionData.m_Command);
 		pRegListView->GetListCtrl().SetItemText(nItem,2,m_OldValue);
 		return ;
 	}
 	if(m_MissionData.m_Command != 0)
 	{
 		ShowResponse(m_MissionData.m_Command);
 		pRegListView->GetListCtrl().SetItemText(nItem,2,m_OldValue);
 		return ;
 	}
 	if(m_IsDigital == REG_VALUE_INT)
 	{
 		char m_Tmpbuf[40] = {0};
 		sprintf(m_Tmpbuf,"0x%08x(%d)",atol(m_Value),
 			atol(m_Value));
 		pRegListView->GetListCtrl().SetItemText(nItem,2,m_Tmpbuf);
 	}
 	else
 		pRegListView->GetListCtrl().SetItemText(nItem,2,m_Value);
}

void CMainFrame::OnUpdateRegRightModify(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pRegListView->GetListCtrl().GetSelectedCount() == 1);	
}

void CMainFrame::OnRegRightRename() 
{
	int nItem = pRegListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	pRegListView->PostMessage(WM_EDITLABLE,(WPARAM) nItem,NULL);	
}


BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//接收套接字信息
	LPWSAPROTOCOL_INFO pInfo = 
		(LPWSAPROTOCOL_INFO) pCopyDataStruct->lpData;

	if(pCopyDataStruct->dwData == CONN_FILE_REGD_RECV)
	{
		m_MissionData.m_SendSocket = 
			WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		return TRUE;
	}
	if(pCopyDataStruct->dwData == CONN_FILE_REGD_SEND)
	{
		m_MissionData.m_RecvSocket = 
			WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		m_CurSorStatus = FALSE;
		PostMessage(WM_SETCURSOR);
		return TRUE;
	}
	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (!m_WndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	CCreateContext m_CreateContext; 
	m_CreateContext.m_pCurrentFrame = this;
	m_CreateContext.m_pCurrentDoc = NULL;
	m_CreateContext.m_pNewDocTemplate = NULL;
	m_WndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyRegTreeCtrl),
		CSize(0, 0), &m_CreateContext);
	m_WndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMyRegListCtrl),
		CSize(0, 0), &m_CreateContext);

	pRegTreeView = (CMyRegTreeCtrl*) m_WndSplitter.GetPane(0,0);
	pRegListView = (CMyRegListCtrl*) m_WndSplitter.GetPane(0,1);
	return CFrameWnd::OnCreateClient(lpcs, pContext);
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

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	if(m_WndSplitter.GetSafeHwnd())
	{
		m_WndSplitter.SetColumnInfo(0,cx * 1/4, 0);
		m_WndSplitter.RecalcLayout();
	}

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

void CMainFrame::OnUpdateMyFiles(CCmdUI* pCmdUI) 
{
	char m_Text[256] = {0};
	sprintf(m_Text,"共有%d个对象",pRegListView->GetListCtrl().GetItemCount());
	pCmdUI->SetText(m_Text);
}
