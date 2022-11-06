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
