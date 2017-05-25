#if !defined(AFX_MYFINDFILEDLG_H__891768AD_30D3_4BF3_846C_EE67ED617D64__INCLUDED_)
#define AFX_MYFINDFILEDLG_H__891768AD_30D3_4BF3_846C_EE67ED617D64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFindFileDlg.h : header file
//

#include "MyFileTransView.h"

/////////////////////////////////////////////////////////////////////////////
// CMyFindFileDlg dialog

class CMyFindFileDlg : public CDialog
{
// Construction
public:
	CMyFindFileDlg(CWnd* pParent , char* pDirName , LPCLIENTDATA pTransData, CMyFileTransView* pWnd);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyFindFileDlg)
	enum { IDD = IDD_DIALOG_FINDFILE };
	CListCtrl	m_FileList;
	CString	m_Dir;
	CString	m_File;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFindFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	LPCLIENTDATA pData;
	CImageList m_imagelist;
	CList <LPMYICONINFO,LPMYICONINFO> m_List;
	void FindMyImage(LPCTSTR ItemName,int &nImage);
	BOOL InsertMyItem(LPDIRFILELIST pItem);
	CMyFileTransView*	pFileTransView;

	// Generated message map functions
	//{{AFX_MSG(CMyFindFileDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickListFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFindRightOpen();
	afx_msg void OnFindExecShow();
	afx_msg void OnFindDownload();
	afx_msg void OnFindDelete();
	afx_msg void OnFindAttrib();
	afx_msg void OnDblclkListFile(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFINDFILEDLG_H__891768AD_30D3_4BF3_846C_EE67ED617D64__INCLUDED_)
