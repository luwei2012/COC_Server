
// COCDlg.h : 头文件
//

#pragma once 
#include <vector>
#include "afxwin.h"
#include <afxstr.h> 
#include "Server.h"
#include "Message.h"
#include "IHListBox.h"
#include "TaskbarNotifier.h"

using namespace std;

#define WM_SHOWTASK WM_USER+1

class CMainDoc;
// CCOCDlg 对话框
class CCOCDlg : public CDialogEx
{
	// 构造
public:
	CCOCDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_COC_DIALOG };

	// 实现任务托盘
	NOTIFYICONDATA m_nid;
	// 标识是否是单机模式，默认不是
	bool m_bAlone;
	// 储存IP地址
	vector<CString> m_ipAdds;
	CString m_curIP;//当天选中的IP
	
	// 服务器 
	CServer m_server; 

	// 监听的端口
	int m_port;

	// 状态
	int m_status;//0表示未激活；1表示已连接；
	// 窗口标题名称
	CString m_windowName;

	// 窗口句柄
	CWnd* pWndPrev;

	// 计时关机
	int m_shutDown;
	bool m_shutTimerFlag;

	CMainDoc*				m_pMainDoc;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// 实现
protected:
	HICON m_hIcon;
	CTaskbarNotifier		m_wndTaskbarNotifier;	//弹出动画
	CStatusBar				m_statusBar;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParams);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy); 
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnCbnSelchangeCombo1();
	// 获取本机所有IP地址
	bool GetIPadd(void);
	// IP地址的列表
	CComboBox m_ipList;
	CButton m_ButtonStart;
	void EnableControls(bool flag);
	CButton m_checkBox;
	// 开始按键刷新
	void startService(void);
	void stopService(void);
	bool startServer(void);
	bool stopServer(void);

	CIHListBox m_messageList;

	bool findCOCWindow(void);
	bool openCOC(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void updateMessage(CString message);
	bool validatePassword(char* pwd);
	CString m_password;

	void OnReceive( int nErrorCode );
	void OnConnect( int nErrorCode );
	void OnOutOfBandData( int nErrorCode );
	void OnAccept( int nErrorCode );
	void OnSend( int nErrorCode );
	void handleMessage(char* data);
	bool findNextToken(char* des,char* data, int& posotion, char sp);
	void InitTaskbarNotifier(void);
	void setShutDownTime(int time);
	void updateTime(void);
};
