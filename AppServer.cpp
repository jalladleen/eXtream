//  AppServer.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Manages the http server component of the backend.
//

#include "AppServer.h"

using namespace std;
using namespace httplib;

static void PrintRequest(const Request& req);
static void ReplaceFirstOccurence(string& s, string const& toReplace, string const& replaceWith);
static vector<string> StringSplitInTwo(const string& str, const string& delimiter);

AppServer* AppServer::s_instance{ nullptr };

AppServer::AppServer()
{}

AppServer& AppServer::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new AppServer();
    }

    return *s_instance;
}

void AppServer::CreateInitialRoutes()
{
    svr.set_base_dir(BASE_DIR_PATH);

    // Initial Page
    svr.Get("/", [](const Request& req, Response &res) 
    {
    string incomingCookie = "a";

    if (req.has_header("Cookie")) incomingCookie = req.get_header_value("Cookie");

    string content;
    if (SessionManager::Instance().KeyExists(incomingCookie))
    {
        content = ReadHTMLFile("webpages/front.html");

        string username = SessionManager::Instance().GetUser(incomingCookie);

        ReplaceFirstOccurence(content, "%NAME%", username);
        ReplaceFirstOccurence(content, "%PIC%", ProfilePictureManager::Instance().GetUserProfilePic(username));

        string roomsHTML{ "" };
        ChatroomManager::Instance().ConstructGridElements(roomsHTML);

        ReplaceFirstOccurence(content, "%ROOMS%", roomsHTML);
    }
    else
    {
        content = ReadHTMLFile("webpages/index.html");
    }

    res.set_content(content, "text/html");

    res.status = 200;
    });

    svr.Post("/CreateAccount", [](const Request& req, Response& res) {

    // PrintRequest(req);

    const string& username = req.get_param_value("username");
    const string& pw = req.get_param_value("password");

    const int statusCode = CreateAccount::Instance().Create(username, pw);

    if (statusCode == 1)
    {
        string content = ReadHTMLFile("webpages/accountcreated.html");

        res.set_content(content, "text/html");

        res.status = 200;
    }
    else if (statusCode == 0)
    {
        res.set_content("<h1>account NOT created.</h1>", "text/html");

        res.status = 200;
    }

    });

    svr.Post("/LoginAccount", [](const Request& req, Response& res) {

    PrintRequest(req);

    const string& username = req.get_param_value("username");
    const string& pw = req.get_param_value("password");

    const int statusCode = Login::Instance().TryLogin(username, pw);

    if (statusCode == 1)
    {
        res.set_content("Logged in.<br><a href='http://localhost:5000'>go</a>", "text/html");

        string cookie = SessionManager::Instance().NewDistinctCookie();
        cout << "Cookie Created: " << cookie << '\n';
        res.set_header("Set-Cookie", cookie);

        SessionManager::Instance().AddSession(cookie, username);

        SessionManager::Instance().PrintSessions();

        res.set_header("Location", "/");

        res.status = 301;

    }
    else if (statusCode == 0)
    {
        res.set_content("Invalid Login Credentials.", "text/html");

        res.status = 200;
    }

    });

    svr.Post("/Logout", [](const Request& req, Response& res) {

    string incomingCookie = req.get_header_value("Cookie");

    cout << SessionManager::Instance().GetUser(incomingCookie) << " is logging out.\n";

    SessionManager::Instance().RemoveSessionViaSessionID(incomingCookie);

    res.set_header("Location", "/");

    res.status = 301;    
    });

    svr.Post("/CreateRoom", [&](const Request& req, Response& res) mutable {

    cout << "Creating Room\n";
    // PrintRequest(req);

    string incomingCookie;

    if (req.has_header("Cookie")) incomingCookie = req.get_header_value("Cookie");
    else 
    {
        res.status = 401;
        res.set_content("Unauthorized.", "text/html");
        return;
    }

    auto room = ChatroomManager::Instance().CreateRoom(incomingCookie);
    int roomID = room->GetID(); 

    cout << "/Rooms/" + to_string(room->GetID()) << "\n";

    this->svr.Get("/Rooms/" + to_string(room->GetID()), [roomID](const Request& reqp, Response& resp) {


        string cook = reqp.get_header_value("Cookie");

        auto room = ChatroomManager::Instance().GetChatroom(roomID);
        
        if (cook == room->GetHostCookie())
        {
            // Host joined.
        }
        else
        {
            room->AddUser(cook, SessionManager::Instance().GetUser(cook)); 
        }     

        resp.set_content("Welcome to room " + to_string(room->GetID()), "text/html");

        resp.status = 200;
    });

    res.set_content("Welcome to room " + to_string(room->GetID()), "text/html");

    ChatroomManager::Instance().PrintChatrooms();

    res.set_header("Location", "/Rooms/" + to_string(room->GetID()));

    res.status = 301;
    });

    svr.Post("/UploadImage", [](const Request& req, Response& res) {

    string incomingCookie = req.get_header_value("Cookie");
    string username = SessionManager::Instance().GetUser(incomingCookie);

    bool hasFile = req.has_file("imagefile");
    
    if (hasFile)
    {
        size_t contentLength = stoi(req.get_header_value("Content-Length"));
        const auto& file = req.get_file_value("imagefile");

        vector<string> fileType = StringSplitInTwo(file.content_type, "/");

        if (fileType[0] == "image")
        {
            string oldPic = ProfilePictureManager::Instance().GetUserProfilePic(username);

            if (oldPic != "images/blank.webp")
            {
                system(("rm " + oldPic).c_str());
            }

            string path = "images/" + username + "." + fileType[1];

            ofstream out(path, ios::binary);
            out.write(file.content.c_str(), contentLength);
            out.close();

            ProfilePictureManager::Instance().UpdateProfilePic(username, path);

            // cout << path << '\n';    

        }
    }

    res.set_header("Location", "/");

    res.status = 301;    
    });

}

void AppServer::Run()
{
    svr.listen("localhost", 5000);
}


static void PrintRequest(const Request& req)
{
for (auto i = req.headers.begin(); i != req.headers.end(); ++i)
{
    cout << (*i).first << ": " << (*i).second << "\n";
}
cout << "\n";
cout << req.body << "\n\n";
}

static void ReplaceFirstOccurence(string& s, string const& toReplace, string const& replaceWith) 
{
    std::size_t pos = s.find(toReplace);

    if (pos == string::npos) return;

    s.replace(pos, toReplace.length(), replaceWith);
}

static vector<string> StringSplitInTwo(const string& str, const string& delimiter)
{
    int index = str.find(delimiter);
    vector<string> list{ };

    list.push_back(str.substr(0, index));
    list.push_back(str.substr(index + 1, str.length()));

    return list;
}
