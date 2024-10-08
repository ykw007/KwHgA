#pragma once

#include "afxdtctl.h"
#include "afxcmn.h"
#include "afxwin.h"

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
using namespace std;

class CKwHgDlg;

// CLogDlg 대화 상자

class CLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLogDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOG_DIALOG };
#endif

	// Attributes
private:
	CKwHgDlg* m_pMainDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	DECLARE_MESSAGE_MAP()


public:
	CListBox m_lbLog;
	BOOL m_bDlgShow;
	CFont m_Font;
	CFont m_FontStatic;

	afx_msg void OnDestroy();


public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();

public:

	void SetMainDlg(CKwHgDlg* pMainDlg) { m_pMainDlg = pMainDlg; }
	void LogMessage(CString strLog);
};
