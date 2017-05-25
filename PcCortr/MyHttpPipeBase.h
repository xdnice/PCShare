// MyHttpPipeBase.h: interface for the CMyHttpPipeBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYHTTPPIPEBASE_H__33524551_7C26_4EE5_BF3D_D8B751B46BD4__INCLUDED_)
#define AFX_MYHTTPPIPEBASE_H__33524551_7C26_4EE5_BF3D_D8B751B46BD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHttpBase.h"

class CMyHttpPipeBase  
{
public:
	void StopWork();
	virtual BOOL StartWork(char* m_ServerAddr, int m_ServerPort, int nSend, int nRecv);
	CMyHttpPipeBase();
	virtual ~CMyHttpPipeBase();

	BOOL SendData(char* pData, DWORD nLen);
	BOOL RecvData(char* pData, DWORD nLen);
private:

	CMyHttpBase m_PipeSend;
	CMyHttpBase m_PipeRecv;
};

#endif // !defined(AFX_MYHTTPPIPEBASE_H__33524551_7C26_4EE5_BF3D_D8B751B46BD4__INCLUDED_)
