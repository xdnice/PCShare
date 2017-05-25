#if !defined(AFX_MYFILETRANSDLG_H__89667B1D_9CD1_4125_9265_9CF9B764E149__INCLUDED_)
#define AFX_MYFILETRANSDLG_H__89667B1D_9CD1_4125_9265_9CF9B764E149__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFileTransDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFileTransDlg dialog

class CMyFileTransDlg : public CDialog
{
// Construction
public:
	CMyFileTransDlg(char* pSrcFile , char* pDesSrc);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyFileTransDlg)
	enum { IDD = IDD_DIALOG_FILE_TRANS };
	CAnimateCtrl	m_Animal;
	CProgressCtrl	m_FileStep;
	CString	m_SrcFile;
	CString	m_DesFile;
	//}}AFX_DATA

	BOOL IsUpLoad;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFileTransDlg)
	public:
	virtual BOOL Create(CWnd* pWnd);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HWND hWnd;
	// Generated message map functions
	//{{AFX_MSG(CMyFileTransDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnTransState(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFILETRANSDLG_H__89667B1D_9CD1_4125_9265_9CF9B764E149__INCLUDED_)
