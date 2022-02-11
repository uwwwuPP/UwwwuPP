#include <iostream>
#include <StringTools/StringTools.h>
#include <string>
#include <sstream>
#include <functional>
#include <algorithm>
#include <random>

//! Generic uppercase character.
constexpr char UPPERCASE = 0;

//! Generic lowercase character.
constexpr char LOWERCASE = (1<<5);

//! Checks whether or not `c` is a vowel. You can define custom vowel characters.
bool IsVowel(const char c, const std::string& vowels = "euioay") {
    return std::any_of(
            vowels.cbegin(),
            vowels.cend(),
            [c](const char vowel) {
                    return c == vowel;
                }
        );
}

//! Returns whether or not `c` is a letter.
bool IsLetter(const char c) {
    const char lowercase_c = !(c & (1<<5)) ? (c | (1<<5)) : c; // Re-implementing IsUpper and MakeLower to prevent stack-overflow by endless recursion
    return (lowercase_c >= 'a') && (lowercase_c <= 'z');
}

//! Returns whether or not `c` is a generic character (that contains JUST the sign)
bool IsGeneric(const char c) {
    return (c == UPPERCASE) || (c == LOWERCASE);
}

//! Checks whether or not `c` is an uppercase character.
bool IsUpper(const char c) {
    if ((!IsLetter(c)) && (!IsGeneric(c)))
        return false;
    else
        return !(c & (1<<5));
}

//! Will return `c` as an uppercase character.
char MakeUpper(char c) {
    if ((!IsLetter(c)) && (!IsGeneric(c)))
        return c;
    else if (IsUpper(c))
        return c;
    else
        return c & ~(1<<5);
}

//! Will return `c` as a lowercase character.
char MakeLower(char c) {
    if ((!IsLetter(c)) && (!IsGeneric(c)))
        return c;
    else if (!IsUpper(c))
        return c;
    else
        return c | (1<<5);
}

//! Will return an empty character with the same sign/capitalization as `c`.
char GetSign(char c) {
    if (IsUpper(c))
        return UPPERCASE;
    else
        return LOWERCASE;
}

//! Will return `c` with the same capitalization as `sign`.
char CopySign(char sign, char c) {
    if ((!IsLetter(c)) && (!IsGeneric(c)))
        return c;
    if (IsUpper(sign))
        return MakeUpper(c);
    else
        return MakeLower(c);
}

//! Will replace all occurrences of a substring `find` in `str` with `sub`, but it will try to keep the characters signs.
//! Like (pay attention to the capitalization):.
//! ("Hello World", "hello", "hi") -> "Hi World".
//! ("hello World", "hello", "hi") -> "hi World".
//! ("HELLO World", "hello", "hi") -> "HI World".
//! You can also supply a callback to only perform a replacement if certain conditions apply.
std::string ReplaceButKeepSigns(
        const std::string& str,
        std::string find,
        const std::string& sub,
        const std::function<bool(const std::string&, const std::size_t)>& onlyIf = [](const std::string &,
                                                                                      const std::size_t) { return true; } // Default is: replace always
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
                        if (IsLetter(followingChar))
                        {
                            // Copy its sign
                            followingCharsSign = GetSign(followingChar);
                            doHaveFollowingChar = true;
                        }
                    }


                    char lastCharCharSign = 0;
                    for (std::size_t j = 0; j < sub.length(); j++)
                    {
                        const char cs = sub[j];

                        // Do we still have chars of 'find' left?
                        if (j < foundInText.length())
                        {
                            // Yes: Just copy the sign as is, and update the last sign seen
                            const char cf = foundInText[j];
                            lastCharCharSign = GetSign(cf);
                            ss << CopySign(cf, cs);
                        }
                        else
                        {
                            // No: Use the last sign seen, or the sign of the following char (the following char within the same word-boundary) (Important for replacing vocals within a word)
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

            // Advance i accordingly
            i += foundInText.length()-1;
        }
        else
        {
            // We do not have an occurrence... just insert the char as is
            ss << str[i];
        }
    }

    return ss.str();
}

//! Will make a boring string look sooper dooper kawaii and cute :3
std::string MakeUwu(std::string boringString) {
    // Easy ones first
    // none, lol

    // Slightly more complex... Multichar replacements, but we have to keep capitalization...
    boringString = ReplaceButKeepSigns(boringString, "th", "tw");
    boringString = ReplaceButKeepSigns(boringString, "ove", "uv");
    boringString = ReplaceButKeepSigns(boringString, "have", "haf");
    boringString = ReplaceButKeepSigns(boringString, "tr", "tw");
    boringString = ReplaceButKeepSigns(boringString, "up", "uwp");

    // Let's do some language adjustments
    boringString = ReplaceButKeepSigns(boringString, "twank you", "you're twe best <3333 xoxo");
    boringString = ReplaceButKeepSigns(boringString, "good", "sooper dooper");
    boringString = ReplaceButKeepSigns(boringString, "suwper", "sooper dooper");
    boringString = ReplaceButKeepSigns(boringString, "well", "sooper dooper");
    boringString = ReplaceButKeepSigns(boringString, "emacs", "vim");
    boringString = ReplaceButKeepSigns(boringString, "twanks", "you're twe best :33 xoxo");
    boringString = ReplaceButKeepSigns(boringString, "hello", "hiiiiiii");
    boringString = ReplaceButKeepSigns(boringString, "dear", "hiiiiiii");
    boringString = ReplaceButKeepSigns(boringString, "hi", "hiiiiiii");

    // Replace N with Ny, but only if succeeded by a vowel
    boringString = ReplaceButKeepSigns(
            boringString,
            "n",
            "ny",
            [boringString](const std::string &found, int index) {
                // Don't replace, if we are on the last char
                if (index + found.length() == boringString.length() - 1)
                    return false;

                // Only replace if the next char is a vowel
                const char nextChar = MakeLower(boringString[index + found.length()]);

                // Is this a vowel?
                if (IsVowel(nextChar))
                    return true;

                // Else, don't replace
                return false;
            }
    );

    // Replace R with W, but only if not succeeded by a non-vowel, and if it's not the first character of a word
    boringString = ReplaceButKeepSigns(
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

                // Only replace if the next char is a vowel
                const char nextChar = MakeLower(boringString[index + found.length()]);
                const char lastChar = MakeLower(boringString[index - 1]);

                // Is this a non-vowel?
                if (!IsVowel(nextChar))
                    return false;

                // Don't replace if the last char is not a letter
                if (!IsLetter(lastChar))
                    return false;

                // Else, replace
                return true;
            }
    );

    // Replace L with W, but only if not followed or preceded by another L, and if it's not the first character of a word
    boringString = ReplaceButKeepSigns(
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

                const char lastChar = MakeLower(boringString[index - 1]);
                const char nextChar = MakeLower(boringString[index + found.length()]);

                // Don't replace if the last char is not a letter
                if (!IsLetter(lastChar))
                    return false;

                return (lastChar != 'l') && (nextChar != 'l');
            }
    );

    // Replace LL with WW, but only if followed by a vowel
    boringString = ReplaceButKeepSigns(
            boringString,
            "ll",
            "ww",
            [boringString](const std::string &found, int index) {
                if (boringString.length() < found.length())
                    return false;

                const char nextChar = MakeLower(boringString[index + found.length()]);

                return IsVowel(nextChar);
            }
    );

    // Replace ER with A, but only if it's the last two letters of a word
    boringString = ReplaceButKeepSigns(
            boringString,
            "er",
            "a",
            [boringString](const std::string &found, int index) {
                // Replace if we're at the end of this line/segment
                if (index + found.length() == boringString.length() - 1)
                    return false;

                // Fetch the next char
                const char nextChar = MakeLower(boringString[index + found.length()]);

                // Replace if the next char is not a letter
                return IsLetter(nextChar) == false;
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
    boringString = ReplaceButKeepSigns(boringString, "c++", "c++ (rust is hella cutewr btw ^^)");


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
