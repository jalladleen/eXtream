//  Chatroom.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//
//  Represents the Chatroom that users can connect to.
//

#include "Chatroom.h"

using namespace std;

Chatroom::Chatroom(int roomID, const string& hostCookie)
: _roomID{ roomID }, _hostCookie{ hostCookie }
{
    _setMutex = new mutex();
    cout << "Chatroom with ID: " << roomID << " created by cookie: " << hostCookie << '\n';
}

Chatroom::Chatroom(int roomID, const string& hostCookie, const string& hostUsername)
: _roomID{ roomID }, _hostCookie{ hostCookie }, _hostUsername{ hostUsername }
{
    _setMutex = new mutex();
    cout << "Chatroom with ID: " << roomID << " created by: " << hostUsername << '\n';
}

Chatroom::~Chatroom()
{
    delete _setMutex;
}

bool Chatroom::AddUser(string cookie, string username)
{
    _setMutex->lock();

    if (_connectedCookies.count(cookie) == 1)
    {
        return false;
    }

    _connectedCookies[cookie] = username;

    _setMutex->unlock();

    return true;
}

bool Chatroom::RemoveUser(string cookie)
{
    _setMutex->lock();

    _connectedCookies.erase(cookie);

    _setMutex->unlock();

    return true;
}

shared_ptr<vector<string>> Chatroom::GetUsernames(bool includeHost)
{
    auto list = make_shared<vector<string>>();

    if (includeHost) list->push_back(_hostUsername);

    for (auto item : _connectedCookies)
    {
        list->push_back(item.second);
    }

    return list;
}

void Chatroom::FormUserHTML(string& str)
{
    auto users = GetUsernames(true);

    for (auto user : *users)
    {
        str += "<li class='active'><a href='#'><div class='d-flex bd-highlight'><div class='img_cont'><img src='/";
        str += ProfilePictureManager::Instance().GetUserProfilePic(user);
        str += "' class='rounded-circle user_img border border-dark'><span class='online_icon'></span></div><div class='user_info'><span>";
        str += user;

        if (user == _hostUsername)
        {
            str += " (HOST)";
        }

        str += "</span><p>Online</p></div></div></a></li>";                                 
    }

}

void Chatroom::Play(double startTime)
{
    _state = Chatroom::State::Playing;

    _songStartTime = startTime;
    
    _songTimer.Start();
}

void Chatroom::Pause()
{
    _state = Chatroom::State::Paused;

    // _songTimer.Stop();
    _songTimer.Reset();
}

void Chatroom::Reset()
{
    _state = Chatroom::State::Paused;

    _songStartTime = 0;

    _songTimer.Reset();
}





