// MyServicesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyServicesDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyServicesDlg dialog


CMyServicesDlg::CMyServicesDlg(LPMYSERVICES Services)
	: CDialog(CMyServicesDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMyServicesDlg)
	
	//}}AFX_DATA_INIT

	pServices = Services;
	if(pServices->dwStartType == SERVICE_AUTO_START)
	{
		m_StartType = "自动";
	}
	else if(pServices->dwStartType == SERVICE_DEMAND_START)
	{
		m_StartType = "手动";
	}
	else
	{
		m_StartType = "已禁用";
	}
	m_DispName = pServices->m_Disp;
	m_Dist = pServices->lpDescribe;
	m_ExeName = pServices->lpBinaryPathName;
	m_Name = pServices->m_Name;
	m_IsModify = FALSE;
}

void CMyServicesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyServicesDlg)
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_StartType);
	DDX_Text(pDX, IDC_EDIT_DISP_NAME, m_DispName);
	DDV_MaxChars(pDX, m_DispName, 255);
	DDX_Text(pDX, IDC_EDIT_DIST, m_Dist);
	DDV_MaxChars(pDX, m_Dist, 255);
	DDX_Text(pDX, IDC_EDIT_EXE, m_ExeName);
	DDV_MaxChars(pDX, m_ExeName, 255);
	DDX_Text(pDX, IDC_STATIC_NAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 255);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyServicesDlg, CDialog)
	//{{AFX_MSG_MAP(CMyServicesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyServicesDlg message handlers

void CMyServicesDlg::OnOK() 
{
	UpdateData();
	if(m_StartType == "自动")
	{
		m_Type = SERVICE_AUTO_START;
	}
	else if(m_StartType == "手动")
	{
		m_Type = SERVICE_DEMAND_START;
	}
	else
	{
		m_Type = SERVICE_DISABLED;
	}
	if(m_Type != pServices->dwStartType)
	{
		m_IsModify = TRUE;
	}
	CDialog::OnOK();
}
