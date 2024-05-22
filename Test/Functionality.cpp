#include "Functionality.h"

std::string fcf::raw_path(const std::string& str)
{
    std::string raw_path;
    for (char c : str)
    {
        if (c == '\\')
        {
            raw_path += "\\\\";
        }
        else if(c == '\"')
        {
            ; //skip
        }
        else
        {
            raw_path += c;
        }
    }
    return raw_path;
}


void fcf::create_minimal_subroutine(std::string name, std::string origin, std::string destiny)
{
    origin = fcf::raw_path(origin);
    destiny = fcf::raw_path(destiny);
    try 
    {
        if (!(std::filesystem::exists(std::filesystem::path(origin)) && std::filesystem::exists(std::filesystem::path(destiny))))
        {
            std::stringstream mesage;
            mesage << "Origin path not found or Destiny path not found\n" << "File: " << __FILE__ << "\n" << "Line: " << __LINE__ << "\n";
            throw std::runtime_error(mesage.str());
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << "\n";
        std::exit(EXIT_FAILURE);
    }
    if (!(std::filesystem::exists(std::filesystem::absolute(std::filesystem::path("../subroutines"))) &&
        std::filesystem::is_directory(std::filesystem::absolute(std::filesystem::path("../subroutines")))))
    {
        std::filesystem::path new_directory = std::filesystem::absolute("../subroutines");
        std::filesystem::create_directory(new_directory);
    }
    std::ofstream subroutine_file;
    int copy = 1;
    std::string subroutine_path = "../subroutines/" + name + ".txt";
    while (std::filesystem::exists(std::filesystem::path(subroutine_path)))
    {
        std::filesystem::path temp(subroutine_path);
        std::string name = temp.filename().string();
        size_t dot_position = name.find('.');
        if (dot_position != std::string::npos)
        {
            name.insert(dot_position, '(' + std::to_string(copy) + ')');
        }
        temp.replace_filename(std::filesystem::path(name));
        subroutine_path = temp.string();
        copy++;
    }
    subroutine_file.open("../subroutines/" + name + ".txt");
    subroutine_file << "FOLDER CENTRAL SUBROUTINE\n";
    subroutine_file << name << "\n";
    subroutine_file << origin << "\n";
    subroutine_file << destiny << "\n";
    subroutine_file.close();
}


void fcf::create_subroutine(std::string origin, std::string destiny, std::vector<std::string> types,
std::pair<std::time_t, std::time_t> dates, std::vector<std::string> authors)
{
    
}

void fcf::execute_minimal_subroutine(std::string& path)
{
    std::string origin;
    std::string destiny;
    path = fcf::raw_path(path);
    try 
    {
        if(std::filesystem::exists(std::filesystem::path(path)) && std::filesystem::is_regular_file(std::filesystem::path(path)))
        {
            ; //skip
        }
        else
        {
            std::stringstream mesage;
            mesage << "Subroutine file not found\n" << "File: " << __FILE__ << "\n" << "Line: " << __LINE__ << "\n";
            throw std::runtime_error(mesage.str());
        }
        if (std::filesystem::exists(std::filesystem::path(origin)) && std::filesystem::is_directory(std::filesystem::path(origin)))
        {
            ; //skip
        }
        else
        {
            std::stringstream mesage;
            mesage << "Subroutine file not found\n" << "File: " << __FILE__ << "\n" << "Line: " << __LINE__ << "\n";
            throw std::runtime_error(mesage.str());
        }
        if (std::filesystem::exists(std::filesystem::path(destiny)) && std::filesystem::is_directory(std::filesystem::path(destiny)))
        {
            ; //skip
        }
        else
        {
            std::stringstream mesage;
            mesage << "Subroutine file not found\n" << "File: " << __FILE__ << "\n" << "Line: " << __LINE__ << "\n";
            throw std::runtime_error(mesage.str());
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << "\n";
        std::exit(EXIT_FAILURE);
    }
    std::string line;
    std::ifstream file;
    std::vector<std::string> content;
    file.open(path);
    while (std::getline(file, line))
    {
        content.push_back(line);
    }
    try
    {
        if (content[0] == "FOLDER CENTRAL SUBROUTINE")
        {
            origin = content[2];
            destiny = content[3];
        }
        else 
        {
            std::stringstream mesage;
            mesage << "Path given is not a Subroutine\n" << "File: " << __FILE__ << "\n" << "Line: " << __LINE__ << "\n";
            throw std::runtime_error(mesage.str());
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << "\n";
        std::exit(EXIT_FAILURE);
    }
    file.close();
    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::path(origin)))
    {
        std::string file_path = entry.path().string();
        std::string new_path = destiny + '/' + entry.path().filename().string();
        int copy = 1;
        //This technically could create a buch of files but only if you execute a subroutine a whole bunch of times, maybe i'll add some security later
        while (std::filesystem::exists(std::filesystem::path(new_path)))
        {
            std::filesystem::path temp(new_path);
            std::string name = temp.filename().string();
            size_t dot_position = name.find('.');
            if (dot_position != std::string::npos)
            {
                name.insert(dot_position, '(' + std::to_string(copy) + ')');
            }
            temp.replace_filename(std::filesystem::path(name));
            new_path = temp.string();
            copy++;
        }
        std::filesystem::rename(std::filesystem::path(file_path), std::filesystem::path(new_path));
    }
}

std::vector<std::string> fcf::get_directory_subroutines(std::string path)
{
    path = fcf::raw_path(path);
    try
    {
        if (std::filesystem::exists(std::filesystem::path(path)) && std::filesystem::is_directory(std::filesystem::path(path)))
        {
            ; //skip
        }
        else
        {
            std::stringstream mesage;
            mesage << "Path given it's not a directory\n" << "File: " << __FILE__ << "\n" << "Line: " << __LINE__ << "\n";
            throw std::runtime_error(mesage.str());
        }
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << "\n";
        std::exit(EXIT_FAILURE);
    }
    std::vector<std::string> paths;
    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::path(path)))
    {
        std::string current_file = entry.path().string();
        std::cout << current_file.substr(current_file.length());
        if (current_file.substr(current_file.length() - 4) != ".txt")
        {
            continue;
        }
        if (!(std::filesystem::exists(std::filesystem::path(current_file))))
        {
            continue;
        }
        std::string line;
        std::ifstream file;
        std::vector<std::string> content;
        file.open(current_file);
        while (std::getline(file, line))
        {
            content.push_back(line);
        }
        if (content[0] != "FOLDER CENTRAL SUBROUTINE")
        {
            continue;
        }
        file.close();
        paths.push_back(current_file);
    }
    std::sort(paths.begin(), paths.end());
    return paths;
}