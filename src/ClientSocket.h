#pragma once

class CKwHgDlg;

// CClientSocket

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//void SetParent();
	void SetParent(CKwHgDlg* pDlg);
private:
	CKwHgDlg* m_pDlg;
public:
	//CClientSocket m_sConnectSocket;
	void OnClose();
	void OnConnect();
	void OnReceive();
};


