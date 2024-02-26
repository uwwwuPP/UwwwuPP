#include <CharTools.h>
#include "Catch2.h"

TEST_CASE(__FILE__"/LowerToUpper_NoSymbols", "[Char][MakeLower]")
{
    // Setup
    const std::string in        = "NEWALBUMCOWBOYTEARSOUTFEBRUARYIAMEXCITED";
    const std::string expected  = "newalbumcowboytearsoutfebruaryiamexcited";

    // Exercise
    std::string out = in;
    for (char& c : out)
        c = CharTools::MakeLower(c);

    // Verify:
    REQUIRE(out == expected);
}

TEST_CASE(__FILE__"/LowerToUpper_Symbols", "[Char][MakeLower]")
{
    // Setup
    const std::string in        = "NEW ALBUM 'COWBOY TEARS' OUT FEBRUARY 18! I AM EXCITED!";
    const std::string expected  = "new album 'cowboy tears' out february 18! i am excited!";

    // Exercise
    std::string out = in;
    for (char& c : out)
        c = CharTools::MakeLower(c);

    // Verify:
    REQUIRE(out == expected);
}

TEST_CASE(__FILE__"/LowerToUpper_Mixed_And_Symbols", "[Char][MakeLower]")
{
    // Setup
    const std::string in        = "New album 'Cowboy Tears' out February 18! I am excited!";
    const std::string expected  = "new album 'cowboy tears' out february 18! i am excited!";

    // Exercise
    std::string out = in;
    for (char& c : out)
        c = CharTools::MakeLower(c);

    // Verify:
    REQUIRE(out == expected);
}
