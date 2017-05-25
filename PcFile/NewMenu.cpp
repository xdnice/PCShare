//------------------------------------------------------------------------------
// File    : NewMenu.cpp 
// Version : 1.18
// Date    : 30. November 2003
// Author  : Bruno Podetti
// Email   : Podetti@gmx.net
// Web     : www.podetti.com/NewMenu 
// Systems : VC6.0/7.0 and VC7.1 (Run under (Window 98/ME), Windows Nt 2000/XP)
//
// For bugreport please add following informations
// - The CNewMenu version number (Example CNewMenu 1.16)
// - Operating system Win95 / WinXP and language (English / Japanese / German etc.)
// - Intalled service packs
// - Short description how to reproduce the bug
// - Pictures/Sample are wellcome too
// - You can write in English or German to the above email-address.
// - Have my compiled examples the same effect?
//
// Special
// Compiled version with visual studio V7.0/7.1 doesn't run correctly on 
// WinNt 4.0 nor Windows 95. For those platforms, you have to compile it with 
// visual studio V6.0. 
// (It may run with 7.0/7.1, but you must be sure to have all required and newest
//  dll from the MFC installed => otherwise menu painting problems)
// Keep in mind you should have installed latest service-packs to the operating-
// system too! (And a new IE because some fixes of common components were made)
// 
// ToDo's
// checking GDI-Leaks, are there some more?
// Shade-Drawing, when underground is changing
// Border repainting after menu closing!!!
// Shade painting problems? On Chinese or Japanese systems?
// ALT-Key-support in menubar
//
// 30. November 2003 (Version 1.18)
// minor changes for CNewToolBar
//
// 11. September 2003 Bug Fixes or nice hints from 1.16
// Better handling of menubar brushes (never destroy) Style_XP and STYLE_XP_2003
// Drawing of menuicons on WinNt 4.0 fixed
// spelling & initializing & unused brushes fixed, thanks to John Zegers
//
// 12. July 2003 Bug Fixes or nice hints from 1.15
// Added gradient-Dockbar (CNewDockBar) for office 2003 style
// (you need to define USE_NEW_DOCK_BAR)
// fixed menu checkmarks with bitmaps (Selection-with is not correct on all styles)
// Drawing to a memory-DC minimizing flickering
// with of menu-bar-item without & now better
//
// 22. June 2003 Bug Fixes or nice hints from 1.14
// Shortkey-handling for ModifyODMenu and InsertODMenu 
// Change os identifer for OS>5.0 to WinXP
// Color scheme for Office menu changed and updating menubarcolor too
// Gradientcolor for Office 2003 bar
// XP-changing settings Border Style => fixed border painting without restarting
//
// 23. April 2003 Bug Fixes or nice hints from 1.13
// Fixed the window menu with extreme width, thanks to Voy 
// Fix bug about shortkey for added menu item with AppendMenu, thanks to Mehdy Bohlool(Zy)
// Measureitem for default item corrected, thanks to LordLiverpool 
// New menu style office 2003, but color schema is not tested, changing of menubar color
// on win95 and WinNt is not possible
// Menubardrawing on deactivated app corrected for win95 & WinNt4.0
//
// 23. January 2003 Bug Fixes or nice hints from 1.12
// Fixed SetMenuText, thanks to Eugene Plokhov
// Easier for having an other menu font, but on your own risk ;)
// Added new function SetNewMenuBorderAllMenu for borderhandling off non CNewMenu
// 
// 22. December 2002 Bug Fixes or nice hints from 1.11
// Added some new tracing stuffs
// fixed SetMenuText
// XP-Style menu more office style and better handling with less 256 color, thanks to John Zegers
// Close window button disabling under XP with theme fixed
// Menubar color with theme fixed, thanks to Luther Weeks 
//
// (9. November) Bug Fixes or nice hints from 1.11b
// Some new function for bleaching bitmaps, thanks to John Zegers
// GetSubMenu(LPCTSTR) , thanks to George Menhorn
// Menu animation under Win 98 fixed
// Borderdrawing a little better also under win 98
// Added new menustyle ICY
//
// (21. August 2002) Bug Fixes or nice hints from 1.10
// Bugfix for Windows NT 4.0 System Bitmaps, thanks to Christoph Weber 
//
// (30. July 2002) Bug Fixes or nice hints from 1.03
// Color of checked icons / selection marks more XP-look
// Updating images 16 color by changing systems colors
// Icon drawing with more highlighting and half transparency 
// Scroller for large menu correcting (but the overlapping border is not corrected)
// Resource-problem on windows 95/98/ME?, when using too much bitmaps in menus
//  changing the kind of storing bitmaps (images list)
// Calculating the size for a menuitem (specially submenuitem) corrected.
// Recentfilelist corrected (Seperator gots a wrong ID number)
//
// (25. June 2002) Bug Fixes or nice hints from 1.02
// Adding removing menu corrected for drawing the shade in menubar
// Draw the menuborder corrected under win 98 at the bottom side
// Highlighting under 98 for menu corrected (Assert), Neville Franks
//  Works also on Windows 95
// Changing styles on XP menucolor of the bar now corrected.
//
// (18. June 2002) Bug Fixes or nice hints from 1.01
// Popup menu which has more items than will fit, better 
// LoadMenu changed for better languagessuport, SnowCat
// Bordercolor & Drawing of XP-Style-Menu changed to more XP-Look
// Added some functions for setting/reading MenuItemData and MenuData
// Menubar highlighting now supported under 98/ME (NT 4.0 and 95?)
// Font for menutitle can be changed
// Bugs for popupmenu by adding submenu corrected, no autodestroy
//
// (6. June 2002) Bug Fixes or nice hints from 1.00
// Loading Icons from a resource dll expanded (LoadToolBar) Jonathan de Halleux, Belgium.
// Minimized resource leak of User and Gdi objects
// Problem of disabled windows button on 98/Me solved
// Gradient-drawing without Msimg32.dll now supported especially for win 95
// Using solid colors for drawing menu items
// GetSubMenu changed to const
// Added helper function for setting popup-flag for popup menu (centered text)
// Redraw menu bar corrected after canceling popup menu in old style menu
//
// (23. Mai 2002) Bug Fixes and portions of code from previous version supplied by:
// Brent Corkum, Ben Ashley, Girish Bharadwaj, Jean-Edouard Lachand-Robert,
// Robert Edward Caldecott, Kenny Goers, Leonardo Zide, Stefan Kuhr, 
// Reiner Jung, Martin Vladic, Kim Yoo Chul, Oz Solomonovich, Tongzhe Cui, 
// Stephane Clog, Warren Stevens, Damir Valiulin
// 
// You are free to use/modify this code but leave this header intact.
// This class is public domain so you are free to use it any of your 
// applications (Freeware, Shareware, Commercial). 
// All I ask is that you let me know so that if you have a real winner I can
// brag to my buddies that some of my code is in your app. I also wouldn't 
// mind if you sent me a copy of your application since I like to play with
// new stuff.
//------------------------------------------------------------------------------

#include "stdafx.h"        // Standard windows header file
#include "NewMenu.h"       // CNewMenu class declaration

// Those two following constants should be only defined for tracing.
// Normally they are commented out.
//#define _TRACE_MENU_
//#define _TRACE_MENU_LOGFILE

//#define _NEW_MENU_USER_FONT
// For using an userfont you can set the define. It does not work right in the
// systemmenu nor in the menubar. But when you like to use the new menu only in
// popups then it will work, but it is newer a good idea to set or change the
// menufont.
// I do not support this mode, you use it on your own risk. :)
#ifdef _NEW_MENU_USER_FONT
static  LOGFONT MENU_USER_FONT = {20, 0, 0, 0, FW_NORMAL,
                                  0, 0, 0, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                                  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                  DEFAULT_PITCH,_T("Comic Sans MS")};
#endif

#ifdef _TRACE_MENU_
#include "MyTrace.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#endif

#ifndef IS_INTRESOURCE
#define IS_INTRESOURCE(hh) (HIWORD(hh)==NULL)
#endif 

#define GAP 2

#ifndef COLOR_MENUBAR
#define COLOR_MENUBAR       30
#endif

#ifndef SPI_GETDROPSHADOW
#define SPI_GETDROPSHADOW   0x1024
#endif

#ifndef SPI_GETFLATMENU
#define SPI_GETFLATMENU     0x1022
#endif

// Count of menu icons normal gloomed and grayed
#define MENU_ICONS    3

BOOL bHighContrast = FALSE;

typedef BOOL (WINAPI* FktGradientFill)( IN HDC, IN PTRIVERTEX, IN ULONG, IN PVOID, IN ULONG, IN ULONG);
typedef BOOL (WINAPI* FktIsThemeActive)();
typedef HRESULT (WINAPI* FktSetWindowTheme)(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);

FktGradientFill pGradientFill = NULL;
FktIsThemeActive pIsThemeActive = NULL;
FktSetWindowTheme pSetWindowTheme = NULL;

/////////////////////////////////////////////////////////////////////////////
// Forwarddeclaration
void DrawGradient(CDC* pDC,CRect& Rect,
                  COLORREF StartColor,COLORREF EndColor, 
                  BOOL bHorizontal,BOOL bUseSolid=FALSE);

COLORREF DarkenColorXP(COLORREF color);
COLORREF DarkenColor( long lScale, COLORREF lColor);
COLORREF LightenColor( long lScale, COLORREF lColor);


/////////////////////////////////////////////////////////////////////////////

// Helper datatypes
class CToolBarData
{
public:
  WORD wVersion;
  WORD wWidth;
  WORD wHeight;
  WORD wItemCount;
  //WORD aItems[wItemCount]
  WORD* items()
    { return (WORD*)(this+1); }
};

class CNewMenuIconInfo
{
public:
  WORD wBitmapID;
  WORD wWidth;
  WORD wHeight;

  WORD* ids(){ return (WORD*)(this+1); }
};

// Helpers for casting
__inline HMENU UIntToHMenu(const unsigned int ui )
{
  return( (HMENU)(UINT_PTR)ui );
}

__inline HMENU HWndToHMenu(const HWND hWnd )
{
  return( (HMENU)hWnd );
}

__inline HWND HMenuToHWnd(const HMENU hMenu)
{
  return( (HWND)hMenu );
}

__inline UINT HWndToUInt(const HWND hWnd )
{
  return( (UINT)(UINT_PTR) hWnd);
}

__inline HWND UIntToHWnd(const UINT hWnd )
{
  return( (HWND)(UINT_PTR) hWnd);
}

__inline UINT HMenuToUInt(const HMENU hMenu )
{
  return( (UINT)(UINT_PTR) hMenu);
}

static void ShowLastError()
{
  DWORD error = GetLastError();
  if(error)
  {
    LPVOID lpMsgBuf=NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_FROM_SYSTEM | 
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  error,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  (LPTSTR) &lpMsgBuf,
                  0,
                  NULL );
    if(lpMsgBuf)
    {
      // Display the string.
      MessageBox( NULL, (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );
      // Free the buffer.
      LocalFree( lpMsgBuf );
    }
    else
    {
      CString temp;
      temp.Format(_T("Error message 0x%lx not found"),error);
      // Display the string.
      MessageBox( NULL,temp, _T("Error"), MB_OK | MB_ICONINFORMATION );
    }
  }
}

UINT GetSafeTimerID(HWND hWnd, const UINT uiElapse)
{
  UINT nNewTimerId = NULL;
  if(IsWindow(hWnd))
  { // Try to start with TimerID 31, normaly is used 1, 10, or 100
    for(UINT nTimerId=31; nTimerId<100 && nNewTimerId==NULL; nTimerId++)
    { // Try to set a timer each uiElapse ms
      nNewTimerId = (UINT)::SetTimer(hWnd,nTimerId,uiElapse,NULL);
    }
    // Wow you have more than 69 timers!!!
    // Try to increase nTimerId<100 to nTimerId<1000;
    ASSERT(nNewTimerId);
  }
  return nNewTimerId;
}

WORD NumBitmapColors(LPBITMAPINFOHEADER lpBitmap)
{
  if ( lpBitmap->biClrUsed != 0)
    return (WORD)lpBitmap->biClrUsed;
  
  switch (lpBitmap->biBitCount)
  {
  case 1:
    return 2;
  case 4:
    return 16;
  case 8:
    return 256;
  }
  return 0;
}

static int NumScreenColors()
{
  static int nColors = 0;
  if (!nColors)
  {
    // DC of the desktop
    CClientDC myDC(NULL);
    nColors = myDC.GetDeviceCaps(NUMCOLORS);
    if (nColors == -1)
    {
      nColors = 64000;
    }
  }
  return nColors;
}  

HBITMAP LoadColorBitmap(LPCTSTR lpszResourceName, HMODULE hInst, int* pNumcol)
{
  if(hInst==0)
  {
    hInst = AfxFindResourceHandle(lpszResourceName, RT_BITMAP);
  }
  HRSRC hRsrc = ::FindResource(hInst,MAKEINTRESOURCE(lpszResourceName),RT_BITMAP);
  if (hRsrc == NULL)
    return NULL;

  // determine how many colors in the bitmap
  HGLOBAL hglb;
  if ((hglb = LoadResource(hInst, hRsrc)) == NULL)
    return NULL;

  LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);
  if (lpBitmap == NULL)
    return NULL;
  WORD numcol = NumBitmapColors(lpBitmap);
  if(pNumcol)
  {
    *pNumcol = numcol;
  }

  UnlockResource(hglb);
  FreeResource(hglb);

  return LoadBitmap(hInst,lpszResourceName);
  //TODO: check it bpo
  //if(numcol!=16)
  //{
  //  return LoadBitmap(hInst,lpszResourceName);
  //  //  (HBITMAP)LoadImage(hInst,lpszResourceName,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_CREATEDIBSECTION|LR_SHARED);
  //}
  //else
  //{
  //  // mapping from color in DIB to system color
  //  // { RGB_TO_RGBQUAD(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
  //  // { RGB_TO_RGBQUAD(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark gray
  //  // { RGB_TO_RGBQUAD(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright gray
  //  // { RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT }   // white
  //  return (HBITMAP)AfxLoadSysColorBitmap(hInst,hRsrc,FALSE);
  //}
}

#if(WINVER < 0x0500)

class CNewLoadLib
{
public:

  HMODULE m_hModule;
  void* m_pProg;

  CNewLoadLib(LPCTSTR pName,LPCSTR pProgName)
  {
    m_hModule = LoadLibrary(pName);
    m_pProg = m_hModule ? (void*)GetProcAddress (m_hModule,pProgName) : NULL;
  }

  ~CNewLoadLib()
  {
    if(m_hModule)
    {
      FreeLibrary(m_hModule);
      m_hModule = NULL;
    }
  }
};

BOOL GetMenuInfo( HMENU hMenu, LPMENUINFO pInfo)
{
  static CNewLoadLib menuInfo(_T("user32.dll"),"GetMenuInfo");
  if(menuInfo.m_pProg)
  {
    typedef BOOL (WINAPI* FktGetMenuInfo)(HMENU, LPMENUINFO);
    return ((FktGetMenuInfo)menuInfo.m_pProg)(hMenu,pInfo);
  }
  return FALSE;
}

BOOL SetMenuInfo( HMENU hMenu, LPCMENUINFO pInfo)
{
  static CNewLoadLib menuInfo(_T("user32.dll"),"SetMenuInfo");
  if(menuInfo.m_pProg)
  {
    typedef BOOL (WINAPI* FktSetMenuInfo)(HMENU, LPCMENUINFO);
    return ((FktSetMenuInfo)menuInfo.m_pProg)(hMenu,pInfo);
  }
  return FALSE;
}

#endif

class CNewBrushList : public CObList
{
public:
  CNewBrushList(){}
  ~CNewBrushList()
  {
    while(!IsEmpty())
    {
      delete RemoveTail();
    }
  }
};

class CNewBrush : public CBrush
{
public:
  UINT m_nMenuDrawMode;
  COLORREF m_BarColor;

  CNewBrush(UINT menuDrawMode, COLORREF barColor):m_nMenuDrawMode(menuDrawMode),m_BarColor(barColor)
  {
    if(menuDrawMode==CNewMenu::STYLE_XP_2003)
    {
         // Get the desktop hDC... 
        HDC hDcDsk = GetWindowDC(0) ;
        CDC* pDcDsk = CDC::FromHandle(hDcDsk);

        CDC clientDC;
        clientDC.CreateCompatibleDC(pDcDsk); 

        CRect rect(0,0,(GetSystemMetrics(SM_CXFULLSCREEN)+16)&~7,20);

        CBitmap bitmap;
        bitmap.CreateCompatibleBitmap(pDcDsk,rect.Width(),rect.Height());
        CBitmap* pOldBitmap = clientDC.SelectObject(&bitmap);

        DrawGradient(&clientDC,rect,barColor,LightenColor(110,barColor),TRUE,TRUE);

        clientDC.SelectObject(pOldBitmap);

        // Release the desktopdc
        ReleaseDC(0,hDcDsk);

        CreatePatternBrush(&bitmap);
    }
    else
    {
      CreateSolidBrush(barColor);
    }
  }
};

CBrush* GetMenuBarBrush()
{
  // The brushes will be destroyed at program-end => Not a memory-leak
  static CNewBrushList brushList;
  static CNewBrush* lastBrush = NULL;

  COLORREF menuBarColor;

  UINT nMenuDrawMode = CNewMenu::GetMenuDrawMode();

  switch(nMenuDrawMode)
  {
  case CNewMenu::STYLE_XP_2003 :
  case CNewMenu::STYLE_XP_2003_NOBORDER :
    {
      menuBarColor = CNewMenu::GetMenuBarColor2003();
      if (NumScreenColors()>=256 && !bHighContrast)
      {
        nMenuDrawMode = CNewMenu::STYLE_XP_2003;
      }
      else
      {
        nMenuDrawMode = CNewMenu::STYLE_XP;
      }
    }
    break;

  case CNewMenu::STYLE_XP :
  case CNewMenu::STYLE_XP_NOBORDER :
    menuBarColor = GetSysColor(COLOR_3DFACE);
    nMenuDrawMode = CNewMenu::STYLE_XP;
    break;

  //case CNewMenu::STYLE_ICY :
  //case CNewMenu::STYLE_ICY_NOBORDER :
  //  menuBarColor = RGB(0,0,255);
  //  nMenuDrawMode = CNewMenu::STYLE_XP;
  //  break;

  default:
    return NULL; 
  }

  // check if the last brush the one which we want
  if(lastBrush!=NULL && lastBrush->m_nMenuDrawMode==nMenuDrawMode && lastBrush->m_BarColor==menuBarColor)
  {
    return lastBrush;
  }

  // Check if the brush is allready created
  POSITION pos = brushList.GetHeadPosition();
  while (pos)
  {
    lastBrush = (CNewBrush*)brushList.GetNext(pos);
    if(lastBrush!=NULL && 
       lastBrush->m_nMenuDrawMode==nMenuDrawMode && 
       lastBrush->m_BarColor==menuBarColor)
    {
      return lastBrush;
    }
  }
  // create a new one and insert into the list
  brushList.AddHead(lastBrush = new CNewBrush(nMenuDrawMode,menuBarColor));
  return lastBrush;
}

void UpdateMenuBarColor(HMENU hMenu)
{
  CBrush* pBrush = GetMenuBarBrush();

  // for WindowsBlind activating it's better for not to change menubar background
  if(!pBrush /* || (pIsThemeActive && pIsThemeActive()) */ )
  { 
    // menubackground hasn't been set
    return;
  }

  MENUINFO menuInfo = {0};
  menuInfo.cbSize = sizeof(menuInfo);
  menuInfo.hbrBack = *pBrush;
  menuInfo.fMask = MIM_BACKGROUND;

  // Change color only for CNewMenu and derived classes
  if(IsMenu(hMenu) && DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hMenu))!=NULL)
  {
    SetMenuInfo(hMenu,&menuInfo);
  }

  CWinApp* pWinApp = AfxGetApp();
  // Update menu from template
  if(pWinApp)
  {
    CDocManager* pManager = pWinApp->m_pDocManager;
    if(pManager)
    {
      POSITION pos = pManager->GetFirstDocTemplatePosition();
      while(pos)
      {
        CDocTemplate* pTemplate = pManager->GetNextDocTemplate(pos);
        CMultiDocTemplate* pMultiTemplate = DYNAMIC_DOWNCAST(CMultiDocTemplate,pTemplate);
        if(pMultiTemplate)
        {
          // Change color only for CNewMenu and derived classes
          if(DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(pMultiTemplate->m_hMenuShared))!=NULL)
          {
            // need for correct menubar color
            SetMenuInfo(pMultiTemplate->m_hMenuShared,&menuInfo);
          }
        }
      }
    }
  }
}

BOOL DrawMenubarItem(CWnd* pWnd,CMenu* pMenu, UINT nItemIndex,UINT nState)
{
  CRect itemRect;
  if (nItemIndex!=UINT(-1) && GetMenuItemRect(pWnd->m_hWnd,pMenu->m_hMenu, nItemIndex, &itemRect))
  { 
    MENUITEMINFO menuInfo = {0};
    menuInfo.cbSize = sizeof(menuInfo);
    menuInfo.fMask = MIIM_DATA|MIIM_TYPE|MIIM_ID;
    if(pMenu->GetMenuItemInfo(nItemIndex,&menuInfo,TRUE))
    {
      // Only ownerdrawn were allowed
      if(menuInfo.fType&MF_OWNERDRAW)
      {        
        CWindowDC dc(pWnd);

        CFont fontMenu;
        LOGFONT logFontMenu;

        #ifdef _NEW_MENU_USER_FONT
            logFontMenu =  MENU_USER_FONT;
        #else
        NONCLIENTMETRICS nm = {0};
            nm.cbSize = sizeof (NONCLIENTMETRICS);
            VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
            logFontMenu =  nm.lfMenuFont;
        #endif

        fontMenu.CreateFontIndirect (&logFontMenu);
        CFont* pOldFont = dc.SelectObject(&fontMenu);

        CRect wndRect;
        GetWindowRect(*pWnd,wndRect);
        itemRect.OffsetRect(-wndRect.TopLeft());

        DRAWITEMSTRUCT drwItem = {0};
        drwItem.CtlType = ODT_MENU;
        drwItem.hwndItem = HMenuToHWnd(pMenu->m_hMenu);
        drwItem.itemID = menuInfo.wID;
        drwItem.itemData = menuInfo.dwItemData;
        drwItem.rcItem = itemRect;
        drwItem.hDC = dc.m_hDC;
        drwItem.itemState = nState;
        drwItem.itemAction = ODA_DRAWENTIRE;

        ASSERT(menuInfo.dwItemData);

        CNewMenu::m_dwLastActiveItem = (DWORD)menuInfo.dwItemData;

        SendMessage(pWnd->GetSafeHwnd(),WM_DRAWITEM,NULL,(LPARAM)&drwItem);

        dc.SelectObject(pOldFont);

        return TRUE;
      }
    }
  }
  return FALSE;
}

Win32Type IsShellType()
{
  OSVERSIONINFO osvi = {0};
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

  DWORD winVer=GetVersion();
  if(winVer<0x80000000)
  {/*NT */
    if(!GetVersionEx(&osvi))
    {
      ShowLastError();
    }
    if(osvi.dwMajorVersion==4L)
    {
      return WinNT4;
    }
    else if(osvi.dwMajorVersion==5L && osvi.dwMinorVersion==0L)
    {
      return Win2000;
    }
    // thanks to John Zegers
    else if(osvi.dwMajorVersion>=5L)// && osvi.dwMinorVersion==1L)
    {
       return WinXP;
    }
    return WinNT3;
  }
  else if (LOBYTE(LOWORD(winVer))<4)
  {
    return Win32s;
  }

  if(!GetVersionEx(&osvi))
  {
    ShowLastError();
  }
  if(osvi.dwMajorVersion==4L && osvi.dwMinorVersion==10L)
  {
    return Win98;
  }
  else if(osvi.dwMajorVersion==4L && osvi.dwMinorVersion==90L)
  {
    return WinME;
  }
  return Win95;
}

BOOL IsShadowEnabled()
{
  BOOL bEnabled = FALSE;
  if(SystemParametersInfo(SPI_GETDROPSHADOW,0,&bEnabled,0))
  {
    return bEnabled;
  }
  return FALSE;
}

COLORREF DarkenColorXP(COLORREF color)
{
  return RGB( MulDiv(GetRValue(color),7,10),
              MulDiv(GetGValue(color),7,10),
              MulDiv(GetBValue(color)+55,7,10));
}

// Function splits a color into its RGB components and
// transforms the color using a scale 0..255
COLORREF DarkenColor( long lScale, COLORREF lColor)
{ 
  long red   = MulDiv(GetRValue(lColor),(255-lScale),255);
  long green = MulDiv(GetGValue(lColor),(255-lScale),255);
  long blue  = MulDiv(GetBValue(lColor),(255-lScale),255);

  return RGB(red, green, blue); 
}

COLORREF MixedColor(COLORREF colorA,COLORREF colorB)
{
  // ( 86a + 14b ) / 100
  int red   = MulDiv(86,GetRValue(colorA),100) + MulDiv(14,GetRValue(colorB),100);
  int green = MulDiv(86,GetGValue(colorA),100) + MulDiv(14,GetGValue(colorB),100);
  int blue  = MulDiv(86,GetBValue(colorA),100) + MulDiv(14,GetBValue(colorB),100);

  return RGB( red,green,blue);
}

COLORREF MidColor(COLORREF colorA,COLORREF colorB)
{ 
  // (7a + 3b)/10
  int red   = MulDiv(7,GetRValue(colorA),10) + MulDiv(3,GetRValue(colorB),10);
  int green = MulDiv(7,GetGValue(colorA),10) + MulDiv(3,GetGValue(colorB),10);
  int blue  = MulDiv(7,GetBValue(colorA),10) + MulDiv(3,GetBValue(colorB),10);

  return RGB( red, green, blue);
}

COLORREF GetXpHighlightColor()
{
  if(bHighContrast)
  {
    return GetSysColor(COLOR_HIGHLIGHT);
  }

  if (NumScreenColors() > 256) 
  {
    //return DarkenColor(30,MidColor(GetSysColor(COLOR_WINDOW),GetSysColor(COLOR_HIGHLIGHT)));
    return MidColor(GetSysColor(COLOR_WINDOW),GetSysColor(COLOR_HIGHLIGHT));
  }
  return GetSysColor(COLOR_WINDOW);
}

COLORREF GrayColor(COLORREF crColor)
{ 
  int Gray  = (((int)GetRValue(crColor)) + GetGValue(crColor) + GetBValue(crColor))/3;

  return RGB( Gray,Gray,Gray);
}

BOOL IsLightColor(COLORREF crColor)
{
  return (((int)GetRValue(crColor)) + GetGValue(crColor) + GetBValue(crColor))>(3*128);
}

// Function splits a color into its RGB components and
// transforms the color using a scale 0..255
COLORREF LightenColor( long lScale, COLORREF lColor)
{ 
  long R = MulDiv(255-GetRValue(lColor),lScale,255)+GetRValue(lColor);
  long G = MulDiv(255-GetGValue(lColor),lScale,255)+GetGValue(lColor);
  long B = MulDiv(255-GetBValue(lColor),lScale,255)+GetBValue(lColor);

  return RGB(R, G, B); 
}

COLORREF BleachColor(int Add, COLORREF color)
{
  return RGB( min (GetRValue(color)+Add, 255),
              min (GetGValue(color)+Add, 255),
              min (GetBValue(color)+Add, 255));
}


void DrawGradient(CDC* pDC,CRect& Rect,
                  COLORREF StartColor,COLORREF EndColor, 
                  BOOL bHorizontal,BOOL bUseSolid)
{
  int Count = pDC->GetDeviceCaps(NUMCOLORS);
  if(Count==-1)
    bUseSolid = FALSE;

  // for running under win95 and WinNt 4.0 without loading Msimg32.dll
  if(!bUseSolid && pGradientFill )
  {
    TRIVERTEX vert[2] ;
    GRADIENT_RECT gRect;

    vert [0].y = Rect.top;
    vert [0].x = Rect.left;

    vert [0].Red    = COLOR16(COLOR16(GetRValue(StartColor))<<8);
    vert [0].Green  = COLOR16(COLOR16(GetGValue(StartColor))<<8);
    vert [0].Blue   = COLOR16(COLOR16(GetBValue(StartColor))<<8);
    vert [0].Alpha  = 0x0000;

    vert [1].y = Rect.bottom;
    vert [1].x = Rect.right;

    vert [1].Red    = COLOR16(COLOR16(GetRValue(EndColor))<<8);
    vert [1].Green  = COLOR16(COLOR16(GetGValue(EndColor))<<8);
    vert [1].Blue   = COLOR16(COLOR16(GetBValue(EndColor))<<8);
    vert [1].Alpha  = 0x0000;

    gRect.UpperLeft  = 0;
    gRect.LowerRight = 1;

    if(bHorizontal)
    {
      pGradientFill(pDC->m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);
    }
    else
    {
      pGradientFill(pDC->m_hDC,vert,2,&gRect,1,GRADIENT_FILL_RECT_V);
    }
  }
  else
  {
    BYTE StartRed   = GetRValue(StartColor);
    BYTE StartGreen = GetGValue(StartColor);
    BYTE StartBlue  = GetBValue(StartColor);

    BYTE EndRed    = GetRValue(EndColor);
    BYTE EndGreen  = GetGValue(EndColor);
    BYTE EndBlue   = GetBValue(EndColor);

    int n = (bHorizontal)?Rect.Width():Rect.Height();

    // only need for the rest, can be optimized
    {
      if(bUseSolid)
      {
        // We need a solid brush (can not be doted)
        pDC->FillSolidRect(Rect,pDC->GetNearestColor(EndColor));
      }
      else
      {
        // We need a brush (can be doted)
        CBrush TempBrush(EndColor);
        pDC->FillRect(Rect,&TempBrush);
      }
    }
    int dy = 2;
    n-=dy;
    for(int dn=0;dn<=n;dn+=dy)
    {
      BYTE ActRed = (BYTE)(MulDiv(int(EndRed)-StartRed,dn,n)+StartRed);
      BYTE ActGreen = (BYTE)(MulDiv(int(EndGreen)-StartGreen,dn,n)+StartGreen);
      BYTE ActBlue = (BYTE)(MulDiv(int(EndBlue)-StartBlue,dn,n)+StartBlue);

      CRect TempRect; 
      if(bHorizontal)
      {
        TempRect = CRect(CPoint(Rect.left+dn,Rect.top),CSize(dy,Rect.Height()));
      }
      else
      {
        TempRect = CRect(CPoint(Rect.left,Rect.top+dn),CSize(Rect.Width(),dy));
      }
      if(bUseSolid)
      {
        pDC->FillSolidRect(TempRect,pDC->GetNearestColor(RGB(ActRed,ActGreen,ActBlue)));
      }
      else
      {
        CBrush TempBrush(RGB(ActRed,ActGreen,ActBlue));
        pDC->FillRect(TempRect,&TempBrush);
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CMenuTheme for drawing border and the rest

typedef void (CNewMenu::*pItemMeasureFkt) (LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenubar);
typedef void (CNewMenu::*pItemDrawFkt) (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenubar);
typedef BOOL (CNewMenu::*pEraseBkgndFkt) (HWND hWnd, HDC hDC);

typedef void (CMenuTheme::*pDrawMenuBorder)( HWND hWnd, HDC hDC, CPoint screen);

class CMenuTheme
{
public:
  CMenuTheme();

  CMenuTheme(DWORD dwThemeId, 
             pItemMeasureFkt pMeasureItem,
             pItemDrawFkt pDrawItem,
             pItemDrawFkt pDrawTitle,
             DWORD dwFlags=0);

  virtual ~CMenuTheme();
  virtual BOOL OnInitWnd(HWND hWnd);
  virtual BOOL OnUnInitWnd(HWND hWnd);

  virtual BOOL DoDrawBorder();

  virtual BOOL OnDrawBorder(HWND hWnd, HDC hDC, BOOL bOnlyBorder=FALSE);
  virtual BOOL OnEraseBkgnd(HWND hWnd, HDC hDC);
  virtual BOOL OnNcCalcSize(HWND hWnd, NCCALCSIZE_PARAMS* pCalc);
  virtual BOOL OnWindowPosChanging(HWND hWnd, LPWINDOWPOS pPos);
  virtual BOOL OnCalcFrameRect(HWND hWnd,LPRECT pRect);

  void DrawShade( HWND hWnd, HDC hDC, CPoint screen);
  void DrawSmalBorder( HWND hWnd, HDC hDC);
  void DrawFrame(CDC* pDC, CRect rectOuter, CRect rectInner, COLORREF crBorder);

  void* SetScreenBitmap(HWND hWnd, HDC hDC);

public:
  DWORD m_dwThemeId;
  DWORD m_dwFlags;

  pItemMeasureFkt m_pMeasureItem;
  pItemDrawFkt m_pDrawItem;
  pItemDrawFkt m_pDrawTitle;

  CSize m_BorderTopLeft;
  CSize m_BorderBottomRight;
};

/////////////////////////////////////////////////////////////////////////////
// CMenuThemeXP for drawing border and the rest

class CMenuThemeXP :public CMenuTheme
{
public:
  CMenuThemeXP(DWORD dwThemeId, 
                pItemMeasureFkt pMeasureItem,
                pItemDrawFkt pDrawItem,
                pItemDrawFkt pDrawTitle,
                DWORD dwFlags=0);

  virtual BOOL OnDrawBorder(HWND hWnd, HDC hDC, BOOL bOnlyBorder=FALSE);
  virtual BOOL OnEraseBkgnd(HWND hWnd, HDC hDC);
};

/////////////////////////////////////////////////////////////////////////////
// CNewMenuHook important class for subclassing menus!

class CNewMenuHook
{
public:
  class CMenuHookData 
  {
  public:
    CMenuHookData(HWND hWnd,BOOL bSpecialWnd) 
      : m_dwData(bSpecialWnd),m_bDrawBorder(FALSE),m_Point(0,0),m_hRgn((HRGN)1),m_bDoSubclass(TRUE)
    {
      // Safe actual menu
      SetMenu(CNewMenuHook::m_hLastMenu);
      // Reset for the next menu
      CNewMenuHook::m_hLastMenu = NULL;

      // Save actual border setting etc.
      m_dwStyle = GetWindowLong(hWnd, GWL_STYLE) ;
      m_dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE); 

      //if(pSetWindowTheme)pSetWindowTheme(hWnd,L" ",L" ");
    }

    ~CMenuHookData()
    {
      if(m_hRgn!=(HRGN)1)
      {
        DeleteObject(m_hRgn);
        m_hRgn = (HRGN)1;
      }
    }

    BOOL SetMenu(HMENU hMenu)
    {
      m_hMenu = hMenu;
      if(!CNewMenu::GetNewMenuBorderAllMenu() && 
         !DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hMenu)))
      {
        m_bDoSubclass = FALSE;
      }
      else
      {

        m_bDoSubclass = TRUE;
      }
      // When I change the backgroundcolor the borderdrawing well be wrong (scrollmenu)
      //if(IsMenu(hMenu) &&
      //    CNewMenu::GetMenuDrawMode()==CNewMenu::STYLE_XP || 
      //    CNewMenu::GetMenuDrawMode()==CNewMenu::STYLE_XP_NOBORDER )
      //{
      //  MENUINFO menuInfo;
      //  ZeroMemory(&menuInfo,sizeof(menuInfo));
      //  menuInfo.cbSize = sizeof(menuInfo);
      //  menuInfo.hbrBack = g_MenuBrush;
      //  menuInfo.fMask = MIM_BACKGROUND;
      //  ::SetMenuInfo(hMenu,&menuInfo);
      //}
      return m_bDoSubclass;
    }

    DWORD m_dwStyle;
    DWORD m_dwExStyle;

    CPoint m_Point;
    DWORD m_dwData; //  1=Sepcial WND, 2=Styles Changed,4=VK_ESCAPE, 8=in Print

    BOOL m_bDrawBorder;
    HMENU m_hMenu;

    CBitmap m_Screen;
    HRGN m_hRgn;

    BOOL m_bDoSubclass;
  }; 

public:
  CNewMenuHook();
  ~CNewMenuHook();

public:
  static CMenuHookData* GetMenuHookData(HWND hWnd);

  static BOOL AddTheme(CMenuTheme*);
  static CMenuTheme* RemoveTheme(DWORD dwThemeId);
  static CMenuTheme* FindTheme(DWORD dwThemeId);

private:
  static LRESULT CALLBACK NewMenuHook(int code, WPARAM wParam, LPARAM lParam);
  static BOOL CheckSubclassing(HWND hWnd,BOOL bSpecialWnd);
  static LRESULT CALLBACK SubClassMenu(HWND hWnd,  UINT uMsg, WPARAM wParam,  LPARAM lParam );
  static void UnsubClassMenu(HWND hWnd);
 
  static BOOL SubClassMenu2(HWND hWnd,  UINT uMsg, WPARAM wParam,  LPARAM lParam, DWORD* pResult);

public:
  static HMENU m_hLastMenu;
  static DWORD m_dwMsgPos; 
  static DWORD m_bSubclassFlag;

private:
  static HMODULE m_hLibrary;
  static HMODULE m_hThemeLibrary;
  static HHOOK HookOldMenuCbtFilter;

#ifdef _TRACE_MENU_LOGFILE
  static HANDLE m_hLogFile;
#endif //_TRACE_MENU_LOGFILE

  // an map of actual opened Menu and submenu
  static CTypedPtrMap<CMapPtrToPtr,HWND,CMenuHookData*> m_MenuHookData;
  // Stores list of all defined Themes
  static CTypedPtrList<CPtrList, CMenuTheme*>* m_pRegisteredThemesList; 
};

/////////////////////////////////////////////////////////////////////////////
// CNewMenuIconLock Helperclass for reference-counting !

class CNewMenuIconLock
{
  CNewMenuIcons* m_pIcons;

public:
  CNewMenuIconLock(CNewMenuIcons* pIcons):m_pIcons(pIcons)
  {
    m_pIcons->AddRef();
  }

  ~CNewMenuIconLock()
  {
    m_pIcons->Release();
  }
  operator CNewMenuIcons*(){return m_pIcons;}
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewMenuIcons,CObject); 

CNewMenuIcons::CNewMenuIcons()
: m_lpszResourceName(NULL),
  m_hInst(NULL),
  m_nColors(0),
  m_crTransparent(CLR_NONE),
  m_dwRefCount(0)
{
}

CNewMenuIcons::~CNewMenuIcons()
{
  if(m_lpszResourceName && !IS_INTRESOURCE(m_lpszResourceName))
  {
    delete (LPTSTR)m_lpszResourceName;
  }
}

int CNewMenuIcons::AddRef()
{
  if(this==NULL)
    return NULL;

  return ++m_dwRefCount;
}

int CNewMenuIcons::Release()
{
  if(this==NULL)
    return NULL;

  DWORD dwCount = --m_dwRefCount;
  if(m_dwRefCount==0)
  {
    if(CNewMenu::m_pSharedMenuIcons)
    {
      POSITION pos = CNewMenu::m_pSharedMenuIcons->Find(this);
      if(pos)
      {
        CNewMenu::m_pSharedMenuIcons->RemoveAt(pos);
      }      
    }
    delete this;
  }
  return dwCount;
}

#if defined(_DEBUG) || defined(_AFXDLL)
// Diagnostic Support
void CNewMenuIcons::AssertValid() const
{
  CObject::AssertValid();
}

void CNewMenuIcons::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);
  dc << _T("NewMenuIcons: ") << _T("\n"); 
}
#endif

BOOL CNewMenuIcons::DoMatch(LPCTSTR lpszResourceName, HMODULE hInst)
{
  if(hInst==m_hInst && lpszResourceName)
  {
    if(IS_INTRESOURCE(m_lpszResourceName))
    {
      return (lpszResourceName==m_lpszResourceName);
    }
    
    return (_tcscmp(lpszResourceName,m_lpszResourceName)==0);
  }
  return FALSE;
}

BOOL CNewMenuIcons::DoMatch(WORD* pIconInfo, COLORREF crTransparent)
{
  if(m_crTransparent==crTransparent && pIconInfo!=NULL)
  {
    CNewMenuIconInfo* pInfo = (CNewMenuIconInfo*)pIconInfo;

    // Check for the same resource ID
    if( pInfo->wBitmapID && IS_INTRESOURCE(m_lpszResourceName) &&
        ((UINT)(UINT_PTR)m_lpszResourceName)==pInfo->wBitmapID)
    {
      int nCount = (int)m_IDs.GetSize();
      WORD* pID = pInfo->ids();
      for(int nIndex=0 ; nIndex<nCount ; nIndex++,pID++)
      {
        if( (*pID)==0 || m_IDs.GetAt(nIndex)!=(*pID) )
        {
          return FALSE;
        }
      }
      return TRUE;
    }
  }
  return FALSE;
} 

int CNewMenuIcons::FindIndex(UINT nID)
{
  int nIndex = (int)m_IDs.GetSize();
  while(nIndex--)
  {
    if(m_IDs.GetAt(nIndex)==nID)
    {
      return nIndex*MENU_ICONS;
    }
  }
  return -1;
}

BOOL CNewMenuIcons::GetIconSize(int* cx, int* cy)
{
  return ::ImageList_GetIconSize(m_IconsList,cx,cy);
}

CSize CNewMenuIcons::GetIconSize()
{
  int cx=0;
  int cy=0;
  if(::ImageList_GetIconSize(m_IconsList,&cx,&cy))
  {
    return CSize(cx,cy);
  }
  return CSize(0,0);
}

void CNewMenuIcons::OnSysColorChange()
{
  if(m_lpszResourceName!=NULL)
  {
    int cx=16,cy=16;
    if(GetIconSize(&cx, &cy) && LoadBitmap(cx,cy,m_lpszResourceName,m_hInst))
    {
      MakeImages();
    }
  }
} 

BOOL CNewMenuIcons::LoadBitmap(int nWidth, int nHeight, LPCTSTR lpszResourceName, HMODULE hInst)
{
  m_nColors = 0;
  HBITMAP hBitmap = LoadColorBitmap(lpszResourceName,hInst,&m_nColors);
  if(hBitmap!=NULL)
  {
    CBitmap bitmap;
    bitmap.Attach(hBitmap);
    if(m_IconsList.GetSafeHandle())
    {
      m_IconsList.DeleteImageList();
    }
    m_IconsList.Create(nWidth,nHeight,ILC_COLORDDB|ILC_MASK,0,10); 
    m_IconsList.Add(&bitmap,m_crTransparent);

    return TRUE;
  }
  return FALSE;
}

BOOL CNewMenuIcons::LoadToolBar(WORD* pIconInfo, COLORREF crTransparent)
{
  BOOL bResult = FALSE;
  m_crTransparent = crTransparent;
  CNewMenuIconInfo* pInfo = (CNewMenuIconInfo*)pIconInfo; 
  
  if (LoadBitmap(pInfo->wWidth,pInfo->wHeight,MAKEINTRESOURCE(pInfo->wBitmapID)))
  {
    SetResourceName(MAKEINTRESOURCE(pInfo->wBitmapID));

    WORD* pID = pInfo->ids();
    while(*pID)
    {
      UINT nID = *(pID++);
      m_IDs.Add(nID);
      bResult = TRUE;
    }
    MakeImages();
  } 
  return bResult;
}

void CNewMenuIcons::SetResourceName(LPCTSTR lpszResourceName)
{
  ASSERT_VALID(this);
  ASSERT(lpszResourceName != NULL);

  if(m_lpszResourceName && !IS_INTRESOURCE(m_lpszResourceName))
  {
    delete (LPTSTR)m_lpszResourceName;
  }
  if( lpszResourceName && !IS_INTRESOURCE(lpszResourceName))
  {
    m_lpszResourceName = new TCHAR[_tcslen(lpszResourceName)+1];
    _tcscpy((LPTSTR)m_lpszResourceName,lpszResourceName);
  }
  else
  {
    m_lpszResourceName = lpszResourceName;
  }
}

BOOL CNewMenuIcons::LoadToolBar(LPCTSTR lpszResourceName, HMODULE hInst)
{
  ASSERT_VALID(this);

  SetResourceName(lpszResourceName);

  m_hInst = hInst;

  // determine location of the bitmap in resource
  if(hInst==0)
  {
    hInst = AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
  }
  HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
  
  if (hRsrc == NULL)
  { // Special purpose when you try to load it from a dll 30.05.2002
    if(AfxGetResourceHandle()!=hInst)
    {  
      hInst = AfxGetResourceHandle();
      hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
    }
    if (hRsrc == NULL)
    {
      return FALSE;
    }
  }

  HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
  if (hGlobal == NULL)
  {
    return FALSE;
  }

  CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
  if (pData == NULL)
  {
    return FALSE;
  }

  BOOL bResult = FALSE;
  ASSERT(pData->wVersion == 1);
  
  if(LoadBitmap(pData->wWidth,pData->wHeight,lpszResourceName,hInst))
  {
    // Remove all previous ID's
    m_IDs.RemoveAll();
    for (int i = 0; i < pData->wItemCount; i++)
    { 
      UINT nID = pData->items()[i];
      if (nID)
      {
        m_IDs.Add(nID);
        bResult = TRUE;
      }
    }
  }

  UnlockResource(hGlobal);
  FreeResource(hGlobal);
  
  MakeImages();
  
  return bResult;
}

int CNewMenuIcons::AddGloomIcon(HICON hIcon, int nIndex)
{
  ICONINFO iconInfo = {0};
  if(!GetIconInfo(hIcon,&iconInfo))
  {
    return -1;
  }

  CSize size = GetIconSize();
  CDC myDC;
  myDC.CreateCompatibleDC(0);

  CBitmap bmColor;
  bmColor.Attach(iconInfo.hbmColor);
  CBitmap bmMask;
  bmMask.Attach(iconInfo.hbmMask);

  CBitmap* pOldBitmap = myDC.SelectObject(&bmColor);
  COLORREF crPixel;
  for(int i=0;i<size.cx;++i)
  {
    for(int j=0;j<size.cy;++j)
    {
      crPixel = myDC.GetPixel(i,j);
      myDC.SetPixel(i,j,DarkenColor(50,crPixel));
//      //John Zegers
//      myDC.SetPixel(i,j,BleachColor(64, crPixel));
    }
  }
  myDC.SelectObject(pOldBitmap);
  if(nIndex==-1)
  {
    return m_IconsList.Add(&bmColor,&bmMask);
  }

  return (m_IconsList.Replace(nIndex,&bmColor,&bmMask)) ? nIndex: -1;
}

int CNewMenuIcons::AddGrayIcon(HICON hIcon, int nIndex)
{
  ICONINFO iconInfo = {0};
  if(!GetIconInfo(hIcon,&iconInfo))
  {
    return -1;
  }

  CSize size = GetIconSize();
  CDC myDC;
  myDC.CreateCompatibleDC(0);

  CBitmap bmColor;
  bmColor.Attach(iconInfo.hbmColor);
  CBitmap bmMask;
  bmMask.Attach(iconInfo.hbmMask);

  CBitmap* pOldBitmap = myDC.SelectObject(&bmColor);
  COLORREF crMenu = CNewMenu::GetMenuBarColor();
//  COLORREF crBtnFace = GetSysColor(COLOR_BTNFACE);
//  COLORREF crBtnShadow = GetSysColor(COLOR_BTNSHADOW);
  COLORREF crPixel;
  for(int i=0;i<size.cx;++i)
  {
    for(int j=0;j<size.cy;++j)
    {
      crPixel = myDC.GetPixel(i,j);

      //if (IsLightColor(crPixel)) 
      //{
      //  myDC.SetPixel(i,j,crBtnFace);
      //}
      //else 
      //{
      //  myDC.SetPixel(i,j,crBtnShadow);
      //}

      //myDC.SetPixel(i,j,GrayColor(crPixel));
      //myDC.SetPixel(i,j,MidColor(GrayColor(crPixel),crMenu));      
      myDC.SetPixel(i,j,MixedColor(LightenColor(100,GrayColor(crPixel)),crMenu));      
    }
  }
  myDC.SelectObject(pOldBitmap);
  if(nIndex==-1)
  {
    return m_IconsList.Add(&bmColor,&bmMask);
  }

  return (m_IconsList.Replace(nIndex,&bmColor,&bmMask)) ? nIndex: -1;
}

BOOL CNewMenuIcons::MakeImages()
{
  int nCount = m_IconsList.GetImageCount();
  if(!nCount)
  {
    return FALSE;
  }

  CSize size = GetIconSize();
  CImageList ilTemp;
  ilTemp.Attach(m_IconsList.Detach()); 
  m_IconsList.Create(size.cx,size.cy,ILC_COLORDDB|ILC_MASK,0,10);

  for(int nIndex=0;nIndex<nCount;nIndex++)
  {
    HICON hIcon = ilTemp.ExtractIcon(nIndex);
    m_IconsList.Add(hIcon);
    AddGloomIcon(hIcon);
    AddGrayIcon(hIcon);

    DestroyIcon(hIcon);
  }
  return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewMenuBitmaps,CNewMenuIcons); 

CNewMenuBitmaps::CNewMenuBitmaps()
{
}

CNewMenuBitmaps::~CNewMenuBitmaps()
{
}

int CNewMenuBitmaps::Add(UINT nID, COLORREF crTransparent)
{
  int nIndex = (int)m_IDs.GetSize();
  while(nIndex--)
  {
    if(m_IDs.GetAt(nIndex)==nID)
    {
      return nIndex*MENU_ICONS;
    }
  }
  // Try to load the bitmap for getting dimension
  HBITMAP hBitmap = LoadColorBitmap(MAKEINTRESOURCE(nID),0);
  if(hBitmap!=NULL)
  {
    CBitmap temp;
    temp.Attach(hBitmap);

    BITMAP bitmap = {0};
    if(!temp.GetBitmap(&bitmap))
    {
        return -1;
    }

    if(m_IconsList.GetSafeHandle()==NULL)
    {
      m_IconsList.Create(bitmap.bmWidth,bitmap.bmHeight,ILC_COLORDDB|ILC_MASK,0,10);
    }
    else
    {
      CSize size = GetIconSize();
      // Wrong size?
      if(size.cx!=bitmap.bmWidth || size.cy!=bitmap.bmHeight)
      {
        return -1;
      }
    }
    m_TranspColors.Add(crTransparent);
    m_IDs.Add(nID);

    nIndex = m_IconsList.Add(&temp,crTransparent); 
    HICON hIcon = m_IconsList.ExtractIcon(nIndex);
    AddGloomIcon(hIcon);
    AddGrayIcon(hIcon);
    DestroyIcon(hIcon);

    //SetBlendImage();
    return nIndex;
  }
  return -1;
}

void CNewMenuBitmaps::OnSysColorChange()
{
  int nCount = (int)m_IDs.GetSize();
  for(int nIndex=0;nIndex<nCount;nIndex+=MENU_ICONS)
  {
    //Todo reload icons
    HICON hIcon = m_IconsList.ExtractIcon(nIndex);
    AddGloomIcon(hIcon,nIndex+1);
    AddGrayIcon(hIcon,nIndex+2);

    DestroyIcon(hIcon);
  }
}

int CNewMenuBitmaps::Add(HICON hIcon, UINT nID)
{
  ICONINFO iconInfo = {0};
  if(!GetIconInfo(hIcon,&iconInfo))
  {
    return -1;
  }

  CBitmap temp;
  temp.Attach(iconInfo.hbmColor);
  ::DeleteObject(iconInfo.hbmMask);

  BITMAP bitmap = {0};
  if(!temp.GetBitmap(&bitmap))
  {
    return -1;
  }

  if(m_IconsList.GetSafeHandle()==NULL)
  {
    m_IconsList.Create(bitmap.bmWidth,bitmap.bmHeight,ILC_COLORDDB|ILC_MASK,0,10);
  }
  else
  {
    CSize size = GetIconSize();
    // Wrong size?
    if(size.cx!=bitmap.bmWidth || size.cy!=bitmap.bmHeight)
    {
      return -1;
    }
  }
  if(nID)
  {
    int nIndex = (int)m_IDs.GetSize();
    while(nIndex--)
    {
      if(m_IDs.GetAt(nIndex)==nID)
      {
        // We found the index also replace the icon
        nIndex = nIndex*MENU_ICONS;
        m_IconsList.Replace(nIndex,hIcon);
        AddGloomIcon(hIcon,nIndex+1);
        AddGrayIcon(hIcon,nIndex+2);
        return nIndex;
      }
    }
  }
  COLORREF clr = CLR_NONE;
  m_TranspColors.Add(clr);
  m_IDs.Add(nID);
  int nIndex = m_IconsList.Add(hIcon);
  AddGloomIcon(hIcon);
  AddGrayIcon(hIcon);

  return nIndex;
}

int CNewMenuBitmaps::Add(CBitmap* pBitmap, COLORREF crTransparent)
{
  ASSERT(pBitmap);

  BITMAP bitmap = {0};
  if(!pBitmap->GetBitmap(&bitmap))
  {
    return -1;
  }

  if(m_IconsList.GetSafeHandle()==NULL)
  {
    m_IconsList.Create(bitmap.bmWidth,bitmap.bmHeight,ILC_COLORDDB|ILC_MASK,0,10);
  }
  else
  {
    CSize size = GetIconSize();
    // Wrong size?
    if(size.cx!=bitmap.bmWidth || size.cy!=bitmap.bmHeight)
    {
      return -1;
    }
  }
  UINT nID = 0;
  m_TranspColors.Add(crTransparent);
  m_IDs.Add(nID);
  int nIndex = m_IconsList.Add(pBitmap,crTransparent);
  HICON hIcon = m_IconsList.ExtractIcon(nIndex);
  AddGloomIcon(hIcon);
  AddGrayIcon(hIcon);
  DestroyIcon(hIcon);
  //SetBlendImage();
  return nIndex;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewMenuItemData,CObject); 

CNewMenuItemData::CNewMenuItemData()
: m_nTitleFlags(0),
  m_nFlags(0),
  m_nID(0),
  m_nSyncFlag(0),
  m_pData(NULL),
  m_pMenuIcon(NULL),
  m_nMenuIconOffset(-1)
{
}

CNewMenuItemData::~CNewMenuItemData()
{
  // it's a safe release. Do not care for NULL pointers.
  m_pMenuIcon->Release();
}

LPCTSTR CNewMenuItemData::GetString()
{
  return m_szMenuText;
}
 
void CNewMenuItemData::SetString(LPCTSTR szMenuText)
{
  m_szMenuText = szMenuText;
}

#if defined(_DEBUG) || defined(_AFXDLL)
// Diagnostic Support
void CNewMenuItemData::AssertValid() const
{
  CObject::AssertValid();
}

void CNewMenuItemData::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);
  dc << _T("MenuItem: ") << m_szMenuText << _T("\n"); 
}

#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewMenu,CMenu);

// actual selectet menu-draw mode
CMenuTheme* CNewMenu::m_pActMenuDrawing = NULL;
CTypedPtrList<CPtrList, CNewMenuIcons*>* CNewMenu::m_pSharedMenuIcons = NULL;

// Gloabal logfont for all menutitles
LOGFONT CNewMenu::m_MenuTitleFont = {16, 0, 0, 0, FW_BOLD,
                                    0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                    DEFAULT_PITCH,_T("Arial")};


void CNewMenu::SetMenuTitleFont(CFont* pFont)
{
  ASSERT(pFont);
  pFont->GetLogFont(&m_MenuTitleFont);
}

void CNewMenu::SetMenuTitleFont(LOGFONT* pLogFont)
{
  ASSERT(pLogFont);
  m_MenuTitleFont = *pLogFont;
}

LOGFONT CNewMenu::GetMenuTitleFont()
{
  return m_MenuTitleFont;
}

DWORD CNewMenu::m_dwLastActiveItem = NULL;

// how the menu's are drawn in winXP
BOOL CNewMenu::m_bEnableXpBlending=TRUE;
BOOL CNewMenu::m_bNewMenuBorderAllMenu=TRUE;
BOOL CNewMenu::m_bSelectDisable=TRUE;

const Win32Type g_Shell = IsShellType();
BOOL bRemoteSession = FALSE;

// one instance of the hook for menu-subclassing
static CNewMenuHook MyNewMenuHookInstance;

CNewMenu::CNewMenu(HMENU hParent)
: m_hTempOwner(NULL),
  m_hParentMenu(hParent),
  m_bIsPopupMenu(TRUE),
  m_dwOpenMenu(NULL),
  m_LastActiveMenuRect(0,0,0,0),
  m_pData(NULL)
{
  // O.S. - no dynamic icons by default
  m_bDynIcons = FALSE;
  // Icon sizes default to 16 x 16
  m_iconX = 16;
  m_iconY = 15;
  m_selectcheck = -1;
  m_unselectcheck = -1;
  m_checkmaps=NULL;
  m_checkmapsshare=FALSE;

  // set the color used for the transparent background in all bitmaps
  m_bitmapBackground = CLR_DEFAULT;
}

CNewMenu::~CNewMenu()
{
  DestroyMenu();
}

COLORREF CNewMenu::GetMenuColor(HMENU hMenu)
{
  if(hMenu!=NULL)
  {
    MENUINFO menuInfo={0};
    menuInfo.cbSize = sizeof(menuInfo);
    menuInfo.fMask = MIM_BACKGROUND;

    if(::GetMenuInfo(hMenu,&menuInfo) && menuInfo.hbrBack)
    {
      LOGBRUSH logBrush;
      if(GetObject(menuInfo.hbrBack,sizeof(LOGBRUSH),&logBrush))
      {
        return logBrush.lbColor;
      }
    }
  }

  if(IsShellType()==WinXP)
  {
    BOOL bFlatMenu = FALSE;
    // theme ist not checket, that must be so 
    if( (SystemParametersInfo(SPI_GETFLATMENU,0,&bFlatMenu,0) && bFlatMenu==TRUE) )
    {
      return GetSysColor(COLOR_MENUBAR);
    } 
  }
  return GetSysColor(COLOR_MENU);
}

COLORREF CNewMenu::GetMenuBarColorXP()
{
  // Win95 or WinNT do not support to change the menubarcolor
  if(IsShellType()==Win95 || IsShellType()==WinNT4)
  {
    return GetSysColor(COLOR_MENU);
  }
  return GetSysColor(COLOR_3DFACE);
}

COLORREF CNewMenu::GetMenuBarColor2003()
{
  // Win95 or WinNT do not support to change the menubarcolor
  if(IsShellType()==Win95 || IsShellType()==WinNT4)
  {
    return GetSysColor(COLOR_MENU);
  }
  COLORREF colorWindow = DarkenColor(10,GetSysColor(COLOR_WINDOW));
  COLORREF colorCaption = GetSysColor(COLOR_ACTIVECAPTION);

  CClientDC myDC(NULL);
  COLORREF nearColor = myDC.GetNearestColor(MidColor(colorWindow,colorCaption));

  // some colorscheme corrections (Andreas Sch鋜er)
  if (nearColor == 15779244) //standartblau 
  { //entspricht (haar-)genau office 2003
    nearColor = RGB(163,194,245);
  }
  else if (nearColor == 15132390) //standartsilber
  {
    nearColor = RGB(215,215,229);
  }
  else if (nearColor == 13425878) //olivgr黱
  {
    nearColor = RGB(218,218,170);
  }

  return nearColor;
}

COLORREF CNewMenu::GetMenuBarColor(HMENU hMenu)
{
  if(hMenu!=NULL)
  {
    MENUINFO menuInfo = {0};
    menuInfo.cbSize = sizeof(menuInfo);
    menuInfo.fMask = MIM_BACKGROUND;

    if(::GetMenuInfo(hMenu,&menuInfo) && menuInfo.hbrBack)
    {
      LOGBRUSH logBrush;
      if(GetObject(menuInfo.hbrBack,sizeof(LOGBRUSH),&logBrush))
      {
        return logBrush.lbColor;
      }
    }
  }
  if(IsShellType()==WinXP)
  {
    BOOL bFlatMenu = FALSE;
    if((SystemParametersInfo(SPI_GETFLATMENU,0,&bFlatMenu,0) && bFlatMenu==TRUE) ||
       (pIsThemeActive && pIsThemeActive()))
    {
      return GetSysColor(COLOR_MENUBAR);
    } 
  }
  return GetSysColor(COLOR_MENU);
}

void CNewMenu::SetLastMenuRect(HDC hDC, LPRECT pRect)
{
  if(!m_bIsPopupMenu)
  {
    HWND hWnd = WindowFromDC(hDC);
    if(hWnd && pRect)
    {
      CRect Temp;
      GetWindowRect(hWnd,Temp);
      m_LastActiveMenuRect = *pRect;
      m_LastActiveMenuRect.OffsetRect(Temp.TopLeft());
      #ifdef _TRACE_MENU_
        AfxTrace(_T("ActiveRect: (%ld,%ld,%ld,%ld)\n"),m_LastActiveMenuRect.left,m_LastActiveMenuRect.top,m_LastActiveMenuRect.right,m_LastActiveMenuRect.bottom);
      #endif 
    }
  }
}

BOOL CNewMenu::IsNewShell()
{
  return (g_Shell>=Win95);
}

BOOL CNewMenu::OnMeasureItem(const MSG* pMsg)
{
  if(pMsg->message==WM_MEASUREITEM)
  {
    LPMEASUREITEMSTRUCT lpMIS = (LPMEASUREITEMSTRUCT)pMsg->lParam;
    if(lpMIS->CtlType==ODT_MENU)
    {
      CMenu* pMenu=NULL;
      if(::IsMenu(UIntToHMenu(lpMIS->itemID)) )
      {
        pMenu = CMenu::FromHandlePermanent(UIntToHMenu(lpMIS->itemID) );
      }
      else
      {
        _AFX_THREAD_STATE* pThreadState = AfxGetThreadState ();
        if (pThreadState->m_hTrackingWindow == pMsg->hwnd)
        {
          // start from popup
          pMenu = FindPopupMenuFromIDData(pThreadState->m_hTrackingMenu,lpMIS->itemID,lpMIS->itemData);
        }
        if(pMenu==NULL)
        {
          // start from menubar
          pMenu = FindPopupMenuFromIDData(::GetMenu(pMsg->hwnd),lpMIS->itemID,lpMIS->itemData);
          if(pMenu==NULL)
          {
            // finaly start from system menu.
            pMenu = FindPopupMenuFromIDData(::GetSystemMenu(pMsg->hwnd,FALSE),lpMIS->itemID,lpMIS->itemData);
          }
        }
      }
      if(pMenu!=NULL)
      {
        #ifdef _TRACE_MENU_
        UINT oldWidth = lpMIS->itemWidth;
        #endif //_TRACE_MENU_

        pMenu->MeasureItem(lpMIS);

        #ifdef _TRACE_MENU_
          AfxTrace(_T("NewMenu MeasureItem: ID:0x08%X, oW:0x%X, W:0x%X, H:0x%X\n"),lpMIS->itemID,oldWidth,lpMIS->itemWidth,lpMIS->itemHeight);
        #endif //_TRACE_MENU_
        return TRUE;
      }
    }
  }
  return FALSE;
}

CMenu* CNewMenu::FindPopupMenuFromID(HMENU hMenu, UINT nID)
{
  // check for a valid menu-handle
  if ( ::IsMenu(hMenu))
  {
    CMenu *pMenu = CMenu::FromHandlePermanent(hMenu);
    if(pMenu)
    {
      return FindPopupMenuFromID(pMenu,nID);
    }
  }
  return NULL; 
}

CMenu* CNewMenu::FindPopupMenuFromIDData(HMENU hMenu, UINT nID, ULONG_PTR pData)
{
  // check for a valid menu-handle
  if ( ::IsMenu(hMenu))
  {
    CMenu *pMenu = CMenu::FromHandlePermanent(hMenu);
    if(pMenu)
    {
      return FindPopupMenuFromIDData(pMenu,nID,pData);
    }
  }
  return NULL; 
}

CMenu* CNewMenu::FindPopupMenuFromIDData(CMenu* pMenu, UINT nID, ULONG_PTR pData)
{
  if(!pMenu || !IsMenu(pMenu->m_hMenu))
  {
    return NULL;
  }
  ASSERT_VALID(pMenu);
  // walk through all items, looking for ID match
  UINT nItems = pMenu->GetMenuItemCount();
  for (int iItem = 0; iItem < (int)nItems; iItem++)
  {
    CMenu* pPopup = pMenu->GetSubMenu(iItem);
    if (pPopup!=NULL)
    {
      // recurse to child popup
      pPopup = FindPopupMenuFromIDData(pPopup, nID, pData);
      // check popups on this popup
      if (pPopup != NULL)
      {
        return pPopup;
      }
    }
    else if (pMenu->GetMenuItemID(iItem) == nID)
    { 
      MENUITEMINFO MenuItemInfo = {0};
      MenuItemInfo.cbSize = sizeof(MenuItemInfo);
      MenuItemInfo.fMask = MIIM_DATA;

      if(pMenu->GetMenuItemInfo(iItem,&MenuItemInfo,TRUE))
      {
        if(MenuItemInfo.dwItemData==pData)
        {
          // it is a normal item inside our popup
          return pMenu;
        }
      }
    }
  }
  // not found
  return NULL;
}

CMenu* CNewMenu::FindPopupMenuFromID(CMenu* pMenu, UINT nID)
{
  if(!pMenu || !IsMenu(pMenu->m_hMenu))
  {
    return NULL;
  }
  ASSERT_VALID(pMenu);
  // walk through all items, looking for ID match
  UINT nItems = pMenu->GetMenuItemCount();
  for (int iItem = 0; iItem < (int)nItems; iItem++)
  {
    CMenu* pPopup = pMenu->GetSubMenu(iItem);
    if (pPopup != NULL)
    {
      // recurse to child popup
      pPopup = FindPopupMenuFromID(pPopup, nID);
      // check popups on this popup
      if (pPopup != NULL)
      {
        return pPopup;
      }
    }
    else if (pMenu->GetMenuItemID(iItem) == nID)
    {
      // it is a normal item inside our popup
      return pMenu;
    }
  }
  // not found
  return NULL;
}

BOOL CNewMenu::DestroyMenu()
{
  // Destroy Sub menus:
  int m;
  int numSubMenus = (int)m_SubMenus.GetUpperBound();
  for(m = numSubMenus; m >= 0; m--)
  {
    // Destroy only if we createt it!!!!!
    CNewMenu* pMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(m_SubMenus[m]));
    if(pMenu)
    {
      delete pMenu;
    }
  }
  m_SubMenus.RemoveAll();

  // Destroy menu data
  int numItems = (int)m_MenuItemList.GetUpperBound();
  for(m = 0; m <= numItems; m++)
  {
    delete(m_MenuItemList[m]);
  }  
  m_MenuItemList.RemoveAll();
  
  if(m_checkmaps&&!m_checkmapsshare)
  {
    delete m_checkmaps;
    m_checkmaps=NULL;
  }
  // Call base-class implementation last:
  return(CMenu::DestroyMenu());
};

UINT CNewMenu::GetMenuDrawMode()
{
  ASSERT(m_pActMenuDrawing);
  return m_pActMenuDrawing->m_dwThemeId;
}

UINT CNewMenu::SetMenuDrawMode(UINT mode)
{
#ifdef _TRACE_MENU_
  if(mode&1)
  {
   AfxTrace(_T("\nDraw menu no border\n"));
  }
  else
  {
   AfxTrace(_T("\nDraw menu with border\n"));
  }
#endif //  _TRACE_MENU_  

  UINT nOldMode = (UINT)STYLE_UNDEFINED;
  CMenuTheme* pTheme = CNewMenuHook::FindTheme(mode);
  if(pTheme)
  {
    if(m_pActMenuDrawing)
    {
      nOldMode = m_pActMenuDrawing->m_dwThemeId;
    }

    m_pActMenuDrawing = pTheme;
  }
  return nOldMode;
}

HMENU CNewMenu::GetParent()
{
  return m_hParentMenu;
}

BOOL CNewMenu::IsPopup()
{
  return m_bIsPopupMenu;
}

BOOL CNewMenu::SetPopup(BOOL bIsPopup)
{
  BOOL bOldFlag = m_bIsPopupMenu;
  m_bIsPopupMenu = bIsPopup;
  return bOldFlag;
}

BOOL CNewMenu::SetSelectDisableMode(BOOL mode)
{
  BOOL bOldMode = m_bSelectDisable;
  m_bSelectDisable=mode;
  return bOldMode;
}

BOOL CNewMenu::GetSelectDisableMode()
{
  return m_bSelectDisable;
}

BOOL CNewMenu::SetXpBlendig(BOOL bEnable)
{
  BOOL bOldMode = m_bEnableXpBlending;
  m_bEnableXpBlending = bEnable;
  return bOldMode;
}

BOOL CNewMenu::GetXpBlendig()
{
  return m_bEnableXpBlending;
}

// Function to set how default menu border were drawn
//(enable=TRUE means that all menu in the application has the same border)
BOOL CNewMenu::SetNewMenuBorderAllMenu(BOOL bEnable /* =TRUE*/)
{                                                      
  BOOL bOldMode = m_bNewMenuBorderAllMenu;
  m_bNewMenuBorderAllMenu = bEnable;
  return bOldMode;
}

BOOL CNewMenu::GetNewMenuBorderAllMenu()
{
  return m_bNewMenuBorderAllMenu;
}

void CNewMenu::OnSysColorChange()
{
  static DWORD dwLastTicks = 0;
  DWORD dwAktTicks = GetTickCount();

  // Last Update 2 sec
  if((dwAktTicks-dwLastTicks)>2000)
  {
    dwLastTicks = dwAktTicks;
    if(m_pSharedMenuIcons)
    {
      POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
      while(pos)
      {
        CNewMenuIcons* pMenuIcons = m_pSharedMenuIcons->GetNext(pos);
        pMenuIcons->OnSysColorChange();
      }
    }
  }
} 

void CNewMenu::MeasureItem( LPMEASUREITEMSTRUCT lpMIS )
{
  ASSERT(m_pActMenuDrawing);

  BOOL bIsMenuBar = IsMenuBar(UIntToHMenu(lpMIS->itemID));
  if(!bIsMenuBar && m_hParentMenu &&::IsMenu(UIntToHMenu(lpMIS->itemID)) )
  {
    CNewMenu* pMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(m_hParentMenu));
    if(pMenu)
    {
      ((*pMenu).*m_pActMenuDrawing->m_pMeasureItem)(lpMIS,bIsMenuBar);
      return;
    }
  }
  ((*this).*m_pActMenuDrawing->m_pMeasureItem)(lpMIS,bIsMenuBar);
}

void CNewMenu::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
  ASSERT(m_pActMenuDrawing);
  
  BOOL bIsMenuBar = m_hParentMenu ? FALSE: ((m_bIsPopupMenu)?FALSE:TRUE);

  if(bIsMenuBar && m_dwLastActiveItem==lpDIS->itemData)
  {
    if(! (lpDIS->itemState&ODS_HOTLIGHT) )
    { 
      // Mark for redraw helper for win 98
      m_dwLastActiveItem = NULL;
    }
  }

  (this->*m_pActMenuDrawing->m_pDrawItem)(lpDIS,bIsMenuBar);
}

// Erase the Background of the menu
BOOL CNewMenu::EraseBkgnd(HWND hWnd, HDC hDC)
{
  CDC* pDC = CDC::FromHandle (hDC);
  CRect Rect;
  //  Get the size of the menu... 
  GetClientRect(hWnd, Rect );

  pDC->FillSolidRect (Rect,GetMenuColor());

  return TRUE;
}

void CNewMenu::DrawTitle(LPDRAWITEMSTRUCT lpDIS,BOOL bIsMenuBar)
{
  ASSERT(m_pActMenuDrawing);
  (this->*m_pActMenuDrawing->m_pDrawTitle)(lpDIS,bIsMenuBar);
}

void CNewMenu::DrawMenuTitle(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  UNREFERENCED_PARAMETER(bIsMenuBar);

  CDC* pDC = CDC::FromHandle(lpDIS->hDC);

  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);
  ASSERT(pMenuData);

  COLORREF colorWindow = GetSysColor(COLOR_WINDOW);
  COLORREF colorMenuBar = GetMenuColor();
  COLORREF colorMenu = MixedColor(colorWindow,colorMenuBar);

  CRect rcClipBox;
  pDC->GetClipBox(rcClipBox);

  // draw the title bar
  CRect rect = lpDIS->rcItem;
  CPoint TextPoint;

  CFont Font;
  LOGFONT MyFont = m_MenuTitleFont;
  if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
  {
    rect.top = rcClipBox.top;
    rect.bottom = rcClipBox.bottom;
    rect.right += GetSystemMetrics(SM_CXMENUCHECK);
    MyFont.lfOrientation = 900;
    MyFont.lfEscapement = 900;
    TextPoint = CPoint(rect.left+2, rect.bottom-4);
  }
  else
  {
    MyFont.lfOrientation = 0;
    MyFont.lfEscapement = 0;

    TextPoint = CPoint(rect.left+2, rect.top);
  }
  Font.CreateFontIndirect(&MyFont); 
  CFont *pOldFont = pDC->SelectObject(&Font);
  SIZE size = {0,0};
  VERIFY(::GetTextExtentPoint32(pDC->m_hDC,pMenuData->m_szMenuText,pMenuData->m_szMenuText.GetLength(),&size));
  COLORREF oldColor = pDC->SetTextColor(::GetSysColor(COLOR_CAPTIONTEXT));
  int OldMode = pDC->SetBkMode(TRANSPARENT);

  if(pMenuData->m_nTitleFlags&MFT_GRADIENT)
  {
    if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      DrawGradient(pDC,rect,colorMenu,::GetSysColor(COLOR_ACTIVECAPTION),false);
    }
    else
    {
      DrawGradient(pDC,rect,::GetSysColor(COLOR_ACTIVECAPTION),colorMenu,true);
    }
  }
  else
  {
    if(pMenuData->m_nTitleFlags&MFT_ROUND)
    {
      if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
      {
        TextPoint.y-=2;
        rect.right = rect.left+size.cy+4;
      }
      else
      {
        int maxSpace = ((rect.Width()-size.cx)/2);
        TextPoint.x+=min(maxSpace,10);
      }

      CBrush brush(GetSysColor(COLOR_ACTIVECAPTION));
      CPen* pOldPen = (CPen*)pDC->SelectStockObject(WHITE_PEN);
      CBrush* pOldBrush = pDC->SelectObject(&brush);

      pDC->RoundRect(rect,CPoint(10,10));
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
    }
    else
    {
      pDC->FillSolidRect(rect,GetSysColor(COLOR_ACTIVECAPTION));
    }
  }
  if (pMenuData->m_nTitleFlags&MFT_SUNKEN)
  {
    pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
  }

  if (pMenuData->m_nTitleFlags&MFT_CENTER)
  {
    if (pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      TextPoint.y = rect.bottom - ((rect.Height()-size.cx)>>1);
    }
    else
    {
      TextPoint.x = rect.left + ((rect.Width()-size.cx)>>1);
    }
  }

  pDC->TextOut(TextPoint.x,TextPoint.y, pMenuData->GetString());

  if(pMenuData->m_nTitleFlags&MFT_LINE)
  {
    if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
    {
      CRect rect2(rect.left+20,rect.top+5,rect.left+22,rect.bottom-5);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
      rect2.OffsetRect(3,0);
      rect2.InflateRect(0,-10);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
    }
    else
    {
      CRect rect2(rect.left+2,rect.bottom-7,rect.right-2,rect.bottom-5);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
      rect2.OffsetRect(0,3);
      rect2.InflateRect(-10,0);
      pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
    }
  }
  pDC->SetBkMode(OldMode);
  pDC->SetTextColor(oldColor);
  pDC->SelectObject(pOldFont);
}

void CNewMenu::DrawItem_WinXP(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  ASSERT(lpDIS != NULL);

  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);
  ASSERT(pMenuData);

  UINT state = pMenuData->m_nFlags;

  CNewMemDC memDC(&lpDIS->rcItem,lpDIS->hDC);
  CDC* pDC;
  if( bIsMenuBar || (state&MF_SEPARATOR) )
  { // For title and menubardrawing disable memory painting
    memDC.DoCancel();
    pDC = CDC::FromHandle(lpDIS->hDC);
  }
  else
  { 
    pDC = &memDC;
  }

  COLORREF colorWindow = GetSysColor(COLOR_WINDOW);
//  COLORREF colorMenuBar = bIsMenuBar?GetMenuBarColor(m_hMenu):GetMenuColor();
  COLORREF colorMenuBar = GetMenuBarColor(m_hMenu);
  COLORREF colorMenu = MixedColor(colorWindow,colorMenuBar);
  COLORREF colorBitmap = MixedColor(GetMenuBarColor(m_hMenu),colorWindow);
  COLORREF colorSel = GetXpHighlightColor();
  COLORREF colorBorder = GetSysColor(COLOR_HIGHLIGHT);//DarkenColor(128,colorMenuBar);

  if(bHighContrast)
  {
    colorBorder = GetSysColor(COLOR_BTNTEXT);
  }

  if (NumScreenColors() <= 256) 
  {
    colorBitmap = GetSysColor(COLOR_BTNFACE);
  }

  // Better contrast when you have less than 256 colors
  if(pDC->GetNearestColor(colorMenu)==pDC->GetNearestColor(colorBitmap))
  {
    colorMenu = colorWindow;
    colorBitmap = colorMenuBar;
  }

  //CPen Pen(PS_SOLID,0,GetSysColor(COLOR_HIGHLIGHT));
  CPen Pen(PS_SOLID,0,colorBorder);

  if(bIsMenuBar)
  {
#ifdef _TRACE_MENU_
 //   AfxTrace(_T("BarState: 0x%lX Menus %ld\n"),lpDIS->itemState,m_dwOpenMenu);
#endif
    if(!m_dwOpenMenu && lpDIS->itemState&ODS_SELECTED)
    {
      lpDIS->itemState = (lpDIS->itemState&~ODS_SELECTED)|ODS_HOTLIGHT;
    }
    if(!(lpDIS->itemState&ODS_HOTLIGHT))
    { 
      colorSel = colorBitmap;
    }
    colorMenu = colorMenuBar;
  }

  CBrush m_brSel(colorSel);
  CBrush m_brBitmap(colorBitmap);

  CRect RectL(lpDIS->rcItem);
  CRect RectR(lpDIS->rcItem);
  CRect RectSel(lpDIS->rcItem);

  if(bIsMenuBar)
  {
    RectR.InflateRect (0,0,0,0);
    RectSel.InflateRect (0,0,-2 -2,0);
  }  
  else
  {
    RectL.right = RectL.left + m_iconX + 8;
    RectR.left  = RectL.right;
    // Draw for Bitmapbackground
    pDC->FillSolidRect (RectL,colorBitmap);
  }
  // Draw for Textbackground
  pDC->FillSolidRect (RectR,colorMenu);

  // Spacing for submenu only in popups
  if(!bIsMenuBar)
  {
    RectR.left += 4;
    RectR.right-= 15;
  }

  //  Flag for highlighted item
  if(lpDIS->itemState & (ODS_HOTLIGHT|ODS_INACTIVE) )
  {
    lpDIS->itemState |= ODS_SELECTED;
  }

  if(bIsMenuBar && (lpDIS->itemState&ODS_SELECTED) )
  {
    if(!(lpDIS->itemState&ODS_INACTIVE) )
    {
      SetLastMenuRect(lpDIS->hDC,RectSel);
      if(!(lpDIS->itemState&ODS_HOTLIGHT) )
      { 
        // Create a new pen for the special color
        Pen.DeleteObject();
        colorBorder = bHighContrast?GetSysColor(COLOR_BTNTEXT):DarkenColor(128,GetMenuBarColor());
        Pen.CreatePen(PS_SOLID,0,colorBorder);

        int X,Y;
        CRect rect = RectR;
        int winH = rect.Height(); 

        // Simulate a shadow on right edge... 
        if (NumScreenColors() <= 256) 
        {
          DWORD clr = GetSysColor(COLOR_BTNSHADOW);
          for (X=3; X<=4 ;X++)
          { 
            for (Y=4; Y<8 ;Y++)
            {
              pDC->SetPixel(rect.right-X,Y+rect.top,clr) ;
            }
            for (Y=8; Y<=(winH-1) ;Y++)
            {
              pDC->SetPixel(rect.right - X, Y+rect.top, clr );
            }
          }
        }
        else
        {
          for (X=1; X<=4 ;X++)
          { 
            for (Y=0; Y<4 ;Y++)
            {
              pDC->SetPixel(rect.right-X,Y+rect.top, colorMenuBar );
            }
            for (Y=4; Y<8 ;Y++)
            {
              pDC->SetPixel(rect.right-X,Y+rect.top,DarkenColor(2* 3 * X * (Y - 3), colorMenuBar)) ;
            }
            for (Y=8; Y<=(winH-1) ;Y++)
            {
              pDC->SetPixel(rect.right - X, Y+rect.top, DarkenColor(2*15 * X, colorMenuBar) );
            }
          }
        }
      }
    }
  }
  // For keyboard navigation only
  BOOL bDrawSmallSelection = FALSE;
  // remove the selected bit if it's grayed out
  if( (lpDIS->itemState&ODS_GRAYED) && !m_bSelectDisable)
  {
    if( lpDIS->itemState & ODS_SELECTED )
    {
      lpDIS->itemState = lpDIS->itemState & (~ODS_SELECTED);
      DWORD MsgPos = ::GetMessagePos();
      if( MsgPos==CNewMenuHook::m_dwMsgPos )
      {
        bDrawSmallSelection = TRUE;
      }
      else
      {
        CNewMenuHook::m_dwMsgPos = MsgPos;
      }
    }
  }

  // Draw the seperator
  if( state & MF_SEPARATOR )
  {
    if( pMenuData->m_nTitleFlags&MFT_TITLE )
    {
      DrawTitle(lpDIS,bIsMenuBar);
    }
    else
    {
      // Draw only the seperator
      CRect rect;
      rect.top = RectR.CenterPoint().y;
      rect.bottom = rect.top+1;
      rect.right = lpDIS->rcItem.right;
      rect.left = RectR.left;
      pDC->FillSolidRect(rect,GetSysColor(COLOR_GRAYTEXT));
    }
  }
  else
  {
    if( (lpDIS->itemState & ODS_SELECTED) && !(lpDIS->itemState&ODS_INACTIVE) )
    {
      pDC->FillSolidRect(RectSel,colorSel);
      // Draw the selection
      CPen* pOldPen = pDC->SelectObject(&Pen);
      CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);
      pDC->Rectangle(RectSel);
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
    }
    else if (bDrawSmallSelection)
    {
      pDC->FillSolidRect(RectSel,colorMenu);
      // Draw the selection for keyboardnavigation
      CPen* pOldPen = pDC->SelectObject(&Pen);
      CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);
      pDC->Rectangle(RectSel);
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
    }

    UINT state = lpDIS->itemState;

    BOOL standardflag=FALSE;
    BOOL selectedflag=FALSE;
    BOOL disableflag=FALSE;
    BOOL checkflag=FALSE;

    CString strText = pMenuData->GetString();

    if( (state&ODS_CHECKED) && (pMenuData->m_nMenuIconOffset<0) )
    {
      if(state&ODS_SELECTED && m_selectcheck>0)
      {
        checkflag=TRUE;
      }
      else if(m_unselectcheck>0)
      {
        checkflag=TRUE;
      }
    }
    else if(pMenuData->m_nMenuIconOffset != -1)
    {
      standardflag=TRUE;
      if(state&ODS_SELECTED)
      {
        selectedflag=TRUE;
      }
      else if(state&ODS_GRAYED) 
      {
        disableflag=TRUE;
      }
    }

    // draw the menutext
    if(!strText.IsEmpty())
    {
      LOGFONT logFontMenu;
      CFont fontMenu;

      #ifdef _NEW_MENU_USER_FONT
        logFontMenu = MENU_USER_FONT;
      #else
      NONCLIENTMETRICS nm = {0};
        nm.cbSize = sizeof (nm);
        VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
        logFontMenu =  nm.lfMenuFont;
      #endif

      // Default selection?
      if(state&ODS_DEFAULT)
      {
        // Make the font bold
        logFontMenu.lfWeight = FW_BOLD;
      }
      fontMenu.CreateFontIndirect(&logFontMenu);

      CString leftStr;
      CString rightStr;
      leftStr.Empty();
      rightStr.Empty();

      int tablocr=strText.ReverseFind(_T('\t'));
      if(tablocr!=-1)
      {
        rightStr=strText.Mid(tablocr+1);
        leftStr=strText.Left(strText.Find(_T('\t')));
      }
      else
      {
        leftStr = strText;
      }

      // Draw the text in the correct color:
      UINT nFormat  = DT_LEFT| DT_SINGLELINE|DT_VCENTER;
      UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;

      int iOldMode = pDC->SetBkMode( TRANSPARENT);
      CFont* pOldFont = pDC->SelectObject (&fontMenu);

      COLORREF OldTextColor;
      if( (lpDIS->itemState&ODS_GRAYED) || 
          (bIsMenuBar && lpDIS->itemState&ODS_INACTIVE) )
      {
        // Draw the text disabled? 
        OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
      }
      else
      {
        // Draw the text normal
        if( bHighContrast && !bIsMenuBar && !(state&ODS_SELECTED) )
        {
          OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
        }
        else
        {
          OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_MENUTEXT));
        }
      }
      if(bIsMenuBar)
      {
        pDC->DrawText(leftStr,RectSel, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
      }
      else
      {
        pDC->DrawText(leftStr,RectR, nFormat);
        if(tablocr!=-1)
        {
          pDC->DrawText (rightStr,RectR,nFormatr);
        }
      }
      pDC->SetTextColor(OldTextColor);
      pDC->SelectObject(pOldFont);
      pDC->SetBkMode(iOldMode);
    }

    // Draw the bitmap or checkmarks
    if(!bIsMenuBar)
    {
      CRect rect2 = RectR;

      if(checkflag||standardflag||selectedflag||disableflag)
      {
        if(checkflag && m_checkmaps)
        {
          CPoint ptImage(RectL.left+3,RectL.top+4);

          if(state&ODS_SELECTED)
          {
            m_checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
          }
          else
          {
            m_checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
          }
        }
        else
        {
          CSize size = pMenuData->m_pMenuIcon->GetIconSize(); 
          HICON hDrawIcon = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset);
          //CPoint ptImage(RectL.left+3,RectL.top+ 4);
          CPoint ptImage( RectL.left+3, RectL.top + ((RectL.Height()-size.cy)>>1) );

          // Need to draw the checked state
          if (state&ODS_CHECKED)
          {
            CRect rect = RectL;
            rect.InflateRect (-1,-1,-2,-1);
            if(selectedflag)
            {
              if (NumScreenColors() > 256)
              {
                pDC->FillSolidRect(rect,MixedColor(colorSel,GetSysColor(COLOR_HIGHLIGHT)));
              }
              else
              {
                pDC->FillSolidRect(rect,colorSel); //GetSysColor(COLOR_HIGHLIGHT)
              }
            }
            else
            {
              pDC->FillSolidRect(rect,MixedColor(colorBitmap,GetSysColor(COLOR_HIGHLIGHT)));
            }

            CPen* pOldPen = pDC->SelectObject(&Pen);
            CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);

            pDC->Rectangle(rect);

            pDC->SelectObject(pOldBrush);
            pDC->SelectObject(pOldPen);
          } 

          // Correcting of a smaler icon
          if(size.cx<m_iconX)
          {
            ptImage.x += (m_iconX-size.cx)>>1;
          }

          if(state & ODS_DISABLED)
          {
            if(m_bEnableXpBlending)
            {
              // draws the icon blended
              HICON hDrawIcon2 = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset+2);
              pDC->DrawState(ptImage, size, hDrawIcon2, DSS_NORMAL,(HBRUSH)NULL);
              DestroyIcon(hDrawIcon2);
            }
            else
            {
              CBrush Brush;
              Brush.CreateSolidBrush(pDC->GetNearestColor(DarkenColor(70,colorBitmap)));
              pDC->DrawState(ptImage, size, hDrawIcon, DSS_MONO, &Brush);
            }
          }
          else
          {
            if(selectedflag)
            {
              CBrush Brush;
              // Color of the shade
              Brush.CreateSolidBrush(pDC->GetNearestColor(DarkenColorXP(colorSel)));
              if(!(state & ODS_CHECKED))
              {
                ptImage.x++; ptImage.y++;
                pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL | DSS_MONO, &Brush);
                ptImage.x-=2; ptImage.y-=2;
              }
              pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL,(HBRUSH)NULL);
            }
            else
            { 
              if(m_bEnableXpBlending)
              {
                // draws the icon blended
                HICON hDrawIcon2 = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset+1);
                pDC->DrawState(ptImage, size, hDrawIcon2, DSS_NORMAL,(HBRUSH)NULL);
                DestroyIcon(hDrawIcon2);
              }
              else
              {
                // draws the icon with normal color
                pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL,(HBRUSH)NULL);
              }
            }    
          }
          DestroyIcon(hDrawIcon);
        }
      }

      if(pMenuData->m_nMenuIconOffset<0 /*&& state&ODS_CHECKED */ && !checkflag)
      {
        MENUITEMINFO info = {0};
        info.cbSize = sizeof(info);
        info.fMask = MIIM_CHECKMARKS;

        ::GetMenuItemInfo(HWndToHMenu(lpDIS->hwndItem),lpDIS->itemID,MF_BYCOMMAND, &info);

        if(state&ODS_CHECKED || info.hbmpUnchecked) 
        {
          CRect rect = RectL;
          rect.InflateRect (-1,-1,-2,-1);
          // draw the color behind checkmarks
          if(state&ODS_SELECTED)
          {
            if (NumScreenColors() > 256)
            {
              pDC->FillSolidRect(rect,MixedColor(colorSel,GetSysColor(COLOR_HIGHLIGHT)));
            }
            else
            {
              pDC->FillSolidRect(rect,colorSel);
            }
          }
          else
          {
            pDC->FillSolidRect(rect,MixedColor(colorBitmap,GetSysColor(COLOR_HIGHLIGHT)));
          }
          CPen* pOldPen = pDC->SelectObject(&Pen);
          CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);

          pDC->Rectangle(rect);

          pDC->SelectObject(pOldBrush);
          pDC->SelectObject(pOldPen);
          if (state&ODS_CHECKED)
          {
            CRect rect(RectL);
            rect.InflateRect(2,((m_iconY-RectL.Height())>>1)+2);

            if (!info.hbmpChecked)
            { // Checkmark
              DrawSpecialCharStyle(pDC,rect,98,state);
            }
            else if(!info.hbmpUnchecked)
            { // Bullet
              DrawSpecialCharStyle(pDC,rect,105,state);
            }
            else
            { // Draw Bitmap
              BITMAP myInfo = {0};
              GetObject((HGDIOBJ)info.hbmpChecked,sizeof(myInfo),&myInfo);
              CPoint Offset = RectL.TopLeft() + CPoint((RectL.Width()-myInfo.bmWidth)/2,(RectL.Height()-myInfo.bmHeight)/2);
              pDC->DrawState(Offset,CSize(0,0),info.hbmpChecked,DST_BITMAP|DSS_MONO);
            }
          }
          else if(info.hbmpUnchecked) //BPO
          {
            // Draw Bitmap
            BITMAP myInfo = {0};
            GetObject((HGDIOBJ)info.hbmpUnchecked,sizeof(myInfo),&myInfo);
            CPoint Offset = RectL.TopLeft() + CPoint((RectL.Width()-myInfo.bmWidth)/2,(RectL.Height()-myInfo.bmHeight)/2);
            if(state & ODS_DISABLED)
            {
              pDC->DrawState(Offset,CSize(0,0),info.hbmpUnchecked,DST_BITMAP|DSS_MONO|DSS_DISABLED);
            }
            else
            {
              pDC->DrawState(Offset,CSize(0,0),info.hbmpUnchecked,DST_BITMAP|DSS_MONO);
            }   
          }
        }
        else if ((lpDIS->itemID&0xffff)>=SC_SIZE && (lpDIS->itemID&0xffff)<=SC_HOTKEY )
        {
          DrawSpecial_WinXP(pDC,RectL,lpDIS->itemID,state);
        }
      }
    }
  }
}

void CNewMenu::DrawItem_XP_2003(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  #ifdef _TRACE_MENU_
    AfxTrace(_T("BarState: 0x%lX MenuID 0x%lX\n"),lpDIS->itemState,lpDIS->itemID);
  #endif
  ASSERT(lpDIS != NULL);

  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);
  ASSERT(pMenuData);

  UINT state = pMenuData->m_nFlags;

  CNewMemDC memDC(&lpDIS->rcItem,lpDIS->hDC);
  CDC* pDC;
  if( bIsMenuBar || (state&MF_SEPARATOR) )
  { // For title and menubardrawing disable memory painting
    memDC.DoCancel();
    pDC = CDC::FromHandle(lpDIS->hDC);
  }
  else
  { 
    pDC = &memDC;
  }

  COLORREF colorWindow = DarkenColor(10,GetSysColor(COLOR_WINDOW));
  COLORREF colorMenuBar = bIsMenuBar?GetMenuBarColor():GetMenuColor();
  COLORREF colorMenu = MixedColor(colorWindow,colorMenuBar);
  COLORREF colorBitmap = MixedColor(GetMenuBarColor(),colorWindow);
  COLORREF colorSel = GetXpHighlightColor();
  COLORREF colorBorder = GetSysColor(COLOR_HIGHLIGHT);//DarkenColor(128,colorMenuBar);
  
  //COLORREF colorCaption = GetSysColor(COLOR_ACTIVECAPTION); //RGB(0,84,227);
  //COLORREF cc1 = MixedColor(colorWindow,colorCaption);
  //COLORREF cc2 = MidColor(colorWindow,colorCaption);

  COLORREF colorCheck    = RGB(255,192,111);
  COLORREF colorCheckSel = RGB(254,128,62);
  colorSel = RGB(255,238,194);
  colorBitmap = colorMenuBar = GetMenuBarColor2003();

  if(bHighContrast)
  {
    colorBorder = GetSysColor(COLOR_BTNTEXT);
  }

  // Better contrast when you have less than 256 colors
  if(pDC->GetNearestColor(colorMenu)==pDC->GetNearestColor(colorBitmap))
  {
    colorMenu = colorWindow;
    colorBitmap = colorMenuBar;
  }

  CPen Pen(PS_SOLID,0,colorBorder);

  if(bIsMenuBar)
  {
    if(!m_dwOpenMenu && lpDIS->itemState&ODS_SELECTED)
    {
      lpDIS->itemState = (lpDIS->itemState&~ODS_SELECTED)|ODS_HOTLIGHT;
    }
    if(!(lpDIS->itemState&ODS_HOTLIGHT))
    { 
      colorSel = colorBitmap;
    }
    colorMenu = colorMenuBar;
  }

  CBrush m_brSel(colorSel);
  CBrush m_brBitmap(colorBitmap);

  CRect RectL(lpDIS->rcItem);
  CRect RectR(lpDIS->rcItem);
  CRect RectSel(lpDIS->rcItem);

  if(bIsMenuBar)
  {
    RectR.InflateRect (0,0,0,0);
    RectSel.InflateRect (0,0,-2 -2,0); 

    if(lpDIS->itemState&ODS_SELECTED)
    {
      RectR.right -=4;
      if(NumScreenColors() <= 256)
      {
        pDC->FillSolidRect(RectR,colorMenu);
      }
      else
      {
        DrawGradient(pDC,RectR,colorMenu,colorBitmap,FALSE,TRUE);
      }
      RectR.right +=4;
    }
    else
    {
      MENUINFO menuInfo = {0};
      menuInfo.cbSize = sizeof(menuInfo);
      menuInfo.fMask = MIM_BACKGROUND;

      if(::GetMenuInfo(m_hMenu,&menuInfo) && menuInfo.hbrBack)
      {
        CBrush *pBrush = CBrush::FromHandle(menuInfo.hbrBack);
        VERIFY(pBrush->UnrealizeObject());
        CPoint oldOrg = pDC->SetBrushOrg(0,0);
        pDC->FillRect(RectR,pBrush);
        pDC->SetBrushOrg(oldOrg);
      }
      else
      {
        pDC->FillSolidRect(RectR,colorMenu); 
      }
    }
  }  
  else
  {
    RectL.right = RectL.left + m_iconX + 8;
    RectR.left  = RectL.right;
    // Draw for Bitmapbackground
    DrawGradient(pDC,RectL,colorMenu,colorBitmap,TRUE);
    // Draw for Textbackground
    pDC->FillSolidRect(RectR,colorMenu);
  }

  // Spacing for submenu only in popups
  if(!bIsMenuBar)
  {
    RectR.left += 4;
    RectR.right -= 15;
  }

  //  Flag for highlighted item
  if(lpDIS->itemState & (ODS_HOTLIGHT|ODS_INACTIVE) )
  {
    lpDIS->itemState |= ODS_SELECTED;
  }

  if(bIsMenuBar && (lpDIS->itemState&ODS_SELECTED) )
  {
    if(!(lpDIS->itemState&ODS_INACTIVE) )
    {
      SetLastMenuRect(lpDIS->hDC,RectSel);
      if(!(lpDIS->itemState&ODS_HOTLIGHT) )
      { 
        // Create a new pen for the special color
        Pen.DeleteObject();
        colorBorder = bHighContrast?GetSysColor(COLOR_BTNTEXT):DarkenColor(128,GetMenuBarColor());
        Pen.CreatePen(PS_SOLID,0,colorBorder);

        int X,Y;
        CRect rect = RectR;
        int winH = rect.Height(); 

        // Simulate a shadow on right edge... 
        if (NumScreenColors() <= 256) 
        {
          DWORD clr = GetSysColor(COLOR_BTNSHADOW);
          for (X=3; X<=4 ;X++)
          { 
            for (Y=4; Y<8 ;Y++)
            {
              pDC->SetPixel(rect.right-X,Y+rect.top,clr) ;
            }
            for (Y=8; Y<=(winH-1) ;Y++)
            {
              pDC->SetPixel(rect.right - X, Y+rect.top, clr );
            }
          }
        }
        else
        {
          COLORREF barColor = pDC->GetPixel(rect.right,rect.top);
          for (X=1; X<=4 ;X++)
          { 
            for (Y=0; Y<4 ;Y++)
            {
              pDC->SetPixel(rect.right-X,Y+rect.top, barColor );
            }
            for (Y=4; Y<8 ;Y++)
            {
              pDC->SetPixel(rect.right-X,Y+rect.top,DarkenColor(2* 3 * X * (Y - 3), barColor)) ;
            }
            for (Y=8; Y<=(winH-1) ;Y++)
            {
              pDC->SetPixel(rect.right - X, Y+rect.top, DarkenColor(2*15 * X, barColor) );
            }
          }
        }
      }
    }
  }
  // For keyboard navigation only
  BOOL bDrawSmallSelection = FALSE;
  // remove the selected bit if it's grayed out
  if( (lpDIS->itemState&ODS_GRAYED) && !m_bSelectDisable)
  {
    if( lpDIS->itemState & ODS_SELECTED )
    {
      lpDIS->itemState = lpDIS->itemState & (~ODS_SELECTED);
      DWORD MsgPos = ::GetMessagePos();
      if( MsgPos==CNewMenuHook::m_dwMsgPos )
      {
        bDrawSmallSelection = TRUE;
      }
      else
      {
        CNewMenuHook::m_dwMsgPos = MsgPos;
      }
    }
  }

  // Draw the seperator
  if( state & MF_SEPARATOR )
  {
    if( pMenuData->m_nTitleFlags&MFT_TITLE )
    {
      DrawTitle(lpDIS,bIsMenuBar);
    }
    else
    {
      // Draw only the seperator
      CRect rect;
      rect.top = RectR.CenterPoint().y;
      rect.bottom = rect.top+1;
      rect.right = lpDIS->rcItem.right;
      rect.left = RectR.left;
      pDC->FillSolidRect(rect,GetSysColor(COLOR_GRAYTEXT));
    }
  }
  else
  {
    if( (lpDIS->itemState & ODS_SELECTED) && !(lpDIS->itemState&ODS_INACTIVE) )
    {
      if(bIsMenuBar)
      {
        if(NumScreenColors() <= 256)
        {
          pDC->FillSolidRect(RectSel,colorWindow);
        }
        else
        {
          DrawGradient(pDC,RectSel,colorWindow,colorSel,FALSE,TRUE);
        }
      }
      else
      {
        pDC->FillSolidRect(RectSel,colorSel);
      } 
      // Draw the selection
      CPen* pOldPen = pDC->SelectObject(&Pen);
      CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);
      pDC->Rectangle(RectSel);
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
    }
    else if (bDrawSmallSelection)
    {
      pDC->FillSolidRect(RectSel,colorMenu);
      // Draw the selection for keyboardnavigation
      CPen* pOldPen = pDC->SelectObject(&Pen);
      CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);
      pDC->Rectangle(RectSel);
      pDC->SelectObject(pOldBrush);
      pDC->SelectObject(pOldPen);
    }

    UINT state = lpDIS->itemState;

    BOOL standardflag=FALSE;
    BOOL selectedflag=FALSE;
    BOOL disableflag=FALSE;
    BOOL checkflag=FALSE;

    CString strText = pMenuData->GetString();

    if( (state&ODS_CHECKED) && (pMenuData->m_nMenuIconOffset<0) )
    {
      if(state&ODS_SELECTED && m_selectcheck>0)
      {
        checkflag=TRUE;
      }
      else if(m_unselectcheck>0)
      {
        checkflag=TRUE;
      }
    }
    else if(pMenuData->m_nMenuIconOffset != -1)
    {
      standardflag = TRUE;
      if(state&ODS_SELECTED)
      {
        selectedflag=TRUE;
      }
      else if(state&ODS_GRAYED) 
      {
        disableflag=TRUE;
      }
    }

    // draw the menutext
    if(!strText.IsEmpty())
    {
      LOGFONT logFontMenu;
      CFont fontMenu;

      #ifdef _NEW_MENU_USER_FONT
        logFontMenu = MENU_USER_FONT;
      #else
        NONCLIENTMETRICS nm = {0};
        nm.cbSize = sizeof (nm);
        VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
        logFontMenu = nm.lfMenuFont;
      #endif

      // Default selection?
      if(state&ODS_DEFAULT)
      {
        // Make the font bold
        logFontMenu.lfWeight = FW_BOLD;
      }
      fontMenu.CreateFontIndirect(&logFontMenu);

      CString leftStr;
      CString rightStr;
      leftStr.Empty();
      rightStr.Empty();

      int tablocr = strText.ReverseFind(_T('\t'));
      if(tablocr!=-1)
      {
        rightStr = strText.Mid(tablocr+1);
        leftStr = strText.Left(strText.Find(_T('\t')));
      }
      else
      {
        leftStr=strText;
      }

      // Draw the text in the correct color:
      UINT nFormat  = DT_LEFT| DT_SINGLELINE|DT_VCENTER;
      UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;

      int iOldMode = pDC->SetBkMode( TRANSPARENT);
      CFont* pOldFont = pDC->SelectObject (&fontMenu);

      COLORREF OldTextColor;
      if( (lpDIS->itemState&ODS_GRAYED) || 
          (bIsMenuBar && lpDIS->itemState&ODS_INACTIVE) )
      {
        // Draw the text disabled? 
        if(bIsMenuBar && (NumScreenColors() <= 256) )
        {
          OldTextColor = pDC->SetTextColor(colorWindow);
        }
        else
        {
          OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
        }
      }
      else
      {
        // Draw the text normal
        if( bHighContrast && !bIsMenuBar && !(state&ODS_SELECTED) )
        {
          OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
        }
        else
        {
          OldTextColor = pDC->SetTextColor(GetSysColor(COLOR_MENUTEXT));
        }
      }
      if(bIsMenuBar)
      {
        pDC->DrawText(leftStr,RectSel, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
      }
      else
      {
        pDC->DrawText(leftStr,RectR, nFormat);
        if(tablocr!=-1)
        {
          pDC->DrawText (rightStr,RectR,nFormatr);
        }
      }
      pDC->SetTextColor(OldTextColor);
      pDC->SelectObject(pOldFont);
      pDC->SetBkMode(iOldMode);
    }

    // Draw the bitmap or checkmarks
    if(!bIsMenuBar)
    {
      CRect rect2 = RectR;

      if(checkflag||standardflag||selectedflag||disableflag)
      {
        if(checkflag && m_checkmaps)
        {
          CPoint ptImage(RectL.left+3,RectL.top+4);

          if(state&ODS_SELECTED)
          {
            m_checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
          }
          else
          {
            m_checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
          }
        }
        else
        {
          CSize size = pMenuData->m_pMenuIcon->GetIconSize(); 
          HICON hDrawIcon = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset);
          //CPoint ptImage(RectL.left+3,RectL.top+ 4);
          CPoint ptImage( RectL.left+3, RectL.top + ((RectL.Height()-size.cy)>>1) );

          // Need to draw the checked state
          if (state&ODS_CHECKED)
          {
            CRect rect = RectL;
            rect.InflateRect (-1,-1,-2,-1);
            if(selectedflag)
            {
              pDC->FillSolidRect(rect,colorCheckSel);
            }
            else
            {
              pDC->FillSolidRect(rect,colorCheck);
            }

            CPen* pOldPen = pDC->SelectObject(&Pen);
            CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);

            pDC->Rectangle(rect);

            pDC->SelectObject(pOldBrush);
            pDC->SelectObject(pOldPen);
          } 

          // Correcting of a smaler icon
          if(size.cx<m_iconX)
          {
            ptImage.x += (m_iconX-size.cx)>>1;
          }

          if(state & ODS_DISABLED)
          {
            if(m_bEnableXpBlending)
            {
              // draws the icon blended
              HICON hDrawIcon2 = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset+2);
              pDC->DrawState(ptImage, size, hDrawIcon2, DSS_NORMAL,(HBRUSH)NULL);
              DestroyIcon(hDrawIcon2);
            }
            else
            {
              CBrush Brush;
              Brush.CreateSolidBrush(pDC->GetNearestColor(DarkenColor(70,colorBitmap)));
              pDC->DrawState(ptImage, size, hDrawIcon, DSS_MONO, &Brush);
            }
          }
          else
          {
            if(selectedflag)
            {
              CBrush Brush;
              // Color of the shade
              Brush.CreateSolidBrush(pDC->GetNearestColor(DarkenColorXP(colorSel)));
              if(!(state & ODS_CHECKED))
              {
                ptImage.x++; ptImage.y++;
                pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL | DSS_MONO, &Brush);
                ptImage.x-=2; ptImage.y-=2;
              }
              pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL,(HBRUSH)NULL);
            }
            else
            { 
              if(m_bEnableXpBlending)
              {
                // draws the icon blended
                HICON hDrawIcon2 = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset+1);
                pDC->DrawState(ptImage, size, hDrawIcon2, DSS_NORMAL,(HBRUSH)NULL);
                DestroyIcon(hDrawIcon2);
              }
              else
              {
                // draws the icon with normal color
                pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL,(HBRUSH)NULL);
                //ImageList_DrawEx(pMenuData->m_pMenuIcon->m_IconsList,pMenuData->m_nMenuIconOffset,pDC->GetSafeHdc(),ptImage.x,ptImage.y,0,0,CLR_DEFAULT,CLR_DEFAULT,ILD_NORMAL);
              }
            }    
          }
          DestroyIcon(hDrawIcon);
        }
      }

      if(pMenuData->m_nMenuIconOffset<0 /*&& state&ODS_CHECKED */ && !checkflag)
      {
        MENUITEMINFO info = {0};
        info.cbSize = sizeof(info);
        info.fMask = MIIM_CHECKMARKS;

        ::GetMenuItemInfo(HWndToHMenu(lpDIS->hwndItem),lpDIS->itemID,MF_BYCOMMAND, &info);

        if(state&ODS_CHECKED || info.hbmpUnchecked) 
        {
          CRect rect = RectL;
          rect.InflateRect (-1,-1,-2,-1);
          // draw the color behind checkmarks
          if(state&ODS_SELECTED)
          {
            pDC->FillSolidRect(rect,colorCheckSel);
          }
          else
          {
            pDC->FillSolidRect(rect,colorCheck);
          }
          CPen* pOldPen = pDC->SelectObject(&Pen);
          CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(HOLLOW_BRUSH);

          pDC->Rectangle(rect);

          pDC->SelectObject(pOldBrush);
          pDC->SelectObject(pOldPen);
          if (state&ODS_CHECKED)
          {
            CRect rect(RectL);
            rect.InflateRect(2,((m_iconY-RectL.Height())>>1)+2);

            if (!info.hbmpChecked)
            { // Checkmark
              DrawSpecialCharStyle(pDC,rect,98,state);
            }
            else if(!info.hbmpUnchecked)
            { // Bullet
              DrawSpecialCharStyle(pDC,rect,105,state);
            }
            else
            { // Draw Bitmap
              BITMAP myInfo = {0};
              GetObject((HGDIOBJ)info.hbmpChecked,sizeof(myInfo),&myInfo);
              CPoint Offset = RectL.TopLeft() + CPoint((RectL.Width()-myInfo.bmWidth)/2,(RectL.Height()-myInfo.bmHeight)/2);
              pDC->DrawState(Offset,CSize(0,0),info.hbmpChecked,DST_BITMAP|DSS_MONO);
            }
          }
          else
          {
            // Draw Bitmap
            BITMAP myInfo = {0};
            GetObject((HGDIOBJ)info.hbmpUnchecked,sizeof(myInfo),&myInfo);
            CPoint Offset = RectL.TopLeft() + CPoint((RectL.Width()-myInfo.bmWidth)/2,(RectL.Height()-myInfo.bmHeight)/2);
            if(state & ODS_DISABLED)
            {
              pDC->DrawState(Offset,CSize(0,0),info.hbmpUnchecked,DST_BITMAP|DSS_MONO|DSS_DISABLED);
            }
            else
            {
              pDC->DrawState(Offset,CSize(0,0),info.hbmpUnchecked,DST_BITMAP|DSS_MONO);
            }   
          }
        }
        else if ((lpDIS->itemID&0xffff)>=SC_SIZE && (lpDIS->itemID&0xffff)<=SC_HOTKEY )
        {
          DrawSpecial_WinXP(pDC,RectL,lpDIS->itemID,state);
        }
      }
    }
  }
}

void CNewMenu::DrawItem_SpecialStyle (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  if(!bIsMenuBar)
  {
    DrawItem_OldStyle(lpDIS,bIsMenuBar);
    return;
  }

  ASSERT(lpDIS != NULL);
  //CNewMemDC memDC(&lpDIS->rcItem,lpDIS->hDC);
  //CDC* pDC = &memDC;
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);

  ASSERT(lpDIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);

  CRect rect(lpDIS->rcItem);
  //rect.InflateRect(0,-1);

  COLORREF colorBack;
  if(lpDIS->itemState&(ODS_SELECTED|ODS_HOTLIGHT))
  {
    colorBack = GetSysColor(COLOR_HIGHLIGHT);
    SetLastMenuRect(lpDIS->hDC,rect);
  }
  else
  {
    colorBack = GetMenuBarColor();
  }
  pDC->FillSolidRect(rect,colorBack);

  int iOldMode = pDC->SetBkMode( TRANSPARENT);
  CString strText = pMenuData->GetString();
  COLORREF crTextColor;
  if(!(lpDIS->itemState & ODS_GRAYED))
  {
    if(lpDIS->itemState&(ODS_SELECTED|ODS_HOTLIGHT))
    {
      crTextColor = GetSysColor(COLOR_HIGHLIGHTTEXT);
    }
    else
    {
      crTextColor = GetSysColor(COLOR_MENUTEXT);
    }
  }
  else
  {
    crTextColor = GetSysColor(COLOR_GRAYTEXT);
  }
  COLORREF oldColor = pDC->SetTextColor(crTextColor);
  
  CFont fontMenu;
  LOGFONT logFontMenu;

  #ifdef _NEW_MENU_USER_FONT
    logFontMenu =  MENU_USER_FONT;
  #else
    NONCLIENTMETRICS nm = {0};
    nm.cbSize = sizeof (nm);
    VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
    logFontMenu =  nm.lfMenuFont;
  #endif
  fontMenu.CreateFontIndirect (&logFontMenu);
  
  CFont* pOldFont = pDC->SelectObject(&fontMenu);
  pDC->DrawText(strText,rect,DT_CENTER|DT_SINGLELINE|DT_VCENTER);  
  pDC->SelectObject(pOldFont);

  pDC->SetTextColor(oldColor);
  pDC->SetBkMode( iOldMode);
}

void CNewMenu::DrawItem_Icy(LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  ASSERT(lpDIS != NULL);
  CRect rect;

  ASSERT(lpDIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);

  UINT state = pMenuData->m_nFlags;
 
  CNewMemDC memDC(&lpDIS->rcItem,lpDIS->hDC);
  CDC* pDC;
  if( bIsMenuBar || (state&MF_SEPARATOR) )
  { // For title and menubardrawing disable memory painting
    memDC.DoCancel();
    pDC = CDC::FromHandle(lpDIS->hDC);
  }
  else
  { 
    pDC = &memDC;
  }

  COLORREF colorMenu = GetMenuColor();
  COLORREF colorBack = bIsMenuBar?GetMenuBarColor():colorMenu;
  COLORREF color3DShadow = DarkenColor(60,colorMenu);
  COLORREF color3DHilight = LightenColor(60,colorMenu);
  COLORREF colorGrayText = DarkenColor(100,colorMenu);//GetSysColor(COLOR_GRAYTEXT);
  COLORREF colorHilight = GetSysColor(COLOR_HIGHLIGHT);
  COLORREF colorGrayed = bHighContrast?GetSysColor(COLOR_BTNSHADOW):pDC->GetNearestColor(DarkenColor(70,color3DShadow)); 

  if(bHighContrast)
  { 
    color3DShadow = GetSysColor(COLOR_BTNTEXT);
    color3DHilight = GetSysColor(COLOR_BTNTEXT);
  }

  CRect RectL(lpDIS->rcItem);
  CRect RectR(lpDIS->rcItem);
  CRect RectSel(lpDIS->rcItem);

  RectL.InflateRect (-1,0,0,0);
  RectR.InflateRect (-1,0,0,0);
  RectSel.InflateRect (0,0,0,0);

  if(!bIsMenuBar)
  {
    RectL.right = RectL.left + m_iconX + 6 + GAP;
    RectR.left  = RectL.right;
  }
  else
  {
    if(!m_dwOpenMenu && lpDIS->itemState&ODS_SELECTED)
    {
      lpDIS->itemState = (lpDIS->itemState&~ODS_SELECTED)|ODS_HOTLIGHT;
    }

    RectSel.InflateRect(0,0,-1,-1);
    RectR.InflateRect (1,-2,0,0);

    if(lpDIS->itemState&(ODS_SELECTED|ODS_HOTLIGHT))
    {
      SetLastMenuRect(lpDIS->hDC,RectSel);
    }
  }

   // For keyboard navigation only
  BOOL bDrawSmallSelection = FALSE;

  // remove the selected bit if it's grayed out
  if( (lpDIS->itemState&ODS_GRAYED) && !m_bSelectDisable )
  {
    if(lpDIS->itemState & ODS_SELECTED)
    {
      lpDIS->itemState &= ~ODS_SELECTED;
      DWORD MsgPos = ::GetMessagePos();
      if(MsgPos==CNewMenuHook::m_dwMsgPos)
      {
        bDrawSmallSelection = TRUE;
      }
      else
      {
        CNewMenuHook::m_dwMsgPos = MsgPos;
      }
    }
  }

  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      DrawTitle(lpDIS,bIsMenuBar);
    }
    else
    {
      rect = lpDIS->rcItem; 
      //pDC->FillSolidRect(rect,colorBack);
      pDC->FillSolidRect(rect,color3DHilight);
      rect.left += 1;
      rect.right -= 1;
      pDC->DrawEdge(&rect,EDGE_ETCHED,BF_TOP); 
    }
  }
  else
  {
    CRect rect2;
    BOOL standardflag=FALSE,selectedflag=FALSE,disableflag=FALSE;
    BOOL checkflag=FALSE;

    CBrush m_brSelect;
    int nIconNormal=-1;

    // set some colors and the font
    m_brSelect.CreateSolidBrush(colorHilight);
    rect2=rect=RectSel;

    // draw the up/down/focused/disabled state
    UINT state = lpDIS->itemState;
    CString strText;

    nIconNormal = pMenuData->m_nMenuIconOffset;
    strText = pMenuData->GetString();

    if( (state&ODS_CHECKED) && nIconNormal<0)
    {
      if(state&ODS_SELECTED && m_selectcheck>0)
      {
        checkflag = TRUE;
      }
      else if(m_unselectcheck>0) 
      {
        checkflag = TRUE;
      }
    }
    else if(nIconNormal != -1)
    {
      standardflag = TRUE;
      if(state&ODS_SELECTED && !(state&ODS_GRAYED))
      {
        selectedflag=TRUE;
      }
      else if(state&ODS_GRAYED)
      {
        disableflag=TRUE;
      }
    }

    if(bIsMenuBar)
    {
      CRect tempRect = rect;
      tempRect.InflateRect (1,0,1,1);
      rect.OffsetRect(0,1);
      rect2=rect;

      if( bHighContrast || (state&ODS_INACTIVE) || (!(state&ODS_HOTLIGHT) && !(state&ODS_SELECTED)) )
      {
        // pDC->FillSolidRect(tempRect,colorBack);
        MENUINFO menuInfo = {0};
        menuInfo.cbSize = sizeof(menuInfo);
        menuInfo.fMask = MIM_BACKGROUND;

        if(!bHighContrast && ::GetMenuInfo(m_hMenu,&menuInfo) && menuInfo.hbrBack)
        {
          CBrush *pBrush = CBrush::FromHandle(menuInfo.hbrBack);
          VERIFY(pBrush->UnrealizeObject());
          CPoint oldOrg = pDC->SetBrushOrg(0,0);
          pDC->FillRect(tempRect,pBrush);
          pDC->SetBrushOrg(oldOrg);
        }
        else
        {
          pDC->FillSolidRect(tempRect,colorBack); 
        }
      }
      else
      {
        colorBack = GetMenuColor();
        DrawGradient(pDC,tempRect,LightenColor(30,colorBack),DarkenColor(30,colorBack),false,true);
      }
    }
    else
    {
      if(bHighContrast)
      {
        pDC->FillSolidRect (rect,colorBack);
      }
      else
      {
        DrawGradient(pDC,rect,LightenColor(30,colorBack),DarkenColor(30,colorBack),false,true);
      }
    }
    // Draw the selection
    if(state&ODS_SELECTED)
    {
      // You need only Text highlight and that's what you get
      if(!bIsMenuBar)
      {
        if(checkflag||standardflag||selectedflag||disableflag||state&ODS_CHECKED)
        {
          rect2.SetRect(rect.left+m_iconX+4+GAP,rect.top,rect.right,rect.bottom);
        }

        if(bHighContrast)
        {
          pDC->FillSolidRect (rect2,colorHilight);
        }
        else
        {
          DrawGradient(pDC,rect2,LightenColor(30,colorHilight),DarkenColor(30,colorHilight),false,true);
        }
        pDC->Draw3dRect(rect2 ,color3DShadow,color3DHilight);
      }
      else
      {
        pDC->Draw3dRect(rect2 ,color3DShadow,color3DHilight);
      }
    }
    else if(bIsMenuBar && (state&ODS_HOTLIGHT) && !(state&ODS_INACTIVE))
    {
      pDC->Draw3dRect(rect,color3DHilight,color3DShadow);
    }
    else if (bDrawSmallSelection)
    {
      pDC->DrawFocusRect(rect);
    }

    // Draw the Bitmap or checkmarks
    if(!bIsMenuBar)
    {
      CRect IconRect(rect.TopLeft(),CSize(m_iconX,m_iconY));
      IconRect.OffsetRect(GAP+1,((rect.Height()-m_iconY)>>1));

      CPoint ptImage = IconRect.TopLeft();

      IconRect.InflateRect(2,2);
      if(checkflag||standardflag||selectedflag||disableflag)
      {
        if(checkflag && m_checkmaps)
        {
          if(state&ODS_SELECTED)
          {
            m_checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
          }
          else
          {
            m_checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
          }
        }
        else
        {
          // Need to draw the checked state
          if (IsNewShell())
          {
            if(state&ODS_CHECKED)
            {
              pDC->Draw3dRect(IconRect,color3DShadow,color3DHilight);
            }
            else if (selectedflag)
            {
              pDC->Draw3dRect(IconRect,color3DHilight,color3DShadow);
            }
          }

          CSize size = pMenuData->m_pMenuIcon->GetIconSize(); 
          // Correcting of a smaler icon
          if(size.cx<m_iconX)
          {
            ptImage.x += (m_iconX-size.cx)>>1;
          }
          if(size.cy<m_iconY)
          {
            ptImage.y += (m_iconY-size.cy)>>1;
          }

          HICON hDrawIcon = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset);
          if(state & ODS_DISABLED)
          {
            CBrush Brush;
            Brush.CreateSolidBrush(colorGrayed); 
            pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL | DSS_MONO, (HBRUSH)Brush);
          }
          else
          {
            pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL, (HBRUSH)NULL);
          }
          DestroyIcon(hDrawIcon);
        }
      }
      if(nIconNormal<0 /*&& state&ODS_CHECKED */&& !checkflag)
      {
        MENUITEMINFO info = {0};
        info.cbSize = sizeof(info);
        info.fMask = MIIM_CHECKMARKS;

        ::GetMenuItemInfo(HWndToHMenu(lpDIS->hwndItem),lpDIS->itemID,MF_BYCOMMAND, &info);

        Draw3DCheckmark(pDC, IconRect,info.hbmpChecked,info.hbmpUnchecked,state);
      }
      else if ((lpDIS->itemID&0xffff)>=SC_SIZE && (lpDIS->itemID&0xffff)<=SC_HOTKEY )
      {
        DrawSpecial_OldStyle(pDC,IconRect,lpDIS->itemID,state);
      } 
    }

    if(!strText.IsEmpty())
    {
      COLORREF crText = GetSysColor(COLOR_MENUTEXT);

      if(bIsMenuBar)
      {
        rect.left += 6;
        if(lpDIS->itemState&ODS_INACTIVE)
        {
          crText = colorGrayText;
        }
      }
      else
      {
        if(lpDIS->itemState&ODS_SELECTED)
        {
          crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
        }
        rect.left += m_iconX + 12;
      }
      CRect rectt(rect.left,rect.top-1,rect.right,rect.bottom-1);

      // Find tabs
      CString leftStr,rightStr;
      leftStr.Empty();rightStr.Empty();

      int tablocr = strText.ReverseFind(_T('\t'));
      if(tablocr!=-1)
      {
        rightStr = strText.Mid(tablocr+1);
        leftStr = strText.Left(strText.Find(_T('\t')));
        rectt.right -= m_iconX;
      }
      else
      {
        leftStr = strText;
      }

      int iOldMode = pDC->SetBkMode( TRANSPARENT);
      // Draw the text in the correct colour:
      UINT nFormat  = DT_LEFT|DT_SINGLELINE|DT_VCENTER;
      UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;

      if(bIsMenuBar)
      {
        rectt = RectSel;
        rectt.OffsetRect(-1,0);
        if(state & ODS_SELECTED)
        {
          rectt.OffsetRect(1,1);
        } 
        nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
      }

      CFont fontMenu;
      LOGFONT logFontMenu;

      #ifdef _NEW_MENU_USER_FONT
        logFontMenu =  MENU_USER_FONT;
      #else
        NONCLIENTMETRICS nm = {0};
        nm.cbSize = sizeof (nm);
        VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
        logFontMenu =  nm.lfMenuFont;
      #endif

      // Default selection?
      if(state&ODS_DEFAULT)
      {
        // Make the font bold
        logFontMenu.lfWeight = FW_BOLD;
      }

      fontMenu.CreateFontIndirect (&logFontMenu);
      CFont* pOldFont = pDC->SelectObject(&fontMenu);

      if(!(lpDIS->itemState & ODS_GRAYED))
      {
        pDC->SetTextColor(crText);
        pDC->DrawText (leftStr,rectt,nFormat);
        if(tablocr!=-1)
        {
          pDC->DrawText (rightStr,rectt,nFormatr);
        }
      }
      else
      {
        // Draw the disabled text
        if(!(state & ODS_SELECTED))
        {
          CRect offset = rectt;
          offset.OffsetRect (1,1);

          pDC->SetTextColor(colorGrayed);
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1)
          {
            pDC->DrawText(rightStr,rectt,nFormatr);
          }
        }
        else
        {
          // And the standard Grey text:
          pDC->SetTextColor(colorBack);
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1)
          {
            pDC->DrawText (rightStr,rectt,nFormatr);
          }
        }
      }
      pDC->SelectObject(pOldFont);
      pDC->SetBkMode( iOldMode );
    }
    m_brSelect.DeleteObject();
  }
}

void CNewMenu::DrawItem_OldStyle (LPDRAWITEMSTRUCT lpDIS, BOOL bIsMenuBar)
{
  ASSERT(lpDIS != NULL);
  CRect rect;

  ASSERT(lpDIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpDIS->itemData);

  UINT state = pMenuData->m_nFlags;

  CNewMemDC memDC(&lpDIS->rcItem,lpDIS->hDC);
  CDC* pDC;
  if( bIsMenuBar || (state&MF_SEPARATOR) )
  { // For title and menubardrawing disable memory painting
    memDC.DoCancel();
    pDC = CDC::FromHandle(lpDIS->hDC);
  }
  else
  { 
    pDC = &memDC;
  }

  COLORREF colorBack = bIsMenuBar?GetMenuBarColor():GetSysColor(COLOR_MENU);

  CRect RectL(lpDIS->rcItem);
  CRect RectR(lpDIS->rcItem);
  CRect RectSel(lpDIS->rcItem);

  RectL.InflateRect (-1,0,0,0);
  RectR.InflateRect (-1,0,0,0);
  RectSel.InflateRect (0,0,0,0);

  if(!bIsMenuBar)
  {
    RectL.right = RectL.left + m_iconX + 6 + GAP;
    RectR.left  = RectL.right;
  }
  else
  {
#ifdef _TRACE_MENU_
 //   AfxTrace(_T("BarState: 0x%lX Menus %ld\n"),lpDIS->itemState,m_dwOpenMenu);
#endif
    if(!m_dwOpenMenu && lpDIS->itemState&ODS_SELECTED)
    {
      lpDIS->itemState = (lpDIS->itemState&~ODS_SELECTED)|ODS_HOTLIGHT;
    }

    RectR.InflateRect (1,0,0,0);
    RectSel.InflateRect (0,0,-2,0);
    RectSel.OffsetRect(1,-1);

    if(lpDIS->itemState&(ODS_SELECTED|ODS_HOTLIGHT))
    {
      SetLastMenuRect(lpDIS->hDC,RectSel);
    }
  }

   // For keyboard navigation only
  BOOL bDrawSmallSelection = FALSE;

  // remove the selected bit if it's grayed out
  if( (lpDIS->itemState&ODS_GRAYED) && !m_bSelectDisable )
  {
    if(lpDIS->itemState & ODS_SELECTED)
    {
      lpDIS->itemState &= ~ODS_SELECTED;
      DWORD MsgPos = ::GetMessagePos();
      if(MsgPos==CNewMenuHook::m_dwMsgPos)
      {
        bDrawSmallSelection = TRUE;
      }
      else
      {
        CNewMenuHook::m_dwMsgPos = MsgPos;
      }
    }
  }

  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      DrawTitle(lpDIS,bIsMenuBar);
    }
    else
    {
      rect = lpDIS->rcItem; 
      pDC->FillSolidRect(rect,colorBack);
      rect.left += 1;
      pDC->DrawEdge(&rect,EDGE_ETCHED,BF_TOP);
    }
  }
  else
  {
    CRect rect2;
    BOOL standardflag=FALSE,selectedflag=FALSE,disableflag=FALSE;
    BOOL checkflag=FALSE;

    CBrush m_brSelect;
    int nIconNormal=-1;
    //CImageList *bitmap=NULL;

    // set some colors and the font
    m_brSelect.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

    // draw the colored rectangle portion
    rect.CopyRect(&lpDIS->rcItem);
    rect.OffsetRect (1,1);
    rect2=rect=RectSel;

    // draw the up/down/focused/disabled state
    UINT state = lpDIS->itemState;
    CString strText;

    nIconNormal = pMenuData->m_nMenuIconOffset;
    strText = pMenuData->GetString();

    if( (state&ODS_CHECKED) && nIconNormal<0)
    {
      if(state&ODS_SELECTED && m_selectcheck>0)
      {
        checkflag = TRUE;
      }
      else if(m_unselectcheck>0)
      {
        checkflag = TRUE;
      }
    }
    else if(nIconNormal != -1)
    {
      standardflag=TRUE;
      if(state&ODS_SELECTED && !(state&ODS_GRAYED))
      {
        selectedflag = TRUE;
      }
      else if(state&ODS_GRAYED)
      {
        disableflag = TRUE;
      }
    }

    if(bIsMenuBar)
    {
      //rect.InflateRect (1,0,0,0);
      rect.OffsetRect(-1,1);
      rect2=rect;
      rect.right +=2;
      pDC->FillSolidRect (rect,colorBack);
      rect.right -=2;
    }
    else
    {
      // Draw the background
      pDC->FillSolidRect (rect,colorBack);
    }
    // Draw the selection
    if(state&ODS_SELECTED)
    {
      // You need only Text highlight and that's what you get
      if(!bIsMenuBar)
      {
        if(checkflag||standardflag||selectedflag||disableflag||state&ODS_CHECKED)
        {
          rect2.SetRect(rect.left+m_iconX+4+GAP,rect.top,rect.right,rect.bottom);
        }
        pDC->FillRect(rect2,&m_brSelect);
      }
      else
      {
        pDC->Draw3dRect(rect ,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
      }
    }
    else if(bIsMenuBar && (state&ODS_HOTLIGHT) && !(state&ODS_INACTIVE))
    {
      pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
    }
    else if (bDrawSmallSelection)
    {
      pDC->DrawFocusRect(rect);
    }

    // Draw the Bitmap or checkmarks
    if(!bIsMenuBar)
    {
      CRect IconRect(rect.TopLeft(),CSize(m_iconX,m_iconY));
      IconRect.OffsetRect(GAP+1,((rect.Height()-m_iconY)>>1));

      CPoint ptImage = IconRect.TopLeft();

      IconRect.InflateRect(2,2);
      if(checkflag||standardflag||selectedflag||disableflag)
      {
        if(checkflag && m_checkmaps)
        {
          if(state&ODS_SELECTED)
          {
            m_checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
          }
          else
          {
            m_checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
          }
        }
        else
        {
          // Need to draw the checked state
          if (IsNewShell())
          {
            if(state&ODS_CHECKED)
            {
              pDC->Draw3dRect(IconRect,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
            }
            else if (selectedflag)
            {
              pDC->Draw3dRect(IconRect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
            }
          }

          CSize size = pMenuData->m_pMenuIcon->GetIconSize(); 
          // Correcting of a smaler icon
          if(size.cx<m_iconX)
          {
            ptImage.x += (m_iconX-size.cx)>>1;
          }
          if(size.cy<m_iconY)
          {
            ptImage.y += (m_iconY-size.cy)>>1;
          }

          HICON hDrawIcon = pMenuData->m_pMenuIcon->m_IconsList.ExtractIcon(pMenuData->m_nMenuIconOffset);
          if(state & ODS_DISABLED)
          {
            pDC->DrawState(ptImage, size, hDrawIcon, DSS_DISABLED, (HBRUSH)NULL);
          }
          else
          {
            pDC->DrawState(ptImage, size, hDrawIcon, DSS_NORMAL, (HBRUSH)NULL);
          }
          DestroyIcon(hDrawIcon);
        }
      }
      if(nIconNormal<0 /*&& state&ODS_CHECKED */ && !checkflag)
      {
        MENUITEMINFO info = {0};
        info.cbSize = sizeof(info);
        info.fMask = MIIM_CHECKMARKS;

        ::GetMenuItemInfo(HWndToHMenu(lpDIS->hwndItem),lpDIS->itemID,MF_BYCOMMAND, &info);
        Draw3DCheckmark(pDC, IconRect,info.hbmpChecked,info.hbmpUnchecked,state);
      }
      else if ((lpDIS->itemID&0xffff)>=SC_SIZE && (lpDIS->itemID&0xffff)<=SC_HOTKEY )
      {
        DrawSpecial_OldStyle(pDC,IconRect,lpDIS->itemID,state);
      }
    }

    if(!strText.IsEmpty())
    {
      COLORREF crText = GetSysColor(COLOR_MENUTEXT);

      if(bIsMenuBar)
      {
        rect.left += 6;
        if(lpDIS->itemState&ODS_INACTIVE) 
          crText = GetSysColor(COLOR_GRAYTEXT);
      }
      else
      {
        if(lpDIS->itemState&ODS_SELECTED)
        {
          crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
        }

        rect.left += m_iconX + 12;
      }
      CRect rectt(rect.left,rect.top-1,rect.right,rect.bottom-1);

      // Find tabs
      CString leftStr,rightStr;
      leftStr.Empty();rightStr.Empty();

      int tablocr = strText.ReverseFind(_T('\t'));
      if(tablocr!=-1)
      {
        rightStr = strText.Mid(tablocr+1);
        leftStr = strText.Left(strText.Find(_T('\t')));
        rectt.right -= m_iconX;
      }
      else
      {
        leftStr = strText;
      }

      int iOldMode = pDC->SetBkMode( TRANSPARENT);
      // Draw the text in the correct colour:
      UINT nFormat  = DT_LEFT|DT_SINGLELINE|DT_VCENTER;
      UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;

      if(bIsMenuBar)
      {
        rectt = RectSel;
        rectt.OffsetRect(-1,0);
        if(state & ODS_SELECTED)
        {
          rectt.OffsetRect(1,1);
        } 
        nFormat = DT_CENTER|DT_SINGLELINE|DT_VCENTER;
      }

      CFont fontMenu;
      LOGFONT logFontMenu;

      #ifdef _NEW_MENU_USER_FONT
        logFontMenu =  MENU_USER_FONT;
      #else
        NONCLIENTMETRICS nm = {0};
        nm.cbSize = sizeof (nm);
        VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
        logFontMenu =  nm.lfMenuFont;
      #endif

      // Default selection?
      if(state&ODS_DEFAULT)
      {
        // Make the font bold
        logFontMenu.lfWeight = FW_BOLD;
      }

      fontMenu.CreateFontIndirect (&logFontMenu);
      CFont* pOldFont = pDC->SelectObject(&fontMenu);

      if(!(lpDIS->itemState & ODS_GRAYED))
      {
        pDC->SetTextColor(crText);
        pDC->DrawText (leftStr,rectt,nFormat);
        if(tablocr!=-1)
        {
          pDC->DrawText (rightStr,rectt,nFormatr);
        }
      }
      else
      {
        // Draw the disabled text
        if(!(state & ODS_SELECTED))
        {
          CRect offset = rectt;
          offset.OffsetRect (1,1);

          pDC->SetTextColor(GetSysColor(COLOR_BTNHILIGHT));
          pDC->DrawText(leftStr,&offset, nFormat);
          if(tablocr!=-1)
          {
            pDC->DrawText (rightStr,&offset,nFormatr);
          }

          pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1)
          {
            pDC->DrawText(rightStr,rectt,nFormatr);
          }
        }
        else
        {
          // And the standard Grey text:
          pDC->SetTextColor(colorBack);
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1)
          {
            pDC->DrawText (rightStr,rectt,nFormatr);
          }
        }
      }
      pDC->SelectObject(pOldFont);
      pDC->SetBkMode( iOldMode );
    }
    m_brSelect.DeleteObject();
  }
}

BOOL CNewMenu::IsMenuBar(HMENU hMenu)
{
  BOOL bIsMenuBar = ::IsMenu(hMenu);
  if(bIsMenuBar)
  {
    if(m_hParentMenu==NULL)
    {
      return m_bIsPopupMenu?FALSE:TRUE; 
    }
    CNewMenu* pMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(m_hParentMenu));
    if (pMenu!=NULL)
    {
      return pMenu->m_bIsPopupMenu?FALSE:TRUE; 
    }
  }
  return bIsMenuBar;
}

/*
==========================================================================
void CNewMenu::MeasureItem(LPMEASUREITEMSTRUCT)
---------------------------------------------

  Called by the framework when it wants to know what the width and height
  of our item will be.  To accomplish this we provide the width of the
  icon plus the width of the menu text, and then the height of the icon.
  
==========================================================================
*/
void CNewMenu::MeasureItem_OldStyle( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar )
{
  ASSERT(lpMIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpMIS->itemData);

  UINT state = pMenuData->m_nFlags;
  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      // DC of the desktop
      CClientDC myDC(NULL);

      CFont font;
      LOGFONT MyFont = m_MenuTitleFont;
      MyFont.lfOrientation = 0;
      MyFont.lfEscapement = 0;
      font.CreateFontIndirect(&MyFont);

      CFont* pOldFont = myDC.SelectObject (&font);
      LPCTSTR lpstrText = pMenuData->GetString();
      SIZE size = {0,0};
      VERIFY(::GetTextExtentPoint32(myDC.m_hDC,lpstrText,(int)_tcslen(lpstrText),&size));
      // Select old font in
      myDC.SelectObject(pOldFont);  

      if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
      {
        lpMIS->itemWidth = size.cy -GetSystemMetrics(SM_CXMENUCHECK);
        // Don't make the menu higher than menuitems in it
        lpMIS->itemHeight = 0;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemWidth += 8;
        }
        else if(pMenuData->m_nTitleFlags&MFT_ROUND)
        {
          lpMIS->itemWidth += 4;
        }
      }
      else
      {
        lpMIS->itemWidth = size.cx;
        lpMIS->itemHeight = size.cy;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemHeight += 8;
        }
      }
    }
    else
    {
      lpMIS->itemHeight = 3;
      lpMIS->itemWidth = 3;
    }
  }
  else
  {
    CFont fontMenu;
    LOGFONT logFontMenu;

    #ifdef _NEW_MENU_USER_FONT
      logFontMenu =  MENU_USER_FONT;
    #else
      NONCLIENTMETRICS nm = {0};
      nm.cbSize = sizeof (nm);
      VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
      logFontMenu =  nm.lfMenuFont;
    #endif

    // Default selection?
    if(GetDefaultItem(0, FALSE) == pMenuData->m_nID)
    {
      // Make the font bold
      logFontMenu.lfWeight = FW_BOLD;
    }

    fontMenu.CreateFontIndirect (&logFontMenu);
    
    // DC of the desktop
    CClientDC myDC(NULL);
    
    // Select menu font in...    
    CFont* pOldFont = myDC.SelectObject (&fontMenu);
    //Get pointer to text SK
    CString itemText = pMenuData->GetString();
    SIZE size = {0,0};
    VERIFY(::GetTextExtentPoint32(myDC.m_hDC,itemText,itemText.GetLength(),&size));
    // Select old font in
    myDC.SelectObject(pOldFont);  
  

    // Set width and height:
    if(bIsMenuBar)
    {
      if(itemText.Find(_T("&"))>=0)
      {
        lpMIS->itemWidth = size.cx - GetSystemMetrics(SM_CXMENUCHECK)/2;
      }
      else
      {
        lpMIS->itemWidth = size.cx;
      }
    }
    else
    {
      lpMIS->itemWidth = m_iconX + size.cx + m_iconX + GAP;
    }

    int temp = GetSystemMetrics(SM_CYMENU);
    lpMIS->itemHeight = (temp>(m_iconY+4)) ? temp : (m_iconY+4);
    if(lpMIS->itemHeight<((UINT)size.cy) )
    {
      lpMIS->itemHeight=((UINT)size.cy);
    }
   
    // set status bar as appropriate
    UINT nItemID = (lpMIS->itemID & 0xFFF0);
    // Special case for system menu
    if (nItemID>=SC_SIZE && nItemID<=SC_HOTKEY) 
    {
      BOOL bGetNext = FALSE;
      // search the actual menu item
      for (int j=0;j<m_MenuItemList.GetUpperBound();++j)
      {
        CNewMenuItemData* pTemp = m_MenuItemList[j];
        if(pTemp==pMenuData || bGetNext==TRUE)
        {
          bGetNext = TRUE;
          pTemp = m_MenuItemList[j+1];
          if(pTemp->m_nID)
          {
            lpMIS->itemData = (ULONG_PTR)pTemp;
            lpMIS->itemID = pTemp->m_nID; 
            UINT nOrgWidth = lpMIS->itemWidth;
            MeasureItem_OldStyle(lpMIS,bIsMenuBar);
            // Restore old values
            lpMIS->itemData = (ULONG_PTR)pMenuData;
            lpMIS->itemID = pMenuData->m_nID;
            lpMIS->itemWidth = max(lpMIS->itemWidth,nOrgWidth);
            break;
          }
        }
      }
      lpMIS->itemHeight = temp;
    } 
  }
}

void CNewMenu::MeasureItem_Icy( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar )
{
  ASSERT(lpMIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpMIS->itemData);

  UINT state = pMenuData->m_nFlags;
  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      // DC of the desktop
      CClientDC myDC(NULL);

      CFont font;
      LOGFONT MyFont = m_MenuTitleFont;
      MyFont.lfOrientation = 0;
      MyFont.lfEscapement = 0;
      font.CreateFontIndirect(&MyFont);

      CFont* pOldFont = myDC.SelectObject (&font);
      LPCTSTR lpstrText = pMenuData->GetString();
      SIZE size = {0,0};
      VERIFY(::GetTextExtentPoint32(myDC.m_hDC,lpstrText,(int)_tcslen(lpstrText),&size));
      // Select old font in
      myDC.SelectObject(pOldFont);  

      if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
      {
        lpMIS->itemWidth = size.cy -GetSystemMetrics(SM_CXMENUCHECK);
        // Don't make the menu higher than menuitems in it
        lpMIS->itemHeight = 0;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemWidth += 8;
        }
         else if(pMenuData->m_nTitleFlags&MFT_ROUND)
        {
          lpMIS->itemWidth += 4;
        }
      }
      else
      {
        lpMIS->itemWidth = size.cx;
        lpMIS->itemHeight = size.cy;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemHeight += 8;
        }
      }
    }
    else
    {
      lpMIS->itemHeight = 3;
      lpMIS->itemWidth = 3;
    }
  }
  else
  {
    LOGFONT logFontMenu;
    CFont fontMenu;

    #ifdef _NEW_MENU_USER_FONT
      logFontMenu =  MENU_USER_FONT;
    #else
      NONCLIENTMETRICS nm = {0};
      nm.cbSize = sizeof (nm);
      VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
      logFontMenu =  nm.lfMenuFont;
    #endif

    // Default selection?
    if(GetDefaultItem(0, FALSE) == pMenuData->m_nID)
    {
      // Make the font bold
      logFontMenu.lfWeight = FW_BOLD;
    }

    fontMenu.CreateFontIndirect (&logFontMenu);
    
    // DC of the desktop
    CClientDC myDC(NULL);
    
    // Select menu font in...    
    CFont* pOldFont = myDC.SelectObject (&fontMenu);
    //Get pointer to text SK
    CString itemText = pMenuData->GetString();
    SIZE size = {0,0};
    // Check the Key-Shortcut replacing for japanise/chinese calculating space
    itemText.Replace(_T("\t"),_T("nnn"));
    VERIFY(::GetTextExtentPoint32(myDC.m_hDC,itemText,itemText.GetLength(),&size));
    // Select old font in
    myDC.SelectObject(pOldFont);  
  
    // Set width and height:
    if(bIsMenuBar)
    {
      if(itemText.Find(_T("&"))>=0)
      {
        lpMIS->itemWidth = size.cx - GetSystemMetrics(SM_CXMENUCHECK)/2;
      }
      else
      {
        lpMIS->itemWidth = size.cx;
      }
    }
    else
    {
      lpMIS->itemWidth = m_iconX + size.cx + m_iconX + GAP;
    }

    int temp = GetSystemMetrics(SM_CYMENU);
    lpMIS->itemHeight = (temp>(m_iconY + 6)) ? temp : (m_iconY+6);
    if(lpMIS->itemHeight<((UINT)size.cy) )
    {
      lpMIS->itemHeight=((UINT)size.cy);
    }
    
    // set status bar as appropriate
    UINT nItemID = (lpMIS->itemID & 0xFFF0);
    // Special case for system menu
    if (nItemID>=SC_SIZE && nItemID<=SC_HOTKEY) 
    {
      BOOL bGetNext = FALSE;
      // search the actual menu item
      for (int j=0;j<m_MenuItemList.GetUpperBound();++j)
      {
        CNewMenuItemData* pTemp = m_MenuItemList[j];
        if(pTemp==pMenuData || bGetNext==TRUE)
        {
          bGetNext = TRUE;
          pTemp = m_MenuItemList[j+1];
          if(pTemp->m_nID)
          {
            lpMIS->itemData = (ULONG_PTR)pTemp;
            lpMIS->itemID = pTemp->m_nID; 
            UINT nOrgWidth = lpMIS->itemWidth;
            MeasureItem_Icy(lpMIS,bIsMenuBar);
            // Restore old values
            lpMIS->itemData = (ULONG_PTR)pMenuData;
            lpMIS->itemID = pMenuData->m_nID;
            lpMIS->itemWidth = max(lpMIS->itemWidth,nOrgWidth);
            break;
          }
        }
      }
      lpMIS->itemHeight = temp;
    } 
  }
}

void CNewMenu::MeasureItem_WinXP( LPMEASUREITEMSTRUCT lpMIS, BOOL bIsMenuBar )
{
  ASSERT(lpMIS->itemData);
  CNewMenuItemData* pMenuData = (CNewMenuItemData*)(lpMIS->itemData);

  UINT state = pMenuData->m_nFlags;
  if(state & MF_SEPARATOR)
  {
    if(pMenuData->m_nTitleFlags&MFT_TITLE)
    {
      // DC of the desktop
      CClientDC myDC(NULL);

      CFont font;
      LOGFONT MyFont = m_MenuTitleFont;
      MyFont.lfOrientation = 0;
      MyFont.lfEscapement = 0;
      font.CreateFontIndirect(&MyFont);

      CFont* pOldFont = myDC.SelectObject (&font);
      LPCTSTR lpstrText = pMenuData->GetString();
      SIZE size = {0,0};
      VERIFY(::GetTextExtentPoint32(myDC.m_hDC,lpstrText,(int)_tcslen(lpstrText),&size));
      // Select old font in
      myDC.SelectObject(pOldFont);  

      if(pMenuData->m_nTitleFlags&MFT_SIDE_TITLE)
      {
        lpMIS->itemWidth = size.cy - GetSystemMetrics(SM_CXMENUCHECK);
        // Don't make the menu higher than menuitems in it
        lpMIS->itemHeight = 0;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemWidth += 8;
        }
        else if(pMenuData->m_nTitleFlags&MFT_ROUND)
        {
          lpMIS->itemWidth += 4;
        }
      }
      else
      {
        lpMIS->itemWidth = size.cx;//*3/4;
        lpMIS->itemHeight = size.cy;//*3/4;
        if(pMenuData->m_nTitleFlags&MFT_LINE)
        {
          lpMIS->itemHeight += 8;
        }
      }
    }
    else
    {
      lpMIS->itemHeight = 3;
      lpMIS->itemWidth = 3;
    }
  }
  else
  {
    CFont fontMenu;
    LOGFONT logFontMenu;

    #ifdef _NEW_MENU_USER_FONT
        logFontMenu =  MENU_USER_FONT;
    #else
        NONCLIENTMETRICS nm = {0};
        nm.cbSize = sizeof (NONCLIENTMETRICS);
        VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
        logFontMenu =  nm.lfMenuFont;
    #endif

    // Default selection?
    if (GetDefaultItem(0, FALSE) == pMenuData->m_nID)
    {
      // Make the font bold
      logFontMenu.lfWeight = FW_BOLD;
    }

    fontMenu.CreateFontIndirect (&logFontMenu);
    
    // DC of the desktop
    CClientDC myDC(NULL);
    
    // Select menu font in...
    CFont* pOldFont = myDC.SelectObject (&fontMenu);
    //Get pointer to text SK
    CString itemText = pMenuData->GetString();
    SIZE size = {0,0};
    // Check the Key-Shortcut replacing for japanise/chinese calculating space
    itemText.Replace(_T("\t"),_T("nnn"));
    VERIFY(::GetTextExtentPoint32(myDC.m_hDC,itemText,itemText.GetLength(),&size));
    // Select old font in
    myDC.SelectObject(pOldFont);  
  
    // Set width and height:
    if(bIsMenuBar)
    {
      if(itemText.Find(_T("&"))>=0)
      {
        lpMIS->itemWidth = size.cx-6; // - GetSystemMetrics(SM_CXMENUCHECK)/2;
      }
      else
      { 
        lpMIS->itemWidth = size.cx;
      }
    }
    else
    {
      lpMIS->itemWidth = 2 + m_iconX +4+ size.cx + GetSystemMetrics(SM_CYMENU) / 2;
    }

    int temp = GetSystemMetrics(SM_CYMENU);
    lpMIS->itemHeight = temp>m_iconY+8 ? temp : m_iconY+7;
    if(lpMIS->itemHeight<((UINT)size.cy) )
    {
      lpMIS->itemHeight=((UINT)size.cy);
    }
    
    // set status bar as appropriate
    UINT nItemID = (lpMIS->itemID & 0xFFF0);
    // Special case for system menu
    if (nItemID>=SC_SIZE && nItemID<=SC_HOTKEY) 
    {
      BOOL bGetNext = FALSE;
      // search the actual menu item
      for (int j=0;j<m_MenuItemList.GetUpperBound();++j)
      {
        CNewMenuItemData* pTemp = m_MenuItemList[j];
        if(pTemp==pMenuData || bGetNext==TRUE)
        {
          bGetNext = TRUE;
          pTemp = m_MenuItemList[j+1];
          if(pTemp->m_nID)
          {
            lpMIS->itemData = (ULONG_PTR)pTemp;
            lpMIS->itemID = pTemp->m_nID; 
            UINT nOrgWidth = lpMIS->itemWidth;
            MeasureItem_WinXP(lpMIS,bIsMenuBar);
            // Restore old values
            lpMIS->itemData = (ULONG_PTR)pMenuData;
            lpMIS->itemID = pMenuData->m_nID;
            lpMIS->itemWidth = max(lpMIS->itemWidth,nOrgWidth);
            break;
          }
        }
      }
      lpMIS->itemHeight = temp;
    }
  }
}

void CNewMenu::SetIconSize (int width, int height)
{
  m_iconX = width;
  m_iconY = height;
}

BOOL CNewMenu::AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID, int nIconNormal)
{
  return CNewMenu::AppendODMenu(lpstrText,nFlags,nID,(CImageList*)NULL,nIconNormal);
}

BOOL CNewMenu::AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID,
                            CBitmap* pBmp)
{
  int nIndex = -1;
  CNewMenuIconLock iconLock(GetMenuIcon(nIndex,pBmp));
  return AppendODMenu(lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CNewMenu::AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID,
                           CImageList* pil, int xoffset)
{
  int nIndex = 0;
  // Helper for addref and release
  CNewMenuIconLock iconLock(GetMenuIcon(nIndex,nID,pil,xoffset));
  return AppendODMenu(lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CNewMenu::AppendODMenu(LPCTSTR lpstrText, UINT nFlags, UINT nID,
                            CNewMenuIcons* pIcons, int nIndex)
{
  // Add the MF_OWNERDRAW flag if not specified:
  if(!nID)
  {
    if(nFlags&MF_BYPOSITION)
      nFlags=MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
    else 
      nFlags=MF_SEPARATOR|MF_OWNERDRAW;
  }
  else if(!(nFlags & MF_OWNERDRAW))
  {
    nFlags |= MF_OWNERDRAW;
  }

  if(nFlags & MF_POPUP)
  {
    CNewMenu* pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(UIntToHMenu(nID)));
    if(pSubMenu)
    {
      pSubMenu->m_hParentMenu = m_hMenu;
    }
  }

  CNewMenuItemData* pItemData = new CNewMenuItemData;
  m_MenuItemList.Add(pItemData);
  pItemData->SetString(lpstrText);

  pIcons->AddRef();
  pItemData->m_pMenuIcon->Release();
  pItemData->m_pMenuIcon = pIcons;
  pItemData->m_nFlags = nFlags;
  pItemData->m_nID = nID;

  if(pIcons && nIndex>=0)
  {
    pItemData->m_nMenuIconOffset = nIndex; 
    CSize size = pIcons->GetIconSize();
    m_iconX = max(m_iconX,size.cx);
    m_iconY = max(m_iconY,size.cy);
  }
  else
  {
    pItemData->m_nMenuIconOffset = -1; 
  } 

  // for having automated shortcut handling, thank to Mehdy Bohlool
  if (CMenu::AppendMenu(nFlags&~MF_OWNERDRAW, nID, pItemData->m_szMenuText))
  {
    return CMenu::ModifyMenu( CMenu::GetMenuItemCount()-1, MF_BYPOSITION| nFlags, nID, (LPCTSTR)pItemData );
  }
  return FALSE;
}

BOOL CNewMenu::InsertODMenu(UINT nPosition, LPCTSTR lpstrText, UINT nFlags, UINT nID,
                           int nIconNormal)
{
  int nIndex = -1;
  CNewMenuIcons* pIcons=NULL;

  if(nIconNormal>=0)
  {
    if(LoadFromToolBar(nID,nIconNormal,nIndex))
    {
      // the nIconNormal is a toolbar
      pIcons = GetToolbarIcons(nIconNormal);
      if(pIcons)
      {
        nIndex = pIcons->FindIndex(nID);
      }
    }
    else
    {
      // the nIconNormal is a bitmap
      pIcons = GetMenuIcon(nIndex,nIconNormal);
    }
  }

  CNewMenuIconLock iconLock(pIcons);
  return InsertODMenu(nPosition,lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CNewMenu::InsertODMenu(UINT nPosition, LPCTSTR lpstrText, UINT nFlags, UINT nID,
                            CBitmap* pBmp)
{
  int nIndex = -1;
  CNewMenuIconLock iconLock(GetMenuIcon(nIndex,pBmp));
  return InsertODMenu(nPosition,lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CNewMenu::InsertODMenu(UINT nPosition, LPCTSTR lpstrText, UINT nFlags, UINT nID,
                            CImageList *pil, int xoffset)
{
  int nIndex = -1;
  CNewMenuIconLock iconLock(GetMenuIcon(nIndex,nID,pil,xoffset));
  return InsertODMenu(nPosition,lpstrText,nFlags,nID,iconLock,nIndex);
}

BOOL CNewMenu::InsertODMenu(UINT nPosition, LPCTSTR lpstrText, UINT nFlags, UINT nID,
                            CNewMenuIcons* pIcons, int nIndex)
{
  if(!(nFlags & MF_BYPOSITION))
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(nPosition,iPosition);
    if(pMenu)
    {
      return(pMenu->InsertODMenu(iPosition,lpstrText,nFlags|MF_BYPOSITION,nID,pIcons,nIndex));
    }
    else 
    {
      return(FALSE);
    }
  }
  
  if(!nID)
  {
    nFlags=MF_SEPARATOR|MF_OWNERDRAW|MF_BYPOSITION;
  }
  else if(!(nFlags & MF_OWNERDRAW))
  {
    nFlags |= MF_OWNERDRAW;
  }
  
  if(nFlags & MF_POPUP)
  { 
    CNewMenu* pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(UIntToHMenu(nID)));
    if(pSubMenu)
    {
      pSubMenu->m_hParentMenu = m_hMenu;
    }
  }
  
  //Stephane Clog suggested adding this, believe it or not it's in the help 
  if(nPosition==(UINT)-1)
  {
    nPosition = GetMenuItemCount();
  }
  
  CNewMenuItemData *pItemData = new CNewMenuItemData;
  m_MenuItemList.InsertAt(nPosition,pItemData);
  pItemData->SetString(lpstrText);

  pIcons->AddRef();
  pItemData->m_pMenuIcon->Release();
  pItemData->m_pMenuIcon = pIcons;
  pItemData->m_nFlags = nFlags;
  pItemData->m_nID = nID;

  if(pIcons && nIndex>=0)
  {
    pItemData->m_nMenuIconOffset = nIndex; 
    CSize size = pIcons->GetIconSize();
    m_iconX = max(m_iconX,size.cx);
    m_iconY = max(m_iconY,size.cy);
  }
  else
  {
    pItemData->m_nMenuIconOffset = -1; 
  }  
  // for having automated shortcut handling, thank to Mehdy Bohlool
  if (CMenu::InsertMenu(nPosition,nFlags&~MF_OWNERDRAW,nID,pItemData->m_szMenuText))
  {
    return CMenu::ModifyMenu(nPosition, MF_BYPOSITION| nFlags, nID, (LPCTSTR)pItemData );
  }
  return FALSE;
}

// Same as ModifyMenu but replacement for CNewMenu
BOOL CNewMenu::ModifyODMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem,LPCTSTR lpszNewItem)
{
  if(!(nFlags & MF_BYPOSITION))
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(nPosition,iPosition);
    if(pMenu)
    {
      return(pMenu->ModifyODMenu(iPosition,nFlags|MF_BYPOSITION,nIDNewItem,lpszNewItem));
    }
    else 
    {
      return(FALSE);
    }
  }
  UINT nMenuID = GetMenuItemID(nPosition);
  if(nMenuID==(UINT)-1)
  {
    nMenuID = HMenuToUInt(::GetSubMenu(m_hMenu,nPosition));
  }
  CNewMenuItemData* pItemData = FindMenuItem(nMenuID);
  BOOL bRet = CMenu::ModifyMenu(nPosition, nFlags, nIDNewItem,lpszNewItem);
  if(pItemData)
  {
    pItemData->m_nID = nIDNewItem;
    GetMenuString(nPosition,pItemData->m_szMenuText,MF_BYPOSITION); 
    CMenu::ModifyMenu(nPosition, nFlags|MF_OWNERDRAW, nIDNewItem,(LPCTSTR)pItemData);
  }
  if(bRet && (nFlags & MF_POPUP) )
  {
    CNewMenu* pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(UIntToHMenu(nIDNewItem)));
    if(pSubMenu)
    {
      pSubMenu->m_hParentMenu = m_hMenu;
    }
  }
  return bRet;
}

BOOL CNewMenu::ModifyODMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, const CBitmap* pBmp)
{
  if(!(nFlags & MF_BYPOSITION))
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(nPosition,iPosition);
    if(pMenu)
    {
      return(pMenu->ModifyODMenu(iPosition,nFlags|MF_BYPOSITION,nIDNewItem,pBmp));
    }
    else 
    {
      return(FALSE);
    }
  }
  UINT nMenuID = GetMenuItemID(nPosition);
  if(nMenuID==(UINT)-1)
  {
    nMenuID = HMenuToUInt(::GetSubMenu(m_hMenu,nPosition));
  }
  CNewMenuItemData* pItemData = FindMenuItem(nMenuID);
  BOOL bRet = CMenu::ModifyMenu(nPosition, nFlags, nIDNewItem,pBmp);
  if(pItemData)
  {
    pItemData->m_nID = nIDNewItem;
    pItemData->m_szMenuText.Empty(); 
    CMenu::ModifyMenu(nPosition, nFlags|MF_OWNERDRAW, nIDNewItem,(LPCTSTR)pItemData);
  }
  if(bRet && (nFlags & MF_POPUP) )
  {
    CNewMenu* pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(UIntToHMenu(nIDNewItem)));
    if(pSubMenu)
    {
      pSubMenu->m_hParentMenu = m_hMenu;
    }
  }
  return bRet;
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, int nIconNormal)
{
  int nLoc;
  CNewMenuItemData* pItemData;
  CArray<CNewMenu*,CNewMenu*>newSubs;
  CArray<int,int&>newLocs;

  BOOL bModifyOK = TRUE;

  // Find the old CNewMenuItemData structure:
  CNewMenu* pSubMenu = FindMenuOption(nID,nLoc);
  do {
    if(pSubMenu && nLoc>=0)
    {
      pItemData = pSubMenu->m_MenuItemList[nLoc];
    }
    else
    {
      // Create a new CNewMenuItemData structure:
      pItemData = new CNewMenuItemData;
      m_MenuItemList.Add(pItemData);
    }

    BOOL bTextChanged = FALSE;
    ASSERT(pItemData);
    if(lpstrText && pItemData->m_szMenuText.Compare(lpstrText)!=NULL)
    {
      bTextChanged = TRUE;
      pItemData->SetString(lpstrText);
    }

    pItemData->m_nMenuIconOffset=-1;
    if(nIconNormal>=0)
    {
      int nxOffset = -1;
      CNewMenuIcons* pIcons=NULL;
      if(LoadFromToolBar(nID,nIconNormal,nxOffset))
      {
        // the nIconNormal is a toolbar
        pIcons = GetToolbarIcons(nIconNormal);
        if(pIcons)
        {
          pItemData->m_nMenuIconOffset = pIcons->FindIndex(nID);
        }
      }
      else
      {
        // the nIconNormal is a bitmap
        pIcons = GetMenuIcon(pItemData->m_nMenuIconOffset,nIconNormal);
      }
      pIcons->AddRef();
      pItemData->m_pMenuIcon->Release();
      pItemData->m_pMenuIcon = pIcons;
      if(pIcons)
      {
        CSize size = pIcons->GetIconSize();
        pSubMenu->m_iconX = max(pSubMenu->m_iconX,size.cx);
        pSubMenu->m_iconY = max(pSubMenu->m_iconY,size.cy);
      }
    }
    pItemData->m_nFlags &= ~(MF_BYPOSITION);
    pItemData->m_nFlags |= MF_OWNERDRAW;
    pItemData->m_nID = nID;

    // for having automated shortcut handling
    if(pSubMenu && bTextChanged)
    {
      if(pSubMenu->ModifyMenu(nLoc, MF_BYPOSITION|(pItemData->m_nFlags&~MF_OWNERDRAW), nID,pItemData->m_szMenuText) )
      {
        if(!pSubMenu->ModifyMenu(nLoc, MF_BYPOSITION|pItemData->m_nFlags, nID,(LPCTSTR)pItemData))
        {
          bModifyOK = FALSE;
        }
      }
      else
      {
        bModifyOK = FALSE;
      }
    }

    newSubs.Add(pSubMenu);
    newLocs.Add(nLoc);

    if(pSubMenu && nLoc>=0)
    {
      pSubMenu = FindAnotherMenuOption(nID,nLoc,newSubs,newLocs);
    }
    else
    {
      pSubMenu = NULL;
    }
  }while(pSubMenu);

  return (CMenu::ModifyMenu(nID,pItemData->m_nFlags,nID,(LPCTSTR)pItemData)) && bModifyOK;
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, CImageList *pil, int xoffset)
{
  int nIndex = 0;
  CNewMenuIcons* pIcons = GetMenuIcon(nIndex,nID,pil,xoffset);
  pIcons->AddRef();

  BOOL bResult = ModifyODMenu(lpstrText,nID,pIcons,nIndex);

  pIcons->Release();

  return bResult; 
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, CNewMenuIcons* pIcons, int xoffset)
{
  ASSERT(pIcons);
  int nLoc;
  CNewMenuItemData *pItemData;
  CArray<CNewMenu*,CNewMenu*>newSubs;
  CArray<int,int&>newLocs;
  BOOL bModifyOK = TRUE;

  // Find the old CNewMenuItemData structure:
  CNewMenu *pSubMenu = FindMenuOption(nID,nLoc);
  do {
    if(pSubMenu && nLoc>=0)
    {
      pItemData = pSubMenu->m_MenuItemList[nLoc];
    }
    else
    {
      // Create a new CNewMenuItemData structure:
      pItemData = new CNewMenuItemData;
      m_MenuItemList.Add(pItemData);
    }

    BOOL bTextChanged = FALSE;
    ASSERT(pItemData);
    if(lpstrText && pItemData->m_szMenuText.Compare(lpstrText)!=NULL)
    {
      bTextChanged = TRUE;
      pItemData->SetString(lpstrText);
    }

    if(pIcons)
    {
      pIcons->AddRef();
      pItemData->m_pMenuIcon->Release();
      pItemData->m_pMenuIcon = pIcons;

      pItemData->m_nMenuIconOffset = xoffset; 

      int x=0;
      int y=0;
      if(pSubMenu && pIcons->GetIconSize(&x,&y))
      {
        // Correct the size of the menuitem
        pSubMenu->m_iconX = max(pSubMenu->m_iconX,x);
        pSubMenu->m_iconY = max(pSubMenu->m_iconY,y);
      }
    }
    else
    {
      pItemData->m_nMenuIconOffset = -1; 
    }
    pItemData->m_nFlags &= ~(MF_BYPOSITION);
    pItemData->m_nFlags |= MF_OWNERDRAW;
    pItemData->m_nID = nID;

    // for having automated shortcut handling
    if(pSubMenu && bTextChanged)
    {
      if(pSubMenu->ModifyMenu(nLoc, MF_BYPOSITION|(pItemData->m_nFlags&~MF_OWNERDRAW), nID,pItemData->m_szMenuText) )
      {
        if(!pSubMenu->ModifyMenu(nLoc, MF_BYPOSITION|pItemData->m_nFlags, nID,(LPCTSTR)pItemData))
        {
          bModifyOK = FALSE;
        }
      }
      else
      {
        bModifyOK = FALSE;
      }
    }

    newSubs.Add(pSubMenu);
    newLocs.Add(nLoc);
    if(pSubMenu && nLoc>=0)
    {
      pSubMenu = FindAnotherMenuOption(nID,nLoc,newSubs,newLocs);
    }
    else 
    {
      pSubMenu = NULL;
    }
  } while(pSubMenu);

  return (CMenu::ModifyMenu(nID,pItemData->m_nFlags,nID,(LPCTSTR)pItemData)) && bModifyOK;
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, CBitmap* bmp)
{
  if (bmp)
  {
    CImageList temp;
    temp.Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
    
    temp.Add(bmp,GetBitmapBackground());

    return ModifyODMenu(lpstrText,nID,&temp,0);
  }
  return ModifyODMenu(lpstrText,nID,(CImageList*)NULL,0);
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText, UINT nID, COLORREF fill, COLORREF border, int hatchstyle)
{
  // Get device context
  CClientDC DC(0);
  CSize bitmap_size(m_iconX,m_iconY);
  CBitmap bmp;
  ColorBitmap(&DC,bmp,bitmap_size,fill,border,hatchstyle);  
  return ModifyODMenu(lpstrText,nID,&bmp);
}

BOOL CNewMenu::ModifyODMenu(LPCTSTR lpstrText, LPCTSTR OptionText, int nIconNormal)
{
  int nIndex = 0;
  CNewMenu* pOptionMenu = FindMenuOption(OptionText,nIndex);

  if(pOptionMenu!=NULL && nIndex>=0)
  {
    CNewMenuItemData* pItemData = pOptionMenu->m_MenuItemList[nIndex];

    BOOL bTextChanged = FALSE;
    ASSERT(pItemData);
    if(lpstrText && pItemData->m_szMenuText.Compare(lpstrText)!=NULL)
    {
      bTextChanged = TRUE;
      pItemData->SetString(lpstrText);
    }

    pItemData->m_nMenuIconOffset = nIconNormal;
    if(nIconNormal>=0)
    {
      CNewMenuIcons* pIcons = GetMenuIcon(pItemData->m_nMenuIconOffset,nIconNormal);
      pIcons->AddRef();
      pItemData->m_pMenuIcon->Release();
      pItemData->m_pMenuIcon = pIcons;

      CNewMenuBitmaps* pMenuIcon = DYNAMIC_DOWNCAST(CNewMenuBitmaps,pItemData->m_pMenuIcon);
      if(pMenuIcon)
      {
        CSize size = pMenuIcon->GetIconSize();
        pOptionMenu->m_iconX = max(pOptionMenu->m_iconX,size.cx);
        pOptionMenu->m_iconY = max(pOptionMenu->m_iconY,size.cy);
      }
    }

        // for having automated shortcut handling
    if(pOptionMenu && bTextChanged)
    {
      if(!pOptionMenu->ModifyMenu(nIndex, MF_BYPOSITION|(pItemData->m_nFlags&~MF_OWNERDRAW), pItemData->m_nID,pItemData->m_szMenuText) ||
         !pOptionMenu->ModifyMenu(nIndex, MF_BYPOSITION|pItemData->m_nFlags, pItemData->m_nID,(LPCTSTR)pItemData))
      {
        return FALSE;
      }
    }
    return TRUE;
  }
  return FALSE;
} 

CNewMenuItemData* CNewMenu::NewODMenu(UINT pos, UINT nFlags, UINT nID, LPCTSTR string)
{
  CNewMenuItemData* pItemData;

  pItemData = new CNewMenuItemData;
  pItemData->m_nFlags = nFlags;
  pItemData->m_nID = nID;
  pItemData->SetString (string);

  if(nFlags & MF_POPUP)
  {
    CNewMenu* pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(UIntToHMenu(nID)));
    if(pSubMenu)
    {
      pSubMenu->m_hParentMenu = m_hMenu;
    }
  }

  BOOL bModified = FALSE;
  if (nFlags&MF_OWNERDRAW)
  {
    ASSERT(!(nFlags&MF_STRING));
    bModified = ModifyMenu(pos,nFlags,nID,(LPCTSTR)pItemData);
  }
  else if (nFlags&MF_BITMAP)
  {
    bModified = ModifyMenu(pos,nFlags,nID,(CBitmap*)string);
  }
  else if (nFlags&MF_SEPARATOR)
  {
    ASSERT(nFlags&MF_SEPARATOR);
    bModified = ModifyMenu(pos,nFlags,nID);
  }
  else // (nFlags&MF_STRING)
  {
    ASSERT(!(nFlags&MF_OWNERDRAW));
    bModified = ModifyMenu(pos,nFlags,nID,pItemData->GetString());
  } 
  if(!bModified)
  {
    ShowLastError();
  }
  return(pItemData);
};

BOOL CNewMenu::LoadToolBars(const UINT* arID, int n, HMODULE hInst)
{
  ASSERT(arID);
  BOOL returnflag = TRUE;
  for(int i=0;i<n;++i)
  {
    if(!LoadToolBar(arID[i],hInst))
    {
      returnflag = FALSE;
    }
  }
  return(returnflag);
}

DWORD CNewMenu::SetMenuIcons(CNewMenuIcons* pMenuIcons)
{
  int nCount = (int)pMenuIcons->m_IDs.GetSize();
  while(nCount--)
  {
    ModifyODMenu(NULL,pMenuIcons->m_IDs[nCount],pMenuIcons,nCount*MENU_ICONS);
  }
  return pMenuIcons->m_dwRefCount;
}

CNewMenuIcons* CNewMenu::GetMenuIcon(int &nIndex, UINT nID, CImageList *pil, int xoffset)
{
  if(pil==NULL || xoffset<0)
  { 
    nIndex=-1;
    return NULL;
  }

  HICON hIcon = pil->ExtractIcon(xoffset);

  if(m_pSharedMenuIcons!=NULL)
  {
    POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
    while(pos)
    { 
      CNewMenuBitmaps* pMenuIcon = DYNAMIC_DOWNCAST(CNewMenuBitmaps,m_pSharedMenuIcons->GetNext(pos));
      if(pMenuIcon)
      {
        nIndex = pMenuIcon->Add(hIcon,nID);
        if(nIndex!=-1)
        {
          DestroyIcon(hIcon);
          return pMenuIcon;
        }
      }
    }
  }
  else
  {
    m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CNewMenuIcons*>;
  }
  CNewMenuBitmaps* pMenuIcon = new CNewMenuBitmaps();
  pMenuIcon->m_crTransparent = m_bitmapBackground;
  nIndex = pMenuIcon->Add(hIcon,nID);
  DestroyIcon(hIcon);
  if(nIndex!=-1)
  {
    m_pSharedMenuIcons->AddTail(pMenuIcon);
    return pMenuIcon;
  }
  delete pMenuIcon;
  return NULL;
}

CNewMenuIcons* CNewMenu::GetMenuIcon(int &nIndex, int nID)
{  
  if(m_pSharedMenuIcons!=NULL)
  {
    POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
    while(pos)
    { 
      CNewMenuBitmaps* pMenuIcon = DYNAMIC_DOWNCAST(CNewMenuBitmaps,m_pSharedMenuIcons->GetNext(pos));
      if(pMenuIcon)
      {
        if(m_bDynIcons)
        {
          nIndex = pMenuIcon->Add((HICON)(INT_PTR)nID);
        }
        else
        {
          nIndex = pMenuIcon->Add(nID,m_bitmapBackground);
        }
        if(nIndex!=-1)
        {
          return pMenuIcon;
        }
      }
    }
  }
  else
  {
    m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CNewMenuIcons*>;
  }
  CNewMenuBitmaps* pMenuIcon = new CNewMenuBitmaps();
  pMenuIcon->m_crTransparent = m_bitmapBackground;
  nIndex = pMenuIcon->Add(nID,m_bitmapBackground);
  if(nIndex!=-1)
  {
    m_pSharedMenuIcons->AddTail(pMenuIcon);
    return pMenuIcon;
  }
  delete pMenuIcon;
  return NULL;
}

CNewMenuIcons* CNewMenu::GetMenuIcon(int &nIndex, CBitmap* pBmp)
{ 
  if(pBmp==NULL)
  { 
    nIndex=-1;
    return NULL;
  }

  if(m_pSharedMenuIcons!=NULL)
  {
    POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
    while(pos)
    { 
      CNewMenuBitmaps* pMenuIcon = DYNAMIC_DOWNCAST(CNewMenuBitmaps,m_pSharedMenuIcons->GetNext(pos));
      if(pMenuIcon)
      {
        nIndex = pMenuIcon->Add(pBmp,m_bitmapBackground);
        if(nIndex!=-1)
        {
          return pMenuIcon;
        }
      }
    }
  }
  else
  {
    m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CNewMenuIcons*>;
  }
  CNewMenuBitmaps* pMenuIcon = new CNewMenuBitmaps();
  pMenuIcon->m_crTransparent = m_bitmapBackground;
  nIndex = pMenuIcon->Add(pBmp,m_bitmapBackground);
  if(nIndex!=-1)
  {
    m_pSharedMenuIcons->AddTail(pMenuIcon);
    return pMenuIcon;
  }
  delete pMenuIcon;
  return NULL;
}


CNewMenuIcons* CNewMenu::GetToolbarIcons(UINT nToolBar, HMODULE hInst)
{
  ASSERT_VALID(this);
  ASSERT(nToolBar != NULL);

  if(m_pSharedMenuIcons!=NULL)
  {
    POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
    while(pos)
    { 
      CNewMenuIcons* pMenuIcon = m_pSharedMenuIcons->GetNext(pos);
      if(pMenuIcon->DoMatch(MAKEINTRESOURCE(nToolBar),hInst))
      {
        return pMenuIcon;
      }
    }
  }
  else
  {
    m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CNewMenuIcons*>;
  }
  CNewMenuIcons* pMenuIcon = new CNewMenuIcons();
  pMenuIcon->m_crTransparent = m_bitmapBackground;
  if(pMenuIcon->LoadToolBar(MAKEINTRESOURCE(nToolBar),hInst))
  {
    m_pSharedMenuIcons->AddTail(pMenuIcon);
    return pMenuIcon;
  }
  delete pMenuIcon;
  return NULL;
}


BOOL CNewMenu::LoadToolBar(LPCTSTR lpszResourceName, HMODULE hInst)
{
  CNewMenuIcons* pMenuIcon = GetToolbarIcons((UINT)(UINT_PTR)lpszResourceName,hInst);
  if(pMenuIcon)
  {
    SetMenuIcons(pMenuIcon);
    return TRUE;
  }
  return FALSE;
}

BOOL CNewMenu::LoadToolBar(WORD* pToolInfo, COLORREF crTransparent)
{
  ASSERT_VALID(this);
  ASSERT(pToolInfo);

  if(crTransparent==CLR_NONE)
  {
    crTransparent = m_bitmapBackground;
  }

  if(m_pSharedMenuIcons!=NULL)
  {
    POSITION pos = m_pSharedMenuIcons->GetHeadPosition();
    while(pos)
    { 
      CNewMenuIcons* pMenuIcon = m_pSharedMenuIcons->GetNext(pos);
      if(pMenuIcon->DoMatch(pToolInfo,crTransparent))
      {
        SetMenuIcons(pMenuIcon);
        return TRUE;
      }
    }
  }
  else
  {
    m_pSharedMenuIcons = new CTypedPtrList<CPtrList, CNewMenuIcons*>;
  }
  CNewMenuIcons* pMenuIcon = new CNewMenuIcons();
  if(pMenuIcon->LoadToolBar(pToolInfo,crTransparent))
  {
    m_pSharedMenuIcons->AddTail(pMenuIcon);
    SetMenuIcons(pMenuIcon);
    return TRUE;
  }
  delete pMenuIcon;
  return FALSE;
}

BOOL CNewMenu::LoadToolBar(UINT nToolBar, HMODULE hInst)
{
  return LoadToolBar((LPCTSTR)(UINT_PTR)nToolBar,hInst);
}

BOOL CNewMenu::LoadFromToolBar(UINT nID, UINT nToolBar, int& xoffset)
{
  int xset,offset;
  UINT nStyle;
  BOOL returnflag=FALSE;
  CToolBar bar;

  CWnd* pWnd = AfxGetMainWnd();
  if (pWnd == NULL)
  {
    pWnd = CWnd::GetDesktopWindow();
  }
  bar.Create(pWnd);

  if(bar.LoadToolBar(nToolBar))
  {
    offset=bar.CommandToIndex(nID);
    if(offset>=0)
    {
      bar.GetButtonInfo(offset,nID,nStyle,xset);
      if(xset>0)
      {
        xoffset = xset;
      }
      returnflag=TRUE;
    }
  }
  return returnflag;
}

// O.S.
CNewMenuItemData* CNewMenu::FindMenuItem(UINT nID)
{
  CNewMenuItemData *pData = NULL;
  int i;
  
  for(i = 0; i <= m_MenuItemList.GetUpperBound(); i++)
  {
    if (m_MenuItemList[i]->m_nID == nID)
    {
      pData = m_MenuItemList[i];
      break;
    }
  }
  if (!pData)
  {
    int loc;
    CNewMenu *pMenu = FindMenuOption(nID, loc);
    ASSERT(pMenu != this);
    if (loc >= 0)
    {
      return pMenu->FindMenuItem(nID);
    }
  }
  return pData;
}


CNewMenu* CNewMenu::FindAnotherMenuOption(int nId, int& nLoc,
                                          CArray<CNewMenu*,CNewMenu*>&newSubs,
                                          CArray<int,int&>&newLocs)
{
  int i,numsubs,j;
  CNewMenu *pSubMenu,*pgoodmenu;
  BOOL foundflag;
  
  for(i=0;i<(int)(GetMenuItemCount());++i)
  {
    pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,GetSubMenu(i));
    if(pSubMenu)
    {
      pgoodmenu = pSubMenu->FindAnotherMenuOption(nId,nLoc,newSubs,newLocs);
      if(pgoodmenu)
      {
        return pgoodmenu;
      }
    }
    else if(nId==(int)GetMenuItemID(i))
    {
      numsubs = (int)newSubs.GetSize();
      foundflag = TRUE;
      for(j=0;j<numsubs;++j)
      {
        if(newSubs[j]==this && newLocs[j]==i)
        {
          foundflag = FALSE;
          break;
        }
      }
      if(foundflag)
      {
        nLoc = i;
        return this;
      }
    }
  }
  nLoc = -1;

  return NULL;
}

CNewMenu* CNewMenu::FindMenuOption(int nId, int& nLoc)
{
  int i;
  CNewMenu *pSubMenu,*pgoodmenu;
  
  for(i=0;i<(int)(GetMenuItemCount());++i)
  {
    pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,GetSubMenu(i));
    if(pSubMenu)
    {
      pgoodmenu = pSubMenu->FindMenuOption(nId,nLoc);
      if(pgoodmenu)
      {
        return pgoodmenu;
      }
    }
    else if(nId==(int)GetMenuItemID(i))
    {
      nLoc = i;
      return(this);
    }
  }
  nLoc = -1;
  return NULL;
}

CNewMenu* CNewMenu::FindMenuOption(LPCTSTR lpstrText, int& nLoc)
{ 
  int i;
  // First look for all item text.
  for(i=0;i<=(int)m_MenuItemList.GetUpperBound();++i)
  {  
    if(m_MenuItemList[i]->m_szMenuText.Compare(lpstrText)==NULL)
    {
      nLoc = i;
      return this;
    }
  }
  CNewMenu* pSubMenu;
  // next, look in all submenus
  for(i=0; i<(int)(GetMenuItemCount());++i)
  {
    pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,GetSubMenu(i));
    if(pSubMenu)
    {
      pSubMenu = pSubMenu->FindMenuOption(lpstrText,nLoc);
      if(pSubMenu)
      {
        return pSubMenu;
      }
    }
  }
  nLoc = -1;
  return NULL;
} 

BOOL CNewMenu::LoadMenu(HMENU hMenu)
{
  if(!::IsMenu(hMenu) || !Attach(hMenu))
  {
    return FALSE;
  }
  m_bIsPopupMenu = FALSE;
  for(int i=0;i<(int)(GetMenuItemCount());++i)
  { 
    HMENU hSubMenu = ::GetSubMenu(m_hMenu,i);
    if(hSubMenu)
    {
      CNewMenu* pMenu = new CNewMenu(m_hMenu);
      m_SubMenus.Add(hSubMenu);
      pMenu->LoadMenu(hSubMenu); 
      pMenu->m_bIsPopupMenu = TRUE;
    }
  }  
  SynchronizeMenu();
  return TRUE;
}

BOOL CNewMenu::LoadMenu(int nResource)
{
  return(CNewMenu::LoadMenu(MAKEINTRESOURCE(nResource)));
}

BOOL CNewMenu::LoadMenu(LPCTSTR lpszResourceName)
{ 
  HMENU hMenu = ::LoadMenu(AfxFindResourceHandle(lpszResourceName,RT_MENU), lpszResourceName);
  return LoadMenu(hMenu);
}

BOOL CNewMenu::SetItemData(UINT uiId, DWORD_PTR dwItemData, BOOL fByPos)
{  
  MENUITEMINFO MenuItemInfo = {0};
  MenuItemInfo.cbSize = sizeof(MenuItemInfo);
  MenuItemInfo.fMask = MIIM_DATA; 
  if(::GetMenuItemInfo(m_hMenu,uiId,fByPos,&MenuItemInfo))
  {
    CNewMenuItemData* pItem = CheckMenuItemData(MenuItemInfo.dwItemData);
    if(pItem)
    {
      pItem->m_pData = (void*)dwItemData;
      return TRUE;
    }
  }
  return FALSE;
}

BOOL CNewMenu::SetItemDataPtr(UINT uiId, void* pItemData, BOOL fByPos )
{
  return SetItemData(uiId, (DWORD_PTR) pItemData, fByPos);
}

DWORD_PTR CNewMenu::GetItemData(UINT uiId, BOOL fByPos) const
{
  MENUITEMINFO MenuItemInfo = {0};
  MenuItemInfo.cbSize = sizeof(MenuItemInfo);
  MenuItemInfo.fMask = MIIM_DATA; 
  if(::GetMenuItemInfo(m_hMenu,uiId,fByPos,&MenuItemInfo))
  {
    CNewMenuItemData* pItem = CheckMenuItemData(MenuItemInfo.dwItemData);
    if(pItem)
    {
      return (DWORD_PTR)pItem->m_pData;
    }
  }
  return DWORD_PTR(-1);
}

void* CNewMenu::GetItemDataPtr(UINT uiId, BOOL fByPos) const
{
  return (void*)GetItemData(uiId,fByPos);
}

BOOL CNewMenu::SetMenuData(DWORD_PTR dwMenuData)
{
  m_pData = (void*)dwMenuData;
  return TRUE;
}

BOOL CNewMenu::SetMenuDataPtr(void* pMenuData)
{
  m_pData = (void*)pMenuData;
  return TRUE;
}

DWORD_PTR CNewMenu::GetMenuData() const
{
  return (DWORD_PTR)m_pData;
}

void* CNewMenu::GetMenuDataPtr() const
{
  return m_pData;
}


void CNewMenu::LoadCheckmarkBitmap(int unselect, int select)
{
  if(unselect>0 && select>0)
  {
    m_selectcheck = select;
    m_unselectcheck = unselect;
    if(m_checkmaps)
    {
      m_checkmaps->DeleteImageList();
    }
    else
    {
      m_checkmaps = new CImageList();
    }

    m_checkmaps->Create(m_iconX,m_iconY,ILC_MASK,2,1);
    BOOL flag1 = AddBitmapToImageList(m_checkmaps,unselect);
    BOOL flag2 = AddBitmapToImageList(m_checkmaps,select);

    if(!flag1||!flag2)
    {
      m_checkmaps->DeleteImageList();
      delete m_checkmaps;
      m_checkmaps = NULL;
    }
  }
}

BOOL CNewMenu::GetMenuText(UINT id, CString& string, UINT nFlags/*= MF_BYPOSITION*/)
{
  if(MF_BYPOSITION&nFlags)
  {
    UINT numMenuItems = (int)m_MenuItemList.GetUpperBound();
    if(id<=numMenuItems)
    {
      string = m_MenuItemList[id]->GetString();
      return TRUE;
    }
  }
  else
  {
    int uiLoc;
    CNewMenu* pMenu = FindMenuOption(id,uiLoc);
    if(NULL!=pMenu)
    {
      return pMenu->GetMenuText(uiLoc,string);
    }
  }
  return FALSE;
}

CNewMenuItemData* CNewMenu::CheckMenuItemData(ULONG_PTR nItemData) const
{
  for(int i=0;i<=m_MenuItemList.GetUpperBound();++i)
  {
    CNewMenuItemData* pItem = m_MenuItemList[i];
    if ( ((ULONG_PTR)pItem)==nItemData )
    {
      return pItem;
    }
  }
  return NULL;
}


CNewMenuItemData* CNewMenu::FindMenuList(UINT nID)
{
  for(int i=0;i<=m_MenuItemList.GetUpperBound();++i)
  {
    CNewMenuItemData* pMenuItem = m_MenuItemList[i];
    if(pMenuItem->m_nID==nID && !pMenuItem->m_nSyncFlag)
    {
      pMenuItem->m_nSyncFlag = 1;
      return pMenuItem;
    }
  }
  return NULL;
}

void CNewMenu::InitializeMenuList(int value)
{
  for(int i=0;i<=m_MenuItemList.GetUpperBound();++i)
  {
    m_MenuItemList[i]->m_nSyncFlag = value;
  }
}

void CNewMenu::DeleteMenuList()
{
  for(int i=0;i<=m_MenuItemList.GetUpperBound();++i)
  {
    if(!m_MenuItemList[i]->m_nSyncFlag)
    {
      delete m_MenuItemList[i];
    }
  }
}

void CNewMenu::SynchronizeMenu()
{
  CTypedPtrArray<CPtrArray, CNewMenuItemData*> temp;
  CNewMenuItemData *pItemData;
  CString string;
  UINT submenu,state,j;

  InitializeMenuList(0);
  for(j=0;j<GetMenuItemCount();++j)
  {
    pItemData=NULL;
    state = GetMenuState(j,MF_BYPOSITION);
    // item doesn't exist
    if(state==UINT_PTR(-1))
    {
      break;
    }
    // Special purpose for Windows NT 4.0
    if(state&MF_BITMAP)
    {
      // Bitmap-button like system menu, maximize, minimize and close
      // just ignore.
      UINT nID = GetMenuItemID(j);
      pItemData = FindMenuList(nID);
      if(!pItemData)
      {
        pItemData = new CNewMenuItemData;
        pItemData->m_nFlags = state;
        pItemData->m_nID = nID;
      }
    } 
    else if(state&MF_POPUP)
    {
      HMENU hSubMenu = GetSubMenu(j)->m_hMenu;
      submenu = HMenuToUInt(hSubMenu);
      pItemData = FindMenuList(submenu);
      GetMenuString(j,string,MF_BYPOSITION);

      if(!pItemData)
      {
        state &= ~(MF_USECHECKBITMAPS|MF_SEPARATOR);
        pItemData = NewODMenu(j,state|MF_BYPOSITION|MF_POPUP|MF_OWNERDRAW,submenu,string);
      }
      else if(!string.IsEmpty ())
      {
        pItemData->SetString(string);
      }

      CNewMenu* pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hSubMenu));
      if(pSubMenu && pSubMenu->m_hParentMenu!=m_hMenu)
      { // Sets again the parent to this one
        pSubMenu->m_hParentMenu = m_hMenu;
      }
    }
    else if(state&MF_SEPARATOR)
    {
      pItemData = FindMenuList(0);
      if(!pItemData)
      {
        pItemData = NewODMenu(j,state|MF_BYPOSITION|MF_OWNERDRAW,0,_T(""));
      }
      else
      { 
        pItemData->m_nFlags = state|MF_BYPOSITION|MF_OWNERDRAW;
        ModifyMenu(j,pItemData->m_nFlags,0,(LPCTSTR)pItemData);
      }
    }
    else
    {
      UINT nID = GetMenuItemID(j);
      pItemData = FindMenuList(nID);
      GetMenuString(j,string,MF_BYPOSITION);
      
      if(!pItemData)
      {
        pItemData = NewODMenu(j,state|MF_BYPOSITION|MF_OWNERDRAW,nID,string);
      }
      else
      {
        pItemData->m_nFlags = state|MF_BYPOSITION|MF_OWNERDRAW;
        if(string.GetLength()>0)
        {
          pItemData->SetString(string);
        }
        ModifyMenu(j,pItemData->m_nFlags,nID,(LPCTSTR)pItemData);
      }
    }
    if(pItemData)
    {
      temp.Add(pItemData);
    }
  }
  DeleteMenuList();
  m_MenuItemList.RemoveAll();
  m_MenuItemList.Append(temp);
  temp.RemoveAll(); 
}

void CNewMenu::OnInitMenuPopup(HWND hWnd, CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{ 
  UNREFERENCED_PARAMETER(nIndex);
  UNREFERENCED_PARAMETER(bSysMenu);

#ifdef _TRACE_MENU_
  AfxTrace(_T("InitMenuPopup: 0x%lx from Wnd 0x%lx\n"),HMenuToUInt(pPopupMenu->m_hMenu),HWndToUInt(hWnd));
#endif
  CNewMenuHook::m_hLastMenu = pPopupMenu->m_hMenu;

  if(pPopupMenu->m_hMenu)
  {
    CNewMenu* pSubMenu = DYNAMIC_DOWNCAST(CNewMenu,pPopupMenu);
    if(pSubMenu)
    {
      pSubMenu->m_hTempOwner = hWnd;
      pSubMenu->OnInitMenuPopup();
      HMENU hMenu = pSubMenu->GetParent();
      CNewMenu* pParent = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hMenu));
      if(pParent)
      {
        pParent->m_dwOpenMenu += 1;
        if(pParent->m_dwOpenMenu==1 && !pParent->m_bIsPopupMenu)
        {
          // Redraw the menubar for the shade
          CRect rect = pParent->GetLastActiveMenuRect();
          if(!rect.IsRectEmpty())
          {
            rect.InflateRect(0,0,10,10);
            CPoint Point(0,0);
            ClientToScreen(hWnd,&Point);
            rect.OffsetRect(-Point);
            RedrawWindow(hWnd,rect,0,RDW_FRAME|RDW_INVALIDATE);
          }
        }
      }
    }
  }
}

BOOL CNewMenu::Replace(UINT nID, UINT nNewID)
{
  int nLoc=0;
  CNewMenu* pTempMenu = FindMenuOption(nID,nLoc);
  if(pTempMenu && nLoc >= 0)
  {
#ifdef _TRACE_MENU_
    AfxTrace(_T("Replace MenuID 0x%X => 0x%X\n"),nID,nNewID);
#endif
    CNewMenuItemData* pData = pTempMenu->m_MenuItemList[nLoc];
    UINT nFlags = pData->m_nFlags|MF_OWNERDRAW|MF_BYPOSITION;
    pData->m_nID = nNewID;
    return pTempMenu->ModifyMenu(nLoc,nFlags,nNewID,(LPCTSTR)pData);
  }
  return FALSE;
}

void CNewMenu::OnInitMenuPopup()
{
  m_bIsPopupMenu = true;
  SynchronizeMenu();
  // Special purpose for windows XP with themes!!!
  if(g_Shell==WinXP)
  {
    Replace(SC_RESTORE,SC_RESTORE+1);
    Replace(SC_CLOSE,SC_CLOSE+1);
    Replace(SC_MINIMIZE,SC_MINIMIZE+1);
  }
}

BOOL CNewMenu::OnUnInitPopupMenu()
{
#ifdef _TRACE_MENU_
  AfxTrace(_T("UnInitMenuPopup: 0x%lx\n"),HMenuToUInt(m_hMenu));
#endif
  if(g_Shell==WinXP)
  {
    // Special purpose for windows XP with themes!!!
    // Restore old values otherwise you have disabled windowbuttons
    if(Replace(SC_CLOSE+1,SC_CLOSE))
    {
      //EnableMenuItem(SC_CLOSE, MF_BYCOMMAND|MF_ENABLED);
      SetWindowPos(m_hTempOwner,0,0,0,0,0,SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
    }
    Replace(SC_RESTORE+1,SC_RESTORE);
    Replace(SC_MINIMIZE+1,SC_MINIMIZE);
 }

  HMENU hMenu = GetParent();
  CNewMenu* pParent = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hMenu));
  if(pParent)
  {
    pParent->m_dwOpenMenu -= 1;
    if(pParent->m_dwOpenMenu>=NULL && !pParent->m_bIsPopupMenu)
    {
      pParent->m_dwOpenMenu = 0;
      // Redraw the menubar for the shade
      CRect rect = pParent->GetLastActiveMenuRect();
      if(!rect.IsRectEmpty())
      {
        rect.InflateRect(0,0,10,10);
        CPoint Point(0,0);
        ClientToScreen(m_hTempOwner,&Point);
        rect.OffsetRect(-Point);
        RedrawWindow(m_hTempOwner,rect,0,RDW_FRAME|RDW_INVALIDATE);
      }
      return TRUE;
    }
  }
  return FALSE;
}

LRESULT CNewMenu::FindKeyboardShortcut(UINT nChar, UINT nFlags, CMenu* pMenu)
{
  UNREFERENCED_PARAMETER(nFlags);

  CNewMenu* pNewMenu = DYNAMIC_DOWNCAST(CNewMenu,pMenu);
  if(pNewMenu)
  {
    //SK: modified for Unicode correctness
    CString key(_T('&'),2);
    key.SetAt(1,(TCHAR)nChar);
    key.MakeLower();
    CString menutext;
    int menusize = (int)pNewMenu->GetMenuItemCount();
    if(menusize!=(pNewMenu->m_MenuItemList.GetUpperBound()+1))
    {
      pNewMenu->SynchronizeMenu();
    }
    for(int i=0;i<menusize;++i)
    {
      if(pNewMenu->GetMenuText(i,menutext))
      {
        menutext.MakeLower();
        if(menutext.Find(key)>=0)
        {
          return(MAKELRESULT(i,2));
        }
      }
    }
  }
  return NULL;
}

BOOL CNewMenu::AddBitmapToImageList(CImageList* bmplist,UINT nResourceID)
{
  // O.S.
  if (m_bDynIcons)
  {
    bmplist->Add((HICON)(UINT_PTR)nResourceID);
    return TRUE;
  }

  CBitmap mybmp;
  HBITMAP hbmp = LoadSysColorBitmap(nResourceID);
  if(hbmp)
  {
    // Object will be destroyd by destructor of CBitmap
    mybmp.Attach(hbmp);
  }
  else
  {
    mybmp.LoadBitmap(nResourceID);
  }

  if (mybmp.m_hObject && bmplist->Add(&mybmp,GetBitmapBackground())>=0 )
  {
    return TRUE;
  }

  return FALSE;
}

COLORREF CNewMenu::SetBitmapBackground(COLORREF newColor)
{
  COLORREF oldColor = m_bitmapBackground;
  m_bitmapBackground = newColor;
  return oldColor;
}

COLORREF CNewMenu::GetBitmapBackground()
{
  if(m_bitmapBackground==CLR_DEFAULT)
    return GetSysColor(COLOR_3DFACE);

  return m_bitmapBackground;
}

BOOL CNewMenu::Draw3DCheckmark(CDC *pDC, CRect rect, HBITMAP hbmpChecked, HBITMAP hbmpUnchecked, DWORD dwState)
{
  if(dwState&ODS_CHECKED || hbmpUnchecked)
  {
    rect.InflateRect(-1,-1);

    if (IsNewShell()) //SK: looks better on the old shell
    {
      pDC->DrawEdge(rect, BDR_SUNKENOUTER, BF_RECT);
    }

    rect.InflateRect (2,2);
    if(dwState&ODS_CHECKED)
    {
      if (!hbmpChecked)
      { // Checkmark
        rect.OffsetRect(1,2);
        DrawSpecialCharStyle(pDC,rect,98,dwState);
      }
      else if(!hbmpUnchecked)
      { // Bullet
        DrawSpecialCharStyle(pDC,rect,105,dwState);
      }
      else
      {
        // Draw Bitmap
        BITMAP myInfo = {0};
        GetObject((HGDIOBJ)hbmpChecked,sizeof(myInfo),&myInfo);
        CPoint Offset = rect.TopLeft() + CPoint((rect.Width()-myInfo.bmWidth)/2,(rect.Height()-myInfo.bmHeight)/2);
        pDC->DrawState(Offset,CSize(0,0),hbmpChecked,DST_BITMAP|DSS_MONO);
      }
    }
    else
    {
      // Draw Bitmap
      BITMAP myInfo = {0};
      GetObject((HGDIOBJ)hbmpUnchecked,sizeof(myInfo),&myInfo);
      CPoint Offset = rect.TopLeft() + CPoint((rect.Width()-myInfo.bmWidth)/2,(rect.Height()-myInfo.bmHeight)/2);
      if(dwState & ODS_DISABLED)
      {
        pDC->DrawState(Offset,CSize(0,0),hbmpUnchecked,DST_BITMAP|DSS_MONO|DSS_DISABLED);
      }
      else
      {
        pDC->DrawState(Offset,CSize(0,0),hbmpUnchecked,DST_BITMAP|DSS_MONO);
      }   
    }
    return TRUE;
  }
  return FALSE;
}

HBITMAP CNewMenu::LoadSysColorBitmap(int nResourceId)
{
  HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(nResourceId),RT_BITMAP);
  HRSRC hRsrc = ::FindResource(hInst,MAKEINTRESOURCE(nResourceId),RT_BITMAP);
  if (hRsrc == NULL)
  {
    return NULL;
  }

  // determine how many colors in the bitmap
  HGLOBAL hglb;
  if ((hglb = LoadResource(hInst, hRsrc)) == NULL)
  {
    return NULL;
  }
  LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);
  if (lpBitmap == NULL)
  {
    return NULL;
  }
  WORD numcol = NumBitmapColors(lpBitmap);
  ::FreeResource(hglb);

  if(numcol!=16)
  {
    return(NULL);
  }
  return AfxLoadSysColorBitmap(hInst, hRsrc, FALSE);
}

// sPos means Seperator's position, since we have no way to find the 
// seperator's position in the menu we have to specify them when we call the 
// RemoveMenu to make sure the unused seperators are removed;
// sPos  = None no seperator removal;
//       = Head  seperator in front of this menu item;
//       = Tail  seperator right after this menu item;
//       = Both  seperators at both ends;
// remove the menu item based on their text, return -1 if not found, otherwise 
// return the menu position;
int CNewMenu::RemoveMenu(LPCTSTR pText, ESeperator sPos)
{
  int nPos = GetMenuPosition(pText);
  if(nPos != -1)
  {
    switch (sPos)
    {
    case CNewMenu::NONE:
      RemoveMenu(nPos, MF_BYPOSITION);
      break;

    case CNewMenu::HEAD:
      ASSERT(nPos - 1 >= 0);
      RemoveMenu(nPos-1, MF_BYPOSITION);
      break;

    case CNewMenu::TAIL:
      RemoveMenu(nPos+1, MF_BYPOSITION);
      break;

    case CNewMenu::BOTH:
      // remove the end first;
      RemoveMenu(nPos+1, MF_BYPOSITION);
      // remove the head;
      ASSERT(nPos - 1 >= 0);
      RemoveMenu(nPos-1, MF_BYPOSITION);
      break;
    }
  }
  return nPos;
}

BOOL CNewMenu::RemoveMenu(UINT uiId, UINT nFlags)
{
  if(MF_BYPOSITION&nFlags)
  {
    UINT nItemState = GetMenuState(uiId,MF_BYPOSITION);
    if((nItemState&MF_SEPARATOR) && !(nItemState&MF_POPUP))
    {  
      CNewMenuItemData* pData =  m_MenuItemList.GetAt(uiId);
      m_MenuItemList.RemoveAt(uiId);
      delete pData;
    }
    else
    {
      CMenu* pSubMenu = GetSubMenu(uiId);
      if(NULL==pSubMenu)
      {
        UINT uiCommandId = GetMenuItemID(uiId);
        for(int i=0;i<m_MenuItemList.GetSize(); i++)
        {
          if(m_MenuItemList[i]->m_nID==uiCommandId)
          {
            CNewMenuItemData* pData = m_MenuItemList.GetAt(i);
            m_MenuItemList.RemoveAt(i);
            delete pData;
            break;
          }
        }
      }
      else
      {
        // Only remove the menu.
        int numSubMenus = (int)m_SubMenus.GetUpperBound();
        for(int m = numSubMenus; m >= 0; m--)
        {
          if(m_SubMenus[m]==pSubMenu->m_hMenu)
          {
            m_SubMenus.RemoveAt(m);
          }
        }
//        int num = pSubMenu->GetMenuItemCount();
//        for(int i=num-1;i>=0;--i)
//        {
//          pSubMenu->RemoveMenu(i,MF_BYPOSITION);
//        }
        for(int i=(int)m_MenuItemList.GetUpperBound();i>=0;i--)
        {
          if(m_MenuItemList[i]->m_nID==HMenuToUInt(pSubMenu->m_hMenu) )
          {
            CNewMenuItemData* pData = m_MenuItemList.GetAt(i);
            m_MenuItemList.RemoveAt(i);
            delete pData;
            break;
          }
        }
        // Don't delete it's only remove
        //delete pSubMenu;
      }
    }
  }
  else
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(uiId,iPosition);
    if(pMenu)
    {
      return pMenu->RemoveMenu(iPosition,MF_BYPOSITION);
    }
  }
  return CMenu::RemoveMenu(uiId,nFlags);
}

BOOL CNewMenu::DeleteMenu(UINT uiId, UINT nFlags)
{
  if(MF_BYPOSITION&nFlags)
  {
    UINT nItemState = GetMenuState(uiId,MF_BYPOSITION);
    if( (nItemState&MF_SEPARATOR) && !(nItemState&MF_POPUP))
    {
      CNewMenuItemData* pData = m_MenuItemList.GetAt(uiId);
      m_MenuItemList.RemoveAt(uiId);
      delete pData;
    }
    else
    {
      CMenu* pSubMenu = GetSubMenu(uiId);
      if(NULL==pSubMenu)
      {
        UINT uiCommandId = GetMenuItemID(uiId);
        for(int i=0;i<m_MenuItemList.GetSize(); i++)
        {
          if(m_MenuItemList[i]->m_nID==uiCommandId)
          {
            CNewMenuItemData* pData = m_MenuItemList.GetAt(i);
            m_MenuItemList.RemoveAt(i);
            delete pData;
          }
        }
      }
      else
      {
        BOOL bCanDelete = FALSE;
        int numSubMenus = (int)m_SubMenus.GetUpperBound();
        for(int m = numSubMenus; m >= 0; m--)
        {
          if(m_SubMenus[m]==pSubMenu->m_hMenu)
          {
            m_SubMenus.RemoveAt(m);
            bCanDelete = TRUE;
          }
        }
//        int num = pSubMenu->GetMenuItemCount();
//        for(int i=num-1;i>=0;--i)
//        {
//          pSubMenu->DeleteMenu(i,MF_BYPOSITION);
//        }
        for(int i=(int)m_MenuItemList.GetUpperBound();i>=0;i--)
        {
          if(m_MenuItemList[i]->m_nID==HMenuToUInt(pSubMenu->m_hMenu) )
          {
            CNewMenuItemData* pData = m_MenuItemList.GetAt(i);
            m_MenuItemList.RemoveAt(i);
            delete pData;
            break;
          }
        }
        // Did we created the menu
        if(bCanDelete)
        { // Oh yes so we can destroy it
          delete pSubMenu;
        }
      }
    }
  }
  else
  {
    int iPosition =0;
    CNewMenu* pMenu = FindMenuOption(uiId,iPosition);
    if(pMenu)
    {
      return pMenu->DeleteMenu(iPosition,MF_BYPOSITION);
    }
  }
  return CMenu::DeleteMenu(uiId,nFlags);
} 

BOOL CNewMenu::AppendMenu(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, int nIconNormal)
{
  return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,nIconNormal);
}

BOOL CNewMenu::AppendMenu(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, CImageList* il, int xoffset)
{
  return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,il,xoffset);
}

BOOL CNewMenu::AppendMenu(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, CBitmap* bmp)
{
  return AppendODMenu(lpszNewItem,nFlags,nIDNewItem,bmp);
}

BOOL CNewMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, int nIconNormal)
{
  return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,nIconNormal);
}

BOOL CNewMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, CImageList* il, int xoffset)
{
  return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,il,xoffset);
}

BOOL CNewMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, CBitmap* bmp)
{
  return InsertODMenu(nPosition,lpszNewItem,nFlags,nIDNewItem,bmp);
}

CNewMenu* CNewMenu::AppendODPopupMenu(LPCTSTR lpstrText)
{
  CNewMenu* pSubMenu = new CNewMenu(m_hMenu);
  pSubMenu->m_unselectcheck=m_unselectcheck;
  pSubMenu->m_selectcheck=m_selectcheck;
  pSubMenu->m_checkmaps=m_checkmaps;
  pSubMenu->m_checkmapsshare=TRUE;
  pSubMenu->CreatePopupMenu();
  if(AppendODMenu(lpstrText,MF_POPUP,HMenuToUInt(pSubMenu->m_hMenu), -1))
  {
    m_SubMenus.Add(pSubMenu->m_hMenu);
    return pSubMenu;
  }
  delete pSubMenu;
  return NULL;
}

CMenu* CNewMenu::GetSubMenu(int nPos) const
{
  return CMenu::GetSubMenu (nPos);
}

CMenu* CNewMenu::GetSubMenu(LPCTSTR lpszSubMenuName) const
{
  int num = GetMenuItemCount ();
  CString name;
  MENUITEMINFO info = {0};

  for (int i=0; i<num; i++)
  {
    GetMenuString (i, name, MF_BYPOSITION); 
    // fix from George Menhorn
    if(name.IsEmpty())
    {
      info.cbSize = sizeof (MENUITEMINFO);
      info.fMask = MIIM_DATA;
      ::GetMenuItemInfo(m_hMenu, i, TRUE, &info);

      CNewMenuItemData* pItemData = CheckMenuItemData(info.dwItemData);
      if (pItemData)
      {
        name = pItemData->GetString();
      }
    }

    if (name.Compare (lpszSubMenuName) == 0)
    {
      return CMenu::GetSubMenu (i);
    }
  }
  return NULL;
}

// Tongzhe Cui, Functions to remove a popup menu based on its name. Seperators
// before and after the popup menu can also be removed if they exist.
int CNewMenu::GetMenuPosition(LPCTSTR pText)
{
  for(int i=0;i<(int)(GetMenuItemCount());++i)
  {
    if(!GetSubMenu(i))
    { 
      for(int j=0;j<=m_MenuItemList.GetUpperBound();++j)
      {  
        if(m_MenuItemList[j]->m_szMenuText.Compare(pText)==NULL)
        {
          return j;
        }
      }
    }
  }
  // means no found;
  return -1;
}

BOOL CNewMenu::RemoveMenuTitle()
{
  int numMenuItems = (int)m_MenuItemList.GetSize();

  // We need a seperator at the beginning of the menu
  if(!numMenuItems || !((m_MenuItemList[0]->m_nFlags)&MF_SEPARATOR) )
  {
    return FALSE;
  }
  CNewMenuItemData* pMenuData = m_MenuItemList[0];
  // Check for title
  if(pMenuData->m_nTitleFlags&MFT_TITLE)
  {
    if(numMenuItems>0)
    {
      CNewMenuItemData* pMenuNextData = m_MenuItemList[1];
      if((pMenuNextData->m_nFlags&MF_MENUBREAK))
      {
        pMenuNextData->m_nFlags &= ~MF_MENUBREAK;
        CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuNextData->m_nFlags,pMenuNextData->m_nID,(LPCTSTR)pMenuNextData);
      }
    }
    // Now remove the title
    RemoveMenu(0,MF_BYPOSITION);
    return TRUE;
  }
  return FALSE;
} 

BOOL CNewMenu::SetMenuTitle(LPCTSTR pTitle, UINT nTitleFlags)
{
  // Check if menu is valid
  if(!::IsMenu(m_hMenu))
  {
    return FALSE;
  }

  // Check the menu integrity
  if((int)GetMenuItemCount()!=(int)m_MenuItemList.GetSize())
  {
    SynchronizeMenu();
  }

  int numMenuItems = (int)m_MenuItemList.GetSize();

  // We need a seperator at the beginning of the menu
  if(!numMenuItems || !((m_MenuItemList[0]->m_nFlags)&MF_SEPARATOR) )
  {
    InsertMenu(0,MF_SEPARATOR|MF_BYPOSITION);
  }

  numMenuItems = (int)m_MenuItemList.GetSize();
  if(numMenuItems)
  {
    CNewMenuItemData* pMenuData = m_MenuItemList[0];
    if(pMenuData->m_nFlags&MF_SEPARATOR)
    {
      pMenuData->SetString(pTitle);
      pMenuData->m_nTitleFlags = nTitleFlags|MFT_TITLE;

      if(numMenuItems>1)
      {
        CNewMenuItemData* pMenuData = m_MenuItemList[1];

        if(nTitleFlags&MFT_SIDE_TITLE)
        {
          if(!(pMenuData->m_nFlags&MF_MENUBREAK))
          {
            pMenuData->m_nFlags |= MF_MENUBREAK;
            CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuData->m_nFlags,pMenuData->m_nID,(LPCTSTR)pMenuData);
          }
        }
        else
        {
          if((pMenuData->m_nFlags&MF_MENUBREAK))
          {
            pMenuData->m_nFlags &= ~MF_MENUBREAK;
            CMenu::ModifyMenu(1,MF_BYPOSITION|pMenuData->m_nFlags,pMenuData->m_nID,(LPCTSTR)pMenuData);
          }
        }
        return TRUE;
      }
    }
  }
  return FALSE;
}

BOOL CNewMenu::SetMenuText(UINT id, CString string, UINT nFlags/*= MF_BYPOSITION*/ )
{
  if(MF_BYPOSITION&nFlags)
  {
    int numMenuItems = (int)m_MenuItemList.GetSize();
    if(id<UINT(numMenuItems))
    {
      // get current menu state so it doesn't change
      UINT nState = GetMenuState(id, MF_BYPOSITION);
      nState &= ~(MF_BITMAP|MF_OWNERDRAW|MF_SEPARATOR);
      // change the menutext
      CNewMenuItemData* pItemData = m_MenuItemList[id];
      pItemData->SetString(string);
      
      if(CMenu::ModifyMenu(id,MF_BYPOSITION|MF_STRING | nState, pItemData->m_nID, string))
      {
        return ModifyMenu(id,MF_BYPOSITION | MF_OWNERDRAW,pItemData->m_nID,(LPCTSTR)pItemData);
      }
    }
  }
  else
  {
    int uiLoc;
    CNewMenu* pMenu = FindMenuOption(id,uiLoc);
    if(NULL!=pMenu)
    {
      return pMenu->SetMenuText(uiLoc,string);
    }
  }
  return FALSE;
}

// courtesy of Warren Stevens
void CNewMenu::ColorBitmap(CDC* pDC, CBitmap& bmp, CSize size, COLORREF fill, COLORREF border, int hatchstyle)
{
  // Create a memory DC
  CDC MemDC;
  MemDC.CreateCompatibleDC(pDC);  
  bmp.CreateCompatibleBitmap(pDC, size.cx, size.cy);  
  CPen border_pen(PS_SOLID, 1, border);

  CBrush fill_brush;
  if(hatchstyle!=-1) 
  { 
    fill_brush.CreateHatchBrush(hatchstyle, fill); 
  }
  else 
  {
    fill_brush.CreateSolidBrush(fill);
  }

  CBitmap* pOldBitmap = MemDC.SelectObject(&bmp);
  CPen*    pOldPen    = MemDC.SelectObject(&border_pen);
  CBrush*  pOldBrush  = MemDC.SelectObject(&fill_brush);

  MemDC.Rectangle(0,0, size.cx, size.cy);

  if(NULL!=pOldBrush)  { MemDC.SelectObject(pOldBrush);  }
  if(NULL!=pOldPen)    { MemDC.SelectObject(pOldPen);    }
  if(NULL!=pOldBitmap) { MemDC.SelectObject(pOldBitmap); }
}

void CNewMenu::DrawSpecial_OldStyle(CDC* pDC, LPCRECT pRect, UINT nID, DWORD dwStyle)
{
  COLORREF oldColor;
  if( (dwStyle&ODS_GRAYED) || (dwStyle&ODS_INACTIVE))
  {
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
  }
  else if (dwStyle&ODS_SELECTED)
  { 
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
  }
  else
  {
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
  }
  BOOL bBold = (dwStyle&ODS_DEFAULT) ? TRUE : FALSE;

  switch(nID&0xfff0)
  {
  case SC_MINIMIZE:
    DrawSpecialChar(pDC,pRect,48,bBold); // Min
    break;
  case SC_MAXIMIZE:
    DrawSpecialChar(pDC,pRect,49,bBold); // Max
    break;
  case SC_CLOSE:
    DrawSpecialChar(pDC,pRect,114,bBold); // Close
    break;
  case SC_RESTORE:
    DrawSpecialChar(pDC,pRect,50,bBold); // restore
    break;
  }
  pDC->SetTextColor(oldColor);
}

void CNewMenu::DrawSpecial_WinXP(CDC* pDC, LPCRECT pRect, UINT nID, DWORD dwStyle)
{
  TCHAR cSign = 0;
  switch(nID&0xfff0)
  {
  case SC_MINIMIZE:
    cSign = 48; // Min
    break;
  case SC_MAXIMIZE:
    cSign = 49;// Max
    break;
  case SC_CLOSE:
    cSign = 114;// Close
    break;
  case SC_RESTORE:
    cSign = 50;// Restore
    break;
  }
  if(cSign)
  {
    COLORREF oldColor;
    BOOL bBold = (dwStyle&ODS_DEFAULT) ? TRUE : FALSE;
    CRect rect(pRect);
    rect.InflateRect(0,(m_iconY-rect.Height())>>1);


    if( (dwStyle&ODS_GRAYED) || (dwStyle&ODS_INACTIVE))
    {
      oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
    }
    else if(dwStyle&ODS_SELECTED)
    {       
      oldColor = pDC->SetTextColor(DarkenColorXP(GetXpHighlightColor()));
      rect.OffsetRect(1,1);
      DrawSpecialChar(pDC,rect,cSign,bBold);
      pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
      rect.OffsetRect(-2,-2);
    }
    else
    { 
      oldColor = pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
    }
    DrawSpecialChar(pDC,rect,cSign,bBold);

    pDC->SetTextColor(oldColor);
  }
}

CRect CNewMenu::GetLastActiveMenuRect()
{
  return m_LastActiveMenuRect;
}

void CNewMenu::DrawSpecialCharStyle(CDC* pDC, LPCRECT pRect, TCHAR Sign, DWORD dwStyle)
{
  COLORREF oldColor;
  if( (dwStyle&ODS_GRAYED) || (dwStyle&ODS_INACTIVE))
  {
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
  }
  else
  { 
    oldColor = pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
  }

  DrawSpecialChar(pDC,pRect,Sign,(dwStyle&ODS_DEFAULT) ? TRUE : FALSE);

  pDC->SetTextColor(oldColor);
}

void CNewMenu::DrawSpecialChar(CDC* pDC, LPCRECT pRect, TCHAR Sign, BOOL bBold)
{
  //  48 Min
  //  49 Max
  //  50 Restore
  //  98 Checkmark 
  // 105 Bullet
  // 114 Close

  CFont MyFont;
  LOGFONT logfont;

  CRect rect(pRect) ;
  rect.DeflateRect(2,2);

  logfont.lfHeight = -rect.Height();
  logfont.lfWidth = 0;
  logfont.lfEscapement = 0;
  logfont.lfOrientation = 0;
  logfont.lfWeight = (bBold) ? FW_BOLD:FW_NORMAL;
  logfont.lfItalic = FALSE;
  logfont.lfUnderline = FALSE;
  logfont.lfStrikeOut = FALSE;
  logfont.lfCharSet = DEFAULT_CHARSET;
  logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
  logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  logfont.lfQuality = DEFAULT_QUALITY;
  logfont.lfPitchAndFamily = DEFAULT_PITCH;

  _tcscpy(logfont.lfFaceName,_T("Marlett"));

  MyFont.CreateFontIndirect (&logfont);

  CFont* pOldFont = pDC->SelectObject (&MyFont); 
  int OldMode = pDC->SetBkMode(TRANSPARENT);  

  pDC->DrawText (&Sign,1,rect,DT_CENTER|DT_SINGLELINE);

  pDC->SetBkMode(OldMode);
  pDC->SelectObject(pOldFont);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuTheme::CMenuTheme()
{ 
  ZeroMemory(this,sizeof(CMenuTheme));
}

CMenuTheme::CMenuTheme( DWORD dwThemeId, 
                        pItemMeasureFkt pMeasureItem,
                        pItemDrawFkt pDrawItem,
                        pItemDrawFkt pDrawTitle,
                        DWORD dwFlags)
  :m_dwThemeId(dwThemeId),
    m_dwFlags(dwFlags),
    m_pMeasureItem(pMeasureItem),
    m_pDrawItem(pDrawItem),
    m_pDrawTitle(pDrawTitle)
{
  m_BorderTopLeft = CSize(2,2);

  if(!IsShadowEnabled())
  {
    m_BorderBottomRight = CSize(5,6);
  }
  else
  {
    m_BorderBottomRight = CSize(2,2);
  }
}

CMenuTheme::~CMenuTheme()
{
}

void CMenuTheme::DrawFrame(CDC* pDC, CRect rectOuter, CRect rectInner, COLORREF crBorder)
{
  CRect Temp;
  rectInner.right -= 1;
  // Border top
  Temp.SetRect(rectOuter.TopLeft(),CPoint(rectOuter.right,rectInner.top));
  pDC->FillSolidRect(Temp,crBorder);
  // Border bottom
  Temp.SetRect(CPoint(rectOuter.left,rectInner.bottom),rectOuter.BottomRight());
  pDC->FillSolidRect(Temp,crBorder);

  // Border left
  Temp.SetRect(rectOuter.TopLeft(),CPoint(rectInner.left,rectOuter.bottom));
  pDC->FillSolidRect(Temp,crBorder);
  // Border right
  Temp.SetRect(CPoint(rectInner.right,rectOuter.top),rectOuter.BottomRight());
  pDC->FillSolidRect(Temp,crBorder);
}

BOOL CMenuTheme::DoDrawBorder()
{
  return (m_dwFlags&1)?TRUE:FALSE;
}

void CMenuTheme::DrawSmalBorder( HWND hWnd, HDC hDC)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(pData!=NULL)
  {
    if(pData->m_hMenu)
    {   
      CNewMenu* pMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(pData->m_hMenu));
      if(pMenu && pMenu->GetParent())
      {
        CNewMenu* pParentMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(pMenu->GetParent()));
        if(pParentMenu && !pParentMenu->IsPopup())
        {
          CRect Rect;
          // Get the size of the menu... 
          GetWindowRect(hWnd, Rect );
          Rect.OffsetRect(pData->m_Point - Rect.TopLeft());
          Rect &= pParentMenu->GetLastActiveMenuRect();
          if(!Rect.IsRectEmpty())
          {
            if(Rect.Width()>Rect.Height())
            {
              Rect.InflateRect(-1,0);
            }
            else
            {
              Rect.InflateRect(0,-1);
            }
            Rect.OffsetRect(-pData->m_Point);
            CDC* pDC = CDC::FromHandle(hDC);
           
            COLORREF colorSmalBorder;
            if (NumScreenColors() > 256) 
            {
              colorSmalBorder = MixedColor(CNewMenu::GetMenuBarColor(),GetSysColor(COLOR_WINDOW));
            }
            else
            {
              colorSmalBorder = GetSysColor(COLOR_BTNFACE);
            }
            pDC->FillSolidRect(Rect,colorSmalBorder);
          }
        }
      }
    }
  }
}

void CMenuTheme::DrawShade( HWND hWnd, HDC hDC, CPoint screen)
{ 
  if(IsShadowEnabled())
    return;

  // Get the size of the menu... 
  CRect Rect;
  GetWindowRect(hWnd, Rect );

  long winW = Rect.Width(); 
  long winH = Rect.Height(); 
  long xOrg = screen.x;  
  long yOrg = screen.y;

  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);

  CDC* pDC = CDC::FromHandle(hDC);
  CDC memDC;
  memDC.CreateCompatibleDC(pDC);
  CBitmap* pOldBitmap = memDC.SelectObject(&pData->m_Screen);

  HDC hDcDsk = memDC.m_hDC;
  xOrg = 0;  
  yOrg = 0;

  //// Get the desktop hDC... 
  //HDC hDcDsk = GetWindowDC(0) ;
  
  int X,Y;
  // Simulate a shadow on right edge... 
  if (NumScreenColors() <= 256) 
  {
    DWORD rgb = ::GetSysColor(COLOR_BTNSHADOW);
    BitBlt(hDC,winW-2,0,    2,winH,hDcDsk,xOrg+winW-2,0,SRCCOPY);
    BitBlt(hDC,0,winH-2,winW,2,hDcDsk,0,yOrg+winH-2,SRCCOPY);
    for (X=3; X<=4 ;X++)
    { 
      for (Y=0; Y<4 ;Y++)
      {
        SetPixel(hDC,winW-X,Y,GetPixel(hDcDsk,xOrg+winW-X,yOrg+Y));
      }
      for (Y=4; Y<8 ;Y++)
      {
        SetPixel(hDC,winW-X,Y,rgb) ;
      }
      for (Y=8; Y<=(winH-5) ;Y++)
      {
        SetPixel( hDC, winW - X, Y, rgb);
      }
      for (Y=(winH-4); Y<=(winH-3) ;Y++)
      {
        SetPixel( hDC, winW - X, Y, rgb);
      }
    }
    // Simulate a shadow on the bottom edge... 
    for(Y=3; Y<=4 ;Y++)
    {
      for(X=0; X<=3 ;X++)
      {
        SetPixel(hDC,X,winH-Y, GetPixel(hDcDsk,xOrg+X,yOrg+winH-Y)) ;
      }
      for(X=4; X<=7 ;X++)
      {
        SetPixel( hDC, X, winH - Y, rgb) ;
      }
      for(X=8; X<=(winW-5) ;X++)
      {
        SetPixel( hDC, X, winH - Y, rgb) ;
      }
    }
  }
  else 
  {
    for (X=1; X<=4 ;X++)
    { 
      for (Y=0; Y<4 ;Y++)
      {
        SetPixel(hDC,winW-X,Y, GetPixel(hDcDsk,xOrg+winW-X,yOrg+Y) );
      }
      for (Y=4; Y<8 ;Y++)
      {
        COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
        SetPixel(hDC,winW-X,Y,DarkenColor(2* 3 * X * (Y - 3), c)) ;
      }
      for (Y=8; Y<=(winH-5) ;Y++)
      {
        COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
        SetPixel( hDC, winW - X, Y, DarkenColor(2* 15 * X, c) );
      }
      for (Y=(winH-4); Y<=(winH-1) ;Y++)
      {
        COLORREF c = GetPixel(hDcDsk, xOrg + winW - X, yOrg + Y) ;
        SetPixel( hDC, winW - X, Y, DarkenColor(2* 3 * X * -(Y - winH), c)) ;
      }
    } 

    // Simulate a shadow on the bottom edge... 
    for(Y=1; Y<=4 ;Y++)
    {
      for(X=0; X<=3 ;X++)
      {
        SetPixel(hDC,X,winH-Y, GetPixel(hDcDsk,xOrg+X,yOrg+winH-Y)) ;
      }
      for(X=4; X<=7 ;X++)
      {
        COLORREF c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y) ;
        SetPixel( hDC, X, winH - Y, DarkenColor(2*3 * (X - 3) * Y, c)) ;
      }
      for(X=8; X<=(winW-5) ;X++)
      {
        COLORREF  c = GetPixel(hDcDsk, xOrg + X, yOrg + winH - Y); 
        SetPixel( hDC, X, winH - Y, DarkenColor(2* 15 * Y, c)) ;
      }
    }
  }

  memDC.SelectObject(pOldBitmap);

  //// Release the desktop hDC... 
  //ReleaseDC(0,hDcDsk);
}

BOOL CMenuTheme::OnInitWnd(HWND hWnd)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  ASSERT(pData);
  if( pData->m_bDoSubclass && DoDrawBorder())
  {
    // Flag for changing styles
    pData->m_dwData |= 2;

    SetWindowLong (hWnd, GWL_STYLE, pData->m_dwStyle & (~WS_BORDER) );
    SetWindowLong (hWnd, GWL_EXSTYLE,pData->m_dwExStyle & ~(WS_EX_WINDOWEDGE|WS_EX_DLGMODALFRAME));
    return TRUE;
  }
  return FALSE;
}

BOOL CMenuTheme::OnUnInitWnd(HWND hWnd)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(pData)
  {
    HMENU hMenu = pData->m_hMenu;
    CNewMenu* pNewMenu = DYNAMIC_DOWNCAST(CNewMenu,CMenu::FromHandlePermanent(hMenu));

    if(pNewMenu)
    {
      // Redraw menubar on place.
      pNewMenu->OnUnInitPopupMenu();
    }
    // were windows-style changed?
    if(pData->m_dwData&2)
    {
      SetLastError(0);
      if(!(pData->m_dwData&1))
      {
        SetWindowLong (hWnd, GWL_STYLE,pData->m_dwStyle);
      }
      else
      {
        // Restore old Styles for special menu!! 
        // (Menu 0x10012!!!) special VISIBLE flag must be set
        SetWindowLong (hWnd, GWL_STYLE,pData->m_dwStyle|WS_VISIBLE);
      }

      ShowLastError();
      SetWindowLong (hWnd, GWL_EXSTYLE, pData->m_dwExStyle);
      ShowLastError();
      // Normaly when you change the style you shold call next function
      // but in this case you would lose the focus for the menu!!
      //SetWindowPos(hWnd,0,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED|SWP_HIDEWINDOW);
    }
  }
  return TRUE;
}

BOOL CMenuTheme::OnEraseBkgnd(HWND hWnd, HDC hDC)
{
  //  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);

  //  Get the size of the menu... 
  CDC* pDC = CDC::FromHandle (hDC);
  CRect Rect;
  GetClientRect(hWnd, Rect );
  if(DoDrawBorder())
    Rect.InflateRect(+2,0,-1,0);
  else
    Rect.InflateRect(+2,0,0,0);

  pDC->FillSolidRect (Rect,GetSysColor(COLOR_MENU));

  return TRUE;
}

BOOL CMenuTheme::OnWindowPosChanging(HWND hWnd, LPWINDOWPOS pPos)
{
  UNREFERENCED_PARAMETER(hWnd);

  if(DoDrawBorder())
  {
  #ifdef _TRACE_MENU_
    AfxTrace(_T("WindowPosChanging hwnd=0x%lX, (%ld,%ld)(%ld,%ld)\n"),hWnd,pPos->x,pPos->y,pPos->cx,pPos->cy);
  #endif

    if(!IsShadowEnabled())
    {
      pPos->cx +=2;
      pPos->cy +=2;
    }
    else
    {
      pPos->cx -=2;
      pPos->cy -=2;
    }
    pPos->y -=1;

  #ifdef _TRACE_MENU_
    AfxTrace(_T("WindowPosChanged  hwnd=0x%lX, (%ld,%ld)(%ld,%ld)\n"),hWnd,pPos->x,pPos->y,pPos->cx,pPos->cy);
  #endif

    return TRUE;
  }
  return FALSE;
}

BOOL CMenuTheme::OnNcCalcSize(HWND hWnd, NCCALCSIZE_PARAMS* pCalc)
{
  UNREFERENCED_PARAMETER(hWnd);

  if(DoDrawBorder())
  {
   #ifdef _TRACE_MENU_
    AfxTrace(_T("OnNcCalcSize 0 hwnd=0x%lX, (top=%ld,bottom=%ld,left=%ld,right=%ld)\n"),hWnd,pCalc->rgrc->top,pCalc->rgrc->bottom,pCalc->rgrc->left,pCalc->rgrc->right);
   #endif

    int cx=0,cy=0;
    if(!IsShadowEnabled())
    {
      cx = 5;
      cy = 6;
    }
    else
    {
      cy = cx = 2;
    }

    pCalc->rgrc->top  += m_BorderTopLeft.cy;
    pCalc->rgrc->left += m_BorderTopLeft.cx;
    pCalc->rgrc->bottom -= cy;
    pCalc->rgrc->right  -= cx;

   #ifdef _TRACE_MENU_
    AfxTrace(_T("OnNcCalcSize 0 hwnd=0x%lX, (top=%ld,bottom=%ld,left=%ld,right=%ld)\n"),hWnd,pCalc->rgrc->top,pCalc->rgrc->bottom,pCalc->rgrc->left,pCalc->rgrc->right);
    AfxTrace(_T("OnNcCalcSize 2 hwnd=0x%lX, (top=%ld,bottom=%ld,left=%ld,right=%ld)\n"),hWnd,pCalc->rgrc[2].top,pCalc->rgrc[2].bottom,pCalc->rgrc[2].left,pCalc->rgrc[2].right);
   #endif
 }
  return FALSE;
}

BOOL CMenuTheme::OnCalcFrameRect(HWND hWnd,LPRECT pRect)
{
  if(GetWindowRect(hWnd,pRect))
  {
    if(DoDrawBorder())
    {
      pRect->top += 2;
      pRect->left += 2;
      if(!IsShadowEnabled())
      {
        pRect->bottom -= 7;
        pRect->right -= 7;
      }
      else
      {
        pRect->bottom -= 3;
        pRect->right -= 3;
      }
    }
    return TRUE;
  }
  return FALSE;
}

void* CMenuTheme::SetScreenBitmap(HWND hWnd, HDC hDC)
{
  UNREFERENCED_PARAMETER(hDC);

  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(pData->m_Screen.m_hObject==NULL)
  {
    // Get the desktop hDC... 
    HDC hDcDsk = GetWindowDC(0) ;
    CDC* pDcDsk = CDC::FromHandle(hDcDsk);

    CDC dc;
    dc.CreateCompatibleDC(pDcDsk);

    CRect rect;
    GetWindowRect(hWnd,rect);
    pData->m_Screen.CreateCompatibleBitmap(pDcDsk,rect.Width()+10,rect.Height()+10);
    CBitmap* pOldBitmap = dc.SelectObject(&pData->m_Screen);
    dc.BitBlt(0,0,rect.Width()+10,rect.Height()+10,pDcDsk,pData->m_Point.x,pData->m_Point.y,SRCCOPY);

    dc.SelectObject(pOldBitmap);
    // Release the desktop hDC...
    ReleaseDC(0,hDcDsk);
  }
  return pData;
}


BOOL CMenuTheme::OnDrawBorder(HWND hWnd, HDC hDC, BOOL bOnlyBorder)
{
  CNewMenuHook::CMenuHookData* pData = (CNewMenuHook::CMenuHookData*)SetScreenBitmap(hWnd,hDC);
  if(DoDrawBorder() && pData)
  {
    CRect rect;
    CRect client;
    CDC* pDC = CDC::FromHandle (hDC);

    // Get the size of the menu... 
    GetWindowRect(hWnd, rect );
    GetClientRect(hWnd, client);
    CPoint offset(0,0);
    ClientToScreen(hWnd,&offset);
    client.OffsetRect(offset-rect.TopLeft());

    long winW = rect.Width(); 
    long winH = rect.Height(); 

    if(!IsShadowEnabled())
    {
      if(!bOnlyBorder)
      {
        DrawFrame(pDC,CRect(CPoint(1,1),CSize(winW-6,winH-6)),client,CNewMenu::GetMenuColor());
      }
      if(bHighContrast)
      {
        pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-4,winH-4)),GetSysColor(COLOR_BTNTEXT ),GetSysColor(COLOR_BTNTEXT ));
      }
      else
      {
        pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-4,winH-4)),GetSysColor(COLOR_HIGHLIGHT),GetSysColor(COLOR_HIGHLIGHT));
        DrawShade(hWnd,hDC,pData->m_Point); 
      }
    }
    else
    {
      if(!bOnlyBorder)
      {
        DrawFrame(pDC,CRect(CPoint(1,1),CSize(winW-2,winH-2)),client,CNewMenu::GetMenuColor());
        //pDC->FillSolidRect(winW-2,2,2,winH-2,RGB(0,0,255));
      }

      if(bHighContrast)
      {
        pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-0,winH-0)),GetSysColor(COLOR_BTNTEXT ),GetSysColor(COLOR_BTNTEXT ));
      }
      else
      {
        pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-0,winH-0)),GetSysColor(COLOR_HIGHLIGHT),GetSysColor(COLOR_HIGHLIGHT));
      }
    }
    //DrawSmalBorder(hWnd,hDC);
    return TRUE;
  }
  return FALSE;
}

CMenuThemeXP::CMenuThemeXP(DWORD dwThemeId, 
                           pItemMeasureFkt pMeasureItem,
                           pItemDrawFkt pDrawItem,
                           pItemDrawFkt pDrawTitle,
                           DWORD dwFlags)
:CMenuTheme(dwThemeId,pMeasureItem,pDrawItem,pDrawTitle,dwFlags)
{
}

BOOL CMenuThemeXP::OnDrawBorder(HWND hWnd, HDC hDC, BOOL bOnlyBorder)
{
  CNewMenuHook::CMenuHookData* pData = (CNewMenuHook::CMenuHookData*)SetScreenBitmap(hWnd,hDC);;
  if(DoDrawBorder() && pData)
  {
    CRect rect;
    CRect client;
    CDC* pDC = CDC::FromHandle (hDC);

    // Get the size of the menu... 
    GetWindowRect(hWnd, rect );
    GetClientRect(hWnd,client);
    CPoint offset(0,0);
    ClientToScreen(hWnd,&offset);
    client.OffsetRect(offset-rect.TopLeft());

    long winW = rect.Width(); 
    long winH = rect.Height(); 

    // Same Color as in DrawItem_WinXP
    COLORREF crMenuBar = CNewMenu::GetMenuColor(pData->m_hMenu);
    COLORREF crWindow = GetSysColor(COLOR_WINDOW);
    COLORREF crThinBorder = MixedColor(crWindow,crMenuBar);
    COLORREF clrBorder = DarkenColor(128,crMenuBar);
    COLORREF colorBitmap;

    if (NumScreenColors() > 256) 
    {
      colorBitmap = MixedColor(crMenuBar,crWindow);
    }
    else
    {
      colorBitmap = GetSysColor(COLOR_BTNFACE);
    }

    // Better contrast when you have less than 256 colors
    if(pDC->GetNearestColor(crThinBorder)==pDC->GetNearestColor(colorBitmap))
    {
      crThinBorder = crWindow;
      colorBitmap = crMenuBar;
    } 

    if(!IsShadowEnabled())
    {
      if(!bOnlyBorder)
      {
        DrawFrame(pDC,CRect(CPoint(1,1),CSize(winW-6,winH-6)),client,crThinBorder);
      }
      
      if(bHighContrast)
      {
        pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-4,winH-4)),GetSysColor(COLOR_BTNTEXT),GetSysColor(COLOR_BTNTEXT));
      }
      else
      { 
        pDC->Draw3dRect(CRect(CPoint(1,1),CSize(winW-6,winH-6)),crThinBorder,crThinBorder);
        pDC->FillSolidRect(1,2,1,winH-8,colorBitmap);
        pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-4,winH-4)),clrBorder,clrBorder);

        DrawShade(hWnd,pDC->m_hDC,pData->m_Point);
      }
    }
    else
    {
      if(!bOnlyBorder)
      {
        DrawFrame(pDC,CRect(CPoint(1,1),CSize(winW-2,winH-2)),client,crThinBorder);
      }

      if(bHighContrast)
      {
        pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-0,winH-0)),GetSysColor(COLOR_BTNTEXT ),GetSysColor(COLOR_BTNTEXT ));
      }
      else
      { 
        pDC->Draw3dRect(CRect(CPoint(1,1),CSize(winW-2,winH-2)),crThinBorder,crThinBorder);
        pDC->FillSolidRect(1,2,1,winH-4,colorBitmap);
        pDC->Draw3dRect(CRect(CPoint(0,0),CSize(winW-0,winH-0)),clrBorder,clrBorder);
      }
    }
    DrawSmalBorder(hWnd,pDC->m_hDC);

    return TRUE;
  }
  return FALSE;
}

BOOL CMenuThemeXP::OnEraseBkgnd(HWND hWnd, HDC hDC)
{
  CNewMenuHook::CMenuHookData* pData = CNewMenuHook::GetMenuHookData(hWnd);
  if(pData->m_hMenu==NULL)
  {
    return CMenuTheme::OnEraseBkgnd(hWnd,hDC);
  }
 
  //  Get the size of the menu... 
  CDC* pDC = CDC::FromHandle (hDC);
  CRect Rect;
  GetClientRect(hWnd, Rect );
  if(DoDrawBorder())
    Rect.InflateRect(+2,0,-1,0);
  else
    Rect.InflateRect(+2,0,0,0);
  
  //BPO!!!!!!!!!!  fehler Zeichnet auch in den rand hinein 2
  //pDC->FillSolidRect (Rect,CNewMenu::GetMenuColor());
  pDC->FillSolidRect (Rect,CNewMenu::GetMenuBarColor(pData->m_hMenu));

  return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const TCHAR _OldMenuProc[] = _T("OldMenuProc");

HMODULE CNewMenuHook::m_hLibrary = NULL;
HMODULE CNewMenuHook::m_hThemeLibrary = NULL;
HHOOK CNewMenuHook::HookOldMenuCbtFilter = NULL;
HMENU CNewMenuHook::m_hLastMenu = NULL;
DWORD CNewMenuHook::m_dwMsgPos = 0;
DWORD CNewMenuHook::m_bSubclassFlag = 0;

#ifdef _TRACE_MENU_LOGFILE
  HANDLE CNewMenuHook::m_hLogFile = INVALID_HANDLE_VALUE;
#endif //_TRACE_MENU_LOGFILE


CTypedPtrList<CPtrList, CMenuTheme*>* CNewMenuHook::m_pRegisteredThemesList = NULL;

CTypedPtrMap<CMapPtrToPtr,HWND,CNewMenuHook::CMenuHookData*> CNewMenuHook::m_MenuHookData;

#ifndef SM_REMOTESESSION
#define SM_REMOTESESSION     0x1000
#endif

CNewMenuHook::CNewMenuHook()
{ 
  if(g_Shell>=Win2000 && GetSystemMetrics(SM_REMOTESESSION))
  {
    bRemoteSession=TRUE;
  }

  HIGHCONTRAST highcontrast = {0};
  highcontrast.cbSize = sizeof(highcontrast);
  if(SystemParametersInfo(SPI_GETHIGHCONTRAST,sizeof(highcontrast),&highcontrast,0) )
  {
    bHighContrast = ((highcontrast.dwFlags&HCF_HIGHCONTRASTON)!=0);
  }

#ifdef _TRACE_MENU_LOGFILE
  m_hLogFile = CreateFile(_T("c:\\NewMenuLog.txt"), GENERIC_WRITE, FILE_SHARE_WRITE, 
      NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if(m_hLogFile!=INVALID_HANDLE_VALUE)
  {
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, m_hLogFile);

    _RPT0(_CRT_WARN,_T("file message\n"));
  }
#endif // _TRACE_MENU_LOGFILE

  // Try to load theme library from XP
  m_hThemeLibrary = LoadLibrary(_T("uxtheme.dll"));
  if(m_hThemeLibrary)
  {
    pIsThemeActive = (FktIsThemeActive)GetProcAddress(m_hThemeLibrary,"IsThemeActive");
    pSetWindowTheme = (FktSetWindowTheme)GetProcAddress(m_hThemeLibrary,"SetWindowTheme");
  }
  else
  {
    pIsThemeActive = NULL;
  }

  // Try to load the library for gradient drawing
  m_hLibrary = LoadLibrary(_T("Msimg32.dll"));

  // Don't use the gradientfill under Win98 because it is buggy!!!
  if(g_Shell!=Win98 && m_hLibrary)
  {
    pGradientFill = (FktGradientFill)GetProcAddress(m_hLibrary,"GradientFill");
  }
  else
  {
    pGradientFill = NULL;
  }
  
  //FixeMe:new 出来的这些资源有内存泄露 by zhangyl
  AddTheme(new CMenuTheme(CNewMenu::STYLE_ICY,
                          &CNewMenu::MeasureItem_Icy,
                          &CNewMenu::DrawItem_Icy,
                          &CNewMenu::DrawMenuTitle,TRUE));

  AddTheme(new CMenuTheme(CNewMenu::STYLE_ICY_NOBORDER,
                          &CNewMenu::MeasureItem_Icy,
                          &CNewMenu::DrawItem_Icy,
                          &CNewMenu::DrawMenuTitle));

  AddTheme(new CMenuTheme(CNewMenu::STYLE_ORIGINAL,
                          &CNewMenu::MeasureItem_OldStyle,
                          &CNewMenu::DrawItem_OldStyle,
                          &CNewMenu::DrawMenuTitle,TRUE));

  AddTheme(new CMenuTheme(CNewMenu::STYLE_ORIGINAL_NOBORDER,
                          &CNewMenu::MeasureItem_OldStyle,
                          &CNewMenu::DrawItem_OldStyle,
                          &CNewMenu::DrawMenuTitle));

  AddTheme(new CMenuThemeXP(CNewMenu::STYLE_XP,
                            &CNewMenu::MeasureItem_WinXP,
                            &CNewMenu::DrawItem_WinXP,
                            &CNewMenu::DrawMenuTitle,TRUE));

  AddTheme(new CMenuThemeXP(CNewMenu::STYLE_XP_NOBORDER,
                            &CNewMenu::MeasureItem_WinXP,
                            &CNewMenu::DrawItem_WinXP,
                            &CNewMenu::DrawMenuTitle));

  AddTheme(new CMenuThemeXP(CNewMenu::STYLE_XP_2003,
                            &CNewMenu::MeasureItem_WinXP,
                            &CNewMenu::DrawItem_XP_2003,
                            &CNewMenu::DrawMenuTitle,TRUE));

  AddTheme(new CMenuThemeXP(CNewMenu::STYLE_XP_2003_NOBORDER,
                            &CNewMenu::MeasureItem_WinXP,
                            &CNewMenu::DrawItem_XP_2003,
                            &CNewMenu::DrawMenuTitle));

  AddTheme(new CMenuTheme(CNewMenu::STYLE_SPECIAL,
                          &CNewMenu::MeasureItem_OldStyle,
                          &CNewMenu::DrawItem_SpecialStyle,
                          &CNewMenu::DrawMenuTitle,TRUE));

  AddTheme(new CMenuTheme(CNewMenu::STYLE_SPECIAL_NOBORDER,
                          &CNewMenu::MeasureItem_OldStyle,
                          &CNewMenu::DrawItem_SpecialStyle,
                          &CNewMenu::DrawMenuTitle));

//  CNewMenu::m_pActMenuDrawing = FindTheme(CNewMenu::STYLE_ORIGINAL);
//  CNewMenu::m_pActMenuDrawing = FindTheme(CNewMenu::STYLE_ORIGINAL_NOBORDER);
  CNewMenu::m_pActMenuDrawing = FindTheme(CNewMenu::STYLE_XP);
//  CNewMenu::m_pActMenuDrawing = FindTheme(CNewMenu::STYLE_XP_NOBORDER);

  if (HookOldMenuCbtFilter == NULL)
  {
    HookOldMenuCbtFilter = ::SetWindowsHookEx(WH_CALLWNDPROC, NewMenuHook, NULL, ::GetCurrentThreadId());
    if (HookOldMenuCbtFilter == NULL)
    {
      ShowLastError();
      AfxThrowMemoryException();
    }
  } 
}

CNewMenuHook::~CNewMenuHook()
{
  if (HookOldMenuCbtFilter != NULL)
  {
    if(!::UnhookWindowsHookEx(HookOldMenuCbtFilter))
    {
      ShowLastError();
    }
    HookOldMenuCbtFilter = NULL;
  }
  // Destroy all registered themes.
  if( m_pRegisteredThemesList!= NULL)
  {
    while(m_pRegisteredThemesList->GetCount())
    {
      CMenuTheme* pTheme = m_pRegisteredThemesList->RemoveTail();
      delete pTheme;
    }
    delete m_pRegisteredThemesList;
    m_pRegisteredThemesList = NULL;
  }

  pIsThemeActive = NULL;
  FreeLibrary(m_hThemeLibrary);

  pGradientFill = NULL;
  FreeLibrary(m_hLibrary);

  // Cleanup for shared menu icons
  if(CNewMenu::m_pSharedMenuIcons)
  {
    delete CNewMenu::m_pSharedMenuIcons;
    CNewMenu::m_pSharedMenuIcons = NULL;
  }

#ifdef _TRACE_MENU_LOGFILE
  if(m_hLogFile!=INVALID_HANDLE_VALUE)
  {
    CloseHandle(m_hLogFile);
    m_hLogFile = INVALID_HANDLE_VALUE;
  } 
#endif
}

BOOL CNewMenuHook::AddTheme(CMenuTheme* pTheme)
{
  if( m_pRegisteredThemesList== NULL)
  {
    m_pRegisteredThemesList = new CTypedPtrList<CPtrList, CMenuTheme*>;
  }
  if(m_pRegisteredThemesList->Find(pTheme))
  {
    return FALSE;
  }
  m_pRegisteredThemesList->AddTail(pTheme);
  return TRUE;
}

CMenuTheme* CNewMenuHook::RemoveTheme(DWORD dwThemeId)
{
  CMenuTheme* pTheme = FindTheme(dwThemeId);
  if(pTheme==NULL)
  {
    return NULL;
  }
  POSITION pos = m_pRegisteredThemesList->Find(pTheme);
  ASSERT(pos);
  if(pos)
  {
    m_pRegisteredThemesList->RemoveAt(pos);
    if(m_pRegisteredThemesList->GetCount()==NULL)
    {
      // Destroy the empty list.
      delete m_pRegisteredThemesList;
      m_pRegisteredThemesList = NULL;
    }
  }
  return pTheme; 
}

CMenuTheme* CNewMenuHook::FindTheme(DWORD dwThemeId)
{
  if(m_pRegisteredThemesList==NULL)
  {
    return NULL;
  }

  POSITION pos = m_pRegisteredThemesList->GetHeadPosition();
  while(pos)
  { 
    CMenuTheme* pTheme = m_pRegisteredThemesList->GetNext(pos);
    if(pTheme->m_dwThemeId==dwThemeId)
    {
      return pTheme;
    }
  }
  return NULL;
}

CNewMenuHook::CMenuHookData* CNewMenuHook::GetMenuHookData(HWND hWnd)
{
  CMenuHookData* pData=NULL;
  if(m_MenuHookData.Lookup(hWnd,pData))
  {
    return pData;
  }
  return NULL;
}

void CNewMenuHook::UnsubClassMenu(HWND hWnd)
{
  AFX_MANAGE_STATE(AfxGetModuleState());

  WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, _OldMenuProc);
  ASSERT(oldWndProc != NULL);  

  SetLastError(0);
  if(!SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)(DWORD_PTR)oldWndProc))
  {
    ShowLastError();
  }
  RemoveProp(hWnd, _OldMenuProc);
  GlobalDeleteAtom(GlobalFindAtom(_OldMenuProc));

  // now Clean up
  HMENU hMenu = NULL;
  // Restore old Styles for special menu!! (Menu 0x10012!!!)
  CMenuHookData* pData = GetMenuHookData(hWnd);
  if(pData)
  {
    hMenu = pData->m_hMenu;
    CNewMenu::m_pActMenuDrawing->OnUnInitWnd(hWnd);

    m_MenuHookData.RemoveKey(hWnd);
    delete pData;
  }
  
#ifdef _TRACE_MENU_
  AfxTrace(_T("Unsubclass Menu=0x%lX, hwnd=0x%lX\n"),hMenu,hWnd);
#endif
}

LRESULT CALLBACK CNewMenuHook::SubClassMenu(HWND hWnd,      // handle to window
                                            UINT uMsg,      // message identifier
                                            WPARAM wParam,  // first message parameter
                                            LPARAM lParam)  // second message parameter
{
  AFX_MANAGE_STATE(AfxGetModuleState());

  WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, _OldMenuProc);
  LRESULT result = NULL;
  BOOL bCallDefault = TRUE;


#ifdef _TRACE_MENU_
  static long NestedLevel = 0;
  NestedLevel++;
  MSG msg = {hWnd,uMsg,wParam,lParam,0,0,0};
  TCHAR Buffer[30]; 
  wsprintf(Buffer,_T("Level %02ld"),NestedLevel);
  MyTraceMsg(Buffer,&msg);
#endif

  CMenuHookData* pData = GetMenuHookData(hWnd);
  if(NULL == pData)
  {
    return ::CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
  }
  ASSERT(pData);

  switch(uMsg)
  { 
  case WM_NCPAINT:
    ASSERT(pData);

    if(pData->m_bDoSubclass)
    {
#ifdef _TRACE_MENU_   
      AfxTrace(_T("WM_NCPAINT (0x%x) 0x%X, 0x%X\n"),hWnd,wParam,lParam);
#endif 
      if(!pData->m_bDrawBorder)
      {
        if(pData->m_hRgn!=(HRGN)wParam)
        {
          if(pData->m_hRgn!=(HRGN)1)
          {
            DeleteObject(pData->m_hRgn);
            pData->m_hRgn=(HRGN)1;
          }
          if(wParam!=1)
          {
            CRgn dest;
            dest.CreateRectRgn( 0, 0, 1, 1);
            dest.CopyRgn(CRgn::FromHandle((HRGN)wParam));
            pData->m_hRgn = (HRGN)dest.Detach();
          }
        }
      }

      if(pData->m_dwData&8)
      {
        // do not call default!!!
        bCallDefault=FALSE;
      }
         
      if(pData->m_bDrawBorder &&  CNewMenu::m_pActMenuDrawing->DoDrawBorder())
      {
        //HDC hDC = GetWindowDC(hWnd); 
        HDC hDC;
        //if(wParam!=1)
        //  hDC = GetDCEx(hWnd, (HRGN)wParam, DCX_WINDOW|DCX_INTERSECTRGN);
        //else
          hDC = GetWindowDC (hWnd);

#ifdef _TRACE_MENU_   
        if(wParam!=1)
        {
          DWORD dwCount = GetRegionData((HRGN)wParam,0,0);
          RGNDATA* pRegionData = (RGNDATA*)_alloca(dwCount);
          GetRegionData((HRGN)wParam,dwCount,pRegionData);

          TRACE(_T("WM_NCPAINT (0x%x) region %ld "),hWnd,pRegionData->rdh.nCount);
          CRect* pRect = (CRect*)pRegionData->Buffer;
          for(DWORD n=0; n<pRegionData->rdh.nCount; n++)
          { 
            TRACE( _T("(%ld,%ld,%ld,%ld)"),pRect[n].left,pRect[n].top,pRect[n].right,pRect[n].bottom);
          }
          TRACE(_T("\r\n"));
        }
#endif //  _TRACE_MENU_  

        if(hDC)
        { 
          if(CNewMenu::m_pActMenuDrawing->OnDrawBorder(hWnd,hDC))
          {
            CRect rect;
            if(CNewMenu::m_pActMenuDrawing->OnCalcFrameRect(hWnd,rect))
            {
              CRgn rgn;
              rect.InflateRect(-1,-1);
              rgn.CreateRectRgnIndirect(rect);
              // do we need a combination of the regions?
              //if(wParam!=1)
              //{
              //  rgn.CombineRgn(&rgn,CRgn::FromHandle((HRGN)wParam),RGN_AND);
              //}
              ASSERT(oldWndProc);

              bCallDefault=FALSE;
              result = CallWindowProc(oldWndProc, hWnd, uMsg, (WPARAM)rgn.m_hObject, lParam);
              //result = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
              // Redraw the border and shade
              CNewMenu::m_pActMenuDrawing->OnDrawBorder(hWnd,hDC,true);
            }
          }
          ReleaseDC(hWnd,hDC);
        }
      }
      if(CNewMenu::m_pActMenuDrawing->DoDrawBorder() && bCallDefault)
      {
        // Save the background
        HDC hDC = GetWindowDC (hWnd);
        CNewMenu::m_pActMenuDrawing->SetScreenBitmap(hWnd,hDC);
        ReleaseDC(hWnd,hDC);
      }
    }

    break;

  case WM_PRINT:
    if(pData && pData->m_bDoSubclass)
    {
      if(CNewMenu::m_pActMenuDrawing->DoDrawBorder())
      {
        // Mark for WM_PRINT 
        pData->m_dwData |= 8;

  //      pData->m_bDrawBorder = FALSE;
        // We need to create a bitmap for drawing
        // We can't clipp or make a offset to the DC because NT2000 (blue-screen!!)
        CRect rect;
        GetWindowRect(hWnd, rect);
        CDC dc;
        CBitmap bitmap;

        CDC* pDC = CDC::FromHandle((HDC)wParam);
        dc.CreateCompatibleDC(pDC); 

        bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
        CBitmap* pOldBitmap = dc.SelectObject(&bitmap);

    // new
 //       dc.FillSolidRect(0,0,rect.Width(), rect.Height(),CNewMenu::GetMenuBarColor(pData->m_hMenu));

        CNewMenu::m_pActMenuDrawing->OnDrawBorder(hWnd,dc.m_hDC);

        CRect rectClient;
        if(CNewMenu::m_pActMenuDrawing->OnCalcFrameRect(hWnd,rectClient))
        {
          // might as well clip to the same rectangle
          CRect clipRect = rectClient;
          clipRect.OffsetRect(rectClient.TopLeft()-rect.TopLeft());
          clipRect.InflateRect(-1,-1);
          dc.IntersectClipRect(clipRect);
          result = CallWindowProc(oldWndProc, hWnd, uMsg, (WPARAM)dc.m_hDC, lParam&~PRF_CLIENT);
        
          pDC->BitBlt(0,0, rect.Width(), rect.Height(), &dc,0,0, SRCCOPY);

          GetClientRect(hWnd,clipRect);
          SelectClipRgn(dc.m_hDC,NULL);
          dc.IntersectClipRect(clipRect);

          SendMessage(hWnd,WM_ERASEBKGND,(WPARAM)dc.m_hDC,0);
          SendMessage(hWnd,WM_PRINTCLIENT,(WPARAM)dc.m_hDC,lParam);

          CPoint wndOffset(0,0);
          ClientToScreen(hWnd,&wndOffset);
          wndOffset -= rect.TopLeft();
          pDC->BitBlt(wndOffset.x,wndOffset.y, clipRect.Width()-1, clipRect.Height(), &dc, 0, 0, SRCCOPY);
        }
        // 
        dc.SelectObject(pOldBitmap);
        bCallDefault=FALSE;

        // Clear for WM_PRINT 
        pData->m_dwData &= ~8;
     }
    }
    break;

  case WM_ERASEBKGND:
    ASSERT(pData);
    if(pData->m_bDoSubclass)
    {
      if(CNewMenu::m_pActMenuDrawing->DoDrawBorder())
      {
        if(!(pData->m_dwData&8) && !pData->m_bDrawBorder )
        {
          pData->m_bDrawBorder = true;
          //SendMessage(hWnd,WM_NCPAINT,(WPARAM)pData->m_hRgn,0);
          SendMessage(hWnd,WM_NCPAINT,(WPARAM)1,0);
        }
      }

      if(CNewMenu::m_pActMenuDrawing->OnEraseBkgnd(hWnd,(HDC)wParam))
      {
        bCallDefault=FALSE; 
        result = TRUE;
      }
    }
    break;

  case WM_WINDOWPOSCHANGED:
  case WM_WINDOWPOSCHANGING:
    {
      ASSERT(pData);

      LPWINDOWPOS pPos = (LPWINDOWPOS)lParam;
      if(uMsg==WM_WINDOWPOSCHANGING)
      {
        CNewMenu::m_pActMenuDrawing->OnWindowPosChanging(hWnd,pPos);
      }
      if(!(pPos->flags&SWP_NOMOVE) )
      {
        if(pData->m_Point==CPoint(0,0))
        {
          pData->m_Point = CPoint(pPos->x,pPos->y);
        }
        else if(pData->m_Point!=CPoint(pPos->x,pPos->y))
        {
/*          CRect rect(0,0,0,0);
          if(!GetWindowRect(hWnd,rect))
          {
            AfxTrace(_T("Error get rect\n"));
          }
          #ifdef _TRACE_MENU_

          DWORD dwPos =GetMessagePos();
          AfxTrace(_T("Rect pos (%ld/%ld), dimensions [%ld,%ld], Delta(%ld/%ld),MPos %lx\n"),
                   pData->m_Point.x,pData->m_Point.y,rect.Width(),rect.Height(),
                   pData->m_Point.x-pPos->x,pData->m_Point.y-pPos->y,dwPos);
          #endif
*/
          if(!(pPos->flags&SWP_NOSIZE))
          {
            UnsubClassMenu(hWnd);
          }
          else
          {
            pData->m_Point=CPoint(pPos->x,pPos->y);
            pData->m_Screen.DeleteObject();
          }
        }
      }
    }
    break;

  case WM_KEYDOWN:
    if(wParam==VK_ESCAPE)
    {
      if(pData)
      {
        pData->m_dwData |= 4;
      }
    }
    m_dwMsgPos = GetMessagePos();
    break;

  case WM_NCCALCSIZE:
    if(pData->m_bDoSubclass)
    {
      NCCALCSIZE_PARAMS* pCalc = (NCCALCSIZE_PARAMS*)lParam;
      if(CNewMenu::m_pActMenuDrawing->OnNcCalcSize(hWnd,pCalc))
      {
        bCallDefault=FALSE; 
      }
    }
    break;

  case WM_SHOWWINDOW:
    // Hide the window ? Test for 98 and 2000
    if(wParam==NULL)
    { 
      // Special handling for NT 2000 and WND 0x10012.
      UnsubClassMenu(hWnd);
    }
    break;

  case WM_NCDESTROY:
    UnsubClassMenu (hWnd);
    break;

  //default:
  //  {
  //    static const UINT WBHook = RegisterWindowMessage(_T("WBHook"));
  //    if (uMsg==WBHook)
  //    {
  //      bCallDefault = false;
  //    }
  //  }
  //  break;
  }

  if( bCallDefault )
  {
    ASSERT(oldWndProc != NULL);
    // call original wndproc for default handling
    result = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
  }

#ifdef _TRACE_MENU_
  NestedLevel--;
#endif

  return result;
} 

BOOL CNewMenuHook::CheckSubclassing(HWND hWnd, BOOL bSpecialWnd)
{
  TCHAR Name[20];
  int Count = GetClassName (hWnd,Name,ARRAY_SIZE(Name));
  // Check for the menu-class
  if(Count!=6 || _tcscmp(Name,_T("#32768"))!=0)
  {
    // does not match to menuclass
    return false;
  }

  BOOL bDoNewSubclass = FALSE;
  CMenuHookData* pData=GetMenuHookData(hWnd);
  // check if we have allready some data
  if(pData==NULL)
  {
    WNDPROC oldWndProc;
    // subclass the window with the proc which does gray backgrounds
    oldWndProc = (WNDPROC)(LONG_PTR)GetWindowLong(hWnd, GWL_WNDPROC);
    if (oldWndProc != NULL && GetProp(hWnd, _OldMenuProc) == NULL)
    {
      ASSERT(oldWndProc!=SubClassMenu);

      if(!SetProp(hWnd, _OldMenuProc, oldWndProc))
      {
        ShowLastError();
      }
      if ((WNDPROC)GetProp(hWnd, _OldMenuProc) == oldWndProc)
      {
        GlobalAddAtom(_OldMenuProc);

        CMenuHookData* pData=GetMenuHookData(hWnd);
        ASSERT(pData==NULL);
        if(pData==NULL)
        { 
          pData = new CMenuHookData(hWnd,bSpecialWnd);
          m_MenuHookData.SetAt (hWnd,pData);

          SetLastError(0);
          if(!SetWindowLong(hWnd, GWL_WNDPROC,(DWORD)(DWORD_PTR)SubClassMenu))
          {
            ShowLastError();
          }
          bDoNewSubclass = TRUE;

  #ifdef _TRACE_MENU_
          AfxTrace(_T("Subclass Menu=0x%lX, hwnd=0x%lX\n"),pData->m_hMenu,hWnd);
  #endif 
          CNewMenu::m_pActMenuDrawing->OnInitWnd(hWnd);
        } 
      }
      else
      {
        ASSERT(0);
      }
    }
  }

  // Menu was set also assign it to this menu.
  if(m_hLastMenu)
  {
    CMenuHookData* pData = GetMenuHookData(hWnd);
    if(pData)
    {
      // Safe actual menu
      pData->SetMenu(m_hLastMenu);
      // Reset for the next menu
      m_hLastMenu = NULL;
      //
      CNewMenu::m_pActMenuDrawing->OnInitWnd(hWnd);
    }
  }
  return bDoNewSubclass;
}

class CNewMenuTempHandler : public CObject
{
  CNewMenu m_SystemNewMenu;
  WNDPROC m_oldWndProc;
  HWND m_hWnd;

public:
  CNewMenuTempHandler(HWND hWnd)
  {
    m_hWnd = hWnd;
    VERIFY(SetProp(hWnd,_T("CNewMenuTempHandler"),this)); 
    // Subclass the dialog control. 
    m_oldWndProc = (WNDPROC)(LONG_PTR)SetWindowLong(hWnd, GWL_WNDPROC,(DWORD)(DWORD_PTR)TempSubclass);
  }

  ~CNewMenuTempHandler()
  {
    SetWindowLong(m_hWnd, GWL_WNDPROC,(DWORD)(DWORD_PTR)m_oldWndProc);
    VERIFY(RemoveProp(m_hWnd,_T("CNewMenuTempHandler"))); 
  }

  LRESULT Default(UINT uMsg, WPARAM wParam, LPARAM lParam )
  {
    // call original wndproc for default handling
    return CallWindowProc(m_oldWndProc, m_hWnd, uMsg, wParam, lParam);
  }

  LRESULT OnCmd(UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    MSG msg = {m_hWnd,uMsg,wParam,lParam,0,0,0};
    switch(uMsg)
    {
    case WM_DRAWITEM:
      {
        if(m_SystemNewMenu.m_hMenu)
        {  
          DRAWITEMSTRUCT* lpDrawItemStruct = (DRAWITEMSTRUCT*)lParam;
          if (lpDrawItemStruct->CtlType == ODT_MENU)
          {
            CMenu* pMenu = CMenu::FromHandlePermanent((HMENU)lpDrawItemStruct->hwndItem);
            if (DYNAMIC_DOWNCAST(CNewMenu,pMenu))
            {
              pMenu->DrawItem(lpDrawItemStruct);
              return true; // eat it
            }
          }
        }
        return Default(uMsg, wParam, lParam);
      }
      
    case WM_MEASUREITEM:
      if(CNewMenu::OnMeasureItem(&msg))
      {
        return TRUE;
      }
      break;
      
    case WM_MENUCHAR:
      { 
        CMenu* pMenu = CMenu::FromHandle(UIntToHMenu((UINT)lParam));;
        LRESULT lresult; 
        if( DYNAMIC_DOWNCAST(CNewMenu,pMenu) ) 
          lresult=CNewMenu::FindKeyboardShortcut(LOWORD(wParam), HIWORD(wParam),pMenu ); 
        else 
          lresult=Default(uMsg, wParam, lParam); 
        return lresult; 
      }
      break;
      
    case WM_INITMENUPOPUP:
      {
        CMenu* pMenu = CMenu::FromHandle(UIntToHMenu((UINT)wParam));
        LRESULT result = Default(uMsg, wParam, lParam);
        CNewMenu::OnInitMenuPopup(m_hWnd, pMenu, LOWORD(lParam), HIWORD(lParam));
        return result;
      }
      
    case WM_INITDIALOG:
      if(CNewMenuHook::m_bSubclassFlag&NEW_MENU_DIALOG_SYSTEM_MENU)
      {
        LRESULT bRetval = Default(uMsg, wParam, lParam);
        VERIFY(m_SystemNewMenu.m_hMenu==0);        
        
        HMENU hMenu = ::GetSystemMenu(m_hWnd,FALSE);
        if(IsMenu(hMenu))
        {
          CMenu* pMenu = CMenu::FromHandlePermanent(hMenu);
          // Only attach to CNewMenu once
          if (DYNAMIC_DOWNCAST(CNewMenu,pMenu)==NULL )
          {
            m_SystemNewMenu.Attach(hMenu); 
          }
        }
        return bRetval; 
      }
      break;

    case WM_DESTROY:
      LRESULT result = Default(uMsg, wParam, lParam);
      delete this;
      return result;
    }
    
    return Default(uMsg, wParam, lParam);
  }

  // Subclass procedure 
  static LRESULT APIENTRY TempSubclass(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
  { 
    AFX_MANAGE_STATE(AfxGetModuleState());

    CNewMenuTempHandler* pTemp = (CNewMenuTempHandler*)GetProp(hwnd,_T("CNewMenuTempHandler"));
    ASSERT(pTemp);
    return pTemp->OnCmd(uMsg, wParam, lParam);
  } 

};

LRESULT CALLBACK CNewMenuHook::NewMenuHook(int code, WPARAM wParam, LPARAM lParam)
{
  AFX_MANAGE_STATE(AfxGetModuleState());

  CWPSTRUCT* pTemp = (CWPSTRUCT*)lParam;
  if(code == HC_ACTION )
  {
    HWND hWnd = pTemp->hwnd;

#ifdef _TRACE_MENU_
    static HWND acthMenu = NULL;
    static HWND acthWnd = NULL;

    // Check if we need to find out the window
    if (hWnd && hWnd!=acthWnd && hWnd!=acthMenu)
    {
      TCHAR Name[20];
      int Count = GetClassName (hWnd,Name,ARRAY_SIZE(Name));
      // Check for the menu-class
      if(Count!=6 || _tcscmp(Name,_T("#32768"))!=0)
      {
        // does not match to menuclass
        acthWnd = hWnd;
      }
      else
      {
        acthMenu = hWnd;
        // AfxTrace(_T("Found new menu HWND: 0x%08X\n"),acthMenu);
      }
    }
    // Trace all menu msg
    if(acthMenu==hWnd && acthMenu)
    {
      MSG msg = {hWnd,pTemp->message,pTemp->wParam,pTemp->lParam,0,0,0};
      MyTraceMsg(_T(" Menu   "),&msg);
    }
#endif

    // Normal and special handling for menu 0x10012
    if(pTemp->message==WM_CREATE || pTemp->message==0x01E2)
    {
      if(!CheckSubclassing(hWnd,pTemp->message==0x01E2))
      {
        if( (m_bSubclassFlag&NEW_MENU_DIALOG_SUBCLASS) && pTemp->message==WM_CREATE)
        {
          TCHAR Name[20];
          int Count = GetClassName (hWnd,Name,ARRAY_SIZE(Name));
          // Check for the Dialog-class
          if(Count==6 && _tcscmp(Name,_T("#32770"))==0 )
          { 
            // Only first dialog
           // m_bSubclassFlag &= ~NEW_MENU_DIALOG_SUBCLASS;
            // Freed by WM_DESTROY
            new CNewMenuTempHandler(hWnd);
          }
        }
      }
    }
  }
  return CallNextHookEx(HookOldMenuCbtFilter, code,wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewDialog,CDialog)

BEGIN_MESSAGE_MAP(CNewDialog, CNewFrame<CDialog>)
  //{{AFX_MSG_MAP(CNewDialog)
  ON_WM_INITMENUPOPUP()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CNewDialog::CNewDialog()
{
}

CNewDialog::CNewDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
  ASSERT(IS_INTRESOURCE(lpszTemplateName) || AfxIsValidString(lpszTemplateName));

  m_pParentWnd = pParentWnd;
  m_lpszTemplateName = lpszTemplateName;
  if (IS_INTRESOURCE(m_lpszTemplateName))
    m_nIDHelp = LOWORD((DWORD_PTR)m_lpszTemplateName);
}

CNewDialog::CNewDialog(UINT nIDTemplate, CWnd* pParentWnd)
{
  m_pParentWnd = pParentWnd;
  m_lpszTemplateName = MAKEINTRESOURCE(nIDTemplate);
  m_nIDHelp = nIDTemplate;
}

BOOL CNewDialog::OnInitDialog()
{
  BOOL bRetval = CDialog::OnInitDialog();

  HMENU hMenu = m_SystemNewMenu.Detach();
  HMENU hSysMenu = ::GetSystemMenu(m_hWnd,FALSE);
  if(hMenu!=hSysMenu)
  {
    if(IsMenu(hMenu))
    {
      if(!::DestroyMenu(hMenu))
      {
        ShowLastError();
      }
    }
  }
  m_SystemNewMenu.Attach(hSysMenu);
  m_DefaultNewMenu.LoadMenu(::GetMenu(m_hWnd));

  if(IsMenu(m_DefaultNewMenu.m_hMenu))
  {
    UpdateMenuBarColor(m_DefaultNewMenu);
  }

  return bRetval;
}

extern void AFXAPI AfxCancelModes(HWND hWndRcvr);

// Most of the code is copied from the MFC code from CFrameWnd::OnInitMenuPopup
void CNewDialog::OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu)
{
  AfxCancelModes(m_hWnd);

  // don't support system menu
  if (!bSysMenu)
  {
    ASSERT(pMenu != NULL);
    // check the enabled state of various menu items

    CCmdUI state;
    state.m_pMenu = pMenu;
    ASSERT(state.m_pOther == NULL);
    ASSERT(state.m_pParentMenu == NULL);

    // determine if menu is popup in top-level menu and set m_pOther to
    //  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
    HMENU hParentMenu;
    if (AfxGetThreadState()->m_hTrackingMenu == pMenu->m_hMenu)
    {
      state.m_pParentMenu = pMenu;    // parent == child for tracking popup
    }
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
    {
      CWnd* pParent = GetTopLevelParent();
      // child windows don't have menus -- need to go to the top!
      if (pParent != NULL &&
        (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
      {
        int nIndexMax = ::GetMenuItemCount(hParentMenu);
        for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
        {
          if (::GetSubMenu(hParentMenu, nIndex) == pMenu->m_hMenu)
          {
            // when popup is found, m_pParentMenu is containing menu
            state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
            break;
          }
        }
      }
    }

    state.m_nIndexMax = pMenu->GetMenuItemCount();
    for (state.m_nIndex = 0; state.m_nIndex<state.m_nIndexMax; state.m_nIndex++)
    {
      state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);
      if (state.m_nID == 0)
        continue; // menu separator or invalid cmd - ignore it

      ASSERT(state.m_pOther == NULL);
      ASSERT(state.m_pMenu != NULL);
      if (state.m_nID == (UINT)-1)
      {
        // possibly a popup menu, route to first item of that popup
        state.m_pSubMenu = pMenu->GetSubMenu(state.m_nIndex);
        if (state.m_pSubMenu == NULL ||
          (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
          state.m_nID == (UINT)-1)
        {
          continue;       // first item of popup can't be routed to
        }
        state.DoUpdate(this, FALSE);    // popups are never auto disabled
      }
      else
      {
        // normal menu item
        // Auto enable/disable if frame window has 'm_bAutoMenuEnable'
        //    set and command is _not_ a system command.
        state.m_pSubMenu = NULL;
        state.DoUpdate(this, state.m_nID < 0xF000);
      }

      // adjust for menu deletions and additions
      UINT nCount = pMenu->GetMenuItemCount();
      if (nCount < state.m_nIndexMax)
      {
        state.m_nIndex -= (state.m_nIndexMax - nCount);
        while (state.m_nIndex < nCount &&
          pMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
        {
          state.m_nIndex++;
        }
      }
      state.m_nIndexMax = nCount;
    }
  }
  // Do the work for update
  CNewFrame<CDialog>::OnInitMenuPopup(pMenu,nIndex,bSysMenu);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CNewMiniFrameWnd,CMiniFrameWnd)
IMPLEMENT_DYNCREATE(CNewMDIChildWnd,CMDIChildWnd)
IMPLEMENT_DYNCREATE(CNewMiniDockFrameWnd,CMiniDockFrameWnd);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CNewFrameWnd,CFrameWnd)

#if _MFC_VER < 0x0700

#include <../src/afximpl.h> 

BOOL CNewFrameWnd::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle,
  CWnd* pParentWnd, CCreateContext* pContext)
{
  // only do this once
  ASSERT_VALID_IDR(nIDResource);
  ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

  m_nIDHelp = nIDResource;    // ID for help context (+HID_BASE_RESOURCE)

  CString strFullString;
  if (strFullString.LoadString(nIDResource))
    AfxExtractSubString(m_strTitle, strFullString, 0);    // first sub-string

  VERIFY(AfxDeferRegisterClass(AFX_WNDFRAMEORVIEW_REG));

  // attempt to create the window
  LPCTSTR lpszClass = GetIconWndClass(dwDefaultStyle, nIDResource);
  LPCTSTR lpszTitle = m_strTitle;
  if (!Create(lpszClass, lpszTitle, dwDefaultStyle, rectDefault,
              pParentWnd, MAKEINTRESOURCE(nIDResource), 0L, pContext))
  {
    return FALSE;   // will self destruct on failure normally
  }

  // save the default menu handle
  ASSERT(m_hWnd != NULL);
  m_hMenuDefault = ::GetMenu(m_hWnd);

  // load accelerator resource
  LoadAccelTable(MAKEINTRESOURCE(nIDResource));

  if (pContext == NULL)   // send initial update
    SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

  return TRUE;
}
#endif

BOOL CNewFrameWnd::Create(LPCTSTR lpszClassName,
                          LPCTSTR lpszWindowName,
                          DWORD dwStyle,
                          const RECT& rect,
                          CWnd* pParentWnd,
                          LPCTSTR lpszMenuName,
                          DWORD dwExStyle,
                          CCreateContext* pContext)
{
  if (lpszMenuName != NULL)
  {
    m_DefaultNewMenu.LoadMenu(lpszMenuName);
    // load in a menu that will get destroyed when window gets destroyed
    if (m_DefaultNewMenu.m_hMenu == NULL)
    {
#if _MFC_VER < 0x0700 
      TRACE0("Warning: failed to load menu for CNewFrameWnd.\n");
#else
      TRACE(traceAppMsg, 0, "Warning: failed to load menu for CNewFrameWnd.\n");
#endif
      PostNcDestroy();            // perhaps delete the C++ object
      return FALSE;
    }
  }
  m_strTitle = lpszWindowName;    // save title for later

  if (!CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle,
    rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
    pParentWnd->GetSafeHwnd(), m_DefaultNewMenu.m_hMenu, (LPVOID)pContext))
  {
#if _MFC_VER < 0x0700 
    TRACE0("Warning: failed to create CNewFrameWnd.\n");
#else
    TRACE(traceAppMsg, 0, "Warning: failed to create CNewFrameWnd.\n");
#endif

    return FALSE;
  } 

  UpdateMenuBarColor(m_DefaultNewMenu);

  return TRUE;
}

#ifdef USE_NEW_DOCK_BAR

//Bug in compiler??

// control bar docking
// dwDockBarMap
const DWORD CFrameWnd::dwDockBarMap[4][2] =
{
  { AFX_IDW_DOCKBAR_TOP,      CBRS_TOP    },
  { AFX_IDW_DOCKBAR_BOTTOM,   CBRS_BOTTOM },
  { AFX_IDW_DOCKBAR_LEFT,     CBRS_LEFT   },
  { AFX_IDW_DOCKBAR_RIGHT,    CBRS_RIGHT  },
};

// dock bars will be created in the order specified by dwDockBarMap
// this also controls which gets priority during layout
// this order can be changed by calling EnableDocking repetitively
// with the exact order of priority
void CNewFrameWnd::EnableDocking(DWORD dwDockStyle)
{
  // must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
  ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

  m_pFloatingFrameClass = RUNTIME_CLASS(CNewMiniDockFrameWnd);
  for (int i = 0; i < 4; i++)
  {
    if (dwDockBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY)
    {
      CDockBar* pDock = (CDockBar*)GetControlBar(dwDockBarMap[i][0]);
      if (pDock == NULL)
      {
        pDock = new CNewDockBar;
        if (!pDock->Create(this,
          WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
            dwDockBarMap[i][1], dwDockBarMap[i][0]))
        {
          AfxThrowResourceException();
        }
      }
    }
  }
}
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewMDIFrameWnd,CMDIFrameWnd)

BOOL CNewMDIFrameWnd::ShowMenu(BOOL bShow)
{
  // Gets the actual menu
  HMENU hMenu = ::GetMenu(m_hWnd);   
  if(bShow)
  {
    if(m_hShowMenu)
    {
      ::SetMenu(m_hWnd, m_hShowMenu); 
      DrawMenuBar();
      m_hShowMenu = NULL;
      return FALSE;
    }
    return TRUE;
  }
  else
  {
    m_hShowMenu = hMenu;
    if(m_hShowMenu)
    {
      ::SetMenu(m_hWnd, NULL); 
      DrawMenuBar();
      return TRUE;
    }
    return FALSE;
  }
}



#if _MFC_VER < 0x0700 

BOOL CNewMDIFrameWnd::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle,
                                CWnd* pParentWnd, CCreateContext* pContext)
{
  // only do this once
  ASSERT_VALID_IDR(nIDResource);
  ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

  m_nIDHelp = nIDResource;    // ID for help context (+HID_BASE_RESOURCE)

  CString strFullString;
  if (strFullString.LoadString(nIDResource))
    AfxExtractSubString(m_strTitle, strFullString, 0);    // first sub-string

  VERIFY(AfxDeferRegisterClass(AFX_WNDFRAMEORVIEW_REG));

  // attempt to create the window
  LPCTSTR lpszClass = GetIconWndClass(dwDefaultStyle, nIDResource);
  LPCTSTR lpszTitle = m_strTitle;
  if (!Create(lpszClass, lpszTitle, dwDefaultStyle, rectDefault,
              pParentWnd, MAKEINTRESOURCE(nIDResource), 0L, pContext))
  {
    return FALSE;   // will self destruct on failure normally
  }

  // save the default menu handle
  ASSERT(m_hWnd != NULL);
  m_hMenuDefault = ::GetMenu(m_hWnd);

  // load accelerator resource
  LoadAccelTable(MAKEINTRESOURCE(nIDResource));

  if (pContext == NULL)   // send initial update
    SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

  // save menu to use when no active MDI child window is present
  ASSERT(m_hWnd != NULL);
  m_hMenuDefault = ::GetMenu(m_hWnd);
  if (m_hMenuDefault == NULL)
    TRACE0("Warning: CMDIFrameWnd without a default menu.\n");
  return TRUE;
}
#endif

BOOL CNewMDIFrameWnd::Create( LPCTSTR lpszClassName,
                              LPCTSTR lpszWindowName,
                              DWORD dwStyle,
                              const RECT& rect,
                              CWnd* pParentWnd,
                              LPCTSTR lpszMenuName,
                              DWORD dwExStyle,
                              CCreateContext* pContext)
{
  if (lpszMenuName != NULL)
  {
    m_DefaultNewMenu.LoadMenu(lpszMenuName);
    // load in a menu that will get destroyed when window gets destroyed
    if (m_DefaultNewMenu.m_hMenu == NULL)
    {
#if _MFC_VER < 0x0700 
      TRACE0("Warning: failed to load menu for CNewMDIFrameWnd.\n");
#else
      TRACE(traceAppMsg, 0, "Warning: failed to load menu for CNewMDIFrameWnd.\n");
#endif
      PostNcDestroy();            // perhaps delete the C++ object
      return FALSE;
    }
  }

  m_strTitle = lpszWindowName;    // save title for later

  if (!CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle,
    rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
    pParentWnd->GetSafeHwnd(), m_DefaultNewMenu.m_hMenu, (LPVOID)pContext))
  {
#if _MFC_VER < 0x0700 
    TRACE0("Warning: failed to create CNewMDIFrameWnd.\n");
#else
    TRACE(traceAppMsg, 0, "Warning: failed to create CNewMDIFrameWnd.\n");
#endif

    return FALSE;
  } 

  UpdateMenuBarColor(m_DefaultNewMenu);

  return TRUE;
}

#ifdef USE_NEW_DOCK_BAR

// dock bars will be created in the order specified by dwDockBarMap
// this also controls which gets priority during layout
// this order can be changed by calling EnableDocking repetitively
// with the exact order of priority
void CNewMDIFrameWnd::EnableDocking(DWORD dwDockStyle)
{
  // must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
  ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

  m_pFloatingFrameClass = RUNTIME_CLASS(CNewMiniDockFrameWnd);
  for (int i = 0; i < 4; i++)
  {
    if (dwDockBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY)
    {
      CDockBar* pDock = (CDockBar*)GetControlBar(dwDockBarMap[i][0]);
      if (pDock == NULL)
      {
        pDock = new CNewDockBar;
        if (!pDock->Create(this,
          WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
            dwDockBarMap[i][1], dwDockBarMap[i][0]))
        {
          AfxThrowResourceException();
        }
      }
    }
  }
}
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CNewMultiDocTemplate,CMultiDocTemplate)

CNewMultiDocTemplate::CNewMultiDocTemplate(UINT nIDResource, 
                                           CRuntimeClass* pDocClass,
                                           CRuntimeClass* pFrameClass,
                                           CRuntimeClass* pViewClass)
: CMultiDocTemplate(nIDResource,pDocClass,pFrameClass,pViewClass)
{
  if (m_nIDResource != 0 && m_hMenuShared)
  {
    // Attach the menu.
    m_NewMenuShared.LoadMenu(m_hMenuShared);
    // Try to load icons to the toolbar.
    m_NewMenuShared.LoadToolBar(m_nIDResource);
  }
}

CNewMultiDocTemplate::~CNewMultiDocTemplate()
{
  // Let only the CNewMenu to destroy the menu.
  if(m_hMenuShared==m_NewMenuShared.m_hMenu)
  {
    m_hMenuShared = NULL;
  }
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewMenuHelper::CNewMenuHelper(DWORD dwFlags)
{
  m_dwOldFlags = CNewMenuHook::m_bSubclassFlag; 
  CNewMenuHook::m_bSubclassFlag = dwFlags;

  m_OldMenuDrawStyle = CNewMenu::GetMenuDrawMode();
  if(CNewMenuHook::m_bSubclassFlag&NEW_MENU_DEFAULT_BORDER)
  {
    CNewMenu::SetMenuDrawMode(m_OldMenuDrawStyle|1);
  }
}

CNewMenuHelper::CNewMenuHelper(CNewMenu::EDrawStyle setTempStyle)
{
  m_dwOldFlags = CNewMenuHook::m_bSubclassFlag; 
  m_OldMenuDrawStyle = CNewMenu::SetMenuDrawMode(setTempStyle);
}

CNewMenuHelper::~CNewMenuHelper()
{  
  // Restore the old border style
  CNewMenu::SetMenuDrawMode(m_OldMenuDrawStyle);
  CNewMenuHook::m_bSubclassFlag = m_dwOldFlags;
}


// CNewDockBar

IMPLEMENT_DYNCREATE(CNewDockBar, CDockBar)

CNewDockBar::CNewDockBar(BOOL bFloating):CDockBar(bFloating)
{
}

CNewDockBar::~CNewDockBar()
{
}

BEGIN_MESSAGE_MAP(CNewDockBar, CDockBar)
  ON_WM_ERASEBKGND()
  ON_WM_NCPAINT()
END_MESSAGE_MAP()


// CNewDockBar diagnostics

#ifdef _DEBUG
void CNewDockBar::AssertValid() const
{
  CDockBar::AssertValid();
}

void CNewDockBar::Dump(CDumpContext& dc) const
{
  CDockBar::Dump(dc);
}
#endif //_DEBUG


// CNewDockBar message handlers
void CNewDockBar::EraseNonClient()
{
  // get window DC that is clipped to the non-client area
  CWindowDC dc(this);
  CRect rectClient;
  GetClientRect(rectClient);
  CRect rectWindow;
  GetWindowRect(rectWindow);
  ScreenToClient(rectWindow);
  rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
  dc.ExcludeClipRect(rectClient);

  // draw borders in non-client area
  rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);

  //DrawBorders(&dc, rectWindow);

  // erase parts not drawn
  dc.IntersectClipRect(rectWindow);
  SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);

  // draw gripper in non-client area
  DrawGripper(&dc, rectWindow);
}

BOOL CNewDockBar::OnEraseBkgnd(CDC* pDC)
{
  MENUINFO menuInfo = {0};
  menuInfo.cbSize = sizeof(menuInfo);
  menuInfo.fMask = MIM_BACKGROUND;

  if(::GetMenuInfo(::GetMenu(::GetParent(m_hWnd)),&menuInfo) && menuInfo.hbrBack)
  {
    CRect rectA;
    CRect rectB;
    GetWindowRect(rectA);
    ::GetWindowRect(::GetParent(m_hWnd),rectB);

    CBrush *pBrush = CBrush::FromHandle(menuInfo.hbrBack);
    // need for win95/98/me
    VERIFY(pBrush->UnrealizeObject());
    CPoint oldOrg = pDC->SetBrushOrg(-(rectA.left-rectB.left),0);
    CRect rect;
    pDC->GetClipBox(rect);
    pDC->FillRect(rect,pBrush);
    pDC->SetBrushOrg(oldOrg);
    return true;
  }
  else
  {
    // do default drawing
    return CDockBar::OnEraseBkgnd(pDC);
  }
}

void CNewDockBar::OnNcPaint()
{
  // Do not call CDockBar::OnNcPaint() for painting messages
  EraseNonClient();
}
