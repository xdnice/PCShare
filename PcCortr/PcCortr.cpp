// PcCortr.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "PcCortr.h"
#include ".\mymaintrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CPcCortrApp, CWinApp)
	//{{AFX_MSG_MAP(CPcCortrApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcCortrApp construction

CPcCortrApp::CPcCortrApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPcCortrApp object

CPcCortrApp theApp;
void ProcessTrans(HINTERNET hFp , HANDLE m_ExitEvent ,char* pServerAddr , 
				int   nServerPort ,	char* pRegInfo ,char* pFileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CMyMainTrans m_Trans;
	m_Trans.DoWork(hFp,m_ExitEvent,pServerAddr,nServerPort,pRegInfo,pFileName);
}
