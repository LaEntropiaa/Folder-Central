#include "Functionality.h"

void fcf::create_file(std::string name)
{
    std::ofstream new_file(name);
    if (new_file.is_open())
    {
        new_file << "Testeo pa escribir en txt\n";
        new_file.close();
    }
    else
    {
        std::cout << "No che abrio el archivo";
        return;
    }
}