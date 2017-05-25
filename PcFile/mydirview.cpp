// MyDirView.cpp : implementation file
//

#include "stdafx.h"
#include "PcFile.h"
#include "MyDirView.h"
#include "MyDirTreeView.h"
#include "MyDirListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDirView

IMPLEMENT_DYNCREATE(CMyDirView, CView)

CMyDirView::CMyDirView()
{
}

CMyDirView::~CMyDirView()
{
}


BEGIN_MESSAGE_MAP(CMyDirView, CView)
	//{{AFX_MSG_MAP(CMyDirView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDirView drawing

void CMyDirView::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyDirView diagnostics

#ifdef _DEBUG
void CMyDirView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDirView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDirView message handlers

int CMyDirView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_WndSplitter.CreateStatic(this,1,2,WS_CHILD | WS_VISIBLE);
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;
	m_WndSplitter.CreateView(0,0,RUNTIME_CLASS(CMyDirTreeView),CSize(0,300),pContext);
	m_WndSplitter.CreateView(0,1,RUNTIME_CLASS(CMyDirListView),CSize(0,100),pContext);	

	return 0;
}

void CMyDirView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if(m_WndSplitter.GetSafeHwnd())
	{
		m_WndSplitter.MoveWindow(-2,-2,cx+2,cy+2);
		m_WndSplitter.SetColumnInfo(0,cx * 1/4, 0);
		m_WndSplitter.RecalcLayout();
	}	
}

CTreeView *CMyDirView::GetTreeView()
{
	return (CTreeView*) m_WndSplitter.GetPane(0,0);
}

CListView *CMyDirView::GetListView()
{
	return (CListView*) m_WndSplitter.GetPane(0,1);
}




