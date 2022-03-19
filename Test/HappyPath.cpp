#include <LibUwu.h>
#include "Catch2.h"

// Tests that the program doesnt crash with random input
TEST_CASE(__FILE__"/DoesntCrash", "[]")
{
    SECTION("0") { MakeUwu("nine"); }
    SECTION("1") { MakeUwu("nintendo"); }
    SECTION("2") { MakeUwu("one"); }
    SECTION("3") { MakeUwu("rally"); }
    SECTION("4") { MakeUwu("lary"); }
    SECTION("5") { MakeUwu("larry"); }
    SECTION("6") { MakeUwu("wally"); }
    SECTION("7") { MakeUwu("waly"); }
    SECTION("8") { MakeUwu("gardener"); }
    SECTION("9") { MakeUwu("german"); }
}
