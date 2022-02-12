#include <Util.h>
#include "Catch2.h"

// Test that putting in an empty string returns an empty string
TEST_CASE(__FILE__"/EmptyInputString", "[]")
{
    // Setup
    const std::string in = "";
    const std::string expected = "";

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(in, "findme", "putme");

    // Verify
    REQUIRE(result == expected);
}

// Tests that simple replacing works
TEST_CASE(__FILE__"/SimpleReplacing", "[]")
{
    // Setup
    const std::string in = "Hello $user, you must be $user, so i am calling you $user.";
    const std::string expected = "Hello bob, you must be bob, so i am calling you bob.";

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(in, "$user", "bob");

    // Verify
    REQUIRE(result == expected);
}

// Find-string is empty
TEST_CASE(__FILE__"/FindEmpty", "[]")
{
    // Setup
    const std::string in = "Hello $user, you must be $user, so i am calling you $user.";
    const std::string expected = in;

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(in, "", "bob");

    // Verify
    REQUIRE(result == expected);
}

// Sub-string is empty
TEST_CASE(__FILE__"/SubEmpty", "[]")
{
    // Setup
    const std::string in = "Hello $user, you must be $user, so i am calling you $user.";
    const std::string expected = "Hello , you must be , so i am calling you .";

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(in, "$user", "");

    // Verify
    REQUIRE(result == expected);
}

// Usual use-case
TEST_CASE(__FILE__"/KeepSigns", "[]")
{
    // Setup
    const std::string in = "Hello Alice, lowercase alice, WTF ALICE?!";
    const std::string expected = "Hello Bob, lowercase bob, WTF BOB?!";

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(in, "alice", "bob");

    // Verify
    REQUIRE(result == expected);
}

// Sub-string is longer than find-string
TEST_CASE(__FILE__"/ExtrapolateSigns", "[]")
{
    // Setup
    const std::string in = "Hi Alice. HI Alice. hi Alice. hI Alice. HIalice. hiALICE.";
    const std::string expected = "Hello Alice. HELLO Alice. hello Alice. hELLO Alice. HElloalice. heLLOALICE.";

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(in, "hi", "hello");

    // Verify
    REQUIRE(result == expected);
}

// Tests that not replacing anything (by callback) returns the original string
TEST_CASE(__FILE__"/RejectingAllReplacementsChangesNothing", "[]")
{
    // Setup
    const std::string in = "Hello, i am a generic string with a lot of e's. It would be a shame of any of these e's were lost, wouldn't it?";
    const std::string expected = in;

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(
            in,
            "e",
            "hello",
            [](auto, auto){ return false; } // Reject all replacements
    );

    // Verify
    REQUIRE(result == expected);
}

// Tests that the callback returns the correct index for a finding
TEST_CASE(__FILE__"/Callback_Index_Matches", "[]")
{
    // Setup
    const std::string in = "Hello, banana.";
    const std::string expected = in;

    // Exercise
    Util::ConditionalReplaceButKeepSigns(
            in,
            "banana",
            "hello",
            [](const std::string& finding, const std::size_t index) -> bool {
                REQUIRE(index == 7);
                return true;
            }
    );
}

// Tests that the callback returns the correct substring of a finding
TEST_CASE(__FILE__"/Callback_Finding_Matches", "[]")
{
    // Setup
    const std::string in = "Hello, BANAna.";
    const std::string expected = in;

    // Exercise
    Util::ConditionalReplaceButKeepSigns(
            in,
            "banana",
            "hello",
            [](const std::string& finding, const std::size_t index) -> bool {
                REQUIRE(finding == "BANAna");
                return true;
            }
    );
}

// Tests that the callback function works, here we will be rejecting every other finding
TEST_CASE(__FILE__"/Callback_Conditional_Rejecting_Works", "[]")
{
    // Setup
    const std::string in = "ding ding Ding Ding Ding Ding DING DING";
    const std::string expected = "ding dong Ding Dong Ding Dong DING DONG";

    std::size_t counter = 1; // Start one cycle off
    std::size_t* ptrCounter = &counter;

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(
            in,
            "ding",
            "dong",
            [ptrCounter](const std::string& finding, const std::size_t index) -> bool {
                return (++*ptrCounter) % 2;
            }
    );

    // Verify
    REQUIRE(expected == result);
}

// Tests that replacing symbols works... Why ever you would use this method for this...
TEST_CASE(__FILE__"/ReplaceSymbols", "[]")
{
    // Setup
    const std::string in = "Hello. I like you.";
    const std::string expected = "Hello! I like you!";

    // Exercise
    const std::string result = Util::ConditionalReplaceButKeepSigns(
            in,
            ".",
            "!"
    );

    // Verify
    REQUIRE(result == expected);
}
