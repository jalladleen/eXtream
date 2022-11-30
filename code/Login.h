//  Login.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to login for a user.
//

#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>

#include "LoginDB.hpp"

/// @brief Logging in functionality.
/// Used to handle Logging in functionality for a user.
/// @author Balaaj Arbab
class Login
{
public:
    /// @brief Singleton design pattern for Login.
    /// Allows access to a singular instance of Login across the project.
    /// @return A reference to the instance of Login.
    static const Login& Instance();

    /// @brief Checks to see whether input credentials are valid and exist.
    /// Checks to see whether input credentials are valid and exist.
    /// @param username Username of the user trying to log in.
    /// @param pw Password of the user trying to log in.
    /// @return 1 if successful, -1 if not.
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

