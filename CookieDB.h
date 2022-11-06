#ifndef COOKIE_DB_H
#define COOKIE_DB_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sqlite3.h>
#include <string.h>

#include "Utility.h"

class CookieDB
{
public:
    CookieDB(const std::string& tableName);

    ~CookieDB();

    int AddSession(const std::string& username, const std::string& cookie);

    int RemoveSessionViaUsername(const std::string& username);
    int RemoveSessionViaCookie(const std::string& cookie);

    std::string GetUsername(const std::string& cookie);

    bool CookieExists(const std::string& cookie);

    int DestroyCookieTable();

    bool usernameExists(const std::string& username);

    std::shared_ptr<std::vector<std::string>> ReadAll();

private:
    const std::string _tableName;
    sqlite3* _dbObject;

    int tableSetup();
};

#endif
