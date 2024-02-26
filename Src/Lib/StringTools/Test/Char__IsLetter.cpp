#include <CharTools.h>
#include "Catch2.h"

// Tests character letter-ness by checking it against a map
TEST_CASE(__FILE__"/MapTest", "[Char][IsLetter]")
{
    // Setup
    const std::string in  = "New album 'Cowboy Tears' out February 18! I am excited!";
    const std::string map = "1110111110011111101111100111011111111000001011011111110"; // 0 -> no letter, 1 -> letter

    // Verify that I didn't frick up compiling the map by hand
    if (in.length() != map.length())
        FAIL("map.size() does not match in.size(). (" << in.length() << " : " << map.length() << ")");

    // Exercise & Verify
    for (std::size_t i = 0; i < in.size(); i++)
        if (CharTools::IsLetter(in[i]) != (map[i] == '1'))
            FAIL("'" << in[i] << "' differs from the map. Map says '" << map[i] << "', 1-> is a letter. Check first if the map is wrong, before trying to debug.");
}
