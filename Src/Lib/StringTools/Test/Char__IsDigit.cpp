#include <CharTools.h>
#include "Catch2.h"

// Tests character digit-ness by checking it against a map
TEST_CASE(__FILE__"/MapTest", "[Char][IsUpper]")
{
    // Setup
    const std::string in  = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHJIKLMNOPQRSTUVWXYZ!&/()=?*'#-.,;:_";
    const std::string map = "000000000000000000000000001111111111000000000000000000000000000000000000000000";
    // 0 -> no digit, 1 -> digit

    // Verify that I didn't frick up compiling the map by hand
    if (in.length() != map.length())
        FAIL("map.size() does not match in.size(). (" << in.length() << " : " << map.length() << ")");

    // Exercise & Verify
    for (std::size_t i = 0; i < in.size(); i++)
        if (CharTools::IsDigit(in[i]) != (map[i] == '1'))
            FAIL("'" << in[i] << "' differs from the map. Map says '" << map[i] << "', 1-> is a digit. Check first if the map is wrong, before trying to debug.");
}
