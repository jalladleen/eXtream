//  FriendManager.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//
//  Manages Friend connections between users.
//

#include "FriendManager.h"

using namespace std;

FriendManager* FriendManager::s_instance{ nullptr };

    // Singleton
FriendManager& FriendManager::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new FriendManager();
    }

    return *s_instance;
}


FriendManager::~FriendManager()
{}

int FriendManager::AddFriend(const std::string& username, const std::string& friendUsername)
{
    FriendsListDB friendDB { FRIENDS_TABLE_NAME };

    int statuscode = friendDB.AddFriend(username, friendUsername);

    if (statuscode == 1) cout << username << " Added Friend: " << friendUsername << '\n';
    else cout << username << " Was Not Able to Add Friend: " << friendUsername << '\n';

    return statuscode;
}

std::shared_ptr<std::vector<std::string>> FriendManager::GetAllFriends(const std::string& username)
{
    FriendsListDB friendDB { FRIENDS_TABLE_NAME };

    return friendDB.GetAllFriends(username);
}

void FriendManager::GetHTMLRepresentation(const string& username, string& str)
{
    auto friends = GetAllFriends(username);

    for (auto fr : *friends)
    {
        str += "<div class='friend'><img src='" + ProfilePictureManager::Instance().GetUserProfilePic(fr) + "' alt='pic' width='48' height='48' class='rounded-circle me-2 border border-dark'>";
        str += "<strong style='white-space:pre;'> ";
        str += fr;
        str += "</strong></div>";
    }
}

FriendManager::FriendManager()
{}

