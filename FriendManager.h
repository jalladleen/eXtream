//  SessionManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Manages logged in user sessions.
//

#ifndef FRIEND_MANAGER_H
#define FRIEND_MANAGER_H

#include <iostream>
#include <string>
#include <memory>

#include "FriendsListDB.h"
#include "ProfilePictureManager.h"

/// @brief Manages active sessions for connected users.
class FriendManager
{
public:
    /// @brief Singleton design pattern for SessionManager.
    /// @return A reference to the instance of SessionManager.
    static FriendManager& Instance();

    /// @brief Cleans up. Destroy the associated cookie table.
    ~FriendManager();
    
    int AddFriend(const std::string& username, const std::string& friendUsername);

    std::shared_ptr<std::vector<std::string>> GetAllFriends(const std::string& username);

    void GetHTMLRepresentation(const std::string& username, std::string& str);


protected:
    FriendManager();

private:
    // std::map<std::string, std::shared_ptr<User>> _activeSessions{};

    // Singleton
    static FriendManager* s_instance;

    const std::string FRIENDS_TABLE_NAME = "friends";

    // Prevent copying and assignment
    FriendManager(const FriendManager& other) = delete;
    FriendManager& operator=(const FriendManager& other) = delete;

};

#endif
