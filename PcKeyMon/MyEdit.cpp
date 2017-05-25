// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "pckeymon.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

BOOL CMyEdit::PreTranslateMessage(MSG* pMsg) 
{
		
	return CEdit::PreTranslateMessage(pMsg);
}

void CMyEdit::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CEdit::PreSubclassWindow();
}
