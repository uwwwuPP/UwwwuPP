#include <CharTools.h>
#include "Catch2.h"

// Tests character sign by checking it against a map
TEST_CASE(__FILE__"/MapTest", "[Char][IsLower]")
{
    // Setup
    const std::string in  = "New album 'Cowboy Tears' out February 18! I am excited!";
    const std::string map = "0110111110001111100111100111001111111000000011011111110"; // 1 -> lowercase, 0 -> not lowercase

    // Verify that I didn't frick up compiling the map by hand
    if (in.length() != map.length())
        FAIL("map.size() does not match in.size(). (" << in.length() << " : " << map.length() << ")");

    // Exercise & Verify
    for (std::size_t i = 0; i < in.size(); i++)
        if (CharTools::IsLower(in[i]) != (map[i] == '1'))
            FAIL("'" << in[i] << "' differs from the map. Map says '" << map[i] << "', 1-> is a lowercase. Check first if the map is wrong, before trying to debug.");
}
