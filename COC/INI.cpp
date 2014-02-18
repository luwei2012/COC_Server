#include "stdafx.h"
#include "INI.h"
#include "resource.h"

CINI::CINI():m_bValid(FALSE)
{
	//初始化
	Init();
}
CINI::~CINI()
{
}
void
CINI::SetValid(const BOOL& bValid)
{
	m_bValid = bValid;
}
BOOL
CINI::GetValid()const
{
	return m_bValid;
}

void
CINI::Init()
{
	//获取默认的程序配置文件全路径
	char path[MAX_PATH];
	GetModuleFileName(NULL,path,MAX_PATH);
	ASSERT( strlen(path)>0 );
	m_appINIPath.Format("%s",path);
	int len = m_appINIPath.ReverseFind('\\') + 1;
	m_appINIPath = m_appINIPath.Left(len);
	m_appDir	 = m_appINIPath;
	m_appINIPath = m_appINIPath + _T("CC.ini");

	//检测程序配置文件的存在性
	if ( IsExist() == FALSE )
	{
		if ( CreateINI() == TRUE ){
				SetValid(FALSE);
			}
 		else
 		{
 			AfxMessageBox(IDS_CONFIG_CHECK);
 			exit(0);
 		}
	}
	else
	{
		SetValid(TRUE);
	}
}
BOOL
CINI::CreateINI()
{
	TRY
	{
		CFile f(m_appINIPath, CFile::modeCreate);
		return TRUE;;
	}
	CATCH(CFileException, e)
	{
		return FALSE;
	}
	END_CATCH
}
CString
CINI::CreateINI(const CString& fileName)
{
	
	TRY
	{
		CString fullName(m_appDir);
		fullName = fullName + fileName;
		fullName = fullName + _T(".cc");

		CFile f(fullName, CFile::modeCreate);
		return fullName;;
	}
	CATCH(CFileException, e)
	{
		return _T("");
	}
	END_CATCH
}
BOOL	
CINI::IsFileExist(const CString& fileName)
{
	TRY
	{
		CFile f((LPCTSTR)fileName,CFile::modeRead);
		return TRUE;;
	}
	CATCH(CFileException, e)
	{
		return FALSE;
	}
	END_CATCH
}
BOOL
CINI::IsExistEx()
{
	TRY
	{
		CFile f(m_appINIPath,CFile::modeRead);
		return TRUE;;
	}
	CATCH(CFileException, e)
	{
		return FALSE;
	}
	END_CATCH
}
BOOL
CINI::IsExistEx(LPCTSTR lpFileName)
{
	TRY
	{
		CFile f(lpFileName,CFile::modeRead);
		return TRUE;;
	}
	CATCH(CFileException, e)
	{
		return FALSE;
	}
	END_CATCH
}
BOOL
CINI::IsExist()
{
	TRY
	{
		CFile f(m_appINIPath,CFile::modeRead);
		return TRUE;;
	}
	CATCH(CFileException, e)
	{
		return FALSE;
	}
	END_CATCH
}
void
CINI::WriteVal(LPCTSTR lpSection, LPCTSTR lpKey, const CString& outStr)
{
	//检测文件存在性
	if ( IsExistEx() == FALSE )return;
	//写入串值
	WritePrivateProfileString(lpSection, lpKey, outStr, (LPCTSTR)m_appINIPath);
}
void
CINI::WriteVal(LPCTSTR lpSection, LPCTSTR lpKey, const CString& fileName, const CString& outStr)
{
	//检测文件存在性
	if ( IsExistEx((LPCTSTR)fileName) == FALSE )return;
	//写入串值
	WritePrivateProfileString(lpSection, lpKey, outStr, (LPCTSTR)fileName);
}

void
CINI::WriteStruct(LPCTSTR lpszSection, LPCTSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct, const CString& fileName)
{
	//检测文件存在性
	if ( IsExistEx((LPCTSTR)fileName) == FALSE )return;
	//写入串值
	WritePrivateProfileStruct(lpszSection, lpszKey, lpStruct, uSizeStruct, (LPCTSTR)fileName);
}

BOOL
CINI::GetStruct(LPCTSTR lpszSection, LPCTSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct, const CString& fileName)
{
	//检测文件存在性
	if ( IsExistEx() == FALSE )return FALSE;
	//读出结构体
	if ( GetPrivateProfileStruct(lpszSection, lpszKey, lpStruct, uSizeStruct, (LPCTSTR)fileName) )return TRUE;
	else return FALSE;
}
BOOL
CINI::GetIntVal(LPCTSTR lpSection, LPCTSTR lpKey, int &retVal)
{
	//检测文件存在性
	if ( IsExistEx() == FALSE )return FALSE;
	//读出键值
	retVal = GetPrivateProfileInt(lpSection, lpKey, -1, (LPCTSTR)m_appINIPath);
	if (retVal == -1) return FALSE;
	else return TRUE;
}

BOOL
CINI::GetStrVal(LPCTSTR lpSection, LPCTSTR lpKey, CString& retStr)
{
	//检测文件存在性
	if ( IsExistEx() == FALSE )return FALSE;
	//读出串值
	char buf[MAX_PATH];
	GetPrivateProfileString(lpSection, lpKey, "NULL", buf, MAX_PATH, (LPCTSTR)m_appINIPath);
	retStr.Format("%s", buf);
	if (retStr == _T("NULL")) return FALSE;
	else return TRUE;
}

BOOL
CINI::GetIntVal(LPCTSTR lpSection, LPCTSTR lpKey, const CString& fileName, int& retVal)
{
	//检测文件存在性
	if ( IsExistEx((LPCTSTR)fileName) == FALSE )return FALSE;
	//读出键值
	retVal = GetPrivateProfileInt(lpSection, lpKey, -1, (LPCTSTR)fileName);
	if (retVal == -1) return FALSE;
	else return TRUE;
}
BOOL
CINI::GetStrVal(LPCTSTR lpSection, LPCTSTR lpKey, const CString& fileName, CString& retStr)
{
	//检测文件存在性
	if ( IsExistEx((LPCTSTR)fileName) == FALSE )return FALSE;
	//读出串值
	char buf[MAX_PATH];
	GetPrivateProfileString(lpSection, lpKey, "NULL", buf, MAX_PATH, (LPCTSTR)fileName);
	retStr.Format("%s", buf);
	if (retStr == _T("NULL")) return FALSE;
	else return TRUE;
}