/**
 *@author Daniel Herbert
 *
 *This class represents the database that will store all user information in our project
 */

#include "LoginDB.hpp"
using namespace std;
/** Constructor for the LoginDB class
 *Table name is passed to the constructor
 *Constructor opens a database connection and creates a
 *table that will store all user login info
 */
LoginDB::LoginDB(string tableName)
{
    _tableName = tableName;
    numUsers = 0;
    char *zErrMsg = 0;
    int open;
    int rc;
    //Query to create table
    string query = "create table if not exists " + _tableName + " (username varchar(255), password varchar(255), u_id int);";
    
    const char *sql = query.c_str();
    
    //Opening database connection
    open = sqlite3_open("database.db", &db);
    
    if (open) {
        printf("Can't open database\n");
    }
    else {
        printf("Database opened succesfully\n");
    }
    
    //Creating table to store user information
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK) {
        cout << "Error creating table";
    } else {
        cout << "Table created successfully\n";
    }
    
}

//Destructor
LoginDB::~LoginDB()
{
    sqlite3_close(db);
    cout << "Database successfully closed.\n";
}

//Method to verify login credentials for user
int LoginDB::verifyLogin(string username, string password) {
    vector<string> gettingUserList = getUserDatabase();
    string delimiter = "|";
    for (int i = 0; i < gettingUserList.size(); i++) {
        string temp = gettingUserList.at(i);
        string token = temp.substr(0, temp.find(delimiter));
        if (token == username) {
            temp.erase(0, temp.find(delimiter) + delimiter.length());
            string pw = temp.substr(0, temp.find(delimiter));
            if (pw == encrypt(password)) {
                printf("Login Credentials Provided are correct!\n");
                return 1;           
            }
        }
    }
    printf("Login Credentials Provided are incorrect!\n");
    return 0;
}

//Method to change user's password
int LoginDB::changePassword(string username, string np) {
    //Query to update password
    string newPW = encrypt(np);
    string query = "update " + _tableName + " set password = \'" + newPW + "\'" +  " where username = \'" + username + "\'";
    char *zErrMsg = 0;
    int rc;
    const char *sql = query.c_str();
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        cout << "Error updating password\n";
    } else {
        cout << "Password updated successfully\n";
    }
    return 1;
}

//Method for user to create account and get added to Database table
int LoginDB::createAccount(string u, string p)
{
    //Checking if username already exists
    if (checkUsername(u) == 1)
    {
        cout << "Username already exists.\n";
        
        return 0;
    }

    int rc;
    numUsers++;
    string uniqueID = to_string(numUsers);
    string encryptPW = encrypt(p);
    //Query to insert new user account info in database table
    string query = "insert into " + _tableName + " values (\""+ u +  "\" , \"" + encryptPW + "\" , \"" + uniqueID + "\");";
    const char *sql = query.c_str();
    printf("%s\n", sql);
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    
    if (rc != SQLITE_OK) {
        cout << "Error inserting records\n";
    } else {
        cout << "Records inserted successfully\n";
    }
    return 1;
}

//Method to check if username already exists from the database
int LoginDB::checkUsername(string username) {
    vector<string> gettingUserList = getUserDatabase();
    string delimiter = "|";
    for (int i = 0; i < gettingUserList.size(); i++) {
        string temp = gettingUserList.at(i);
        string token = temp.substr(0, temp.find(delimiter));
        if (token == username) {
            return 1;
        }
    }
    return 0;
}

//Method to get all user information from database and stores it in a vector
vector <string> LoginDB::getUserDatabase() {
    //Creating an empty vector
    vector <string> userLog;
    //SQL statement to retrieve all user information
    string query = "select * from " + _tableName;
    string row;
    sqlite3_stmt* stmt;
    const char *sql = query.c_str();
    int len = strlen(sql);
    int ret = sqlite3_prepare_v2(db, sql, len, &stmt, NULL);
    if (ret != SQLITE_OK) {
        cout << "Error preparing statement records\n";
    }
    int r = sqlite3_step(stmt);
    //While loop to iterate through each row and column in the Database table
    while (r == SQLITE_ROW) {
        string messageCol1 = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        string messageCol2 = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        string messageCol3 = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        row = messageCol1 + "|" + messageCol2 + "|" +messageCol3;
        userLog.push_back(row);
        r = sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    return userLog;
}



//Method to encrypt user passwords
string LoginDB::encrypt(string pw) {
    string epw = "";
    string epwchar;
    int ascii;
    int tempascii;
    //Using ascii values to shift and encrypt
    for (int i = 0; i < pw.length(); i++) {
        ascii = pw[i];
        if (ascii >= 33 && ascii <= 64) {
            tempascii = ascii + 3;
        }
        if (ascii >= 65 && ascii <= 96) {
            tempascii = ascii + 3;
        }
        if (ascii >= 97 && ascii <= 122) {
            tempascii = ascii + 5;
        }
        epwchar = char(tempascii);
        epw.append(epwchar);
    }
    return epw;
}

//Method to decrypt user passwords when verifying login credentials
string LoginDB::decrypt(string epw) {
    string pw = "";
    string pwchar;
    int ascii;
    int tempascii;
    //Decrypting password from database
    for (int i = 0; i < epw.length(); i++) {
        ascii = epw[i];
        if (ascii >= 36 && ascii <= 67) {
            tempascii = ascii - 3;
        }
        if (ascii >= 68 && ascii <= 99) {
            tempascii = ascii - 3;
        }
        if (ascii >= 102 && ascii <= 127) {
            tempascii = ascii - 5;
        }
        pwchar = char(tempascii);
        pw.append(pwchar);
    }
    return pw;
}

