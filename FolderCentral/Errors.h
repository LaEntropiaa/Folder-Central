#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <string>

class InvalidPath : public std::exception
{
private:
    std::string mesage;
public:
    InvalidPath();    
    InvalidPath(const std::string& mesage, const char* file, int line);
    const char* what() const throw() override;
};

#endif
