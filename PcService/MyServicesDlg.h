#if !defined(AFX_MYSERVICESDLG_H__AAFB729C_B589_4B77_B199_032B16DA1B43__INCLUDED_)
#define AFX_MYSERVICESDLG_H__AAFB729C_B589_4B77_B199_032B16DA1B43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyServicesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyServicesDlg dialog
#include "MyMarco.h"
class CMyServicesDlg : public CDialog
{
// Construction
public:
	CMyServicesDlg(LPMYSERVICES Services);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyServicesDlg)
	enum { IDD = IDD_DIALOG_SERVICES };
	CString	m_StartType;
	CString	m_DispName;
	CString	m_Dist;
	CString	m_ExeName;
	CString	m_Name;
	//}}AFX_DATA

	BOOL m_IsModify;
	DWORD m_Type;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyServicesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	LPMYSERVICES pServices;

	// Generated message map functions
	//{{AFX_MSG(CMyServicesDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERVICESDLG_H__AAFB729C_B589_4B77_B199_032B16DA1B43__INCLUDED_)
