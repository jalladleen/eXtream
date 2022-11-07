//  SessionManager.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Manages logged in user sessions.

#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <iostream>
#include <string>
// #include <map>
// #include <utility>
#include <memory>

#include "User.h"
#include "CookieDB.h"

class SessionManager
{
public:
    // Singleton
    static SessionManager& Instance();

    ~SessionManager();
    
    int AddSession(const std::string& sessionID, const std::string& username);

    int RemoveSessionViaSessionID(const std::string& sessionID);
    int RemoveSessionViaUsername(const std::string& username);

    std::string GetUser(const std::string& sessionID);

    bool KeyExists(const std::string& sessionID);

    void PrintSessions() const;

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
