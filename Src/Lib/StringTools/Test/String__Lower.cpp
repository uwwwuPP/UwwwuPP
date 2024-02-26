#include <StringTools.h>
#include "Catch2.h"

// Tests that lowering an empty string returns an empty string
TEST_CASE(__FILE__"/EmptyString", "[Strings][Lower]")
{
    // Setup
    const std::string in = "";

    // Exercise
    const std::string out = StringTools::Lower(in);

    // Verify
    REQUIRE(out == "");
    return;
}

// Tests that lowering a string without any letters returns itself
TEST_CASE(__FILE__"/Symbols", "[Strings][Lower]")
{
    // Setup
    const std::string in = "66! _-\n*";

    // Exercise
    const std::string out = StringTools::Lower(in);

    // Verify
    REQUIRE(out == "66! _-\n*");
    return;
}

// Tests that lowering a string of lowercase letters returns itself
TEST_CASE(__FILE__"/AlreadyLowered", "[Strings][Lower]")
{
    // Setup
    const std::string in = "ughareyouserious";

    // Exercise
    const std::string out = StringTools::Lower(in);

    // Verify
    REQUIRE(out == "ughareyouserious");
    return;
}

// Tests that lowering a string of uppercase letters returns the lowercase version
TEST_CASE(__FILE__"/Uppercase", "[Strings][Lower]")
{
    // Setup
    const std::string in = "UGHAREYOUSERIOUS";

    // Exercise
    const std::string out = StringTools::Lower(in);

    // Verify
    REQUIRE(out == "ughareyouserious");
    return;
}

// Tests that lowering a string of uppercase, lowercase letters and symbols returns the lowercase version
TEST_CASE(__FILE__"/Mixed", "[Strings][Lower]")
{
    // Setup
    const std::string in = "Ugh, Are You Serious?! DON'T DO THAT!!!";

    // Exercise
    const std::string out = StringTools::Lower(in);

    // Verify
    REQUIRE(out == "ugh, are you serious?! don't do that!!!");
    return;
}
