//  ChatroomManager.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Manages Chatroom objects.
//

#include "ChatroomManager.h"

using namespace std;

ChatroomManager* ChatroomManager::s_instance{ nullptr };

ChatroomManager& ChatroomManager::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new ChatroomManager();
    }

    return *s_instance;
}

ChatroomManager::ChatroomManager()
{
    _mapMutex = new mutex;
}

shared_ptr<Chatroom> ChatroomManager::CreateRoom(const string& hostCookie)
{
    _mapMutex->lock();

    int roomID = NewDistinctRoomID();

    auto room = make_shared<Chatroom>(roomID, hostCookie, SessionManager::Instance().GetUser(hostCookie));

    _chatrooms[roomID] = room;

    _mapMutex->unlock();

    return room;
}

void ChatroomManager::PrintChatrooms()
{
    cout << "Chatrooms Count: " << _chatrooms.size() << '\n';

    for (auto item : _chatrooms)
    {
        cout << "Chatroom ID: " << item.second->GetID() << " Host: " << item.second->GetHostUsername() << '\n';
    }
}

const string& ChatroomManager::ConstructGridElements(string& str)
{
    for (auto item : _chatrooms)
    {
        auto room = item.second;

        str += ConstructGridElement(room);
    }

    return str;
}

string ChatroomManager::ConstructGridElement(shared_ptr<Chatroom> room)
{
    string gridElement{ "<div class=\"grid-element\"><div class=\"room-heading\">room "  };
    gridElement += to_string(room->GetID());

    gridElement += "</div><div class=\"room-users\">Users: ";
    gridElement += to_string(room->GetUserCount()) + "/6";

    gridElement += "<br>" + room->GetHostUsername() + "(HOST)";

    auto usernames = room->GetUsernames();

    for (const string& str : *usernames)
    {
        gridElement += "<br>" + str;
    }

    gridElement += "</div><div class=\"room-join\"><form method=\"GET\" action=\"/Rooms/";
    gridElement += to_string(room->GetID());
    gridElement += "\"><button type=\"submit\">Join</button></form></div></div>";

    cout << gridElement << '\n';

    return gridElement;
}

int ChatroomManager::NewDistinctRoomID()
{
    // _mapMutex->lock();

    static const int MAX_ROOM_NUMBER = 100;

    int newID = RandomInteger(0, MAX_ROOM_NUMBER);

    while (_chatrooms.count(newID) == 1)
    {
        newID = RandomInteger(0, MAX_ROOM_NUMBER + 1);
    }

    // _mapMutex->unlock();
    
    return newID;
}


