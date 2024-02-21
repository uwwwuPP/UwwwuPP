#include <iostream>
#include "LibUwu.h"

int main(int argc, char** argv)
{
    // We have arguments. Uwwuify these instead
    if (argc > 1)
    {
        // We have to put the args together first, because some replace-rules cross word-borders
        std::stringstream ss;
        for (std::size_t i = 1; i < argc; i++) {
            ss << std::string(argv[i]) + " ";
        }

        std::cout << MakeUwu(ss.str()) << std::endl;
    }
    // Else, be prepared to get __piped__
    else
    {
        std::string buf;
        while (std::getline(std::cin, buf)) {
            std::cout << buf << std::endl;
        }
    }

    return 0;
}
