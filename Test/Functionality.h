#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <filesystem>
#include <stdexcept>
#include <algorithm>

namespace fcf
{
    std::string raw_path(const std::string& str);
    std::string get_filetype(const std::string& str);
    std::string seconds_to_strdate(long long seconds);
    long long strdate_to_seconds(const std::string& datestr);
    void create_minimal_subroutine(std::string name, std::string origin, std::string destiny);
    void create_subroutine(std::string name, std::string origin, std::string destiny, std::vector<std::string> types,
                           std::pair<long long, long long> dates);
    void execute_minimal_subroutine(std::string path);
    void execute_subroutine(std::string path);
    std::vector<std::string> get_directory_subroutines(std::string path);
}

#endif

