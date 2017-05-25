#if !defined(AFX_MYDISKINFO_H__2DFBD911_0178_44AF_ADAE_F44290F59E7F__INCLUDED_)
#define AFX_MYDISKINFO_H__2DFBD911_0178_44AF_ADAE_F44290F59E7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDiskInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDiskInfo dialog

class CMyDiskInfo : public CDialog
{
// Construction
public:
	CMyDiskInfo(DISKINFO m_DiskInfo);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDiskInfo)
	enum { IDD = IDD_DIALOG_DISKINFO };
	CString	m_Volum;
	CString	m_Content;
	CString	m_FatType;
	CString	m_Type;
	CString	m_Unuse;
	CString	m_Use;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDiskInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_Title;
	// Generated message map functions
	//{{AFX_MSG(CMyDiskInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDISKINFO_H__2DFBD911_0178_44AF_ADAE_F44290F59E7F__INCLUDED_)
