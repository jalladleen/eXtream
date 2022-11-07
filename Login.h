//  Login.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to login for a user.

#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>

#include "LoginDB.hpp"

class Login
{
public:
    static const Login& Instance();

    int TryLogin(std::string username, std::string pw) const;

protected:
    Login();

private:
    // LoginDB _loginDB;

    static const Login* s_instance; 

    const std::string USER_TABLE_NAME = "logintable";

    Login(const Login& other) = delete;
    Login& operator=(const Login& other) = delete;

};

#endif

