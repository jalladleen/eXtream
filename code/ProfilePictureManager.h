//  ProfilePictureManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-11-25.
//
//  Manages Profile Picture access for users.
//

#ifndef PROFILE_PICTURE_MANAGER_H
#define PROFILE_PICTURE_MANAGER_H

#include <iostream>
#include <string>
// #include <map>
// #include <utility>
#include <memory>

#include "ImageDB.h"

/// @brief Manages Profile Picture access for users.
/// Manages Profile Picture access for users.
/// @author Balaaj Arbab
class ProfilePictureManager
{
public:
    /// @brief Singleton design pattern for ProfilePictureManager.
    /// Allows access to a singular instance of the ProfilePictureManager across the project.
    /// @return A reference to the instance of ProfilePictureManager.
    static ProfilePictureManager& Instance();

    /// @brief Cleans up. 
    /// Cleans up. 
    ~ProfilePictureManager();
    
    /// @brief Adds a new user to the image database table with the default profile pic URL.
    /// Adds a new user to the image database table with the default profile pic URL. Used when a new account is created.
    /// @param username The name of the new user.
    /// @return 1 if the operation was successful, not 1 if not.
    int AddNewUser(const std::string& username);

    /// @brief Updates the profile pic URL stored for the given user in the image database table.
    ///  Updates the profile pic URL stored for the given user in the image database table.
    /// @param username The name of the user to update.
    /// @param url The URL of the new image.
    /// @return 1 if the operation was successful, not 1 if not.
    int UpdateProfilePic(const std::string& username, const std::string& url);

    /// @brief Gets the URL of the image associated with the given user.
    /// Gets the URL of the image associated with the given user.
    /// @param username The name of the user whose profile picture to get.
    /// @return The URL of the profile picture for the user.
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
