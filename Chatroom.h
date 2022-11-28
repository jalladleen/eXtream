//  Chatroom.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Represents the Chatroom that users can connect to.
//

#ifndef CHATROOM_H
#define CHATROOM_H

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <mutex>

#include "Stopwatch.h"
#include "ProfilePictureManager.h"

/// @brief Represents a Chatroom that is a conduit between users.
class Chatroom
{
public:
    /// @brief Creates a chatroom.
    /// @param roomID The id assigned to the room.
    /// @param hostCookie Cookie associated with creator of room.
    Chatroom(int roomID, const std::string& hostCookie);

    /// @brief Creates a chatroom
    /// @param roomID The id assigned to the room.
    /// @param hostCookie Cookie associated with creator of room.
    /// @param hostUsername Username associated with creator of room.
    Chatroom(int roomID, const std::string& hostCookie, const std::string& hostUsername);

    ~Chatroom();

    /// @brief Adds a user who has tried join the room.
    /// @param cookie Cookie associated with joining user.
    /// @param username Username associated with joining user.
    /// @return Whether the user was successfully added or not.
    bool AddUser(std::string cookie, std::string username);

    /// @brief Removes a user from the room.
    /// @param cookie Cookie associated with leaving user.
    /// @return Whether the user was sucessfully removed or not.
    bool RemoveUser(std::string cookie);

    /// @brief A list of all currently joined user's usernames.
    /// @return vector<string> of usernames.
    std::shared_ptr<std::vector<std::string>> GetUsernames(bool includeHost = false);

    /// @brief Gets the room's id.
    /// @return Room id integer.
    int GetID(){ return _roomID; }

    /// @brief Gets cookie associated with room creator.
    /// @return Host cookie.
    std::string GetHostCookie() { return _hostCookie; }

    /// @brief Gets username associated with room creator.
    /// @return Host username.
    std::string GetHostUsername() { return _hostUsername; }

    /// @brief Currently connected user count.
    /// @return User count integer.
    int GetUserCount() { return _connectedCookies.size() + 1; }

    void FormUserHTML(std::string& str);

    std::string GetCurrentSongName() { return _currentSongName; }
    std::string GetCurrentSongUploader() { return _currentSongUploader; }

    void SetCurrentSongName(std::string newSong) { _currentSongName = newSong; }
    void SetCurrentSongUploader(std::string newUploader) { _currentSongUploader = newUploader; }  

    enum State
    {
        Paused,
        Playing
        
    };

    Chatroom::State GetState() { return _state; }
    double GetSongTime() { return _songStartTime + _songTimer.TotalElapsed(); };

    void Play(double startTime);
    void Pause();
    void Reset();

private:
    int _roomID;
    std::string _hostCookie;
    std::string _hostUsername;

    std::string _currentSongName { "default_song.mp3" };
    std::string _currentSongUploader { "Server" };
    Chatroom::State _state;
    Stopwatch _songTimer{ };
    double _songStartTime{ 0 };
    
    std::map<std::string, std::string> _connectedCookies;

    std::mutex* _setMutex;

};

#endif
