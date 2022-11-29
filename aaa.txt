//
//  LoginDB.cpp
//  CS 3307 Group Project
//
//  Created by Daniel Herbert on 2022-10-31.
//

#include "LoginDB.hpp"
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

LoginDB::LoginDB(const string& tableName)
: _tableName{ tableName }
{
    char *zErrMsg = 0;
    int open;
    int rc;
    string query = "create table if not exists " + _tableName + " (username varchar(255), password varchar(255), u_id int);";
    
    const char *sql = query.c_str();
    
    open = sqlite3_open("database.db", &db);
    
    if (open) {
        printf("Can't open database\n");
    }
    else {
        printf("Database opened succesfully\n");
    }
    
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK) {
        cout << "Error creating table";
    } else {
        cout << "Table created successfully\n";
    }
}

LoginDB::~LoginDB()
{
    sqlite3_close(db);
    cout << "Database successfully closed.\n";
}

int LoginDB::verifyLogin(string username, string password) {
    vector<string> gettingUserList = getUserDatabase();
    string delimiter = "|";
    for (int i = 0; i < gettingUserList.size(); i++) {
        string temp = gettingUserList.at(i);
        string token = temp.substr(0, temp.find(delimiter));
        //printf("Token: %s\n", token.c_str());
        if (token == username) {
            temp.erase(0, temp.find(delimiter) + delimiter.length());
            string pw = temp.substr(0, temp.find(delimiter));
            if (pw == password) {
                printf("Login Credentials Provided are correct!\n");
                return 1;
            }
        }
    }
    printf("Login Credentials Provided are incorrect!\n");
    return 0;
}

int LoginDB::changePassword(string username, string np) {
    string query = "update " + _tableName + " set password = \'" + np + "\'" +  " where username = \'" + username + "\'";
    char *zErrMsg = 0;
    int rc;
    const char *sql = query.c_str();
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        cout << "Error updating password\n";
    } else {
        cout << "Password updated successfully\n";
    }
    //printf("%s\n", query.c_str());
    
    /*vector<string> gettingUserList = getUserDatabase();
    string delimiter = "|";
    for (int i = 0; i < gettingUserList.size(); i++) {
        string temp = gettingUserList.at(i);
        string token = temp.substr(0, temp.find(delimiter));
        //printf("Token: %s\n", token.c_str());
        if (token == username) {
            
            return 1;
        }
    }*/
    return 1;
}

int LoginDB::createAccount(string u, string p) 
{

    if (checkUsername(u) == 1)
    {
        cout << "Username already exists.\n";

        return 0;
    }

    int rc;
    int random = rand()%1000 + 1;
    string str = to_string(random);
    string query = "insert into " + _tableName + " values (\""+ u +  "\" , \"" + p + "\" , \"" + str + "\");";
    const char *sql = query.c_str();
    printf("%s\n", sql);
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK) {
        cout << "Error inserting records\n";
    } else {
        cout << "Records inserted successfully\n";
    }
    return 1;
}

int LoginDB::checkUsername(string username) {
    vector<string> gettingUserList = getUserDatabase();
    string delimiter = "|";
    for (int i = 0; i < gettingUserList.size(); i++) {
        string temp = gettingUserList.at(i);
        string token = temp.substr(0, temp.find(delimiter));
        //printf("Token: %s\n", token.c_str());
        if (token == username) {
            printf("This username already exists\n");
            return 1;
        }
    }
    return 0;
}

int LoginDB::checkPW(string ePw) {
    return 1;
}

vector <string> LoginDB::getUserDatabase() {
    //Creating an empty vector
    vector <string> userLog;
    //SQL statement to retrieve messages for the app
    string query = "select * from " + _tableName;
    string row;
    sqlite3_stmt* stmt;
    const char *sql = query.c_str();
    int len = strlen(sql);
    int ret = sqlite3_prepare_v2(db, sql, len, &stmt, NULL);
    if (ret != SQLITE_OK) {
        cout << "Error preparing statement records\n";
    }
    int r = sqlite3_step(stmt);
    //While loop that inserts messages into vector as long as there are still messages
    while (r == SQLITE_ROW) {
        string messageCol1 = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        string messageCol2 = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        string messageCol3 = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        row = messageCol1 + "|" + messageCol2 + "|" +messageCol3;
        userLog.push_back(row);
        r = sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    return userLog;
}

