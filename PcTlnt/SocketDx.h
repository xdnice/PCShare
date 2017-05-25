// SocketDx.h: interface for the CSocketDx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETDX_H__DFEE9DED_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_)
#define AFX_SOCKETDX_H__DFEE9DED_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSocketDx  
{
public:
	CSocketDx(char *,int);
	~CSocketDx();
	int Create();
	int Connect();
	SOCKET TelnetConnect();
	sockaddr_in m_sockaddr_in;
	SOCKET m_hSocket;
};

#endif // !defined(AFX_SOCKETDX_H__DFEE9DED_9AF1_11D2_A6CE_204C4F4F5020__INCLUDED_)
