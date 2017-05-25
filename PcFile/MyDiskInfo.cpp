// MyDiskInfo.cpp : implementation file
//

#include "stdafx.h"
#include "MyDiskInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDiskInfo dialog


CMyDiskInfo::CMyDiskInfo(DISKINFO m_DiskInfo)
	: CDialog(CMyDiskInfo::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMyDiskInfo)
	m_Volum = _T("");
	m_Content = _T("");
	m_FatType = _T("");
	m_Type = _T("");
	m_Unuse = _T("");
	m_Use = _T("");
	//}}AFX_DATA_INIT

	m_Title.Format("对象 %s 信息",m_DiskInfo.m_Name);
	m_Volum = _T(m_DiskInfo.m_Volume);
	m_FatType = _T(m_DiskInfo.m_FileSys);

	ULONGLONG m_dUse = m_DiskInfo.TotalNumberOfBytes - m_DiskInfo.FreeBytesAvailable;
	//未使用
	if(m_DiskInfo.FreeBytesAvailable/(1024 * 1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_DiskInfo.FreeBytesAvailable/1024;
		float m_len = (float)TmpLen/(1024*1024);
		m_Unuse.Format("%.1f GB (%I64d 字节)",m_len,m_DiskInfo.FreeBytesAvailable);
	}
	else if(m_DiskInfo.FreeBytesAvailable/(1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_DiskInfo.FreeBytesAvailable/1024;
		float m_len = (float)TmpLen/1024;
		m_Unuse.Format("%.1f MB (%I64d 字节)",m_len,m_DiskInfo.FreeBytesAvailable);
	}
	else if(m_DiskInfo.FreeBytesAvailable/1024 >0)
	{
		LONGLONG TmpLen = m_DiskInfo.FreeBytesAvailable/1024;
		float m_len = (float) TmpLen;
		m_Unuse.Format("%.1f KB (%I64d 字节)",m_len,m_DiskInfo.FreeBytesAvailable);
	}
	else
	{
		m_Unuse.Format("%I64d 字节 (%I64d 字节)",m_DiskInfo.FreeBytesAvailable,m_DiskInfo.FreeBytesAvailable);
	}

	//总容量
	if(m_DiskInfo.TotalNumberOfBytes/(1024 * 1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_DiskInfo.TotalNumberOfBytes/1024;
		float m_len = (float)TmpLen/(1024*1024);
		m_Content.Format("%.1f GB (%I64d 字节)",m_len,m_DiskInfo.TotalNumberOfBytes);
	}
	else if(m_DiskInfo.TotalNumberOfBytes/(1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_DiskInfo.TotalNumberOfBytes/1024;
		float m_len = (float)TmpLen/1024;
		m_Content.Format("%.1f MB (%I64d 字节)",m_len,m_DiskInfo.TotalNumberOfBytes);
	}
	else if(m_DiskInfo.TotalNumberOfBytes/1024 >0)
	{
		LONGLONG TmpLen = m_DiskInfo.TotalNumberOfBytes/1024;
		float m_len = (float) TmpLen;
		m_Content.Format("%.1f KB (%I64d 字节)",m_len,m_DiskInfo.TotalNumberOfBytes);
	}
	else
	{
		m_Content.Format("%I64d 字节 (%I64d 字节)",m_DiskInfo.TotalNumberOfBytes,m_DiskInfo.TotalNumberOfBytes);
	}

	//已使用
	if(m_dUse/(1024 * 1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_dUse/1024;
		float m_len = (float)TmpLen/(1024*1024);
		m_Use.Format("%.1f GB (%I64d 字节)",m_len,m_dUse);
	}
	else if(m_dUse/(1024 * 1024) > 0)
	{
		LONGLONG TmpLen = m_dUse/1024;
		float m_len = (float)TmpLen/1024;
		m_Use.Format("%.1f MB (%I64d 字节)",m_len,m_dUse);
	}
	else if(m_dUse/1024 >0)
	{
		LONGLONG TmpLen = m_dUse/1024;
		float m_len = (float) TmpLen;
		m_Use.Format("%.1f KB (%I64d 字节)",m_len,m_dUse);
	}
	else
	{
		m_Use.Format("%I64d 字节 (%I64d 字节)",m_dUse,m_dUse);
	}

	switch(m_DiskInfo.m_DeviceType)
	{
		case DRIVE_NO_ROOT_DIR	:	m_Type = "无法找到磁盘信息";break;
		case DRIVE_REMOVABLE	:	m_Type = "移动磁盘";break;
		case DRIVE_FIXED		:	m_Type = "本地磁盘";break;
		case DRIVE_REMOTE		:	m_Type = "远程磁盘";break;
		case DRIVE_CDROM		:	m_Type = "光盘驱动器";break;
		case DRIVE_RAMDISK		:	m_Type = "内存映射盘";break;
		default					:	m_Type = "无法找到磁盘信息";break;
	}
}

void CMyDiskInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDiskInfo)
	DDX_Text(pDX, IDC_EDIT_VOLUM, m_Volum);
	DDX_Text(pDX, IDC_STATIC_CONTENT, m_Content);
	DDX_Text(pDX, IDC_STATIC_FAT_TYPE, m_FatType);
	DDX_Text(pDX, IDC_STATIC_TYPE, m_Type);
	DDX_Text(pDX, IDC_STATIC_UNUSE, m_Unuse);
	DDX_Text(pDX, IDC_STATIC_USE, m_Use);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDiskInfo, CDialog)
	//{{AFX_MSG_MAP(CMyDiskInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDiskInfo message handlers

BOOL CMyDiskInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_Title);		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
