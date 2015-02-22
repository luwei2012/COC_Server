#pragma once

// CServer ÃüÁîÄ¿±ê

class CCOCDlg;

class CServer : private CAsyncSocket
{
private:
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


coc pc=private server=99999999999999999999999999999999999999999999999999999999 gems
