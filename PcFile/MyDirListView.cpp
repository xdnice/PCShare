// MyDirListView.cpp : implementation file
//

#include "stdafx.h"
#include "PcFile.h"
#include "MyDirListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDirListView

IMPLEMENT_DYNCREATE(CMyDirListView, CListView)

CMyDirListView::CMyDirListView()
{
	m_IsEdit = FALSE;
	memset(m_OldName,0,sizeof(m_OldName));
}

CMyDirListView::~CMyDirListView()
{
	POSITION pos = m_List.GetHeadPosition();
	LPMYICONINFO pItem = NULL;
	for (int i = 0; i < m_List.GetCount(); i++)
	{
		delete (LPMYICONINFO) m_List.GetNext(pos);
	}
	m_List.RemoveAll();
}


BEGIN_MESSAGE_MAP(CMyDirListView, CListView)
	//{{AFX_MSG_MAP(CMyDirListView)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_EDITLABLE,OnEditLable)
	ON_MESSAGE(WM_INSERTMYITEM,OnInsertMyItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDirListView drawing

void CMyDirListView::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();

}

/////////////////////////////////////////////////////////////////////////////
// CMyDirListView diagnostics

#ifdef _DEBUG
void CMyDirListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyDirListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDirListView message handlers

void CMyDirListView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	AfxGetMainWnd()->PostMessage(WM_DIRRIGHTRCLICK,
		(WPARAM) NULL,(LPARAM) NULL);
	*pResult = 0;
}

void CMyDirListView::FindMyImage(LPCTSTR ItemName,int &nImage)
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

LRESULT CMyDirListView::OnInsertMyItem(WPARAM wParam,LPARAM lParam)
{
	LPDIRFILELIST pItem = (LPDIRFILELIST) wParam;
	
	int m_Image = 0;
	char m_ItemType[20] = {0};
	char *pItemName = strrchr(pItem->m_ItemPath,'\\');
	if(pItemName == NULL) return FALSE;
	pItemName ++;

	if(pItem->m_ItemType == 8)
	{
		//文件
		FindMyImage(pItemName,m_Image);
		pItem->m_ItemType = CLIENT_FILE;
		strcpy(m_ItemType,"文件");
	}
	else if(pItem->m_ItemType == 7)
	{
		//目录
		m_Image = 2;
		pItem->m_ItemType = CLIENT_DIR;
		strcpy(m_ItemType,"文件夹");
	}
	//驱动器
	else
	{
		if(pItemName[0] == 'A' ||
			pItemName[0] == 'B')
		{
			//软驱
			m_Image = 0;
			strcpy(m_ItemType,"软驱");
		}
		else if(pItem->m_ItemType == DRIVE_CDROM)
		{
			//光驱
			m_Image = 1;
			strcpy(m_ItemType,"光驱");
		}
		else if(pItem->m_ItemType == DRIVE_REMOVABLE)
		{
			//可移动
			m_Image = 5;
			strcpy(m_ItemType,"可移动驱动器");
		}
		else if(pItem->m_ItemType == DRIVE_REMOTE)
		{
			//网络映射盘
			m_Image = 4;
			strcpy(m_ItemType,"远程磁盘");
		}
		else 
		{
			//硬盘
			m_Image = 3;
			strcpy(m_ItemType,"本地磁盘");
		}
		pItem->m_ItemType = CLIENT_DISK;
	}
	int nItem = GetListCtrl().InsertItem(
				GetListCtrl().GetItemCount(),
				pItemName,m_Image);
	if(nItem == -1)	return FALSE;

	if(pItem->m_ItemType == CLIENT_DISK)
	{
		GetListCtrl().SetItemText(nItem,1,m_ItemType);
		GetListCtrl().SetItemText(nItem,2,pItem->m_ItemSize);
		GetListCtrl().SetItemText(nItem,3,pItem->m_ModifyTime);
	}
	else
	{
		pItemName --;
		*pItemName = 0;
		GetListCtrl().SetItemText(nItem,1,m_ItemType);
		GetListCtrl().SetItemText(nItem,2,pItem->m_ItemSize);
		GetListCtrl().SetItemText(nItem,3,pItem->m_ModifyTime);
		GetListCtrl().SetItemText(nItem,4,pItem->m_ItemPath);
	}

	GetListCtrl().SetItemData(nItem,pItem->m_ItemType);
	if(lParam != NULL) *((int*)lParam) = nItem;
	GetListCtrl().Update(nItem);
	return TRUE;
}

void CMyDirListView::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	if(m_IsEdit) *pResult = 0;
	else *pResult = 1;
}

void CMyDirListView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;
	if (pDispInfo->item.iItem == -1) 
	{
        return ; 
	}
	if(pDispInfo->item.pszText != NULL && 
		strlen(pDispInfo->item.pszText) > 0)
	{
		CString m_EditEnd = pDispInfo->item.pszText;
		if((m_EditEnd.Find('\'') != -1) ||
			(m_EditEnd.Find('\\') != -1) ||
			(m_EditEnd.Find('/') != -1) ||
			(m_EditEnd.Find(':') != -1) ||
			(m_EditEnd.Find('?') != -1) ||
			(m_EditEnd.Find('\"') != -1) ||
			(m_EditEnd.Find('<') != -1) ||
			(m_EditEnd.Find('>') != -1) ||
			(m_EditEnd.Find('|') != -1)
			)
		{
			MessageBox("文件名中不能包括以下字符:\r\n\'\\/:*?\"<>|",
				"重命名",MB_ICONERROR);
			PostMessage(WM_EDITLABLE,(WPARAM) 
				pDispInfo->item.iItem,NULL);
			return;
		}
		wsprintf(m_OldName,"%s",GetListCtrl().
			GetItemText(pDispInfo->item.iItem,0));
		GetListCtrl().SetItemText(pDispInfo->item.iItem,0,m_EditEnd);
		AfxGetMainWnd()->PostMessage(WM_DIRRIGHTRENAMEOK,
			(WPARAM) m_OldName,(LPARAM) pDispInfo->item.iItem);
	}
	m_IsEdit = FALSE;
}

int CMyDirListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	int nImage = 0;
	m_imagelist.Create(16, 16,ILC_COLOR8|ILC_MASK,6,100);
	for (int nID = IDI_ICON1; nID <= IDI_ICON7; nID++)  
		nImage = m_imagelist.Add(AfxGetApp()->LoadIcon(nID));
	GetListCtrl().SetImageList(&m_imagelist,LVSIL_SMALL);
	GetListCtrl().InsertColumn(0,"名称",LVCFMT_LEFT,140);
	GetListCtrl().InsertColumn(1,"类型",LVCFMT_LEFT,170);
	GetListCtrl().InsertColumn(2,"大小",LVCFMT_RIGHT,100);
	GetListCtrl().InsertColumn(3,"可用空间",LVCFMT_RIGHT,100);
	return 0;
}

LRESULT CMyDirListView::OnEditLable(WPARAM wParam,LPARAM lParam)
{
	int  nItem = (int) wParam;
	m_IsEdit = TRUE;
	SetFocus();
	CEdit *pEdit = GetListCtrl().EditLabel(nItem);
	ASSERT(pEdit);
	return TRUE;
}

void CMyDirListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if(GetListCtrl().GetSelectedCount() == 1)
	{
		AfxGetMainWnd()->PostMessage(WM_COMMAND,(WPARAM) 
			MAKEWPARAM(ID_DIR_RIGHT_OPEN,1),NULL);
	}
}

BOOL CMyDirListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style ^= LVS_REPORT|LVS_EDITLABELS;		
	return CListView::PreCreateWindow(cs);
}

void CMyDirListView::SetMyCoulmn(BOOL IsDisk)
{
	GetListCtrl().DeleteAllItems();
	while(GetListCtrl().
		GetHeaderCtrl()->GetItemCount() > 0)
		GetListCtrl().DeleteColumn(0);
	if(IsDisk)
	{
		GetListCtrl().InsertColumn(0,"名称",LVCFMT_LEFT,140);
		GetListCtrl().InsertColumn(1,"类型",LVCFMT_LEFT,100);
		GetListCtrl().InsertColumn(2,"大小",LVCFMT_RIGHT,100);
		GetListCtrl().InsertColumn(3,"可用空间",LVCFMT_RIGHT,100);
	}
	else
	{
		GetListCtrl().InsertColumn(0,"名称",LVCFMT_LEFT,150);
		GetListCtrl().InsertColumn(1,"类型",LVCFMT_LEFT,100);
		GetListCtrl().InsertColumn(2,"大小",LVCFMT_RIGHT,100);
		GetListCtrl().InsertColumn(3,"修改时间",LVCFMT_RIGHT,100);
		GetListCtrl().InsertColumn(4,"所在目录",LVCFMT_LEFT,250);
	}
}
