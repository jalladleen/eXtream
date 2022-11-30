//  ChatroomManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//
//  Manages Chatroom objects.
//

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

/// @brief Manages the Chatrooms of the app.
/// Manages the Chatrooms of the app.
/// @author Balaaj Arbab
class ChatroomManager
{
public:
    /// @brief Singleton design pattern for ChatroomManager
    /// Singleton design pattern for ChatroomManager
    /// @return A reference to the instance of ChatroomManager
    static ChatroomManager& Instance();

    /// @brief Initializes the ChatroomManager object.
    /// Initializes the ChatroomManager object.
    ChatroomManager();

    /// @brief Creates a new room.
    /// Creates a new room.
    /// @param hostCookie Cookie associated with user trying to create a room.
    /// @return a shared_ptr to the created room.
    std::shared_ptr<Chatroom> CreateRoom(const std::string& hostCookie);

    /// @brief Display all chatrooms with data on the console.
    void PrintChatrooms();

    /// @brief Forms the HTML representation of the grid of chatrooms on front page.
    /// Forms the HTML representation of the grid of chatrooms on front page.
    /// @param str string to store HTML representation to. Passed by reference.
    /// @return const reference to HTML representation string.
    const std::string& ConstructGridElements(std::string& str);

    /// @brief Gets the chatroom with associated id.
    /// Gets the chatroom with associated id.
    /// @param id Room id.
    /// @return A shared_ptr to the Chatroom object.
    std::shared_ptr<Chatroom> GetChatroom(int id){ return _chatrooms[id]; }


private:
    static ChatroomManager* s_instance;

    std::map<int, std::shared_ptr<Chatroom>> _chatrooms;

    std::mutex* _mapMutex;

    std::string ConstructGridElement(std::shared_ptr<Chatroom> room);

    int NewDistinctRoomID();

};

#endif
