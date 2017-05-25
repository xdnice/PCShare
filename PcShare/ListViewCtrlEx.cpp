/******************************************************************************

$Author$
  
$Modtime$
$Revision$

Description: Implementation of class "CListBase"
             (list control with sort icons and colored sort column)

$Log$

******************************************************************************/

#include "stdafx.h"
#include "PcShare.h"
#include "ListViewCtrlEx.h"

/*** Defines not yet available in MS VC++ 6.0 ********************************/
#ifndef HDF_SORTUP
#define HDF_SORTUP 0x0400
#endif
#ifndef HDF_SORTDOWN
#define HDF_SORTDOWN 0x0200
#endif
#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif

/*** Definition of class "CListCtrlEx" ***************************************/

IMPLEMENT_DYNCREATE(CListCtrlEx, CListCtrl)

/*** Protected member functions **********************************************/

/*** A column header has been clicked ****************************************/
BOOL CListCtrlEx::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
  return CListBase::OnColumnclick(pNMHDR, pResult);
}

/*** An item in the column selection menu has been selected ******************/
BOOL CListCtrlEx::OnCommand(WPARAM wParam, LPARAM)
{
  return CListBase::OnCommand(wParam);
}

/*** The user has right clicked the mouse ************************************/
void CListCtrlEx::OnContextMenu(CWnd* pWnd, CPoint) 
{
  CListBase::OnContextMenu(pWnd);
}

/*** A list view (sub)item will be drawn *************************************/
void CListCtrlEx::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
  CListBase::OnCustomDraw(pNMHDR, pResult);
}

/*** All items from a list view control will be removed **********************/
LRESULT CListCtrlEx::OnDeleteAllItems(WPARAM, LPARAM)
{
  return CListBase::OnDeleteAllItems();
}

/*** A column in a list view control will be deleted *************************/
LRESULT CListCtrlEx::OnDeleteColumn(WPARAM wParam, LPARAM)
{
  return CListBase::OnDeleteColumn(wParam);
}

/*** An item from a list view control will be removed ************************/
LRESULT CListCtrlEx::OnDeleteItem(WPARAM wParam, LPARAM)
{
  return CListBase::OnDeleteItem(wParam);
}

/*** The list view control will be destroyed *********************************/
void CListCtrlEx::OnDestroy() 
{
	CListBase::OnDestroy();
}

/*** The background will be erased *******************************************/
BOOL CListCtrlEx::OnEraseBkgnd(CDC* pDC) 
{
  return CListBase::OnEraseBkgnd(pDC);
}

/*** A specific item of a list view control will be searched *****************/
LRESULT CListCtrlEx::OnFindItem(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnFindItem(wParam, lParam);
}

/*** The attributes of a list view control's column will be retrieved ********/
LRESULT CListCtrlEx::OnGetColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetColumn(wParam, lParam);
}

/*** The current left-to-right order of columns in a list view control *******/
/*** will be retrieved                                                 *******/
LRESULT CListCtrlEx::OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetColumnOrderArray(wParam, lParam);
}

/*** The width of a column in a list view control will be retrieved **********/
LRESULT CListCtrlEx::OnGetColumnWidth(WPARAM wParam, LPARAM)
{
  return CListBase::OnGetColumnWidth(wParam);
}

/*** Information needed to display a list view item **************************/
BOOL CListCtrlEx::OnGetdispinfo(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnGetdispinfo(pNMHDR);
}

/*** The extended list view style will be retrieved **************************/
LRESULT CListCtrlEx::OnGetExtendedStyle(WPARAM, LPARAM)
{
  return m_dwExtendedStyle;
}

/*** Some or all of a list view item's attributes will be retrieved **********/
LRESULT CListCtrlEx::OnGetItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnGetItem(lParam);
}

/*** The text of a list view item or subitem will be retrieved ***************/
LRESULT CListCtrlEx::OnGetItemText(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetItemText(wParam, lParam);
}

/*** The list-view item at a specified position will be determined ***********/
LRESULT CListCtrlEx::OnHitTest(WPARAM, LPARAM lParam)
{
  return CListBase::OnHitTest(lParam);
}

/*** List control has been scrolled horizontally *****************************/
void CListCtrlEx::OnHScroll(UINT, UINT, CScrollBar*)
{
  CListBase::OnHScroll();
}

/*** A new column in a list-view control will be inserted ********************/
LRESULT CListCtrlEx::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnInsertColumn(wParam, lParam);
}

/*** A new item in a list-view control will be inserted **********************/
LRESULT CListCtrlEx::OnInsertItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnInsertItem(lParam);
}

/*** A key has been pressed  *************************************************/
void CListCtrlEx::OnKeyDown(UINT nChar, UINT, UINT) 
{
  CListBase::OnKeyDown(nChar);
}

/*** A key has been released *************************************************/
void CListCtrlEx::OnKeyUp(UINT nChar, UINT, UINT) 
{
  CListBase::OnKeyUp(nChar);
}

/*** List control loses input focus ******************************************/
void CListCtrlEx::OnKillFocus(CWnd*) 
{
  CListBase::OnKillFocus();
}

/*** The user double-clicks the left mouse button ****************************/
void CListCtrlEx::OnLButtonDblClk(UINT, CPoint point) 
{
  CListBase::OnLButtonDblClk(point);
}

/*** The user presses the left mouse button **********************************/
void CListCtrlEx::OnLButtonDown(UINT, CPoint point) 
{
  CListBase::OnLButtonDown(point);
}

/*** The user releases the left mouse button *********************************/
void CListCtrlEx::OnLButtonUp(UINT, CPoint) 
{
  CListBase::OnLButtonUp();
}

/*** The mouse has been moved ************************************************/
void CListCtrlEx::OnMouseMove(UINT, CPoint point) 
{
	CListBase::OnMouseMove(point);
}

/*** Divider in header control has been dragged ******************************/
BOOL CListCtrlEx::OnNotify(WPARAM, LPARAM lParam, LRESULT*)
{
  return CListBase::OnNotify(lParam);
}

/*** The contents of the display area of a virtual list view control have ****/
/*** been changed                                                         ****/
BOOL CListCtrlEx::OnODCacheHint(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnODCacheHint(pNMHDR);
}

/*** The background color of the list view control will be set ***************/
LRESULT CListCtrlEx::OnSetBkColor(WPARAM, LPARAM)
{
  return CListBase::OnSetBkColor();
}

/*** The attributes of a list view column will be set ************************/
LRESULT CListCtrlEx::OnSetColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumn(wParam, lParam);
}

/*** The left-to-right order of columns in a list view control will be set ***/
LRESULT CListCtrlEx::OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumnOrderArray(wParam, lParam);
}

/*** The width of a column in a list view control will be changed ************/
LRESULT CListCtrlEx::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumnWidth(wParam, lParam);
}

/*** The extended list view style will be set ********************************/
LRESULT CListCtrlEx::OnSetExtendedStyle(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetExtendedStyle(wParam, lParam);
}

/*** List control gains input focus ******************************************/
void CListCtrlEx::OnSetFocus(CWnd*) 
{
  CListBase::OnSetFocus();
}

/*** An image list will be assigned ******************************************/
LRESULT CListCtrlEx::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetImageList(wParam, lParam);
}

/*** Some or all of a list view item's attributes will be set ****************/
LRESULT CListCtrlEx::OnSetItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnSetItem(lParam);
}

/*** The text of an item or a subitem in a list view control will be changed */
LRESULT CListCtrlEx::OnSetItemText(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetItemText(wParam, lParam);
}

/*** The items of a list view control will be sorted *************************/
LRESULT CListCtrlEx::OnSortItems(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSortItems(wParam, lParam);
}

/*** System colors have been changed *****************************************/
void CListCtrlEx::OnSysColorChange()
{
  CListBase::OnSysColorChange();
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
  ON_MESSAGE(LVM_DELETEALLITEMS, OnDeleteAllItems)
  ON_MESSAGE(LVM_DELETECOLUMN, OnDeleteColumn)
  ON_MESSAGE(LVM_DELETEITEM, OnDeleteItem)
  ON_MESSAGE(LVM_FINDITEM, OnFindItem)
  ON_MESSAGE(LVM_GETCOLUMN, OnGetColumn)
  ON_MESSAGE(LVM_GETCOLUMNORDERARRAY, OnGetColumnOrderArray)
  ON_MESSAGE(LVM_GETCOLUMNWIDTH, OnGetColumnWidth)
  ON_MESSAGE(LVM_GETEXTENDEDLISTVIEWSTYLE , OnGetExtendedStyle)
  ON_MESSAGE(LVM_GETITEM, OnGetItem)
  ON_MESSAGE(LVM_GETITEMTEXT, OnGetItemText)
  ON_MESSAGE(LVM_HITTEST, OnHitTest)
  ON_MESSAGE(LVM_INSERTCOLUMN, OnInsertColumn)
  ON_MESSAGE(LVM_INSERTITEM, OnInsertItem)
  ON_MESSAGE(LVM_SETBKCOLOR, OnSetBkColor)
  ON_MESSAGE(LVM_SETCOLUMN, OnSetColumn)
  ON_MESSAGE(LVM_SETCOLUMNORDERARRAY, OnSetColumnOrderArray)
  ON_MESSAGE(LVM_SETCOLUMNWIDTH, OnSetColumnWidth)
  ON_MESSAGE(LVM_SETEXTENDEDLISTVIEWSTYLE , OnSetExtendedStyle)
  ON_MESSAGE(LVM_SETIMAGELIST, OnSetImageList)
  ON_MESSAGE(LVM_SETITEM, OnSetItem)
  ON_MESSAGE(LVM_SETITEMTEXT, OnSetItemText)
  ON_MESSAGE(LVM_SORTITEMS, OnSortItems)
  ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT_EX(LVN_GETDISPINFO, OnGetdispinfo)
  ON_NOTIFY_REFLECT_EX(LVN_ODCACHEHINT, OnODCacheHint)
END_MESSAGE_MAP()


/*** Definition of class "CListViewEx" ***************************************/

IMPLEMENT_DYNCREATE(CListViewEx, CListView)

/*** Protected member functions **********************************************/

/*** A column header has been clicked ****************************************/
BOOL CListViewEx::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
  return CListBase::OnColumnclick(pNMHDR, pResult);
}

/*** An item in the column selection menu has been selected ******************/
BOOL CListViewEx::OnCommand(WPARAM wParam, LPARAM)
{
  return CListBase::OnCommand(wParam);
}

/*** The user has right clicked the mouse ************************************/
void CListViewEx::OnContextMenu(CWnd* pWnd, CPoint) 
{
  CListBase::OnContextMenu(pWnd);
}

/*** A list view (sub)item will be drawn *************************************/
void CListViewEx::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
  CListBase::OnCustomDraw(pNMHDR, pResult);
}

/*** All items from a list view control will be removed **********************/
LRESULT CListViewEx::OnDeleteAllItems(WPARAM, LPARAM)
{
  return CListBase::OnDeleteAllItems();
}

/*** A column in a list view control will be deleted *************************/
LRESULT CListViewEx::OnDeleteColumn(WPARAM wParam, LPARAM)
{
  return CListBase::OnDeleteColumn(wParam);
}

/*** An item from a list view control will be removed ************************/
LRESULT CListViewEx::OnDeleteItem(WPARAM wParam, LPARAM)
{
  return CListBase::OnDeleteItem(wParam);
}

/*** The list view control will be destroyed *********************************/
void CListViewEx::OnDestroy() 
{
	CListBase::OnDestroy();
}

/*** The background will be erased *******************************************/
BOOL CListViewEx::OnEraseBkgnd(CDC* pDC) 
{
  return CListBase::OnEraseBkgnd(pDC);
}

/*** A specific item of a list view control will be searched *****************/
LRESULT CListViewEx::OnFindItem(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnFindItem(wParam, lParam);
}

/*** The attributes of a list view control's column will be retrieved ********/
LRESULT CListViewEx::OnGetColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetColumn(wParam, lParam);
}

/*** The current left-to-right order of columns in a list view control *******/
/*** will be retrieved                                                 *******/
LRESULT CListViewEx::OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetColumnOrderArray(wParam, lParam);
}

/*** The width of a column in a list view control will be retrieved **********/
LRESULT CListViewEx::OnGetColumnWidth(WPARAM wParam, LPARAM)
{
  return CListBase::OnGetColumnWidth(wParam);
}

/*** Information needed to display a list view item **************************/
BOOL CListViewEx::OnGetdispinfo(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnGetdispinfo(pNMHDR);
}

/*** The extended list view style will be retrieved **************************/
LRESULT CListViewEx::OnGetExtendedStyle(WPARAM, LPARAM)
{
  return m_dwExtendedStyle;
}

/*** Some or all of a list view item's attributes will be retrieved **********/
LRESULT CListViewEx::OnGetItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnGetItem(lParam);
}

/*** The text of a list view item or subitem will be retrieved ***************/
LRESULT CListViewEx::OnGetItemText(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnGetItemText(wParam, lParam);
}

/*** The list-view item at a specified position will be determined ***********/
LRESULT CListViewEx::OnHitTest(WPARAM, LPARAM lParam)
{
  return CListBase::OnHitTest(lParam);
}

/*** List control has been scrolled horizontally *****************************/
void CListViewEx::OnHScroll(UINT, UINT, CScrollBar*)
{
  CListBase::OnHScroll();
}

/*** A new column in a list-view control will be inserted ********************/
LRESULT CListViewEx::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnInsertColumn(wParam, lParam);
}

/*** A new item in a list-view control will be inserted **********************/
LRESULT CListViewEx::OnInsertItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnInsertItem(lParam);
}

/*** A key has been pressed  *************************************************/
void CListViewEx::OnKeyDown(UINT nChar, UINT, UINT) 
{
  CListBase::OnKeyDown(nChar);
}

/*** A key has been released *************************************************/
void CListViewEx::OnKeyUp(UINT nChar, UINT, UINT) 
{
  CListBase::OnKeyUp(nChar);
}

/*** List control loses input focus ******************************************/
void CListViewEx::OnKillFocus(CWnd*) 
{
  CListBase::OnKillFocus();
}

/*** The user double-clicks the left mouse button ****************************/
void CListViewEx::OnLButtonDblClk(UINT, CPoint point) 
{
  CListBase::OnLButtonDblClk(point);
}

/*** The user presses the left mouse button **********************************/
void CListViewEx::OnLButtonDown(UINT, CPoint point) 
{
  CListBase::OnLButtonDown(point);
}


/*** The user releases the left mouse button *********************************/
void CListViewEx::OnLButtonUp(UINT, CPoint) 
{
  CListBase::OnLButtonUp();
}

/*** The mouse has been moved ************************************************/
void CListViewEx::OnMouseMove(UINT, CPoint point) 
{
	CListBase::OnMouseMove(point);
}

/*** Divider in header control has been dragged ******************************/
BOOL CListViewEx::OnNotify(WPARAM, LPARAM lParam, LRESULT*)
{
  return CListBase::OnNotify(lParam);
}

/*** The contents of the display area of a virtual list view control have ****/
/*** been changed                                                         ****/
BOOL CListViewEx::OnODCacheHint(NMHDR* pNMHDR, LRESULT*)
{
  return CListBase::OnODCacheHint(pNMHDR);
}

/*** The background color of the list view control will be set ***************/
LRESULT CListViewEx::OnSetBkColor(WPARAM, LPARAM)
{
  return CListBase::OnSetBkColor();
}

/*** The attributes of a list view column will be set ************************/
LRESULT CListViewEx::OnSetColumn(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumn(wParam, lParam);
}

/*** The left-to-right order of columns in a list view control will be set ***/
LRESULT CListViewEx::OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumnOrderArray(wParam, lParam);
}

/*** The width of a column in a list view control will be changed ************/
LRESULT CListViewEx::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetColumnWidth(wParam, lParam);
}

/*** The extended list view style will be set ********************************/
LRESULT CListViewEx::OnSetExtendedStyle(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetExtendedStyle(wParam, lParam);
}

/*** List control gains input focus ******************************************/
void CListViewEx::OnSetFocus(CWnd*) 
{
  CListBase::OnSetFocus();
}

/*** An image list will be assigned ******************************************/
LRESULT CListViewEx::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetImageList(wParam, lParam);
}

/*** Some or all of a list view item's attributes will be set ****************/
LRESULT CListViewEx::OnSetItem(WPARAM, LPARAM lParam)
{
  return CListBase::OnSetItem(lParam);
}

/*** The state of an item in a list view control will be changed *************/
LRESULT CListViewEx::OnSetItemText(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSetItemText(wParam, lParam);
}

/*** The items of a list view control will be sorted *************************/
LRESULT CListViewEx::OnSortItems(WPARAM wParam, LPARAM lParam)
{
  return CListBase::OnSortItems(wParam, lParam);
}

/*** System colors have been changed *****************************************/
void CListViewEx::OnSysColorChange()
{
  CListBase::OnSysColorChange();
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(CListViewEx, CListView)
	//{{AFX_MSG_MAP(CListViewEx)
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
  ON_MESSAGE(LVM_DELETEALLITEMS, OnDeleteAllItems)
  ON_MESSAGE(LVM_DELETECOLUMN, OnDeleteColumn)
  ON_MESSAGE(LVM_DELETEITEM, OnDeleteItem)
  ON_MESSAGE(LVM_FINDITEM, OnFindItem)
  ON_MESSAGE(LVM_GETCOLUMN, OnGetColumn)
  ON_MESSAGE(LVM_GETCOLUMNORDERARRAY, OnGetColumnOrderArray)
  ON_MESSAGE(LVM_GETCOLUMNWIDTH, OnGetColumnWidth)
  ON_MESSAGE(LVM_GETEXTENDEDLISTVIEWSTYLE , OnGetExtendedStyle)
  ON_MESSAGE(LVM_GETITEM, OnGetItem)
  ON_MESSAGE(LVM_GETITEMTEXT, OnGetItemText)
  ON_MESSAGE(LVM_HITTEST, OnHitTest)
  ON_MESSAGE(LVM_INSERTCOLUMN, OnInsertColumn)
  ON_MESSAGE(LVM_INSERTITEM, OnInsertItem)
  ON_MESSAGE(LVM_SETBKCOLOR, OnSetBkColor)
  ON_MESSAGE(LVM_SETCOLUMN, OnSetColumn)
  ON_MESSAGE(LVM_SETCOLUMNORDERARRAY, OnSetColumnOrderArray)
  ON_MESSAGE(LVM_SETCOLUMNWIDTH, OnSetColumnWidth)
  ON_MESSAGE(LVM_SETEXTENDEDLISTVIEWSTYLE , OnSetExtendedStyle)
  ON_MESSAGE(LVM_SETIMAGELIST, OnSetImageList)
  ON_MESSAGE(LVM_SETITEM, OnSetItem)
  ON_MESSAGE(LVM_SETITEMTEXT, OnSetItemText)
  ON_MESSAGE(LVM_SORTITEMS, OnSortItems)
  ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT_EX(LVN_GETDISPINFO, OnGetdispinfo)
  ON_NOTIFY_REFLECT_EX(LVN_ODCACHEHINT, OnODCacheHint)
END_MESSAGE_MAP()


/*** Definition of helper class "CListCtrlHelper" ****************************/
class CListCtrlHelper: public CListCtrl
{
  public:

  LRESULT Default      ();
  LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlHelper)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListCtrlHelper)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/*** Public member functions *************************************************/

/*** Message handlers ********************************************************/
LRESULT CListCtrlHelper::Default()
{
  return CListCtrl::Default();
}

LRESULT CListCtrlHelper::DefWindowProc(UINT message, WPARAM wParam,
                                       LPARAM lParam)
{
  return CListCtrl::DefWindowProc(message, wParam, lParam);
}

void CListCtrlHelper::OnDestroy() 
{
	CListCtrl::OnDestroy();
}

void CListCtrlHelper::OnMouseMove(UINT nFlags, CPoint point) 
{
	CListCtrl::OnMouseMove(nFlags, point);
}

/*** Table of message handlers ***********************************************/
BEGIN_MESSAGE_MAP(CListCtrlHelper, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlHelper)
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*** Definition of "workhorse" class "CListBase" *****************************/

CListBase::VISUAL_STYLE CListBase::m_visualStyle = Unknown; // visual style?
const int               CListBase::m_nFirstColXOff = 2; // x-off of first col
const int               CListBase::m_nNextColXOff  = 6; // y-off of other cols

/*** Public member functions *************************************************/

/*** Constructor *************************************************************/
CListBase::CListBase()
{
  if (m_visualStyle == Unknown)
  {
    m_visualStyle = NotPresent;

    HINSTANCE hinstDll;
    hinstDll = LoadLibrary(_T("COMCTL32.DLL"));
	
    if (hinstDll)
    {
      DLLGETVERSIONPROC pDllGetVersion =
        reinterpret_cast<DLLGETVERSIONPROC>(GetProcAddress(hinstDll,
          "DllGetVersion"));

      // Because some DLLs might not implement this function, you must test for
      // it explicitly. Depending on the particular DLL, the lack of a
      // DllGetVersion function can be a useful indicator of the version.
      if (pDllGetVersion)
      {
        DLLVERSIONINFO dvi = {sizeof(DLLVERSIONINFO)};

        if (SUCCEEDED((*pDllGetVersion)(&dvi)) && dvi.dwMajorVersion >= 6)
          m_visualStyle = Present;
      }
      
      FreeLibrary(hinstDll);
    }
  }

  m_nIconXOff            = 4;
  m_pListCtrl            = 0;
  m_nColumnHidingAllowed = 0;
  m_bSortIconEnabled     = FALSE;
  m_bColorSortColumn     = FALSE;
  m_nSortColumn          = 0;
  m_bKeepLabelLeft       = false;
  m_bLocked              = false;
  m_bControl             = false;
  m_bIconXOffCalculated  = false;
  m_dwExtendedStyle      = 0;
  m_nHotItem             = -1;
  m_dwHotLite            = /*_winver <= 0x0400 ?
                           RGB(0, 0, 128) :*/ GetSysColor(COLOR_HOTLIGHT);
  m_hcursorCustom        = 0;
  m_hcursorArrow         = 0;
  m_hcursorHand          = 0;
  m_nFirstCachedItem     = INT_MAX;
  m_nLastCachedItem      = 0;
  m_bOnGetDispinfo       = false;
}

/*** Destructor **************************************************************/
CListBase::~CListBase()
{
  // remove remembered column data
  for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; i--)
    delete m_aColumnData[i];

  //TODO:zyl
  /*if (_winver <= 0x400 && m_hcursorHand) DestroyCursor(m_hcursorHand);*/
}

/*** Enable or disable coloring of sort column *******************************/
#if _MSC_VER >= 1300
  #pragma runtime_checks("c", off)  // due to a flaw in the definition of
#endif                              // Get[R|G|B]Value
void CListBase::ColorSortColumn(BOOL bEnable, int nSortColumn)
{
  ASSERT(m_pListCtrl);

  if (bEnable == m_bColorSortColumn &&
      (nSortColumn == 0 || nSortColumn == m_nSortColumn)) return;

  if (bEnable)
  {
    // 256 colors --> don't color sort column
    CDC* pDC    = m_pListCtrl->GetDC();
    bool bColor = pDC->GetDeviceCaps(BITSPIXEL) > 8;

    m_pListCtrl->ReleaseDC(pDC);
    if (!bColor) return;
  }

  if (bEnable != m_bColorSortColumn)
  {
    if (bEnable)
    {
      DWORD dwColNormalColor = m_pListCtrl->GetBkColor();

      // emulate sort column coloring of Windows XP explorer
      UINT nRed   = GetRValue(dwColNormalColor);
      UINT nGreen = GetGValue(dwColNormalColor);
      UINT nBlue  = GetBValue(dwColNormalColor);

      if (nRed > 240 && nGreen > 240 && nBlue > 240)
      {
        nRed   -= 8;
        nGreen -= 8;
        nBlue  -= 8;
      }
      else
      {
        if (nRed   < 232) nRed   += nRed   / 10; else nRed   = 255;
        if (nGreen < 232) nGreen += nGreen / 10; else nGreen = 255;
        if (nBlue  < 232) nBlue  += nBlue  / 10; else nBlue  = 255;
      }
      m_dwColSortColor = RGB(nRed, nGreen, nBlue);
    }
    m_bColorSortColumn = bEnable;
  }
  if (nSortColumn != 0) m_nSortColumn = nSortColumn;
  m_pListCtrl->Invalidate();
}
#if _MSC_VER >= 1300
  #pragma runtime_checks("c", restore)
#endif

/*** Draw small icon *********************************************************/
void CListBase::DrawSmallIcon(CDC* pDC, LVITEM* pItem, LPRECT pRect)
{
  ASSERT(m_pListCtrl);

  if (pItem->iImage > 0)
  {
    CImageList* pimglst = m_pListCtrl->GetImageList(LVSIL_SMALL);

    if (pimglst)
    {
      IMAGEINFO imgInfo;

      if (pimglst->GetImageInfo(pItem->iImage, &imgInfo))
      {
        pimglst->DrawIndirect(
          pDC, pItem->iImage, CPoint(pRect->left, pRect->top),
          CSize(__min(pRect->right - pRect->left + 1,
                      imgInfo.rcImage.right - imgInfo.rcImage.left),
                __min(pRect->bottom - pRect->top + 1,
                      imgInfo.rcImage.bottom - imgInfo.rcImage.top)),
          CPoint(0, 0),
          (pItem->state & LVIS_SELECTED &&
          m_pListCtrl->GetFocus() == m_pListCtrl ?
          ILD_SELECTED : ILD_NORMAL) | pItem->state & LVIS_OVERLAYMASK,
          SRCCOPY, CLR_NONE);
      }
    }
  }
}

/*** Draw state icon *********************************************************/
void CListBase::DrawStateIcon(CDC* pDC, LVITEM* pItem, LPRECT pRect)
{
  ASSERT(m_pListCtrl);

  int nImage = (pItem->state & LVIS_STATEIMAGEMASK) >> 12;

  if (nImage > 0)
  {
    CImageList* pimglst = m_pListCtrl->GetImageList(LVSIL_STATE);

    if (pimglst)
    {
      IMAGEINFO imgInfo;

      // image indices are zero-based
      if (pimglst->GetImageInfo(--nImage, &imgInfo))
      {
        pimglst->DrawIndirect(
        pDC, nImage, CPoint(pRect->left, pRect->top),
        CSize(__min(pRect->right - pRect->left + 1,
                    imgInfo.rcImage.right - imgInfo.rcImage.left),
              __min(pRect->bottom - pRect->top + 1,
                    imgInfo.rcImage.bottom - imgInfo.rcImage.top)),
        CPoint(0, 0),
        pItem->state & LVIS_SELECTED &&
        m_pListCtrl->GetFocus() == m_pListCtrl ? ILD_SELECTED : ILD_NORMAL,
        SRCCOPY, CLR_NONE);
      }
    }
  }
}

/*** Allow or disallow the hiding of a column ********************************/
void CListBase::EnableColumnHiding(int nColumn, bool bEnableIt)
{
  if (nColumn >= 0 && nColumn < m_aColumnData.GetSize())
    if (bEnableIt)
    {
      if (!m_aColumnData[nColumn]->m_bHidingAllowed)
        // The first column is allowed to be hidden only
        // if the list view control is owner-drawn.
        if (nColumn > 0 || m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
        {
          m_aColumnData[nColumn]->m_bHidingAllowed = true;
          ++m_nColumnHidingAllowed;
        }
    }
    else
      if (m_aColumnData[nColumn]->m_bHidingAllowed)
      {
        ShowColumn(nColumn);    // display column if hidden
        m_aColumnData[nColumn]->m_bHidingAllowed = false;
        --m_nColumnHidingAllowed;
      }

  ASSERT(m_nColumnHidingAllowed >= 0);
}

/*** Draw the label of an item or subitem ************************************/
void CListBase::DrawSubItemText(CDC* pDC, LVITEM* pItem, LVCOLUMN* pColumn,
                                LPRECT pRect)
{
  if (*pItem->pszText)
    if (pRect->right - pRect->left > 0)
      pDC->DrawText(pItem->pszText, -1, pRect,
                    (pColumn->fmt & LVCFMT_CENTER ? DT_CENTER :
                     pColumn->fmt & LVCFMT_RIGHT  ? DT_RIGHT  : DT_LEFT) |
                     DT_END_ELLIPSIS | DT_SINGLELINE | DT_NOPREFIX |
                     DT_NOCLIP | DT_VCENTER);
}

/*** Duplicate column information ********************************************/
LVCOLUMN* CListBase::DupLVColumn(LVCOLUMN* pLVColumn) const
{
  LVCOLUMN* pLVColumn2 = new LVCOLUMN(*pLVColumn);

  // mask unnecessary fields
  if (!(pLVColumn2->mask & LVCF_FMT)) pLVColumn2->fmt = 0;
  if (!(pLVColumn2->mask & LVCF_IMAGE)) pLVColumn2->iImage = 0;
  if (!(pLVColumn2->mask & LVCF_ORDER)) pLVColumn2->iOrder = 0;
  if (!(pLVColumn2->mask & LVCF_SUBITEM)) pLVColumn2->iSubItem = 0;
  if (pLVColumn2->mask & LVCF_TEXT)
  {
    ASSERT(pLVColumn2->pszText);
    pLVColumn2->pszText = new TCHAR[_tcslen(pLVColumn->pszText) + 1];
    _tcscpy(pLVColumn2->pszText, pLVColumn->pszText);
  }
  else
    pLVColumn2->pszText = 0;
  if (!(pLVColumn2->mask & LVCF_WIDTH)) pLVColumn2->cx = 0;
  pLVColumn2->cchTextMax = 0;

  return pLVColumn2;
}

/*** Duplicate item information **********************************************/
LVITEM* CListBase::DupLVItem(LVITEM* pLVItem) const
{
  LVITEM* pLVItem2 = new LVITEM(*pLVItem);

  // mask unnecessary fields
  if (!(pLVItem2->mask & LVIF_IMAGE)) pLVItem2->iImage = 0;
  if (!(pLVItem2->mask & LVIF_INDENT)) pLVItem2->iIndent = 0;
  if (!(pLVItem2->mask & LVIF_PARAM)) pLVItem2->lParam = 0;
  if (pLVItem2->mask & LVIF_STATE)
    pLVItem2->state &= pLVItem2->stateMask;
  else
  {
    pLVItem2->state     = 0;
    pLVItem2->stateMask = 0;
  }
  if (pLVItem2->mask & LVIF_TEXT)
  {
    ASSERT(pLVItem2->pszText);
    if (pLVItem2->pszText != LPSTR_TEXTCALLBACK)
    {
      pLVItem2->pszText = new TCHAR[_tcslen(pLVItem->pszText) + 1];
      _tcscpy(pLVItem2->pszText, pLVItem->pszText);
    }
  }
  else
    pLVItem2->pszText = 0;
  pLVItem2->iSubItem   = 0;
  pLVItem2->cchTextMax = 0;

  return pLVItem2;
}

/*** Enable or disable sort icon *********************************************/
void CListBase::EnableSortIcon(BOOL bEnable, int nSortColumn)
{
  ASSERT(m_pListCtrl);
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  m_bSortIconEnabled = bEnable;
  if (nSortColumn != 0) m_nSortColumn = nSortColumn;
  if (bEnable && m_visualStyle == NotPresent)
  {
    CreateSortIcons                           ();
    m_pListCtrl->GetHeaderCtrl()->SetImageList(&m_imglstSortIcons);
  }
  SetSortIcon();            // display or hide sort icon
}

/*** Gets the position of the first checked item in the list view control ****/
POSITION CListBase::GetFirstCheckedItemPosition() const
{
  ASSERT(m_pListCtrl);

  int nItemCount = m_pListCtrl->GetItemCount();

  for (int nItem = 0; nItem < nItemCount; ++nItem)
    if (m_pListCtrl->GetCheck(nItem))
      return reinterpret_cast<POSITION>(static_cast<INT_PTR>(nItem + 1));

  return 0;
}

/*** Gets the index of the next checked item in the list view control ********/
int CListBase::GetNextCheckedItem(POSITION& pos) const
{
  ASSERT(pos);
  ASSERT(m_pListCtrl);
  
  int nOldPos    = static_cast<int>(reinterpret_cast<INT_PTR>(pos));
  int nItemCount = m_pListCtrl->GetItemCount();

  pos = 0;
  for (int nItem = nOldPos; nItem < nItemCount; ++nItem)
    if (m_pListCtrl->GetCheck(nItem))
    {
      pos = reinterpret_cast<POSITION>(static_cast<INT_PTR>(nItem + 1));
      break;
    }

  return nOldPos - 1;
}
  
/*** Get attributes of this list view control ********************************/
bool CListBase::GetState(LPBYTE* ppState, LPUINT pnStateLen) const
{
  ASSERT(m_pListCtrl);

  int nColumnCount = static_cast<int>(m_aColumnData.GetSize());

  if (nColumnCount > 0 && ppState)
  {
    UINT nStateLen =
      2 * sizeof(int) + nColumnCount * (sizeof(bool) + 2 * sizeof(int));

    *ppState = new BYTE[nStateLen];
    LPBYTE p = *ppState;

    *reinterpret_cast<LPINT>(p) = nColumnCount;
    p                          += sizeof(int);
    *reinterpret_cast<LPINT>(p) = m_nSortColumn;

    for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
    {
      p                          += sizeof(int);
      *reinterpret_cast<bool*>(p) = m_aColumnData[nColumn]->m_bHidingAllowed ?
                                    m_aColumnData[nColumn]->m_bVisible : true;
      p                          += sizeof(bool);
      *reinterpret_cast<LPINT>(p) = m_aColumnData[nColumn]->m_bVisible   ?
                                    m_pListCtrl->GetColumnWidth(nColumn) :
                                    m_aColumnData[nColumn]->m_nWidth,
      p                          += sizeof(int);
      *reinterpret_cast<LPINT>(p) = m_aColumnData[nColumn]->m_nOrder;
    }

    if (pnStateLen) *pnStateLen = nStateLen;
    return true;
  }
  else
    return false;
}

/*** Small icon always should be kept left ***********************************/
bool CListBase::KeepLabelLeft(bool bKeepLeft)
{
  bool bSuccess = true;

  if (bKeepLeft)
    if ((m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED) == 0)
    {
      bKeepLeft = false;
      bSuccess  = false;
    }

  if (bSuccess && bKeepLeft != m_bKeepLabelLeft)
  {
    m_bKeepLabelLeft = bKeepLeft;
    m_pListCtrl->Invalidate();
  }
  return bSuccess;
}

/*** Restore attributes of this list view control ****************************/
bool CListBase::RestoreState(LPCTSTR pszSection, LPCTSTR pszEntry)
{
  ASSERT(m_pListCtrl);

  bool bSuccess = false;

  if (static_cast<int>(m_aColumnData.GetSize()) > 0)
  {
    LPBYTE pState;
    UINT   nStateLen;

    if (AfxGetApp()->GetProfileBinary(pszSection, pszEntry, &pState,
                                      &nStateLen))
    {
      bSuccess = SetState(pState, nStateLen);
      delete[] pState;
    }
  }

  return bSuccess;
}

/*** Save attributes of this list view control *******************************/
bool CListBase::SaveState(LPCTSTR pszSection, LPCTSTR pszEntry) const
{
  LPBYTE pState;
  UINT   nStateLen;

  if (GetState(&pState, &nStateLen))           // get current state
  {
    bool bSuccess =
      AfxGetApp()->WriteProfileBinary(pszSection, pszEntry, pState, nStateLen)
      != FALSE;

    delete[] pState;
    return bSuccess;
  }
  else
    return false;
}

/*** Set column to be sorted *************************************************/
void CListBase::SetSortColumn(int nColumn)
{
  ASSERT(abs(nColumn) <= m_aColumnData.GetSize());
  ASSERT(m_pListCtrl);

  if (nColumn != m_nSortColumn)
  {
    m_nSortColumn = nColumn;
    SetSortIcon();
    if (abs(nColumn) != abs(m_nSortColumn)) m_pListCtrl->Invalidate();
  }
}

/*** Set attributes of this list view control ********************************/
bool CListBase::SetState(LPBYTE pState, UINT nStateLen)
{
  ASSERT(m_pListCtrl);

  int nColumnCount = static_cast<int>(m_aColumnData.GetSize());

  if (nColumnCount                    > 0                           &&
      nStateLen                        ==
      2*sizeof(int) + nColumnCount * (sizeof(bool) + 2*sizeof(int)) &&
      *reinterpret_cast<LPINT>(pState) == nColumnCount)
  {
    pState += sizeof(int);

    int nColumn = *reinterpret_cast<LPINT>(pState);
    if (abs(nColumn) <= nColumnCount)
      SetSortColumn(nColumn);
    else
      return false;                       // wrong sort column

    for (nColumn = 0; nColumn < nColumnCount; nColumn++)
    {
      COLUMN_DATA* pColData = m_aColumnData[nColumn];

      // restore display status of column
      pState += sizeof(int);
      bool bVisible = *reinterpret_cast<bool*>(pState);
      if (bVisible != pColData->m_bVisible)
        if (pColData->m_bHidingAllowed || !pColData->m_bVisible)
          ShowColumn(nColumn, bVisible);
      pState += sizeof(bool);

      // restore width of column
      m_pListCtrl->SetColumnWidth(nColumn, *reinterpret_cast<LPINT>(pState));
      pState += sizeof(int);

      // restore column order
      int nOrder = *reinterpret_cast<LPINT>(pState);
      if (nOrder < nColumnCount)
        pColData->m_nOrder = nOrder;
      else
        return false;
    }

    // set column order
    LPINT pnColOrder = new int[nColumnCount];
    for (nColumn = 0; nColumn < nColumnCount; nColumn++)
      pnColOrder[m_aColumnData[nColumn]->m_nOrder] = nColumn;
    m_pListCtrl->SetColumnOrderArray(nColumnCount, pnColOrder);
    delete[] pnColOrder;
  }

  return true;
}

/*** Show or hide an individual column ***************************************/
void CListBase::ShowColumn(int nColumn, bool bShowIt)
{
  ASSERT(m_pListCtrl);
  ASSERT(nColumn >= 0 && nColumn < m_aColumnData.GetSize());

  if (m_aColumnData[nColumn]->m_bHidingAllowed)
    if (bShowIt)
    {
      if (!m_aColumnData[nColumn]->m_bVisible)
      {
        // show column
        bool bNoColumnWasVisible = true;

        for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; i--)
          if (m_aColumnData[i]->m_bVisible)
          {
            bNoColumnWasVisible = false;
            break;
          }

        m_aColumnData[nColumn]->m_bVisible = true;

        int      nPhysicalColumn = GetPhysicalIndex(nColumn);
        LVCOLUMN lvColumn        = *m_aColumnData[nColumn]->m_pLVColumn;

        lvColumn.mask  |= LVCF_ORDER;
        lvColumn.iOrder = GetPhysicalOrder(m_aColumnData[nColumn]->m_nOrder);
        if (m_pListCtrl->DefWindowProc(LVM_INSERTCOLUMN,
                                       nPhysicalColumn,
                                       reinterpret_cast<LPARAM>(&lvColumn)) !=
            -1)
        {
          if (nPhysicalColumn == 0)
            // rejustify first column of listview control to enable a right-
            // justified or centerd first column
            JustifyFirstColumn(lvColumn.fmt);

          if (m_nSortColumn != 0 && abs(m_nSortColumn) - 1 == nColumn)
            // restore sort icon
            SetSortIcon();

          if (!(m_pListCtrl->GetStyle() & LVS_OWNERDATA))
          {
            if (nPhysicalColumn > 0)
              for (int nItem = m_pListCtrl->GetItemCount(); --nItem >= 0;)
              {
                LVITEM lvItem = {LVIF_PARAM, nItem, 0};

                if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                              reinterpret_cast<LPARAM>(&lvItem)))
                {
                  LVITEM* pLVItem =
                    reinterpret_cast<ITEM_DATA*>(
                      lvItem.lParam)->m_apLVItem[nColumn];

                  pLVItem->iItem    = nItem;
                  pLVItem->iSubItem = nColumn;
                  m_pListCtrl->SetItem(pLVItem);
                }
              }
          }

          m_pListCtrl->SetColumnWidth(nColumn,
                                      m_aColumnData[nColumn]->m_nWidth);
        }
      }
    }
    else
      if (m_aColumnData[nColumn]->m_bVisible)
      {
        // hide column
        int nPhysicalColumn = GetPhysicalIndex(nColumn);

        m_aColumnData[nColumn]->m_nWidth =
          m_pListCtrl->GetColumnWidth(nColumn);
        m_pListCtrl->DefWindowProc(LVM_DELETECOLUMN, nPhysicalColumn, 0);
        m_aColumnData[nColumn]->m_bVisible = false;
      }
}

/*** Private member functions ************************************************/

/*** Compare function for sorting of list view control ***********************/
int CALLBACK CListBase::CompareFunc(LPARAM lParam1, LPARAM lParam2,
                                    LPARAM lParamSort)
{
  CListBase* pThis = reinterpret_cast<CListBase*>(lParamSort);

  return pThis->m_pfnLVCompare(reinterpret_cast<ITEM_DATA*>(lParam1)->m_lParam,
                               reinterpret_cast<ITEM_DATA*>(lParam2)->m_lParam,
                               pThis->m_lParamSort);                 
}

/*** Create image list with sort icons ***************************************/
void CListBase::CreateSortIcons()
{
  if (!m_imglstSortIcons.m_hImageList)
  {
    COLORMAP cm = {RGB(0, 0, 0), GetSysColor(COLOR_GRAYTEXT)};

    m_imglstSortIcons.Create   (9, 5, ILC_COLOR24 | ILC_MASK, 2, 0);
    m_bmpUpArrow.LoadMappedBitmap(IDB_HDRUP, 0, &cm, 1);
    m_nUpArrow = m_imglstSortIcons.Add(&m_bmpUpArrow, RGB(255, 255, 255));
    m_bmpDownArrow.LoadMappedBitmap(IDB_HDRDOWN, 0, &cm, 1);
    m_nDownArrow = m_imglstSortIcons.Add(&m_bmpDownArrow, RGB(255, 255, 255));
  }
}

/*** Draw the entire item (called if window has style LVS_OWNERDRAWFIXED) ****/
void CListBase::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  ASSERT(m_pListCtrl);

  LVITEM* pItem = GetLVITEM(lpDrawItemStruct->itemID);

  DWORD dwStyle          = m_pListCtrl->GetStyle();
  bool  bAlwaysSelected  = pItem->state & LVIS_SELECTED &&
                           (dwStyle & LVS_SHOWSELALWAYS) != 0;
  bool  bLVHasFocus      = m_pListCtrl->GetFocus() == m_pListCtrl;
  bool  bItemHasFocus    = pItem->state & LVIS_FOCUSED  && bLVHasFocus;
	bool  bSelected        = (pItem->state & LVIS_SELECTED) != 0;
	bool  bReallySelected  = bSelected && bLVHasFocus;
  bool  bFullRowSelected = (m_dwExtendedStyle & LVS_EX_FULLROWSELECT) != 0;

  CRect rcItem;                   // rectangle bounding complete item
  m_pListCtrl->GetItemRect(pItem->iItem, rcItem, LVIR_BOUNDS);

  CRect rcSubItem0;               // rectangle bounding subitem 0
  GetRealSubItemRect(pItem->iItem, 0, LVIR_BOUNDS, rcSubItem0);

  CRect rcLabel;                  // rectangle bounding item label
  GetRealSubItemRect(pItem->iItem, 0, LVIR_LABEL, rcLabel);

	CRect rcSelection;              // rectangle bounding selection
  if (bFullRowSelected)
  {
	  rcSelection = rcItem;
    if (IndexToOrder(0) == 0 || m_bKeepLabelLeft)
    {
      rcSelection.left = rcLabel.left;
      int nWidthOfCol0 =
        static_cast<int>(
          m_pListCtrl->DefWindowProc(LVM_GETCOLUMNWIDTH, OrderToIndex(0), 0));
      if (rcSelection.left > nWidthOfCol0) rcSelection.left = nWidthOfCol0;
    }
  }

	CDC*   pDC          = CDC::FromHandle(lpDrawItemStruct->hDC);
  CBrush brushHiLite;
  DWORD  dwNormalText = GetSysColor(COLOR_WINDOWTEXT);
  DWORD  dwHiLiteBk   = 0;

	if (bReallySelected)
	{
    dwHiLiteBk =
      pItem->iItem == m_nHotItem ? m_dwHotLite : GetSysColor(COLOR_HIGHLIGHT);
    brushHiLite.CreateSolidBrush(dwHiLiteBk);
	}
	else if (bAlwaysSelected)
  {
    dwHiLiteBk = GetSysColor(COLOR_3DFACE);
    brushHiLite.CreateSolidBrush(dwHiLiteBk);
  }

  CFont* pfontPrev          = 0;
  CFont* pfontHotUnderlined = 0;
  bool   bHotUnderlining    = false;
  if (m_dwExtendedStyle & LVS_EX_TWOCLICKACTIVATE                           &&
      (bSelected || bAlwaysSelected)                                        ||
      (m_dwExtendedStyle & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE)) ==
      (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE)                       &&
      pItem->iItem == m_nHotItem)
  {
    CFont*  pFont = m_pListCtrl->GetFont();
    LOGFONT logFont;

    if (pFont->GetLogFont(&logFont))
    {
      logFont.lfUnderline = TRUE;
      pfontHotUnderlined  = new CFont;
      pfontHotUnderlined->CreateFontIndirect(&logFont);
      pfontPrev           = pDC->SelectObject(pfontHotUnderlined);
      bHotUnderlining     = true;
    }
  }

  LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;

  // display all subitems
  int nIndex;
	for (int nColumn = 0;
       m_pListCtrl->DefWindowProc(LVM_GETCOLUMN,
                                  nIndex = OrderToIndex(nColumn),
                                  reinterpret_cast<LPARAM>(&lvc));
       nColumn++)
  {
    LVITEM* pSubItem  = nIndex > 0 ? GetLVITEM(pItem->iItem, nIndex) : pItem;
    CRect   rcSubItem;                  // rectangle bounding subitem
	  CRect   rcText;                     // output rectangle
    int     nAbsSortColumn = abs(m_nSortColumn) - 1;

    // background color of current column
    DWORD  dwBkColor = m_bColorSortColumn                        &&
                       m_nSortColumn != 0                        &&
                       m_aColumnData[nAbsSortColumn]->m_bVisible &&
                       nIndex == GetPhysicalIndex(nAbsSortColumn) ?
                       m_dwColSortColor : m_pListCtrl->GetBkColor();
    CBrush brushBk(dwBkColor);

    // consider column margins
    if (nColumn > 0)
    {
      // move output rectangle over next column
      rcSubItem.left   = rcSubItem.right;
      rcSubItem.right += lvc.cx;
    }
    else
    {
      rcSubItem       = rcItem;
      rcSubItem.right = rcSubItem.left + lvc.cx;
    }

    if (nIndex == 0 && !m_bKeepLabelLeft || nColumn == 0 && m_bKeepLabelLeft)
    {
      rcText        = rcLabel;
      rcText.left  += m_nFirstColXOff;
      rcText.right -= nIndex > 0 ? m_nNextColXOff : m_nFirstColXOff;
    }
    else
    {
      rcText        = rcSubItem;
      rcText.left  += m_nNextColXOff;
      rcText.right -= m_nNextColXOff;

      // take subitem image into consideration
      if (!m_bKeepLabelLeft                        &&
          nIndex > 0                               &&
          m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES &&
          pSubItem->iImage)
      {
        CRect rcIcon;

        if (m_pListCtrl->GetSubItemRect(pItem->iItem, nIndex, LVIR_ICON,
                                        rcIcon)) rcText.left += rcIcon.Width();
      }
    }

    int  nLabelWidth = GetLabelWidth(pDC, pSubItem, rcText.Width());
    bool bHiLite     = false;

    if (bReallySelected ||
        bAlwaysSelected ||
        bItemHasFocus && !bFullRowSelected)
      if (nIndex == 0 && nColumn != 0 && !m_bKeepLabelLeft && !bFullRowSelected
          ||
          nColumn == 0 && (m_bKeepLabelLeft || nIndex == 0))
      {
        // calculate selection area
        CRect rcSubItemSelection(rcLabel);

        if (!bFullRowSelected)
        {
          int nFormat = nIndex == 0 && nColumn == 0 || !m_bKeepLabelLeft ?
                        m_nFormatOfSubItem0 : lvc.fmt & LVCFMT_JUSTIFYMASK;

          switch (nFormat)
          {
            case LVCFMT_LEFT:
              rcSubItemSelection.right =
                rcSubItemSelection.left +
                  m_nFirstColXOff + nLabelWidth + m_nNextColXOff;
              break;

            case LVCFMT_RIGHT:
              rcSubItemSelection.left =
                rcSubItemSelection.right -
                  m_nFirstColXOff - nLabelWidth - m_nNextColXOff;
              break;

            case LVCFMT_CENTER:
            {
              int nSelectionWidth =
                m_nNextColXOff + nLabelWidth + m_nNextColXOff;
              rcSubItemSelection.left  =
                rcLabel.left + (rcLabel.Width() - nSelectionWidth) / 2;
              rcSubItemSelection.right =
                rcSubItemSelection.left + nSelectionWidth;
              break;
            }

            default:
              ASSERT(false);
              break;
          }
          if (rcSubItemSelection.left < rcLabel.left)
            rcSubItemSelection.left = rcLabel.left;
          if (rcSubItemSelection.right > rcLabel.right)
            rcSubItemSelection.right = rcLabel.right;

          rcSelection = rcSubItemSelection;
        }

        if (bReallySelected || bAlwaysSelected)
        {
          if (rcSubItemSelection.left > rcSubItem.left)
          {
            // fill area left from selection with background color
            CRect rc(rcSubItem);
            rc.right = rcSubItemSelection.left-1;
            CBrush brush(dwBkColor);
            pDC->FillRect(rc, &brushBk);
          }

          // fill selection area with highlight color
          pDC->FillRect(rcSubItemSelection, &brushHiLite);

          // fill area right from selection with background color
          if (rcSubItemSelection.right < rcSubItem.right)
          {
            CRect rc(rcSubItem);
            rc.left = rcSubItemSelection.right+1;
            CBrush brush(dwBkColor);
            pDC->FillRect(rc, &brushBk);
          }

          pDC->SetBkColor  (dwHiLiteBk);
          pDC->SetTextColor(
            bReallySelected ? GetSysColor(COLOR_HIGHLIGHTTEXT) :
            bHotUnderlining ? m_dwHotLite                      :
            dwNormalText);
          bHiLite = true;
        }
      }
      else
        if (bFullRowSelected)
        {
          pDC->FillRect    (rcSubItem, &brushHiLite);
          pDC->SetBkColor  (dwHiLiteBk);
          pDC->SetTextColor(
            bReallySelected ? GetSysColor(COLOR_HIGHLIGHTTEXT) :
            bHotUnderlining ? m_dwHotLite                      :
            dwNormalText);
          bHiLite = true;
        }

    if (!bHiLite)
    {
      pDC->FillRect    (rcSubItem, &brushBk);
      pDC->SetBkColor  (dwBkColor);
      pDC->SetTextColor(bHotUnderlining ? m_dwHotLite : dwNormalText);
    }

    if (!m_bKeepLabelLeft && nIndex  == 0 ||
         m_bKeepLabelLeft && nColumn == 0)
    {
      CRect rcIcon;

      if (GetStateIconRect(pItem->iItem, rcIcon))
        DrawStateIcon(pDC, pItem, rcIcon);
    }

    if (!m_bKeepLabelLeft &&
        (nIndex  == 0 ||
         m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES && pSubItem->iImage > 0) ||
        m_bKeepLabelLeft && nColumn == 0)
    {
      CRect rcIcon;

      if (GetRealSubItemRect(pItem->iItem, m_bKeepLabelLeft ? 0 : nIndex,
                             LVIR_ICON, rcIcon))
      {
        LVITEM*      pLogicalItem;
        NMLVDISPINFO lvDispInfo;

        if (dwStyle & LVS_OWNERDATA)
        {
          lvDispInfo.hdr.hwndFrom   = m_pListCtrl->m_hWnd;
          lvDispInfo.hdr.idFrom     = m_pListCtrl->GetDlgCtrlID();
          lvDispInfo.hdr.code       = LVN_GETDISPINFO;
          lvDispInfo.item.mask      = LVIF_IMAGE;
          lvDispInfo.item.iItem     = pItem->iItem;
          lvDispInfo.item.iSubItem  = 0;
          OnGetdispinfo(&lvDispInfo.hdr);
          pLogicalItem = &lvDispInfo.item;
        }
        else
          pLogicalItem =
            reinterpret_cast<ITEM_DATA*>(pItem->lParam)->m_apLVItem[0];

        // take state of the physical item!
        pLogicalItem->state     = pItem->state;
        pLogicalItem->stateMask = pItem->stateMask;

        DrawSmallIcon(pDC, pLogicalItem, rcIcon);

        pLogicalItem->state     = 0;
        pLogicalItem->stateMask = 0;
      }
    }

    pSubItem->iSubItem = GetLogicalIndex(pSubItem->iSubItem);
    lvc.iSubItem       = pSubItem->iSubItem;
    DrawSubItemText(pDC, pSubItem, &lvc, rcText);

    if (nIndex > 0)
    {
      delete[] pSubItem->pszText;
      delete pSubItem;
    }
  }

  if (bHotUnderlining)
  {
    pDC->SelectObject(pfontPrev);
    delete pfontHotUnderlined;
  }
  delete[] pItem->pszText;
  delete pItem;

  // If item has focus draw focus rectangle
	if (bItemHasFocus)
  {
    pDC->SetTextColor (dwNormalText);
    pDC->DrawFocusRect(rcSelection);
  }
}

/*** Calculate width of item or subitem label ********************************/
int CListBase::GetLabelWidth(CDC* pDC, LVITEM* pItem, int nMaxWidth) const
{
  if (nMaxWidth > 0 && *pItem->pszText)
    return
      __min(pDC->GetTextExtent(pItem->pszText,
                               static_cast<int>(_tcslen(pItem->pszText))).cx,
                               nMaxWidth);
  else
    return 0;
}

/*** Retrieve for a given physical column number the logical column number ***/
int CListBase::GetLogicalIndex(int nPhysicalIndex) const
{
  INT_PTR nColumnCount = m_aColumnData.GetSize();

  for (int i = 0; i < nColumnCount; i++)
    if (m_aColumnData[i]->m_bVisible)
    {
      if (i == nPhysicalIndex) return nPhysicalIndex;
    }
    else
      nPhysicalIndex++;

  ASSERT(false);
  return -1;
}

/*** Retrieve for a given physical column order the logical column order *****/
int CListBase::GetLogicalOrder(int nPhysicalOrder) const
{
  for (int i = 0; i <= nPhysicalOrder; i++)
    for (INT_PTR j = m_aColumnData.GetUpperBound(); j >= 0; j--)
      if (m_aColumnData[j]->m_nOrder == i)
      {
        if (m_aColumnData[j]->m_bVisible)
        {
          if (i == nPhysicalOrder) return nPhysicalOrder;
        }
        else
          nPhysicalOrder++;
        break;
      }

  ASSERT(false);
  return -1;
}

/*** Get all attributes of a given physical item or subitem ******************/
LVITEM* CListBase::GetLVITEM(int nItem, int nSubItem) const
{
  ASSERT(m_pListCtrl);

  LVITEM* pItem = new LVITEM;

  pItem->mask      = LVIF_IMAGE | LVIF_STATE | LVIF_TEXT | LVIF_PARAM;
  pItem->iItem     = nItem;
  pItem->iSubItem  = nSubItem;
  pItem->stateMask = ~0U;

  // enlarge text buffer gradually until it's large enough
  for (int nLen = 128;; nLen += nLen)
  {
    LPTSTR pszText = new TCHAR[nLen];

    pItem->cchTextMax = nLen;
    pItem->pszText    = pszText;
    if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                   reinterpret_cast<LPARAM>(pItem)))
    {
      if (pItem->pszText != pszText)
      {
        // Windows hasn't used our buffer!
        _tcsncpy(pszText, pItem->pszText, nLen-1);
        pszText[nLen-1] = _T('\0');
        pItem->pszText  = pszText;
      }
    }
    else
    {
      delete[] pszText;
      delete pItem;
      return 0;
    }
    if (static_cast<int>(_tcslen(pItem->pszText)) < nLen-1) break;
    delete[] pItem->pszText;
  }

  return pItem;
}

/*** Returns the physical index of a given column index **********************/
int CListBase::GetPhysicalIndex(int nColumnIndex) const
{
  int nIndex = 0;

  for (int i = 0; i < nColumnIndex; i++)
    if (m_aColumnData[i]->m_bVisible) nIndex++;

  return nIndex;
}

/*** Returns the physical order of a given column order **********************/
int CListBase::GetPhysicalOrder(int nColumnOrder) const
{
  int nOrder = 0;

  for (int i = 0; i < nColumnOrder; i++)
    for (INT_PTR j = m_aColumnData.GetUpperBound(); j >= 0; j--)
      if (m_aColumnData[j]->m_nOrder == i)
      {
        if (m_aColumnData[j]->m_bVisible) nOrder++;
        break;
      }

  return nOrder;
}

/*** Calculates the bounding rectangle of a subitem.                       ***/
/*** Difference to GetSubItemRect:                                         ***/
/*** If the bounding rectangle of subitem 0 is requested, the function     ***/
/*** returns the bounding rectangle of the label including the icons only, ***/
/*** not the bounding rectangle of the whole item.                         ***/
bool CListBase::GetRealSubItemRect(int iItem, int iSubItem, int nArea,
                                       CRect& ref)
{
  ASSERT(m_pListCtrl);
  ASSERT(iSubItem >= 0);

  switch (nArea)
  {
    case LVIR_BOUNDS:
      if (m_pListCtrl->GetSubItemRect(iItem, iSubItem, LVIR_BOUNDS, ref))
        if (iSubItem == 0)
        {
          CRect rcLabel;

          if (m_pListCtrl->GetSubItemRect(iItem, 0, LVIR_LABEL, rcLabel))
          {
            ref.right = rcLabel.right;

            int nOrder = IndexToOrder(0);
            if (nOrder > 0)
            {
              // The left edge of subitem 0 is identical with the right edge of
              // the subitem left of subitem 0.
              CRect rcSubItem;

              if (m_pListCtrl->GetSubItemRect(iItem, OrderToIndex(nOrder - 1),
                                              LVIR_BOUNDS, rcSubItem))
              {
                ref.left = rcSubItem.right;
                return true;
              }
            }
            else
              return true;
          }
        }
        else
          return true;
      break;

    case LVIR_ICON:
    {
      CRect rcIcon;           // rectangle bounding small icon

      if (m_pListCtrl->GetSubItemRect(iItem, iSubItem, LVIR_ICON, rcIcon))
      {
        CRect rcSubItem;      // rectangle bounding subitem

        if (GetRealSubItemRect(iItem, iSubItem, LVIR_BOUNDS, rcSubItem))
          if (m_bKeepLabelLeft && iSubItem == 0 && IndexToOrder(0) > 0)
          {
            int nIndex = OrderToIndex(0);

            if (GetRealSubItemRect(iItem, nIndex, LVIR_BOUNDS, ref))
            {
              int nSmallIconXOff = rcIcon.left - rcSubItem.left;

              ref.left  += nSmallIconXOff;
              ref.right  = ref.left + rcIcon.Width();

              // clip rectangle at right edge if necessary
              INT_PTR nWidth =
                m_pListCtrl->DefWindowProc(LVM_GETCOLUMNWIDTH, nIndex, 0);
              if (nSmallIconXOff + ref.Width() >= nWidth)
                ref.right = ref.left - nSmallIconXOff + nWidth - 1;
              return true;
            }
          }
          else if ( m_bKeepLabelLeft && iSubItem == 0 ||
                   !m_bKeepLabelLeft && iSubItem >= 0)
          {
            // clip rectangle at right edge if necessary
            if (rcIcon.right > rcSubItem.right)
              rcIcon.right = rcSubItem.right;
            ref = rcIcon;
            return true;
          }
      }
      break;
    }

    case LVIR_LABEL:
    {
      CRect rcLabel;          // rectangle bounding label of subitem 0

      if (m_pListCtrl->GetSubItemRect(iItem, 0, LVIR_LABEL, rcLabel))
      {
        CRect rcSubItem0;     // rectangle bounding subitem 0

        if (GetRealSubItemRect(iItem, 0, LVIR_BOUNDS, rcSubItem0))
          if (IndexToOrder(0) > 0 && m_bKeepLabelLeft)
          {
            if (GetRealSubItemRect(iItem, OrderToIndex(0), LVIR_BOUNDS, ref))
            {
              ref.left += rcLabel.left - rcSubItem0.left;
              return true;
            }
          }
          else
          {
            ref = rcLabel;
            return true;
          }
      }
      break;
    }

    default:
      ASSERT(false);
      break;
  }

  return false;
}

/*** Retrieves the bounding rectangle for the state icon of an item **********/
bool CListBase::GetStateIconRect(int nItem, LPRECT pRect)
{
  CRect rcSubItem;

  if (GetRealSubItemRect(nItem, m_bKeepLabelLeft ? OrderToIndex(0) : 0,
                         LVIR_BOUNDS, rcSubItem))
  {
    CRect rcSmallIcon;

    if (GetRealSubItemRect(nItem, 0, LVIR_ICON, rcSmallIcon))
    {
      *pRect       = rcSubItem;
      pRect->right = rcSmallIcon.left;
      if (rcSmallIcon.right > rcSmallIcon.left) pRect->right--;

      // calculate x-offset of state icon
      if (!m_bIconXOffCalculated)
      {
        ASSERT(m_pListCtrl);
        CImageList* pImageList = m_pListCtrl->GetImageList(LVSIL_STATE);

        if (pImageList)
        {
          // retrieve width of state icon
          IMAGEINFO ii = {0, 0, 0, 0};

          if (pImageList->GetImageInfo(0, &ii))
          {
            int nXOff = pRect->right - (ii.rcImage.right - ii.rcImage.left) -
                        pRect->left;

            if (nXOff < 0)
              m_nIconXOff = 0;
            else if (nXOff < 4)
              m_nIconXOff = nXOff;
            else
              m_nIconXOff = 4;
          }
          else
            m_nIconXOff = 4;
        }
        else
          m_nIconXOff = 4;

        m_bIconXOffCalculated = true;
      }

      pRect->left += m_nIconXOff;

      // clip at right column border
      int nWidth = rcSubItem.Width();
      if (pRect->right >= rcSubItem.left + nWidth)
        pRect->right = pRect->left - m_nIconXOff + nWidth - 1;

      return true;
    }
  }

  return false;
}

/*** Return the order in the header control of a subitem, based on its index */
int CListBase::IndexToOrder(int nIndex)
{
  ASSERT(m_pListCtrl);
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  HDITEM headerItem = {HDI_ORDER};
  return m_pListCtrl->GetHeaderCtrl()->GetItem(nIndex, &headerItem) ?
         headerItem.iOrder : -1;

}

/*** Invalidate client area not covered by list control items ****************/
void CListBase::InvalidateNonItemArea()
{
  ASSERT(m_pListCtrl);

  int nTopIndex = m_pListCtrl->GetTopIndex();

  if (nTopIndex >= 0)
  {
    // update coloring of sort column
    CRect rectHdrItem;
    ASSERT(m_pListCtrl->GetHeaderCtrl());
    if (m_pListCtrl->GetHeaderCtrl()->GetItemRect(
          abs(m_nSortColumn) - 1, rectHdrItem))
    {
      // erase area above top item
      CRect rectThis;
      m_pListCtrl->GetClientRect(rectThis);

      CRect rectItem;
      m_pListCtrl->GetItemRect(nTopIndex, rectItem, LVIR_BOUNDS);

      CRect rectToBeErased(rectThis.left, rectHdrItem.bottom,
                           rectThis.right, rectItem.top);
      m_pListCtrl->InvalidateRect(rectToBeErased);

      // erase area below bottom item
      m_pListCtrl->GetItemRect(m_pListCtrl->GetItemCount() - 1, rectItem,
                               LVIR_BOUNDS);
      if (rectItem.bottom < rectThis.bottom)
      {
        rectToBeErased.top    = rectItem.bottom;
        rectToBeErased.bottom = rectThis.bottom;
      }
      m_pListCtrl->InvalidateRect(rectToBeErased);
    }
  }
}

/*** Rejustify first column of listview control to enable a right- ***********/
/*** justified or centerd first column                             ***********/
void CListBase::JustifyFirstColumn(int nFormat)
{
  ASSERT(m_pListCtrl);

  m_nFormatOfSubItem0 = nFormat;

  if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED ||
      m_dwExtendedStyle       & LVS_EX_FULLROWSELECT)
  {
    CHeaderCtrl* pHeaderCtrl = m_pListCtrl->GetHeaderCtrl();
    ASSERT(pHeaderCtrl);
    HDITEM hdrItem;

    hdrItem.mask = HDI_FORMAT;
    if (pHeaderCtrl->GetItem(0, &hdrItem))
    {
      hdrItem.fmt =
        hdrItem.fmt & ~HDF_JUSTIFYMASK | nFormat & HDF_JUSTIFYMASK;
      pHeaderCtrl->SetItem(0, &hdrItem);
    }
  }
}

/*** A column header has been clicked ****************************************/
BOOL CListBase::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW* pNMListView    = reinterpret_cast<NMLISTVIEW*>(pNMHDR);
  int         nAbsSortColumn = abs(m_nSortColumn);

  pNMListView->iSubItem = GetLogicalIndex(pNMListView->iSubItem);
  if (nAbsSortColumn > 0)
    if (pNMListView->iSubItem == nAbsSortColumn-1)
      m_nSortColumn = -m_nSortColumn;
    else
      m_nSortColumn = pNMListView->iSubItem + 1;
  else
    m_nSortColumn = pNMListView->iSubItem + 1;
  SetSortIcon();

	*pResult = 0;
  return FALSE;
}

/*** An item in the column selection menu has been selected ******************/
BOOL CListBase::OnCommand(WPARAM wParam)
{
  if (HIWORD(wParam) == 0)
    ShowColumn(static_cast<int>(wParam), !m_aColumnData[wParam]->m_bVisible);
  return TRUE;
}

/*** The user has right clicked the mouse ************************************/
void CListBase::OnContextMenu(CWnd* pWnd)
{
  ASSERT(m_pListCtrl);

  if (pWnd == m_pListCtrl->GetHeaderCtrl())
    if (m_nColumnHidingAllowed)
    {
      CMenu menu;

      if (menu.CreatePopupMenu())
      {
        for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; i--)
          menu.InsertMenu(0,
            MF_BYPOSITION                                              |
            (m_aColumnData[i]->m_bVisible ? MF_CHECKED : MF_UNCHECKED) |
            (m_aColumnData[i]->m_bHidingAllowed ? 0 : MF_GRAYED)       |
            MF_STRING, i, m_aColumnData[i]->m_pLVColumn->pszText);

        CPoint pt(0, 0);
        GetCursorPos       (&pt);
        menu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, m_pListCtrl, 0);
      }
    }
}

/*** A list view (sub)item will be drawn *************************************/
void CListBase::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
  ASSERT(m_pListCtrl);
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  NMLVCUSTOMDRAW* pNMLVCustomDraw = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

  switch (pNMLVCustomDraw->nmcd.dwDrawStage)
  {
    case CDDS_PREPAINT:
      *pResult = CDRF_NOTIFYITEMDRAW;
      break;

    case CDDS_ITEMPREPAINT:
      *pResult = CDRF_NOTIFYSUBITEMDRAW;
      break;

    case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
    {
      int nSortColumn = abs(m_nSortColumn) - 1;

      if (m_bColorSortColumn                     &&
          m_nSortColumn != 0                     &&
          m_aColumnData[nSortColumn]->m_bVisible &&
          pNMLVCustomDraw->iSubItem == GetPhysicalIndex(nSortColumn))
      {
        pNMLVCustomDraw->clrTextBk = m_dwColSortColor;
        *pResult = CDRF_NEWFONT | CDRF_NOTIFYPOSTPAINT;
      }
      else
      {
        pNMLVCustomDraw->clrTextBk = m_pListCtrl->GetBkColor();
        *pResult = CDRF_DODEFAULT;
      }

      if (pNMLVCustomDraw->iSubItem == 0 ||
          m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES)
        *pResult |= CDRF_NOTIFYPOSTPAINT;
      break;
    }

    case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM:
    {
      // special treatment for first subitem:
      // fill empty area left of text label
      int   nItem    = static_cast<int>(pNMLVCustomDraw->nmcd.dwItemSpec);
      int   nSubItem = pNMLVCustomDraw->iSubItem;
      CRect rectItem;
      m_pListCtrl->GetHeaderCtrl()->GetItemRect(nSubItem, rectItem);
      int   nColumnWidth = rectItem.Width();
      int   nLeftX       = rectItem.left - m_pListCtrl->GetScrollPos(SB_HORZ);
      bool  bFirstColumn = rectItem.left == 0;
      bool  bHasFocus    = m_pListCtrl->GetFocus() == m_pListCtrl;
      CDC*  pDC          = CDC::FromHandle(pNMLVCustomDraw->nmcd.hdc);
      CRect rect;
      m_pListCtrl->GetSubItemRect(nItem, nSubItem, LVIR_ICON, rect);
      if (nSubItem > 0) rect.right += m_nIconXOff;
      if (rect.right > rectItem.right) rect.right = rectItem.right;

      CBrush brushColColor;
      int    nSortColumn    = abs(m_nSortColumn) - 1;
      bool   bFullRowSelect = (m_dwExtendedStyle & LVS_EX_FULLROWSELECT) != 0;
      bool   bSelected      = false;

      LVITEM item;
      item.mask      = LVIF_IMAGE | LVIF_STATE;
      item.iItem     = nItem;
      item.iSubItem  = nSubItem;
      item.stateMask =
        LVIS_SELECTED | LVIS_FOCUSED | LVIS_STATEIMAGEMASK | LVIS_OVERLAYMASK;
      m_pListCtrl->GetItem(&item);
      
      if (!bFirstColumn                                        &&
          bFullRowSelect                                       &&
          item.state & LVIS_SELECTED                           &&
          bHasFocus                                            &&
          m_dwExtendedStyle & (LVS_EX_UNDERLINEHOT |
            LVS_EX_ONECLICKACTIVATE | LVS_EX_TWOCLICKACTIVATE) &&
          item.iItem == m_pListCtrl->GetHotItem())
        // create brush with hot-tracked color
        brushColColor.CreateSolidBrush(m_dwHotLite);
      else if (!bFirstColumn              &&
               bFullRowSelect             &&
               item.state & LVIS_SELECTED &&
               bHasFocus)
      {
        // create brush with highlight color
        brushColColor.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
        bSelected = true;
      }
      else if (!bFirstColumn              &&
               bFullRowSelect             &&
               item.state & LVIS_SELECTED &&
               m_pListCtrl->GetStyle() & LVS_SHOWSELALWAYS)
      {
        // create brush with highlight (nonfocus) color
        brushColColor.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
        bSelected = true;
      }
      else if (m_bColorSortColumn                     &&
               m_nSortColumn != 0                     &&
               m_aColumnData[nSortColumn]->m_bVisible &&
               nSubItem == GetPhysicalIndex(nSortColumn))
        // create brush with sort color
        brushColColor.CreateSolidBrush(m_dwColSortColor);
      else
        // create brush with normal background color
        brushColColor.CreateSolidBrush(m_pListCtrl->GetBkColor());

      // select new brush and save previous brush
      CBrush* pbrushPrev = pDC->SelectObject(&brushColColor);

      // color area left of text label
      if (nSubItem == 0 ||
          m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES && item.iImage > 0)
        pDC->PatBlt(nLeftX, rect.top, __max(rect.left, rect.right) - nLeftX,
                    rect.Height(), PATCOPY);

      if (nSubItem == 0 && nColumnWidth > m_nIconXOff)
      {
        // draw state icon
        CImageList* pimglst = m_pListCtrl->GetImageList(LVSIL_STATE);
        if (pimglst)
        {
          int nImage = (item.state & LVIS_STATEIMAGEMASK) >> 12;
          if (nImage > 0)
          {
            IMAGEINFO imgInfo;
            // image indices are zero-based
            if (pimglst->GetImageInfo(--nImage, &imgInfo) &&
                GetStateIconRect(item.iItem, rect))
              pimglst->DrawIndirect(
                pDC, nImage, rect.TopLeft(),
                CSize(__min(rect.Width(),
                            imgInfo.rcImage.right - imgInfo.rcImage.left),
                      __min(rect.Height(),
                            imgInfo.rcImage.bottom - imgInfo.rcImage.top)),
                CPoint(0, 0),
                item.state & LVIS_SELECTED && bHasFocus ?
                ILD_SELECTED : ILD_NORMAL,
                SRCCOPY, CLR_NONE);
          }
        }
      }

      if (nSubItem == 0 && nColumnWidth > m_nIconXOff ||
          m_dwExtendedStyle & LVS_EX_SUBITEMIMAGES &&
          nSubItem > 0 && nColumnWidth > 0)
      {
        // draw small icon
        CImageList* pimglst = m_pListCtrl->GetImageList(LVSIL_SMALL);
        if (pimglst)
          if (item.iImage > 0)
          {
            IMAGEINFO imgInfo;
            if (pimglst->GetImageInfo(item.iImage, &imgInfo) &&
                m_pListCtrl->GetSubItemRect(nItem, nSubItem, LVIR_ICON, rect))
            {
              int nIconOffset = rect.left - nLeftX;
              if (nColumnWidth > nIconOffset)
                pimglst->DrawIndirect(
                  pDC, item.iImage, rect.TopLeft(),
                  CSize(__min(nColumnWidth - nIconOffset,
                              imgInfo.rcImage.right - imgInfo.rcImage.left),
                        __min(rect.Height(),
                              imgInfo.rcImage.bottom - imgInfo.rcImage.top)),
                  CPoint(0, 0),
                  (item.state & LVIS_SELECTED && bHasFocus ?
                  ILD_SELECTED : ILD_NORMAL) | item.state & LVIS_OVERLAYMASK,
                  SRCCOPY, CLR_NONE);
            }
          }
      }

      // restore previous brush
      pDC->SelectObject(pbrushPrev);

      *pResult = CDRF_DODEFAULT;
      break;
    }

    default:
      *pResult = CDRF_DODEFAULT;
      break;
  }
}

/*** All items will be removed ***********************************************/
LRESULT CListBase::OnDeleteAllItems()
{
  ASSERT(m_pListCtrl);

  BOOL bSuccess = TRUE;

  // First remove all item data ..
  for (int nItem =
         static_cast<int>(m_pListCtrl->DefWindowProc(LVM_GETITEMCOUNT, 0, 0));
       --nItem >= 0;)
  {
    LVITEM lvItem = {LVIF_PARAM, nItem, 0};

    if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                   reinterpret_cast<LPARAM>(&lvItem)))
      delete reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
    else
    {
      ASSERT(false);
      bSuccess = FALSE;
    }
  }

  // ... then remove all items
  m_pListCtrl->Default();

  return bSuccess;
}

/*** A column will be deleted ************************************************/
LRESULT CListBase::OnDeleteColumn(WPARAM wParam)
{
  ASSERT(m_pListCtrl);

  int     nColumn      = static_cast<int>(wParam);
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nColumn < 0 || nColumn >= nColumnCount) return FALSE;

  LRESULT lResult = m_aColumnData[nColumn]->m_bVisible ?
                    m_pListCtrl->DefWindowProc(LVM_DELETECOLUMN,
                                               GetPhysicalIndex(nColumn), 0) :
                    TRUE;

  if (lResult)
  {
    // adjust column order
    int i;
    for (i = 0; i < nColumnCount; i++)
      if (m_aColumnData[i]->m_nOrder > m_aColumnData[nColumn]->m_nOrder)
        m_aColumnData[i]->m_nOrder--;

    delete m_aColumnData[nColumn];
    m_aColumnData.RemoveAt(nColumn);

    if (m_nSortColumn)
    {
      // adjust index of sort column
      if (m_nSortColumn < 0)
      {
        if (nColumn < -m_nSortColumn) m_nSortColumn++;
      }
      else
      {
        if (nColumn < m_nSortColumn) m_nSortColumn--;
      }
      if (abs(m_nSortColumn) == nColumn) m_nSortColumn = 0;
    }

    // delete subitem structures belonging to column
    for (i = static_cast<int>(m_pListCtrl->DefWindowProc(
           LVM_GETITEMCOUNT, 0, 0)); --i >= 0;)
    {
      LVITEM lvItem = {LVIF_PARAM, i, 0};

      if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                     reinterpret_cast<LPARAM>(&lvItem)))
      {
        ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
        LVITEM*    pLVItem   = pItemData->m_apLVItem[nColumn];

        pItemData->m_apLVItem.RemoveAt(nColumn);
        if (pLVItem)
        {
          delete[] pLVItem->pszText;
          delete pLVItem;
        }
      }
    }
  }

  return lResult;
}

/*** An item will be removed *************************************************/
LRESULT CListBase::OnDeleteItem(WPARAM wParam)
{
  ASSERT(m_pListCtrl);

  int nItem = static_cast<int>(wParam);
  if (nItem < 0) return FALSE;

  LVITEM lvItem = {LVIF_PARAM, nItem, 0};

  if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                 reinterpret_cast<LPARAM>(&lvItem)) &&
      m_pListCtrl->Default())
  {
    // remove administration data
    delete reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
    return TRUE;
  }
  else
    return FALSE;
}

/*** The list view control will be destroyed *********************************/
void CListBase::OnDestroy()
{
  ASSERT(m_pListCtrl);

  // delete all items explicitly to ensure
  // that all administration data will be deleted, too
  m_pListCtrl->DeleteAllItems();
  m_pListCtrl->OnDestroy     ();
}

/*** The background will be erased *******************************************/
BOOL CListBase::OnEraseBkgnd(CDC* pDC) 
{
  ASSERT(m_pListCtrl);

  if (m_bColorSortColumn && m_nSortColumn != 0)
  {
    int nAbsSortColumn = abs(m_nSortColumn) - 1;

    if (m_aColumnData[nAbsSortColumn]->m_bVisible)
    {
      CRect rect;
      if (!m_pListCtrl->GetHeaderCtrl()->GetItemRect(
             GetPhysicalIndex(nAbsSortColumn), rect))
        return m_pListCtrl->Default() != 0;

      int nXScrlOff = m_pListCtrl->GetScrollPos(SB_HORZ);
      int nLeftX    = rect.left  - nXScrlOff;
      int nRightX   = rect.right - nXScrlOff;

      pDC->GetClipBox(&rect);     // get area to be erased
      if (nLeftX < rect.right && nRightX > rect.left)
      {
        CBrush  brushNormalColor(m_pListCtrl->GetBkColor());
        CBrush  brushSortColor(m_dwColSortColor);
        CBrush* pbrushPrev = 0;

        if (nLeftX > rect.left)
        {
          // select brush with normal background color and save default brush
          pbrushPrev = pDC->SelectObject(&brushNormalColor);

          // erase area left from sort column with normal background color
          pDC->PatBlt(rect.left, rect.top, nLeftX - rect.left, rect.Height(),
                      PATCOPY);
        }
    
        // select brush with sort color and save default brush
        if (pbrushPrev)
          pDC->SelectObject(&brushSortColor);
        else
          pbrushPrev = pDC->SelectObject(&brushSortColor);

        // erase area inside sort column with sort color
        if (nLeftX < rect.left)
          if (nRightX < rect.right)
            pDC->PatBlt(rect.left, rect.top, nRightX - rect.left,
                        rect.Height(), PATCOPY);
          else
            pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(),
                        PATCOPY);
        else
          if (nRightX < rect.right)
            pDC->PatBlt(nLeftX, rect.top, nRightX - nLeftX, rect.Height(),
                        PATCOPY);
          else
            pDC->PatBlt(nLeftX, rect.top, rect.right - nLeftX, rect.Height(),
                        PATCOPY);

        if (nRightX < rect.right)
        {
          // select brush with normal background color
          pDC->SelectObject(&brushNormalColor);

          // color area right from sort column
          pDC->PatBlt(nRightX, rect.top, rect.right - nRightX, rect.Height(),
                      PATCOPY);
        }

        // restore previous brush
        pDC->SelectObject(pbrushPrev);

        return TRUE;
      }
    }
  }

  return m_pListCtrl->Default() != 0;
}

/*** A specific item will be searched ****************************************/
LRESULT CListBase::OnFindItem(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  int iStart = static_cast<int>(wParam);
  ASSERT(iStart >= -1);

  const LVFINDINFO* plvfi = reinterpret_cast<const LVFINDINFO*>(lParam);

  if (plvfi->flags & LVFI_PARAM)
  {
    int nItemCount = m_pListCtrl->GetItemCount();

    for (int nItem = iStart; ++nItem < nItemCount;)
    {
      LVITEM lvItem = {LVIF_PARAM, nItem, 0};

      if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                     reinterpret_cast<LPARAM>(&lvItem)))
        if (reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->m_lParam ==
            plvfi->lParam) return nItem;
    }

    // wrap around?
    if (iStart >= 0 && plvfi->flags & LVFI_WRAP)
      for (int nItem = 0; nItem <= iStart; nItem++)
      {
        LVITEM lvItem = {LVIF_PARAM, nItem, 0};

        if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                       reinterpret_cast<LPARAM>(&lvItem)))
          if (reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->m_lParam ==
              plvfi->lParam) return nItem;
      }

    return -1;
  }
  else
    return m_pListCtrl->Default();
}

/*** The attributes of a column will be retrieved ****************************/
LRESULT CListBase::OnGetColumn(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  int nColumn = static_cast<int>(wParam);
  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize()) return FALSE;

  LVCOLUMN* pLVColumn = reinterpret_cast<LVCOLUMN*>(lParam);

  if (m_aColumnData[nColumn]->m_bVisible)
  {
    LRESULT lResult = m_pListCtrl->DefWindowProc(LVM_GETCOLUMN,
                                                 GetPhysicalIndex(nColumn),
                                                 lParam);

    if (lResult)
    {
      // adjust index and order
      if (pLVColumn->mask & LVCF_ORDER)
        pLVColumn->iOrder = m_aColumnData[nColumn]->m_nOrder;
      if (pLVColumn->mask & LVCF_SUBITEM) pLVColumn->iSubItem = nColumn;
    }

    return lResult;
  }
  else
  {
    LVCOLUMN* pLVColumnSrc = m_aColumnData[nColumn]->m_pLVColumn;

    // retrieve column attributes from remembered column data
    if (pLVColumn->mask & LVCF_FMT)
      if (pLVColumnSrc->mask & LVCF_FMT)
        pLVColumn->fmt = pLVColumnSrc->fmt;
      else
        pLVColumn->fmt = LVCFMT_LEFT;
    if (pLVColumn->mask & LVCF_IMAGE)
      if (pLVColumnSrc->mask & LVCF_IMAGE)
        pLVColumn->iImage = pLVColumnSrc->iImage;
      else
        pLVColumn->iImage = -1;
    if (pLVColumn->mask & LVCF_ORDER)
      pLVColumn->iOrder = m_aColumnData[nColumn]->m_nOrder;
    if (pLVColumn->mask & LVCF_SUBITEM) pLVColumn->iSubItem = nColumn;
    if (pLVColumn->mask & LVCF_TEXT &&
        pLVColumn->pszText && pLVColumn->cchTextMax > 0)
      if (pLVColumnSrc->mask & LVCF_TEXT)
        if (_tcslen(pLVColumnSrc->pszText) >=
            static_cast<size_t>(pLVColumn->cchTextMax - 1))
        {
          _tcsncpy(pLVColumn->pszText, pLVColumnSrc->pszText,
                   pLVColumn->cchTextMax - 1);
          pLVColumn->pszText[pLVColumn->cchTextMax - 1] = _T('\0');
        }
        else
          _tcscpy(pLVColumn->pszText, pLVColumnSrc->pszText);
      else
        *pLVColumn->pszText = _T('\0');
    if (pLVColumn->mask & LVCF_WIDTH)
      pLVColumn->cx = m_aColumnData[nColumn]->m_nWidth;

    return TRUE;
  }
}

/*** The current left-to-right order of columns will be retrieved ************/
LRESULT CListBase::OnGetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  INT_PTR nCount = wParam;
  if (nCount <= 0) return 0;
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nCount > nColumnCount) nCount = nColumnCount;

  LPINT pArray = reinterpret_cast<LPINT>(lParam);

  for (int i = 0; i < nCount; i++)
    for (int j = 0; j < nColumnCount; j++)
      if (m_aColumnData[j]->m_nOrder == i) pArray[i] = j;

  return nCount;
}

/*** The width of a column will be retrieved *********************************/
LRESULT CListBase::OnGetColumnWidth(WPARAM wParam)
{
  ASSERT(m_pListCtrl);

  int nColumn = static_cast<int>(wParam);
  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize()) return 0;

  if (m_aColumnData[nColumn]->m_bVisible)
    return m_pListCtrl->DefWindowProc(LVM_GETCOLUMNWIDTH,
                                      GetPhysicalIndex(nColumn), 0);
  else
    // invisible column returns 0
    return 0;
}

/*** Information needed to display an item will be requested *****************/
BOOL CListBase::OnGetdispinfo(NMHDR* pNMHDR)
{
  ASSERT(m_pListCtrl);

  if (m_bOnGetDispinfo) return FALSE;
  m_bOnGetDispinfo = true;

  LVITEM* pLVItem       = &reinterpret_cast<NMLVDISPINFO*>(pNMHDR)->item;
  bool    bNotifyParent = true;
  int     iOrigSubItem  = pLVItem->iSubItem;

  pLVItem->iSubItem = GetLogicalIndex(pLVItem->iSubItem);
  if (!(m_pListCtrl->GetStyle() & LVS_OWNERDATA) && pLVItem->mask & LVIF_TEXT)
  {
    LVITEM* pLVItemStored =
      reinterpret_cast<ITEM_DATA*>(
        pLVItem->lParam)->m_apLVItem[pLVItem->iSubItem];

    if (pLVItemStored                   &&
        pLVItemStored->mask & LVIF_TEXT &&
        pLVItemStored->pszText != LPSTR_TEXTCALLBACK)
    {
      pLVItem->pszText = pLVItemStored->pszText;
      bNotifyParent    = false;
    }
  }

  if (bNotifyParent)
  {
    // notify parent window
    CWnd* pwndParent = m_pListCtrl->GetParent();

    if (pwndParent)
      pwndParent->SendMessage(WM_NOTIFY, m_pListCtrl->GetDlgCtrlID(),
                              reinterpret_cast<LPARAM>(pNMHDR));
  }

  // restore original subitem number
  pLVItem->iSubItem = iOrigSubItem;

  m_bOnGetDispinfo = false;
  return TRUE;
}

/*** Some or all of an item's attributes will be retrieved *******************/
LRESULT CListBase::OnGetItem(LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  LVITEM* pLVItem = reinterpret_cast<LVITEM*>(lParam);
  int     nColumn = pLVItem->iSubItem;

  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize() || pLVItem->iItem < 0)
    return FALSE;

  bool bVisible = m_aColumnData[nColumn]->m_bVisible;
  UINT origMask = pLVItem->mask;

  if (bVisible)
    pLVItem->iSubItem = GetPhysicalIndex(nColumn);
  else
  {
    if (pLVItem->mask & ~LVIF_STATE) pLVItem->mask |= LVIF_PARAM;
    pLVItem->mask    &= LVIF_STATE | LVIF_PARAM;
    pLVItem->iSubItem = 0;
  }

  LRESULT lResult = m_pListCtrl->Default();
  pLVItem->mask     = origMask;
  pLVItem->iSubItem = nColumn;

  if (lResult && (!bVisible || pLVItem->mask != LVIF_STATE))
  {
    ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(pLVItem->lParam);

    if (pLVItem->mask & LVIF_PARAM) pLVItem->lParam = pItemData->m_lParam;

    // column visible and only lParam (and state) shall be retrieved
    //   --> all has been done!
    if (bVisible) return lResult;

    LVITEM* pLVItemSrc = pItemData->m_apLVItem[nColumn];

    // retrieve item attributes from remembered item data (except state)
    if (pLVItem->mask & LVIF_IMAGE)
      if (pLVItemSrc && pLVItemSrc->mask & LVIF_IMAGE)
        pLVItem->iImage = pLVItemSrc->iImage;
      else
        pLVItem->iImage = 0;
    if (pLVItem->mask & LVIF_INDENT)
      if (pLVItemSrc && pLVItemSrc->mask & LVIF_INDENT)
        pLVItem->iIndent = pLVItemSrc->iIndent;
      else
        pLVItem->iIndent = 0;
    if (pLVItem->mask & LVIF_TEXT &&
        pLVItem->pszText && pLVItem->cchTextMax > 0)
      if (pLVItemSrc && pLVItemSrc->mask & LVIF_TEXT)
        if (_tcslen(pLVItemSrc->pszText) >
            static_cast<size_t>(pLVItem->cchTextMax - 1))
        {
          _tcsncpy(pLVItem->pszText, pLVItemSrc->pszText,
                   pLVItem->cchTextMax - 1);
          pLVItem->pszText[pLVItem->cchTextMax - 1] = _T('\0');
        }
        else
          _tcscpy(pLVItem->pszText, pLVItemSrc->pszText);
      else
        *pLVItem->pszText = _T('\0');
  }

  return lResult;
}

/*** The text of an item or subitem will be retrieved ************************/
LRESULT CListBase::OnGetItemText(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  INT_PTR nItem   = wParam;
  LVITEM* pLVItem = reinterpret_cast<LVITEM*>(lParam);
  int     nColumn = pLVItem->iSubItem;

  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize() || nItem < 0)
    return FALSE;

  if (m_aColumnData[nColumn]->m_bVisible)
  {
    pLVItem->iSubItem = GetPhysicalIndex(nColumn);
    LRESULT lResult =
      m_pListCtrl->DefWindowProc(LVM_GETITEMTEXT, wParam, lParam);
    pLVItem->iSubItem = nColumn;

    return lResult;
  }
  else
  {
    LVITEM lvItem = {LVIF_PARAM, pLVItem->iItem, 0};

    if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                   reinterpret_cast<LPARAM>(&lvItem)))
    {
      LVITEM* pLVItemSrc =
        reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->m_apLVItem[nColumn];

      // retrieve text from remembered item
      if (pLVItemSrc                   &&
          pLVItemSrc->mask & LVIF_TEXT &&
          pLVItemSrc->pszText && pLVItemSrc->cchTextMax > 0 &&
          pLVItem->pszText    && pLVItem->cchTextMax    > 0)
        if (_tcslen(pLVItemSrc->pszText) >
            static_cast<size_t>(pLVItem->cchTextMax - 1))
        {
          _tcsncpy(pLVItem->pszText, pLVItemSrc->pszText,
                   pLVItem->cchTextMax - 1);
          pLVItem->pszText[pLVItem->cchTextMax - 1] = _T('\0');
          return pLVItem->cchTextMax - 1;
        }
        else
        {
          _tcscpy(pLVItem->pszText, pLVItemSrc->pszText);
          return _tcslen(pLVItem->pszText);
        }
      else
      {
        *pLVItem->pszText = _T('\0');
        return 0;
      }
    }
    else
      return 0;
  }
}

/*** Determines which list view item, if any, is at a specified position *****/
int CListBase::OnHitTest(LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  if (m_pListCtrl->Default() != -1)
  {
    LPLVHITTESTINFO pHitTestInfo = reinterpret_cast<LPLVHITTESTINFO>(lParam);

    if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED &&
        pHitTestInfo->iItem    >= 0)
      if (pHitTestInfo->flags == LVHT_ONITEM)
      {
        CRect rc;
        if (GetRealSubItemRect(pHitTestInfo->iItem, 0, LVIR_LABEL, rc) &&
            rc.PtInRect(pHitTestInfo->pt))
          pHitTestInfo->flags = LVHT_ONITEMLABEL;
        else if (GetRealSubItemRect(pHitTestInfo->iItem, 0, LVIR_ICON, rc) &&
                 rc.PtInRect(pHitTestInfo->pt))
          pHitTestInfo->flags = LVHT_ONITEMICON;
        else if (GetStateIconRect(pHitTestInfo->iItem, rc) &&
                 rc.PtInRect(pHitTestInfo->pt))
          pHitTestInfo->flags = LVHT_ONITEMSTATEICON;
        else if (m_pListCtrl->GetItemRect(pHitTestInfo->iItem, rc, LVIR_BOUNDS)
                 &&
                 (!rc.PtInRect(pHitTestInfo->pt)    ||
                  // The small area left from state icon is LVHT_NOWHERE!!!
                  rc.left            > -m_nIconXOff &&
                  pHitTestInfo->pt.x <
                  __min(m_nIconXOff+rc.left, m_nIconXOff)))
          pHitTestInfo->flags = LVHT_NOWHERE;
      }
    return pHitTestInfo->iItem;
  }
  else
    return -1;
}

/*** List control has been scrolled horizontally *****************************/
void CListBase::OnHScroll()
{
  ASSERT(m_pListCtrl);

  m_pListCtrl->Default ();
  InvalidateNonItemArea();
}

/*** A new column will be inserted *******************************************/
LRESULT CListBase::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  int     nColumn      = static_cast<int>(wParam);
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nColumn < 0 || nColumn > nColumnCount) return -1;

  LVCOLUMN* pLVColumn = DupLVColumn(reinterpret_cast<LVCOLUMN*>(lParam));

  // adjust column attributes according to the real physical conditions
  pLVColumn->mask &= ~LVCF_SUBITEM;   // mask unnecessary subitem number
  if (pLVColumn->mask & LVCF_ORDER)
  {
    ASSERT(pLVColumn->iOrder >= 0 && pLVColumn->iOrder <= nColumnCount);
    pLVColumn->iOrder = GetPhysicalOrder(pLVColumn->iOrder);
  }

  LRESULT lResult =
    m_pListCtrl->DefWindowProc(LVM_INSERTCOLUMN, GetPhysicalIndex(nColumn),
                               reinterpret_cast<LPARAM>(pLVColumn));

  if (lResult != -1)
  {
    if (nColumn == 0)
      // Rejustify first column of listview control to enable a right-justified
      // or centerd first column
      JustifyFirstColumn(reinterpret_cast<LVCOLUMN*>(lParam)->fmt);

    // create and fill column administration structure
    COLUMN_DATA* pColumnData = new COLUMN_DATA;

    pLVColumn->mask         |= LVCF_WIDTH;
    pLVColumn->cx            = 0;
    pColumnData->m_pLVColumn = pLVColumn;
    pColumnData->m_nOrder    = pLVColumn->mask & LVCF_ORDER ?
                               reinterpret_cast<LVCOLUMN*>(lParam)->iOrder :
                               nColumn;

    // adjust column order
    int i;
    for (i = 0; i < nColumnCount; i++)
      if (m_aColumnData[i]->m_nOrder >= pColumnData->m_nOrder)
        m_aColumnData[i]->m_nOrder++;

    // store column administration structure
    m_aColumnData.InsertAt(nColumn, pColumnData);

    if (m_nSortColumn)
      // adjust index of sort column
      if (m_nSortColumn < 0)
      {
        if (nColumn < -m_nSortColumn) m_nSortColumn--;
      }
      else
      {
        if (nColumn < m_nSortColumn) m_nSortColumn++;
      }

    // insert subitem placeholders belonging to column
    for (i = static_cast<int>(m_pListCtrl->DefWindowProc(
           LVM_GETITEMCOUNT, 0, 0)); --i >= 0;)
    {
      LVITEM lvItem = {LVIF_PARAM, i, 0};

      if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                     reinterpret_cast<LPARAM>(&lvItem)))
        reinterpret_cast<ITEM_DATA*>(lvItem.lParam)->m_apLVItem.InsertAt(
          nColumn, 0, 1);
    }
  }
  else
  {
    delete[] pLVColumn->pszText;
    delete pLVColumn;
  }

  return lResult;
}

/*** A new item will be inserted *********************************************/
LRESULT CListBase::OnInsertItem(LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  LVITEM* pLVItemSrc = reinterpret_cast<LVITEM*>(lParam);
  if (pLVItemSrc->iItem < 0) return -1;
  LVITEM* pLVItem = DupLVItem(pLVItemSrc);

  // save lParam in administration data
  ITEM_DATA* pItemData = new ITEM_DATA;
  if (pLVItemSrc->mask & LVIF_PARAM) pItemData->m_lParam = pLVItem->lParam;
  // ^administration data is physical lParam
  pLVItem->lParam = reinterpret_cast<LPARAM>(pItemData);
  pLVItem->mask  |= LVIF_PARAM;

  // physical text is always LPSTR_TEXTCALLBACK
  LPTSTR pszOrigText = pLVItem->pszText;
  if (pLVItemSrc->mask    &  LVIF_TEXT          &&
      pLVItemSrc->pszText != LPSTR_TEXTCALLBACK &&
      !(m_pListCtrl->GetStyle() & (LVS_SORTASCENDING | LVS_SORTDESCENDING)))
    pLVItem->pszText = LPSTR_TEXTCALLBACK;
  
  LRESULT lResult =
    m_pListCtrl->DefWindowProc(LVM_INSERTITEM, 0,
                               reinterpret_cast<LPARAM>(pLVItem));

  if (lResult != -1)
  {
    // correct item data
    pLVItem->mask    = pLVItemSrc->mask;
    pLVItem->iItem   = static_cast<int>(lResult);
    pLVItem->pszText = pszOrigText;

    // insert item into administration data for column 0
    pItemData->m_apLVItem.InsertAt(0, pLVItem);

    // insert placeholders for other columns
    INT_PTR nColumnCount = m_aColumnData.GetSize();
    for (int nColumn = 1; nColumn < nColumnCount; ++nColumn)
      pItemData->m_apLVItem.InsertAt(nColumn, 0, 1);
  }
  else
  {
    if (pLVItemSrc->pszText != LPSTR_TEXTCALLBACK) delete[] pszOrigText;
    delete pLVItem;
    delete pItemData;
  }

  return lResult;
}

/*** A key has been pressed  *************************************************/
void CListBase::OnKeyDown(UINT nChar) 
{
  ASSERT(m_pListCtrl);

  switch (nChar)
  {
    // Numpad-Plus
    case VK_ADD:
      // Ctrl-Numpad-Plus --> set optimum width for all columns
      if (m_bControl && m_bKeepLabelLeft && IndexToOrder(0) > 0)
      {
        LVCOLUMN lvc;
	      lvc.mask = LVCF_FMT;

        int nIndex;
      	for (int nColumn = 0;
             m_pListCtrl->DefWindowProc(LVM_GETCOLUMN,
                                        nIndex = OrderToIndex(nColumn),
                                        reinterpret_cast<LPARAM>(&lvc));
             nColumn++)
        {
          int nOptWidth;

          if (nIndex == 0 || nColumn == 0)
          {
            // calculate needed column width
            nOptWidth = 0;
            for (int nItem = m_pListCtrl->GetItemCount(); --nItem >= 0;)
            {
              int nWidth =
                m_pListCtrl->GetStringWidth(
                  m_pListCtrl->GetItemText(nItem, nIndex));
              if (nWidth > nOptWidth) nOptWidth = nWidth;
            }

            if (nIndex > 0)
            {
              // add space for state icon and small icon
              CRect rcSubItem;
              if (GetRealSubItemRect(0, nIndex, LVIR_BOUNDS, rcSubItem))
              {
                CRect rcLabel;
                if (GetRealSubItemRect(0, nIndex, LVIR_LABEL, rcLabel))
                  nOptWidth += rcLabel.left - rcSubItem.left;
              }

              // add left offset
              nOptWidth += m_nFirstColXOff;
            }
            else
              // add left offset
              nOptWidth += m_nNextColXOff;

            // add right offset
            nOptWidth += m_nNextColXOff;
          }
          else
            nOptWidth = LVSCW_AUTOSIZE;

          m_pListCtrl->SetColumnWidth(nIndex, nOptWidth);
        }
      }
      else
        m_pListCtrl->Default();
      break;

    // Ctrl
    case VK_CONTROL:
      if (m_bKeepLabelLeft && IndexToOrder(0) > 0)
        m_bControl = true;
      else
        m_pListCtrl->Default();
      break;

    // All other keys
    default:
      m_pListCtrl->Default();
      break;
  }
}

/*** A key has been released *************************************************/
void CListBase::OnKeyUp(UINT nChar) 
{
  ASSERT(m_pListCtrl);

	if (nChar == VK_CONTROL) m_bControl = false;
  m_pListCtrl->Default();  

}

/*** List control loses input focus ******************************************/
void CListBase::OnKillFocus() 
{
  ASSERT(m_pListCtrl);

  m_pListCtrl->Default();

	// manually remove focus state so that custom drawing will function properly
  int nItem = m_pListCtrl->GetNextItem(-1, LVNI_SELECTED);
  if (nItem >= 0) m_pListCtrl->SetItemState(nItem, 0, LVIS_FOCUSED);
}

/*** The user double-clicks the left mouse button ****************************/
void CListBase::OnLButtonDblClk(CPoint point) 
{
  ASSERT(m_pListCtrl);

  UINT flags;
  int  nItem = m_pListCtrl->HitTest(point, &flags);

  if (nItem            >= 0                 &&
      m_dwExtendedStyle & LVS_EX_CHECKBOXES &&
      flags            == LVHT_ONITEMSTATEICON)
  {
    BOOL bChecked = !m_pListCtrl->GetCheck(nItem);

    if (m_pListCtrl->GetItemState(nItem, LVIS_SELECTED))
      for (POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); pos;)
        m_pListCtrl->SetCheck(m_pListCtrl->GetNextSelectedItem(pos),
                              bChecked);
    else
      m_pListCtrl->SetCheck(nItem, bChecked);
  }
  else
    m_pListCtrl->Default();
}

/*** The user presses the left mouse button **********************************/
void CListBase::OnLButtonDown(CPoint point) 
{
  ASSERT(m_pListCtrl);

  if (m_hcursorCustom) SetCursor(m_hcursorCustom);

  UINT flags;
  int  nItem = m_pListCtrl->HitTest(point, &flags);

  if (nItem >= 0                            &&
      m_dwExtendedStyle & LVS_EX_CHECKBOXES &&
      flags            == LVHT_ONITEMSTATEICON)
  {
    BOOL bChecked = !m_pListCtrl->GetCheck(nItem);

    if (m_pListCtrl->GetItemState(nItem, LVIS_SELECTED))
      for (POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); pos;)
        m_pListCtrl->SetCheck(m_pListCtrl->GetNextSelectedItem(pos),
                              bChecked);
    else
      m_pListCtrl->SetCheck(nItem, bChecked);
  }
  else
    m_pListCtrl->Default();

  SetHotCursor(point);
}

/*** The user releases the left mouse button *********************************/
void CListBase::OnLButtonUp()
{
  ASSERT(m_pListCtrl);

  if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
    if (m_hcursorCustom) SetCursor(m_hcursorCustom);

  m_pListCtrl->Default();
}

/*** The mouse has been moved ************************************************/
void CListBase::OnMouseMove(CPoint point)
{
  ASSERT(m_pListCtrl);

  m_pListCtrl->Default();
  SetHotCursor        (point);
}

/*** Divider in header control has been doubleclicked or dragged *************/
BOOL CListBase::OnNotify(LPARAM lParam) 
{
  ASSERT(m_pListCtrl);
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  BOOL       bRet   = FALSE;
  LPNMHEADER pNMHdr = reinterpret_cast<LPNMHEADER>(lParam);

  if (pNMHdr->hdr.hwndFrom == m_pListCtrl->GetHeaderCtrl()->m_hWnd)
    switch (pNMHdr->hdr.code)
    {
      case HDN_DIVIDERDBLCLICKW:
      case HDN_DIVIDERDBLCLICKA:
        if (m_bKeepLabelLeft                    &&
            (GetLogicalIndex(pNMHdr->iItem) > 0 &&
             IndexToOrder(pNMHdr->iItem)   == 0 ||
             pNMHdr->iItem                 == 0 &&
             IndexToOrder(pNMHdr->iItem)    > 0))
        {
          // calculate needed column width
          int nFirstItem;
          int nLastItem;
          int nOptWidth = 0;

          if (m_pListCtrl->GetStyle() & LVS_OWNERDATA)
          {
            // In a virtual list view control
            // at least the visible items and
            // at most the cached items will be considered.
            int nFirstVisibleItem = m_pListCtrl->GetTopIndex();

            nFirstItem = __min(m_nFirstCachedItem, nFirstVisibleItem);
            nLastItem  =
              __min(__max(m_nLastCachedItem,
                          nFirstVisibleItem + m_pListCtrl->GetCountPerPage()),
                    m_pListCtrl->GetItemCount() - 1);
          }
          else
          {
            nFirstItem = 0;
            nLastItem  = m_pListCtrl->GetItemCount() - 1;
          }

          for (int nItem = nFirstItem; nItem <= nLastItem; nItem++)
          {
            int nWidth =
              m_pListCtrl->GetStringWidth(
                m_pListCtrl->GetItemText(nItem,
                  GetLogicalIndex(pNMHdr->iItem)));
            if (nWidth > nOptWidth) nOptWidth = nWidth;
          }

          if (GetLogicalIndex(pNMHdr->iItem) > 0)
          {
            // add space for state icon and small icon
            CRect rcSubItem;
            if (GetRealSubItemRect(0, pNMHdr->iItem, LVIR_BOUNDS, rcSubItem))
            {
              CRect rcLabel;
              if (GetRealSubItemRect(0, pNMHdr->iItem, LVIR_LABEL, rcLabel))
                nOptWidth += rcLabel.left - rcSubItem.left;
            }

            // add left offset
            nOptWidth += m_nFirstColXOff;
          }
          else
            // add left offset
            nOptWidth += m_nNextColXOff;

          // add right offset
          nOptWidth += m_nNextColXOff;

          m_pListCtrl->DefWindowProc(LVM_SETCOLUMNWIDTH, pNMHdr->iItem,
                                     nOptWidth);
          return TRUE;
        }
        else
          bRet = m_pListCtrl->Default() != 0;
        break;

      case HDN_ENDDRAG:
        bRet = m_pListCtrl->Default() != 0;
        if (pNMHdr->pitem->iOrder >= 0)
        {
          int nColumn = GetLogicalIndex(pNMHdr->iItem);
          int nOrder  = GetLogicalOrder(pNMHdr->pitem->iOrder);

          if (nOrder < m_aColumnData[nColumn]->m_nOrder)
          {
            // adjust column order
            for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; i--)
              if (m_aColumnData[i]->m_nOrder >= nOrder &&
                  m_aColumnData[i]->m_nOrder <
                  m_aColumnData[nColumn]->m_nOrder)
                m_aColumnData[i]->m_nOrder++;
            m_aColumnData[nColumn]->m_nOrder = nOrder;
          }
          else if (nOrder > m_aColumnData[nColumn]->m_nOrder)
          {
            // adjust column order
            for (INT_PTR i = m_aColumnData.GetUpperBound(); i >= 0; i--)
              if (m_aColumnData[i]->m_nOrder >
                  m_aColumnData[nColumn]->m_nOrder &&
                  m_aColumnData[i]->m_nOrder <= nOrder)
                m_aColumnData[i]->m_nOrder--;
            m_aColumnData[nColumn]->m_nOrder = nOrder;
          }
        }
        break;

      case HDN_ENDTRACKW:
      case HDN_ENDTRACKA:
      case HDN_ITEMCHANGEDW:
      case HDN_ITEMCHANGEDA:
        bRet = m_pListCtrl->Default() != 0;
        if (m_bColorSortColumn) InvalidateNonItemArea();
        break;

      case HDN_ITEMCLICK:
        m_pListCtrl->Default();
        // Suppress further processing of this message to prevent Windows from
        // sending the notification message LVN_COLUMNCLICK a second time!
        // For unknown reasons this is necessary in an Unicode environment
        // only.
        return TRUE;

      default:
        bRet = m_pListCtrl->Default() != 0;
        break;
    }

  return bRet;
}

/*** The contents of the display area of a virtual list view control have ****/
/*** been changed                                                         ****/
BOOL CListBase::OnODCacheHint(NMHDR* pNMHDR)
{
  LPNMLVCACHEHINT pNMLVCacheHint = reinterpret_cast<LPNMLVCACHEHINT>(pNMHDR);

  // remember caching area
  m_nFirstCachedItem = pNMLVCacheHint->iFrom;
  m_nLastCachedItem  = pNMLVCacheHint->iTo;

  return FALSE;
}

/*** The background color of the list view control will be set ***************/
LRESULT CListBase::OnSetBkColor()
{
  ASSERT(m_pListCtrl);

  if (m_pListCtrl->Default())
  {
    if (m_bColorSortColumn)
    {
      // force recalculation of sort column color
      m_bColorSortColumn = false;
      ColorSortColumn();
    }
    return TRUE;
  }
  else
    return FALSE;
}

/*** The attributes of a column will be set **********************************/
LRESULT CListBase::OnSetColumn(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  int     nColumn      = static_cast<int>(wParam);
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nColumn < 0 || nColumn >= nColumnCount) return FALSE;

  LVCOLUMN* pLVColumn = DupLVColumn(reinterpret_cast<LVCOLUMN*>(lParam));

  // adjust column attributes according to the real physical conditions
  pLVColumn->mask &= ~LVCF_SUBITEM;   // mask unnecessary subitem number
  if (pLVColumn->mask & LVCF_ORDER)
  {
    ASSERT(pLVColumn->iOrder >= 0 && pLVColumn->iOrder < nColumnCount);
    pLVColumn->iOrder = GetPhysicalOrder(pLVColumn->iOrder);
  }

  LRESULT lResult = m_aColumnData[nColumn]->m_bVisible ?
    m_pListCtrl->DefWindowProc(LVM_SETCOLUMN, GetPhysicalIndex(nColumn),
                               reinterpret_cast<LPARAM>(pLVColumn)) : TRUE;

  if (lResult)
  {
    // update column data
    LVCOLUMN* pLVColumnDst = m_aColumnData[nColumn]->m_pLVColumn;
    if (pLVColumn->mask & LVCF_FMT) pLVColumnDst->fmt = pLVColumn->fmt;
    if (pLVColumn->mask & LVCF_IMAGE) pLVColumnDst->iImage = pLVColumn->iImage;
    if (pLVColumn->mask & LVCF_ORDER)
    {
      int nOrder = reinterpret_cast<LVCOLUMN*>(lParam)->iOrder;

      if (nOrder < m_aColumnData[nColumn]->m_nOrder)
      {
        // adjust column order
        for (int i = 0; i < nColumnCount; i++)
          if (m_aColumnData[i]->m_nOrder >= nOrder &&
              m_aColumnData[i]->m_nOrder <  m_aColumnData[nColumn]->m_nOrder)
            m_aColumnData[i]->m_nOrder++;
        m_aColumnData[nColumn]->m_nOrder = nOrder;
      }
      else if (nOrder > m_aColumnData[nColumn]->m_nOrder)
      {
        // adjust column order
        for (int i = 0; i < nColumnCount; i++)
          if (m_aColumnData[i]->m_nOrder >  m_aColumnData[nColumn]->m_nOrder &&
              m_aColumnData[i]->m_nOrder <= nOrder)
            m_aColumnData[i]->m_nOrder--;
        m_aColumnData[nColumn]->m_nOrder = nOrder;
      }
    }
    if (pLVColumn->mask & LVCF_TEXT && pLVColumn->pszText)
    {
      delete[] pLVColumnDst->pszText;
      pLVColumnDst->pszText = new TCHAR[_tcslen(pLVColumn->pszText)+1];
      _tcscpy(pLVColumnDst->pszText, pLVColumn->pszText);
    }
    pLVColumnDst->mask |= pLVColumn->mask;
  }

  delete[] pLVColumn->pszText;
  delete pLVColumn;

  return lResult;
}

/*** The left-to-right order of columns will be set **************************/
LRESULT CListBase::OnSetColumnOrderArray(WPARAM wParam, LPARAM lParam)
{
  INT_PTR nCount = wParam;
  if (nCount <= 0) return 0;
  INT_PTR nColumnCount = m_aColumnData.GetSize();
  if (nCount > nColumnCount) nCount = nColumnCount;

  LPINT pArraySrc = reinterpret_cast<LPINT>(lParam);
  LPINT pArrayDst = new int[nCount];

  int n = 0;
  for (int i = 0; i < nCount; i++)
  {
    int nColumn = pArraySrc[i];
    if (nColumn >= nColumnCount)
    {
      // illegal column index
      delete[] pArrayDst;
      return 0;
    }

    if (m_aColumnData[nColumn]->m_bVisible)
      pArrayDst[n++] = GetPhysicalIndex(nColumn);
  }

  LRESULT lResult =
    m_pListCtrl->DefWindowProc(LVM_SETCOLUMNORDERARRAY, n,
                               reinterpret_cast<LPARAM>(pArrayDst));

  delete[] pArrayDst;

  if (lResult)
    // adjust column order
    for (int i = 0; i < nCount; i++)
    {
      int nColumn = pArraySrc[i];

      if (i < m_aColumnData[nColumn]->m_nOrder)
      {
        for (int j = 0; j < nColumnCount; j++)
          if (m_aColumnData[j]->m_nOrder >= i &&
              m_aColumnData[j]->m_nOrder <  m_aColumnData[nColumn]->m_nOrder)
            m_aColumnData[j]->m_nOrder++;
        m_aColumnData[nColumn]->m_nOrder = i;
      }
      else if (i > m_aColumnData[nColumn]->m_nOrder)
      {
        for (int j = 0; j < nColumnCount; j++)
          if (m_aColumnData[j]->m_nOrder >  m_aColumnData[nColumn]->m_nOrder &&
              m_aColumnData[j]->m_nOrder <= i) m_aColumnData[j]->m_nOrder--;
        m_aColumnData[nColumn]->m_nOrder = i;
      }
    }

  return lResult;
}

/*** The width of a column will be changed ***********************************/
LRESULT CListBase::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  int nColumn = static_cast<int>(wParam);
  if (nColumn < 0 || nColumn >= m_aColumnData.GetSize()) return FALSE;

  if (m_aColumnData[nColumn]->m_bVisible)
    return m_pListCtrl->DefWindowProc(LVM_SETCOLUMNWIDTH,
                                      GetPhysicalIndex(nColumn), lParam);
  else
  {
    // remember new column width
    m_aColumnData[nColumn]->m_nWidth = static_cast<int>(lParam);
    return TRUE;
  }
}

/*** The extended list view style will be set ********************************/
LRESULT CListBase::OnSetExtendedStyle(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  LRESULT dwResult = m_dwExtendedStyle;
  if (!wParam) wParam = ~0U;
  m_dwExtendedStyle = static_cast<DWORD>(wParam & lParam);

  if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
    // Hide the bits LVS_EX_UNDERLINEHOT, LVS_EX_ONECLICKACTIVATE, and
    // LVS_EX_TWOCLICKACTIVATE from Windows
    if (wParam & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
                  LVS_EX_TWOCLICKACTIVATE))
    {
      if (lParam & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
                    LVS_EX_TWOCLICKACTIVATE))
        PrepareHotUnderlining();
      else
        m_hcursorCustom = 0;

      m_pListCtrl->DefWindowProc(LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
                                 m_dwExtendedStyle         &
                                 ~(LVS_EX_UNDERLINEHOT     |
                                   LVS_EX_ONECLICKACTIVATE |
                                   LVS_EX_TWOCLICKACTIVATE));
      return dwResult;
    }
    else
      m_hcursorCustom = 0;

  return m_pListCtrl->Default();
}

/*** List control gains input focus ******************************************/
void CListBase::OnSetFocus() 
{
  ASSERT(m_pListCtrl);

  m_pListCtrl->Default();

	// manually set focus state so that custom drawing will function properly
  int nItem = m_pListCtrl->GetNextItem(-1, LVNI_SELECTED);
  if (nItem >= 0) m_pListCtrl->SetItemState(nItem, LVIS_FOCUSED, LVIS_FOCUSED);
}

/*** Assigns an image list to a list control *********************************/
LRESULT CListBase::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);
  ASSERT(m_pListCtrl->GetHeaderCtrl());
  ASSERT(wParam != LVSIL_NORMAL);

  LRESULT dwResult = m_pListCtrl->Default();

  if (wParam == LVSIL_SMALL && lParam)
  {
    // restore image list with sort icons because default behavior is that the
    // header control shares its image list with the small icon list of the
    // list control
    m_pListCtrl->GetHeaderCtrl()->SetImageList(&m_imglstSortIcons);
  }

  return dwResult;
}

/*** Some or all of a list view items attributes will be set *****************/
LRESULT CListBase::OnSetItem(LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  LVITEM* pLVItemSrc = reinterpret_cast<LVITEM*>(lParam);
  int     nColumn    = pLVItemSrc->iSubItem;

  if (nColumn           < 0 || nColumn >= m_aColumnData.GetSize() ||
      pLVItemSrc->iItem < 0) return FALSE;

  LVITEM* pLVItem     = DupLVItem(pLVItemSrc);
  bool    bVisible    = m_aColumnData[nColumn]->m_bVisible;
  LRESULT lResult;
  LPTSTR  pszOrigText = pLVItem->pszText;

  if (bVisible     && pLVItemSrc->mask & ~LVIF_PARAM ||
      nColumn == 0 && pLVItemSrc->mask &  LVIF_STATE)
  {
    // column is visible and other attributes than lParam will be set
    //   or
    // column zero and at least state will be set
    //   --> do it physically
    pLVItem->mask &= ~LVIF_PARAM;
    if (bVisible)
    {
      if (pLVItemSrc->mask    &  LVIF_TEXT          &&
          pLVItemSrc->pszText != LPSTR_TEXTCALLBACK &&
          !(m_pListCtrl->GetStyle() &
          (LVS_SORTASCENDING | LVS_SORTDESCENDING)))
        pLVItem->pszText = LPSTR_TEXTCALLBACK;
    }
    else
      pLVItem->mask &= LVIF_STATE;

    if (pLVItem->mask)
    {
      pLVItem->iSubItem = GetPhysicalIndex(nColumn);
      lResult           =
        m_pListCtrl->DefWindowProc(LVM_SETITEM, 0,
                                   reinterpret_cast<LPARAM>(pLVItem));
    }
    else
      lResult = TRUE;
  }
  else
    lResult = TRUE;

  if (lResult)
  {
    LVITEM lvItem = {LVIF_PARAM, pLVItemSrc->iItem, 0};

    if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                   reinterpret_cast<LPARAM>(&lvItem)))
    {
      ITEM_DATA* pItemData = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);

      // store lParam in administration data
      if (pLVItemSrc->mask & LVIF_PARAM)
        pItemData->m_lParam = pLVItemSrc->lParam;

      LVITEM* pLVItemDst;
      bool    bInsertItem;
      
      if (pItemData->m_apLVItem.GetSize() > nColumn)
      {
        pLVItemDst  = pItemData->m_apLVItem[nColumn];
        bInsertItem = false;
      }
      else
      {
        pLVItemDst  = 0;
        bInsertItem = true;
      }

      // Does the subitem already exist in the administration data?
      if (pLVItemDst)
      {
        delete pLVItem;

        // update subitem data
        if (pLVItemSrc->mask & LVIF_IMAGE)
          pLVItemDst->iImage = pLVItemSrc->iImage;
        if (pLVItemSrc->mask & LVIF_INDENT)
          pLVItemDst->iIndent = pLVItemSrc->iIndent;
        if (pLVItemSrc->mask & LVIF_TEXT && pszOrigText)
        {
          if (pLVItemDst->mask & LVIF_TEXT &&
              pLVItemDst->pszText != LPSTR_TEXTCALLBACK)
            delete[] pLVItemDst->pszText;
          pLVItemDst->pszText = pszOrigText;
        }
        pLVItemDst->mask |= pLVItemSrc->mask;
      }
      else
      {
        // store subitem administration data
        pLVItem->mask     = pLVItemSrc->mask;
        pLVItem->iSubItem = nColumn;
        pLVItem->pszText  = pszOrigText;
        if (bInsertItem)
          pItemData->m_apLVItem.InsertAt(nColumn, pLVItem);
        else
          pItemData->m_apLVItem[nColumn] = pLVItem;
      }
    }
  }
  else
  {
    if (pLVItemSrc->mask    &  LVIF_TEXT &&
        pLVItemSrc->pszText != LPSTR_TEXTCALLBACK) delete[] pszOrigText;
    delete pLVItem;
  }

  return lResult;
}

/*** The text of an item or a subitem will be changed ************************/
LRESULT CListBase::OnSetItemText(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  int     nItem     = static_cast<int>(wParam);
  LVITEM  lvItemSrc = *reinterpret_cast<LVITEM*>(lParam);

  if (lvItemSrc.iSubItem <  0                       ||
      lvItemSrc.iSubItem >= m_aColumnData.GetSize() ||
      nItem           <  0) return FALSE;

  lvItemSrc.mask = LVIF_TEXT;
  LVITEM* pLVItem     = DupLVItem(&lvItemSrc);
  LRESULT lResult;
  LPTSTR  pszOrigText = pLVItem->pszText;

  if (m_aColumnData[lvItemSrc.iSubItem]->m_bVisible)
  {
    if (pszOrigText != LPSTR_TEXTCALLBACK &&
        !(m_pListCtrl->GetStyle() & (LVS_SORTASCENDING | LVS_SORTDESCENDING)))
      pLVItem->pszText = LPSTR_TEXTCALLBACK;
    pLVItem->iSubItem = GetPhysicalIndex(lvItemSrc.iSubItem);
    lResult           =
      m_pListCtrl->DefWindowProc(LVM_SETITEMTEXT, wParam,
                                 reinterpret_cast<LPARAM>(pLVItem));
  }
  else
    lResult = TRUE;

  if (lResult)
  {
    LVITEM lvItem = {LVIF_PARAM, nItem, 0};

    if (m_pListCtrl->DefWindowProc(LVM_GETITEM, 0,
                                   reinterpret_cast<LPARAM>(&lvItem)))
    {
      ITEM_DATA* pItemData  = reinterpret_cast<ITEM_DATA*>(lvItem.lParam);
      LVITEM*    pLVItemDst;
      bool       bInsertItem;
      
      if (pItemData->m_apLVItem.GetSize() > lvItemSrc.iSubItem)
      {
        pLVItemDst  = pItemData->m_apLVItem[lvItemSrc.iSubItem];
        bInsertItem = false;
      }
      else
      {
        pLVItemDst  = 0;
        bInsertItem = true;
      }

      // Does the subitem already exist in the administration data?
      if (pLVItemDst)
      {
        delete pLVItem;

        // update subitem text
        if (pszOrigText)
        {
          if (pLVItemDst->mask & LVIF_TEXT &&
              pLVItemDst->pszText != LPSTR_TEXTCALLBACK)
            delete[] pLVItemDst->pszText;
          pLVItemDst->pszText = pszOrigText;
        }
        pLVItemDst->mask |= lvItemSrc.mask;
      }
      else
      {
        // store subitem administration data
        pLVItem->iSubItem = lvItemSrc.iSubItem;
        pLVItem->pszText  = pszOrigText;
        if (bInsertItem)
          pItemData->m_apLVItem.InsertAt(lvItemSrc.iSubItem, pLVItem);
        else
          pItemData->m_apLVItem[lvItemSrc.iSubItem] = pLVItem;
      }
    }
  }
  else
  {
    if (lvItemSrc.pszText != LPSTR_TEXTCALLBACK) delete[] pszOrigText;
    delete pLVItem;
  }

  return lResult;
}

/*** The items will be sorted ************************************************/
LRESULT CListBase::OnSortItems(WPARAM wParam, LPARAM lParam)
{
  ASSERT(m_pListCtrl);

  m_pfnLVCompare = reinterpret_cast<PFNLVCOMPARE>(lParam);
  m_lParamSort   = wParam;

  return m_pListCtrl->DefWindowProc(LVM_SORTITEMS,
                                    reinterpret_cast<WPARAM>(this),
                                    reinterpret_cast<LPARAM>(CompareFunc));
}

/*** System colors have been changed *****************************************/
void CListBase::OnSysColorChange() 
{
  ASSERT(m_pListCtrl);
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  m_pListCtrl->Default();

  // update color of sort icons
  if (m_imglstSortIcons.m_hImageList)
  {
    m_imglstSortIcons.DeleteImageList         ();
    m_bmpUpArrow.DeleteObject                 ();
    m_bmpDownArrow.DeleteObject               ();
    CreateSortIcons                           ();
    m_pListCtrl->GetHeaderCtrl()->SetImageList(&m_imglstSortIcons);
    SetSortIcon                               ();
  }

  // force update of column colors
  m_bColorSortColumn = !m_bColorSortColumn;
  ColorSortColumn(!m_bColorSortColumn);
}

/*** Return the index of a subitem, based in its order in the header control */
int CListBase::OrderToIndex(int nOrder)
{
  ASSERT(m_pListCtrl);
  ASSERT(m_pListCtrl->GetHeaderCtrl());

  return m_pListCtrl->GetHeaderCtrl()->OrderToIndex(nOrder);
}

/*** Prepare resources for hot underlining ***********************************/
void CListBase::PrepareHotUnderlining()
{
  ASSERT(m_pListCtrl);

  if (!m_hcursorArrow) m_hcursorArrow = LoadCursor(0, IDC_ARROW);
  if (!m_hcursorHand)
	//todo:zyl   
	  //if (_winver <= 0x0400)
    //  // Under Windows 95/NT we must create our own cursor
    //  // to indicate hot items
    //  m_hcursorHand = LoadCursor(AfxGetResourceHandle(), _T("IDC_HAND"));
    //else
      m_hcursorHand = LoadCursor(0, IDC_HAND);
}

/*** Set cursor if hot-tracking is enabled ***********************************/
void CListBase::SetHotCursor(const CPoint& point)
{
  if (m_dwExtendedStyle & (LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE |
                           LVS_EX_TWOCLICKACTIVATE))
  {
    // determine item under mouse cursor (hot item) and
    // the appropriate mouse cursor
    UINT flags;
    int  nItem       = m_pListCtrl->HitTest(point, &flags);
    int  nOldHotItem = m_nHotItem;

    m_nHotItem =
      nItem >= 0                                                        &&
      flags & LVHT_ONITEM & ~LVHT_ONITEMSTATEICON                       &&
      (m_dwExtendedStyle & LVS_EX_TWOCLICKACTIVATE                      &&
       m_pListCtrl->GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED ||
       m_dwExtendedStyle & LVS_EX_ONECLICKACTIVATE) ? nItem : -1;

    if (m_pListCtrl->GetStyle() & LVS_OWNERDRAWFIXED)
    {
      m_hcursorCustom = m_nHotItem != -1 ? m_hcursorHand : m_hcursorArrow;

      if (m_nHotItem != nOldHotItem)
      {
        CRect rc;

        if (nOldHotItem != -1)
        {
          m_pListCtrl->GetItemRect   (nOldHotItem, rc, LVIR_BOUNDS);
          m_pListCtrl->InvalidateRect(rc, FALSE);
        }
        if (m_nHotItem != -1)
        {
          m_pListCtrl->GetItemRect   (m_nHotItem, rc, LVIR_BOUNDS);
          m_pListCtrl->InvalidateRect(rc, FALSE);
        }
      }

      SetCursor(m_hcursorCustom);
    }
  }
}

/*** Display or hide sort icon on column to be sorted ************************/
void CListBase::SetSortIcon()
{
  ASSERT(m_pListCtrl);
  CHeaderCtrl* pHeaderCtrl = m_pListCtrl->GetHeaderCtrl();
  ASSERT(pHeaderCtrl);

  for (int col = static_cast<int>(m_aColumnData.GetUpperBound());
       col >= 0;
       col--)
    if (m_aColumnData[col]->m_bVisible)
    {
      HDITEM hdrItem;
      int    nPhysicalCol = GetPhysicalIndex(col);

      if (m_visualStyle == Present)
      {
        hdrItem.mask = HDI_FORMAT;
        pHeaderCtrl->GetItem(nPhysicalCol, &hdrItem);
        if (m_bSortIconEnabled     &&
            m_nSortColumn     != 0 &&
            m_nSortColumn - 1 == col)
          hdrItem.fmt =
            hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING | HDF_SORTUP;
        else if (m_bSortIconEnabled      &&
                  m_nSortColumn     != 0 &&
                 -m_nSortColumn - 1 == col)
          hdrItem.fmt =
            hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING | HDF_SORTDOWN;
        else
          hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING;
      }
      else
      {
        hdrItem.mask = HDI_FORMAT | HDI_IMAGE;
        pHeaderCtrl->GetItem(nPhysicalCol, &hdrItem);
        if (m_bSortIconEnabled     &&
            m_nSortColumn     != 0 &&
            m_nSortColumn - 1 == col)
        {
          hdrItem.iImage = m_nUpArrow;
          hdrItem.fmt    = hdrItem.fmt & HDF_JUSTIFYMASK |
                           HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
        }
        else if (m_bSortIconEnabled      &&
                  m_nSortColumn     != 0 &&
                 -m_nSortColumn - 1 == col)
        {
          hdrItem.iImage = m_nDownArrow;
          hdrItem.fmt    = hdrItem.fmt & HDF_JUSTIFYMASK |
                           HDF_IMAGE | HDF_STRING | HDF_BITMAP_ON_RIGHT;
        }
        else
          hdrItem.fmt = hdrItem.fmt & HDF_JUSTIFYMASK | HDF_STRING;
      }

      pHeaderCtrl->SetItem(nPhysicalCol, &hdrItem);
    }
}

/*** Definition of structure "CListBase::COLUMN_DATA" ************************/

/*** Destructor **************************************************************/
CListBase::COLUMN_DATA::~COLUMN_DATA()
{
  if (m_pLVColumn)
  {
    delete[] m_pLVColumn->pszText;
    delete m_pLVColumn;
  }
}


/*** Definition of structure "CListBase::ITEM_DATA" **************************/

/*** Destructor **************************************************************/
CListBase::ITEM_DATA::~ITEM_DATA()
{
  for (INT_PTR nColumn = m_apLVItem.GetUpperBound(); nColumn >= 0; nColumn--)
  {
    LVITEM* pLVItem = m_apLVItem[nColumn];

    if (pLVItem)
    {
      delete[] pLVItem->pszText;
      delete pLVItem;
    }
  }
}
