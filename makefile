all: Program

Program: code/AppServer.cpp code/Chatroom.cpp code/ChatroomManager.cpp code/CookieDB.cpp code/CreateAccount.cpp code/FriendManager.cpp code/FriendsListDB.cpp code/ImageDB.cpp code/Login.cpp code/LoginDB.cpp code/ProfilePictureManager.cpp code/Program.cpp code/SessionManager.cpp code/SongManager.cpp code/Utility.cpp
	g++ -o Program.exe code/*.cpp -lsqlite3 -pthread