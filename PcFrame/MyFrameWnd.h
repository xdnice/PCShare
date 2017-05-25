#if !defined(AFX_MYFRAMEWND_H__FE4E9B37_C1C1_489A_8779_0745C311B462__INCLUDED_)
#define AFX_MYFRAMEWND_H__FE4E9B37_C1C1_489A_8779_0745C311B462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFrameWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFrameWnd frame
#include "MyFrameView.h"

class CMyFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrameWnd)
protected:

public:
	CMyFrameWnd();           // protected constructor used by dynamic creation

	virtual ~CMyFrameWnd();
// Attributes
public:

// Operations
public:

	BOOL				m_CurSorStatus;
	HCURSOR				m_WaitCur;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFrameWnd)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	CStatusBar		m_wndStatusBar;
	CToolBar		m_wndToolBar;
	FRAMINFO		m_FrameInfo;
	CMyFrameView*	pFrameView;
	CImageList		m_ImageList;

	BOOL StartWork();

	// Generated message map functions
	//{{AFX_MSG(CMyFrameWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFrameSave();
	afx_msg void OnFrameControl();
	afx_msg void OnFrameCtrl();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnUpdatePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFrameControl(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFrameSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFrameCtrl(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFRAMEWND_H__FE4E9B37_C1C1_489A_8779_0745C311B462__INCLUDED_)
