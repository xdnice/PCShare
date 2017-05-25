// MyRegListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "PcRegedit.h"
#include "MyRegListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRegListCtrl

IMPLEMENT_DYNCREATE(CMyRegListCtrl, CListView)

CMyRegListCtrl::CMyRegListCtrl()
{
	
}

CMyRegListCtrl::~CMyRegListCtrl()
{
	
}


BEGIN_MESSAGE_MAP(CMyRegListCtrl, CListView)
	//{{AFX_MSG_MAP(CMyRegListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_EDITLABLE,OnEditLable)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRegListCtrl drawing

void CMyRegListCtrl::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyRegListCtrl diagnostics

#ifdef _DEBUG
void CMyRegListCtrl::AssertValid() const
{
	CListView::AssertValid();
}

void CMyRegListCtrl::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyRegListCtrl message handlers

int CMyRegListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_ListImageList.Create(16, 16,ILC_COLOR8|ILC_MASK,2,2);
	m_ListImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_REG_BIN));
	m_ListImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_REG_SZ));
	GetListCtrl().SetImageList(&m_ListImageList,LVSIL_SMALL);
	GetListCtrl().InsertColumn(0,"名称",LVCFMT_LEFT,280);
	GetListCtrl().InsertColumn(1,"类型",LVCFMT_LEFT,80);
	GetListCtrl().InsertColumn(2,"数值",LVCFMT_LEFT,350);
	GetListCtrl().GetHeaderCtrl()->ModifyStyle(HDS_BUTTONS ,HDS_HOTTRACK );
	return 0;
}

void CMyRegListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if(GetListCtrl().GetSelectedCount() > 0)
	{
		AfxGetMainWnd()->PostMessage(WM_COMMAND,
			(WPARAM) MAKEWPARAM(ID_REG_RIGHT_MODIFY,1),NULL);
	}
}

void CMyRegListCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	AfxGetMainWnd()->PostMessage(WM_REGRIGHTRBCLICK,NULL,NULL);
}

LRESULT CMyRegListCtrl::OnEditLable(WPARAM wParam,LPARAM lParam)
{
	int  nItem = (int) wParam;
	m_IsEdit = TRUE;
	SetFocus();
	CEdit *pEdit = GetListCtrl().EditLabel(nItem);
	ASSERT(pEdit);
	return TRUE;
}

void CMyRegListCtrl::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	if(m_IsEdit)
	{
		*pResult = 0;
	}
	else
	{
		*pResult = 1;
	}
}

void CMyRegListCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	if (pDispInfo->item.iItem == -1) 
	{
        return ; 
	}
	if(pDispInfo->item.pszText != NULL && strlen(pDispInfo->item.pszText) > 0)
	{
		CString m_EditEnd = pDispInfo->item.pszText;
		if(m_EditEnd.Find('\\') != -1) 
		{
			MessageBox("键名中不能包括以下字符:\\","重命名",MB_ICONERROR);
			PostMessage(WM_EDITLABLE,(WPARAM) pDispInfo->item.iItem,NULL);
			return;
		}
		wsprintf(m_OldName,"%s",GetListCtrl().GetItemText(pDispInfo->item.iItem,0));
		GetListCtrl().SetItemText(pDispInfo->item.iItem,0,m_EditEnd);
		AfxGetMainWnd()->PostMessage(WM_REGRIGHTRENAMEOK,
			(WPARAM) m_OldName,(LPARAM) pDispInfo->item.iItem);
	}
	m_IsEdit = FALSE;
}

BOOL CMyRegListCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style ^= LVS_REPORT|LVS_EDITLABELS|LVS_SINGLESEL;			
	return CListView::PreCreateWindow(cs);
}

