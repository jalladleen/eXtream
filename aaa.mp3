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

/// @brief Provides access to the User Credentials Table for the app.
class LoginDB {   
public:
    /// @brief Initializes the object and acquires a database handle.
    /// @param tableName Table name of the credentials data table.
    LoginDB(const std::string& tableName);

    /// @brief Safely closes the Database handle and cleans up.
    ~LoginDB();
    
    /// @brief Checks to see whether input credentials are valid and exist.
    /// @param username Username of the user trying to log in.
    /// @param pw Password of the user trying to log in.
    /// @return 1 if successful, -1 if not.
    int verifyLogin(std::string username, std::string password);
    
    /// @brief NOT IMPLEMENTED
    /// @param username 
    /// @param np 
    /// @return 
    int changePassword(std::string username, std::string np);
    
    /// @brief Inserts a new user into the database.
    /// @param u Username of the new user.
    /// @param p Password of the new user.
    /// @return 1 if successful, -1 if not.
    int createAccount(std::string u, std::string p);
    
    /// @brief Checks whether if a given username already exists.
    /// @param username Username string to check.
    /// @return 1 if true, -1 if not.
    int checkUsername(std::string username);
    
    int checkPW(std::string ePw);
    
    /// @brief Load DB into memory.
    /// @return Vector of string representation of rows.
    std::vector<std::string> getUserDatabase();
    

private:
    sqlite3* db;
    const std::string _tableName;

};

#endif
