#include <StringTools.h>
#include "Catch2.h"

// Tests that uppering an empty string returns an empty string
TEST_CASE(__FILE__"/EmptyString", "[Strings][Upper]")
{
    // Setup
    const std::string in = "";

    // Exercise
    const std::string out = StringTools::Upper(in);

    // Verify
    REQUIRE(out == "");
    return;
}

// Tests that uppering a string without any letters returns itself
TEST_CASE(__FILE__"/Symbols", "[Strings][Upper]")
{
    // Setup
    const std::string in = "66! _-\n*";

    // Exercise
    const std::string out = StringTools::Upper(in);

    // Verify
    REQUIRE(out == "66! _-\n*");
    return;
}

// Tests that uppering a string of uppercase letters returns itself
TEST_CASE(__FILE__"/AlreadyUppered", "[Strings][Upper]")
{
    // Setup
    const std::string in = "UGHAREYOUSERIOUS";

    // Exercise
    const std::string out = StringTools::Upper(in);

    // Verify
    REQUIRE(out == "UGHAREYOUSERIOUS");
    return;
}

// Tests that uppering a string of lowercase letters returns the uppercase version
TEST_CASE(__FILE__"/Lowercase", "[Strings][Upper]")
{
    // Setup
    const std::string in = "ughareyouserious";

    // Exercise
    const std::string out = StringTools::Upper(in);

    // Verify
    REQUIRE(out == "UGHAREYOUSERIOUS");
    return;
}

// Tests that uppering a string of uppercase, lowercase letters and symbols returns the uppercase version
TEST_CASE(__FILE__"/Mixed", "[Strings][Upper]")
{
    // Setup
    const std::string in = "Ugh, Are You Serious?! DON'T do that!!!";

    // Exercise
    const std::string out = StringTools::Upper(in);

    // Verify
    REQUIRE(out == "UGH, ARE YOU SERIOUS?! DON'T DO THAT!!!");
    return;
}
