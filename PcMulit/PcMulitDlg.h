// PcMulitDlg.h : header file
//

#if !defined(AFX_PCMULITDLG_H__2F6E3702_4595_4A61_8798_1A7254DF90ED__INCLUDED_)
#define AFX_PCMULITDLG_H__2F6E3702_4595_4A61_8798_1A7254DF90ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "MyFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CPcMulitDlg dialog

class CPcMulitDlg : public CDialog
{
// Construction
public:
	void StartWork(void);
	void SetTitle(char* pTitle);
	CPcMulitDlg(CWnd* pParent = NULL);	// standard constructor
	~CPcMulitDlg();
	
// Dialog Data
	//{{AFX_DATA(CPcMulitDlg)
	enum { IDD = IDD_PCMULIT_DIALOG };
	CMyFrame	m_Frame;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcMulitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL		m_CurSorStatus;
	HCURSOR		m_WaitCur;
	BITMAPINFO	m_BmpInfo;
	HICON		m_hIcon;
	char		m_Title[256];
	THREADINFO  m_Info;
	// Generated message map functions
	//{{AFX_MSG(CPcMulitDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	afx_msg LRESULT DrawOneFrame(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCMULITDLG_H__2F6E3702_4595_4A61_8798_1A7254DF90ED__INCLUDED_)
