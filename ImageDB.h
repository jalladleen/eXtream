//  CookieDB.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to the cookie database table for the app.
//

#ifndef IMAGE_DB_H
#define IMAGE_DB_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <sqlite3.h>
#include <string.h>

#include "Utility.h"

/// @brief Provides access to the Cookie Table for the app.
class ImageDB
{
public:
    /// @brief Initializes the object and acquires a database handle.
    /// @param tableName Table name of the cookie table.
    ImageDB(const std::string& tableName);

    /// @brief Safely closes the Database handle and cleans up.
    ~ImageDB();

    int AddNewUser(const std::string& username);

    int UpdateProfilePic(const std::string& username, const std::string& url);

    std::string GetUserProfilePic(const std::string& username);

private:
    const std::string _tableName;
    sqlite3* _dbObject;

    int tableSetup();
};

#endif
