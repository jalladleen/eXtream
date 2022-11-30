//  ProfilePictureManager.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-11-25.
//
//  Manages Profile Picture access for users.
//

#include "ProfilePictureManager.h"

using namespace std;

ProfilePictureManager* ProfilePictureManager::s_instance{ nullptr };

    // Singleton
ProfilePictureManager& ProfilePictureManager::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new ProfilePictureManager();
    }

    return *s_instance;
}


ProfilePictureManager::~ProfilePictureManager()
{}

int ProfilePictureManager::AddNewUser(const string& username)
{
    ImageDB imageDB{ PROFILEPICTURE_TABLE_NAME };

    return imageDB.AddNewUser(username);
}

int ProfilePictureManager::UpdateProfilePic(const string& username, const string& url)
{
    ImageDB imageDB{ PROFILEPICTURE_TABLE_NAME };

    cout << username << " just updated their profile picture!\n";

    return imageDB.UpdateProfilePic(username, url);

}

string ProfilePictureManager::GetUserProfilePic(const string& username)
{
    ImageDB imageDB{ PROFILEPICTURE_TABLE_NAME };

    if (username.substr(0, 5) == "Guest")
    {
        return "images/blank.webp";
    }

    return imageDB.GetUserProfilePic(username);
}

ProfilePictureManager::ProfilePictureManager()
{}
