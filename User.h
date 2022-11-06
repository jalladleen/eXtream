#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

class User
{
public:
    User(std::string userName, std::string email, std::string uID);
    User(std::string userName, std::string uID);
    User(std::string username);

    const std::string& GetUserName() const;
    const std::string& GetEmail() const;
    void SetChatroomID(int id);

private:
    std::string _userName;
    std::string _emailAddress{ "" };
    std::string _uID;
    int _connectedChatroomID;

};

std::ostream& operator<<(std::ostream& out, const User& user);

#endif
