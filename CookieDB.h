//  CookieDB.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to the cookie database table for the app.
//

#ifndef COOKIE_DB_H
#define COOKIE_DB_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sqlite3.h>
#include <string.h>

#include "Utility.h"

/// @brief Provides access to the Cookie Table for the app.
class CookieDB
{
public:
    /// @brief Initializes the object and acquires a database handle.
    /// @param tableName Table name of the cookie table.
    CookieDB(const std::string& tableName);

    /// @brief Safely closes the Database handle and cleans up.
    ~CookieDB();

    /// @brief Adds a session entry to DB.
    /// @param username Username associated with user.
    /// @param cookie Cookie for the current session of the user.
    /// @return 1 if successful, -1 if not.
    int AddSession(const std::string& username, const std::string& cookie);

    /// @brief Removes a session from the DB via username.
    /// @param username Username string of the user whose session to remove.
    /// @return 1 if successful, -1 if not.
    int RemoveSessionViaUsername(const std::string& username);

    
    /// @brief Removes a session from the DB via cookie.
    /// @param cookie Cookie string of the user whose session to remove.
    /// @return 1 if successful, -1 if not.
    int RemoveSessionViaCookie(const std::string& cookie);

    /// @brief Gets the username associated with the user with given cookie.
    /// @param cookie Cookie string
    /// @return Username of user with cookie
    std::string GetUsername(const std::string& cookie);

    /// @brief Checks whether a given cookie exists in the DB.
    /// @param cookie Cookie string to check.
    /// @return bool
    bool CookieExists(const std::string& cookie);

    /// @brief DROPS the cookie table. Used for cleanup.
    /// @return 1 if successful, -1 if not.
    int DestroyCookieTable();

    /// @brief Checks whether a given username exists in the DB.
    /// @param username username string to check.
    /// @return bool
    bool usernameExists(const std::string& username);

    /// @brief String representation for all rows in the cookie table.
    /// @return shared_ptr to a vector of the strings.
    std::shared_ptr<std::vector<std::string>> ReadAll();

private:
    const std::string _tableName;
    sqlite3* _dbObject;

    int tableSetup();
};

#endif
