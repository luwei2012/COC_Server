/*
*MainDoc.h
*
*2011-08
*
*
*/
#ifndef _MAINDOC_H_
#define _MAINDOC_H_

#include <afxtempl.h>
#include "Type.h"
#include "SkinPPWTL.h" 
#include "INI.h" 

class CMainDoc
{
public:
	CMainDoc();
	~CMainDoc();
	 
	 
public:
	void				ReadINIInfo();
	void				WriteINIInfo();


public:
	INI					m_INI;
	CINI*				m_pINI;

public:
	//≥ı ºªØ
	void				Init();
	void				UnInit();
 
    CString			m_host;
};




#endif