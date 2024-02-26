#include <iostream>
#include <StringTools.h>

int main()
{
    std::cout << StringTools::Replace("Hello, ${where}!\n", "${where}", "World") << std::endl;

    return 0;
}
