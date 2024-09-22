// BasicTestDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "YOADLLClient.h"
#include "BasicTestDlg.h"
#include "afxdialogex.h"
#include "../../include/MessageDef.h"
#include "YOADLLClientDlg.h"

// CBasicTestDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBasicTestDlg, CDialogEx)

CBasicTestDlg::CBasicTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBasicTestDlg::IDD, pParent)
	, m_strJongCode(_T(""))
{
	m_pMainDlg = NULL;

	m_nReqID_300001 = -1;
}

CBasicTestDlg::~CBasicTestDlg()
{
}

void CBasicTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_JONGCODE, m_strJongCode);
	DDX_Control(pDX, IDC_LIST_LOG, m_lbLog);
}


BEGIN_MESSAGE_MAP(CBasicTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CBasicTestDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_REGIST, &CBasicTestDlg::OnBnClickedButtonAutoRegist)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_UNREGIST, &CBasicTestDlg::OnBnClickedButtonAutoUnRegist)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_RECEIVE_DATA, OnReceiveData)
	ON_MESSAGE(WMU_RECEIVE_REAL_DATA, OnReceiveRealData)
END_MESSAGE_MAP()


void CBasicTestDlg::LogMessage( CString strMsg )
{
	m_lbLog.InsertString( 0, strMsg );
}

// BasicTestDlg �޽��� ó�����Դϴ�.


void CBasicTestDlg::OnBnClickedButtonSearch()
{
	UpdateData();

	TCHAR szJang[10] = {0, };
	// ��ȸTR(DSO) ���� ��� 1 ///////////////////////////////////////////////////////////////////
	g_iYuantaAPI.YOA_GetCodeInfo(MARKET_TYPE_INTERNAL, CODE_INFO_JANG_GUBUN, m_strJongCode, szJang, sizeof(szJang));
	int nResult = g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"),	_T("jang"), szJang );

	// ���� ó�� - ��ȸTR��, InBlock��, �ʵ���� Ʋ�� ��� ���� ��ȯ�մϴ�. (�����ڵ� CommDef.h ����)
	// ERROR_DSO_NOT_FOUND					202		// DSO�� ã�� �� �����ϴ�.
	// ERROR_BLOCK_NOT_FOUND				203		// ����� ã�� �� �����ϴ�.
	// ERROR_FIELD_NOT_FOUND				204		// �ʵ带 ã�� �� �����ϴ�.
	if ( RESULT_SUCCESS != nResult )
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// �ʵ尪 ���� ������ ���� �޽����� ���� �� �ֽ��ϴ�.

		AfxMessageBox(msg);
	}

	g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("jongcode"),	m_strJongCode );
	g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("outflag"),	_T("N") );
	g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("tsflag"),	_T("0") );
	//////////////////////////////////////////////////////////////////////////////////////////////


	// ��ȸTR(DSO) ���� ��� 2 ///////////////////////////////////////////////////////////////////
	/*
	g_iYuantaAPI.YOA_SetTRInfo( _T("300001"), _T("InBlock1") );
	g_iYuantaAPI.YOA_SetFieldString( _T("jang"),	 _T("1") );
	g_iYuantaAPI.YOA_SetFieldString( _T("jongcode"), m_strJongCode );
	g_iYuantaAPI.YOA_SetFieldString( _T("outflag"),	 _T("N") );
	g_iYuantaAPI.YOA_SetFieldString( _T("tsflag"),	 _T("0") );
	*/
	//////////////////////////////////////////////////////////////////////////////////////////////

	m_nReqID_300001 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("300001") );

	if ( ERROR_MAX_CODE < m_nReqID_300001 )			// ��ȸ ��û ���� ��, ERROR_MAX_CODE(1000)���� ū ���� ���� ��ûID ��ȯ�մϴ�.
	{												// ��ȸ������ �޾���, �����ϴ� ID�� ����մϴ�.
		LogMessage( _T("[300001]�ֽ����簡 ��ȸ�� ��û�Ͽ����ϴ�.") );
	}
	else	// ��ȸ ��û ���� ��, ���� ó��
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( m_nReqID_300001, msg, sizeof(msg) );			// ��ȸ ��û ���п� ���� �޽����� ���� �� �ֽ��ϴ�.

		LogMessage(msg);
	}
}


void CBasicTestDlg::OnBnClickedButtonAutoRegist()
{
	UpdateData();

	g_iYuantaAPI.YOA_SetTRFieldString( _T("11"), _T("InBlock1"), _T("jongcode"), m_strJongCode );
	int nResult = g_iYuantaAPI.YOA_RegistAuto( GetSafeHwnd(), _T("11") );

	if ( ERROR_MAX_CODE < nResult )
	{
		GetDlgItem( IDC_BUTTON_AUTO_REGIST )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_AUTO_UNREGIST )->EnableWindow( TRUE );

		LogMessage( _T("[11]�ֽ� �ǽð�ü���� ��� �Ǿ����ϴ�.") );
	}
	else
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// �ǽð� ��� ���п� ���� �޽����� ���� �� �ֽ��ϴ�.

		LogMessage(msg);
	}
}

void CBasicTestDlg::OnBnClickedButtonAutoUnRegist()
{
	int nResult = g_iYuantaAPI.YOA_UnregistAuto( GetSafeHwnd(), _T("11") );

	if ( RESULT_SUCCESS == nResult )
	{
		GetDlgItem( IDC_BUTTON_AUTO_REGIST )->EnableWindow( TRUE );
		GetDlgItem( IDC_BUTTON_AUTO_UNREGIST )->EnableWindow( FALSE );

		LogMessage( _T("[11]�ֽ� �ǽð�ü���� ���� �Ǿ����ϴ�.") );
	}
	else
	{
		TCHAR msg[2048] = {0,};
		g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );			// �ǽð� ���� ���п� ���� �޽����� ���� �� �ֽ��ϴ�.

		LogMessage(msg);
	}
}

LRESULT CBasicTestDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
{

	int nReqID = wParam;

	CString strMsg;
	CString strTrName;

	if ( nReqID == m_nReqID_300001 )
	{
		strTrName = _T("[300001]�ֽ����簡");
	}	

	switch ( lParam )
	{
	case ERROR_TIMEOUT_DATA:			// ������ �ð� �ȿ� �����κ��� ������ ���� ���, Ÿ�Ӿƿ��� �߻��մϴ�. (�⺻ 10��)
		{
			strMsg.Format( _T("Timeout %s ��û�� ������ �����ϴ�."), strTrName);
			LogMessage(strMsg);
		}
		break;
	case ERROR_REQUEST_FAIL:			// �������� ��ȸTR(DSO) ó���� ������ �ִ� ��� �߻��մϴ�.
		{
			TCHAR msg[2048] = {0,};
			g_iYuantaAPI.YOA_GetErrorMessage( nReqID, msg, sizeof(msg) );	// ó�� �� ������ ���� �޽����� ���� �� �ֽ��ϴ�.
			strMsg.Format( _T("%s\n%s"), strTrName, msg);
			strMsg.TrimRight();
			LogMessage(strMsg);
		}
		break;
	}
	
	return 0;

}

LRESULT CBasicTestDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	//CString strTRID( (LPCTSTR)(LPCSTR)lParam );
	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;

	CString strTrName = _T("");

	if ( wParam == m_nReqID_300001 )
	{
		strTrName = _T("[300001]�ֽ����簡");

		TCHAR data[1024] = {0,};

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("300001"), _T("OutBlock1"), _T("jongname"), data, sizeof(data) );
		GetDlgItem( IDC_BT_JONGNAME )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("300001"), _T("OutBlock1"), _T("curjuka"), data, sizeof(data) );
		GetDlgItem( IDC_BT_CURJUKA )->SetWindowText( data );

		g_iYuantaAPI.YOA_SetTRInfo( _T("300001"), _T("OutBlock1") );
		g_iYuantaAPI.YOA_GetFieldString( _T("debi"), data, sizeof(data) );
		GetDlgItem( IDC_BT_DEBI )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetFieldString( _T("debirate"), data, sizeof(data) );
		GetDlgItem( IDC_BT_DEBIRATE )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetFieldString( _T("volume"), data, sizeof(data) );
		GetDlgItem( IDC_BT_VOLUME )->SetWindowText( data );

		LogMessage( _T("[300001]�ֽ����簡 ������ �����Ͽ����ϴ�.") );
	}
	else if ( wParam == m_nReqID_160001 )
	{
		TCHAR data[1024] = {0,};

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("160001"), _T("OutBlock1"), _T("org_no"), data, sizeof(data) );
	}

	return 0;

}

LRESULT CBasicTestDlg::OnReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	
	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;
	CString strAutoID( pRecvData->szTrCode );
	
	if ( 0 == strAutoID.Compare( _T("11") ) )
	{
		long nData = 0;
		TCHAR data[1024] = {0,};

		//g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("curjuka"), &nData );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("curjuka"), data, sizeof(data) );
		GetDlgItem( IDC_BT_CURJUKA )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("debi"), data, sizeof(data) );
		GetDlgItem( IDC_BT_DEBI )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("debirate"), data, sizeof(data) );
		GetDlgItem( IDC_BT_DEBIRATE )->SetWindowText( data );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("volume"), data, sizeof(data) );
		GetDlgItem( IDC_BT_VOLUME )->SetWindowText( data );
	}
	else if ( 0 == strAutoID.Compare( _T("71") ) )
	{
		byte gubun48 = 0;
		g_iYuantaAPI.YOA_GetTRFieldByte( _T("71"), _T("OutBlock1"), _T("gubun48"), &gubun48 );

		TCHAR data[1024] = {0,};
		memset(data, 0x00, sizeof(data));
		g_iYuantaAPI.YOA_GetTRFieldString( _T("71"), _T("OutBlock1"), _T("custseq"), data, sizeof(data) );

		memset(data, 0x00, sizeof(data));
		g_iYuantaAPI.YOA_GetTRFieldString( _T("71"), _T("OutBlock1"), _T("origno"), data, sizeof(data) );

		memset(data, 0x00, sizeof(data));
		g_iYuantaAPI.YOA_GetTRFieldString( _T("71"), _T("OutBlock1"), _T("ordno"), data, sizeof(data) );

		memset(data, 0x00, sizeof(data));
		g_iYuantaAPI.YOA_GetTRFieldString( _T("71"), _T("OutBlock1"), _T("jumunno"), data, sizeof(data) );

		__int64 cheprcise = 0;
		int nResult = g_iYuantaAPI.YOA_GetTRFieldLong64( _T("71"), _T("OutBlock1"), _T("jumunuv"), &cheprcise );

		if ( ERROR_MAX_CODE < nResult )
		{										

		}
		else	// ��ȸ ��û ���� ��, ���� ó��
		{
			TCHAR msg[2048] = {0,};
			g_iYuantaAPI.YOA_GetErrorMessage( nResult, msg, sizeof(msg) );

			LogMessage(msg);
		}
	}

	return 0;

}
