//  CreateAccount.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  An interface to create accounts.
//

#include "CreateAccount.h"

using namespace std;

const CreateAccount* CreateAccount::s_instance{ nullptr };

const CreateAccount& CreateAccount::Instance()
{
    if (!CreateAccount::s_instance)
    {
        CreateAccount::s_instance = new CreateAccount{};
    }

    return *CreateAccount::s_instance;
}

int CreateAccount::Create(string username, string password) const
{
    LoginDB dbConnection{ USER_TABLE_NAME };

    int statusCode = dbConnection.createAccount(username, password);

    if (statusCode == 1)
    {
        ProfilePictureManager::Instance().AddNewUser(username);
    }

    return statusCode;
}

CreateAccount::CreateAccount()
{}




