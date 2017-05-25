// MyFindFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyFindFileDlg.h"
#include "MyFileInfo.h"
#include "MyFileTransDlg.h"
#include "DirDialog.h"
#include "ManaFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFindFileDlg dialog


CMyFindFileDlg::CMyFindFileDlg(CWnd* pParent , 
							   char* pDirName , 
							   LPCLIENTDATA pTransData,
							   CMyFileTransView* pWnd)
	: CDialog(CMyFindFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyFindFileDlg)
	m_Dir = pDirName;
	m_File = _T("");
	//}}AFX_DATA_INIT

	pData = pTransData;
	pFileTransView = pWnd;
}


void CMyFindFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyFindFileDlg)
	DDX_Control(pDX, IDC_LIST_FILE, m_FileList);
	DDX_Text(pDX, IDC_EDIT_DIR, m_Dir);
	DDV_MaxChars(pDX, m_Dir, 255);
	DDX_Text(pDX, IDC_EDIT_FILE, m_File);
	DDV_MaxChars(pDX, m_File, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyFindFileDlg, CDialog)
	//{{AFX_MSG_MAP(CMyFindFileDlg)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_FILE, OnRclickListFile)
	ON_COMMAND(ID_FIND_RIGHT_OPEN, OnFindRightOpen)
	ON_COMMAND(ID_FIND_EXEC_SHOW, OnFindExecShow)
	ON_COMMAND(ID_FIND_DOWNLOAD, OnFindDownload)
	ON_COMMAND(ID_FIND_DELETE, OnFindDelete)
	ON_COMMAND(ID_FIND_ATTRIB, OnFindAttrib)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILE, OnDblclkListFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFindFileDlg message handlers

void CMyFindFileDlg::OnOK() 
{
	UpdateData();
	if(m_File.IsEmpty() || m_Dir.IsEmpty())
		return;

	wsprintf(pData->m_TransData,"%s%s",m_Dir,m_File);
	pData->m_TransLen = strlen(pData->m_TransData);
	pData->m_Command = CLIENT_FIND_FILE;

	CWaitCursor m_Cur;
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	if(!ProcessOneTrans(pData))
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		m_Cur.Restore();
		MessageBox("通信故障","错误");
		return ;
	}
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	m_Cur.Restore();

	if(pData->m_Command == NOT_FIND_ANY_FILE)
		return ;

	if(pData->m_Command != 0)
	{
		MessageBox("客户机器故障","错误");
		return ;
	}

	m_FileList.DeleteAllItems();
	LPDIRLIST pItem = (LPDIRLIST) pData->m_TransData;
	for(UINT i = 0; i < pData->m_TransLen/sizeof(DIRLIST); i++)
	{
		DIRFILELIST pFileList = {0};
		strcpy(pFileList.m_ItemPath,pItem->m_ItemName);
		if(pItem->m_FileLen > 1024)
			sprintf(pFileList.m_ItemSize,
			"%ld KB",pItem->m_FileLen/1024);
		else
			sprintf(pFileList.m_ItemSize,
			"%ld 字节",pItem->m_FileLen);
		strcpy(pFileList.m_ModifyTime,pItem->m_ModifyTime);
		InsertMyItem(&pFileList);
		pItem++;
	}
}

void CMyFindFileDlg::OnCancel() 
{
	POSITION pos = m_List.GetHeadPosition();
	LPMYICONINFO pItem = NULL;
	for (int i = 0; i < m_List.GetCount(); i++)
	{
		delete (LPMYICONINFO) m_List.GetNext(pos);
	}
	m_List.RemoveAll();
	CDialog::OnCancel();
}

BOOL CMyFindFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int nImage = 0;
	m_imagelist.Create(16, 16,ILC_COLOR8|ILC_MASK,6,100);
	for (int nID = IDI_ICON1; nID <= IDI_ICON7; nID++)  
		nImage = m_imagelist.Add(AfxGetApp()->LoadIcon(nID));
	m_FileList.SetImageList(&m_imagelist , LVSIL_SMALL);

	m_FileList.InsertColumn(0,"名称",LVCFMT_LEFT,140);
	m_FileList.InsertColumn(1,"大小",LVCFMT_RIGHT,80);
	m_FileList.InsertColumn(2,"修改时间",LVCFMT_RIGHT,110);
	m_FileList.InsertColumn(3,"所在目录",LVCFMT_LEFT,205);

	m_FileList.GetHeaderCtrl()->ModifyStyle(HDS_BUTTONS ,
		HDS_HOTTRACK   );
	return TRUE;  
}

void CMyFindFileDlg::FindMyImage(LPCTSTR ItemName,int &nImage)
{
	char m_Ext[5] = {0};
	char m_ItemName[256] = {0};
	strcpy(m_ItemName,ItemName);
	memset(m_Ext,0,sizeof(m_Ext));
	memcpy(m_Ext,&m_ItemName[strlen(m_ItemName) - 4],4);
	_strupr(m_Ext);

	if(!strcmp(m_Ext,".EXE"))
	{
		nImage = 6;
		return;
	}

	POSITION pos = m_List.GetHeadPosition();
	LPMYICONINFO pItem = NULL;
	for (int i = 0; i < m_List.GetCount(); i++)
	{
		LPMYICONINFO pItem = (LPMYICONINFO) m_List.GetNext(pos);
		if(!strcmp(pItem->m_Ext,m_Ext))
		{
			nImage = pItem->m_Index;
			return;
		}
	}

	SHFILEINFO m_Info = {0};
	DWORD ret = SHGetFileInfo(m_ItemName,FILE_ATTRIBUTE_NORMAL,
		&m_Info,sizeof(SHFILEINFO),SHGFI_SMALLICON |
		SHGFI_ICON |SHGFI_USEFILEATTRIBUTES);
	ASSERT(ret);
	nImage = m_imagelist.Add(m_Info.hIcon);
	m_imagelist.SetOverlayImage(nImage, 1);
	pItem = new MYICONINFO;
	strcpy(pItem->m_Ext,m_Ext);
	pItem->m_Index = nImage;
	m_List.AddTail(pItem);
}

BOOL CMyFindFileDlg::InsertMyItem(LPDIRFILELIST pItem)
{
   	int m_Image = 0;
	char m_ItemType[20] = {0};
	char *pItemName = strrchr(pItem->m_ItemPath,'\\');
	if(pItemName == NULL) return FALSE;
	pItemName ++;

	FindMyImage(pItemName,m_Image);
	int nItem = m_FileList.InsertItem(
		m_FileList.GetItemCount(),pItemName,m_Image);
	if(nItem == -1)	return FALSE;

	*(pItemName - 1) = 0;
	m_FileList.SetItemText(nItem,1,pItem->m_ItemSize);
	m_FileList.SetItemText(nItem,2,pItem->m_ModifyTime);
	m_FileList.SetItemText(nItem,3,pItem->m_ItemPath);
	m_FileList.Update(nItem);
	return TRUE;
}

void CMyFindFileDlg::OnRclickListFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if(m_FileList.GetItemCount() <= 0)
		return;
	CPoint m_point;
	CMenu m_menu;
	m_menu.LoadMenu(IDR_MENU_FINDFILE);
	GetCursorPos(&m_point);
	SetForegroundWindow();   
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|
		TPM_RIGHTBUTTON,m_point.x,m_point.y,this);
	m_menu.DestroyMenu();
}

void CMyFindFileDlg::OnFindRightOpen() 
{
	int nItem =m_FileList.GetNextItem(-1,LVNI_SELECTED);
	if(nItem == -1) return;

	//初始化信息
	char m_TempPath[256] = {0};
	GetTempPath(200,m_TempPath);
	MYLISTFILEINFO m_Info = {0};
	wsprintf(m_Info.m_LocalFile,"%s%s",m_TempPath,
		m_FileList.GetItemText(nItem,0));
	wsprintf(m_Info.m_RemoteFile,"%s\\%s",
		m_FileList.GetItemText(nItem,3),
		m_FileList.GetItemText(nItem,0));

	//创建下载窗口
	CMyFileTransDlg *pDlg = new 
		CMyFileTransDlg(m_Info.m_RemoteFile,m_Info.m_LocalFile);
	pDlg->Create(this);

	//提交传输任务
	m_Info.hWnd = pDlg->GetSafeHwnd();
	m_Info.m_IsExec = TRUE;
	memcpy(pData->m_TransData,&m_Info,sizeof(MYLISTFILEINFO));
	pData->m_TransLen = sizeof(MYLISTFILEINFO);
	pData->m_Command = CLIENT_DL_FILE;
	if(!ProcessOneTrans(pData) || pData->m_Command != 0)
		pDlg->DestroyWindow();
	else
		pDlg->ShowWindow(SW_SHOW);	
}

void CMyFindFileDlg::OnFindExecShow() 
{
	int nItem = m_FileList.GetNextItem(-1,LVNI_SELECTED);
	if(nItem == -1) return;

	wsprintf(pData->m_TransData,"%s\\%s",
			m_FileList.GetItemText(nItem,3),
			m_FileList.GetItemText(nItem,0));
	pData->m_TransLen = strlen(pData->m_TransData);
	pData->m_Command = CLIENT_EXEC_FILE;

	CWaitCursor m_Cur;
	if(!ProcessOneTrans(pData))
	{
		m_Cur.Restore();
		MessageBox("通信故障","错误");
		return;
	}
	m_Cur.Restore();

	if(pData->m_Command != 0)
		MessageBox("远程运行文件失败","错误");
}

void CMyFindFileDlg::OnFindDownload() 
{
	char m_LocalPath[2048] = {0};
	CDirDialog dlg;
	if(!dlg.DoBrowse(this)) return;
	wsprintf(m_LocalPath,"%s",dlg.m_strPath);
	if(m_LocalPath[strlen(m_LocalPath) - 1] == '\\')
		m_LocalPath[strlen(m_LocalPath) - 1] = 0;

	int  nItem = m_FileList.GetNextItem(-1, LVNI_SELECTED);
	FILEINFO m_FileInfo = {0};
	wsprintf(m_FileInfo.remote,"%s\\%s",
		m_FileList.GetItemText(nItem,3),
		m_FileList.GetItemText(nItem,0));
	wsprintf(m_FileInfo.local,"%s\\%s",
		m_LocalPath , m_FileList.GetItemText(nItem,0));

	char m_Text[256] = {0};
	int nFileItem = pFileTransView->GetListCtrl().
		InsertItem(pFileTransView->GetListCtrl().GetItemCount(),m_FileInfo.local);
	pFileTransView->GetListCtrl().SetItemText(nFileItem,1,"<=");
	pFileTransView->GetListCtrl().SetItemText(nFileItem,2,m_FileInfo.remote);
	pFileTransView->GetListCtrl().SetItemText(nFileItem,
		3,m_FileList.GetItemText(nItem,1));
	pFileTransView->GetListCtrl().SetItemText(nFileItem,4,"0");
	pFileTransView->GetListCtrl().SetItemText(nFileItem,5," ");
}

void CMyFindFileDlg::OnFindDelete() 
{
	
	int nItem =m_FileList.GetNextItem(-1,LVNI_SELECTED);
	if(nItem == -1) return;

	if(MessageBox("真要删除?！","删除",
		MB_OKCANCEL|MB_ICONQUESTION) != IDOK)
		return;

	DIRLIST m_DirList = {0};
	wsprintf(m_DirList.m_ItemName,"%s\\%s",
			m_FileList.GetItemText(nItem,3),
			m_FileList.GetItemText(nItem,0));
	m_DirList.m_ItemType = CLIENT_FILE;
	pData->m_Command = CLIENT_FILE_DELETE;
	memcpy(pData->m_TransData,&m_DirList,sizeof(DIRLIST));
	pData->m_TransLen = sizeof(DIRLIST);

	CWaitCursor m_Cur;
	if(!ProcessOneTrans(pData))
	{
		m_Cur.Restore();
		MessageBox("通信故障","错误");
		return;
	}
	m_Cur.Restore();
	if(pData->m_Command != 0)
	{
		MessageBox("删除文件失败","错误");
		return;
	}
	m_FileList.DeleteItem(nItem);
}

void CMyFindFileDlg::OnFindAttrib() 
{
	int nItem =m_FileList.GetNextItem(-1,LVNI_SELECTED);
	if(nItem == -1) return;

	wsprintf(pData->m_TransData,"%s\\%s",
			m_FileList.GetItemText(nItem,3),
			m_FileList.GetItemText(nItem,0));
	pData->m_TransLen = strlen(pData->m_TransData);
	pData->m_Command = CLIENT_FILE_INFO;

	CWaitCursor m_Cur;
	if(!ProcessOneTrans(pData))
	{
		m_Cur.Restore();
		MessageBox("通信故障","错误");
		return;
	}
	m_Cur.Restore();

	if(pData->m_Command != 0)
	{
		MessageBox("取文件属性失败","错误");
		return;
	}

	CMyFileInfo dlg(*((CFileStatus*) pData->m_TransData));
	dlg.DoModal();
}

void CMyFindFileDlg::OnDblclkListFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	OnFindRightOpen();
}

