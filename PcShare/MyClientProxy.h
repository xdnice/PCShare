#if !defined(AFX_MYCLIENTPROXY_H__155985B9_9566_4455_9596_072321FF48A7__INCLUDED_)
#define AFX_MYCLIENTPROXY_H__155985B9_9566_4455_9596_072321FF48A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyClientProxy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyClientProxy dialog

class CMyClientProxy : public CDialog
{
// Construction
public:
	CMyClientProxy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyClientProxy)
	enum { IDD = IDD_DIALOG_CLIENT_PROXY };
	UINT	m_Port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyClientProxy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyClientProxy)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCLIENTPROXY_H__155985B9_9566_4455_9596_072321FF48A7__INCLUDED_)
