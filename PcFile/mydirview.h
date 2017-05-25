#if !defined(AFX_MYDIRVIEW_H__F3A04BDC_D22E_4250_A41A_613AF047ABE2__INCLUDED_)
#define AFX_MYDIRVIEW_H__F3A04BDC_D22E_4250_A41A_613AF047ABE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDirView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDirView view

class CMyDirView : public CView
{
protected:
	CMyDirView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyDirView)

// Attributes
public:

// Operations
public:

// Operations
public:
	CListView *GetListView();
	CTreeView *GetTreeView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDirView)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSplitterWnd	m_WndSplitter;
	virtual ~CMyDirView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyDirView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIRVIEW_H__F3A04BDC_D22E_4250_A41A_613AF047ABE2__INCLUDED_)
