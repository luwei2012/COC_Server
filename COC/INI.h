#pragma once

class CINI
{
public:
	CINI();
	~CINI();
public:
	void	WriteVal(LPCTSTR lpSection, LPCTSTR lpKey, const CString& outStr);
	void	WriteVal(LPCTSTR lpSection, LPCTSTR lpKey, const CString& fileName, const CString& outStr);
	void	WriteStruct(LPCTSTR lpszSection, LPCTSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct, const CString& fileName);

	BOOL	GetIntVal(LPCTSTR lpSection, LPCTSTR lpKey, int& retVal);
	BOOL	GetStrVal(LPCTSTR lpSection, LPCTSTR lpKey, CString& retStr);

	BOOL	GetIntVal(LPCTSTR lpSection, LPCTSTR lpKey, const CString& fileName, int& retVal);
	BOOL	GetStrVal(LPCTSTR lpSection, LPCTSTR lpKey, const CString& fileName, CString& retStr);
	BOOL	GetStruct(LPCTSTR lpszSection, LPCTSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct, const CString& fileName);

	CString	CreateINI(const CString& fileName);

public:
	void	SetValid(const BOOL& bValid);
	BOOL	GetValid()const;
	BOOL	IsFileExist(const CString& fileName);

private:
	BOOL	IsExist();
	BOOL	IsExistEx(LPCTSTR lpFileName);
	BOOL	IsExistEx();
	BOOL	CreateINI();
	void	Init();
private:
	CString	m_appINIPath;
	CString m_appDir;
	BOOL	m_bValid;
};