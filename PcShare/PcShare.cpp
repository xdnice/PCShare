// PcShare.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PcShare.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPcShareApp

BEGIN_MESSAGE_MAP(CPcShareApp, CWinApp)
	//{{AFX_MSG_MAP(CPcShareApp)

		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcShareApp construction

CPcShareApp::CPcShareApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_LockHandle = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPcShareApp object

CPcShareApp theApp;
extern GOLBALVALUE m_MainValue;

/////////////////////////////////////////////////////////////////////////////
// CPcShareApp initialization

BOOL CPcShareApp::InitInstance()
{
	//保证只启动一次
	m_LockHandle = CreateMutex(NULL,TRUE,"PcShare2005");
	if(m_LockHandle == NULL ||
		GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;
	ReleaseMutex(m_LockHandle);

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

	//初始化控件环境
	AfxEnableControlContainer();
	//Enable3dControls();	
    CoInitialize(NULL);

	memset(&m_MainValue, 0, sizeof(m_MainValue));

	//启动主界面
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->ResizeWnd();
	pFrame->UpdateWindow();

	pFrame->StartWork();
	return TRUE;
}


