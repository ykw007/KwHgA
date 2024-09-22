#pragma once

#include "afxdtctl.h"
#include "afxcmn.h"
#include "afxwin.h"

#include <my_global.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")

#include "GridCtrl.h"
#include "ChartViewer.h"

#include "DlgStkinfo1.h"
#include "DlgStkinfo2.h"
#include "DlgStkinfo3.h"
#include "DlgStkinfo4.h"

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
using namespace std;

class CKwHgDlg;
class FinanceChart;

// CStkInfoDlg 대화 상자

class CStkInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStkInfoDlg)

private:
	CKwHgDlg* m_pMainDlg;

public:
	CStkInfoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CStkInfoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STKINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	DECLARE_MESSAGE_MAP()

public:
	CString m_strScrNo;
	BOOL m_bDlgShow;

	CString m_strStkCd;
	CString m_strStkNm;

	CDlgStkinfo1* m_pDlgStkinfo1;
	CDlgStkinfo2* m_pDlgStkinfo2;
	CDlgStkinfo3* m_pDlgStkinfo3;
	CDlgStkinfo4* m_pDlgStkinfo4;

	afx_msg void OnDestroy();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();


public:

	void SetMainDlg(CKwHgDlg* pMainDlg) { m_pMainDlg = pMainDlg; }

	void InitControl(CString strStkCd, CString strStkNm);

	CGridCtrl	m_grdJongInfo1;		// 종목정보1 그리드
	void InitJongInfo1Grid();

	void SetTrData(CKwHgApp& theApp, CString strScrNo, CString sTrcode, CString strRQName);

	int m_nDisplayCandleNum;
	CChartViewer m_ChartViewer;
	void ShowChart(CString strStkCd);
	FinanceChart* m_fc;
	//void drawChart(CChartViewer* viewer);
	void DrawChart(CChartViewer* viewer, int nCandleNum, double* dDate, double* dHp, double* dLp, double* dOp, double* dCp, double* dVol, CString strStkCd);
	afx_msg void OnBnClickedButtonMa5();
	afx_msg void OnBnClickedButtonMa10();
	afx_msg void OnBnClickedButtonMa20();
	afx_msg void OnBnClickedButtonMa60();
	afx_msg void OnBnClickedButtonMa120();
	afx_msg void OnBnClickedButtonMa240();
	afx_msg void OnBnClickedButtonMa480();
	void ShowChartByMa(int nMaVal);


	CTabCtrl m_tabStkinfo;
	afx_msg void OnSelchangeTabStkinfo(NMHDR* pNMHDR, LRESULT* pResult);


	afx_msg void OnBnClickedCancel();
};
