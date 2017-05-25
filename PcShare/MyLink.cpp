// MyLink.cpp : implementation file
//

#include "stdafx.h"
#include "MyLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyLink

CMyLink::CMyLink()
{
	
}

CMyLink::~CMyLink()
{
}


BEGIN_MESSAGE_MAP(CMyLink, CStatic)
	//{{AFX_MSG_MAP(CMyLink)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyLink message handlers

void CMyLink::OnPaint() 
{
	CPaintDC dc(this); 

	CFont *pFont = NULL;
	CString m_Text;
	GetWindowText(m_Text);
	dc.SetBkMode(TRANSPARENT);
	if(m_Font.GetSafeHandle())
	{
		pFont = &m_Font;
		CFont *pOldFont = dc.SelectObject(pFont);
		dc.SetTextColor(RGB(20,10,200));
		dc.TextOut(0,0,m_Text);
		dc.SelectObject(pOldFont);
	}
}

void CMyLink::SetMyFont(LPCTSTR FontName,int FontSize,int FontWidth,BOOL IsLine)
{
	if(m_Font.GetSafeHandle()) m_Font.DeleteObject();
	m_Font.CreateFont(FontSize,0,0,0,FontWidth,0,IsLine,0,0,0,0,0,0,FontName);
}

CSize CMyLink::GetMySize(LPCTSTR m_Text)
{
	CDC *pDC = GetDesktopWindow()->GetDC();
	CFont *pOldFont = pDC->SelectObject(&m_Font);
	CSize m_LinkSize = pDC->GetOutputTextExtent(m_Text);
	pDC->SelectObject(pOldFont);
	GetDesktopWindow()->ReleaseDC(pDC);
	return m_LinkSize;
}

