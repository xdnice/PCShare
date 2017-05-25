// MyRegTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "PcRegedit.h"
#include "MyRegTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRegTreeCtrl

IMPLEMENT_DYNCREATE(CMyRegTreeCtrl, CTreeView)

CMyRegTreeCtrl::CMyRegTreeCtrl()
{
	
}

CMyRegTreeCtrl::~CMyRegTreeCtrl()
{
	
}


BEGIN_MESSAGE_MAP(CMyRegTreeCtrl, CTreeView)
	//{{AFX_MSG_MAP(CMyRegTreeCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRegTreeCtrl drawing

void CMyRegTreeCtrl::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyRegTreeCtrl diagnostics

#ifdef _DEBUG
void CMyRegTreeCtrl::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMyRegTreeCtrl::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyRegTreeCtrl message handlers

int CMyRegTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_TreeImageList.Create(16, 16,ILC_COLOR8|ILC_MASK ,3,3);
	m_TreeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_T_NORMAL));
	m_TreeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_T_OPEN));
	m_TreeImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_T_ROOT));
	GetTreeCtrl().SetImageList(&m_TreeImageList,TVSIL_NORMAL);

	GetTreeCtrl().ModifyStyle(NULL,TVS_HASLINES|
		TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS);
	
	ReStart();

	return 0;
}

void CMyRegTreeCtrl::ReStart()
{
	GetTreeCtrl().DeleteAllItems();

	HTREEITEM m_Parent = NULL;

	TV_INSERTSTRUCT tvstruct;
	tvstruct.hParent = TVI_ROOT;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.iImage = 2;
	tvstruct.item.iSelectedImage = 2;
	tvstruct.item.pszText = "ÎÒµÄµçÄÔ";
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	HTREEITEM m_RootItem = GetTreeCtrl().InsertItem(&tvstruct);

	tvstruct.hParent = m_RootItem;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 1;
	tvstruct.item.pszText = "HKEY_CLASSES_ROOT";
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	m_Parent = GetTreeCtrl().InsertItem(&tvstruct);
	GetTreeCtrl().SetItemData(m_Parent,0);

	TVITEM tvi;
	tvi.mask = TVIF_CHILDREN;
	tvi.hItem = m_Parent;
	tvi.cChildren = 1;
	GetTreeCtrl().SetItem(&tvi);

	tvstruct.hParent = m_RootItem;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 1;
	tvstruct.item.pszText = "HKEY_CURRENT_USER";
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	m_Parent = GetTreeCtrl().InsertItem(&tvstruct);
	GetTreeCtrl().SetItemData(m_Parent,0);

	tvi.hItem = m_Parent;
	GetTreeCtrl().SetItem(&tvi);

	tvstruct.hParent = m_RootItem;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 1;
	tvstruct.item.pszText = "HKEY_LOCAL_MACHINE";
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	m_Parent = GetTreeCtrl().InsertItem(&tvstruct);
	GetTreeCtrl().SetItemData(m_Parent,0);

	tvi.hItem = m_Parent;
	GetTreeCtrl().SetItem(&tvi);

	tvstruct.hParent = m_RootItem;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 1;
	tvstruct.item.pszText = "HKEY_USERS";
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	m_Parent = GetTreeCtrl().InsertItem(&tvstruct);
	GetTreeCtrl().SetItemData(m_Parent,0);

	tvi.hItem = m_Parent;
	GetTreeCtrl().SetItem(&tvi);

	tvstruct.hParent = m_RootItem;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.iImage = 0;
	tvstruct.item.iSelectedImage = 1;
	tvstruct.item.pszText = "HKEY_CURRENT_CONFIG";
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	m_Parent = GetTreeCtrl().InsertItem(&tvstruct);
	GetTreeCtrl().SetItemData(m_Parent,0);

	tvi.hItem = m_Parent;
	GetTreeCtrl().SetItem(&tvi);
	GetTreeCtrl().Expand(m_RootItem,TVE_EXPAND);
}

void CMyRegTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	AfxGetMainWnd()->PostMessage(WM_REGLEFTDBCLICK,
		(WPARAM) pNMTreeView->itemNew.hItem,TRUE);	

	*pResult = 0;
}

void CMyRegTreeCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if(GetTreeCtrl().GetSelectedItem() != NULL)
	{
		AfxGetMainWnd()->PostMessage(WM_REGLEFTRCLICK,NULL,NULL);	
	}
}	








