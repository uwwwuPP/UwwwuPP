#include <iostream>
#include <StringTools/Stringtools.h>
#include <string>
#include <sstream>
#include <functional>

constexpr char UPPERCASE = (1<<5);
constexpr char LOWERCASE = 0;

bool IsVowel(char c) {
    const std::string vowels = "euioa";
    for (const char vowel : vowels)
        if (vowel == c)
            return true;

    return false;
}

bool IsUpper(char c) {
    return !(c & (1<<5));
}

char MakeUpper(char c) {
    if (IsUpper(c))
        return c;
    else
        return c & ~(1<<5);
}

char MakeLower(char c) {
    if (!IsUpper(c))
        return c;
    else
        return c | (1<<5);
}

char CopySign(char sign, char c) {
    if (IsUpper(sign))
        return MakeUpper(c);
    else
        return MakeLower(c);
}

std::string ReplaceButKeepCapitalization(
        const std::string& str,
        std::string find,
        const std::string& sub,
        std::function<bool(const std::string&, int)> onlyIf = [](const std::string&, int){return true;}
) {

    // Quick accepts-and rejects
    if (str.length() == 0)
        return "";
    else if (find.length() == 0)
        return str;

    std::stringstream ss;

    // Better safe than sorry
    find = StringTools::Lower(find);

    for (std::size_t i = 0; i < str.length(); i++)
    {
        const std::string foundInText = str.substr(i, find.length());
        const std::string foundInText_lower = StringTools::Lower(foundInText);
        if (foundInText_lower == find)
        {
            // Advance i accordingly
            i += foundInText.length()-1;

            // Ask the callback if we should replace this one
            if (onlyIf(foundInText, i))
            {
                // Here we've found our occurrence...
                // We have three possible cases:
                // 1: len(find) == len(sub), in this case we want to sync capitalization by index.
                // 2: len(find) < len(sub), in this case we sync by index, BUT...
                // 3: len(find) > len(sub): sync capitalization by index

                // We want to sync capitalization by index
                // This accounts for both cases: 1 and 3
                if (foundInText.length() >= sub.length())
                {
                    for (std::size_t j = 0; j < sub.length(); j++)
                    {
                        const char cf = foundInText[j];
                        const char cs = sub[j];

                        ss << CopySign(cf, cs);
                    }
                }

                // in this case we sync by index, BUT...
                else if (foundInText.length() < sub.length())
                {
                    char followingCharsSign = 0;
                    bool doHaveFollowingChar = false;
                    // Do we even have a following char?
                    if (str.length() >= i + foundInText.length() + 1)
                    {
                        const char followingChar = str[i + foundInText.length()];

                        // Is it a letter?
                        if ((followingChar >= 'a' && followingChar <= 'z') ||
                            (followingChar >= 'A' && followingChar <= 'Z'))
                        {
                            // Copy its sign
                            followingCharsSign = followingChar & (1 << 5);
                            doHaveFollowingChar = true;
                        }
                    }


                    {
                        char lastCharCharSign = 0;

                        for (std::size_t j = 0; j < sub.length(); j++)
                        {
                            const char cs = sub[j];

                            // Do we still have chars of 'find' left?
                            if (j < foundInText.length()) {
                                const char cf = foundInText[j];
                                lastCharCharSign = cf & (1 << 5);
                            }

                            const char charSignToUse = doHaveFollowingChar ? followingCharsSign : lastCharCharSign;
                            ss << CopySign(charSignToUse, cs);
                        }
                    }
                }
            }
            else
            {
                // We do not have an occurrence... just insert the char as is
                ss << str[i];
            }
        }
        else
        {
            // We do not have an occurrence... just insert the char as is
            ss << str[i];
        }
    }

    return ss.str();
}

std::string MakeUwu(std::string boringString) {
    // Easy ones first
    // none, lol

    // Slightly more complex... Multichar replacements, but we have to keep capitalization...
    boringString = ReplaceButKeepCapitalization(boringString, "th", "tw");
    boringString = ReplaceButKeepCapitalization(boringString, "ove", "uv");
    boringString = ReplaceButKeepCapitalization(boringString, "have", "haf");
    boringString = ReplaceButKeepCapitalization(boringString, "tr", "tw");
    boringString = ReplaceButKeepCapitalization(boringString, "up", "uwp");

    // Replace N with Ny, but only if succeeded by a vowel
    boringString = ReplaceButKeepCapitalization(
            boringString,
            "n",
            "ny",
            [boringString](const std::string& found, int index)
            {
                // Don't replace, if we are on the last char
                if (index == boringString.length() - 1)
                    return false;

                // Only replace if the next char is a vowel
                const char nextChar = MakeLower(boringString[index + found.length()-1]);

                // Is this a vowel?
                if (IsVowel(nextChar))
                    return true;

                // Else, don't replace
                return false;
            }
        );

    // Replace R with W, but only if not preceded by a vowel
    boringString = ReplaceButKeepCapitalization(
            boringString,
            "r",
            "w",
            [boringString](const std::string& found, int index)
            {
                // Don't replace, if we are on the first char
                if (index == 0)
                    return false;

                // Only replace if the last char is not a vowel
                const char lastChar = MakeLower(boringString[index - 1]);

                // Is this a vowel?
                if (IsVowel(lastChar))
                    return false;

                // Else, replace
                return true;
            }
        );

    // Replace R with nothing, but only if preceded by a vowel, and (not succeeded by a non-letter or eof)
    boringString = ReplaceButKeepCapitalization(
            boringString,
            "r",
            "",
            [boringString](const std::string& found, int index)
            {
                // Don't replace, if we are on the last char
                if (index == boringString.length() - 1)
                    return false;

                if ((index == 0) ||(index == boringString.length() - 1))
                    return false;

                // Only replace if the last char is not a vowel
                const char lastChar = MakeLower(boringString[index - 1]);
                const char nextChar = MakeLower(boringString[index + found.length()-1]);

                // Is the next char a letter?
                if (!((lastChar >= 'a') && (nextChar <= 'z')))
                    return false;

                // Is this a vowel?
                if (IsVowel(lastChar))
                    return true;

                // Else, don't replace
                return false;
            }
    );


    // Replace L with W, but only if not followed or preceded by another L
    boringString = ReplaceButKeepCapitalization(
            boringString,
            "l",
            "w",
            [boringString](const std::string& found, int index)
            {
                if (boringString.length() < found.length() + 2)
                    return false;

                const char lastChar = MakeLower(boringString[index - 1]);
                const char nextChar = MakeLower(boringString[index + found.length()-1]);

                return (lastChar != 'l') && (nextChar != 'l');
            }
    );

    // Replace LL with WW, but only if followed by a vowel
    boringString = ReplaceButKeepCapitalization(
            boringString,
            "ll",
            "ww",
            [boringString](const std::string& found, int index)
            {
                if (boringString.length() < found.length())
                    return false;

                const char nextChar = MakeLower(boringString[index + found.length()-1]);

                return IsVowel(nextChar);
            }
    );

    // Replace ? with ..., but only if not followed by another ?
    boringString = ReplaceButKeepCapitalization(
            boringString,
            "?",
            "?? tell me! >:(",
            [boringString](const std::string& found, int index)
            {
                // Do replace, if we are on the last char
                if (index == boringString.length() - 1)
                    return true;

                const char nextChar = MakeLower(boringString[index + found.length()-1]);

                return nextChar != '?';
            }
    );


    // Also replace some ascii-"emojis'
    boringString = StringTools::Replace(boringString, ":)", "UwU :D");
    boringString = StringTools::Replace(boringString, ":-)", "UwwwU :D");
    boringString = StringTools::Replace(boringString, "lol", "XDD");
    boringString = StringTools::Replace(boringString, "^^", "^.^ UwU");
    boringString = StringTools::Replace(boringString, "thank you", "youwe twe best <3333 xoxo");
    boringString = StringTools::Replace(boringString, "thanks", "youwe twe best :D xoxo");
    boringString = StringTools::Replace(boringString, "thank's", "youwe twe best <3 uwu");
    boringString = StringTools::Replace(boringString, "hello", "Hiiiiiii");
    boringString = StringTools::Replace(boringString, "c++", "c++ (rust is hella cutewr btw ^^)");
    boringString = StringTools::Replace(boringString, "C++", "C++ (rust is hella cutewr btw ^^)");

    return boringString;
}

int main(int argc, char** argv) {

    // We have arguments. Uwwuifie these instead
    if (argc > 1)
    {
        for (std::size_t i = 1; i < argc; i++)
            std::cout << MakeUwu(argv[i]) + " ";

        std::cout << std::endl;
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
