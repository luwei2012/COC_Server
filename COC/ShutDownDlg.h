#pragma once
#include "afxwin.h"

class CCOCDlg;

// CShutDownDlg 对话框

class CShutDownDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShutDownDlg)

public:
	CShutDownDlg(CCOCDlg* pParent = NULL);   // 标准构造函数
	virtual ~CShutDownDlg();
	CCOCDlg* m_pParent;

// 对话框数据
	enum { IDD = IDD_DIALOG_SHUTDOWN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1(); 
	afx_msg void OnBnClickedOk();
	void setTime(int time);
	int m_shutDownTime;
};
