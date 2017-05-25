#if !defined(AFX_MYREGTREECTRL_H__49363F2E_0A6A_40BD_A0B7_2E10DC9A577E__INCLUDED_)
#define AFX_MYREGTREECTRL_H__49363F2E_0A6A_40BD_A0B7_2E10DC9A577E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyRegTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyRegTreeCtrl view

class CMyRegTreeCtrl : public CTreeView
{
protected:
	CMyRegTreeCtrl();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyRegTreeCtrl)

// Attributes
public:

// Operations
public:

	void ReStart();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRegTreeCtrl)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyRegTreeCtrl();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:

	CImageList	m_TreeImageList;
	//{{AFX_MSG(CMyRegTreeCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYREGTREECTRL_H__49363F2E_0A6A_40BD_A0B7_2E10DC9A577E__INCLUDED_)
