#pragma warning(disable : 4996)
#include <iostream>
#include "Functionality.h"
#include <ctime>
#include <chrono>

int main()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %X");
    std::cout << ss.str();
    return 0;
}