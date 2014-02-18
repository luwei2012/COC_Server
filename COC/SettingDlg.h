#pragma once


// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	BOOL m_autoStart;
	BOOL m_pop;
	afx_msg void OnBnClickedRadio1(); 
	BOOL m_contentChanged;
	CString m_skinPath;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheck1();
	virtual BOOL OnInitDialog();
	bool AutoStart(const bool &bStart);
	void UpdateCtrl(void);
	int m_radioValue;  
};
