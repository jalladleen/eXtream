//  CreateAccount.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//
//  An interface to create accounts.
//

#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include <iostream>
#include <string>

#include "LoginDB.hpp"
#include "ProfilePictureManager.h"

/// @brief Account creating functionality.
/// Account creating functionality.
/// @author Balaaj Arbab
class CreateAccount
{
public:
    /// @brief Singleton design pattern for CreateAccount.
    /// /// Allows access to a singular instance of CreateAccount across the project.
    /// @return A reference to the instance of CreateAccount.
    static const CreateAccount& Instance();

    /// @brief Inserts a new user into the database.
    /// Inserts a new user into the database with specified username and password, which is encrypted before insertion.
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
