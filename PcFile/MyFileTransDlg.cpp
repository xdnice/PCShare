// MyFileTransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PcFile.h"
#include "MyFileTransDlg.h"
#include ".\myfiletransdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileTransDlg dialog


CMyFileTransDlg::CMyFileTransDlg(char* pSrcFile , char* pDesSrc)
{
	//{{AFX_DATA_INIT(CMyFileTransDlg)
	m_SrcFile = pSrcFile;
	m_DesFile = pDesSrc;
	//}}AFX_DATA_INIT
	IsUpLoad = FALSE;
}

void CMyFileTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyFileTransDlg)
	DDX_Control(pDX, IDC_ANIMATE_FILE, m_Animal);
	DDX_Control(pDX, IDC_PROGRESS_FILE, m_FileStep);
	DDX_Text(pDX, ID_FILE_SRC, m_SrcFile);
	DDX_Text(pDX, ID_FILE_DES, m_DesFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyFileTransDlg, CDialog)
	//{{AFX_MSG_MAP(CMyFileTransDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRANS_STATE, OnTransState)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFileTransDlg message handlers

void CMyFileTransDlg::OnOK() 
{
	
}

void CMyFileTransDlg::OnCancel() 
{
	DestroyWindow();
}

BOOL CMyFileTransDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	m_Animal.Open(IDR_AVI_FILE);
	ShowWindow(SW_HIDE);
	hWnd = AfxGetMainWnd()->GetSafeHwnd();
	return TRUE;  
}

BOOL CMyFileTransDlg::Create(CWnd* pWnd) 
{
	return CDialog::Create(IDD, pWnd);
}

void CMyFileTransDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	delete this;
}

LRESULT CMyFileTransDlg::OnTransState(WPARAM wParam, LPARAM lParam)
{
	//初始化数据
	LPMYLISTFILEINFO pInfo = (LPMYLISTFILEINFO) lParam;
	int nMin = 0, nMax = 0;
	m_FileStep.GetRange(nMin, nMax);

	if(wParam == 0)
	{
		if(IsUpLoad)
			::PostMessage(hWnd, WM_COMMAND,(WPARAM) 
				MAKEWPARAM(ID_DIR_FLUSH,1),NULL);
		DestroyWindow();
	}
	else if(wParam == 1)
	{
		m_FileStep.SetPos(pInfo->m_FilePoint);
	}
	else if(wParam == 2)
	{
		m_FileStep.SetRange32(0,pInfo->m_FileLen);
	}
	else if(wParam == 3)
	{
		MessageBox("文件传输失败!","错误");
		DestroyWindow();
	}
	return TRUE;
}

