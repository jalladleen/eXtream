//  Program.exe
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Driver file.

#include <iostream>
#include <memory.h>
#include <signal.h>

#include "./httplib.h"
#include "CreateAccount.h"
#include "Login.h"
#include "Utility.h"
#include "SessionManager.h"
#include "AppServer.h"

using namespace std;
using namespace httplib;

const string BASE_DIR_PATH{"."};

void SignalHandler(int n);

int main(int argc, char** argv)
{
    cout << "Hello World!\n";
    signal(SIGINT, SignalHandler);

    AppServer& svr = AppServer::Instance();

    svr.CreateInitialRoutes();

    svr.Run();  

    return 0;
}


void SignalHandler(int n)
{
    delete &SessionManager::Instance(); 

    cout << "Exiting\n";

    exit(0);
}