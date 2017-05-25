#if !defined(AFX_MYFILEINFO_H__4B10311C_C48D_4280_8A57_1173E51A2055__INCLUDED_)
#define AFX_MYFILEINFO_H__4B10311C_C48D_4280_8A57_1173E51A2055__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFileInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFileInfo dialog

class CMyFileInfo : public CDialog
{
// Construction
public:
	CMyFileInfo(CFileStatus m_FileStatus);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyFileInfo)
	enum { IDD = IDD_DIALOG_FILEINFO };
	BOOL	m_Arich;
	BOOL	m_Hide;
	BOOL	m_ReadOnly;
	CString	m_Path;
	CString	m_AccessTime;
	CString	m_CreateTime;
	CString	m_Len;
	CString	m_ModifyTime;
	CString	m_Type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFileInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_Title;
	// Generated message map functions
	//{{AFX_MSG(CMyFileInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFILEINFO_H__4B10311C_C48D_4280_8A57_1173E51A2055__INCLUDED_)
