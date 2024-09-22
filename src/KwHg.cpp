
// KwHg.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "KwHg.h"
#include "KwHgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKwHgApp

BEGIN_MESSAGE_MAP(CKwHgApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKwHgApp ����

CKwHgApp::CKwHgApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CKwHgApp ��ü�Դϴ�.

CKwHgApp theApp;

// CKwHgApp �ʱ�ȭ

BOOL CKwHgApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	//////////////////////////////////////////////////////////////////
	// ���������� �н��� �����Ѵ�.
	//wchar_t szPath[MAX_PATH];
	//GetModuleFileName(AfxGetInstanceHandle(), szPath, MAX_PATH);
	//*strrchr(ConvertWCtoC(szPath), '\\') = '\0';
	//m_sAppPath = szPath;

	
	char szPath[MAX_PATH]; //CA2CT(szPath)
	wchar_t wszPath[MAX_PATH];
	mbstowcs(wszPath, szPath, strlen(szPath) + 1);//Plus null LPWSTR ptr = wtext;

	GetModuleFileName(AfxGetInstanceHandle(), wszPath, MAX_PATH);
	char *szTmpPath = ConvertWCtoC(wszPath);
	*strrchr(szTmpPath, '\\') = '\0';
	m_sAppPath = szTmpPath;
	/*
	CString strFileName = m_sAppPath + "/data";
	if (!::PathIsDirectory(strFileName))		// ������ ���ٸ�
	{
		::CreateDirectory(strFileName, NULL);
	}
	*/

	CKwHgDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}

char* CKwHgApp::ConvertWCtoC(wchar_t* str)
{
	//��ȯ�� char* ���� ����
	char* pStr;

	//�Է¹��� wchar_t ������ ���̸� ����
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	//char* �޸� �Ҵ�
	pStr = new char[strSize];

	//�� ��ȯ 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);

	return pStr;
}


//*******************************************************************/
//! Function Name : ConvDataFormat
//! Function      : ���ڿ� ���� ����
//! Param         : int nType, LPCTSTR szData, LPCTSTR szBeforeData/* = ""*/, LPCTSTR szAfterData/* = ""*/
//! Return        : CString
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
CString CKwHgApp::ConvDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData/* = _T("")*/, LPCTSTR szAfterData/* = _T("")*/)
{
	CString strReturn, strData, strTemp = strData = szData;
	switch (nType)
	{
	case DT_DATE:			// ����
	{
		if (strTemp.GetLength() == 6)
		{
			strData.Format(_T("%02s/%02s/%02s"), strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Right(2));
		}
		else if (strTemp.GetLength() == 8)
		{
			strData.Format(_T("%04s/%02s/%02s"), strTemp.Left(4), strTemp.Mid(4, 2), strTemp.Right(2));
		}
	}
	break;
	case DT_TIME:			// �ð�
	{
		if (strTemp.GetLength() == 6)
		{
			strData.Format(_T("%02s:%02s:%02s"), strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Right(2));
		}
		else if (strTemp.GetLength() == 8)
		{
			strData.Format(_T("%02s:%02s:%02s:%02s"), strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Mid(4, 2), strTemp.Right(2));
		}
	}
	break;
	case DT_NUMBER:			// ����
	case DT_ZERO_NUMBER:	// ����(0ǥ��)
	{
		strTemp.Replace(_T("+"), _T(""));
		if (_wtof(strTemp) == 0.00)
		{
			strData = nType == DT_ZERO_NUMBER ? strTemp : _T("");
			break;
		}

		int nFind = strTemp.Find(_T("."));
		if (nFind < 0)
		{
			strData = strTemp;
		}
		else
		{
			strData = strTemp.Left(nFind);
			strTemp = strTemp.Mid(nFind);
		}

		TCHAR szFormatData[1024] = { 0, };
		NUMBERFMT fmt = { 0, 0, 3, _T("."), _T(","), 1 };
		::GetNumberFormat(NULL, 0, strData, &fmt, szFormatData, 1024);

		if (nFind < 0)
		{
			nType == DT_ZERO_NUMBER ? strData.Format(_T("%01s"), szFormatData) : strData.Format(_T("%s"), szFormatData);
		}
		else
		{
			strData.Format(_T("%01s%s"), szFormatData, strTemp);
		}
	}
	break;
	}

	strReturn.Format(_T("%s%s%s"), szBeforeData, strData, szAfterData);

	return strReturn;
}

//*******************************************************************/
//! Function Name : IsError
//! Function      : ���� ����
//! Param         : long lErrCode
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CKwHgApp::IsError(long lErrCode)
{
	CString strMsg = _T("");
	switch (lErrCode)
	{
		////////////////////////////
		// �Ϲ� ��ȸ ���� ó��
	case OP_ERR_SISE_OVERFLOW:		// �ü���ȸ ������
		strMsg = "�ü���ȸ ������";
		break;
	case OP_ERR_RQ_STRUCT_FAIL:		// REQUEST_INPUT_st Failed
		strMsg = "REQUEST_INPUT_st Failed";
		break;
	case OP_ERR_RQ_STRING_FAIL:		// ��û ���� �ۼ� ����
		strMsg = "��û ���� �ۼ� ����";
		break;
	case OP_ERR_NO_DATA:			// �����Ͱ� �������� �ʽ��ϴ�.
		strMsg = "�����Ͱ� �������� �ʽ��ϴ�.";
		break;

		////////////////////////////
		// ���� ���� ��ȸ ���� ó��
	case OP_ERR_OVER_MAX_DATA:			// �ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�.
		strMsg = "�ѹ��� ��ȸ ������ ���񰳼��� �ִ� 100���� �Դϴ�.";
		break;

		////////////////////////////
		// �ֹ� ���� ó��
	case OP_ERR_ORD_WRONG_INPUT:		// �Է°� ����
		strMsg = "�Է°� ����";
		break;
	case OP_ERR_ORD_WRONG_ACCNO:		// ���º�й�ȣ�� �Է��Ͻʽÿ�.
		strMsg = "���º�й�ȣ�� �Է��Ͻʽÿ�.";
		break;
	case OP_ERR_OTHER_ACC_USE:			// Ÿ�ΰ��´� ����� �� �����ϴ�.
		strMsg = "Ÿ�ΰ��´� ����� �� �����ϴ�.";
		break;
	case OP_ERR_MIS_2BILL_EXC:			// �ֹ������� 20����� �ʰ��մϴ�.
		strMsg = "�ֹ������� 20����� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_5BILL_EXC:			// �ֹ������� 50����� �ʰ��մϴ�.
		strMsg = "�ֹ������� 50����� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_1PER_EXC:			// �ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�.
		strMsg = "�ֹ������� �ѹ����ּ��� 1%�� �ʰ��մϴ�.";
		break;
	case OP_ERR_MIS_3PER_EXC:			// �ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�.
		strMsg = "�ֹ������� �ѹ����ּ��� 3%�� �ʰ��� �� �����ϴ�.";
		break;
	case OP_ERR_SEND_FAIL:				// �ֹ����۽���
		strMsg = "�ֹ����ۿ� �����Ͽ����ϴ�..";
		break;
	case OP_ERR_ORD_OVERFLOW:			// �ֹ����� ������
		strMsg = "�ֹ����� ������ �Դϴ�. ��� �� �ٽ� �ֹ��Ͽ� �ּ���.";
		break;
	}

	// ���� �޼��� ó��
	if (!strMsg.IsEmpty())
	{
		//AfxMessageBox(strMsg);
		return FALSE;
	}

	return TRUE;
}