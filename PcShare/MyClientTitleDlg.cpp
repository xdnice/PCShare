// MyClientTitleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "MyClientTitleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyClientTitleDlg dialog


CMyClientTitleDlg::CMyClientTitleDlg(char *Title)
	: CDialog(CMyClientTitleDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMyClientTitleDlg)
	m_Title = Title;
	//}}AFX_DATA_INIT
}


void CMyClientTitleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyClientTitleDlg)
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Title);
	DDV_MaxChars(pDX, m_Title, 250);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyClientTitleDlg, CDialog)
	//{{AFX_MSG_MAP(CMyClientTitleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyClientTitleDlg message handlers
