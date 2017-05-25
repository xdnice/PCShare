// MySocketDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PcTlnt.h"
#include "MySocketDlg.h"


// CMySocketDlg 对话框

IMPLEMENT_DYNAMIC(CMySocketDlg, CDialog)
CMySocketDlg::CMySocketDlg(char* pTitle, HANDLE hEvent)

{
	m_soSend = 0;
	m_soRecv = 0;
	strcpy(m_Title,pTitle);
	hExitEvent = hEvent;
}

CMySocketDlg::~CMySocketDlg()
{
}

void CMySocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMySocketDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CMySocketDlg 消息处理程序

void CMySocketDlg::OnBnClickedOk()
{
	//OnOK();
}

void CMySocketDlg::OnBnClickedCancel()
{
	//OnCancel();
}

BOOL CMySocketDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	//接收套接字信息
	LPWSAPROTOCOL_INFO pInfo = 
		(LPWSAPROTOCOL_INFO) pCopyDataStruct->lpData;

	if(pCopyDataStruct->dwData == CONN_FILE_TLNT_RECV)
	{
		//发送信息套接字
		m_soSend = WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
	}
	else if(pCopyDataStruct->dwData == CONN_FILE_TLNT_SEND)
	{
		//接收信息套接字
		m_soRecv = WSASocket(AF_INET, SOCK_STREAM,0,
			pInfo,0,WSA_FLAG_OVERLAPPED);
		SetEvent(hExitEvent);
	}
	else
		return CDialog::OnCopyData(pWnd, pCopyDataStruct);
	return TRUE;
}

BOOL CMySocketDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_Title);

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


