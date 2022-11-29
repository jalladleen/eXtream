//  AppServer.h
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Manages the http server component of the backend.
//

#ifndef APP_SERVER_H
#define APP_SERVER_H

#include <iostream>
#include <memory.h>
#include <signal.h>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "./httplib.h"
#include "CreateAccount.h"
#include "Login.h"
#include "Utility.h"
#include "SessionManager.h"
#include "ChatroomManager.h"
#include "ProfilePictureManager.h"
#include "SongManager.h"
#include "FriendManager.h"

/// @brief The HTTP webserver for the app.
class AppServer
{
public:
    /// @brief Initializes the app server.
    AppServer();

    /// @brief Singleton design pattern for AppServer
    /// @return A reference to the instance of AppServer
    static AppServer& Instance();

    /// @brief Sets up http endpoints.
    void CreateInitialRoutes();

    /// @brief Starts the webserver.
    void Run();

private:
    static AppServer* s_instance;

    const std::string BASE_DIR_PATH{"."};

    httplib::Server svr;

    AppServer(const AppServer& other) = delete;
    AppServer& operator=(const AppServer& other) = delete;

};

#endif
