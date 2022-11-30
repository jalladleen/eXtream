//  FriendsListDB.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-11-25.
//
//  An interface to the friends list database table for the app.
//

#include "FriendsListDB.h"

using namespace std;

static const char* DB_PATH{ "./database.db" };

FriendsListDB::FriendsListDB(const string& tableName)
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

FriendsListDB::~FriendsListDB()
{
    sqlite3_close(_dbObject);
    cout << "Cookie database successfully closed.\n";
}

int FriendsListDB::AddFriend(const string& username, const string& friendUsername)
{
    if (RelationshipExists(username, friendUsername)) return -1;
    if (LoginDB {"logintable"}.checkUsername(friendUsername) != 1) return -1;
    if (username == friendUsername) return -1;

    string insertionStatement = "INSERT INTO " + _tableName + " VALUES " + "(\"" + username + "\", \"" + friendUsername + "\");";

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

bool FriendsListDB::RelationshipExists(const string& username, const string& friendUsername)
{
    string sqlQuery = "SELECT COUNT(*) FROM " + _tableName + " WHERE username='" + username + "' AND friend='" + friendUsername + "';";

    sqlite3_stmt* stmtObject;


    if (SQLITE_OK != sqlite3_prepare_v2(_dbObject, sqlQuery.data(), sqlQuery.length() + 1, &stmtObject, nullptr))
    {
        throw "Unable to prepare SQL statement.";
    }

    sqlite3_step(stmtObject);

    string countStr = (const char *)sqlite3_column_text(stmtObject, 0);
    int count = stoi(countStr);

    sqlite3_finalize(stmtObject);

    return count >= 1;
}

std::shared_ptr<std::vector<std::string>> FriendsListDB::GetAllFriends(const std::string& username)
{
    auto list = make_shared<vector<string>>();

    string sqlQuery = "SELECT friend from " + _tableName + " WHERE username='" + username + "';";
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

        string friendUsername = (const char *) sqlite3_column_text(stmtObject, 0);
        
        list->push_back(friendUsername);

        stepReturnCode = sqlite3_step(stmtObject);
    }

    sqlite3_finalize(stmtObject);

    return list;
}


int FriendsListDB::tableSetup()
{
    string tableStatement = "CREATE TABLE IF NOT EXISTS " +
                            _tableName +
                            " (username VARCHAR(255), friend VARCHAR(255));";

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
