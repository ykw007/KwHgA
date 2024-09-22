
#include "stdafx.h"
#include "KwHg.h"
#include "KwHgDlg.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
	: m_pDlg(NULL)
{
	m_pDlg = NULL;
}

CClientSocket::~CClientSocket()
{
	m_pDlg = NULL;
}


void CClientSocket::OnClose(int nErrorCode)
{
	if (nErrorCode == 0)
		m_pDlg->OnClose();
	//CAsyncSocket::OnClose(nErrorCode);
}


void CClientSocket::OnConnect(int nErrorCode)
{
	if (nErrorCode == 0)
		m_pDlg->OnConnect();

	//CAsyncSocket::OnConnect(nErrorCode);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	if (nErrorCode == 0)
		m_pDlg->OnReceive();
	//CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::SetParent(CKwHgDlg* pDlg)
{
	m_pDlg = pDlg;
}


void CClientSocket::OnClose()
{
}


void CClientSocket::OnConnect()
{
}


void CClientSocket::OnReceive()
{
}
