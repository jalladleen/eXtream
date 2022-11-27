//  ImageDB.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to the cookie database table for the app.
//

#include "ImageDB.h"

using namespace std;

static const char* DB_PATH{ "./database.db" };

ImageDB::ImageDB(const string& tableName)
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

ImageDB::~ImageDB()
{
    sqlite3_close(_dbObject);
    cout << "Image database successfully closed.\n";
}

int ImageDB::AddNewUser(const string& username)
{
    string insertionStatement = "INSERT INTO " + _tableName + " VALUES " + "(\"" + username + "\", 'images/blank.webp');";

    char* err = nullptr;

    sqlite3_exec(_dbObject, insertionStatement.data(), nullptr, nullptr, &err);

    if (err) // TEST THIS MORE
    {
        cout << "added user to imagedb\n"; // REMOVE THIS
        cerr << err;
        sqlite3_free(err);
        err = nullptr;

        return -1;
    }

    return 1;
}

int ImageDB::UpdateProfilePic(const string& username, const string& url)
{
    string updateStatement = "UPDATE " + _tableName + " SET imageurl='" + url + "' WHERE username='" + username + "';";

    char* err = nullptr;

    sqlite3_exec(_dbObject, updateStatement.data(), nullptr, nullptr, &err);

    if (err) // TEST THIS MORE
    {
        cout << "updated user pic in imagedb\n"; // REMOVE THIS
        cerr << err;
        sqlite3_free(err);
        err = nullptr;

        return -1;
    }

    return 1;
}

string ImageDB::GetUserProfilePic(const string& username)
{
    string sqlQuery = "SELECT imageurl FROM " + _tableName + " WHERE username='" + username + "';";

    sqlite3_stmt* stmtObject;

    if (SQLITE_OK != sqlite3_prepare_v2(_dbObject, sqlQuery.data(), sqlQuery.length() + 1, &stmtObject, nullptr))
    {
        throw "Unable to prepare SQL statement.";
    }

    sqlite3_step(stmtObject);

    string url = (const char *) sqlite3_column_text(stmtObject, 0);

    sqlite3_finalize(stmtObject);

    return url;
}

int ImageDB::tableSetup()
{
    string tableStatement = "CREATE TABLE IF NOT EXISTS " +
                            _tableName +
                            " (username VARCHAR(255), imageurl VARCHAR(255), PRIMARY KEY (username));";

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
