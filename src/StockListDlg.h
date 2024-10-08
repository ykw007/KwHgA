#if !defined(AFX_TESTCOMBOVIEW_H__939B886D_3068_11E0_8FFC_0050BF29759A__INCLUDED_)
#define AFX_TESTCOMBOVIEW_H__939B886D_3068_11E0_8FFC_0050BF29759A__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKwHgDlg;

// CStockListDlg 대화 상자

class CStockListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStockListDlg)

public:
	CStockListDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CStockListDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STOCKLIST_DIALOG };
#endif

protected:

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

public:

	//int m_nNum;

	void SetSearchWord(CString strSearchWord);
	void SetMainDlg(CKwHgDlg* pMainDlg) { m_pMainDlg = pMainDlg; }


	void Update(void);
	void InitControl();

	afx_msg void OnBnClickedButtonSearch();
	CEdit m_EditStockSearch;
	CListCtrl m_ListStockSearch;
	afx_msg void OnNMDblclkListStockSearch(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CKwHgDlg* m_pMainDlg;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnClose();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCOMBOVIEW_H__939B886D_3068_11E0_8FFC_0050BF29759A__INCLUDED_)
