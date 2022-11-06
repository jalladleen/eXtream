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

    return statusCode;
}

CreateAccount::CreateAccount()
{}



