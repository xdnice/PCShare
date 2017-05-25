// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include "MyProcessListView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;

	//数据类
	CLIENTDATA			m_MissionData;			//数据传送结构

	//图标
	BOOL				m_CurSorStatus;
	HCURSOR				m_WaitCur;

	CMyProcessListView* pProcessListView;

	void ShowResponse(UINT m_Response);

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

	afx_msg void OnProcessFlush();
	afx_msg void OnUpdateProcessFlush(CCmdUI* pCmdUI);
	afx_msg void OnProcessKill();
	afx_msg void OnUpdateProcessKill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMyFiles(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnUserRClickProcess(WPARAM wParam,LPARAM lParam);

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnClose();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnSetMyCursor(WPARAM wParam,LPARAM lParam);
};


