//  CookieDB.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to the cookie database table for the app.
//

#ifndef FRIENDSLIST_DB_H
#define FRIENDSLIST_DB_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sqlite3.h>
#include <string.h>

#include "Utility.h"
#include "LoginDB.hpp"

/// @brief Provides access to the Cookie Table for the app.
class FriendsListDB
{
public:
    /// @brief Initializes the object and acquires a database handle.
    /// @param tableName Table name of the cookie table.
    FriendsListDB(const std::string& tableName);

    /// @brief Safely closes the Database handle and cleans up.
    ~FriendsListDB();

    int AddFriend(const std::string& username, const std::string& friendUsername);

    /// @brief String representation for all rows in the cookie table.
    /// @return shared_ptr to a vector of the strings.
    std::shared_ptr<std::vector<std::string>> GetAllFriends(const std::string& username);

private:
    const std::string _tableName;
    sqlite3* _dbObject;

    bool RelationshipExists(const std::string& username, const std::string& friendUsername);

    int tableSetup();
};

#endif
