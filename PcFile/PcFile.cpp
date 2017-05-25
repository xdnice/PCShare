// PcFile.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PcFile.h"
#include "ManaFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPcFileApp

BEGIN_MESSAGE_MAP(CPcFileApp, CWinApp)
	//{{AFX_MSG_MAP(CPcFileApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcFileApp construction

CPcFileApp::CPcFileApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPcFileApp object

CPcFileApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPcFileApp initialization

BOOL CPcFileApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	//初始化SOCKET环境
	WSADATA		data;
	if(WSAStartup(MAKEWORD(2, 2), &data))
	{
		return FALSE;
	}
	if (LOBYTE(data.wVersion) !=2 || 
		HIBYTE(data.wVersion) != 2)
	{
		WSACleanup();
		return FALSE;
	}

	if(strlen(m_lpCmdLine) == 0) return FALSE;

	//取初始化参数
	CManaFrame* pFrame = new CManaFrame;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MENU_MANA);
	
	//标题
	char m_Title[256] = {0};
	strcpy(m_Title, m_lpCmdLine);
	char m_Id[256] = {0};
	char* pFind = strrchr(m_Title,':');
	if(pFind != NULL)
	{
		//取ID
		memcpy(m_Id, pFind + 1,16);
		*(pFind + 9) = 0;
	}
	pFrame->SetWindowText(m_Title);
	
	//查看是否有文件下载
	strcat(m_Id,".Ini");
	char m_FileName[256] = {0};
	GetModuleFileName(NULL,m_FileName,200);
	pFind = strrchr(m_FileName,'\\');
	if(pFind != NULL) *pFind = 0;
	SetCurrentDirectory(m_FileName);
	strcat(m_FileName, "\\data\\");
	strcat(m_FileName, m_Id);
	pFrame->SetIniFileName(m_FileName);

	CFileStatus m_Status;
	if(CFile::GetStatus(m_FileName, m_Status) 
		&& m_Status.m_size)
		pFrame->LoadTransInfo();
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	pFrame->BringWindowToTop();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPcFileApp message handlers

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPcFileApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPcFileApp message handlers

