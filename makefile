all: Program

Program: AppServer.cpp Chatroom.cpp ChatroomManager.cpp CookieDB.cpp CreateAccount.cpp Login.cpp LoginDB.cpp Program.cpp SessionManager.cpp Utility.cpp
	g++ -o Program.exe AppServer.cpp Chatroom.cpp ChatroomManager.cpp CookieDB.cpp CreateAccount.cpp Login.cpp LoginDB.cpp Program.cpp SessionManager.cpp Utility.cpp -lsqlite3 -pthread