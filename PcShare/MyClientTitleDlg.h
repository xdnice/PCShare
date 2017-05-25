#if !defined(AFX_MYCLIENTTITLEDLG_H__39452878_6435_4633_A663_2D788DECEF8E__INCLUDED_)
#define AFX_MYCLIENTTITLEDLG_H__39452878_6435_4633_A663_2D788DECEF8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyClientTitleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyClientTitleDlg dialog

class CMyClientTitleDlg : public CDialog
{
// Construction
public:
	CMyClientTitleDlg(char *Title);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyClientTitleDlg)
	enum { IDD = IDD_DIALOG_CLIENT_TITLE };
	CString	m_Title;
	//}}AFX_DATA

	BOOL m_IsSetNet;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyClientTitleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyClientTitleDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCLIENTTITLEDLG_H__39452878_6435_4633_A663_2D788DECEF8E__INCLUDED_)
