#include <StringTools.h>
#include "Catch2.h"

// Tests that replacing something in an empty string returns an empty string
TEST_CASE(__FILE__"/EmptyString", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "";

    // Exercise
    const std::string out = StringTools::Replace(in, 'a', "Subst");

    // Verify
    REQUIRE(out == "");
    return;
}

// Tests that replacing a char to an empty string works
TEST_CASE(__FILE__"/Single_ReplaceToEmpty", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "i";

    // Exercise
    const std::string out = StringTools::Replace(in, 'i', "");

    // Verify
    REQUIRE(out == "");
    return;
}

// Tests that replacing to a single char works
TEST_CASE(__FILE__"/Single_ReplaceToSingleChar", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "a";

    // Exercise
    const std::string out = StringTools::Replace(in, 'a', "i");

    // Verify
    REQUIRE(out == "i");
    return;
}

// Tests that replacing to a single char works, passing a char
TEST_CASE(__FILE__"/Single_ReplaceToSingleChar_AsChar", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "Oilbanger";

    // Exercise
    const std::string out = StringTools::Replace(in, 'a', 'i');

    // Verify
    REQUIRE(out == "Oilbinger");
    return;
}

// Tests that replacing the find to something longer works
TEST_CASE(__FILE__"/Single_ReplaceToLonger", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "Littled";

    // Exercise
    const std::string out = StringTools::Replace(in, 'd', "binger");

    // Verify
    REQUIRE(out == "Littlebinger");
    return;
}

// Tests that replacing a char to an empty string works
TEST_CASE(__FILE__"/Multiple_ReplaceToEmpty", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "dirty dogs dig dirt daringly";

    // Exercise
    const std::string out = StringTools::Replace(in, 'd', "");

    // Verify
    REQUIRE(out == "irty ogs ig irt aringly");
    return;
}

// Tests that replacing to a single char works
TEST_CASE(__FILE__"/Multiple_ReplaceToSingleChar", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "Oilbanger, Bangerfanger, Lattle brattle oaly skattle.";

    // Exercise
    const std::string out = StringTools::Replace(in, 'a', "i");

    // Verify
    REQUIRE(out == "Oilbinger, Bingerfinger, Little brittle oily skittle.");
    return;
}

// Tests that replacing to a single char works, passing a char
TEST_CASE(__FILE__"/Multiple_ReplaceToSingleChar_AsChar", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "Oilbanger, Bangerfanger, Lattle brattle oaly skattle.";

    // Exercise
    const std::string out = StringTools::Replace(in, 'a', 'i');

    // Verify
    REQUIRE(out == "Oilbinger, Bingerfinger, Little brittle oily skittle.");
    return;
}

// Tests that replacing the find to something longer works
TEST_CASE(__FILE__"/Multiple_ReplaceToLonger", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "d d d d d d d d";

    // Exercise
    const std::string out = StringTools::Replace(in, 'd', "bla");

    // Verify
    REQUIRE(out == "bla bla bla bla bla bla bla bla");
    return;
}

// Tests that the replacer ignores chars put in by the replacer
TEST_CASE(__FILE__"/ReplacerIgnoresReplaced", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "b b b b b b b b";

    // Exercise
    const std::string out = StringTools::Replace(in, 'b', "bla");

    // Verify
    REQUIRE(out == "bla bla bla bla bla bla bla bla");
    return;
}

// Tests that replacing succesive findings works
TEST_CASE(__FILE__"/Replace_Successive", "[Strings][ReplaceChar]")
{
    // Setup
    const std::string in = "bbbbbbbb";

    // Exercise
    const std::string out = StringTools::Replace(in, 'b', "bla");

    // Verify
    REQUIRE(out == "blablablablablablablabla");
    return;
}
