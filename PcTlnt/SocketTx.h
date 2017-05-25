// SocketTx.h: interface for the CSocketTx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETTX_H__DFEE9DEA_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_)
#define AFX_SOCKETTX_H__DFEE9DEA_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSocketTx  
{
public:
	CSocketTx(SOCKET,HANDLE&);
	virtual ~CSocketTx();
	static DWORD SendTh(CSocketTx*);

	SOCKET m_hSocket;
	HANDLE m_hThread;
	int m_nExit;
};

#endif // !defined(AFX_SOCKETTX_H__DFEE9DEA_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_)
