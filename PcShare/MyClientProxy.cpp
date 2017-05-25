// MyClientProxy.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "MyClientProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyClientProxy dialog


CMyClientProxy::CMyClientProxy(CWnd* pParent /*=NULL*/)
	: CDialog(CMyClientProxy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyClientProxy)
	m_Port = 80;
	//}}AFX_DATA_INIT
}

void CMyClientProxy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyClientProxy)
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Port);
	DDV_MinMaxUInt(pDX, m_Port, 80, 65000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyClientProxy, CDialog)
	//{{AFX_MSG_MAP(CMyClientProxy)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyClientProxy message handlers
