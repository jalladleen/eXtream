/**
 * @author Daniel Herbert
 *
 * This class represents the database that will store all user information
 */


#ifndef LOGINDB_H
#define LOGINDB_H

#include <stdio.h>
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

/**
 * @brief The LoginDB class
 * @author Daniel Herbert
 *
 * This class will connect to an sqlite database and store all user information in the database, as well as the friends a user has added
 * It implements the functions for verifying a user's login credentials, changing a user's password, creating an account, checking if a username already exists, as well as allowing a user to add a friend and subsequently updating that in the database.
 */

class LoginDB {
public:
    /**
     * Constructor that creates a sqlite database and two tables: one to store user login credentials and the other to track the friends a user has added
     *
     * @param The name of the user login table
     */
    LoginDB(std::string tableName);
    
    /**
     * Destructor to close database connection
     */
    ~LoginDB();
    
    /**
     * Verifies a user's login credentials
     *
     * @param username The username passed to login
     * @param password The password passed to login
     *
     * @return int Returns 1 if the user credentials entered are correct, 0 otherwise
     */
    int verifyLogin(std::string username, std::string password);
    
    /**
     * Changes a user's password
     *
     * @param username The user's username that wants their password changed
     * @param newpw The new password the user would like to change their password to
     *
     *  @return int Returns 1 if the password was successfully changed and updated in the database, 0 otherwise
     */
    int changePassword(std::string username, std::string np);
    
    /**
     * Creates an account and stores user credentials in the database
     *
     * @param u The username of the new user
     * @param p The password the new user would like to use
     *
     * @return int Returns 1 if the account was successfully created, 0 otherwise
     */
    int createAccount(std::string u, std::string p);
    
    /**
     * Checks if a username already exists in the database
     *
     * @param username The username a user would like to sign up with
     *
     * @return int
     */
    int checkUsername(std::string username);
    
    /**
     * Getting user credentials for all users in the database
     *
     * @return vector<std::string> Vector containing all stored information for each user in the database
     */
    std::vector<std::string> getUserDatabase();
    
    /**
     * Encrypts the password a user would like to use
     *
     * @param pw Users password
     *
     * @return std::string Encrypted password
     */
    std::string encrypt(std::string pw);
    
    /**
     * Decrypts an encrypted password
     *
     * @param epw An encrypted password
     *
     * @return std::string The decrypted password
     */
    std::string decrypt(std::string epw);
    
private:
    sqlite3* db;
    std::string _tableName;
    int numUsers;

};

#endif
