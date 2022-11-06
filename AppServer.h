#ifndef APP_SERVER_H
#define APP_SERVER_H

#include <iostream>
#include <memory.h>
#include <signal.h>
#include <string>

#include "./httplib.h"
#include "CreateAccount.h"
#include "Login.h"
#include "Utility.h"
#include "SessionManager.h"
#include "ChatroomManager.h"

class AppServer
{
public:
    AppServer();

    static AppServer& Instance();

    void CreateInitialRoutes();

    void Run();

private:
    static AppServer* s_instance;

    const std::string BASE_DIR_PATH{"."};

    httplib::Server svr;

    AppServer(const AppServer& other) = delete;
    AppServer& operator=(const AppServer& other) = delete;

};

#endif
