#if !defined(AFX_MYSETUPDLG_H__4EFEA936_91D5_4D6B_9B20_F0C84F903716__INCLUDED_)
#define AFX_MYSETUPDLG_H__4EFEA936_91D5_4D6B_9B20_F0C84F903716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMySetupDlg dialog

class CMySetupDlg : public CDialog
{
// Construction
public:

	CMySetupDlg();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMySetupDlg)
	enum { IDD = IDD_DIALOG_SETUP };
	CSpinButtonCtrl	m_SpinPortMain;
	CSpinButtonCtrl	m_SpinMaxLinkMain;
	CString	m_MaxLinkMain;
	CString	m_PortMain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySetupDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMySetupDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSETUPDLG_H__4EFEA936_91D5_4D6B_9B20_F0C84F903716__INCLUDED_)
