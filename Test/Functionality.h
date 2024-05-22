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

namespace fcf
{
    std::string raw_path(const std::string& str);
    void create_minimal_subroutine(std::string name, std::string origin, std::string destiny);
    void create_subroutine(std::string origin, std::string destiny, std::vector<std::string> types,
                           std::pair<std::time_t, std::time_t> dates, std::vector<std::string> authors);
    void execute_minimal_subroutine(std::string& path);
    std::vector<std::string> get_directory_subroutines(std::string path);
}

#endif

