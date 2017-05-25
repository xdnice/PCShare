// SocketDx.cpp: implementation of the CSocketDx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcTlnt.h"
#include "SocketDx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketDx::CSocketDx(char *strIP,int nPort)
{
unsigned long ip;

  if((*strIP <= '9') && (*strIP >= '0'))
  {
     if((ip = inet_addr(strIP)) == INADDR_NONE)
       printf("invalid host ip given");
  }
  else
  {
    hostent* ent = gethostbyname(strIP);
    if(!ent) printf("\nError\n");
    ip = *(unsigned long*)(ent->h_addr);
  }

	m_sockaddr_in.sin_family = AF_INET;
	m_sockaddr_in.sin_port = htons(nPort);
	m_sockaddr_in.sin_addr = *(in_addr*)&ip;
}
CSocketDx::~CSocketDx()
{

}
int CSocketDx::Create()
{
  m_hSocket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
  if ( m_hSocket == INVALID_SOCKET) return -1;
  return 0;
}
int CSocketDx::Connect()
{
int nRet;

  nRet = connect(m_hSocket,(sockaddr*)&m_sockaddr_in,sizeof(sockaddr));
  if ( nRet == SOCKET_ERROR ) return -1;
  return 0;
}
SOCKET CSocketDx::TelnetConnect()
{
int nRet;
	
	nRet = Create();
	if ( nRet < 0 ) return NULL;

	nRet = Connect();
	if ( nRet < 0 ) return NULL;

	return m_hSocket;
}
