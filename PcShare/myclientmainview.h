#if !defined(AFX_MYCLIENTMAINVIEW_H__F62905AC_B92B_4B6B_8C38_4B7D7ABC36AE__INCLUDED_)
#define AFX_MYCLIENTMAINVIEW_H__F62905AC_B92B_4B6B_8C38_4B7D7ABC36AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyClientMainView.h : header file
//

#include "ListViewCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CMyClientMainView view

#define SORT_IP			0
#define SORT_TITLE		1


class CMyClientMainView : public CListViewEx
{
protected:
	CMyClientMainView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyClientMainView)

// Attributes
public:

	UINT nSortId;

// Operations
public:
	void SetItemInfo(char* pInfo , char* pId);
	LPCLIENTITEM FindTitle(char *ItemName);
	LPCLIENTITEM GetTitleItem(char *Title);
	LPCLIENTITEM GetNameItem(char *Name);
	LPCLIENTITEM GetCurSel();
	LPCLIENTITEM GetSocketItem(SOCKET s);
	LPCLIENTITEM InsertItem(LPCLIENTITEM pItem);
	void DeleteCurItem();
	DWORD CloseClient(SOCKET s);
	void StopWork();
	int  FindItemTitle(char *ItemName);
	int  FindItem(char *ItemName);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyClientMainView)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyClientMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	static int CALLBACK CompareCountries(LPARAM lParam1, LPARAM lParam2,
                                  LPARAM lParamSort);

	// Generated message map functions
protected:
	CImageList m_imagelist;
	CPtrList   m_List;
	HANDLE	   m_Thread;	
	UINT	   m_Command;

	//{{AFX_MSG(CMyClientMainView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnInitialUpdate(); // called first time after construct
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnResizeWnd(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCLIENTMAINVIEW_H__F62905AC_B92B_4B6B_8C38_4B7D7ABC36AE__INCLUDED_)
