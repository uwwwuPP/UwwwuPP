#include <StringTools.h>
#include "Catch2.h"

// Tests that replacing something in an empty string returns an empty string
TEST_CASE(__FILE__"/EmptyString", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "";

    // Exercise
    const std::string out = StringTools::Replace(in, "burger", "Subst");

    // Verify
    REQUIRE(out == "");
    return;
}

// Tests that replacing a string to an empty string works
TEST_CASE(__FILE__"/Single_ReplaceToEmpty", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "Squarepants";

    // Exercise
    const std::string out = StringTools::Replace(in, "Squarepants", "");

    // Verify
    REQUIRE(out == "");
    return;
}

// Tests that replacing to a single char works
TEST_CASE(__FILE__"/Single_ReplaceToSingleChar", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "Squarepants";

    // Exercise
    const std::string out = StringTools::Replace(in, "Squarepants", "i");

    // Verify
    REQUIRE(out == "i");
    return;
}

// Tests that replacing to a single char works, passing a char
TEST_CASE(__FILE__"/Single_ReplaceToSingleChar_AsChar", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "Oilbanger";

    // Exercise
    const std::string out = StringTools::Replace(in, "Oilbanger", 'i');

    // Verify
    REQUIRE(out == "i");
    return;
}

// Tests that replacing the find to something longer works
TEST_CASE(__FILE__"/Single_ReplaceToLonger", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "LittleDong";

    // Exercise
    const std::string out = StringTools::Replace(in, "Dong", "Binger");

    // Verify
    REQUIRE(out == "LittleBinger");
    return;
}

// Tests that replacing a string to an empty string works
TEST_CASE(__FILE__"/Multiple_ReplaceToEmpty", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "The fucking dogs are fucking eating the fucking chicken.";

    // Exercise
    const std::string out = StringTools::Replace(in, "fucking ", "");

    // Verify
    REQUIRE(out == "The dogs are eating the chicken.");
    return;
}

// Tests that replacing to a single char works
TEST_CASE(__FILE__"/Multiple_ReplaceToSingleChar", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "Oilbsmearynger, Bsmearyngerfsmearynger, Lsmearyttle brsmearyttle osmearyly sksmearyttle.";

    // Exercise
    const std::string out = StringTools::Replace(in, "smeary", "i");

    // Verify
    REQUIRE(out == "Oilbinger, Bingerfinger, Little brittle oily skittle.");
    return;
}

// Tests that replacing to a single char works, passing a char
TEST_CASE(__FILE__"/Multiple_ReplaceToSingleChar_AsChar", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "Oilbsmearynger, Bsmearyngerfsmearynger, Lsmearyttle brsmearyttle osmearyly sksmearyttle.";

    // Exercise
    const std::string out = StringTools::Replace(in, "smeary", 'i');

    // Verify
    REQUIRE(out == "Oilbinger, Bingerfinger, Little brittle oily skittle.");
    return;
}

// Tests that replacing the find to something longer works
TEST_CASE(__FILE__"/Multiple_ReplaceToLonger", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "honk honk honk honk honk honk honk honk";

    // Exercise
    const std::string out = StringTools::Replace(in, "honk", "hallery");

    // Verify
    REQUIRE(out == "hallery hallery hallery hallery hallery hallery hallery hallery");
    return;
}

// Tests that the replacer ignores chars put in by the replacer
TEST_CASE(__FILE__"/ReplacerIgnoresReplaced", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "honk honk honk honk honk honk honk honk";

    // Exercise
    const std::string out = StringTools::Replace(in, "honk", "honka");

    // Verify
    REQUIRE(out == "honka honka honka honka honka honka honka honka");
    return;
}

// Tests that replacing successive findings works
TEST_CASE(__FILE__"/Replace_Successive", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "honkhonkhonkhonkhonkhonkhonkhonk";

    // Exercise
    const std::string out = StringTools::Replace(in, "honk", "hallery");

    // Verify
    REQUIRE(out == "halleryhalleryhalleryhalleryhalleryhalleryhalleryhallery");
    return;
}

// Tests that if find.length() == 0, it returns just the input
TEST_CASE(__FILE__"/Find_Length0_Returns_Input", "[Strings][ReplaceString]")
{
    // Setup
    const std::string in = "Littled";

    // Exercise
    const std::string out = StringTools::Replace(in, "", "binger");

        // Verify
        REQUIRE(out == "Littled");
    return;
}
