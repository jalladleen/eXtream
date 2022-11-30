//  Utility.cpp
//  CS 3307 Group Project
//
//  Created by Balaaj Arbab on 2022-10-31.
//  Date: 3rd November 2022
//
//  Provides various helpful utility functions.
//

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

/// @brief Reads in an HTML file.
/// Reads in an HTML file.
/// @param path Path of HTML file.
/// @return string holding the content of the HTML file.
/// @author Balaaj Arbab
std::string ReadHTMLFile(const std::string& path);

/// @brief Produces a random integer between min(inclusive) and max(exclusive)
/// Produces a random integer between min(inclusive) and max(exclusive)
/// @param min Lower bound, inclusive
/// @param max Upper bound, exclusive
/// @return Random int between min(inclusive) and max(exclusive).
/// @author Balaaj Arbab
int RandomInteger(int min, int max);

/// @brief Returns a string of the current timestamp of the world, at the time of invocation.
/// Returns a string of the current timestamp of the world, at the time of invocation.
/// @return A string of the current time
/// @author Balaaj Arbab
std::string GetCurrentTime();

#endif
