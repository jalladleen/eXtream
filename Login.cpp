//  Login.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to login for a user.

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



