//  SongManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-11-25.
//
//  Manages Song uploads for the app.
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

/// @brief Manages the Song uploads of the app.
/// @author Balaaj Arbab
class SongManager
{
public:
    /// @brief Singleton design pattern for SongManager
    /// Allows access to a singular instance of SongManager across the project.
    /// @return A reference to the instance of SongManager
    static SongManager& Instance();

    /// @brief Constructs the SongManager.
    SongManager();

    /// @brief Destroys the SongManager object and does any necessary cleanup.
    /// Removes all songs in the song directory that were uploaded during the current run of the program. Leaves default_song.mp3 alone.
    ~SongManager();

    /// @brief Log that a song has been uploaded.
    /// Keeps track of uploaded songs.
    /// @param songName Name of the song that was uploaded.
    /// @return 1 if the operation was successful, not 1 if not.
    int AddSong(std::string songName);

private:
    static SongManager* s_instance;

    const std::string SONG_DIRECTORY{ "songs/" };

    std::vector<std::string> _songNames{ };

};

#endif
