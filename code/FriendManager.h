//  FriendManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//
//  Manages Friend connections between users.
//

#ifndef FRIEND_MANAGER_H
#define FRIEND_MANAGER_H

#include <iostream>
#include <string>
#include <memory>

#include "FriendsListDB.h"
#include "ProfilePictureManager.h"

/// @brief Manages Friend connections between users.
/// @author Balaaj Arbab
class FriendManager
{
public:
    /// @brief Singleton design pattern for FriendManager.
    /// Allows access to a singular instance FriendManager across the project.
    /// @return A reference to the instance of FriendManager.
    static FriendManager& Instance();

    /// @brief 
    ~FriendManager();
    
    /// @brief Adds a friend relationship between 2 users.
    /// Adds a friend relationship between 2 users and stores it in the friends database table.
    /// @param username first user
    /// @param friendUsername The user to add as friend to first user.
    /// @return 1 is the operation was successful, not 1 if not.
    int AddFriend(const std::string& username, const std::string& friendUsername);

    /// @brief Returns the username of all usernames that are friends with the input user.
    /// @param username The input user.
    /// @return A shared_ptr to a list of friend usernames.
    std::shared_ptr<std::vector<std::string>> GetAllFriends(const std::string& username);

    /// @brief Creates the HTML representation of all friends of a user.
    /// Creates the HTML representation of all friends of a user and stores it in str, to be used for the friends list component of the front page.
    /// @param username The input user.
    /// @param str A reference to a string where the HTML will be stored.
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
