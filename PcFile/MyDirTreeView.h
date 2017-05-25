#if !defined(AFX_MYDIRTREEVIEW_H__C2BB8727_7217_4415_8384_71433E07297E__INCLUDED_)
#define AFX_MYDIRTREEVIEW_H__C2BB8727_7217_4415_8384_71433E07297E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDirTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDirTreeView view

class CMyDirTreeView : public CTreeView
{
protected:
	CMyDirTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyDirTreeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDirTreeView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_IsEdit;
	CImageList		m_TreeImageList;
	virtual ~CMyDirTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyDirTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIRTREEVIEW_H__C2BB8727_7217_4415_8384_71433E07297E__INCLUDED_)
