
// KwHg.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
//#include ".\IsiLcdLib\IsiLcdDisplay.h"
#include "KHOpenAPICtrl.h"


#define OP_ERR_SISE_OVERFLOW	-200			//"시세조회 과부하"
#define OP_ERR_RQ_STRUCT_FAIL	-201			//"REQUEST_INPUT_st Failed"
#define OP_ERR_RQ_STRING_FAIL	-202			//"요청 전문 작성 실패"
#define OP_ERR_NO_DATA			-203			//"데이터가 존재하지 않습니다."
#define OP_ERR_OVER_MAX_DATA	-204			//"한번에 조회 가능한 종목개수는 최대 100종목 입니다."


#define OP_ERR_ORD_WRONG_INPUT	-300			//"입력값 오류"
#define OP_ERR_ORD_WRONG_ACCNO	-301			//"계좌비밀번호를 입력하십시오."
#define OP_ERR_OTHER_ACC_USE	-302			//"타인계좌는 사용할 수 없습니다."
#define OP_ERR_MIS_2BILL_EXC	-303			//"주문가격이 20억원을 초과합니다."
#define OP_ERR_MIS_5BILL_EXC	-304			//"주문가격이 50억원을 초과합니다."
#define OP_ERR_MIS_1PER_EXC		-305			//"주문수량이 총발행주수의 1%를 초과합니다."
#define OP_ERR_MIS_3PER_EXC		-306			//"주문수량은 총발행주수의 3%를 초과할 수 없습니다."
#define OP_ERR_SEND_FAIL		-307			//"주문전송실패"
#define OP_ERR_ORD_OVERFLOW		-308			//"주문전송 과부하"

#define TR_OPT10001		"OPT10001"
#define TR_OPT10003		"OPT10003"
#define TR_OPT10004		"OPT10004"
#define TR_OPT10080		"OPT10080"
#define TR_OPT10081		"OPT10081"

#define DT_NONE			0		// 기본문자 형식
#define DT_DATE			1		// 일자 형식
#define DT_TIME			2		// 시간 형식
#define DT_NUMBER		3		// 콤파 숫자 형식
#define DT_ZERO_NUMBER	4		// 콤파 숫자(0표시) 형식
#define DT_SIGN			5		// 대비기호 형식

typedef struct
{
	CString	strKey;				// 조회 키
	CString	strRealKey;			// 리얼 키
	int		nRow;				// 그리드 행
	int		nCol;				// 그리드 열
	int		nDataType;			// 데이타 타입(0:기본문자, 1:일자, 2:시간, 3:콤파 숫자, 4:콤파 숫자(0표시), 5:대비기호)
	BOOL		bTextColor;			// 문자열 색 변경(상승, 하락색)
	UINT		nAlign;				// 문자열 정렬(DT_LEFT, DT_CENTER, DT_RIGHT)
	CString	strBeforeData;		// 문자열 앞 문자 넣기
	CString	strAfterData;		// 문자열 뒤 문자 넣기
} stGRID;


// CKwHgApp:
// 이 클래스의 구현에 대해서는 KwHg.cpp을 참조하십시오.
//

class CKwHgApp : public CWinApp
{
private:
	DECLARE_GDI_PLUS;

public:
	CKwHgApp();

public:
	//CKhopenapictrl1 m_khOpenApi;
	CKHOpenAPI	m_khOpenApi;

	CString	m_sAppPath;		// 실행 파일 패스

	char* ConvertWCtoC(wchar_t* str);

	CString ConvDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData = _T(""), LPCTSTR szAfterData = _T(""));
	//void SetSignData(CGridCtrl* pGrid, int nRow, int nCol, LPCTSTR szData);
	//void SetDataFgColour(CGridCtrl* pGrid, int nRow, int nCol, LPCTSTR szData);		// 그리드 셀 문자색 변경

// 재정의입니다.
public:
	virtual BOOL InitInstance();

public:
	BOOL IsError(long lErrCode);		// 오류 여부

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CKwHgApp theApp;