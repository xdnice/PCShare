#if !defined(AFX_MYFILETRANSVIEW_H__49F42741_1D92_450D_A9FC_430951547407__INCLUDED_)
#define AFX_MYFILETRANSVIEW_H__49F42741_1D92_450D_A9FC_430951547407__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFileTransView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFileTransView view

class CMyFileTransView : public CListView
{
protected:
	CMyFileTransView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyFileTransView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFileTransView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyFileTransView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyFileTransView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
	int CheckValidFile(void);
	afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);
	void SetItemFlag(int nItem, BOOL nFlag);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFILETRANSVIEW_H__49F42741_1D92_450D_A9FC_430951547407__INCLUDED_)
