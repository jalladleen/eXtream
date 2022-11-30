//  Chatroom.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
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
/// Represents a Chatroom that connects Users together, stores the currently selected song and its controls.
/// @author Balaaj Arbab
class Chatroom
{
public:
    /// @brief Creates a chatroom.
    /// Creates a chatroom with roomID and hostCookie set.
    /// @param roomID The id assigned to the room.
    /// @param hostCookie Cookie associated with creator of room.
    Chatroom(int roomID, const std::string& hostCookie);

    /// @brief Creates a chatroom.
    /// Creates a chatroom with roomID, hostCookie, and hostUsername set.
    /// @param roomID The id assigned to the room.
    /// @param hostCookie Cookie associated with creator of room.
    /// @param hostUsername Username associated with creator of room.
    Chatroom(int roomID, const std::string& hostCookie, const std::string& hostUsername);

    /// @brief Destroys a chatroom and does necessary clean up.
    /// Destroys a chatroom and does necessary clean up.
    ~Chatroom();

    /// @brief Adds a user who has tried to join the room.
    /// Adds a user who has tried to join the room, and stores their sessionID and username.
    /// @param cookie Cookie associated with joining user.
    /// @param username Username associated with joining user.
    /// @return Whether the user was successfully added or not.
    bool AddUser(std::string cookie, std::string username);

    /// @brief Removes a user from the room.
    /// Removes a user from the room via their sessionID.
    /// @param cookie Cookie associated with leaving user.
    /// @return Whether the user was sucessfully removed or not.
    bool RemoveUser(std::string cookie);

    /// @brief A list of all currently joined user's usernames.
    /// A list of all currently joined user's usernames.
    /// @return vector<string> of usernames.
    std::shared_ptr<std::vector<std::string>> GetUsernames(bool includeHost = false);

    /// @brief Gets the room's id.
    /// Gets the room's id.
    /// @return Room id integer.
    int GetID(){ return _roomID; }

    /// @brief Gets cookie associated with room creator.
    /// Gets cookie associated with room creator.
    /// @return Host cookie.
    std::string GetHostCookie() { return _hostCookie; }

    /// @brief Gets username associated with room creator.
    /// Gets username associated with room creator.
    /// @return Host username.
    std::string GetHostUsername() { return _hostUsername; }

    /// @brief Currently connected user count.
    /// Currently connected user count.
    /// @return User count integer.
    int GetUserCount() { return _connectedCookies.size() + 1; }

    /// @brief Creates the HTML representing the list of users in the room.
    /// Creates the HTML representing the list of users in the room.
    /// @param str a reference to a string to be used to store the HTML text.
    void FormUserHTML(std::string& str);

    /// @brief Gets the current song of the room.
    /// Gets the current song of the room.
    /// @return Name of the current song of the room.
    std::string GetCurrentSongName() { return _currentSongName; }

    /// @brief Gets the current song uploader of the room.
    /// Gets the current song uploader of the room.
    /// @return Name of the current song uploader of the room.
    std::string GetCurrentSongUploader() { return _currentSongUploader; }

    /// @brief Sets the current song of the room.
    /// Sets the current song of the room.
    /// @param newSong name of the new song.
    void SetCurrentSongName(std::string newSong) { _currentSongName = newSong; }

    /// @brief Sets the current song uploader of the room.
    /// Sets the current song uploader of the room.
    /// @param newUploader name of the new uploader.
    void SetCurrentSongUploader(std::string newUploader) { _currentSongUploader = newUploader; }  

    /// @brief An enum to discern the state of song playback that a room is in.
    /// An enum to discern the state of song playback that a room is in.
    enum State
    {
        Paused,
        Playing
        
    };

    /// @brief Returns the playback state of the room.
    /// Returns the playback state of the room.
    /// @return The playback state of the room.
    Chatroom::State GetState() { return _state; }

    /// @brief Returns the current song time.
    /// Returns the current song time.
    /// @return The current song time.
    double GetSongTime() { return _songStartTime + _songTimer.TotalElapsed(); };

    /// @brief Starts playback.
    /// Starts playback at the specified starttime.
    /// @param startTime What time playback begins at.
    void Play(double startTime);

    /// @brief Pauses playback.
    ///  Pauses playback.
    void Pause();

    /// @brief Resets the state of playback.
    /// Resets the state of playback. Song timer set to 0.
    void Reset();

    /// @brief Flips the visibility of the room.
    ///  Flips the visibility of the room.
    void ToggleVisibility() { _visible = !_visible; }

    /// @brief Whether the room is visible or not.
    ///  Whether the room is visible or not.
    /// @return Whether the room is visible or not.
    bool IsVisible() { return _visible; }

private:
    int _roomID;
    std::string _hostCookie;
    std::string _hostUsername;

    std::string _currentSongName { "default_song.mp3" };
    std::string _currentSongUploader { "Server" };
    Chatroom::State _state;
    Stopwatch _songTimer{ };
    double _songStartTime{ 0 };

    bool _visible{ true };
    
    std::map<std::string, std::string> _connectedCookies;

    std::mutex* _setMutex;

};

#endif
