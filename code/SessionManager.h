//  SessionManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//
//  Manages logged in user sessions.
//

#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <iostream>
#include <string>
// #include <map>
// #include <utility>
#include <memory>

#include "CookieDB.h"

/// @brief Manages active sessions for connected users.
/// Manages active sessions for connected users.
/// @author Balaaj Arbab
class SessionManager
{
public:
    /// @brief Singleton design pattern for SessionManager.
    /// Allows access to a singular instance of SessionManager across the project.
    /// @return A reference to the instance of SessionManager.
    static SessionManager& Instance();

    /// @brief Cleans up. Destroy the associated cookie table.
    /// Cleans up. Destroy the associated cookie table.
    ~SessionManager();
    
    /// @brief Adds a session to the session database.
    /// Adds a session to the session database.
    /// @param sessionID Cookie to add.
    /// @param username Username associated with cookie.
    /// @return 1 if successful, -1 if not.
    int AddSession(const std::string& sessionID, const std::string& username);

    /// @brief Removes a session from the DB via cookie.
    /// Removes a session from the DB via cookie.
    /// @param sessionID Cookie string of the user whose session to remove.
    /// @return 1 if successful, -1 if not.
    int RemoveSessionViaSessionID(const std::string& sessionID);

    /// @brief Removes a session from the DB via username.
    /// Removes a session from the DB via username.
    /// @param username Username string of the user whose session to remove.
    /// @return 1 if successful, -1 if not.
    int RemoveSessionViaUsername(const std::string& username);

    /// @brief Gets the username associated with the user with given cookie.
    /// Gets the username associated with the user with given cookie.
    /// @param sessionID Cookie string
    /// @return Username of user with cookie
    std::string GetUser(const std::string& sessionID);

    /// @brief Checks whether a given sessionID exists in the DB.
    /// Checks whether a given sessionID exists in the DB.
    /// @param sessionID Cookie string to check.
    /// @return bool
    bool KeyExists(const std::string& sessionID);

    /// @brief Displays a string representation of all the existing sessions.
    /// Displays a string representation of all the existing sessions.
    void PrintSessions() const;

    /// @brief Generates new unique cookie.
    /// Generates new unique cookie.
    /// @return The unique cookie.
    std::string NewDistinctCookie();

protected:
    SessionManager();

private:
    // std::map<std::string, std::shared_ptr<User>> _activeSessions{};

    // Singleton
    static SessionManager* s_instance;

    const std::string COOKIE_TABLE_NAME = "cookietable";

    // Prevent copying and assignment
    SessionManager(const SessionManager& other) = delete;
    SessionManager& operator=(const SessionManager& other) = delete;

};

#endif
