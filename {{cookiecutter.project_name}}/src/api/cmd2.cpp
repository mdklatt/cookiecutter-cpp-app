/// Implemenation of the cmd1 sample command.
///
#include <iostream>
#include "api.hpp"


void cmd2(const std::string& arg)
{
    std::cout << "cmd1 called with argument " << arg << std::endl;
    return;
}
