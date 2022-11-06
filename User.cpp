#include "User.h"

using namespace std;

User::User(string userName, string email, string uID)
: _userName{ userName }, _emailAddress{ email }, _uID{ uID }
{
}

User::User(string userName, string uID)
: _userName{ userName }, _uID{ uID }
{
}

User::User(string userName)
: _userName{ userName }
{
}

const string& User::GetUserName() const
{
    return _userName;
}

const string& User::GetEmail() const
{
    return _emailAddress;
}

void User::SetChatroomID(int id)
{
    _connectedChatroomID = id;
}

ostream& operator<<(ostream& out, const User& user)
{
    return out << "User: " << user.GetUserName();
}