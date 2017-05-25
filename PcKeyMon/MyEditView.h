#if !defined(AFX_MYEDITVIEW_H__11944F1A_F625_47E1_97FE_FDD7836990D9__INCLUDED_)
#define AFX_MYEDITVIEW_H__11944F1A_F625_47E1_97FE_FDD7836990D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyEditView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyEditView view

class CMyEditView : public CEditView
{
protected:
	CMyEditView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyEditView)

// Attributes
public:

// Operations
public:

	void SaveChar(void);

	int nTxtLen;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEditView)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyEditView)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChange();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	
	//}}AFX_MSG

	afx_msg LRESULT OnGetStr(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEDITVIEW_H__11944F1A_F625_47E1_97FE_FDD7836990D9__INCLUDED_)
