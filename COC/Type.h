/*
*Type.h
*
*2011-08
*
*
*/
#ifndef _TYPE_H_
#define _TYPE_H_

    
typedef struct tagINIFile
{
	BOOL	m_autoStart;		//开机自启动 
	BOOL	m_popUp;			//弹出动画 
	CString m_usrINIPath;		//用户配置文件路径 
	int		m_AutoType;			//自动连接设置
	CString m_skinPath;
}INI;
 

typedef int (__stdcall *InstallHook)(HWND vRecieveWindow);
typedef BOOL (*UnHook)(); 




#endif