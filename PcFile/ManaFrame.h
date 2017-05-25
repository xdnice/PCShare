#if !defined(AFX_MAINFRAME_H__2A4291AB_BF7B_419B_B116_547EAD573A48__INCLUDED_)
#define AFX_MAINFRAME_H__2A4291AB_BF7B_419B_B116_547EAD573A48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManaFrame frame

#include "MyFileTransView.h"
#include "MyDirTreeView.h"
#include "MyDirListView.h"
#include "MyDirView.h"

class CManaFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CManaFrame)
public:

	CManaFrame();           // protected constructor used by dynamic creation
	~CManaFrame();
// Attributes
public:

// Operations
public:

	BOOL StartWork();
	
protected:  
	
	//数据类
	CLIENTDATA			m_MissionData;			//数据传送结构
	BOOL				m_EnalbeFileTrans;

	//图标
	BOOL				m_CurSorStatus;
	HCURSOR				m_WaitCur;
	
	//视类
	CMyDirListView*		pDirListView;
	CMyDirTreeView*		pDirTreeView;
	CMyFileTransView*	pFileTransView;

	//控件类
	CToolBar			m_wndToolBar;
	CStatusBar			m_wndStatusBar;
	CSplitterWnd		m_WndSplitter;
	
	void DeleteTreeChild(HTREEITEM hItem);
	void GetDiskInfo(HTREEITEM hItem);
	BOOL GetClientDir(LPCTSTR RmotePath,LPCTSTR LocalPath);
	void ShowMyText(LPCTSTR Str);
	void ShowResponse(UINT m_Response);
	BOOL GetMyDirLeftPath(HTREEITEM hItem,char *Path);
	void DisplayButton(CTreeCtrl *pTree,HTREEITEM hti,int nChild);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManaFrame)
	public:
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:

	CImageList	m_ilTB;
	char		m_IniFileName[256];
	// Generated message map functions
	//{{AFX_MSG(CManaFrame)

	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDirFlush();
	afx_msg void OnDirPrev();
	afx_msg void OnUpdateDirPrev(CCmdUI* pCmdUI);
	afx_msg void OnDirAttrib();
	afx_msg void OnUpdateDirAttrib(CCmdUI* pCmdUI);
	afx_msg void OnDirRightDelete();
	afx_msg void OnDirRightExecShow();
	afx_msg void OnDirRightOpen();
	afx_msg void OnUpdateDirRightOpen(CCmdUI* pCmdUI);
	afx_msg void OnDirRightRename();
	afx_msg void OnUpdateDirRightRename(CCmdUI* pCmdUI);
	afx_msg void OnDirRightSelall();
	afx_msg void OnUpdateDirRightSelall(CCmdUI* pCmdUI);
	afx_msg void OnDirCreate();
	afx_msg void OnUpdateDirCreate(CCmdUI* pCmdUI);
	afx_msg void OnDirRightDownload();
	afx_msg void OnUpdateDirRightDownload(CCmdUI* pCmdUI);
	afx_msg void OnDirRightUpload();
	afx_msg void OnDirRightAttrib();
	afx_msg void OnUpdateDirRightAttrib(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMyFiles(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDirRightDelete(CCmdUI* pCmdUI);
	afx_msg void OnDirFindFile();
	afx_msg void OnUpdateDirFindFile(CCmdUI* pCmdUI);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnDirRightRClick(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetMyCursor(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnDirRightRenameOk(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnTreeSelChanged(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnFileTransRClick(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileTransDeleteAll();
	afx_msg void OnUpdateFileTransDeleteAll(CCmdUI *pCmdUI);
	afx_msg void OnFileTransStart();
	afx_msg void OnUpdateFileTransStart(CCmdUI *pCmdUI);
	afx_msg void OnFileTransStop();
	afx_msg void OnUpdateFileTransStop(CCmdUI *pCmdUI);
	afx_msg void OnFileTransDelete();
	afx_msg void OnUpdateFileTransDelete(CCmdUI *pCmdUI);
	afx_msg LRESULT OnTransState(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateDirFlush(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDirRightUploadExec();
	
	void GetFileToTrans(void);
	void SaveTransInfo();
	void LoadTransInfo();
	void SetIniFileName(char* pFileName);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__2A4291AB_BF7B_419B_B116_547EAD573A48__INCLUDED_)
