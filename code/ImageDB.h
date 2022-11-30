//  ImageDB.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-11-25.
//
//  An interface to the image database table for the app.
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

/// @brief Provides access to the Image Table for the app.
/// @author Balaaj Arbab
class ImageDB
{
public:
    /// @brief Initializes the object and acquires a database handle.
    /// @param tableName Table name of the Image table.
    ImageDB(const std::string& tableName);

    /// @brief Safely closes the Database handle and cleans up.
    ~ImageDB();

    /// @brief Adds a new user to the image database table with the default profile pic URL.
    /// Adds a new user to the image database table with the default profile pic URL. Used when a new account is created.
    /// @param username The name of the new user.
    /// @return 1 if the operation was successful, not 1 if not.
    int AddNewUser(const std::string& username);

    /// @brief Updates the profile pic URL stored for the given user in the image database table.
    /// @param username The name of the user to update.
    /// @param url The URL of the new image.
    /// @return 1 if the operation was successful, not 1 if not.
    int UpdateProfilePic(const std::string& username, const std::string& url);

    /// @brief Gets the URL of the image associated with the given user.
    /// @param username The name of the user whose profile picture to get.
    /// @return The URL of the profile picture for the user.
    std::string GetUserProfilePic(const std::string& username);

private:
    const std::string _tableName;
    sqlite3* _dbObject;

    int tableSetup();
};

#endif
