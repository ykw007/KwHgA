// CClockDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "KwHg.h"
#include "LogDlg.h"
#include "afxdialogex.h"
#include <ATLComTime.h>

#include "../include/MessageDef.h"
#include "KwHgDlg.h"

#include<iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogDlg dialog

IMPLEMENT_DYNAMIC(CLogDlg, CDialogEx)

CLogDlg::CLogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOG_DIALOG, pParent)
{
		m_pMainDlg = NULL;
		m_bDlgShow = false;
}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TIME, m_Time);
	DDX_Control(pDX, IDC_LIST_LOG, m_lbLog);

}

BEGIN_MESSAGE_MAP(CLogDlg, CDialogEx)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CClockDlg message handlers

BOOL CLogDlg::OnInitDialog()
{
	//DWORD	dwStyle;

	CDialog::OnInitDialog();


	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CLogDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	if (m_bDlgShow)
		lpwndpos->flags |= SWP_SHOWWINDOW;
	else
		lpwndpos->flags &= ~SWP_SHOWWINDOW;

	CDialogEx::OnWindowPosChanging(lpwndpos);
}


void CLogDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}


BOOL CLogDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


// 닫기 버튼 클릭시
void CLogDlg::OnClose()
{
	m_pMainDlg->OnBnClickedBtnLog();

	CDialogEx::OnClose();
}


void CLogDlg::LogMessage(CString strLog)
{
	//m_lbLog.InsertString(0, strLog);
	m_lbLog.AddString(strLog);

	m_lbLog.SetTopIndex(m_lbLog.GetCount() - 1);
}