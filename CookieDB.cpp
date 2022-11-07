//  CookieDB.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to the cookie database table for the app.

#include "CookieDB.h"

using namespace std;

const char* DB_PATH{ "./database.db" };

CookieDB::CookieDB(const string& tableName)
    : _tableName{ tableName }
{
    if (SQLITE_OK == sqlite3_open(DB_PATH, &_dbObject))
    {
        cout << "Database successfully opened. Table: " + _tableName + '\n';
    }
    else
    {
        cout << "Database could not be opened.";
        throw "Database could not be opened.";
    }

    if (tableSetup() == -1) throw "Error occured.";
}

CookieDB::~CookieDB()
{
    sqlite3_close(_dbObject);
    cout << "Cookie database successfully closed.\n";
}

int CookieDB::AddSession(const std::string& username, const std::string& cookie)
{
    if (usernameExists(username)) return 0;

    string timestamp = GetCurrentTime();

    string insertionStatement = "INSERT INTO " + _tableName + " VALUES " + "(\"" + username + "\", \"" + cookie + "\", \"" + timestamp + "\");";

    char* err = nullptr;

    sqlite3_exec(_dbObject, insertionStatement.data(), nullptr, nullptr, &err);

    if (err) // TEST THIS MORE
    {
        cout << "here\n"; // REMOVE THIS
        cerr << err;
        sqlite3_free(err);
        err = nullptr;

        return -1;
    }

    return 1;
}

int CookieDB::RemoveSessionViaUsername(const std::string& username)
{
    string removalStatement = "DELETE FROM " + _tableName + " WHERE username='" + username + "';";

    char* err = nullptr;

    sqlite3_exec(_dbObject, removalStatement.data(), nullptr, nullptr, &err);

    if (err) // TEST THIS MORE
    {
        cout << "here\n"; // REMOVE THIS
        cerr << err;
        sqlite3_free(err);
        err = nullptr;

        return -1;
    }

    return 1;
}

int CookieDB::RemoveSessionViaCookie(const std::string& cookie)
{
    string removalStatement = "DELETE FROM " + _tableName + " WHERE cookie='" + cookie + "';";

    char* err = nullptr;

    sqlite3_exec(_dbObject, removalStatement.data(), nullptr, nullptr, &err);

    if (err) // TEST THIS MORE
    {
        cout << "here\n"; // REMOVE THIS
        cerr << err;
        sqlite3_free(err);
        err = nullptr;

        return -1;
    }

    return 1;
}

string CookieDB::GetUsername(const string& cookie)
{
    string sqlQuery = "SELECT * FROM " + _tableName + " WHERE cookie='" + cookie + "';";

    sqlite3_stmt* stmtObject;

    if (SQLITE_OK != sqlite3_prepare_v2(_dbObject, sqlQuery.data(), sqlQuery.length() + 1, &stmtObject, nullptr))
    {
        throw "Unable to prepare SQL statement.";
    }

    sqlite3_step(stmtObject);

    string name = (const char *) sqlite3_column_text(stmtObject, 0);

    sqlite3_finalize(stmtObject);

    return name;
}

bool CookieDB::CookieExists(const std::string& cookie)
{
    string sqlQuery = "SELECT COUNT(*) as count FROM " + _tableName + " WHERE cookie='" + cookie + "';";

    sqlite3_stmt* stmtObject;

    cout << sqlQuery << "\n";

    if (SQLITE_OK != sqlite3_prepare_v2(_dbObject, sqlQuery.data(), sqlQuery.length() + 1, &stmtObject, nullptr))
    {
        throw "Unable to prepare SQL statement.";
    }


    sqlite3_step(stmtObject);

    string countStr = (const char *)sqlite3_column_text(stmtObject, 0);
    int count = stoi(countStr);

    cout << "Count: " << count << '\n';

    sqlite3_finalize(stmtObject);

    return count >= 1;
}

int CookieDB::DestroyCookieTable()
{
    string query = "DROP TABLE IF EXISTS " + _tableName  + ";";

    char** err = nullptr;

    sqlite3_exec(_dbObject, query.data(), nullptr, nullptr, err);

    if (err) // TEST THIS MORE
    {
        cerr << err;
        sqlite3_free(err);
        err = nullptr;

        return -1;
    }

    cout << _tableName + " successfully destroyed.\n";

    return 1;
}

shared_ptr<vector<string>> CookieDB::ReadAll()
{
    auto list = make_shared<vector<string>>();

    string sqlQuery = "SELECT * from " + _tableName + ";";
    sqlite3_stmt* stmtObject;

    if (SQLITE_OK != sqlite3_prepare_v2(_dbObject, sqlQuery.data(), sqlQuery.length() + 1, &stmtObject, nullptr))
    {
        throw "Unable to prepare SQL statement.";
    }

    int stepReturnCode = sqlite3_step(stmtObject);

    while (stepReturnCode != SQLITE_DONE)
    {
        if (stepReturnCode == SQLITE_ERROR || stepReturnCode == SQLITE_MISUSE)
        {
            throw "Error code: " + stepReturnCode;
        }

        string username = (const char *) sqlite3_column_text(stmtObject, 0);
        string cookie = (const char *) sqlite3_column_text(stmtObject, 1);
        string timestamp = (const char *) sqlite3_column_text(stmtObject, 2);
        

        list->push_back(username + " " + cookie + " " + timestamp);

        stepReturnCode = sqlite3_step(stmtObject);
    }

    sqlite3_finalize(stmtObject);

    return list;
}

bool CookieDB::usernameExists(const std::string& username)
{
    string sqlQuery = "SELECT COUNT(*) as count FROM " + _tableName + " WHERE username='" + username + "';";

    sqlite3_stmt* stmtObject;

    if (SQLITE_OK != sqlite3_prepare_v2(_dbObject, sqlQuery.data(), sqlQuery.length() + 1, &stmtObject, nullptr))
    {
        throw "Unable to prepare SQL statement.";
    }

    sqlite3_step(stmtObject);

    int count = sqlite3_column_int(stmtObject, 0);

    sqlite3_finalize(stmtObject);

    return count >= 1;
}

int CookieDB::tableSetup()
{
    string tableStatement = "CREATE TABLE IF NOT EXISTS " +
                            _tableName +
                            " (username VARCHAR(255), cookie VARCHAR(255), timestamp VARCHAR(255), PRIMARY KEY (username));";

    char* err = nullptr;

    sqlite3_exec(_dbObject, tableStatement.data(), nullptr, nullptr, &err);

    if (err) // TEST THIS MORE
    {
        cout << "here\n"; // REMOVE THIS
        cerr << err;
        sqlite3_free(err);
        err = nullptr;

        return -1;
    }

    return 0;
}
