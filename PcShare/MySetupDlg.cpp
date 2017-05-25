// MySetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "MySetupDlg.h"
#include "DirDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySetupDlg dialog


CMySetupDlg::CMySetupDlg()
: CDialog(CMySetupDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMySetupDlg)
	m_MaxLinkMain = _T("");
	m_PortMain = _T("");
	//}}AFX_DATA_INIT
}

void CMySetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMySetupDlg)
	DDX_Control(pDX, IDC_SPIN_PORT_MAIN, m_SpinPortMain);
	DDX_Control(pDX, IDC_SPIN_MAX_LINK_MAIN, m_SpinMaxLinkMain);
	DDX_Text(pDX, IDC_EDIT_MAX_LINK_MAIN, m_MaxLinkMain);
	DDV_MaxChars(pDX, m_MaxLinkMain, 3);
	DDX_Text(pDX, IDC_EDIT_PORT_MAIN, m_PortMain);
	DDV_MaxChars(pDX, m_PortMain, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMySetupDlg, CDialog)
	//{{AFX_MSG_MAP(CMySetupDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySetupDlg message handlers

void CMySetupDlg::OnOK() 
{
	UpdateData();
	char m_IniFileName[256] = {0};
	GetIniFileName(m_IniFileName);
	WritePrivateProfileString("设置","自动上线连接端口",
		m_PortMain,m_IniFileName);
	WritePrivateProfileString("设置","最大客户连接数量",
		m_MaxLinkMain,m_IniFileName);
	CDialog::OnOK();
}


BOOL CMySetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char m_IniFileName[256] = {0};
	GetIniFileName(m_IniFileName);
	m_SpinPortMain.SetRange32(80,65534);
	m_SpinMaxLinkMain.SetRange(1,999);
	char m_sMaxLinkMain[100] = {0};
	char m_sPortMain[100] = {0};
	GetPrivateProfileString("设置","自动上线连接端口",
		"80",m_sPortMain,99,m_IniFileName);
	GetPrivateProfileString("设置","最大客户连接数量",
		"999",m_sMaxLinkMain,99,m_IniFileName);
	m_MaxLinkMain = m_sMaxLinkMain;
	m_PortMain = m_sPortMain;
	UpdateData(FALSE);
	return TRUE;  
}


