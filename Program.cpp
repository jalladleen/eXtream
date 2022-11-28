//  Program.exe
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Driver file.
//

#include <iostream>
#include <memory.h>
#include <signal.h>

#include "./httplib.h"
#include "CreateAccount.h"
#include "Login.h"
#include "Utility.h"
#include "SessionManager.h"
#include "AppServer.h"
#include "SongManager.h"

using namespace std;
using namespace httplib;

const string BASE_DIR_PATH{"."};

/// @brief Performs necessary clean-up upon interrupt.
/// @param n 
void SignalHandler(int n);

int main(int argc, char** argv)
{
    cout << "App running!\n";
    signal(SIGINT, SignalHandler);

    AppServer& svr = AppServer::Instance();

    svr.CreateInitialRoutes();

    svr.Run();  

    delete &SessionManager::Instance(); 
    delete &SongManager::Instance();

    return 0;
}


void SignalHandler(int n)
{
    delete &SessionManager::Instance(); 
    delete &SongManager::Instance();

    cout << "Exiting\n";

    exit(0);
}