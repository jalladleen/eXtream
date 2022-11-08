//  CreateAccount.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to create accounts.
//

#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include <iostream>
#include <string>

#include "LoginDB.hpp"

/// @brief Account creating functionality.
class CreateAccount
{
public:
    /// @brief Singleton design pattern for CreateAccount.
    /// @return A reference to the instance of CreateAccount.
    static const CreateAccount& Instance();

    /// @brief Inserts a new user into the database.
    /// @param username Username of the new user.
    /// @param password Password of the new user.
    /// @return 1 if successful, -1 if not.
    int Create(std::string username, std::string password) const;

protected:
    CreateAccount();

private:
    static const CreateAccount* s_instance;

    const std::string USER_TABLE_NAME = "logintable";

    CreateAccount(const CreateAccount& other) = delete;
    CreateAccount& operator=(const CreateAccount& other) = delete;

};

#endif
