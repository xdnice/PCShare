// PcFrame.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PcFrame.h"
#include "MyFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPcFrameApp

BEGIN_MESSAGE_MAP(CPcFrameApp, CWinApp)
	//{{AFX_MSG_MAP(CPcFrameApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcFrameApp construction

CPcFrameApp::CPcFrameApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPcFrameApp object

CPcFrameApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPcFrameApp initialization

BOOL CPcFrameApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

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

//	if(strlen(m_lpCmdLine) == 0) return FALSE;

	//取初始化参数
	CMyFrameWnd* pFrame = new CMyFrameWnd;

	//标题
	char m_Title[256] = {0};
	strcpy(m_Title, m_lpCmdLine);
	char* pFind = strrchr(m_Title,':');
	if(pFind != NULL)
	{
		*(pFind + 9) = 0;
	}
	m_pMainWnd = pFrame;
	pFrame->Create(NULL,m_Title);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	pFrame->BringWindowToTop();
	return TRUE;
}

int CPcFrameApp::ExitInstance() 
{
	WSACleanup();
	return CWinApp::ExitInstance();
}

void CPcFrameApp::WinHelp(DWORD dwData, UINT nCmd) 
{

}
