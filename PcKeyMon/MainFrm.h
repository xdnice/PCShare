// MainFrm.h : CMainFrame 类的接口
//

#include "MyEditView.h"

#pragma once
class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	BOOL				m_CurSorStatus;
	HCURSOR				m_WaitCur;
	CMyEditView*		pKeyView;
// 实现
public:
	CMainFrame();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;
	THREADINFO  m_Info;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnClose();
	afx_msg void OnSave();
	afx_msg void OnEmpty();
	afx_msg void OnUpdateSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEmpty(CCmdUI *pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnCRclick();
	void StartWork(void);
};


