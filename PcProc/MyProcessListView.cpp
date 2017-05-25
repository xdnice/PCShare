// MyProcessListView.cpp : implementation file
//

#include "stdafx.h"
#include "MyProcessListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyProcessListView

IMPLEMENT_DYNCREATE(CMyProcessListView, CListView)

CMyProcessListView::CMyProcessListView()
{
}

CMyProcessListView::~CMyProcessListView()
{
	
}


BEGIN_MESSAGE_MAP(CMyProcessListView, CListView)
	//{{AFX_MSG_MAP(CMyProcessListView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyProcessListView drawing

void CMyProcessListView::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyProcessListView diagnostics

#ifdef _DEBUG
void CMyProcessListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyProcessListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyProcessListView message handlers

int CMyProcessListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);
	GetListCtrl().InsertColumn(0,"进程ID",LVCFMT_LEFT,80);
	GetListCtrl().InsertColumn(1,"线程数量",LVCFMT_LEFT,80);
	GetListCtrl().InsertColumn(2,"进程级别",LVCFMT_LEFT,80);
	GetListCtrl().InsertColumn(3,"执行文件",LVCFMT_LEFT,400);
	GetListCtrl().GetHeaderCtrl()->ModifyStyle(HDS_BUTTONS , HDS_HOTTRACK);
	return 0;
}

void CMyProcessListView::InsertMyItem(LPPROCESSLIST pItem)
{
	int i = GetListCtrl().GetItemCount();
	memset(m_TmpBuf,0,sizeof(m_TmpBuf));
	_ultoa(pItem->th32ProcessID,m_TmpBuf,10);
	GetListCtrl().InsertItem(i,m_TmpBuf);
	memset(m_TmpBuf,0,sizeof(m_TmpBuf));
	_ultoa(pItem->cntThreads,m_TmpBuf,10);
	GetListCtrl().SetItemText(i,1,m_TmpBuf);
	_ultoa(pItem->pcPriClassBase,m_TmpBuf,10);
	GetListCtrl().SetItemText(i,2,m_TmpBuf);
	GetListCtrl().SetItemText(i,3,pItem->szExeFile);
}

BOOL CMyProcessListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style ^= LVS_REPORT|LVS_SINGLESEL;		
	return CListView::PreCreateWindow(cs);
}

void CMyProcessListView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	AfxGetMainWnd()->PostMessage(WM_USERRCLICKPROCESS,NULL,NULL);
}



