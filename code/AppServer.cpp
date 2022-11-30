//  AppServer.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//
//  Manages the http server component of the backend.
//

#include "AppServer.h"

using namespace std;
using namespace httplib;

/// @brief Helper method to print an incoming request to the console.
/// @param req 
/// @author Balaaj Arbab
static void PrintRequest(const Request& req);

/// @brief Replaces the first occurence of a placeholder substring in a string, to an input string.
/// @param s String to search for substring in.
/// @param toReplace Substring to replace.
/// @param replaceWith String to replace Substring with.
/// @author Balaaj Arbab
static void ReplaceFirstOccurence(string& s, string const& toReplace, string const& replaceWith);

/// @brief Splits an input string in 2 about the input delimiter.
/// @param str Input string.
/// @param delimiter Input delimiter.
/// @return A list of the 2 strings about the delimiter.
/// @author Balaaj Arbab
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

        string friendsHTML { "" };
        FriendManager::Instance().GetHTMLRepresentation(username, friendsHTML);

        ReplaceFirstOccurence(content, "%FRIENDS%", friendsHTML);
    }
    else
    {
        content = ReadHTMLFile("webpages/index.html");
    }

    res.set_content(content, "text/html");

    res.status = 200;
    });

    // Create account 
    svr.Post("/CreateAccount", [](const Request& req, Response& res) {

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

    // Login a user
    svr.Post("/LoginAccount", [](const Request& req, Response& res) {

    // PrintRequest(req);

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

        // SessionManager::Instance().PrintSessions();

        cout << username << " just logged in with cookie: " << cookie << '\n';

        res.set_header("Location", "/");

        res.status = 301;

    }
    else if (statusCode == 0)
    {
        res.set_content("Invalid Login Credentials.", "text/html");

        res.status = 200;
    }

    });

    // Allow a guest to be logged in and access the frontpage.
    svr.Get("/LoginGuest", [](const Request& req, Response& res) {

        string guestUsername = "Guest" + to_string(RandomInteger(0, 100000));

        string cookie = SessionManager::Instance().NewDistinctCookie();

        res.set_header("Set-Cookie", cookie);

        SessionManager::Instance().AddSession(cookie, guestUsername);

        cout << guestUsername << " just logged in with cookie: " << cookie << '\n';

        res.set_header("Location", "/");

        res.status = 301;

    });

    // Allow a user to logout.
    svr.Post("/Logout", [](const Request& req, Response& res) {

    string incomingCookie = req.get_header_value("Cookie");

    cout << SessionManager::Instance().GetUser(incomingCookie) << " is logging out.\n";

    SessionManager::Instance().RemoveSessionViaSessionID(incomingCookie);

    res.set_header("Location", "/");

    res.status = 301;    
    });

    // Add friends to user
    svr.Post("/AddFriend", [](const Request& req, Response& res) {

    const string& friendUsername = req.get_param_value("friendusername");
    string incomingCookie = req.get_header_value("Cookie");

    const int statusCode = FriendManager::Instance().AddFriend(SessionManager::Instance().GetUser(incomingCookie), friendUsername);

    res.set_redirect("/");

    });

    // Create a room and all necessary endpoints for that room.
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

    this->svr.Get("/Rooms/" + to_string(room->GetID()), [roomID](const Request& reqp, Response& resp) {

        string cook = reqp.get_header_value("Cookie");

        auto room = ChatroomManager::Instance().GetChatroom(roomID);

        string username = SessionManager::Instance().GetUser(cook);
        
        if (cook == room->GetHostCookie())
        {
            // Host joined.
        }
        else
        {
            room->AddUser(cook, username); 
            cout << username << " just joined Room " << roomID << '\n';
        }

        string content = ReadHTMLFile("webpages/chatroom.html");
        string users{ };

        room->FormUserHTML(users);

        ReplaceFirstOccurence(content, "%ROOM%", "Room " + to_string(roomID));
        ReplaceFirstOccurence(content, "%UPLOADSONG%", to_string(roomID));
        ReplaceFirstOccurence(content, "%USERS%", users);

        ReplaceFirstOccurence(content, "%SELF%", username);
        ReplaceFirstOccurence(content, "%SELFIMG%", "/" + ProfilePictureManager::Instance().GetUserProfilePic(username));

        ReplaceFirstOccurence(content, "%SONGNAME%", room->GetCurrentSongName());
        ReplaceFirstOccurence(content, "%UPLOADER%", room->GetCurrentSongUploader());
        ReplaceFirstOccurence(content, "%SONGFILE%", room->GetCurrentSongName());

        resp.set_content(content, "text/html");

        resp.status = 200;
    });

    this->svr.Get("/Rooms/" + to_string(room->GetID()) + "/UserList", [roomID](const Request& reqp, Response& resp) {

        auto room = ChatroomManager::Instance().GetChatroom(roomID);

        string users{ };

        room->FormUserHTML(users);

        resp.set_content(users, "text/plain");

        resp.status = 200;
    });

    // Allow a song to be uploaded and accessed by a room.
    svr.Post("/UploadSong" + to_string(room->GetID()), [roomID](const Request& req, Response& res) {

    auto room = ChatroomManager::Instance().GetChatroom(roomID);

    if (room->GetState() == Chatroom::State::Playing) return;

    string incomingCookie = req.get_header_value("Cookie");
    string username = SessionManager::Instance().GetUser(incomingCookie);

    bool hasFile = req.has_file("songfile");
    
    if (hasFile)
    {
        size_t contentLength = stoi(req.get_header_value("Content-Length"));
        const auto& file = req.get_file_value("songfile");

        vector<string> fileType = StringSplitInTwo(file.content_type, "/");

        // cout << fileType[0] << '\n';  
        // cout << fileType[1] << '\n';  
        // cout << contentLength << '\n';  

        if (fileType[0] == "audio" && fileType[1] == "mpeg")
        {
            string path = "songs/" + file.filename;

            ofstream out(path, ios::binary);
            out.write(file.content.c_str(), contentLength);
            out.close();

            room->SetCurrentSongName(file.filename);
            room->SetCurrentSongUploader(username);
            room->Reset();
            SongManager::Instance().AddSong(file.filename);

            cout << username << " just uploaded " << file.filename << " to room: " << roomID << '\n';

        }
    }

    });

    this->svr.Get("/Rooms/" + to_string(room->GetID()) + "/SongInfo", [roomID](const Request& reqp, Response& resp) {

        auto room = ChatroomManager::Instance().GetChatroom(roomID);

        string responseJson{ "{\"SongName\" : \"" + room->GetCurrentSongName() + "\", \"SongUploader\" : \"" + room->GetCurrentSongUploader() + "\", \"State\" : \"" };

        if (room->GetState() == Chatroom::State::Paused)
        {
            responseJson += "Paused\"";
        }
        else if (room->GetState() == Chatroom::State::Playing)
        {
            responseJson += "Playing\", ";
            responseJson += "\"Time\" : " + to_string(room->GetSongTime());
        }

        responseJson += "}";

        resp.set_content(responseJson, "application/json");

        resp.status = 200;
    });

    this->svr.Post("/Rooms/" + to_string(room->GetID()) + "/SongControl", [roomID](const Request& reqp, Response& resp) {

        auto room = ChatroomManager::Instance().GetChatroom(roomID);

        const string& action = reqp.get_param_value("Action");
        

        cout << "Action: " << action << '\n';
        

        if (action == "Play")
        {
            double time = stod(reqp.get_param_value("Time"));

            // cout << "Time: " << time << '\n';

            room->Play(time);
        }
        else if (action == "Pause")
        {
            room->Pause();
        }
        else if (action == "Reset")
        {
            room->Reset();
        }

        resp.set_content("", "text/plain");

        resp.status = 200;
    });

    this->svr.Post("/Rooms/" + to_string(room->GetID()) + "/Visibility", [roomID](const Request& reqp, Response& resp) {

        auto room = ChatroomManager::Instance().GetChatroom(roomID);

        room->ToggleVisibility();

        cout << "Room " << roomID << " visibility toggled.\n";

        resp.set_content("", "text/plain");

        resp.status = 200;
    });

    // this->svr.Post("/Rooms/" + to_string(room->GetID()) + "/Host", [roomID](const Request& reqp, Response& resp) {

    //     auto room = ChatroomManager::Instance().GetChatroom(roomID);

    //     resp.set_content(room->GetHostUsername(), "text/plain");

    //     resp.status = 200;
    // });

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
