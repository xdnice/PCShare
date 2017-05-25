// SocketRx.h: interface for the CSocketRx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETRX_H__DFEE9DEC_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_)
#define AFX_SOCKETRX_H__DFEE9DEC_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProtocolRx.h"
class CProtocolRx;
class CSocketRx  
{
public:
	CSocketRx();
	CSocketRx(SOCKET,HANDLE&);
	virtual ~CSocketRx();
	static DWORD RdTh(CSocketRx *);

	SOCKET m_hSocket;
	HANDLE m_hThread;
	int m_nExit;
	CProtocolRx m_Protocol;
};

#endif // !defined(AFX_SOCKETRX_H__DFEE9DEC_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_)
