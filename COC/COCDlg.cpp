
// COCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "COC.h"
#include "COCDlg.h"
#include "afxdialogex.h"
#include "SettingDlg.h"
#include <string.h>
#include "ShutDownDlg.h"
#include "MainDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCOCDlg 对话框

#define TIMER1 1
#define TIMER2 2
#define INTERNAL_TIME 5000
//##################################local global variable################################//
static UINT	indicators[] = 
{
	IDS_MESSAGE,
	IDS_TIME
};

CCOCDlg::CCOCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCOCDlg::IDD, pParent)
	, m_password(_T("123456"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_shutTimerFlag = false;
	m_pMainDoc = ((CCOCApp*)AfxGetApp())->m_pMainDoc; 
}

void CCOCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ipList);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonStart);
	DDX_Control(pDX, IDC_CHECK1, m_checkBox);
	DDX_Control(pDX, IDC_LIST2, m_messageList);
}

BEGIN_MESSAGE_MAP(CCOCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_SIZE() 
	ON_BN_CLICKED(IDC_CHECK1, &CCOCDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CCOCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CCOCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCOCDlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCOCDlg::OnCbnSelchangeCombo1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCOCDlg 消息处理程序

BOOL CCOCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_shutDown = 0;
	//make StatusBar
	if(!m_statusBar.Create(this) ||
		!m_statusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0(_T("create status bar error!"));
		return -1;
	}
	CRect rect;
	GetClientRect(&rect);

	m_statusBar.SetPaneInfo(0, IDS_MESSAGE, SBPS_STRETCH, 0);
	m_statusBar.SetPaneInfo(1, IDS_TIME, SBPS_NORMAL, rect.Width()-175);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	m_statusBar.SetPaneText(0, _T("倒计时："));
	CTime time = CTime::GetCurrentTime();
	m_statusBar.SetPaneText(1, time.Format("%H:%M:%S"));
	m_statusBar.ShowWindow(SW_HIDE);
 
	//获取本机IP
	GetIPadd();
	//初始化下拉列表
	int i=0;
	for (i;i < m_ipAdds.size();i++)
	{
		m_ipList.AddString(m_ipAdds.at(i));
	}
	m_ipList.SetCurSel(i-1);
	// 默认不是单机模式
	m_bAlone = false;
	// 默认端口号为
	m_port = 5888;
	// 初始状态代码
	m_status = 0;
	//--------------托盘显示--------------------//
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd  = this->m_hWnd;
	m_nid.uID =  IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;

	m_nid.uCallbackMessage  = WM_SHOWTASK;//自定义消息名称
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(m_nid.szTip,"服务器程序");//信息提示条“服务器程序”
	Shell_NotifyIcon(NIM_ADD,&m_nid);//在托盘区添加图标

	// 设置窗口名称
	m_windowName = "BlueStacks App Player for Windows (beta-1)"; 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCOCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCOCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CCOCDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME) return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出菜单
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();
			menu.AppendMenu(MF_STRING,WM_DESTROY,"关闭");
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			this->ShowWindow(SW_SHOWNORMAL);
		}
		break;
	}
	return 0;
}


void CCOCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if (nType==SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);
	} 

}




BOOL CCOCDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	Shell_NotifyIcon(NIM_DELETE,&m_nid); 
	return CDialogEx::DestroyWindow();
}



void CCOCDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bAlone==false)
	{
		m_bAlone=true;
		m_ipList.EnableWindow(false);
	}else
	{
		m_bAlone = false;
		m_ipList.EnableWindow(true);
	}
}


void CCOCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码  
	if (m_bAlone)
	{
		if (m_status==1)
		{
			//停止刷新按钮
			stopService();
		}else
		{
			//开始刷新
			startService();
		}
	}else
	{
		int selected = m_ipList.GetCurSel();
		if (selected>=0)
		{
			m_ipList.GetLBText(selected,m_curIP);
		}
		else
		{ 
			//提示用户需要选择一个IP
			MessageBox(IDS_SELECT_IP),IDS_WARNING,MB_OK );
			return ;
		}
		if (m_status==1)
		{
			//停止监听
			stopServer();
		}else
		{
			//开始监听
			startServer();
		}
	}
	m_status = ++m_status % 2;
	switch(m_status)
	{
	case 0:
		m_ButtonStart.SetWindowText("开始"); 
		EnableControls(true);
		break; 
	default:
		m_ButtonStart.SetWindowText("停止"); 
		EnableControls(false);
		break; 
	} 	
}

//定时关机
void CCOCDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CShutDownDlg shutDlg(this);
	shutDlg.setTime(m_shutDown);
	shutDlg.DoModal();
}


//设置对话框
void CCOCDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CSettingDlg setDlg;
	setDlg.DoModal();
}


void CCOCDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}



// 获取本机所有IP地址
bool CCOCDlg::GetIPadd(void)
{
	WSADATA wsadata;
	int ret = WSAStartup(MAKEWORD(2,2),&wsadata);
	if (ret!=0)
	{
		return false;
	}
	//获取主机名
	char hostname[256]={'\0'};
	ret = gethostname(hostname,sizeof(hostname));
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	m_pMainDoc->m_host.Format("%s",hostname);
	//获取IP
	HOSTENT* host = gethostbyname(hostname);
	if (host == NULL)
	{
		return false;
	}
	//逐个转化为ip
	int ipNum = host->h_length;
	for (int i = 0;i<ipNum;i++)
	{
		in_addr* addr=(in_addr*)*host->h_addr_list;
		CString ipStr;
		ipStr = inet_ntoa(addr[i]);
		m_ipAdds.push_back(ipStr);
	}

	return false;
}



void CCOCDlg::EnableControls(bool flag)
{ 
	if (!flag)
	{
		m_ipList.EnableWindow(flag);
	}else 
		m_ipList.EnableWindow(!m_bAlone);
	m_checkBox.EnableWindow(flag);
}


// 开始按键刷新
void CCOCDlg::startService(void)
{
	SetTimer(TIMER1,INTERNAL_TIME,0);
}


void CCOCDlg::stopService(void)
{
	KillTimer(TIMER1);
}



bool CCOCDlg::startServer(void)
{
	m_server.setCallBackDlg(this);
	m_server.Create(m_port,SOCK_DGRAM,63L,m_curIP);
	BOOL optBool=true;
	BOOL bb=m_server.SetSockOpt(SO_BROADCAST,(const char*)&optBool,sizeof(optBool));
	if (!bb)
	{  
		updateMessage("服务器启动失败！"); 
		m_server.Close();
		return false; 
	}else{
		updateMessage("服务器启动成功，等待连接！");
		return true;
	}

}




bool CCOCDlg::stopServer(void)
{
	m_server.ShutDown(1);
	m_server.Close();
	updateMessage("服务器关闭！");
	return true;
}


bool CCOCDlg::findCOCWindow(void)
{ 
	// Determine if a window with the class name exists...
	if (pWndPrev = CWnd::FindWindow(NULL,m_windowName))
	{

		// If iconic, restore the main window
		if (pWndPrev->IsIconic())
			pWndPrev->ShowWindow(SW_RESTORE); 
		return true;
	}
	return false;
}


bool CCOCDlg::openCOC(void)
{
	return false;
}


void CCOCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case TIMER1:
		// 向指定窗口发送消息
		// 获取指定窗口的句柄
		if(!findCOCWindow()){
			//没有获取到模拟器的窗口，自动打开模拟器
			openCOC();
		}else{ 
			if (pWndPrev!=NULL)
			{
				LPARAM lParam = MAKELPARAM(533,100);
				pWndPrev->SendMessage(WM_LBUTTONDOWN, MK_LBUTTON, lParam);
				pWndPrev->SendMessage(WM_LBUTTONUP, MK_LBUTTON, lParam);  
			}
			// 更新消息列表
			m_messageList.AddString("触发点击事件");
		}

		break;
	case TIMER2:
		{
			--m_shutDown>0?updateTime():ExitWindowsEx(EWX_POWEROFF,0);
		}
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CCOCDlg::updateMessage(CString message)
{
	m_messageList.AddString(message);
}


bool CCOCDlg::validatePassword(char* pwd)
{
	if (pwd==NULL)
	{
		return false;
	}else { 
		CString tmp(pwd);
		if (m_password.Compare(tmp)==0)
			return true;
		else
			return false;
	}
	return false;
}


//callback
void CCOCDlg::OnReceive( int nErrorCode )
{
	char strBuff[1024]={'\0'}; 
	CString tar_ip="";
	UINT tar_port=0;
	CString tar_port_sz="0";

	int res=m_server.ReceiveFrom(&strBuff,sizeof(strBuff),tar_ip,tar_port);
	if (res>0)
	{
		//处理消息
		
		string tmp = strBuff;
		tar_port_sz.Format("Data:%s  From:%s :%d",tmp.c_str(),tar_ip,tar_port);
		m_messageList.AddString(tar_port_sz);
		handleMessage(strBuff);
		int ret=m_server.SendToEx(&strBuff,sizeof(strBuff),tar_port,tar_ip);
		if (ret>0)
		{
			m_messageList.AddString("转发成功!");
		}else{
			CString tmp;
			tmp.Format("%d",m_server.GetLastError());
			m_messageList.AddString(tmp);
		}
	}
}

void CCOCDlg::OnConnect( int nErrorCode )
{
	m_messageList.AddString("OnConnect");
}

void CCOCDlg::OnOutOfBandData( int nErrorCode )
{
	m_messageList.AddString("OnOutOfBandData");
}

void CCOCDlg::OnAccept( int nErrorCode )
{
	m_messageList.AddString("OnAccept");
}

void CCOCDlg::OnSend( int nErrorCode )
{
	m_messageList.AddString("OnSend");
}

void CCOCDlg::handleMessage(char* data)
{
	// 消息的格式是 type(int)+";"+message(string)+";"+password
	int position=0;
	char tmp[1024]={'\0'};
	bool flag = findNextToken(tmp,data,position,';');;
	//type
	int type = atoi(tmp);
	string ack;
	memset(tmp,'\0',1024); 
	switch(type)
	{
	case WM_CONNECT_REQ:{
		//message
		findNextToken(tmp,data,position,';');
		if (strcmp(tmp,appName)==0)
		{
			memset(tmp,'\0',1024);
			//password
			findNextToken(tmp,data,position,';');
			CString pass1(tmp);
			if (pass1.Compare(m_password)==0)
			{ 
				//通过验证，连接成功，返回成功消息
				ack = WM_CONNECT_ACK+";";
				ack+="1;";
				ack+="验证成功！";  
				strcpy(data,ack.c_str());
				updateMessage("客户端连接成功！");
				m_wndTaskbarNotifier.Show("客户端连接成功！");

			}else{ 
				//密码验证失败，返回错误信息
				ack = WM_CONNECT_ACK+";";
				ack+="0;";
				ack+="密码错误，请重新登陆！";   
				strcpy(data,ack.c_str()); 
			}
			memset(tmp,'\0',1024);
		}
		else{
			memset(tmp,'\0',1024);
			//密码验证失败，返回错误信息
			ack = WM_CONNECT_ACK+";";
			ack+="0;";
			ack+="客户端版本错误！";   
			strcpy(data,ack.c_str());  
		} }
						break;
	case WM_START_REQ:{
		//message
		findNextToken(tmp,data,position,';');
		if (strcmp(tmp,appName)==0)
		{
			memset(tmp,'\0',1024);
			//password
			findNextToken(tmp,data,position,';');
			CString pass2(tmp);
			if (pass2.Compare(m_password)==0)
			{ 
				//通过验证，连接成功，返回成功消息
				ack = WM_START_ACK+";";
				ack+="1;";
				ack+="按键精灵正在运行中！";  
				strcpy(data,ack.c_str());  
				startService();
				m_wndTaskbarNotifier.Show("按键精灵开始运行！");

			}else{ 
				//密码验证失败，返回错误信息
				ack = WM_START_ACK+";";
				ack+="0;";
				ack+="密码错误，请重新登陆！"; 
				strcpy(data,ack.c_str());  
			}
			memset(tmp,'\0',1024);
		}
		else{
			memset(tmp,'\0',1024);
			//密码验证失败，返回错误信息
			ack = WM_START_ACK+";";
			ack+="1;";
			ack+="客户端版本错误！";   
			strcpy(data,ack.c_str());   
		} }
					  break; 
	case WM_IP_REQ:{
		//message
		findNextToken(tmp,data,position,';');
		if (strcmp(tmp,appName)==0)
		{
			memset(tmp,'\0',1024);
			//password
			findNextToken(tmp,data,position,';');
			CString pass3(tmp);
			if (pass3.Compare(m_password)==0)
			{ 
				//通过验证，连接成功，返回成功消息
				string cash=WM_IP_ACK+";1;"; 
				for (int i=0;i<m_ipAdds.size();i++)
				{
					cash.append((LPSTR)(LPCTSTR)(m_ipAdds[i]));
					if (i<m_ipAdds.size()-1)
					{
						cash.append("&");
					}

				} 
				strcpy(data,cash.c_str());
				updateMessage("客户端下载服务器IP列表");
				m_wndTaskbarNotifier.Show("客户端获取服务器IP列表！");

			}else{ 
				//密码验证失败，返回错误信息
				ack = WM_IP_ACK+";";
				ack+="0;";
				ack+="密码错误，请重新登陆！";   
				strcpy(data,ack.c_str()); 
			}
			memset(tmp,'\0',1024);
		}
		else{
			memset(tmp,'\0',1024);
			//密码验证失败，返回错误信息
			ack = WM_IP_ACK+";";
			ack+="0;";
			ack+="客户端版本错误！"; 
			strcpy(data,ack.c_str()); 
		} }
				   break; 
	case WM_TIME_REQ: {
		//message
		findNextToken(tmp,data,position,';');
		int time = atoi(tmp);
		memset(tmp,'\0',1024);
		findNextToken(tmp,data,position,';');
		CString pass4(tmp);
		if (pass4.Compare(m_password)==0)
		{

			//通过验证，设置定时关机，返回成功消息
			ack = WM_START_ACK+";";
			ack+="1;";
			ack+="定时关机设置成功！";  
			strcpy(data,ack.c_str());
			CString msg;
			msg.Format("设置定时关机：%d 秒后关机！",time);
			updateMessage(msg);
			m_wndTaskbarNotifier.Show(msg);

		}else{

			//密码验证失败，返回错误信息
			ack = WM_START_ACK+";";
			ack+="0;";
			ack+="密码错误，请重新登陆！";  
			strcpy(data,ack.c_str());   
		}
		memset(tmp,'\0',1024);}
					  break;  
	case WM_STOP_REQ:{ 
		//message
		findNextToken(tmp,data,position,';');
		if (strcmp(tmp,appName)==0)
		{
			memset(tmp,'\0',1024);
			//password
			findNextToken(tmp,data,position,';');
			CString pass5(tmp);
			if (pass5.Compare(m_password)==0)
			{ 
				//通过验证，连接成功，返回成功消息
				ack = WM_STOP_ACK+";";
				ack+="1;";
				ack+="按键精灵已停止！";
				strcpy(data,ack.c_str());
				stopService();
				m_wndTaskbarNotifier.Show("按键精灵已停止!");
			}else{ 
				//密码验证失败，返回错误信息
				ack = WM_STOP_ACK+";";
				ack+="0;";
				ack+="密码错误，请重新登陆！"; 
				strcpy(data,ack.c_str()); 
			}
			memset(tmp,'\0',1024);
		}
		else{
			memset(tmp,'\0',1024);
			//密码验证失败，返回错误信息
			ack = WM_STOP_ACK+";";
			ack+="0;";
			ack+="客户端版本错误！";  
			strcpy(data,ack.c_str());  
		} }
					 break; 
	default:
		break;
	}
}


bool CCOCDlg::findNextToken(char* des,char* data, int& posotion, char sp)
{
	if (data==NULL)
	{
		return false;
	}else if (strlen(data)<=posotion)
	{
		return false;
	}else{
		int i=0;
		int end = strlen(data); 
		for (posotion,i;posotion<end;posotion++,i++)
		{
			if (data[posotion]!=sp)
			{
				des[i] = data[posotion];
				continue;
			}else{
				posotion+=1;
				break;
			}
		}
		des[i]='\0';
		return true;
	}
}


void CCOCDlg::InitTaskbarNotifier(void)
{
	m_wndTaskbarNotifier.Create(this);
	m_wndTaskbarNotifier.SetSkin(IDB_SKIN_GUY,255,0,255);
	m_wndTaskbarNotifier.SetTextFont("Arial",110,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE | TN_TEXT_BOLD);
	m_wndTaskbarNotifier.SetTextColor(RGB(0,0,0),RGB(200,200,200));
	m_wndTaskbarNotifier.SetTextRect(CRect(25,40,m_wndTaskbarNotifier.m_nSkinWidth-30,m_wndTaskbarNotifier.m_nSkinHeight-80));
}


void CCOCDlg::setShutDownTime(int time)
{
	if (time<=0)
	{
		//取消定时关机
		//1.取消定时器
		if (m_shutTimerFlag)
		{
			m_shutTimerFlag=!KillTimer(TIMER2);
			//2.影藏task
			m_statusBar.ShowWindow(SW_HIDE);
		}
		 
	}else{
		//开启定时器
		m_shutTimerFlag = SetTimer(TIMER2,1000,0);
		m_shutDown = time;
		updateTime();
		m_statusBar.ShowWindow(SW_SHOW);
	}
}


void CCOCDlg::updateTime(void)
{
	int h = m_shutDown / 3600;
	int m = (m_shutDown-3600*h) / 60;
	int s = m_shutDown-3600*h-60*m;
	CString time;
	time.Format("%d时%d分%d秒",h,m,s); 
	m_statusBar.SetPaneText(1, time);
}
