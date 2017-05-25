// MyServicesView.cpp : implementation file
//

#include "stdafx.h"
#include "MyServicesView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyServicesView

IMPLEMENT_DYNCREATE(CMyServicesView, CListView)

CMyServicesView::CMyServicesView()
{
	
}

CMyServicesView::~CMyServicesView()
{
}


BEGIN_MESSAGE_MAP(CMyServicesView, CListView)
	//{{AFX_MSG_MAP(CMyServicesView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyServicesView drawing

void CMyServicesView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyServicesView diagnostics

#ifdef _DEBUG
void CMyServicesView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyServicesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyServicesView message handlers

int CMyServicesView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_imagelist.Create(16, 16,ILC_COLOR8|ILC_MASK,1,1);
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	GetListCtrl().SetImageList(&m_imagelist,LVSIL_SMALL);
	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);
	GetListCtrl().InsertColumn(0,"名称",LVCFMT_LEFT,240);
	GetListCtrl().InsertColumn(1,"描述",LVCFMT_LEFT,340);
	GetListCtrl().InsertColumn(2,"状态",LVCFMT_LEFT,60);
	GetListCtrl().InsertColumn(3,"启动类别",LVCFMT_LEFT,80);
	GetListCtrl().InsertColumn(4,"登录身份",LVCFMT_LEFT,80);

	GetListCtrl().GetHeaderCtrl()->ModifyStyle(HDS_BUTTONS ,HDS_HOTTRACK   );
	return 0;
}

BOOL CMyServicesView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style ^= LVS_REPORT|LVS_SINGLESEL;		
	return CListView::PreCreateWindow(cs);
}

void CMyServicesView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	AfxGetMainWnd()->PostMessage(WM_USERRCLICKSERVICES,NULL,NULL);
	*pResult = 0;
}

void CMyServicesView::DeleteAllItems()
{
	for(int i = 0; i < GetListCtrl().GetItemCount(); i++)
	{
		delete (LPMYSERVICES) GetListCtrl().GetItemData(i);
	}
	GetListCtrl().DeleteAllItems();
}

void CMyServicesView::InsertItem(LPMYSERVICES pServices)
{
	LPMYSERVICES pItem = new MYSERVICES;
	*pItem = *pServices;
	int nItem = GetListCtrl().InsertItem(
		GetListCtrl().GetItemCount(),pItem->m_Disp,0);
	GetListCtrl().SetItemText(nItem,1,pItem->lpDescribe);
	DWORD m_Status = *((DWORD*) pServices->m_Status);
	switch(m_Status)
	{
		case SERVICE_STOPPED : GetListCtrl().SetItemText(nItem,2,"已停止");break;
		case SERVICE_RUNNING : GetListCtrl().SetItemText(nItem,2,"已运行");break;
		case SERVICE_PAUSED : GetListCtrl().SetItemText(nItem,2,"暂停");break;
		case SERVICE_START_PENDING : GetListCtrl().SetItemText(nItem,2,"正在启动");break;
		default				 : GetListCtrl().SetItemText(nItem,2,"状态未定");break;
	}

	if(pItem->dwStartType == SERVICE_AUTO_START)
	{
		GetListCtrl().SetItemText(nItem,3,"自动");
	}
	else if(pItem->dwStartType == SERVICE_DEMAND_START)
	{
		GetListCtrl().SetItemText(nItem,3,"手动");
	}
	else
	{
		GetListCtrl().SetItemText(nItem,3,"已禁用");
	}
	GetListCtrl().SetItemText(nItem,4,pItem->lpServiceStartName);
	GetListCtrl().SetItemData(nItem,(DWORD) pItem);
}	

void CMyServicesView::OnDestroy() 
{
	DeleteAllItems();
	CListView::OnDestroy();
}

void CMyServicesView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if(GetListCtrl().GetSelectedCount() == 1)
	{
		GetParent()->
			PostMessage(WM_COMMAND,(WPARAM) MAKEWPARAM(ID_SERVICES_ATTRIB,1),NULL);
	}
}

void CMyServicesView::UpDateItem(int nItem,LPMYSERVICES pServices)
{
	GetListCtrl().SetItemText(nItem,1,pServices->lpDescribe);
	DWORD m_Status = *((DWORD*) pServices->m_Status);
	switch(m_Status)
	{
		case SERVICE_STOPPED : GetListCtrl().SetItemText(nItem,2,"已停止");break;
		case SERVICE_RUNNING : GetListCtrl().SetItemText(nItem,2,"已运行");break;
		case SERVICE_PAUSED : GetListCtrl().SetItemText(nItem,2,"暂停");break;
		case SERVICE_START_PENDING : GetListCtrl().SetItemText(nItem,2,"正在启动");break;
		default				 : GetListCtrl().SetItemText(nItem,2,"状态未定");break;
	}
	if(pServices->dwStartType == SERVICE_AUTO_START)
	{
		GetListCtrl().SetItemText(nItem,3,"自动");
	}
	else if(pServices->dwStartType == SERVICE_DEMAND_START)
	{
		GetListCtrl().SetItemText(nItem,3,"手动");
	}
	else
	{
		GetListCtrl().SetItemText(nItem,3,"已禁用");
	}
	GetListCtrl().SetItemText(nItem,4,pServices->lpServiceStartName);
}

void CMyServicesView::ReStart()
{
	DeleteAllItems();
}