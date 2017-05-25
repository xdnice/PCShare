// MyEditView.cpp : implementation file
//

#include "stdafx.h"
#include "pckeymon.h"
#include "MyEditView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEditView

IMPLEMENT_DYNCREATE(CMyEditView, CEditView)

CMyEditView::CMyEditView()
{
	nTxtLen = 0;
}

CMyEditView::~CMyEditView()
{
	
}


BEGIN_MESSAGE_MAP(CMyEditView, CEditView)
	//{{AFX_MSG_MAP(CMyEditView)
	ON_WM_CHAR()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GETSTR, OnGetStr)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEditView drawing

void CMyEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyEditView diagnostics

#ifdef _DEBUG
void CMyEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyEditView message handlers

void CMyEditView::SaveChar(void)
{
	int len = GetWindowTextLength();
	if(len <= 0) return;

	//取目标文件名称
	CString szFilter = "文本文件(*.txt)|*.txt|";
	CFileDialog m_filedialog(FALSE,NULL,"PsKey.txt",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,this);
	if(m_filedialog.DoModal() != IDOK) return;
	
	FILE *fp = fopen(m_filedialog.GetPathName(), "wb");
	if(fp != NULL)
	{
		char* pBuf = new char[len + 1];
		len = GetWindowText(pBuf, len);
		fwrite(pBuf,len,1,fp);
		delete [] pBuf;
	}
	fclose(fp);
}

LRESULT CMyEditView::OnGetStr(WPARAM wParam, LPARAM lParam)
{
	GetEditCtrl().SetSel(nTxtLen, nTxtLen);
	GetEditCtrl().SendMessage(EM_REPLACESEL , wParam, lParam);
	nTxtLen += strlen((char*) lParam);
	return TRUE;
}

BOOL CMyEditView::PreCreateWindow(CREATESTRUCT& cs) 
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 启用换行
	return bPreCreated;
}

void CMyEditView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

}

void CMyEditView::OnChange() 
{

}

void CMyEditView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	
}

void CMyEditView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CMainFrame *pWnd = (CMainFrame*) AfxGetMainWnd();
	pWnd->OnCRclick();
}




