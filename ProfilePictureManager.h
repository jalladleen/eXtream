//  SessionManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Manages logged in user sessions.
//

#ifndef PROFILE_PICTURE_MANAGER_H
#define PROFILE_PICTURE_MANAGER_H

#include <iostream>
#include <string>
// #include <map>
// #include <utility>
#include <memory>

#include "User.h"
#include "ImageDB.h"

/// @brief Manages active sessions for connected users.
class ProfilePictureManager
{
public:
    /// @brief Singleton design pattern for SessionManager.
    /// @return A reference to the instance of SessionManager.
    static ProfilePictureManager& Instance();

    /// @brief Cleans up. Destroy the associated cookie table.
    ~ProfilePictureManager();
    
    int AddNewUser(const std::string& username);

    int UpdateProfilePic(const std::string& username, const std::string& url);

    std::string GetUserProfilePic(const std::string& username);

protected:
    ProfilePictureManager();

private:
    // std::map<std::string, std::shared_ptr<User>> _activeSessions{};

    // Singleton
    static ProfilePictureManager* s_instance;

    const std::string PROFILEPICTURE_TABLE_NAME = "images";

    // Prevent copying and assignment
    ProfilePictureManager(const ProfilePictureManager& other) = delete;
    ProfilePictureManager& operator=(const ProfilePictureManager& other) = delete;

};

#endif
