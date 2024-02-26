#ifndef STRINGTOOLS_CHARTOOLS_H
#define STRINGTOOLS_CHARTOOLS_H

#include <string>

/* Handy utensils to manipulate characters */

class CharTools {
public:
    //! Checks whether or not `c` is a vowel. You can define custom vowel characters.
    static bool IsVowel(const char c, const std::string &vowels = "euioay");

    //! Returns whether or not `c` is a letter.
    static bool IsLetter(const char c);

    //! Returns whether or not `c` is a digit.
    static bool IsDigit(const char c);

    //! Checks whether or not `c` is an uppercase character.
    static bool IsUpper(const char c);

    //! Checks whether or not `c` is a lowercase character.
    static bool IsLower(const char c);

    //! Will return `c` as an uppercase character.
    static char MakeUpper(char c);

    //! Will return `c` as a lowercase character.
    static char MakeLower(char c);

    //! Will return `c` with the same capitalization as `sign`.
    static char CopySign(char sign, char c);
};

#endif //STRINGTOOLS_CHARTOOLS_H
