// MyRegEditValue.cpp : implementation file
//

#include "stdafx.h"
#include "MyRegEditValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyRegEditValue dialog


CMyRegEditValue::CMyRegEditValue(LPCTSTR Name,LPCTSTR Value,int IsDigital)
	: CDialog(CMyRegEditValue::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMyRegEditValue)
	
	//}}AFX_DATA_INIT
	m_Name = Name;
	m_Value = Value;
	m_IsDigital = IsDigital;
}


void CMyRegEditValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyRegEditValue)
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_Value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyRegEditValue, CDialog)
	//{{AFX_MSG_MAP(CMyRegEditValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRegEditValue message handlers

BOOL CMyRegEditValue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CEdit *pEdit = (CEdit*) GetDlgItem(IDC_EDIT_VALUE);	
	if(m_IsDigital == REG_VALUE_INT)
	{
		pEdit->ModifyStyle(0,ES_NUMBER);
		char m_Num[20] = {0};
		strcpy(m_Num,(LPCTSTR) m_Value);
		m_Num[m_Value.GetLength() - 1] = 0;
		m_Value = strchr(m_Num,'(') + 1;
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
