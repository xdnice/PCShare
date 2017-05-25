#if !defined(AFX_MYEVENTVIEW_H__6A335856_7263_463E_9B8F_C457B5700E2D__INCLUDED_)
#define AFX_MYEVENTVIEW_H__6A335856_7263_463E_9B8F_C457B5700E2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyEventView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyEventView view

#include "ListViewCtrlEx.h"

class CMyEventView : public CListView
{
protected:
	CMyEventView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyEventView)

// Attributes
public:

// Operations
public:

	void InsertItem(LPCTSTR Text, BOOL Flag);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEventView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyEventView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	CImageList m_imagelist;
	//{{AFX_MSG(CMyEventView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnResizeWnd(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEVENTVIEW_H__6A335856_7263_463E_9B8F_C457B5700E2D__INCLUDED_)
