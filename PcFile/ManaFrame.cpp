// MainFrame.cpp : implementation file
//

#include "stdafx.h"
#include "PcFile.h"
#include "ManaFrame.h"
#include "MyDirInfoDlg.h"
#include "MyFileInfo.h"
#include "MyDiskInfo.h"
#include "DirDialog.h"
#include "MyDirListView.h"
#include "MyFindFileDlg.h"
#include "MyFileTransDlg.h"
#include "MyRenameDlg.h"
#include "NewMenu.h" 
#include ".\manaframe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManaFrame

IMPLEMENT_DYNCREATE(CManaFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CManaFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CManaFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_COMMAND(ID_DIR_FLUSH, OnDirFlush)
	ON_COMMAND(ID_DIR_PREV, OnDirPrev)
	ON_UPDATE_COMMAND_UI(ID_DIR_PREV, OnUpdateDirPrev)
	ON_COMMAND(ID_DIR_ATTRIB, OnDirAttrib)
	ON_UPDATE_COMMAND_UI(ID_DIR_ATTRIB, OnUpdateDirAttrib)
	ON_COMMAND(ID_DIR_RIGHT_DELETE, OnDirRightDelete)
	ON_UPDATE_COMMAND_UI(ID_DIR_RIGHT_DELETE, OnUpdateDirRightDelete)
	ON_COMMAND(ID_DIR_RIGHT_EXEC_SHOW, OnDirRightExecShow)
	ON_COMMAND(ID_DIR_RIGHT_OPEN, OnDirRightOpen)
	ON_UPDATE_COMMAND_UI(ID_DIR_RIGHT_OPEN, OnUpdateDirRightOpen)
	ON_COMMAND(ID_DIR_RIGHT_RENAME, OnDirRightRename)
	ON_UPDATE_COMMAND_UI(ID_DIR_RIGHT_RENAME, OnUpdateDirRightRename)
	ON_COMMAND(ID_DIR_RIGHT_SELALL, OnDirRightSelall)
	ON_UPDATE_COMMAND_UI(ID_DIR_RIGHT_SELALL, OnUpdateDirRightSelall)
	ON_COMMAND(ID_DIR_CREATE, OnDirCreate)
	ON_UPDATE_COMMAND_UI(ID_DIR_CREATE, OnUpdateDirCreate)
	ON_COMMAND(ID_DIR_RIGHT_DOWNLOAD, OnDirRightDownload)
	ON_UPDATE_COMMAND_UI(ID_DIR_RIGHT_DOWNLOAD, OnUpdateDirRightDownload)
	ON_COMMAND(ID_DIR_RIGHT_UPLOAD, OnDirRightUpload)
	ON_COMMAND(ID_DIR_RIGHT_ATTRIB, OnDirRightAttrib)
	ON_UPDATE_COMMAND_UI(ID_DIR_RIGHT_ATTRIB, OnUpdateDirRightAttrib)
	ON_UPDATE_COMMAND_UI(IDS_MYDIRFILES, OnUpdateMyFiles)
	ON_COMMAND(ID_DIR_FIND_FILE, OnDirFindFile)
	ON_UPDATE_COMMAND_UI(ID_DIR_FIND_FILE, OnUpdateDirFindFile)
	ON_COMMAND(ID_EXIT,OnClose)
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DIRRIGHTRCLICK,OnDirRightRClick)
	ON_MESSAGE(WM_TREESELCHANGED,OnTreeSelChanged)
	ON_MESSAGE(WM_DIRRIGHTRENAMEOK,OnDirRightRenameOk)
	ON_MESSAGE(WM_SETMYCURSOR,OnSetMyCursor)
	ON_MESSAGE(WM_FILETRANSRCLICK,OnFileTransRClick)
	ON_COMMAND(ID_FILE_TRANS_DELETE_ALL, OnFileTransDeleteAll)
	ON_UPDATE_COMMAND_UI(ID_FILE_TRANS_DELETE_ALL, OnUpdateFileTransDeleteAll)
	ON_COMMAND(ID_FILE_TRANS_START, OnFileTransStart)
	ON_UPDATE_COMMAND_UI(ID_FILE_TRANS_START, OnUpdateFileTransStart)
	ON_COMMAND(ID_FILE_TRANS_STOP, OnFileTransStop)
	ON_UPDATE_COMMAND_UI(ID_FILE_TRANS_STOP, OnUpdateFileTransStop)
	ON_COMMAND(ID_FILE_TRANS_DELETE, OnFileTransDelete)
	ON_UPDATE_COMMAND_UI(ID_FILE_TRANS_DELETE, OnUpdateFileTransDelete)
	ON_MESSAGE(WM_TRANS_STATE, OnTransState)
	ON_UPDATE_COMMAND_UI(ID_DIR_FLUSH, OnUpdateDirFlush)
	ON_WM_TIMER()
	ON_COMMAND(ID_DIR_RIGHT_UPLOAD_EXEC, OnDirRightUploadExec)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManaFrame message handlers

static UINT indicatorsMana[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_MYDIRFILES,
};

CManaFrame::CManaFrame()
{
	m_WaitCur = AfxGetApp()->LoadCursor(IDC_CURSOR_WAIT);
	m_CurSorStatus = TRUE;
	memset(&m_MissionData,0,sizeof(CLIENTDATA));
	memset(m_IniFileName,0,sizeof(m_IniFileName));
	m_MissionData.m_WorkEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_MissionData.m_TransData = new char[TRAN_DATA_LEN + 100];
	m_EnalbeFileTrans = TRUE;
}

CManaFrame::~CManaFrame()
{
	if(m_MissionData.m_TransData != NULL)
	{
		CloseHandle(m_MissionData.m_WorkEvent);
		delete [] m_MissionData.m_TransData;
	}
}

int CManaFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT|TBSTYLE_LIST, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC|WS_EX_RTLREADING   ) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicatorsMana,
		  sizeof(indicatorsMana)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//设置ToolBar的图标列表
	m_ilTB.Create(16, 16, TRUE | ILC_COLOR8, 4, 0);
	HICON hIcon = NULL;

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_T_PREV), IMAGE_ICON, 16, 16, 0);
	m_ilTB.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_T_FLUSH), IMAGE_ICON, 16, 16, 0);
	m_ilTB.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_T_FIND), IMAGE_ICON, 16, 16, 0);
	m_ilTB.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_T_CREATE), IMAGE_ICON, 16, 16, 0);
	m_ilTB.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_T_DELETE), IMAGE_ICON, 16, 16, 0);
	m_ilTB.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_T_DL), IMAGE_ICON, 16, 16, 0);
	m_ilTB.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_T_RENAME), IMAGE_ICON, 16, 16, 0);
	m_ilTB.Add(hIcon);
	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ilTB);

	for(int i = 0 ; i < 7; i++)
		m_wndToolBar.SetButtonStyle(i,TBBS_AUTOSIZE);
	
	m_wndToolBar.SetButtonText(0,"后退");
	m_wndToolBar.SetButtonText(1,"刷新");
	m_wndToolBar.SetButtonText(2,"搜索");
	m_wndToolBar.SetButtonText(3,"新建");
	m_wndToolBar.SetButtonText(4,"删除");
	m_wndToolBar.SetButtonText(5,"下载");
	m_wndToolBar.SetButtonText(6,"重命名");
	return 0;
}

BOOL CManaFrame::PreCreateWindow(CREATESTRUCT& cs)
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

// CManaFrame 消息处理程序

void CManaFrame::ShowResponse(UINT m_Response)
{
	char m_Text[4096] = {0};
	switch(m_Response)
	{
		case NOT_FIND_ANY_FILE			:	strcpy(m_Text,"找不到任何文件");break;
		case CAN_NOT_OPEN_OBJECE		:	strcpy(m_Text,"");break;
		case INVALID_COMMAND			:	strcpy(m_Text,"无效命令");break;
		case CAN_NOT_OPEN_FILE			:	strcpy(m_Text,"无法打开文件");break;
		case GET_DISK_INFO_FAIL			:	strcpy(m_Text,"取磁盘信息失败");break;
		case EXEC_FILE_FAIL				:	strcpy(m_Text,"远程运行程序失败");break;
		case TRANS_DATA_ERR				:	strcpy(m_Text,"通信失败");break;
		case RENAME_FAILE				:	strcpy(m_Text,"更名失败");break;
		case CREATE_DIR_FAILE			:	strcpy(m_Text,"创建目录失败");break;
		case COMMAND_PARAM_ERR			:	strcpy(m_Text,"参数错误");break;
		case OPEB_REG_KEY_ERR			:	strcpy(m_Text,"无法打开指定键值");break;
		case CAN_NOT_CREATE_TMP_FILE	: 	strcpy(m_Text,"无法创建临时文件");break;
		default							:	return;
	}
	ShowMyText(m_Text);
}

LRESULT CManaFrame::OnTreeSelChanged(WPARAM wParam,LPARAM lParam)
{
	//检查数据正确性
	HTREEITEM hItem = (HTREEITEM) wParam;
	if(hItem == NULL || 
		m_MissionData.m_RecvSocket == 0 || 
		m_MissionData.m_SendSocket == 0)
		return FALSE;

	//磁盘列表
	if(hItem == pDirTreeView->GetTreeCtrl().GetRootItem())
	{
		GetDiskInfo(hItem);
		return TRUE;
	}

	//取当前所在目录
	if(!GetMyDirLeftPath(hItem,m_MissionData.m_TransData))
		return FALSE;

	//取通信数据
	m_MissionData.m_Command = CLIENT_DIR_LIST;
	m_MissionData.m_TransLen = strlen(m_MissionData.m_TransData);
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		pDirTreeView->GetTreeCtrl().SelectItem(
			pDirTreeView->GetTreeCtrl().GetParentItem(hItem));
		return FALSE;
	}

	//清空当前列表
	pDirListView->SetMyCoulmn(FALSE);
	DeleteTreeChild(hItem);
	if(m_MissionData.m_Command != 0)
	{
		DisplayButton(&pDirTreeView->GetTreeCtrl(),hItem,0);
		ShowResponse(m_MissionData.m_Command);
		return FALSE;
	}
	
	//显示列表
	DWORD dwFileSize = m_MissionData.m_TransLen;
	BYTE * p = (LPBYTE) m_MissionData.m_TransData;
	DIRFILELIST m_DirList = {0};
	TV_INSERTSTRUCT tvstruct;
	int  m_Image = 0;
	BOOL IsHasChild = FALSE;
	for(ULONG i = 0; i < (dwFileSize/sizeof(DIRFILELIST)); i++)
	{
		memcpy(&m_DirList,p,sizeof(DIRFILELIST));
		char* pItemName = strrchr(m_DirList.m_ItemPath,'\\');
		if(pItemName == NULL) continue;
		pItemName ++;

		if(m_DirList.m_ItemType == 7)
		{
			tvstruct.hParent = hItem;
			tvstruct.hInsertAfter = TVI_LAST;
			tvstruct.item.iImage = 2;
			tvstruct.item.iSelectedImage = 6;
			tvstruct.item.pszText = pItemName;
			tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
			HTREEITEM hItem = pDirTreeView->GetTreeCtrl().InsertItem(&tvstruct);
			DisplayButton(&pDirTreeView->GetTreeCtrl(),hItem,1);
			pDirTreeView->GetTreeCtrl().SetItemData(hItem,CLIENT_DIR);
			pDirListView->SendMessage(WM_INSERTMYITEM,(WPARAM) &m_DirList,NULL);
			IsHasChild = TRUE;
		}
		p += sizeof(DIRFILELIST);
	}
	pDirListView->GetListCtrl().SetItemCount(dwFileSize/sizeof(DIRFILELIST)); 
	p = (LPBYTE) m_MissionData.m_TransData;
	for(ULONG i = 0; i < (dwFileSize/sizeof(DIRFILELIST)); i++)
	{
		memcpy(&m_DirList,p,sizeof(DIRFILELIST));
		if(m_DirList.m_ItemType == 8)
		{
			pDirListView->SendMessage(WM_INSERTMYITEM,(WPARAM) &m_DirList,NULL);
		}
		p += sizeof(DIRFILELIST);
	}
	if(!IsHasChild)
		DisplayButton(&pDirTreeView->GetTreeCtrl(),hItem,0);
	pDirTreeView->GetTreeCtrl().Expand(hItem,TVE_EXPAND);
	return TRUE;
}

BOOL CManaFrame::GetClientDir(LPCTSTR RmotePath,LPCTSTR LocalPath)
{
	char m_RmotePath[2048] = {0};
	char m_LocalPath[2048] = {0};

	strcpy(m_RmotePath,RmotePath);
	strcpy(m_LocalPath,LocalPath);

	if(m_RmotePath[strlen(m_RmotePath) - 1] == '\\')
		m_RmotePath[strlen(m_RmotePath) - 1] = 0;
	if(m_LocalPath[strlen(m_LocalPath) - 1] == '\\')
		m_LocalPath[strlen(m_LocalPath) - 1] = 0;

	m_MissionData.m_Command = CLIENT_COPY_DIR_LIST;
	strcpy(m_MissionData.m_TransData,m_RmotePath);
	m_MissionData.m_TransLen = strlen(m_MissionData.m_TransData);

	//通信,生成临时文件
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		return FALSE;
	}
	if(m_MissionData.m_Command == NOT_FIND_ANY_FILE)
	{
		//目录下无文件
		return TRUE;
	}
	else if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return FALSE;
	}
	
	char m_ItemName[256] = {0};
	char *pName = strrchr(m_RmotePath,'\\');
	if(pName != NULL)
		strcpy(m_ItemName,pName + 1);
	else
		m_ItemName[0] = 0;

	UINT m_Count = m_MissionData.m_TransLen/sizeof(CPFILEINFO);
	LPCPFILEINFO pSrc = (LPCPFILEINFO) m_MissionData.m_TransData;
	for(UINT i = 0; i < m_Count; i++)
	{
		char * pDir = strstr(pSrc->name,m_ItemName);
		if(pDir == NULL) pDir = pSrc->name;
		pDir = strchr(pDir,'\\');
		if(pDir == NULL) continue;
		char m_Text[256] = {0};

       sprintf(m_Text,"%s%s",m_LocalPath,pDir);
		int nFileItem = pFileTransView->GetListCtrl().
			InsertItem(pFileTransView->GetListCtrl().GetItemCount(), m_Text);
		
		pFileTransView->GetListCtrl().SetItemText(nFileItem,1,"<=");
		pFileTransView->GetListCtrl().SetItemText(nFileItem,2, pSrc->name);
		if(pSrc->len > 1024)
			sprintf(m_Text,"%d KB",pSrc->len/1024);
		else
			sprintf(m_Text,"%d 字节",pSrc->len);
		pFileTransView->GetListCtrl().SetItemText(nFileItem,3,m_Text);
		pFileTransView->GetListCtrl().SetItemText(nFileItem,4,"0");
		pFileTransView->GetListCtrl().SetItemText(nFileItem,5," ");
		pSrc ++;
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char m_Title[256] = {0};
	::GetWindowText(hwnd,m_Title,250);
	if(!memcmp(m_Title,"PcShare文件传输",7))
	{
		::SendMessage(hwnd,WM_CLOSE,0,0);
	}
	return TRUE;
}

void CManaFrame::OnClose()
{
//	EnumWindows(EnumWindowsProc,NULL);

	m_EnalbeFileTrans = FALSE;
	KillTimer(TIMER_FILE_TRANS);
	KillTimer(TIMER_SAVE_TRANS);
	SetEvent(m_MissionData.m_WorkEvent);
	closesocket(m_MissionData.m_SendSocket);
	closesocket(m_MissionData.m_RecvSocket);
	CFrameWnd::OnClose();
	ExitProcess(0);
}

LRESULT CManaFrame::OnSetMyCursor(WPARAM wParam,LPARAM lParam)
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

void CManaFrame::ShowMyText(LPCTSTR Str)
{
	m_wndStatusBar.SetPaneText(0,Str);
}


BOOL CManaFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!m_WndSplitter.CreateStatic(this, 2, 1))
		return FALSE;

	CCreateContext m_CreateContext; 
	m_CreateContext.m_pCurrentFrame = this;
	m_CreateContext.m_pCurrentDoc = NULL;
	m_CreateContext.m_pNewDocTemplate = NULL;
	m_WndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyDirView),
		CSize(0, 0), &m_CreateContext);
	m_WndSplitter.CreateView(1, 0, RUNTIME_CLASS(CMyFileTransView),
		CSize(0, 0), &m_CreateContext);

	CMyDirView* pDirView = (CMyDirView*) m_WndSplitter.GetPane(0,0);
	pDirListView = (CMyDirListView*) pDirView->GetListView();
	pDirTreeView = (CMyDirTreeView*) pDirView->GetTreeView();
	pFileTransView = (CMyFileTransView*) m_WndSplitter.GetPane(1,0);
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

BOOL CManaFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_CurSorStatus)
	{
		SetCursor(m_WaitCur);
		return TRUE;
	}
	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CManaFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	if(m_WndSplitter.GetSafeHwnd())
	{
		m_WndSplitter.SetRowInfo(0,cy * 3/4,0);
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

BOOL CManaFrame::GetMyDirLeftPath(HTREEITEM hItem,char *Path)
{
	CTreeCtrl * pList = &pDirTreeView->GetTreeCtrl();
	if(hItem == NULL) return FALSE;
	if(hItem == pList->GetRootItem())
	{
		strcpy(Path,"");
		return TRUE;
	}

	char m_ItemName[512] = "";
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


void CManaFrame::OnDirFlush() 
{
	HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
	if(hItem == NULL) return;
	PostMessage(WM_TREESELCHANGED,(WPARAM) hItem,NULL);
}

void CManaFrame::OnUpdateDirFlush(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_MissionData.m_RecvSocket != 0);
}

void CManaFrame::OnDirPrev() 
{
	HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
	if(hItem == NULL) return;
	HTREEITEM hParent = pDirTreeView->GetTreeCtrl().GetParentItem(hItem);
	if(hParent == NULL) return;
	pDirTreeView->GetTreeCtrl().SelectItem(hParent);
}

void CManaFrame::OnUpdateDirPrev(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pDirTreeView->GetTreeCtrl().GetSelectedItem() != 
		pDirTreeView->GetTreeCtrl().GetRootItem());
}

void CManaFrame::OnDirAttrib() 
{
	CTreeCtrl * pList = &pDirTreeView->GetTreeCtrl();
	HTREEITEM hItem = pList->GetSelectedItem();
	if(!GetMyDirLeftPath(hItem,m_MissionData.m_TransData))
		return ;
	if(pList->GetItemData(hItem) == CLIENT_DIR)
		m_MissionData.m_Command = CLIENT_DIR_INFO;
	else
		m_MissionData.m_Command = CLIENT_DISK_INFO;

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
	if(pList->GetItemData(hItem) == CLIENT_DIR)
	{
		CMyDirInfoDlg dlg(*((LPDIRINFO) m_MissionData.m_TransData));
		dlg.DoModal();
	}
	else
	{
		CMyDiskInfo dlg(*((LPDISKINFO) m_MissionData.m_TransData));
		dlg.DoModal();
	}
}

void CManaFrame::OnUpdateDirAttrib(CCmdUI* pCmdUI) 
{
	CTreeCtrl * pList = &pDirTreeView->GetTreeCtrl();
	HTREEITEM hItem = pList->GetSelectedItem();
	BOOL IsEnable = FALSE;
	if(hItem != NULL || hItem != pList->GetRootItem())
		IsEnable = TRUE;
	pCmdUI->Enable(IsEnable);	
}


void CManaFrame::OnDirRightDelete() 
{
	char m_PathName[1024] = {0};
	if(!GetMyDirLeftPath(pDirTreeView->GetTreeCtrl().GetSelectedItem()
		,m_PathName))
	{
		return ;
	}

	int m_Count = pDirListView->GetListCtrl().GetSelectedCount();
	if(m_Count <= 0) return;
	
	if(m_Count * sizeof(DIRLIST) >= TRAN_DATA_LEN)
	{
		ShowMyText("选择项目太多,分次删除!");
		return;
	}

	if(MessageBox("真要删除?","删除",
		MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
		return;

	int  nItem = -1;
	DIRLIST m_DirList;
	char *p = m_MissionData.m_TransData;
	m_MissionData.m_TransLen = 0;
	for(int i = 0; i < m_Count; i++)
	{
		nItem = pDirListView->GetListCtrl().GetNextItem(nItem, LVNI_SELECTED);
		wsprintf(m_DirList.m_ItemName,"%s\\%s",m_PathName,
			pDirListView->GetListCtrl().GetItemText(nItem,0));
		memcpy(p,&m_DirList,sizeof(DIRLIST));
		m_MissionData.m_TransLen += sizeof(DIRLIST);
		p += sizeof(DIRLIST);
	}
	m_MissionData.m_Command = CLIENT_FILE_DELETE;
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		if(m_Count != 1)
		{
			OnDirFlush();
		}
		return;
	}
	nItem = -1;
	for(int i = 0; i < m_Count; i++)
	{
		//删除目录,删除树项目
		nItem = pDirListView->GetListCtrl().GetNextItem(nItem, LVNI_SELECTED);
		if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_DIR)
		{
			HTREEITEM hNextItem;
			HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
			HTREEITEM hChildItem = pDirTreeView->GetTreeCtrl().GetChildItem(hItem);
			while (hChildItem != NULL)
			{
				hNextItem = pDirTreeView->GetTreeCtrl().GetNextItem(hChildItem,TVGN_NEXT);
				if(pDirTreeView->GetTreeCtrl().GetItemText(hChildItem) ==
					pDirListView->GetListCtrl().GetItemText(nItem,0))
				{
					pDirTreeView->GetTreeCtrl().DeleteItem(hChildItem);
					break;
				}
				hChildItem = hNextItem;
			}
		}
	}
	for(int i = 0; i < m_Count; i++)
	{
		nItem = pDirListView->GetListCtrl().GetNextItem(-1, LVNI_SELECTED);
		pDirListView->GetListCtrl().DeleteItem(nItem);
	}
}

void CManaFrame::OnDirRightExecShow() 
{
	if(!GetMyDirLeftPath(pDirTreeView->GetTreeCtrl().
		GetSelectedItem(),m_MissionData.m_TransData))
		return ;

	int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	strcat(m_MissionData.m_TransData,(LPCTSTR) 
		pDirListView->GetListCtrl().GetItemText(nItem,0));
	m_MissionData.m_TransLen = strlen(m_MissionData.m_TransData);
	m_MissionData.m_Command = CLIENT_EXEC_FILE;
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		return;
	}
	if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return;
	}
	ShowMyText("远程运行程序成功!");
}

LRESULT CManaFrame::OnDirRightRClick(WPARAM wParam,LPARAM lParam)
{
	CNewMenu m_menu;
	if(pDirListView->GetListCtrl().GetSelectedCount() > 0)
	{
		if(pDirListView->GetListCtrl().GetSelectedCount() == 1)
		{
			int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
			if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_DISK)
			{
				//磁盘
				m_menu.CreatePopupMenu();
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_OPEN,"打开");
				m_menu.AppendMenu(MF_STRING,ID_DIR_FIND_FILE,"搜索文件");
				m_menu.AppendMenu(MF_SEPARATOR);
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_ATTRIB,"属性");
			}
			else if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_DIR)
			{
				//目录
				m_menu.CreatePopupMenu();
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_OPEN,"打开");
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_DELETE,"删除");
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_RENAME,"重命名");
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_DOWNLOAD,"下载");
				m_menu.AppendMenu(MF_STRING,ID_DIR_FIND_FILE,"搜索文件");
				m_menu.AppendMenu(MF_SEPARATOR);
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_ATTRIB,"属性");
			}
			else
			{
				//文件
				m_menu.LoadMenu(IDR_MENU_DIR_RIGHT);
				CPoint m_point;
				GetCursorPos(&m_point);
				SetForegroundWindow();   
				m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
					TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
				m_menu.DestroyMenu();
				return TRUE;
			}
		}
		else
		{
			//多选
			if(pDirTreeView->GetTreeCtrl().GetSelectedItem()
				!= pDirTreeView->GetTreeCtrl().GetRootItem())
			{
				//非磁盘
				m_menu.CreatePopupMenu();
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_DELETE,"删除");
				m_menu.AppendMenu(MF_STRING,ID_DIR_RIGHT_DOWNLOAD,"下载");
			}
			else return FALSE;
		}
	}
	else
	{
		HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
		if(hItem != pDirTreeView->GetTreeCtrl().GetRootItem())
		{
			m_menu.LoadMenu(IDR_MENU_DIR_RIGHT_EMPTY);
			CPoint m_point;
			GetCursorPos(&m_point);
			SetForegroundWindow();   
			m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
				TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
			m_menu.DestroyMenu();
			return TRUE;
		}
		else
		{
			m_menu.CreatePopupMenu();
			m_menu.AppendMenu(MF_STRING,ID_DIR_FLUSH,"刷新");
		}
	}
	CPoint m_point;
	GetCursorPos(&m_point);
	SetForegroundWindow();   
	m_menu.TrackPopupMenu(TPM_LEFTALIGN|
		TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
	m_menu.DestroyMenu();
	return TRUE;
}

void CManaFrame::OnDirRightOpen() 
{
	int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_FILE)	//文件
	{
		//初始化信息
		char m_TempPath[256] = {0};
		GetTempPath(200,m_TempPath);
		MYLISTFILEINFO m_Info = {0};
		wsprintf(m_Info.m_LocalFile,"%s%s",m_TempPath,
			pDirListView->GetListCtrl().GetItemText(nItem,0));
		wsprintf(m_Info.m_RemoteFile,"%s\\%s",
			pDirListView->GetListCtrl().GetItemText(nItem,4),
			pDirListView->GetListCtrl().GetItemText(nItem,0));
		m_Info.m_IsExec = TRUE;

		//创建下载窗口
		CMyFileTransDlg *pDlg = new CMyFileTransDlg(
			m_Info.m_RemoteFile, m_Info.m_LocalFile);
		pDlg->IsUpLoad = FALSE;
		pDlg->Create(this);

		//提交传输任务
		m_Info.hWnd = pDlg->GetSafeHwnd();
		memcpy(m_MissionData.m_TransData,&m_Info,sizeof(MYLISTFILEINFO));
		m_MissionData.m_TransLen = sizeof(MYLISTFILEINFO);
		m_MissionData.m_Command = CLIENT_DL_FILE;
		if(!ProcessOneTrans(&m_MissionData) || m_MissionData.m_Command != 0)
		{
			pDlg->DestroyWindow();
			ShowResponse(m_MissionData.m_Command);
			return;
		}
		else
			pDlg->ShowWindow(SW_SHOW);
	}
	else //目录或者磁盘
	{
		char m_TmpItemName[256] = {0};
		char m_ItemName[256] = {0};
		strcpy(m_ItemName,(LPCTSTR) 
			pDirListView->GetListCtrl().GetItemText(nItem,0));
		HTREEITEM hItem = 
			pDirTreeView->GetTreeCtrl().GetSelectedItem();
		if (pDirTreeView->GetTreeCtrl().ItemHasChildren(hItem))
		{
		   HTREEITEM hNextItem;
		   HTREEITEM hChildItem = pDirTreeView->
			   GetTreeCtrl().GetChildItem(hItem);
		   while (hChildItem != NULL)
		   {
			   hNextItem = pDirTreeView->GetTreeCtrl().
				   GetNextItem(hChildItem,TVGN_NEXT);
			   strcpy(m_TmpItemName,pDirTreeView->
				   GetTreeCtrl().GetItemText(hChildItem));
			   if(!strcmp(m_TmpItemName,m_ItemName))
			   {
				   pDirTreeView->GetTreeCtrl().SelectItem(hChildItem);
				   break;
			   }
			   hChildItem = hNextItem;
		   }
		}
	}
}

void CManaFrame::OnUpdateDirRightOpen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pDirListView->GetListCtrl().GetSelectedCount() == 1);
}

LRESULT CManaFrame::OnDirRightRenameOk(WPARAM wParam,LPARAM lParam)
{
	int nItem = (int) lParam;
	char m_NewName[2048] = {0};
	char m_OldName[2048] = {0};
	wsprintf(m_NewName,"%s\\%s",
		pDirListView->GetListCtrl().GetItemText(nItem,4),
		pDirListView->GetListCtrl().GetItemText(nItem,0));
	wsprintf(m_OldName,"%s\\%s",
		pDirListView->GetListCtrl().GetItemText(nItem,4),
		(char*) wParam);

	sprintf(m_MissionData.m_TransData,"%s*%s",m_NewName,m_OldName);
	m_MissionData.m_TransLen = strlen(m_MissionData.m_TransData);
	m_MissionData.m_Command = CLIENT_RENAME;
	if(!ProcessOneTrans(&m_MissionData))
	{
		ShowResponse(m_MissionData.m_Command);
		pDirListView->GetListCtrl().SetItemText(nItem,0,(char*) wParam);
		return FALSE;
	}
	if(m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		pDirListView->GetListCtrl().SetItemText(nItem,0,(char*) wParam);
		return FALSE;
	}
	if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_DIR)
	{
		//查看是否是目录
		HTREEITEM hItem = 
			pDirTreeView->GetTreeCtrl().GetSelectedItem();
		if (pDirTreeView->GetTreeCtrl().ItemHasChildren(hItem))
		{
		   HTREEITEM hNextItem;
		   HTREEITEM hChildItem = 
			   pDirTreeView->GetTreeCtrl().GetChildItem(hItem);
		   while (hChildItem != NULL)
		   {
			  hNextItem = pDirTreeView->GetTreeCtrl().
				  GetNextItem(hChildItem,TVGN_NEXT);
			  if(pDirTreeView->GetTreeCtrl().
				  GetItemText(hChildItem) == (char*) wParam)
			   {
				  pDirTreeView->GetTreeCtrl().SetItemText(hChildItem,
					  pDirListView->GetListCtrl().GetItemText(nItem,0));
				  break;
			   }
			  hChildItem = hNextItem;
		   }
		}
	}
	return TRUE;
}

void CManaFrame::OnDirRightRename() 
{
	int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	pDirListView->PostMessage(WM_EDITLABLE,(WPARAM) nItem,NULL);
}


void CManaFrame::OnUpdateDirRightDelete(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	if(pDirListView->GetListCtrl().GetSelectedCount() > 0)
	{
		int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		if(pDirListView->GetListCtrl().GetItemData(nItem) != CLIENT_DISK)
		{
			IsEnable = TRUE;
		}
	}
	pCmdUI->Enable(IsEnable);
}

void CManaFrame::OnUpdateDirRightRename(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	if(pDirListView->GetListCtrl().GetSelectedCount() == 1)
	{
		int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		if(pDirListView->GetListCtrl().GetItemData(nItem) != CLIENT_DISK)
		{
			IsEnable = TRUE;
		}
	}
	pCmdUI->Enable(IsEnable);
}

void CManaFrame::OnDirCreate() 
{
	char m_RomotePath[2048] = {0};
	HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
	if(!GetMyDirLeftPath(hItem,m_RomotePath)) return ;

	CMyRenameDlg dlg;
	if(dlg.DoModal() != IDOK) return;

	DIRFILELIST m_DirList = {0};
	m_DirList.m_ItemType = 7;
	wsprintf(m_DirList.m_ItemPath,"\\%s",dlg.m_FileName);
	int nItem = 0;
	pDirListView->SendMessage(WM_INSERTMYITEM,(WPARAM) &m_DirList,(LPARAM) &nItem);
	if(nItem == -1) return;

	m_MissionData.m_Command = CLIENT_CREATE_DIR;
	wsprintf(m_MissionData.m_TransData,"%s%s",m_RomotePath,dlg.m_FileName);
	m_MissionData.m_TransLen = strlen(m_MissionData.m_TransData);

	//通信
	if(!ProcessOneTrans(&m_MissionData) ||
		m_MissionData.m_Command != 0)
	{
		pDirListView->GetListCtrl().DeleteItem(nItem);
		ShowResponse(m_MissionData.m_Command);
		return ;
	}
	
	TV_INSERTSTRUCT tvstruct;
	tvstruct.hParent = hItem;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.iImage = 2;
	tvstruct.item.iSelectedImage = 7;
	tvstruct.item.pszText = dlg.m_FileName.LockBuffer();
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	hItem = pDirTreeView->GetTreeCtrl().InsertItem(&tvstruct);	
	pDirTreeView->GetTreeCtrl().SetItemData(hItem,CLIENT_DIR);
	pDirListView->GetListCtrl().SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);
}

void CManaFrame::OnDirRightAttrib() 
{
	int nItem = pDirListView->GetListCtrl().
		GetNextItem(-1,LVNI_SELECTED);
	wsprintf(m_MissionData.m_TransData,"%s\\%s",
		pDirListView->GetListCtrl().GetItemText(nItem,4),
		pDirListView->GetListCtrl().GetItemText(nItem,0));

	if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_DIR)
	{
		m_MissionData.m_Command = CLIENT_DIR_INFO;
	}
	else if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_DISK)
	{
		wsprintf(m_MissionData.m_TransData,"%s",
		pDirListView->GetListCtrl().GetItemText(nItem,0));
		m_MissionData.m_Command = CLIENT_DISK_INFO;
	}
	else
	{
		m_MissionData.m_Command = CLIENT_FILE_INFO;
	}
	m_MissionData.m_TransLen = 
		strlen(m_MissionData.m_TransData);
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

	if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_DIR)
	{
		CMyDirInfoDlg dlg(*((LPDIRINFO) m_MissionData.m_TransData));
		dlg.DoModal();
	}
	else if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_DISK)
	{
		CMyDiskInfo dlg(*((LPDISKINFO) 	m_MissionData.m_TransData));
		dlg.DoModal();
	}
	else
	{
		CMyFileInfo dlg(*((CFileStatus*) m_MissionData.m_TransData));
		dlg.DoModal();
	}
}

void CManaFrame::OnUpdateDirRightAttrib(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pDirListView->GetListCtrl().GetSelectedCount() == 1);
}

void CManaFrame::OnDirRightDownload() 
{
	//本地路径
	char m_LocalPath[2048] = {0};
	CDirDialog dlg;
	if(!dlg.DoBrowse(this)) return;
	wsprintf(m_LocalPath,"%s",dlg.m_strPath);
	if(m_LocalPath[strlen(m_LocalPath) - 1] == '\\')
		m_LocalPath[strlen(m_LocalPath) - 1] = 0;

	TRACE("%s\n",m_LocalPath);

	//远程路径
	char m_RmotePath[512] = {0};
	HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
	if(!GetMyDirLeftPath(hItem,m_RmotePath)) return ;

	//文件下载
	int m_Count = pDirListView->GetListCtrl().GetSelectedCount();
	int m_FileCount = 0;
	int nItem = -1;
	for(int i = 0; i < m_Count; i++)
	{
		nItem = pDirListView->GetListCtrl().GetNextItem(nItem, LVNI_SELECTED);
		if(pDirListView->GetListCtrl().GetItemData(nItem) == CLIENT_FILE)
		{
			char m_Text[256] = {0};
			wsprintf(m_Text,"%s\\%s",m_LocalPath,
			pDirListView->GetListCtrl().GetItemText(nItem,0));
			int nFileItem = pFileTransView->GetListCtrl().InsertItem
				(pFileTransView->GetListCtrl().GetItemCount(),m_Text);

			pFileTransView->GetListCtrl().SetItemText(nFileItem,1,"<=");

			wsprintf(m_Text,"%s\\%s",
			pDirListView->GetListCtrl().GetItemText(nItem,4),
			pDirListView->GetListCtrl().GetItemText(nItem,0));
			pFileTransView->GetListCtrl().SetItemText(nFileItem,2,m_Text);

			strcpy(m_Text,(LPCTSTR)	pDirListView->GetListCtrl().GetItemText(nItem,2));
			pFileTransView->GetListCtrl().SetItemText(nFileItem,3,m_Text);
			pFileTransView->GetListCtrl().SetItemText(nFileItem,4,"0");
			pFileTransView->GetListCtrl().SetItemText(nFileItem,5," ");
		}
		else
		{
			//目录下载
			char m_RmotePathName[512] = {0};
			char m_LocalPathName[512] = {0};
			wsprintf(m_LocalPathName,"%s\\%s",m_LocalPath,
				pDirListView->GetListCtrl().GetItemText(nItem,0));
			wsprintf(m_RmotePathName,"%s%s",m_RmotePath,
				pDirListView->GetListCtrl().GetItemText(nItem,0));
			GetClientDir(m_RmotePathName,m_LocalPathName);
		}
	}

	/*
	if(m_FileThreadInfo.soCmd == 0)
		OnFileTransStart();
	*/
}

void CManaFrame::OnUpdateDirRightDownload(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	if(pDirListView->GetListCtrl().GetSelectedCount() > 0)
	{
		int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		if(pDirListView->GetListCtrl().GetItemData(nItem) != CLIENT_DISK)
		{
			IsEnable = TRUE;
		}
	}
	pCmdUI->Enable(IsEnable);
}

void CManaFrame::OnDirFindFile() 
{
	char m_ItemName[256] = {0};
	int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
	HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
	if(hItem == pDirTreeView->GetTreeCtrl().GetRootItem())
	{
		wsprintf(m_ItemName,"%s\\",
			pDirListView->GetListCtrl().GetItemText(nItem,0));
	}
	else
	{
		wsprintf(m_ItemName,"%s\\%s\\",
			pDirListView->GetListCtrl().GetItemText(nItem,4),
			pDirListView->GetListCtrl().GetItemText(nItem,0));
	}
	CMyFindFileDlg dlg(this , m_ItemName,&m_MissionData, pFileTransView);
	dlg.DoModal();
}

void CManaFrame::OnDirRightUpload() 
{
	char OldDir[256] = "";
	char *m_FileBuf = new char[512 * 1024];
	memset(m_FileBuf,0,512 * 1024);
	GetCurrentDirectory(256,OldDir);
	CString szFilter = "(*.*)|*.*|";
	CFileDialog m_filedialog(TRUE,NULL,"*.*",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		|OFN_ALLOWMULTISELECT ,szFilter,this);

	m_filedialog.m_ofn.lpstrFile = m_FileBuf;
	m_filedialog.m_ofn.nMaxFile = 10000;
	char m_Title[4096] = {0};
	CString m_Str;
	GetWindowText(m_Str);

	char m_RomotePath[2048] = {0};
	HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
	if(!GetMyDirLeftPath(hItem,m_RomotePath))
	{
		delete [] m_FileBuf;
		return ;
	}
	
	wsprintf(m_Title,"上传文件到%s\\%s",m_Str,m_RomotePath);
	m_filedialog.m_ofn.lpstrTitle = (LPCTSTR) m_Title;
	if(m_filedialog.DoModal()!=IDOK)
	{
		delete [] m_FileBuf;
		return;
	}
	SetCurrentDirectory(OldDir);

	UINT nCurFileLen = 0;
	POSITION m_Pos = m_filedialog.GetStartPosition();
	while(m_Pos != NULL)
	{
		int nFileItem = pFileTransView->GetListCtrl().InsertItem
			(pFileTransView->GetListCtrl().GetItemCount(),
			m_filedialog.GetNextPathName(m_Pos));

		pFileTransView->GetListCtrl().SetItemText(nFileItem,1,"=>");
		
		CFileStatus m_FileStatus;
		if(!CFile::GetStatus(pFileTransView->GetListCtrl().
			GetItemText(nFileItem,0),m_FileStatus))
			continue;
		char m_Text[256] = {0};
		char *p = strrchr(m_FileStatus.m_szFullName,'\\');
		if(p == NULL) continue;
		wsprintf(m_Text,"%s%s",m_RomotePath,p + 1);
		pFileTransView->GetListCtrl().SetItemText(nFileItem,2,m_Text);

		if(m_FileStatus.m_size > 1024)
			sprintf(m_Text,"%ld KB",m_FileStatus.m_size/1024);
		else
			sprintf(m_Text,"%d 字节",m_FileStatus.m_size);
		pFileTransView->GetListCtrl().SetItemText(nFileItem,3,m_Text);
		pFileTransView->GetListCtrl().SetItemText(nFileItem,4,"0");
		pFileTransView->GetListCtrl().SetItemText(nFileItem,5," ");
	}
	delete [] m_FileBuf;
}

void CManaFrame::OnDirRightUploadExec()
{
	char OldDir[256] = {0};
	GetCurrentDirectory(256,OldDir);
	CString szFilter = "文件(*.*)|*.*|";
	CFileDialog m_filedialog(TRUE,NULL,"*.*",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter,this);
	if(m_filedialog.DoModal()!=IDOK) return;
	SetCurrentDirectory(OldDir);

	char m_RomotePath[2048] = {0};
	HTREEITEM hItem = pDirTreeView->GetTreeCtrl().GetSelectedItem();
	if(!GetMyDirLeftPath(hItem,m_RomotePath)) return ;

	char m_LocalName[512] = {0};
	char m_RemoteName[512] = {0};
	strcpy(m_LocalName,(LPCTSTR) m_filedialog.GetPathName());
	wsprintf(m_RemoteName,"%s%s",m_RomotePath,
		m_filedialog.GetFileName());

	MYLISTFILEINFO m_Info = {0};
	sprintf(m_Info.m_LocalFile,m_LocalName);
	strcpy(m_Info.m_RemoteFile,m_RemoteName);
	CFileStatus m_Status;
	if(!CFile::GetStatus(m_LocalName,m_Status))
		return;
	m_Info.m_FileLen = (DWORD) m_Status.m_size;
	m_Info.m_IsExec = TRUE;

	//创建上传窗口
	CMyFileTransDlg *pDlg = new CMyFileTransDlg(
		m_Info.m_RemoteFile,m_Info.m_LocalFile);
	pDlg->IsUpLoad = TRUE;
	pDlg->Create(this);

	//提交传输任务
	m_Info.hWnd = pDlg->GetSafeHwnd();
	memcpy(m_MissionData.m_TransData,&m_Info,sizeof(MYLISTFILEINFO));
	m_MissionData.m_TransLen = sizeof(MYLISTFILEINFO);
	m_MissionData.m_Command = CLIENT_UP_FILE;
	if(!ProcessOneTrans(&m_MissionData) || m_MissionData.m_Command != 0)
	{
		pDlg->DestroyWindow();
		ShowResponse(m_MissionData.m_Command);
	}
	else
		pDlg->ShowWindow(SW_SHOW);
}

void CManaFrame::OnDirRightSelall() 
{
	for(int i = 0; i < pDirListView->GetListCtrl().GetItemCount(); i++)
	{
		pDirListView->GetListCtrl().SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
	}
}

void CManaFrame::OnUpdateDirRightSelall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(pDirListView->GetListCtrl().GetItemCount() > 0);
}

void CManaFrame::OnUpdateDirFindFile(CCmdUI* pCmdUI) 
{
	BOOL bIsEnable = FALSE;
	if(pDirListView->GetListCtrl().GetSelectedCount() == 1)
	{
		int nItem = pDirListView->GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		if(pDirListView->GetListCtrl().GetItemData(nItem) != CLIENT_FILE)
		{
			bIsEnable = TRUE;
		}
	}
	pCmdUI->Enable(bIsEnable);
}

void CManaFrame::OnUpdateDirCreate(CCmdUI* pCmdUI) 
{
	BOOL IsEnable = FALSE;
	if(pDirListView->GetListCtrl().GetSelectedCount() == 0)
	{
		if(pDirTreeView->GetTreeCtrl().GetSelectedItem() 
			!= pDirTreeView->GetTreeCtrl().GetRootItem())
		{
			IsEnable = TRUE;
		}
	}
	pCmdUI->Enable(IsEnable);
}

void CManaFrame::OnUpdateMyFiles(CCmdUI* pCmdUI) 
{
	char m_Text[256] = {0};
	CWnd *pWnd = GetFocus();
	if(pWnd == pFileTransView)
		sprintf(m_Text,"共有%d个传输任务",pFileTransView->GetListCtrl().GetItemCount());
	else
		sprintf(m_Text,"共有%d个对象",pDirListView->GetListCtrl().GetItemCount());
	pCmdUI->SetText(m_Text);
}


void CManaFrame::DisplayButton(CTreeCtrl *pTree,HTREEITEM hti,int nChild)
{
	TVITEM tvi;
	tvi.mask = TVIF_CHILDREN;
	tvi.hItem = hti;
	tvi.cChildren = nChild;
	pTree->SetItem(&tvi);
}


void CManaFrame::GetDiskInfo(HTREEITEM hItem)
{
	//取客户磁盘信息列表
	m_MissionData.m_Command = CLIENT_DISK_LIST;
	m_MissionData.m_TransLen = 0;
	if(!ProcessOneTrans(&m_MissionData) 
		|| m_MissionData.m_Command != 0)
	{
		ShowResponse(m_MissionData.m_Command);
		return ;
	}

	//删除当前树子项
	DeleteTreeChild(hItem);
	
	//增加新项目
	pDirListView->SetMyCoulmn(TRUE);

	int m_Image = 0;
	LPDIRFILELIST pItem = (LPDIRFILELIST) m_MissionData.m_TransData;
	for(DWORD i = 0; i < m_MissionData.m_TransLen/sizeof(DIRFILELIST); i++)
	{
		char *pItemName = strrchr(pItem->m_ItemPath,'\\');
		if(pItemName == NULL) continue;
		pItemName ++;
		
		if(pItemName[0] == 'A' || pItemName[0] == 'B')
			m_Image = 0;
		else if(pItem->m_ItemType == DRIVE_CDROM)
			m_Image = 1;
		else if(pItem->m_ItemType == DRIVE_REMOVABLE)
			m_Image = 5;
		else if(pItem->m_ItemType == DRIVE_REMOTE)
			m_Image = 4;
		else 
			m_Image = 3;
	
		TV_INSERTSTRUCT tvstruct;
		tvstruct.hParent = hItem;
		tvstruct.hInsertAfter = TVI_LAST;
		tvstruct.item.iImage = m_Image;
		tvstruct.item.iSelectedImage = m_Image;
		tvstruct.item.pszText = pItemName;
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
		HTREEITEM hcItem = pDirTreeView->GetTreeCtrl().InsertItem(&tvstruct);	
		DisplayButton(&pDirTreeView->GetTreeCtrl(),hcItem,1);
		pDirTreeView->GetTreeCtrl().SetItemData(hItem,CLIENT_DISK);
		pDirListView->SendMessage(WM_INSERTMYITEM,(WPARAM) pItem,NULL);
		pItem++;
	}
	pDirTreeView->GetTreeCtrl().Expand(hItem,TVE_EXPAND);
}

void CManaFrame::DeleteTreeChild(HTREEITEM hItem)
{
	if(pDirTreeView->GetTreeCtrl().ItemHasChildren(hItem))
	{
	   HTREEITEM hNextItem;
	   HTREEITEM hChildItem = 
		   pDirTreeView->GetTreeCtrl().GetChildItem(hItem);
	   while (hChildItem != NULL)
	   {
		  hNextItem = pDirTreeView->GetTreeCtrl().
			  GetNextItem(hChildItem,TVGN_NEXT);
		  pDirTreeView->GetTreeCtrl().DeleteItem(hChildItem);
		  hChildItem = hNextItem;
	   }
	}
}

//启动函数
BOOL CManaFrame::StartWork()
{
	//拷贝数据
	
	return TRUE;
}

BOOL CManaFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	//接收套接字信息
	LPWSAPROTOCOL_INFO pInfo = 
		(LPWSAPROTOCOL_INFO) pCopyDataStruct->lpData;

	if(pCopyDataStruct->dwData == CONN_FILE_MANA_RECV)
	{
		//开始文件管理
		m_MissionData.m_SendSocket = 
			WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		return TRUE;
	}
	if(pCopyDataStruct->dwData == CONN_FILE_MANA_SEND)
	{
		//开始文件管理
		m_MissionData.m_RecvSocket = 
			WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		m_CurSorStatus = FALSE;
		PostMessage(WM_SETCURSOR);
		m_MissionData.hParent = GetSafeHwnd();
		SendMessage(WM_TREESELCHANGED,(WPARAM) 
			pDirTreeView->GetTreeCtrl().GetRootItem(),NULL);
		SetTimer(TIMER_FILE_TRANS,200,NULL);
		SetTimer(TIMER_SAVE_TRANS,200,NULL);
		return TRUE;
	}
	else if(pCopyDataStruct->dwData == CONN_FILE_DL)
	{
		//下载运行文件
		SOCKET s = 	WSASocket(AF_INET, SOCK_STREAM,0,
					pInfo,0,WSA_FLAG_OVERLAPPED);
		_beginthread(DlFileExecThread,0,(LPVOID) s);
		return TRUE;
	}
	else if(pCopyDataStruct->dwData == CONN_FILE_UP)
	{
		//上传运行文件
		SOCKET s = 	WSASocket(AF_INET, SOCK_STREAM,0,
					pInfo,0,WSA_FLAG_OVERLAPPED);
		_beginthread(UpFileExecThread,0, (LPVOID) s);
		return TRUE;
	}
	else
		return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
	return TRUE;
}

LRESULT CManaFrame::OnFileTransRClick(WPARAM wParam, LPARAM lParam)
{
	CPoint m_point;
	CNewMenu m_menu;
	m_menu.LoadMenu(IDR_MENU_FILE_TRANS);
	GetCursorPos(&m_point);
	SetForegroundWindow();   
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
		TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
	m_menu.DestroyMenu();
	return TRUE;
}

LRESULT CManaFrame::OnTransState(WPARAM wParam, LPARAM lParam)
{
	if(!m_EnalbeFileTrans) return FALSE;

	//查找指定项
	LPMYLISTFILEINFO pInfo = (LPMYLISTFILEINFO) lParam;
	int nItem = -1;
	int nCount = pFileTransView->GetListCtrl().GetItemCount();
	for(int i = 0; i < nCount; i++)
	{
		if(pFileTransView->GetListCtrl().GetItemText(i,0) == 
			pInfo->m_LocalFile &&
			pFileTransView->GetListCtrl().GetItemText(i,2) == 
			pInfo->m_RemoteFile)
		{
			nItem = i;
			break;
		}
	}
	if(nItem == -1) return FALSE;

	//初始化数据
	if(wParam == 0)
	{
		//一个文件传输完成
		pFileTransView->GetListCtrl().DeleteItem(nItem);
	}
	else if(wParam == 1)
	{
		//当前文件传输的状态
		char m_Text[256] = {0};
		sprintf(m_Text, "%d", pInfo->m_FilePoint);
		pFileTransView->GetListCtrl().SetItemText(nItem, 4, m_Text);
		return TRUE;
	}
	else if(wParam == 3)
	{
		pFileTransView->GetListCtrl().SetItemText(nItem, 5, "传输失败");
	}
	return TRUE;
}

void CManaFrame::OnFileTransDeleteAll()
{
	pFileTransView->GetListCtrl().DeleteAllItems();
}

void CManaFrame::OnUpdateFileTransDeleteAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(pFileTransView->GetListCtrl().GetItemCount() > 0);
}

void CManaFrame::OnFileTransStart()
{
	m_EnalbeFileTrans = TRUE;
	int nCount = pFileTransView->GetListCtrl().GetItemCount();
	for(int i = 0; i < nCount; i++)
	{
		pFileTransView->GetListCtrl().SetItemText(i,5," ");
	}
}

void CManaFrame::OnUpdateFileTransStart(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_EnalbeFileTrans);
}

void CManaFrame::OnFileTransStop()
{
	m_EnalbeFileTrans = FALSE;

	int nItem = -1;
	int nCount = pFileTransView->GetListCtrl().GetItemCount();
	for(int i = 0; i < nCount; i++)
	{
		if(pFileTransView->GetListCtrl().GetItemText(i,0) == 
			"正在传输")
		{
			nItem = i;
			break;
		}
	}
	if(nItem == -1) nItem = 0;
	pFileTransView->GetListCtrl().SetItemText(nItem,5,"用户终止");
}

void CManaFrame::OnUpdateFileTransStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_EnalbeFileTrans);
}

void CManaFrame::OnFileTransDelete()
{
	int m_Count = pFileTransView->GetListCtrl().GetSelectedCount();
	for(int i = 0; i < m_Count; i++)
	{
		int nItem = pFileTransView->GetListCtrl().GetNextItem(-1, LVNI_SELECTED);
		pFileTransView->GetListCtrl().DeleteItem(nItem);
	}
}

void CManaFrame::OnUpdateFileTransDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(	pFileTransView->GetListCtrl().GetItemCount() > 0);
}

void CManaFrame::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == TIMER_FILE_TRANS)
	{
		GetFileToTrans();
	}
	else if(nIDEvent == TIMER_SAVE_TRANS)
	{
		SaveTransInfo();
	}
	else
		CFrameWnd::OnTimer(nIDEvent);
}

void CManaFrame::LoadTransInfo()
{
	//打开文件
	CFile m_File;
	if(!m_File.Open(m_IniFileName, CFile::modeRead))
		return;

	//取文件长度
	DWORD nLen = (DWORD) m_File.GetLength();
	if(nLen == 0)
	{
		m_File.Close();
		DeleteFile(m_IniFileName);
		return;
	}

	//装载数据
	for(DWORD i = 0; i < nLen/sizeof(SAVEFILEINFO); i++)
	{
		SAVEFILEINFO m_SaveInfo = {0};
		m_File.Read(&m_SaveInfo,sizeof(SAVEFILEINFO));
		int nItem = pFileTransView->GetListCtrl().InsertItem(
			pFileTransView->GetListCtrl().GetItemCount(),m_SaveInfo.m_LocalFile);
		pFileTransView->GetListCtrl().SetItemText(nItem,1,m_SaveInfo.m_LoadWay);
		pFileTransView->GetListCtrl().SetItemText(nItem,2,m_SaveInfo.m_RemoteFile);
		pFileTransView->GetListCtrl().SetItemText(nItem,3,m_SaveInfo.m_FileLen);
		pFileTransView->GetListCtrl().SetItemText(nItem,4,m_SaveInfo.m_FilePoint);
		pFileTransView->GetListCtrl().SetItemText(nItem,5," ");
	}
	m_File.Close();
}

void CManaFrame::GetFileToTrans(void)
{
	//查看是否需要检查文件传输
	if(!m_EnalbeFileTrans || m_MissionData.m_IsWork) return;
	int nItem = pFileTransView->CheckValidFile();
	if(nItem == -1) return;

	MYLISTFILEINFO mInfo = {0};
	
	//服务器文件名称
	strcpy(mInfo.m_LocalFile, 
		pFileTransView->GetListCtrl().GetItemText(nItem, 0));

	//客户机文件名称
	strcpy(mInfo.m_RemoteFile, 
		pFileTransView->GetListCtrl().GetItemText(nItem, 2));

	//文件断点
	mInfo.m_FilePoint = 
		atoi(pFileTransView->GetListCtrl().GetItemText(nItem, 4));

	//窗口句柄和项目号
	mInfo.hWnd = GetSafeHwnd();

	//传输方向
	if(pFileTransView->GetListCtrl().GetItemText(nItem, 1) == "=>")
	{
		CFileStatus m_Status;
		if(!CFile::GetStatus(mInfo.m_LocalFile,m_Status)
			|| m_Status.m_size == 0)
		{
			//文件错误或者字节为0
			pFileTransView->GetListCtrl().DeleteItem(nItem);
			return;
		}
		mInfo.m_FileLen = (DWORD) m_Status.m_size;
		m_MissionData.m_Command = CLIENT_UP_FILE;
	}
	else
		m_MissionData.m_Command = CLIENT_DL_FILE;

	//发送数据
	memcpy(m_MissionData.m_TransData,&mInfo,sizeof(MYLISTFILEINFO));
	m_MissionData.m_TransLen = sizeof(MYLISTFILEINFO);
	pFileTransView->GetListCtrl().SetItemText(nItem, 5, "正在传输");
	if(!ProcessOneTrans(&m_MissionData) || m_MissionData.m_Command != 0)
		ShowResponse(m_MissionData.m_Command);
}

void CManaFrame::SaveTransInfo()
{
	int nCount = pFileTransView->GetListCtrl().GetItemCount();
	if(nCount <= 0)	
	{
		DeleteFile(m_IniFileName);
		return;
	}

	//创建目录
	CreateDirectory("data",NULL);

	//打开文件
	CFile m_File;
	if(!m_File.Open(m_IniFileName, CFile::modeCreate|CFile::modeWrite))
		return;

	for(int i = 0; i < nCount; i++)
	{
		SAVEFILEINFO m_SaveInfo = {0};
		strcpy(m_SaveInfo.m_LocalFile, pFileTransView->GetListCtrl().GetItemText(i,0));
		strcpy(m_SaveInfo.m_LoadWay, pFileTransView->GetListCtrl().GetItemText(i,1));
		strcpy(m_SaveInfo.m_RemoteFile, pFileTransView->GetListCtrl().GetItemText(i,2));
		strcpy(m_SaveInfo.m_FileLen, pFileTransView->GetListCtrl().GetItemText(i,3));
		strcpy(m_SaveInfo.m_FilePoint, pFileTransView->GetListCtrl().GetItemText(i,4));
		strcpy(m_SaveInfo.m_FileState, " ");
		m_File.Write(&m_SaveInfo,sizeof(SAVEFILEINFO));
	}
	m_File.Close();
}

void CManaFrame::SetIniFileName(char* pFileName)
{
	strcpy(m_IniFileName,pFileName);
}
