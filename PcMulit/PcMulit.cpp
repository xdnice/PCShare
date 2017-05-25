// PcMulit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PcMulit.h"
#include "PcMulitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPcMulitApp

BEGIN_MESSAGE_MAP(CPcMulitApp, CWinApp)
	//{{AFX_MSG_MAP(CPcMulitApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcMulitApp construction

CPcMulitApp::CPcMulitApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPcMulitApp object

CPcMulitApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPcMulitApp initialization

BOOL CPcMulitApp::InitInstance()
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
		return FALSE;

	if (LOBYTE(data.wVersion) !=2 || 
		HIBYTE(data.wVersion) != 2)
	{
		WSACleanup();
		return FALSE;
	}

	if(strlen(m_lpCmdLine) == 0) return FALSE;

	//标题
	char m_Title[256] = {0};
	strcpy(m_Title, m_lpCmdLine);
	char* pFind = strrchr(m_Title,':');
	if(pFind != NULL)
	{
		*(pFind + 9) = 0;
	}

	CPcMulitDlg dlg;
	dlg.SetTitle(m_Title);
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
