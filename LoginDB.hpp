//
//  LoginDB.hpp
//  CS 3307 Group Project
//
//  Created by Daniel Herbert on 2022-10-31.
//

#ifndef LOGINDB_H
#define LOGINDB_H

#include <stdio.h>

#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>

class LoginDB {   
public:
    LoginDB(const std::string& tableName);

    ~LoginDB();
    
    int verifyLogin(std::string username, std::string password);
    
    int changePassword(std::string username, std::string np);
    
    int createAccount(std::string u, std::string p);
    
    int checkUsername(std::string username);
    
    int checkPW(std::string ePw);
    
    std::vector<std::string> getUserDatabase();
    


private:
    sqlite3* db;
    const std::string _tableName;

};

#endif
