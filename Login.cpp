#include "Login.h"

using namespace std;

const Login* Login::s_instance{ nullptr };

const Login& Login::Instance()
{
    if (Login::s_instance == nullptr)
    {
        Login::s_instance = new Login{};
    }

    return *Login::s_instance;
}

int Login::TryLogin(std::string username, std::string pw) const
{
    LoginDB dbConnection{ USER_TABLE_NAME };

    int statusCode = dbConnection.verifyLogin(username, pw);

    return statusCode;
}


Login::Login()
{}



