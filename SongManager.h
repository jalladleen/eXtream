//  ChatroomManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Manages Chatroom objects.
//

#ifndef SONG_MANAGER_H
#define SONG_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <fstream>
#include <stdlib.h>

#include "httplib.h"
#include "Chatroom.h"
#include "Utility.h"
#include "SessionManager.h"

/// @brief Manages the Chatrooms of the app.
class SongManager
{
public:
    /// @brief Singleton design pattern for ChatroomManager
    /// @return A reference to the instance of ChatroomManager
    static SongManager& Instance();


    SongManager();
    ~SongManager();

    int AddSong(std::string songName);


private:
    static SongManager* s_instance;

    const std::string SONG_DIRECTORY{ "songs/" };

    std::vector<std::string> _songNames{ };

};

#endif
