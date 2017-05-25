#if !defined(AFX_MYDIRINFODLG_H__B02C02C1_B93F_4D55_9740_EB367EDB550F__INCLUDED_)
#define AFX_MYDIRINFODLG_H__B02C02C1_B93F_4D55_9740_EB367EDB550F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDirInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDirInfoDlg dialog

class CMyDirInfoDlg : public CDialog
{
// Construction
public:
	CMyDirInfoDlg(DIRINFO m_DirInfo);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDirInfoDlg)
	enum { IDD = IDD_DIALOG_DIRINFO };
	CString	m_Path;
	CString	m_Time;
	CString	m_FileCount;
	CString	m_Len;
	CString	m_Type;
	BOOL	m_Arich;
	BOOL	m_Hide;
	BOOL	m_ReadOnly;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDirInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CString m_Title;
	// Generated message map functions
	//{{AFX_MSG(CMyDirInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIRINFODLG_H__B02C02C1_B93F_4D55_9740_EB367EDB550F__INCLUDED_)
