#if !defined(AFX_MYFRAMEVIEW_H__C84AE6DD_DD18_4AC4_B317_872CC653F7BE__INCLUDED_)
#define AFX_MYFRAMEVIEW_H__C84AE6DD_DD18_4AC4_B317_872CC653F7BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFrameView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFrameView view

class CMyFrameView : public CScrollView
{
protected:
	CMyFrameView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyFrameView)

// Attributes
public:

// Operations
public:

	SOCKET	m_MouseSocket;
	void SaveFrame();
	void GetSize(char* pText);
	BOOL ExecCmd(LPMOUSEINFO pInfo);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFrameView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBitmap	m_MainBitmap;					//Ö÷Í¼Ïó
	char*	pBitHeadInfo;
	BOOL	bIsInit;
	LPBITMAPINFOHEADER lpbi;
	

	virtual ~CMyFrameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyFrameView)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnOneFrame(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	void MakeBitmap(CDC *pDC);
	void InitMyData(CSize m_Size);
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFRAMEVIEW_H__C84AE6DD_DD18_4AC4_B317_872CC653F7BE__INCLUDED_)
