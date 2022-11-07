//  CreateAccount.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to create accounts.

#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include <iostream>
#include <string>

#include "LoginDB.hpp"

class CreateAccount
{
public:
    static const CreateAccount& Instance();

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
