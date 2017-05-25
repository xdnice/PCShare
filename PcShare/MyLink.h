#if !defined(AFX_MYLINK_H__CB717501_4ABD_4331_AE3C_BD28C050F561__INCLUDED_)
#define AFX_MYLINK_H__CB717501_4ABD_4331_AE3C_BD28C050F561__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyLink.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyLink window

class CMyLink : public CStatic
{
// Construction
public:
	CMyLink();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyLink)
	//}}AFX_VIRTUAL

// Implementation
public:
	CSize GetMySize(LPCTSTR m_Text);
	void SetMyFont(LPCTSTR FontName,int FontSize,int FontWidth,BOOL IsLine);
	virtual ~CMyLink();

	// Generated message map functions
protected:

	CFont m_Font;
	//{{AFX_MSG(CMyLink)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLINK_H__CB717501_4ABD_4331_AE3C_BD28C050F561__INCLUDED_)
