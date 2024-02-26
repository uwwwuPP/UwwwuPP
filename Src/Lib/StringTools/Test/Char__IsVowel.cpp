#include <CharTools.h>
#include "Catch2.h"

// Tests character vowel-ness by checking it against a map
TEST_CASE(__FILE__"/MapTest", "[Char][IsVowel]")
{
    // Setup
    const std::string in  = "New album 'Cowboy Tears' out February 18! I am excited!";
    const std::string map = "0100100100001001100110000110001001101000001010010010100"; // 0 -> no vowel, 1 -> vowel

    // Verify that I didn't frick up compiling the map by hand
    if (in.length() != map.length())
        FAIL("map.size() does not match in.size(). (" << in.length() << " : " << map.length() << ")");

    // Exercise & Verify
    for (std::size_t i = 0; i < in.size(); i++)
        if (CharTools::IsVowel(in[i]) != (map[i] == '1'))
            FAIL("'" << in[i] << "' differs from the map. Map says '" << map[i] << "', 1-> is a vowel. Check first if the map is wrong, before trying to debug.");
}
