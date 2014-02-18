#pragma once

// CServer ÃüÁîÄ¿±ê

class CCOCDlg;

class CServer : public CAsyncSocket
{
public:
	CServer(CCOCDlg* pwnd=NULL);
	virtual ~CServer();
	CCOCDlg* m_pWnd;
	virtual void OnAccept(int nErrorCode); 
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	
	void setCallBackDlg(CCOCDlg* callBackDlg);
	virtual void OnOutOfBandData(int nErrorCode);
};


