
// COC.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "SkinPPWTL.h" 
#include "Global.h"
// CCOCApp:
// 有关此类的实现，请参阅 COC.cpp
//
class CMainDoc;

class CCOCApp : public CWinApp
{
public:
	CCOCApp();

	CMainDoc*				m_pMainDoc;

// 重写
public:
	virtual BOOL InitInstance();

// 实现
private: 
	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CCOCApp theApp;