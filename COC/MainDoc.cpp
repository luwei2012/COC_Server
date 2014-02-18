/*
*MainDoc.cpp
*
*2011-08
*
*
*/

#include "stdafx.h"
#include "Global.h"
/*
*although i don't  use marco in resource.h file, if i don't include this file,
*complier would remind of error.
*/
#include "resource.h"	
#include "MainDoc.h" 
#include "INI.h"

CMainDoc::CMainDoc()
{ 
	m_pINI = new CINI();
	ASSERT( m_pINI != NULL ); 
	m_host="";
	Init();
	 
}

CMainDoc::~CMainDoc()
{
	UnInit(); 
}

void
CMainDoc::Init()
{  
	
	//初始化程序配置信息
	m_INI.m_autoStart=0;  
	m_INI.m_popUp=0;
	m_INI.m_AutoType=0;
	m_INI.m_skinPath=_T("");
	m_INI.m_usrINIPath=_T("");
	if ( m_pINI->GetValid() == TRUE){
		ReadINIInfo();
	} 
}
void
CMainDoc::UnInit()
{
	//写文件保存
	WriteINIInfo(); 
}
void
CMainDoc::ReadINIInfo()
{
	 
	int inVal;
	CString inStr;
	//获取用户配置文件路径
	if (m_pINI->GetStrVal(appName, g_INI[INI_USR_PATH], inStr) == TRUE){
			m_INI.m_usrINIPath = inStr;
	}
	else{
		m_INI.m_usrINIPath = _T("");
	}
// ///////////////////////////////////////////////////////////
	//modify by luwei
	if (m_INI.m_usrINIPath == _T(""))
	{
		m_pINI->SetValid(FALSE);
		return;
	}

	if (m_pINI->IsFileExist(m_INI.m_usrINIPath) == FALSE)
	{
		m_INI.m_usrINIPath = _T("");
		m_pINI->SetValid(FALSE);
		return;
	}

	//在用户配置文件下获取数据
	m_pINI->SetValid(TRUE);

	//获取开机自启动信息
	if (m_pINI->GetIntVal(appName, g_INI[INI_AUTO_START], m_INI.m_usrINIPath, inVal) == TRUE){
			m_INI.m_autoStart = inVal;
	}
	else{
		m_INI.m_autoStart = FALSE;
	}
	
	//获取是否弹出动画提示信息
	if (m_pINI->GetIntVal(appName, g_INI[INI_POP_UP_NOTIFY], m_INI.m_usrINIPath , inVal) == TRUE){
		m_INI.m_popUp = inVal;
	}
	else{
		m_INI.m_popUp = FALSE;
	}
	 
	 
	//////////////////////////////////////////////////////////////////////////////////////
	//add by luwei
	//获取自动连接设置信息
	if (m_pINI->GetIntVal(appName, g_INI[INI_AUTO_TYPE], m_INI.m_usrINIPath , inVal) == TRUE){
		m_INI.m_AutoType = inVal;
	}
	else{
		m_INI.m_AutoType = 0;
	}

	//获取皮肤设置信息
	if (m_pINI->GetStrVal(appName, g_INI[INI_SKIN_PATH], m_INI.m_usrINIPath , inStr) == TRUE){
		m_INI.m_skinPath = inStr;
	}
	else{
		m_INI.m_skinPath = _T("");
	}
	 
}


void
CMainDoc::WriteINIInfo()
{
	 
	if ( m_INI.m_usrINIPath == _T("") )
	{
		if (MessageBox(NULL,IDS_CONFIG_MISSING, NULL, MB_OKCANCEL) == IDOK){
			m_INI.m_usrINIPath = m_pINI->CreateINI(m_host);
			m_pINI->WriteVal(appName, g_INI[INI_USR_PATH],m_INI.m_usrINIPath);
		}
		else{
			AfxMessageBox(IDS_SAVE_FAILED);
			return;
		}
	}
	if (m_pINI->IsFileExist(m_INI.m_usrINIPath) == FALSE)
	{
		AfxMessageBox(IDS_SAVE_FAILED);
		return;
	}
	//写入用户配置文件路径信息
	m_pINI->WriteVal(appName, g_INI[INI_USR_PATH], m_INI.m_usrINIPath);
	//写入开机启动信息
	switch(m_INI.m_autoStart)
	{
	case TRUE:
		m_pINI->WriteVal(appName, g_INI[INI_AUTO_START], m_INI.m_usrINIPath, _T("1"));
		break;
	
	case FALSE:
		m_pINI->WriteVal(appName, g_INI[INI_AUTO_START], m_INI.m_usrINIPath, _T("0"));
		break;

	default:
		break;
	}
	//写入是否弹出动画提示信息
	switch(m_INI.m_popUp)
	{
	case TRUE:
		m_pINI->WriteVal(appName, g_INI[INI_POP_UP_NOTIFY], m_INI.m_usrINIPath, _T("1"));
		break;

	case FALSE:
		m_pINI->WriteVal(appName, g_INI[INI_POP_UP_NOTIFY], m_INI.m_usrINIPath, _T("0"));
		break;

	default:
		break;
	}
	 
	/////////////////////////////////////////////////////////////////////////////////
	//add by luwei
	//写入自动连接设置
	switch(m_INI.m_AutoType)
	{
	case 0:
		m_pINI->WriteVal(appName, g_INI[INI_AUTO_TYPE], m_INI.m_usrINIPath, _T("0"));
		break;
		
	case 1:
		m_pINI->WriteVal(appName, g_INI[INI_AUTO_TYPE], m_INI.m_usrINIPath, _T("1"));
		break;
	 
	default:
		break;
	}

	//写入皮肤文件路径
	m_pINI->WriteVal(appName, g_INI[INI_SKIN_PATH],m_INI.m_skinPath);
	m_pINI->WriteVal(appName, g_INI[INI_SKIN_PATH], m_INI.m_usrINIPath,(LPSTR)(LPCTSTR)m_INI.m_skinPath);
	 
}
 