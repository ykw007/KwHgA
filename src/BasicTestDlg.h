#pragma once
#include "afxwin.h"


class CYOADLLClientDlg;

// CBasicTestDlg ��ȭ �����Դϴ�.

class CBasicTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBasicTestDlg)

public:
	CBasicTestDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBasicTestDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BASICTEST_DIALOG };

// Attributes
private:
	CYOADLLClientDlg* m_pMainDlg;
	int	m_nReqID_300001;
	int	m_nReqID_160001;

// Operations
public:
	void SetMainDlg( CYOADLLClientDlg* pMainDlg ) { m_pMainDlg = pMainDlg; }
	void LogMessage( CString strMsg );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonAutoRegist();
	afx_msg void OnBnClickedButtonAutoUnRegist();
	LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveRealData(WPARAM wParam, LPARAM lParam);
public:
	CString m_strJongCode;
	CListBox m_lbLog;
};
