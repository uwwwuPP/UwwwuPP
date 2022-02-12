#include <iostream>
#include <StringTools.h>
#include <CharTools.h>
#include <string>
#include <sstream>
#include <functional>
#include <random>
#include "Util.h"

//! Will make a boring string look sooper dooper kawaii and cute :3
std::string MakeUwu(std::string boringString) {
    // Easy ones first
    // none, lol

    // Slightly more complex... Multichar replacements, but we have to keep capitalization...
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "th", "tw");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "ove", "uv");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "have", "haf");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "tr", "tw");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "up", "uwp");

    // Let's do some language adjustments
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "twank you", "you're twe best <3333 xoxo");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "good", "sooper dooper");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "suwper", "sooper dooper");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "well", "sooper dooper");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "emacs", "vim");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "twanks", "you're twe best :33 xoxo");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "hello", "hiiiiiii");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "dear", "hiiiiiii");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "hi", "hiiiiiii");

    // Replace N with Ny, but only if succeeded by a vowel, and not preceded by an o: "one" has such a niche pronunciation.
    boringString = Util::ConditionalReplaceButKeepSigns(
            boringString,
            "n",
            "ny",
            [boringString](const std::string &found, int index) {
                // Don't replace, if we are on the last char
                if (index + found.length() == boringString.length() - 1)
                    return false;

                const char nextChar = CharTools::MakeLower(boringString[index + found.length()]);
                const char lastChar = CharTools::MakeLower(boringString[index - 1]);

                // Don't replace if the last char is an 'o'
                if (lastChar == 'o')
                    return false;

                // Is this a vowel?
                if (CharTools::IsVowel(nextChar))
                    return true;

                // Else, don't replace
                return false;
            }
    );

    // Replace R with W, but only if not succeeded by a non-vowel, and if it's not the first character of a word
    boringString = Util::ConditionalReplaceButKeepSigns(
            boringString,
            "r",
            "w",
            [boringString](const std::string &found, const std::size_t index) {
                // Don't replace, if we are on the last char
                if (index + found.length() == boringString.length() - 1)
                    return false;

                // Don't replace if we're at index 0
                if (index == 0)
                    return false;

                const char nextChar = CharTools::MakeLower(boringString[index + found.length()]);
                const char lastChar = CharTools::MakeLower(boringString[index - 1]);

                // Is this a non-vowel?
                if (!CharTools::IsVowel(nextChar))
                    return false;

                // Don't replace if the last char is not a letter
                if (!CharTools::IsLetter(lastChar))
                    return false;

                // Else, replace
                return true;
            }
    );

    // Replace L with W, but only if not followed or preceded by another L, and if it's not the first character of a word
    boringString = Util::ConditionalReplaceButKeepSigns(
            boringString,
            "l",
            "w",
            [boringString](const std::string &found, int index) {
                // Our segment has to be at least two characters long
                if (boringString.length() < found.length() + 2)
                    return false;

                // Don't replace if we're at index o
                if (index == 0)
                    return false;

                const char lastChar = CharTools::MakeLower(boringString[index - 1]);
                const char nextChar = CharTools::MakeLower(boringString[index + found.length()]);

                // Don't replace if the last char is not a letter
                if (!CharTools::IsLetter(lastChar))
                    return false;

                return (lastChar != 'l') && (nextChar != 'l');
            }
    );

    // Replace LL with WW, but only if followed by a vowel
    boringString = Util::ConditionalReplaceButKeepSigns(
            boringString,
            "ll",
            "ww",
            [boringString](const std::string &found, int index) {
                // Don't replace, if we are on the last char
                if (index + found.length() == boringString.length() - 1)
                    return false;

                const char nextChar = CharTools::MakeLower(boringString[index + found.length()]);

                return CharTools::IsVowel(nextChar);
            }
    );

    // Replace ER with A, but only if it's the last two letters of a word
    boringString = Util::ConditionalReplaceButKeepSigns(
            boringString,
            "er",
            "a",
            [boringString](const std::string &found, int index) {
                // Replace if we're at the end of this line/segment
                if (index + found.length() == boringString.length() - 1)
                    return false;

                // Fetch the next char
                const char nextChar = CharTools::MakeLower(boringString[index + found.length()]);

                // Replace if the next char is not a letter
                return CharTools::IsLetter(nextChar) == false;
            }
    );

    // Replace random punctuation with uwwwwu cute symbols
    // About evewy fifteenth symbol
    std::stringstream ss;
    std::mt19937 rng(std::hash<std::string>()(boringString)); // Seed rng based on string
    for (const char c : boringString)
    {
        if ((c == '.') && (rng() % 15 == 0))
        {
            ss << " <3333 ^.^ ";
        }
        else if ((c == '!') && (rng() % 15 == 0))
        {
            ss << "!! Thadws impowtant! <3 ";
        }
        else if ((c == ',') && (rng() % 15 == 0))
        {
            ss << " <3 aaaaaand ";
        }
        else if ((c == '?') && (rng() % 15 == 0))
        {
            ss << "?? now tell me! >:( ";
        }
        else
            ss << c;
    }
    boringString = ss.str();

    // Also replace some ascii-"emojis'
    boringString = StringTools::Replace(boringString, ":)", "UwU :D");
    boringString = StringTools::Replace(boringString, ":D", ":3");
    boringString = StringTools::Replace(boringString, ":-)", "UwwwU :3");
    boringString = StringTools::Replace(boringString, "^^", "^.^ UwU");

    // Some language replacement should happen after these more complex rules
    boringString = Util::HeConditionalReplaceButKeepSigns(boringString, "c++", "c++ (rust is hella cutewr btw ^^)");


    return boringString;
}

int main(int argc, char** argv) {

    // We have arguments. Uwwuifie these instead
    if (argc > 1)
    {
        // We have to put the args together first, because some replace-rules cross word-borders
        std::stringstream  ss;
        for (std::size_t i = 1; i < argc; i++)
            ss << std::string(argv[i]) + " ";

        std::cout << MakeUwu(ss.str()) << std::endl;
    }

    // Else, be prepared to get __piped__
    else
    {
        std::string buf;
        while (std::getline(std::cin, buf))
            std::cout << MakeUwu(buf) << std::endl;

    }

    return 0;
}
