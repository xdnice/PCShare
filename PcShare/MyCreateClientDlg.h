#if !defined(AFX_MYCREATECLIENTDLG_H__4161D257_6B0F_464E_B4D3_20AF765F1F90__INCLUDED_)
#define AFX_MYCREATECLIENTDLG_H__4161D257_6B0F_464E_B4D3_20AF765F1F90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyCreateClientDlg.h : header file
//

#include "MyLink.h"

/////////////////////////////////////////////////////////////////////////////
// CMyCreateClientDlg dialog

class CMyCreateClientDlg : public CDialog
{
// Construction
public:

	CMyCreateClientDlg();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyCreateClientDlg)
	enum { IDD = IDD_DIALOG_CREATE_CLIENT };
	CComboBox	m_IpList;
	CString	m_Port;
	CString	m_BakUrl;
	CString	m_CtrlFile;
	int		m_Proc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCreateClientDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyCreateClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCreate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
	CString m_StartFile;
	afx_msg void OnBnClickedRadioVip();
	afx_msg void OnBnClickedRadioNovip();
	BOOL m_IsVip;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCREATECLIENTDLG_H__4161D257_6B0F_464E_B4D3_20AF765F1F90__INCLUDED_)
