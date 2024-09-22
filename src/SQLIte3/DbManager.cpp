#include "../stdafx.h"
#include "DbManager.h"
#include "CppSQLite3.h"
#include "../KwHg.h"

#define DBF_NAME _T("santorini.rbf")

CDbManager::CDbManager()
{
	m_pDbUtil = new CppSQLite3DB();

	CString path = theApp.m_sAppPath + _T("\\" + DBF_NAME);

	//::OutputDebugString(path);

	m_gszFile = new char[path.GetLength() + 1];
	strcpy((char*)m_gszFile, CT2A(path));
}

CDbManager::~CDbManager()
{
	close();

	if (m_gszFile != NULL)
		delete[] m_gszFile;


	if (m_pDbUtil != NULL)
		delete m_pDbUtil;
}

void CDbManager::open()
{
	m_pDbUtil->open(m_gszFile);
}

void CDbManager::close()
{
	m_pDbUtil->close();
}

void CDbManager::DbUtf8ToAnsi(const char* szVal, CString& strVal)
{
	CString strRtn = _T("");

	char* tmp = (char*)szVal;
	char szName[2048];
	UTF8ToAnsi(tmp, szName, 2048);
	strVal = szName;
}

void CDbManager::AnsiToDbUtf8(CString strVal, char* szVal)
{
	char* s_name;

	char c[1024] = { 0 };
	wcstombs(c, strVal.GetBuffer(strVal.GetLength()), wcslen(strVal.GetBuffer(strVal.GetLength())));

	int len = strlen(c);
	WCHAR * lpcwchStr = new WCHAR[len];
	// Converts the path to wide characters

	MultiByteToWideChar(0, 0, (CStringA)strVal, len + 1, lpcwchStr, len + 1);

	int sLen = WideCharToMultiByte(CP_ACP, 0, lpcwchStr, -1, NULL, 0, NULL, NULL);
	s_name = new char[sLen + 1];
	WideCharToMultiByte(CP_ACP, 0, lpcwchStr, -1, s_name, sLen, NULL, NULL);

	//AnsiToUTF8(s_name, szVal, 100);
	ToUtf8(s_name, szVal, 100);

	//memcpy(szVal, s_name, sLen+1);

	delete[]s_name;
}


// SQLite는 UTF8을 사용하기 때문에 코드 변환이 필요합니다.
int CDbManager::AnsiToUTF8(char* szSrc, char* strDest, int destSize)
{
	WCHAR szUnicode[255];
	char szUTF8code[255];

	int nSize = MultiByteToWideChar(CP_ACP, 0, szSrc, -1, 0, 0);
	int nUnicodeSize = MultiByteToWideChar(CP_ACP, 0, szSrc, (int)strlen(szSrc), szUnicode, nSize);//sizeof(szUnicode));
	int nUTF8codeSize = WideCharToMultiByte(CP_UTF8, 0, szUnicode, nUnicodeSize, szUTF8code, sizeof(szUTF8code), NULL, NULL);
	//assert(destSize > nUTF8codeSize);
	memcpy(strDest, szUTF8code, nUTF8codeSize);
	strDest[nUTF8codeSize] = 0;
	return nUTF8codeSize;
}

int CDbManager::UTF8ToAnsi(char* szSrc, char* strDest, int destSize)
{
	WCHAR szUnicode[2048];
	char szAnsi[2048];

	int nSize = MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, 0, 0);
	int nUnicodeSize = MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, szUnicode, nSize);
	int nAnsiSize = WideCharToMultiByte(CP_ACP, 0, szUnicode, nUnicodeSize, szAnsi, sizeof(szAnsi), NULL, NULL);
	//assert(destSize > nAnsiSize);
	memcpy(strDest, szAnsi, nAnsiSize);
	strDest[nAnsiSize] = 0;
	return nAnsiSize;
}

void CDbManager::ToUtf8(const char* pszIn, char* strDest, int destSize)
{

	int nLenOfUni = 0, nLenOfUTF = 0;
	wchar_t* us = NULL;
	char* pszOut = NULL;

	if ((nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, strlen(pszIn), NULL, 0)) <= 0)
		return;

	us = new wchar_t[nLenOfUni + 1];
	memset(us, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

	// ansi ---> unicode
	nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, strlen(pszIn), us, nLenOfUni);

	if ((nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, us, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
	{
		//free(us);
		delete[] us;
		return;
	}

	pszOut = new char[nLenOfUTF + 1];
	memset(pszOut, 0x00, sizeof(char) * (nLenOfUTF + 1));

	// unicode ---> utf8
	nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, us, nLenOfUni, pszOut, nLenOfUTF, NULL, NULL);
	pszOut[nLenOfUTF] = 0;
	//resultString = pszOut;

	//strDest = pszOut;
	memcpy(strDest, pszOut, nLenOfUTF);

	strDest[nLenOfUTF] = 0;

	delete[] us;
	delete[] pszOut;

	//return resultString;

}

void CDbManager::execQueryUtf8(CString strQuery)
{
	char szQuery[1000];
	memset(szQuery, 0, sizeof(char) * 1000);
	DBM->AnsiToDbUtf8(strQuery, szQuery);
	DBM->m_pDbUtil->execQuery(szQuery);
}