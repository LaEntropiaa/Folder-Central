#include "Errors.h"

InvalidPath::InvalidPath()
{
    this->mesage = "Directory or file not found";
}

InvalidPath::InvalidPath(const std::string& mesage, const char* file, int line)
{
    this->mesage = "Error:" + mesage + "\n" + "File: " + file + "\n" + "Line: " + std::to_string(line);
}

const char* InvalidPath::what() const throw()
{
    return this->mesage.c_str();
}

