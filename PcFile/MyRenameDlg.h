#pragma once


// CMyRenameDlg 对话框

class CMyRenameDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyRenameDlg)

public:
	CMyRenameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyRenameDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_RENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_FileName;
};
