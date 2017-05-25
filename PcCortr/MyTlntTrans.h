// MyTlntTrans.h: interface for the CMyTlntTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTLNTTRANS_H__D438FABD_683A_40E8_91D5_FC993011810D__INCLUDED_)
#define AFX_MYTLNTTRANS_H__D438FABD_683A_40E8_91D5_FC993011810D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHttpPipeBase.h"

class CMyTlntTrans : public CMyHttpPipeBase  
{
public:
	CMyTlntTrans();
	virtual ~CMyTlntTrans();

	virtual BOOL StartWork(char* m_ServerAddr, int m_ServerPort, 
							int nSend, int nRecv);
	void ProcessCmd();

private:
	BOOL	CreateShellRedirect();
	BOOL	CreateChildProcess();
	
	HANDLE	hExitEvent;
	HANDLE	hChildStdinRd;
	HANDLE	hChildStdinWr;
	HANDLE	hChildStdinWrDup;
	HANDLE	hChildStdoutRd;
	HANDLE	hChildStdoutWr;
	HANDLE	hChildStdoutRdDup;
	HANDLE	hSaveStdin;
	HANDLE	hSaveStdout;
	HANDLE	hProcess;

	CMyHttpBase m_TlntHttp;
	static void TlntThread(LPVOID);
};

#endif // !defined(AFX_MYTLNTTRANS_H__D438FABD_683A_40E8_91D5_FC993011810D__INCLUDED_)
