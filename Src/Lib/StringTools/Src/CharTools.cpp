#include "CharTools.h"
#include <algorithm>

bool CharTools::IsVowel(const char c, const std::string &vowels) {
    const char lc = MakeLower(c);

    return std::any_of(
            vowels.cbegin(),
            vowels.cend(),
            [lc](const char vowel) {
                return lc == vowel;
            }
    );
}

bool CharTools::IsLetter(const char c) {
    // Re-implementing IsUpper and MakeLower to prevent stack-overflow by endless recursion
    const char lowercase_c = !(c & (1<<5)) ? (c | (1<<5)) : c;

    return (lowercase_c >= 'a') && (lowercase_c <= 'z');
}

bool CharTools::IsDigit(const char c) {
    return (c >= '0') && (c <= '9');
}

bool CharTools::IsUpper(const char c) {
    if (!IsLetter(c))
        return false;
    else
        return !(c & (1<<5));
}

bool CharTools::IsLower(const char c) {
    // Can't just return !IsUpper(c), because it should still return false for digits and symbols...

    if (!IsLetter(c))
        return false;
    else
        return (c & (1<<5));
}

char CharTools::MakeUpper(char c) {
    if (!IsLetter(c))
        return c;
    else if (IsUpper(c))
        return c;
    else
        return c & ~(1<<5);
}

char CharTools::MakeLower(char c) {
    if (!IsLetter(c))
        return c;
    else if (!IsUpper(c))
        return c;
    else
        return c | (1<<5);
}

char CharTools::CopySign(char sign, char c) {
    if ((!IsLetter(c)) || (!IsLetter(sign)))
        return c;
    if (IsUpper(sign))
        return MakeUpper(c);
    else
        return MakeLower(c);
}
