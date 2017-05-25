// MyHtmlView.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "MyHtmlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlView

IMPLEMENT_DYNCREATE(CMyHtmlView, CHtmlView)

CMyHtmlView::CMyHtmlView()
{
	//{{AFX_DATA_INIT(CMyHtmlView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMyHtmlView::~CMyHtmlView()
{
}

void CMyHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyHtmlView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyHtmlView, CHtmlView)
	//{{AFX_MSG_MAP(CMyHtmlView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlView diagnostics

#ifdef _DEBUG
void CMyHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlView message handlers
