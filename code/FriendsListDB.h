//  FriendsListDB.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-11-25.
//
//  An interface to the friends list database table for the app.
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

/// @brief Provides access to the Friends List Table for the app.
/// Provides access to the Friends List Table for the app.
/// @author Balaaj Arbab
class FriendsListDB
{
public:
    /// @brief Initializes the object and acquires a database handle.
    /// Initializes the object and acquires a database handle.
    /// @param tableName Table name of the Friends List table.
    FriendsListDB(const std::string& tableName);

    /// @brief Safely closes the Database handle and cleans up.
    /// Safely closes the Database handle and cleans up.
    ~FriendsListDB();

    /// @brief Adds a friend relationship between 2 users.
    /// Adds a friend relationship between 2 users and stores it in the friends database table.
    /// @param username first user
    /// @param friendUsername The user to add as friend to first user.
    /// @return 1 is the operation was successful, not 1 if not.
    int AddFriend(const std::string& username, const std::string& friendUsername);

    /// @brief Returns the username of all usernames that are friends with the input user.
    /// Returns the username of all usernames that are friends with the input user.
    /// @param username The input user.
    /// @return A shared_ptr to a list of friend usernames.
    std::shared_ptr<std::vector<std::string>> GetAllFriends(const std::string& username);

private:
    const std::string _tableName;
    sqlite3* _dbObject;

    bool RelationshipExists(const std::string& username, const std::string& friendUsername);

    int tableSetup();
};

#endif
