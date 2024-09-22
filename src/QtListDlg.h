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

// CQtListDlg 대화 상자

class CQtListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQtListDlg)

public:
	CQtListDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CQtListDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QTLIST_DIALOG };
#endif

protected:

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

public:
	BOOL m_bDlgShow;
	CGridCtrl m_grdQtList;

	// QT 종목 데이터 리스트
	int m_nMapQtDataNum;
	int m_nQtColCnt;
	map<CString, GV_ITEM*, less<CString>> m_mapQtData;
	void InitQtGrid();
	void CreateMapQtData();
	void UpdateGridQtData();

	//void SetSearchWord(CString strSearchWord);
	void SetMainDlg(CKwHgDlg* pMainDlg) { m_pMainDlg = pMainDlg; }


	//void Update(void);
	void InitControl();

	//afx_msg void OnBnClickedButtonSearch();
	//CEdit m_EditStockSearch;
	//CListCtrl m_ListStockSearch;
	//afx_msg void OnNMDblclkListStockSearch(NMHDR* pNMHDR, LRESULT* pResult);

private:
	CKwHgDlg* m_pMainDlg;
	CString m_szHtmlPage;

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnClose();
	afx_msg void OnBnClickedGetHtml();

	void GetTagsFromHtml(CStringArray* pstrArr, CString szHtmlPage, CString szTag, CString szAtrib, CString szAtribVal);
	int GetIfrsCountFromHtml(CString szHtmlPage, CString szTag, CString szAtrib, CString szAtribVal);

	long GetTableRowColValSum(int nLimitCnt, CString szHtmlPage, CString szTag, CString szAtrib, CString szAtribVal);

	afx_msg void OnBnClickedGetDart();

	void GetFileList(CString strFolder);
	void parse(CString filepath, CString& strFileContents);

	bool IsUTF8(const void* pBuffer, long size);

	void SaveDartFiData(CString strTableName, CString fullData);
	void MultipleInsert(char* tmpchQry);

	CListBox m_lstFiList;
	afx_msg void OnBnClickedGetDart2();
	afx_msg void OnBnClickedQntQltCompt();

	void UpdateQuantQlt();
	void UpdateQuantMmt();
	afx_msg void OnBnClickedQntMmtCompt();

	void ReqKwDataByStkCd(CString strScrNo, CString strStkCd);
	afx_msg void OnBnClickedQntValCompt();
	afx_msg void OnBnClickedQntTotCompt();
};