#include <CharTools.h>
#include "Catch2.h"
#include <iostream>

// Tests character sign by checking it against a map
TEST_CASE(__FILE__"/MapTest", "[Char][IsUpper]")
{
    // Setup
    const std::string in  = "New album 'Cowboy Tears' out February 18! I am excited!";
    const std::string map = "1000000000010000001000000000010000000000001000000000000"; // 1 -> uppercase, 0 -> not uppercase

    // Verify that I didn't frick up compiling the map by hand
    if (in.length() != map.length())
        FAIL("map.size() does not match in.size(). (" << in.length() << " : " << map.length() << ")");

    // Exercise & Verify
    for (std::size_t i = 0; i < in.size(); i++)
        if (CharTools::IsUpper(in[i]) != (map[i] == '1'))
            FAIL("'" << in[i] << "' differs from the map. Map says '" << map[i] << "', 1-> is an uppercase. Check first if the map is wrong, before trying to debug.");
}
