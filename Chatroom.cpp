#include "Chatroom.h"

using namespace std;

Chatroom::Chatroom(int roomID, const string& hostCookie)
: _roomID{ roomID }, _hostCookie{ hostCookie }
{
    _setMutex = new mutex();
}

Chatroom::Chatroom(int roomID, const string& hostCookie, const string& hostUsername)
: _roomID{ roomID }, _hostCookie{ hostCookie }, _hostUsername{ hostUsername }
{
    _setMutex = new mutex();
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

shared_ptr<vector<string>> Chatroom::GetUsernames()
{
    auto list = make_shared<vector<string>>();

    for (auto item : _connectedCookies)
    {
        list->push_back(item.second);
    }

    return list;
}


