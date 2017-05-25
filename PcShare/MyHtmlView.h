#if !defined(AFX_MYHTMLVIEW_H__7923797E_788F_4B61_AA6A_5AE270EC7A5A__INCLUDED_)
#define AFX_MYHTMLVIEW_H__7923797E_788F_4B61_AA6A_5AE270EC7A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyHtmlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlView html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CMyHtmlView : public CHtmlView
{
protected:
        // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyHtmlView)

// html Data
public:
	//{{AFX_DATA(CMyHtmlView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

		CMyHtmlView();   
		virtual ~CMyHtmlView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyHtmlView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMyHtmlView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYHTMLVIEW_H__7923797E_788F_4B61_AA6A_5AE270EC7A5A__INCLUDED_)
