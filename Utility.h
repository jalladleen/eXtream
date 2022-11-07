//  Utility.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Provides various helpful utility functions.

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <stdint.h>
#include <chrono>
#include <ctime>
#include <mutex>

std::string ReadHTMLFile(const std::string& path);

int RandomInteger(int min, int max);

std::string GetCurrentTime();

#endif
