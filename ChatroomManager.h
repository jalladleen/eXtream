#ifndef CHATROOM_MANAGER_H
#define CHATROOM_MANAGER_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <mutex>

#include "Chatroom.h"
#include "Utility.h"
#include "SessionManager.h"

class ChatroomManager
{
public:
    static ChatroomManager& Instance();

    ChatroomManager();

    std::shared_ptr<Chatroom> CreateRoom(const std::string& hostCookie);

    void PrintChatrooms();

    const std::string& ConstructGridElements(std::string& str);

    std::shared_ptr<Chatroom> GetChatroom(int id){ return _chatrooms[id]; }


private:
    static ChatroomManager* s_instance;

    std::map<int, std::shared_ptr<Chatroom>> _chatrooms;

    std::mutex* _mapMutex;

    std::string ConstructGridElement(std::shared_ptr<Chatroom> room);

    int NewDistinctRoomID();

};

#endif
