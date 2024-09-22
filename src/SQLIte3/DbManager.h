#pragma once

#ifndef DB_MANAGER_SINGLETON_CLASS_H
#define DB_MANAGER_SINGLETON_CLASS_H

class CppSQLite3DB;
class CppSQLite3Query;

template < typename T >
class TemplateSingleton
{
protected:
    TemplateSingleton()
    {

    }
    virtual ~TemplateSingleton()
    {

    }

public:
    static T* GetInstance()
    {
        if (m_pInstance == NULL)
            m_pInstance = new T;
        return m_pInstance;
    };

    static void DestroyInstance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    };

private:
    static T* m_pInstance;
};

template <typename T> T* TemplateSingleton<T>::m_pInstance = 0;


class CDbManager : public TemplateSingleton<CDbManager> //ÅÛÇÃ¸´ ½Ì±ÛÅæ »ó¼Ó
{
private:

    const char* m_gszFile;

public:
    CDbManager();
    virtual ~CDbManager();

    CppSQLite3DB* m_pDbUtil;

    void open();
    void close();
    //void Init();

    void DbUtf8ToAnsi(const char* szVal, CString& strVal);
    void AnsiToDbUtf8(CString strVal, char* szVal);
    void ToUtf8(const char* pszIn, char* strDest, int destSize);

    int AnsiToUTF8(char* szSrc, char* strDest, int destSize);
    int UTF8ToAnsi(char* szSrc, char* strDest, int destSize);

    void execQueryUtf8(CString strQuery);
};

#define DBM CDbManager::GetInstance()
#define GETSTR_EXECSQL(stmt)   sqlite3_expanded_sql(stmt.getSqlite3Stmt())

#define EXECSQL(query)   DBM->m_pDbUtil->execQuery(query);
#define EXECSQL_UTF8(query)   DBM->execQueryUtf8(query);

#endif