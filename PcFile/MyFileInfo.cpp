// MyFileInfo.cpp : implementation file
//

#include "stdafx.h"
#include "MyFileInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileInfo dialog


CMyFileInfo::CMyFileInfo(CFileStatus m_FileStatus)
	: CDialog(CMyFileInfo::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMyFileInfo)
	//}}AFX_DATA_INIT
	char * p = strrchr(m_FileStatus.m_szFullName,'\\');
	ASSERT(p);
	p++;
	m_Title.Format("对象 %s 信息",p);
	*p = 0;
	
	m_Path = _T(m_FileStatus.m_szFullName);
	m_CreateTime = _T(m_FileStatus.m_ctime.Format("%Y年%m月%d日,%H:%m:%S"));
	m_AccessTime = _T(m_FileStatus.m_atime.Format("%Y年%m月%d"));
	m_ModifyTime = _T(m_FileStatus.m_mtime.Format("%Y年%m月%d日,%H:%m:%S"));
	
	if(m_FileStatus.m_attribute & 0x10)
	{
		m_Type = _T("目录");
	}
	else
	{
		m_Type = _T("文件");
	}

	m_Arich = (m_FileStatus.m_attribute & 0x20) > 0 ? 1 : 0;
	m_Hide = (m_FileStatus.m_attribute & 0x02) > 0 ? 1 : 0;
	m_ReadOnly = (m_FileStatus.m_attribute & 0x01) > 0 ? 1 : 0;

	if(m_FileStatus.m_size/(1024 * 1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_FileStatus.m_size/1024;
		float m_len = (float)TmpLen/(1024*1024);
		m_Len.Format("%.1f GB (%ld 字节)",m_len,m_FileStatus.m_size);
	}
	else if(m_FileStatus.m_size/(1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_FileStatus.m_size/1024;
		float m_len = (float)TmpLen/1024;
		m_Len.Format("%.1f MB (%ld 字节)",m_len,m_FileStatus.m_size);
	}
	else if(m_FileStatus.m_size/1024 >0)
	{
		LONGLONG TmpLen = m_FileStatus.m_size/1024;
		float m_len = (float) TmpLen;
		m_Len.Format("%.1f KB (%ld 字节)",m_len,m_FileStatus.m_size);
	}
	else
	{
		m_Len.Format("%ld 字节 (%ld 字节)",m_FileStatus.m_size,m_FileStatus.m_size);
	}
}


void CMyFileInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyFileInfo)
	DDX_Check(pDX, IDC_CHECK3, m_Arich);
	DDX_Check(pDX, IDC_CHECK2, m_Hide);
	DDX_Check(pDX, IDC_CHECK1, m_ReadOnly);
	DDX_Text(pDX, IDC_EDIT_PATH, m_Path);
	DDX_Text(pDX, IDC_STATIC_ACCESSTIME, m_AccessTime);
	DDX_Text(pDX, IDC_STATIC_CREATETIME, m_CreateTime);
	DDX_Text(pDX, IDC_STATIC_LEN, m_Len);
	DDX_Text(pDX, IDC_STATIC_MODIFYTIME, m_ModifyTime);
	DDX_Text(pDX, IDC_STATIC_TYPE, m_Type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyFileInfo, CDialog)
	//{{AFX_MSG_MAP(CMyFileInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFileInfo message handlers

BOOL CMyFileInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_Title);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


