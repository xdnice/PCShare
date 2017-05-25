// MyKeyMonTrans.h: interface for the CMyKeyMonTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYKEYMONTRANS_H__B56715F4_723A_460F_BD0A_6A3F4AF94D1E__INCLUDED_)
#define AFX_MYKEYMONTRANS_H__B56715F4_723A_460F_BD0A_6A3F4AF94D1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyHttpPipeBase.h"

class CMyKeyMonTrans : public CMyHttpPipeBase  
{
public:
	CMyKeyMonTrans();
	virtual ~CMyKeyMonTrans();
	virtual BOOL StartWork(char* m_ServerAddr, int m_ServerPort, 
							int nSend, int nRecv);
	void ProcessCmd();

	HANDLE		hExitEvent;
	static void RecvThread(LPVOID);
};

#endif // !defined(AFX_MYKEYMONTRANS_H__B56715F4_723A_460F_BD0A_6A3F4AF94D1E__INCLUDED_)
