#if !defined(AFX_MYSERVICESVIEW_H__D13EF556_250E_4D85_9EF1_3C36E7155EDB__INCLUDED_)
#define AFX_MYSERVICESVIEW_H__D13EF556_250E_4D85_9EF1_3C36E7155EDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyServicesView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyServicesView view
#include <Winsvc.h>
#include <afxcview.h>
#include "MyMarco.h"

class CMyServicesView : public CListView
{
protected:
	CMyServicesView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyServicesView)

// Attributes
public:

	void ReStart();

// Operations
public:
	void UpDateItem(int nItem,LPMYSERVICES pServices);
	void InsertItem(LPMYSERVICES pServices);
	void DeleteAllItems();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyServicesView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyServicesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CImageList m_imagelist;
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyServicesView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERVICESVIEW_H__D13EF556_250E_4D85_9EF1_3C36E7155EDB__INCLUDED_)
