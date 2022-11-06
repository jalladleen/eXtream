#ifndef CHATROOM_H
#define CHATROOM_H

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <mutex>

class Chatroom
{
public:
    Chatroom(int roomID, const std::string& hostCookie);
    Chatroom(int roomID, const std::string& hostCookie, const std::string& hostUsername);

    ~Chatroom();

    bool AddUser(std::string cookie, std::string username);

    bool RemoveUser(std::string cookie);

    std::shared_ptr<std::vector<std::string>> GetUsernames();

    int GetID(){ return _roomID; }
    std::string GetHostCookie() { return _hostCookie; }
    std::string GetHostUsername() { return _hostUsername; }
    int GetUserCount() { return _connectedCookies.size() + 1; }

private:
    int _roomID;
    std::string _hostCookie;
    std::string _hostUsername;
    
    std::map<std::string, std::string> _connectedCookies;

    std::mutex* _setMutex;

};

#endif
