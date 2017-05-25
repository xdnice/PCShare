// PcFile.h : main header file for the PCFILE application
//

#if !defined(AFX_PCFILE_H__03612636_1F7B_4C10_8D86_0A03707121B5__INCLUDED_)
#define AFX_PCFILE_H__03612636_1F7B_4C10_8D86_0A03707121B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPcFileApp:
// See PcFile.cpp for the implementation of this class
//

class CPcFileApp : public CWinApp
{
public:
	CPcFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcFileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CPcFileApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCFILE_H__03612636_1F7B_4C10_8D86_0A03707121B5__INCLUDED_)
