#include <CharTools.h>
#include "Catch2.h"

TEST_CASE(__FILE__"/JustChars", "[Char][CopySign]")
{
    // Setup
    // Correct letters
    const std::string in        = "tHEEuEUROPEanunioNCOnsiStsOFStATESIncLudingGERmanySWedenAndfRanCE";
    // Correct signs
    const std::string signs     = "AaaAAApqlkzicZnionceroigjreiojiopjaopickwapPjfipojWqfpohoijFucmwp";
    // Correct signs and letters
    const std::string expected  = "TheEUEuropeanUnionconsistsofstatesincludingGermanySwedenandFrance";

    // Exercise
    std::string out = in;
    for (std::size_t i = 0; i < in.size(); i++)
    {
        const char cs = signs[i];
        char& co = out[i];
        co = CharTools::CopySign(cs, co);
    }

    // Verify:
    REQUIRE(out == expected);
}

TEST_CASE(__FILE__"/WithSymbols", "[Char][CopySign]")
{
    // Setup
    // Correct letters
    const std::string in        = "ThE eu (euRoPeAN uNIon) cONsiSts Of 20 STAtes, iNCLUDInG GeRMAnY, sweden, aND fRancE.";
    // Correct signs
    const std::string signs     = "DwefOPerKofkaqdioJeriofgjqeiopqwqefijoqgehjloivxcvmopfkuoQpwfioqjiOqgjeprjgnvqPemrqij";
    // Correct signs and letters
    const std::string expected  = "The EU (European Union) consists of 20 states, including Germany, Sweden, and France.";

    // Exercise
    std::string out = in;
    for (std::size_t i = 0; i < in.size(); i++)
    {
        const char cs = signs[i];
        char& co = out[i];
        co = CharTools::CopySign(cs, co);
    }

    // Verify:
    REQUIRE(out == expected);
}

TEST_CASE(__FILE__"/DoesntChangeSignsIfSymbolSupplied", "[Char][CopySign]")
{
    // Setup
    const std::string in        = "ThE eu (euRoPeAN uNIon) cONsiSts Of 20 STAtes, iNCLUDInG GeRMAnY, sweden, aND fRancE.";
    const std::string signs     = "!§$)=%164)';:'*?)/!?/&()()?)*'_;:_,.93ß04750928372!!$==)()/!§$)=%)*'';:'*?)/!1572?/&(";
    const std::string expected  = in;

    // Exercise
    std::string out = in;
    for (std::size_t i = 0; i < in.size(); i++)
    {
        const char cs = signs[i];

        char& co = out[i];
        co = CharTools::CopySign(cs, co);
    }

    // Verify:
    REQUIRE(out == expected);
}