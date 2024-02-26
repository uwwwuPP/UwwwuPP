#include <CharTools.h>
#include "Catch2.h"

TEST_CASE(__FILE__"/LowerToUpper_NoSymbols", "[Char][MakeUpper]")
{
    // Setup
    const std::string in        = "newalbumcowboytearsoutfebruaryiamexcited";
    const std::string expected  = "NEWALBUMCOWBOYTEARSOUTFEBRUARYIAMEXCITED";

    // Exercise
    std::string out = in;
    for (char& c : out)
        c = CharTools::MakeUpper(c);

    // Verify:
    REQUIRE(out == expected);
}

TEST_CASE(__FILE__"/LowerToUpper_Symbols", "[Char][MakeUpper]")
{
    // Setup
    const std::string in        = "new album 'Cowboy Tears' out february 18! i am excited!";
    const std::string expected  = "NEW ALBUM 'COWBOY TEARS' OUT FEBRUARY 18! I AM EXCITED!";

    // Exercise
    std::string out = in;
    for (char& c : out)
        c = CharTools::MakeUpper(c);

    // Verify:
    REQUIRE(out == expected);
}

TEST_CASE(__FILE__"/LowerToUpper_Mixed_And_Symbols", "[Char][MakeUpper]")
{
    // Setup
    const std::string in        = "New album 'Cowboy Tears' out February 18! I am excited!";
    const std::string expected  = "NEW ALBUM 'COWBOY TEARS' OUT FEBRUARY 18! I AM EXCITED!";

    // Exercise
    std::string out = in;
    for (char& c : out)
        c = CharTools::MakeUpper(c);

    // Verify:
    REQUIRE(out == expected);
}
