// PcMulitDlg.cpp : implementation file
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
// CPcMulitDlg dialog

CPcMulitDlg::CPcMulitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPcMulitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPcMulitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(m_Title,0,sizeof(m_Title));
	m_WaitCur = AfxGetApp()->LoadCursor(IDC_CURSOR_WAIT);
	m_CurSorStatus = TRUE;

	m_Info.pDesData = new char[101952];
	m_Info.pSrcData = new char[101952];
}

CPcMulitDlg::~CPcMulitDlg()
{
	delete [] m_Info.pDesData;
	delete [] m_Info.pSrcData;
}

void CPcMulitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPcMulitDlg)
	DDX_Control(pDX, IDC_STATIC_FRAME, m_Frame);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPcMulitDlg, CDialog)
	//{{AFX_MSG_MAP(CPcMulitDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_COPYDATA()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GETONEFRAME, DrawOneFrame)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcMulitDlg message handlers

BOOL CPcMulitDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_Title);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRect rcMain;
	GetClientRect(&rcMain);
	CRect reFrame;
	reFrame.left = (rcMain.Width() - IMAGE_WIDTH)/2;
	reFrame.bottom = rcMain.Height();
	reFrame.top = reFrame.bottom - IMAGE_HEIGHT - 2;
	reFrame.right = reFrame.left + IMAGE_WIDTH + 2;
	m_Frame.MoveWindow(reFrame);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPcMulitDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPcMulitDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPcMulitDlg::OnOK() 
{
	
}

void CPcMulitDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CPcMulitDlg::SetTitle(char *pTitle)
{
	strcpy(m_Title, pTitle);
}

void CPcMulitDlg::StartWork(void)
{
	m_Info.hWnd = GetSafeHwnd();
	_beginthread(TransMuiltThread, 0, &m_Info);
}

BOOL CPcMulitDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	//接收套接字信息
	LPWSAPROTOCOL_INFO pInfo = 
		(LPWSAPROTOCOL_INFO) pCopyDataStruct->lpData;

	if(pCopyDataStruct->dwData == CONN_FILE_MULT_RECV)
	{
		//发送信息套接字
		m_Info.soSend = WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
	}
	else if(pCopyDataStruct->dwData == CONN_FILE_MULT_SEND)
	{
		//接收信息套接字
		m_Info.soRecv = WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		m_CurSorStatus = FALSE;
		PostMessage(WM_SETCURSOR);
		StartWork();
	}
	else
		return CDialog::OnCopyData(pWnd, pCopyDataStruct);
	return TRUE;
}

LRESULT CPcMulitDlg::DrawOneFrame(WPARAM wParam, LPARAM lParam)
{
	if(lParam == TRUE)
	{
		//图形信息
		memcpy(&m_BmpInfo, (LPBITMAPINFO) 
			wParam,	sizeof(BITMAPINFO));
		return TRUE;
	}

	if(m_BmpInfo.bmiHeader.biWidth == 0)
		return FALSE;

	m_Frame.DrawOneFrame(&m_BmpInfo, m_Info.pDesData);
	return TRUE;
}

BOOL CPcMulitDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_CurSorStatus)
	{
		SetCursor(m_WaitCur);
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

