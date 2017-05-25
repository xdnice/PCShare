// MyDirInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyDirInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDirInfoDlg dialog


CMyDirInfoDlg::CMyDirInfoDlg(DIRINFO m_DirInfo)
	: CDialog(CMyDirInfoDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMyDirInfoDlg)
	
	//}}AFX_DATA_INIT

	char * p = strrchr(m_DirInfo.m_FileStatus.m_szFullName,'\\');
	ASSERT(p);
	p++;
	m_Title.Format("对象 %s 信息",p);
	*p = 0;
	
	m_Path = _T(m_DirInfo.m_FileStatus.m_szFullName);
	m_Time = _T(m_DirInfo.m_FileStatus.m_ctime.Format("%Y年%m月%d日,%H:%m:%S"));
	m_FileCount.Format("%d 个文件,%d 个文件夹",
		m_DirInfo.m_FileCount,m_DirInfo.m_DirCount);

	if(m_DirInfo.m_AllFileSize/(1024 * 1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_DirInfo.m_AllFileSize/1024;
		float m_len = (float)TmpLen/(1024*1024);
		m_Len.Format("%.1f GB (%I64d 字节)",m_len,m_DirInfo.m_AllFileSize);
	}
	else if(m_DirInfo.m_AllFileSize/(1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_DirInfo.m_AllFileSize/1024;
		float m_len = (float)TmpLen/1024;
		m_Len.Format("%.1f MB (%I64d 字节)",m_len,m_DirInfo.m_AllFileSize);
	}
	else if(m_DirInfo.m_AllFileSize/1024 >0)
	{
		LONGLONG TmpLen = m_DirInfo.m_AllFileSize/1024;
		float m_len = (float) TmpLen;
		m_Len.Format("%.1f KB (%I64d 字节)",m_len,m_DirInfo.m_AllFileSize);
	}
	else
	{
		m_Len.Format("%I64d 字节 (%I64d 字节)",m_DirInfo.m_AllFileSize,m_DirInfo.m_AllFileSize);
	}

	if(m_DirInfo.m_FileStatus.m_attribute & 0x10)
	{
		m_Type = _T("目录");
	}
	else
	{
		m_Type = _T("文件");
	}

	m_Arich = (m_DirInfo.m_FileStatus.m_attribute & 0x20) > 0 ? 1 : 0;
	m_Hide = (m_DirInfo.m_FileStatus.m_attribute & 0x02) > 0 ? 1 : 0;
	m_ReadOnly = (m_DirInfo.m_FileStatus.m_attribute & 0x01) > 0 ? 1 : 0;
}


void CMyDirInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDirInfoDlg)
	DDX_Text(pDX, IDC_EDIT_PATH, m_Path);
	DDX_Text(pDX, IDC_STATIC_CREATETIME, m_Time);
	DDX_Text(pDX, IDC_STATIC_FILECOUNT, m_FileCount);
	DDX_Text(pDX, IDC_STATIC_LEN, m_Len);
	DDX_Text(pDX, IDC_STATIC_TYPE, m_Type);
	DDX_Check(pDX, IDC_CHECK_ARICH, m_Arich);
	DDX_Check(pDX, IDC_CHECK_HIDE, m_Hide);
	DDX_Check(pDX, IDC_CHECK_READONLY, m_ReadOnly);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDirInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDirInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDirInfoDlg message handlers

BOOL CMyDirInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_Title);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
