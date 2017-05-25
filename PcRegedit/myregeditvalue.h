#if !defined(AFX_MYREGEDITVALUE_H__06DE3C5F_14C1_4E27_A7C6_A20136AF0537__INCLUDED_)
#define AFX_MYREGEDITVALUE_H__06DE3C5F_14C1_4E27_A7C6_A20136AF0537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyRegEditValue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyRegEditValue dialog

class CMyRegEditValue : public CDialog
{
// Construction
public:
	CMyRegEditValue(LPCTSTR Name,LPCTSTR Value,int IsDigital);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyRegEditValue)
	enum { IDD = IDD_DIALOG_REG_EDIT_VALUE };
	CString	m_Name;
	CString	m_Value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRegEditValue)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL m_IsDigital;
	// Generated message map functions
	//{{AFX_MSG(CMyRegEditValue)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYREGEDITVALUE_H__06DE3C5F_14C1_4E27_A7C6_A20136AF0537__INCLUDED_)
