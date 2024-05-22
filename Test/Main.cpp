#include <iostream>
#include "Functionality.h"


int main()
{

    std::vector<std::string> paths = fcf::get_directory_subroutines(R"(C:\Users\aadri\Desktop\Coding\Repositories\Folder-Central\subroutines)");
    for (const std::string& entry : paths)
    {
        std::cout << entry << "\n";
    }
    std::cout << paths.size();
    std::cout << "hi";

    return 0;
}