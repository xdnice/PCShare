#if !defined(AFX_MYPROCESSLISTVIEW_H__89065C61_8E1B_4489_8401_235D1126C607__INCLUDED_)
#define AFX_MYPROCESSLISTVIEW_H__89065C61_8E1B_4489_8401_235D1126C607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyProcessListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyProcessListView view

class CMyProcessListView : public CListView
{
protected:
	CMyProcessListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyProcessListView)

// Attributes
public:

	
// Operations
public:
	void InsertMyItem(LPPROCESSLIST	pItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyProcessListView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_TmpBuf[2048];

	virtual ~CMyProcessListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyProcessListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROCESSLISTVIEW_H__89065C61_8E1B_4489_8401_235D1126C607__INCLUDED_)
