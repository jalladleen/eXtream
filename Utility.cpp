//  Utility.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Provides various helpful utility functions.

#include "Utility.h"

using namespace std;

std::string ReadHTMLFile(const std::string& path)
{
    std::ifstream inFile;
    inFile.open(path);

    std::stringstream ss;
    ss << inFile.rdbuf();

    std::string str = ss.str();

    return str;
}

mutex g_randInt_mutex;

int RandomInteger(int min, int max)
{
    g_randInt_mutex.lock();

    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist{ min, max - 1 };

    int n = dist(mt);
    
    g_randInt_mutex.unlock();

    return n;
}

std::string GetCurrentTime()
{
    auto time = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(time);

    std::string timestamp = std::ctime(&t);

    return timestamp.substr(0, timestamp.length() - 1);
}
