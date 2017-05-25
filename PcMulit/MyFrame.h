#if !defined(AFX_MYFRAME_H__C71BE42C_F09F_458C_BB9C_33FC5544FFB9__INCLUDED_)
#define AFX_MYFRAME_H__C71BE42C_F09F_458C_BB9C_33FC5544FFB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFrame.h : header file
//

#define IMAGE_WIDTH       176
#define IMAGE_HEIGHT      144

/////////////////////////////////////////////////////////////////////////////
// CMyFrame window

class CMyFrame : public CStatic
{
// Construction
public:
	CMyFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawOneFrame(LPBITMAPINFO pInfo, LPVOID pData);
	virtual ~CMyFrame();
	
	void SaveFrame();
	BOOL SaveBitmapToFile(HBITMAP hBitmap , CString lpFileName);
	HBITMAP hBitmap;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyFrame)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFRAME_H__C71BE42C_F09F_458C_BB9C_33FC5544FFB9__INCLUDED_)
