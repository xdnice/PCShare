#if !defined(AFX_MYCLIENTINFOVIEW_H__D2998A0B_99F2_403C_BA9B_6F76CB9E6F1E__INCLUDED_)
#define AFX_MYCLIENTINFOVIEW_H__D2998A0B_99F2_403C_BA9B_6F76CB9E6F1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyClientInfoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyClientInfoView view

class CMyClientInfoView : public CListView
{
protected:
	CMyClientInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyClientInfoView)

// Attributes
public:

	void SetMyItem(LPCLIENTITEM ClientItem);
	
// Operations
public:
	void Empty();
	void IsCurItem(LPCLIENTITEM ClientItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyClientInfoView)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_imagelist;
	LPCLIENTITEM pClientItem;
	
	virtual ~CMyClientInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyClientInfoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnResizeWnd(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCLIENTINFOVIEW_H__D2998A0B_99F2_403C_BA9B_6F76CB9E6F1E__INCLUDED_)
