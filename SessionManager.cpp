//  SessionManager.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Manages logged in user sessions.
//

#include "SessionManager.h"

using namespace std;

SessionManager* SessionManager::s_instance{ nullptr };

    // Singleton
SessionManager& SessionManager::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new SessionManager();
    }

    return *s_instance;
}

SessionManager::~SessionManager()
{
    CookieDB db{ COOKIE_TABLE_NAME };
    db.DestroyCookieTable();

    cout << "Cookie Table destroyed\n";
}

int SessionManager::AddSession(const string& sessionID, const string& username)
{
    CookieDB db{ COOKIE_TABLE_NAME };

    if (!db.usernameExists(username)) // User not already logged in
    {
        db.AddSession(username, sessionID);

        return 1;
    }
    else
    {
        db.RemoveSessionViaUsername(username);

        db.AddSession(username, sessionID);

        return 2;
    }
}

int SessionManager::RemoveSessionViaSessionID(const string& sessionID)
{
    CookieDB db{ COOKIE_TABLE_NAME };

    return db.RemoveSessionViaCookie(sessionID);
}

int SessionManager::RemoveSessionViaUsername(const string& username)
{
    CookieDB db{ COOKIE_TABLE_NAME };

    return db.RemoveSessionViaUsername(username);
}

string SessionManager::GetUser(const string& sessionID)
{
    CookieDB db{ COOKIE_TABLE_NAME };

    if (db.CookieExists(sessionID)) 
    {
        return db.GetUsername(sessionID);
    }
    else
    {
        return "NULL";
    }
}

bool SessionManager::KeyExists(const string& sessionID)
{
    CookieDB db{ COOKIE_TABLE_NAME };

    return db.CookieExists(sessionID);
}

void SessionManager::PrintSessions() const
{
    CookieDB db{ COOKIE_TABLE_NAME };

    auto records = db.ReadAll();

    for (auto record : *records)
    {
        cout << record << '\n';
    }
}

SessionManager::SessionManager()
{}

string SessionManager::NewDistinctCookie()
{
    std::string cookieCandidate = std::to_string(RandomInteger(0, INT32_MAX));

    while (KeyExists(cookieCandidate))
    {
        cookieCandidate = std::to_string(RandomInteger(0, INT32_MAX));
    }

    return cookieCandidate;
}
