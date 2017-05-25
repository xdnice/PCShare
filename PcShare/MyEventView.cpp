// MyEventView.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "MyEventView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEventView

IMPLEMENT_DYNCREATE(CMyEventView, CListView)

CMyEventView::CMyEventView()
{
}

CMyEventView::~CMyEventView()
{
}


BEGIN_MESSAGE_MAP(CMyEventView, CListView)
	//{{AFX_MSG_MAP(CMyEventView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RESIZE_WND,OnResizeWnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEventView drawing

void CMyEventView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyEventView diagnostics

#ifdef _DEBUG
void CMyEventView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyEventView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyEventView message handlers

int CMyEventView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_imagelist.Create(16, 16,ILC_COLOR8|ILC_MASK,6,100);
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_EVENT_NORMAL));
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_EVENT_ERROR));
	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);
	GetListCtrl().SetImageList(&m_imagelist,LVSIL_SMALL);
	GetListCtrl().InsertColumn(0,"发生时间",LVCFMT_LEFT,160);
	GetListCtrl().InsertColumn(1,"事件内容",LVCFMT_LEFT,360);
	GetListCtrl().GetHeaderCtrl()->ModifyStyle(HDS_BUTTONS ,HDS_HOTTRACK);
	return 0;
}

void CMyEventView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	AfxGetThread()->m_pMainWnd->PostMessage(
		WM_CLIENTMAINRCLICK,(WPARAM) IDR_MENU_LIST,(LPARAM) NULL);
}

BOOL CMyEventView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style ^= LVS_REPORT;	
	return CListView::PreCreateWindow(cs);
}

void CMyEventView::InsertItem(LPCTSTR Text, BOOL Flag)
{
	CTime t = CTime::GetCurrentTime();
	int nCount = GetListCtrl().GetItemCount();
	GetListCtrl().InsertItem(nCount,
		t.Format("%Y年%m月%d日 - %H时%M分%S秒"),Flag);
	GetListCtrl().SetItemText(nCount,1,Text);
	GetListCtrl().EnsureVisible(nCount, FALSE);
	OnResizeWnd(0,0);
}

LRESULT CMyEventView::OnResizeWnd(WPARAM wParam,LPARAM lParam)
{
	CRect rect;
	GetClientRect(&rect);
	if(rect.Width() > 0)
	{
		GetListCtrl().SetColumnWidth(0,186);
		GetListCtrl().SetColumnWidth(1,rect.Width() - 186);
	}
	return TRUE;
}
