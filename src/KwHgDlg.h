
// KwHgDlg.h : 헤더 파일
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
	int* pnCheMin;	// 체결 시간(분)
	int nCandleNum;
} CHART_ITEM;

typedef struct _STK_REG_INFO {
	CString strKey;
	CString strScrNo;
} STK_REG_INFO;

// CKwHgDlg 대화 상자
class CKwHgDlg : public CDialogEx
{
// 생성입니다.
public:
	CKwHgDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_KWHG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	//CMap<int, int, CString, CString>	m_mapReqID;


	//CChildDlg* m_pDlg;
	CSplashScreenEx* m_pSplash;
public:
	// 종목검색 창
	CStockListDlg* m_pStockListDlg;

	// 로그 창
	CLogDlg* m_pLogDlg;
	BOOL	m_bLogShowYn;

	// 퀀트 종목선정
	CQtListDlg* m_pQtListDlg;
	BOOL	m_bQtDlgShowYn;

	// 조건검색 창
	CCondSrchDlg* m_pCondSrchDlg;
	BOOL	m_bCondSrchDlgShowYn;

	// 종목상세조회 창
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
// 구현입니다.
protected:
	HICON m_hIcon;

	HICON m_hIconConnected;
	HICON m_hIconClosed;

	// 생성된 메시지 맵 함수

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
	CString m_strToday;			// 거래일자(오늘) yyyymmdd
	int m_nJangStart;
	int m_nCloseJangFlag;

	int m_nCloseIcs900;

	BOOL m_bRtStart;

	int m_iOdPosNum;		// 주문가능한 매수구역수
	int m_iOdPosAmt;

	CFont m_Font;
	CFont m_FontStatic;
	CString m_stTime;
	CIsiLcdDisplay m_CIsiLcdSample10;


	CComboBox m_cbAcc;
	CMapStringToString m_mapAccount;
	CString m_strAccount;
	CString m_strAcctPassword;
	CEdit m_edJumunPossAmt;	// 주문가능금액
	int m_iOdPosAmtTot; // 주문가능금액

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

	void GetStockList();	// 전체 종목 업데이트


	//afx_msg void OnCbnSelchangeComboAcc();
	afx_msg void OnSelectMyAccount();

	BOOL m_bPgStart;

	void InitControl();
	void InitAccount();
	void AddAccount(TCHAR* strAccount, TCHAR* strAcctName);
	void GetAccounts();

	map<int, CString> m_mapRtScrNo;
	void ReqGetConditionLoad(); // 조건검색식 불러오기
	void ReqSendCondition(int nCsId, CString strCsNm, int nRtmAt);  // 조건검색식 종목 가져오기
	void ReqSendConditionStop(int nCsId, CString strCsNm); //실시간 종목 검색 중지
	void SaveKwCondSrch();
	// 조건검색 종목등록함수
	void RegTrStkByCondSch(CString strCsId, CString strStkCd, CString strStkNm, CString strStkGb, BOOL bRtAt, CString strExtraParam1, CString strExtraParam2);
	void StartRtCondSch(); // 실시간 조건 검색 시작
	CString m_strRtScrNo;

	CString m_strScrNo;

	int m_nInit;

	CEdit m_edStockSearch;
	CListCtrl m_listStock;
	afx_msg void OnBnClickedButtonStkSearch();


	//=================================================
	// 종목 등록 함수
	void RegTrStk(CString strStkCd, CString strStkNm, CString strStkGb);
	void RegTrExStk(CString strStkCd, CString strStkNm, CString strStkGb);

	CStringArray m_strArrRegStkCds;
	CStringArray m_strArrRegStkNms;
	CStringArray m_strArrRegStkGbs;
	BOOL m_bRegExStk;
	int m_nArrRegIdx;

	afx_msg void OnBnClickedButtonGetStock();

	// 실시간 
	CStringArray m_strArrRealRegStkInfos;


	BOOL m_bGrdListLoadAll;		// 등록 종목 모두 로드하였는지
	BOOL m_bGrdExListLoadAll;		// 실행 종목 모두 로드하였는지
	map<CString, STK_REG_INFO*> m_mapStkRegInfo;

	STK_REG_INFO* GetStkRegInfo(CString strStkCd);

	//int m_nTgBuyCnt;  // 대상 종목 주문 요청 건수
	int GetBuyOrdReqCount();


	// 매매 대상 등록 종목 리스트
	int m_nMapDataNum;
	CGridCtrl m_grdList;
	int m_nColCnt;
	map<CString, GV_ITEM*, greater<CString>> m_mapData;
	void InitGrid();
	void CreateMapData(CString strRegId = _T(""), CString strStkCd = _T(""));
	void UpdateGridData();

	// 매매 실행 종목 리스트
	int m_nMapExDataNum;
	CGridCtrl m_grdExList;
	int m_nExColCnt;
	map<CString, GV_ITEM*, greater<CString>> m_mapExData;
	void InitExGrid();
	void CreateMapExData(CString strRegId = _T(""), CString strStkCd = _T(""));
	void UpdateGridExData();

	// 매매 손익 리스트
	int m_nMapPlDataNum;
	CGridCtrl m_grdPlList;
	int m_nPlColCnt;
	int m_nEdPlTdSum;
	int m_nEdPlSum;

	map<CString, GV_ITEM*, greater<CString>> m_mapPlData;
	void InitPlGrid();
	void CreateMapPlData();
	void UpdateGridPlData();

	// 분할 매수 현황
	CGridCtrl m_grdDvList;
	int m_nDvColCnt;
	double m_dEdDvSum;
	map<CString, GV_ITEM*, less<CString>> m_mapDvData;
	void InitDvGrid();
	void CreateMapDvData(CString strRegId = _T(""), CString strStkCd = _T(""));
	void UpdateGridDvData();
	void InsertDvData(CString strScrNo, CString strRegId, CString strStkCd);

	void InsertExDvData(CString strScrNo, CString strRegId, CString strStkCd);

	// 실시간 매수 매도 미체결 현황 표시
	CGridCtrl m_grdTrList;
	int m_nTrColCnt;
	map<CString, GV_ITEM*, greater<CString>> m_mapTrData;
	void InitTrGrid();
	void CreateMapTrData();
	void UpdateGridTrData();

	void UpdateListNum(int nListType); // 각 종목 개수 업데이트

	void ReqKwDataByStkCd(CString strScrNo, CString strStkCd);// 종목 키움 일자별 종가 데이터 요청
	void ReqKwDataForDetailStkInfo(CString strScrNo, CString strStkCd);

	void ReqOpt20006(CString strStkCd); // 종합지수 일봉 조회 요청
	void ReqOpt10081(CString strScrNo, CString strStkCd); // 주식일봉차트조회요청
	void ReqOpt10080_ICS900(CString strScrNo, CString strStkCd); // 주식분봉차트조회요청 ics900
	void ReqOpt10080(CString strScrNo, CString strStkCd); // 주식분봉차트조회요청 

	double m_dKs9Sum;
	double m_dKq9Sum;
	double m_dCurKsp;
	double m_dCurKqp;
	BOOL m_bWarnKsMkt;
	BOOL m_bWarnKqMkt;

	void SetGridRowColor(CGridCtrl& grdList, int row, COLORREF clr);

	map<CString, CHART_ITEM*> m_mapChart;	// 차트 데이터 MAP

	void CheckJangStart();

	CString m_strSrv;	// 모의서버/실시간서버

	double m_dFeeRate;	// 수수료율

	CString m_strSelKey;
	CString m_strSelStkCd;
	CString m_strOldSelStkCd;

	CString m_strBuyCncTrKey;	// 매수주문취소 키
	CString m_strSellCncTrKey;	// 매도주문취소 키

	BOOL m_bChkHtsList;
	void ReqAccntStkList();	// 계좌평가잔고내역요청

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

	int GetNotDelDvBno(CString strRegDt, CString strStkCd); // 분할차수 수정시 삭제 불가 차수 조회

	void UpdateGwgeVal(int nGridNo, int nCol, CString strRegDt, CString strStkCd, CString strVal);

	void OrderSellGridRow(CString strRegDt, CString strStkCd, GV_ITEM* pItem);	// 수동 매도
	void DeleteGridRow(CString strRegDt, CString strStkCd);	// 삭제

	void DeleteExGridRow(CString strRegDt, CString strStkCd);

	void UpdateGridCellDvData(CString strRegDt, CString strStkCd, CString strBno, int nRow, int nCol, CString strUpdateVal);
	void UpdateDvBcndv(CString strRegDt, CString strStkCd, CString strBno, CString strUpdateVal, GV_ITEM* pDvItem);	// 분할 매수조건값 수정
	void UpdateDvBamt(CString strRegDt, CString strStkCd, CString strBno, CString strUpdateVal, GV_ITEM* pDvItem);	// 분할 매수금액/주식수 수정

	void ProcRealData(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void ProcViRealData(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);

	void TradeByCond(CString strScrNo, CString strKey, int nOp, int nCp, int nCurQty, int nMc, GV_ITEM* pItem, int nChetime);
	void Order(int nGb, CString strKey, long nPrice, long nQty, CString strOrgOrdNo = _T(""));
	//void CancelOrder(int nGb, CString strTrKey);

	void InsertOrder(CString strKey, int nOrdGb);
	void UpdateOrder(CString strOrdState, CString strStkCd, CString strOrdNo, int nBuysellType, CString strBno
		, CString strOrdPrice, int nOrdQty, int nNotConQty, CString strOrdTime);

	void UpdateCancelOrder(CString strOrdState, CString strStkCd, CString strOrgOrdNo, int nBuysellType);

	void CancelOrderByTimeOut(); // 주문번호 없는 경우 시간이 지난 주문요청 flag 해제 -> BFL 1 로 세팅되어 있으면 주문요청이 안됨
	void CancelOrderByTimeOut2();

	void ReqOpt10170(); // 당일매매일지요청 
	void ReqOpt10075(); // 미체결요청
	void ReqOpt10085(); // 계좌수익률요청

	void ReqOpt10001(CString strScrNo, CString strStkCd); // opt10001 : 주식기본정보요청
	void ReqOpt10045(CString strScrNo, CString strStkCd); // opt10045 : 종목별기관매매추이요청
	void ReqOpt10054(CString strScrNo); // opt10054 : 종목별기관매매추이요청

	GV_ITEM* GetMapItemByStkCd(CString strStkCd);

	int GetHogaUnit(int nPrice);

	void UpdateBuyLmtAt(BOOL bVal);
	void UpdateMktAt(BOOL bVal);
	void UpdateColfstddyAt(BOOL bVal);

	void DeleteTgListAll(); // 대상종목 모두 삭제

	int CompareDoubleAbsoulteAndUlps(double x,
		double y,
		double absTolerance = (1.0e-8),
		int ulpsTolerance = 4);

	//BOOL IsStkTradeUntilToday(CString strStkCd); // 금일까지 거래했던 종목이었는지 여부
	CString GetViStartTime(CString strViStartTime);

	void ReqUpdateViStdPrice(CString strStkCd); // ics900 vi 기준가격 업데이트 요청
	void ReqUpdateViStdPriceByCurTime(CString strCurTime); // ics900 vi 기준가격 업데이트 요청 15초마다
	void ReqUpdateViStdPrice0900(); // ics900 9시00분 발생 vi 기준가격 업데이트 요청 20초마다 9시  5분부터 
	
	void UpdateViStdPrice(CString strRegDt, CString strStkCd, CString strStdPr, CString strStdVo); // ics900 vi 기준가격 업데이트
	void UpdateViStdCnt(CString strRegDt, CString strStkCd, int nStdCnt);
	void UpdateSpth(CString strRegDt, CString strStkCd, CString strSpth);
	void UpdateIcs900Dt240(CString strRegDt, CString strStkCd, CString strDt240);// ics900 240 하향 돌파여부 update

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

	map<CString, CHART_ITEM*> m_map1mcData;	// 1분종가 데이터 MAP

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
	int m_nChkBuyLmtCnt; // 매수종목 제한
	CString m_strBuyLmtCnt;	// 매수종목건수 제한

	BOOL m_bChkBuyLmt;	// 매수종목건수 제한 적용 여부

	CButton m_chkMktAt;	// 마켓타이밍 적용 여부
	BOOL m_bChkMktAt;

	BOOL m_bChkFstddyAt;	// 첫매수D-Day 적용 여부
	BOOL m_bChkOpmPmtAt;	// 첫매수시가 허용
	BOOL m_bChkFstAdjAt;	// 첫매수가조정여부
	BOOL m_bChkSelDdyAt;	// 매도D-Day
	int m_nMisBuyAt;

	CString m_strCnfTpf;
	int m_nCnfStl;
	int m_nCnfBdv;


	BOOL m_bChkBuyAlldelAt;	// 매수 후 대상 종목 모두 삭제
	BOOL m_bChkHtsSyncAt;	// HTS 계좌 보유 종목 동기화
	BOOL m_bChkOdStpAt;	// 매수 중지 여부
	int m_nApGb;		// 추가매수구분
	CString m_strOdGb;	// 매수기준 >=, >, ==, <, <=

	void UpdateGrid();

	BOOL CheckBuyOdCondMkt(BOOL bBuyYn, int nJgb); //  매수 주문 체크 : 마켓타이밍
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
