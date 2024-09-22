
// KwHgDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include <my_global.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")

#include <iostream>
#include <utility>
#include <map>
#include <string>
using namespace std;

#include "GridCtrl.h"
#include "ChartViewer.h"

#include "TTFNameLibrary/TTF.h"

#include "ClientSocket.h"

class CLogDlg;
class CStockListDlg;
class FinanceChart;
class CSplashScreenEx;
class CQtListDlg;
class CCondSrchDlg;
class CStkInfoDlg;

typedef struct _CHART_ITEM {
	double* dDate;
	double* dOp;
	double* dCp;
	double* dHp;
	double* dLp;
	double* dVol;
	double* dMa5;
	double* dMa120;
	double* dMa240;
	double dMa5Sum;
	double dMa10Sum;
	double dMa13Sum;
	double dMa20Sum;
	double dMa60Sum;
	double dMa120Sum;
	double dMa240Sum;
	int* pnCheMin;	// ü�� �ð�(��)
	int nCandleNum;
} CHART_ITEM;

typedef struct _STK_REG_INFO {
	CString strKey;
	CString strScrNo;
} STK_REG_INFO;

// CKwHgDlg ��ȭ ����
class CKwHgDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CKwHgDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_KWHG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

private:
	//CMap<int, int, CString, CString>	m_mapReqID;


	//CChildDlg* m_pDlg;
	CSplashScreenEx* m_pSplash;
public:
	// ����˻� â
	CStockListDlg* m_pStockListDlg;

	// �α� â
	CLogDlg* m_pLogDlg;
	BOOL	m_bLogShowYn;

	// ��Ʈ ������
	CQtListDlg* m_pQtListDlg;
	BOOL	m_bQtDlgShowYn;

	// ���ǰ˻� â
	CCondSrchDlg* m_pCondSrchDlg;
	BOOL	m_bCondSrchDlgShowYn;

	// �������ȸ â
	CStkInfoDlg* m_pStkInfoDlg;
	BOOL	m_bStkInfoDlgShowYn;

public:
	void LogMessage(CString strMsg, int nType = 0, BOOL bTimeStamp = TRUE);
	int write_log_file(CString str);
	CString GetProgPath();

	CString AccountFormat( TCHAR* pData );
	CString Commify( TCHAR* pData );
	CString Commify( long nData );
	CString Commify( double dData );

	void Wait(DWORD dwMillisecond);

	void SetOdPosAmt(double odPosAmt);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
// �����Դϴ�.
protected:
	HICON m_hIcon;

	HICON m_hIconConnected;
	HICON m_hIconClosed;

	// ������ �޽��� �� �Լ�

	virtual void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	BOOL ShowWindowEx(int nCmdShow);

	bool m_bShowStatus;
	//static BOOL CALLBACK GridCallback(GV_DISPINFO* pDispInfo, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	void OnEventConnect(LONG nItemCnt);
	DECLARE_EVENTSINK_MAP()

public:	
	CString m_strToday;			// �ŷ�����(����) yyyymmdd
	int m_nJangStart;
	int m_nCloseJangFlag;

	int m_nCloseIcs900;

	BOOL m_bRtStart;

	int m_iOdPosNum;		// �ֹ������� �ż�������
	int m_iOdPosAmt;

	CFont m_Font;
	CFont m_FontStatic;
	CString m_stTime;
	CIsiLcdDisplay m_CIsiLcdSample10;


	CComboBox m_cbAcc;
	CMapStringToString m_mapAccount;
	CString m_strAccount;
	CString m_strAcctPassword;
	CEdit m_edJumunPossAmt;	// �ֹ����ɱݾ�
	int m_iOdPosAmtTot; // �ֹ����ɱݾ�

	//CString m_sTgtStkCd;
	BOOL m_nContiFlag;
	BOOL m_nOrderTimeOutFlag;
	BOOL m_nBsFlag;

	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex);
	void OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext);
	void OnReceiveConditionVer(long lRet, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);

	void GetStockList();	// ��ü ���� ������Ʈ


	//afx_msg void OnCbnSelchangeComboAcc();
	afx_msg void OnSelectMyAccount();

	BOOL m_bPgStart;

	void InitControl();
	void InitAccount();
	void AddAccount(TCHAR* strAccount, TCHAR* strAcctName);
	void GetAccounts();

	map<int, CString> m_mapRtScrNo;
	void ReqGetConditionLoad(); // ���ǰ˻��� �ҷ�����
	void ReqSendCondition(int nCsId, CString strCsNm, int nRtmAt);  // ���ǰ˻��� ���� ��������
	void ReqSendConditionStop(int nCsId, CString strCsNm); //�ǽð� ���� �˻� ����
	void SaveKwCondSrch();
	// ���ǰ˻� �������Լ�
	void RegTrStkByCondSch(CString strCsId, CString strStkCd, CString strStkNm, CString strStkGb, BOOL bRtAt, CString strExtraParam1, CString strExtraParam2);
	void StartRtCondSch(); // �ǽð� ���� �˻� ����
	CString m_strRtScrNo;

	CString m_strScrNo;

	int m_nInit;

	CEdit m_edStockSearch;
	CListCtrl m_listStock;
	afx_msg void OnBnClickedButtonStkSearch();


	//=================================================
	// ���� ��� �Լ�
	void RegTrStk(CString strStkCd, CString strStkNm, CString strStkGb);
	void RegTrExStk(CString strStkCd, CString strStkNm, CString strStkGb);

	CStringArray m_strArrRegStkCds;
	CStringArray m_strArrRegStkNms;
	CStringArray m_strArrRegStkGbs;
	BOOL m_bRegExStk;
	int m_nArrRegIdx;

	afx_msg void OnBnClickedButtonGetStock();

	// �ǽð� 
	CStringArray m_strArrRealRegStkInfos;


	BOOL m_bGrdListLoadAll;		// ��� ���� ��� �ε��Ͽ�����
	BOOL m_bGrdExListLoadAll;		// ���� ���� ��� �ε��Ͽ�����
	map<CString, STK_REG_INFO*> m_mapStkRegInfo;

	STK_REG_INFO* GetStkRegInfo(CString strStkCd);

	//int m_nTgBuyCnt;  // ��� ���� �ֹ� ��û �Ǽ�
	int GetBuyOrdReqCount();


	// �Ÿ� ��� ��� ���� ����Ʈ
	int m_nMapDataNum;
	CGridCtrl m_grdList;
	int m_nColCnt;
	map<CString, GV_ITEM*, greater<CString>> m_mapData;
	void InitGrid();
	void CreateMapData(CString strRegId = _T(""), CString strStkCd = _T(""));
	void UpdateGridData();

	// �Ÿ� ���� ���� ����Ʈ
	int m_nMapExDataNum;
	CGridCtrl m_grdExList;
	int m_nExColCnt;
	map<CString, GV_ITEM*, greater<CString>> m_mapExData;
	void InitExGrid();
	void CreateMapExData(CString strRegId = _T(""), CString strStkCd = _T(""));
	void UpdateGridExData();

	// �Ÿ� ���� ����Ʈ
	int m_nMapPlDataNum;
	CGridCtrl m_grdPlList;
	int m_nPlColCnt;
	int m_nEdPlTdSum;
	int m_nEdPlSum;

	map<CString, GV_ITEM*, greater<CString>> m_mapPlData;
	void InitPlGrid();
	void CreateMapPlData();
	void UpdateGridPlData();

	// ���� �ż� ��Ȳ
	CGridCtrl m_grdDvList;
	int m_nDvColCnt;
	double m_dEdDvSum;
	map<CString, GV_ITEM*, less<CString>> m_mapDvData;
	void InitDvGrid();
	void CreateMapDvData(CString strRegId = _T(""), CString strStkCd = _T(""));
	void UpdateGridDvData();
	void InsertDvData(CString strScrNo, CString strRegId, CString strStkCd);

	void InsertExDvData(CString strScrNo, CString strRegId, CString strStkCd);

	// �ǽð� �ż� �ŵ� ��ü�� ��Ȳ ǥ��
	CGridCtrl m_grdTrList;
	int m_nTrColCnt;
	map<CString, GV_ITEM*, greater<CString>> m_mapTrData;
	void InitTrGrid();
	void CreateMapTrData();
	void UpdateGridTrData();

	void UpdateListNum(int nListType); // �� ���� ���� ������Ʈ

	void ReqKwDataByStkCd(CString strScrNo, CString strStkCd);// ���� Ű�� ���ں� ���� ������ ��û
	void ReqKwDataForDetailStkInfo(CString strScrNo, CString strStkCd);

	void ReqOpt20006(CString strStkCd); // �������� �Ϻ� ��ȸ ��û
	void ReqOpt10081(CString strScrNo, CString strStkCd); // �ֽ��Ϻ���Ʈ��ȸ��û
	void ReqOpt10080_ICS900(CString strScrNo, CString strStkCd); // �ֽĺк���Ʈ��ȸ��û ics900
	void ReqOpt10080(CString strScrNo, CString strStkCd); // �ֽĺк���Ʈ��ȸ��û 

	double m_dKs9Sum;
	double m_dKq9Sum;
	double m_dCurKsp;
	double m_dCurKqp;
	BOOL m_bWarnKsMkt;
	BOOL m_bWarnKqMkt;

	void SetGridRowColor(CGridCtrl& grdList, int row, COLORREF clr);

	map<CString, CHART_ITEM*> m_mapChart;	// ��Ʈ ������ MAP

	void CheckJangStart();

	CString m_strSrv;	// ���Ǽ���/�ǽð�����

	double m_dFeeRate;	// ��������

	CString m_strSelKey;
	CString m_strSelStkCd;
	CString m_strOldSelStkCd;

	CString m_strBuyCncTrKey;	// �ż��ֹ���� Ű
	CString m_strSellCncTrKey;	// �ŵ��ֹ���� Ű

	BOOL m_bChkHtsList;
	void ReqAccntStkList();	// �������ܰ�����û

	//void OnGridBeginDrag(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);
	void OnGridStartSelChange(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);
	void OnGridEndSelChange(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);
	void OnGridExStartSelChange(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);
	void OnGridExEndSelChange(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);
	void OnGridStartEdit(NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnGridExStartEdit(NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnGridExEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult);

	void OnGridDvStartEdit(NMHDR* pNotifyStruct, LRESULT* pResult);
	void OnGridDvEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult);

	afx_msg void OnGridClick(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);
	afx_msg void OnGridExClick(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);
	//afx_msg void OnGridDvClick(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);
	afx_msg void OnGridTrClick(NMHDR* pNotifyStruct, LRESULT* /*pResult*/);

	void SelectGridCell(int nGridNo, CString strRegDt, CString strStkCd, int nRow, int nCol);
	void CheckGridCell(int nGridNo, CString strRegDt, CString strStkCd, int nRow, int nCol);
	void UpdateGridCellData(int nGridNo, CString strRegDt, CString strStkCd, int nRow, int nCol, CString strUpdateVal);

	int GetNotDelDvBno(CString strRegDt, CString strStkCd); // �������� ������ ���� �Ұ� ���� ��ȸ

	void UpdateGwgeVal(int nGridNo, int nCol, CString strRegDt, CString strStkCd, CString strVal);

	void OrderSellGridRow(CString strRegDt, CString strStkCd, GV_ITEM* pItem);	// ���� �ŵ�
	void DeleteGridRow(CString strRegDt, CString strStkCd);	// ����

	void DeleteExGridRow(CString strRegDt, CString strStkCd);

	void UpdateGridCellDvData(CString strRegDt, CString strStkCd, CString strBno, int nRow, int nCol, CString strUpdateVal);
	void UpdateDvBcndv(CString strRegDt, CString strStkCd, CString strBno, CString strUpdateVal, GV_ITEM* pDvItem);	// ���� �ż����ǰ� ����
	void UpdateDvBamt(CString strRegDt, CString strStkCd, CString strBno, CString strUpdateVal, GV_ITEM* pDvItem);	// ���� �ż��ݾ�/�ֽļ� ����

	void ProcRealData(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void ProcViRealData(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);

	void TradeByCond(CString strScrNo, CString strKey, int nOp, int nCp, int nCurQty, int nMc, GV_ITEM* pItem, int nChetime);
	void Order(int nGb, CString strKey, long nPrice, long nQty, CString strOrgOrdNo = _T(""));
	//void CancelOrder(int nGb, CString strTrKey);

	void InsertOrder(CString strKey, int nOrdGb);
	void UpdateOrder(CString strOrdState, CString strStkCd, CString strOrdNo, int nBuysellType, CString strBno
		, CString strOrdPrice, int nOrdQty, int nNotConQty, CString strOrdTime);

	void UpdateCancelOrder(CString strOrdState, CString strStkCd, CString strOrgOrdNo, int nBuysellType);

	void CancelOrderByTimeOut(); // �ֹ���ȣ ���� ��� �ð��� ���� �ֹ���û flag ���� -> BFL 1 �� ���õǾ� ������ �ֹ���û�� �ȵ�
	void CancelOrderByTimeOut2();

	void ReqOpt10170(); // ���ϸŸ�������û 
	void ReqOpt10075(); // ��ü���û
	void ReqOpt10085(); // ���¼��ͷ���û

	void ReqOpt10001(CString strScrNo, CString strStkCd); // opt10001 : �ֽı⺻������û
	void ReqOpt10045(CString strScrNo, CString strStkCd); // opt10045 : ���񺰱���Ÿ����̿�û
	void ReqOpt10054(CString strScrNo); // opt10054 : ���񺰱���Ÿ����̿�û

	GV_ITEM* GetMapItemByStkCd(CString strStkCd);

	int GetHogaUnit(int nPrice);

	void UpdateBuyLmtAt(BOOL bVal);
	void UpdateMktAt(BOOL bVal);
	void UpdateColfstddyAt(BOOL bVal);

	void DeleteTgListAll(); // ������� ��� ����

	int CompareDoubleAbsoulteAndUlps(double x,
		double y,
		double absTolerance = (1.0e-8),
		int ulpsTolerance = 4);

	//BOOL IsStkTradeUntilToday(CString strStkCd); // ���ϱ��� �ŷ��ߴ� �����̾����� ����
	CString GetViStartTime(CString strViStartTime);

	void ReqUpdateViStdPrice(CString strStkCd); // ics900 vi ���ذ��� ������Ʈ ��û
	void ReqUpdateViStdPriceByCurTime(CString strCurTime); // ics900 vi ���ذ��� ������Ʈ ��û 15�ʸ���
	void ReqUpdateViStdPrice0900(); // ics900 9��00�� �߻� vi ���ذ��� ������Ʈ ��û 20�ʸ��� 9��  5�к��� 
	
	void UpdateViStdPrice(CString strRegDt, CString strStkCd, CString strStdPr, CString strStdVo); // ics900 vi ���ذ��� ������Ʈ
	void UpdateViStdCnt(CString strRegDt, CString strStkCd, int nStdCnt);
	void UpdateSpth(CString strRegDt, CString strStkCd, CString strSpth);
	void UpdateIcs900Dt240(CString strRegDt, CString strStkCd, CString strDt240);// ics900 240 ���� ���Ŀ��� update

	CString GetVeNt(CString strStkCd);
	void Update1mc(CString strCndId, CString strStkCd, CHART_ITEM* p1mcItem, GV_ITEM* pItem);
	void Update1mIcs900();
	void UpdateMCandleIcs900(CString strStkCd);
	void Update1MmaIcs900(CString strStkCd, GV_ITEM* pItem);
	CString GetUseAtIcs900();
	void DeleteIcs900();
	void UpdateCndId(CString strCndId, GV_ITEM* pItem);

	CString IsRegStock(CString strStkCd);
	BOOL IsBuyLimit();

	map<CString, CHART_ITEM*> m_map1mcData;	// 1������ ������ MAP

	int CrossUpVOL(CHART_ITEM* pMcpItem);
	double CalculateEMA(const std::vector<double>& prices, int period);
	int CrossUpMACD(CHART_ITEM* pMcpItem);
	int CrossUpCCI(CHART_ITEM* pMcpItem, double dCmpVal);
	int CrossUpDI(CHART_ITEM* pMcpItem);
	double CalculateMinusDM(double todayLow, double yesterdayLow);
	double CalculatePlusDM(double todayHigh, double yesterdayHigh);
	double CalculateTrueRange(double todayHigh, double todayLow, double yesterdayClose);

public:
	FinanceChart* m_fc;

	CChartViewer m_ChartViewer;
	//void drawChart(CChartViewer* viewer);
	void DrawChart(CChartViewer* viewer, int nCandleNum, double* dDate, double* dHp, double* dLp, double* dOp, double* dCp, double* dVol, CString strStkCd);

	void ShowChart(CString strStkCd);
	//void drawBuyLine(MultiChart* m, int mouseY, int nLineStyle);

	void DrawLineInChart(MultiChart* m, int mouseY, int nLineStyle);

	void reverse_array(double array[], int arraylength);

public:
	afx_msg void OnBnClickedBtnBuyTest();
	afx_msg void OnBnClickedBtnSellTest();
	afx_msg void OnBnClickedBtnLog();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnOdAmtAllset();

	afx_msg void OnCbnSelchangeComboChartCn();
private:
	CComboBox m_cbDvSetLst;
	CComboBox m_cbDvBcnd;
	CComboBox m_cbDvBagb;
	CEdit m_edCnd1HogaIntv;

	CComboBox m_cbChartCn;
	int m_nChartCn;

	CComboBox m_cbSelDdy;
	CEdit m_edSelDdyCpHh;
	CEdit m_edSelDdyCpMi;
	CEdit m_edSelDdyCpSs;


	void GetRegConfData();
	CString m_strCfOdMny;
	CString m_strAccIdx;
	int m_nAccIdx;

	CEdit m_edOdMny;
	CEdit m_edChkBuyLmtCnt;
	CButton m_chkBuyLmtCnt;
	int m_nChkBuyLmtCnt; // �ż����� ����
	CString m_strBuyLmtCnt;	// �ż�����Ǽ� ����

	BOOL m_bChkBuyLmt;	// �ż�����Ǽ� ���� ���� ����

	CButton m_chkMktAt;	// ����Ÿ�̹� ���� ����
	BOOL m_bChkMktAt;

	BOOL m_bChkFstddyAt;	// ù�ż�D-Day ���� ����
	BOOL m_bChkOpmPmtAt;	// ù�ż��ð� ���
	BOOL m_bChkFstAdjAt;	// ù�ż�����������
	BOOL m_bChkSelDdyAt;	// �ŵ�D-Day
	int m_nMisBuyAt;

	CString m_strCnfTpf;
	int m_nCnfStl;
	int m_nCnfBdv;


	BOOL m_bChkBuyAlldelAt;	// �ż� �� ��� ���� ��� ����
	BOOL m_bChkHtsSyncAt;	// HTS ���� ���� ���� ����ȭ
	BOOL m_bChkOdStpAt;	// �ż� ���� ����
	int m_nApGb;		// �߰��ż�����
	CString m_strOdGb;	// �ż����� >=, >, ==, <, <=

	void UpdateGrid();

	BOOL CheckBuyOdCondMkt(BOOL bBuyYn, int nJgb); //  �ż� �ֹ� üũ : ����Ÿ�̹�
	BOOL CheckBuyOdCondOdMny(BOOL bBuyYn, int nOdMny, int nBuyAmt, int nPca);
	BOOL CheckBuyOdCondDayBuyLmt(BOOL bBuyYn, int nDayBuyLmt, int nTodayCheCnt);
	BOOL CheckBuyOdCondDvOrdPr(BOOL bBuyYn, int nDvBno, int nDvOrdPr, int nCp, CString strDvBcnd);
	BOOL CheckBuyOdCondDvCnd(BOOL bBuyYn, CString strKey, int nDvBno, CString strDvBcnd, double dProfitRate, double dDvBcndv, int nDvBcndv, int nCp, int nApGb);
	BOOL CheckBuyOdCondFstDdy(BOOL bBuyYn, int nDvBno, int nRegPrd, int nFstDdy);
	BOOL CheckBuyOdCondBuyLmtCnt(BOOL bBuyYn, int nDvBno);
	GV_ITEM* CheckBuyOdCondDivideNo(BOOL bBuyYn, int nOdPrcHigh, int nCp, int nBdv, CString strKey, int* pNTodayCheCnt, int* pNDvOrdPr, int nRtmAt, double dRate, double dOpbPmt, CString strOdGb);

public:

	CString m_strCnfDvSvid;


	afx_msg void OnBnClickedBtnDvSave();
	afx_msg void OnBnClickedBtnDvHogaIntv();

	void SaveDvSetting(CString strSaveNm);
	void InitCbDvSetLst();
	afx_msg void OnCbnSelchangeCbDvSetLst();
	afx_msg void OnBnClickedBtnDvGetSv();
	afx_msg void OnCbnSelchangeComboDvBcnd();
	afx_msg void OnCbnSelchangeCbDvcnd2();
	afx_msg void OnBnClickedBtnBuyStopY();
	afx_msg void OnBnClickedBtnBuyStopN();
	afx_msg void OnBnClickedBtnAutosellY();
	afx_msg void OnBnClickedBtnAutosellN();

	afx_msg void OnBnClickedBtnSelDdyCpSave();
	CButton m_btnSaveSelDdy;
	afx_msg void OnCbnSelchangeCbSelDdy();
	afx_msg void OnBnClickedBtnRegSet();
	afx_msg void OnBnClickedChkBuyLmtCnt();
	afx_msg void OnBnClickedBtnChkSell();
	afx_msg void OnBnClickedBtnAllSell();
	afx_msg void OnCbnSelchangeCbAcc();
	afx_msg void OnBnClickedChkMktAt();
	afx_msg void OnBnClickedBtChartMa5();
	afx_msg void OnBnClickedBtChartMa60();
	afx_msg void OnBnClickedBtnDv2Del();

	long m_nConnState;
	afx_msg void OnBnClickedBtQt();

	int m_nResults;
	CString m_szFontFile;
	HANDLE m_fonthandle;
	TTF m_Ttf;

	LOGFONT m_logFont;
	CFont m_font;

	CStringArray m_strArrMisBuyOpts;

	afx_msg void OnBnClickedBtnAllReadyBuy();
	afx_msg void OnBnClickedBtnAllStop();
	afx_msg void OnBnClickedBtnAllReadyBuy2();
	afx_msg void OnBnClickedBtnAllStop2();
	afx_msg void OnBnClickedBtnAllMissStop();
	afx_msg void OnBnClickedBtnAllMissDel();
	afx_msg void OnBnClickedBtnAllMissNo();
	afx_msg void OnBnClickedBtCndSearch();
	afx_msg void OnBnClickedButtonUnitTest();


	BOOL m_bStkDetailMode;
	afx_msg void OnClose();

	void ShowStkInfoDlg(CString strStkCd = _T(""), CString strStkNm = _T(""));
	afx_msg void OnBnClickedBtStkinfo();

	CStringArray m_strArrApGb;
	CStringArray m_strArrOdGb;

	CStatusBarCtrl m_statusBar;

public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);


	void InitDbTables();
	void SaveCOM900MT(COM900MT stData);

public:
	CString m_strServerName;
	int m_nServerPort;

	BOOL m_bConnect;

	void OnDisconnect();
	void OnReceive();
	void OnSocketClose();
	void OnConnect();

	CClientSocket* m_pConnectSocket;

	void SendDataToLauncher(CString strSendMsg);
};
