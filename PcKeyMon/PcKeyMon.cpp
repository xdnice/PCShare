// PcKeyMon.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "PcKeyMon.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPcKeyMonApp

BEGIN_MESSAGE_MAP(CPcKeyMonApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()


// CPcKeyMonApp 构造

CPcKeyMonApp::CPcKeyMonApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CPcKeyMonApp 对象

CPcKeyMonApp theApp;

// CPcKeyMonApp 初始化

BOOL CPcKeyMonApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

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

	//取初始化参数
	CMainFrame* pFrame = new CMainFrame;

	//标题
	char m_Title[256] = {0};
	strcpy(m_Title, m_lpCmdLine);
	char* pFind = strrchr(m_Title,':');
	if(pFind != NULL)
	{
		*(pFind + 9) = 0;
	}
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME);
	pFrame->SetWindowText(m_Title);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	pFrame->BringWindowToTop();
	return TRUE;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CPcKeyMonApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CPcKeyMonApp 消息处理程序

