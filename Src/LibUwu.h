#ifndef UWWWU_LIBUWU_H
#define UWWWU_LIBUWU_H

#include <StringTools.h>
#include <CharTools.h>
#include <string>
#include <sstream>
#include <functional>
#include <random>
#include "Util.h"

// I stole these from the fastest uwuifier in the west :3 (also added my own)
std::string boykisserChatter[] = {
    "OwO",
    "UwU",
    "owo",
    "uwu",
    "eugh",
    "o.O",
    "o.o",
    "O.o",
    "Oo",
    "oO",
    "xoxo",
    ">w<",
    ">///<",
    ">_<",
    ">w<'",
    ">///<'",
    ">_<'",
    ":3", // Important enough to have four of
    ":3",
    ":3",
    ":3",
    ";3",
    ";3",
    "x3",
    "xd",
    "xD",
    "XD",
    "x3c",
    ":p",
    ";p",
    "<3",
    "<33",
    "<3333",
    "^^",
    "^.^",
    "^_^",
    "^-^",
    "^.^'",
    "^_^'",
    "^-^'",
    "nyaa~",
    "mya",
    "rawr",
    ";w;",
    "*_*",
    "*.*",
    "-.-",
    "-.-'",
    "(ˆ ﻌ ˆ)♡",
    "^•ﻌ•^",
    "/(^•ω•^)",
    "(✿oωo)",
    "(~˘▾˘)~",
    "(づ￣ ³￣)づ",
    "(⑅˘꒳˘)",
    "(˘ω˘)",
    "(U ᵕ U❁)",
    "σωσ",
    "òωó",
    "(U ﹏ U)",
    "(ꈍᴗꈍ)",
};

const std::string& getRandomBoykisserChatter(int rand = -1) {
    // Set rand, if unset
    if (rand == -1) {
        std::random_device rd;
        rand = rd();
    }

    return boykisserChatter[rand % (sizeof(boykisserChatter) / sizeof(boykisserChatter[0]))];
}

// This validator will only replace findings, if they are a complete word, and not just part of a word.
static inline auto ValidatorFindingIsCompleteWord(const std::string& original, const std::string& finding, const std::size_t index) -> bool {
    // Quick-accept: Original-string length matches finding-string length
    if (original.length() == finding.length())
        return true;

    bool lastCharBreaksWord = true; // Default is true, because this value stays in case there is no last/next char.
    bool nextCharBreaksWord = true; // In this case, "no character" would imply the word to be broken.

    // Assign surrounding chars, if possible
    if (index > 0)
        lastCharBreaksWord = !CharTools::IsLetter(original[index - 1]);
    if (index + finding.length() < original.length())
        nextCharBreaksWord = !CharTools::IsLetter(original[index + finding.length()]);

    // If both the last and the next character are word-breaking, replace.
    if (lastCharBreaksWord && nextCharBreaksWord)
        return true;
        // Else: don't
    else
        return false;
}

// This validator will only replace findings, if they are at the end of a word
static inline auto ValidatorFindingIsEndOfWord(const std::string& original, const std::string& finding, const std::size_t index) -> bool {
    // Replace if we're at the end of this line/segment
    if (index + finding.length() == original.length())
        return true;

    // Fetch the next char
    const char nextChar = CharTools::MakeLower(original[index + finding.length()]);

    // Replace if the next char is not a letter
    return !CharTools::IsLetter(nextChar);
}

// This validator will only replace findings 50% of the time
static inline auto Validator50Percent(const std::string& original, const std::string& finding, const std::size_t index) -> bool {
    std::random_device rd;
    return rd() % 2;
}

// This validator will only replace findings, if they are a complete word, and not just part of a word, at 50%
static inline auto ValidatorFindingIsCompleteWordAt50Percent(const std::string& original, const std::string& finding, const std::size_t index) -> bool {
    return Validator50Percent(original, finding, index) && ValidatorFindingIsCompleteWord(original, finding, index);
}

// Validator for stuttering (y -> y-y)
// but only sometimes (random change),
// and if it is the first character of a word,
static inline auto ValidatorStutter(const std::string& original, const std::string& finding, const std::size_t index) -> bool {
    // Don't replace, if we're at the end of our string
    if (index + finding.length() == original.length())
        return false;

    // This is a bit tricky, because we can't abort if we're on the first char
    // but we can can't not check the previous char either. Running big risk
    // of causing a segfault. So we have to not check the previous character,
    // if we are on the first char.

    // Are we on the first char?
    const bool isFirstChar = index == 0;

    // Fetch the last character
    const char lastChar = isFirstChar ? '\0' : CharTools::MakeLower(original[index - 1]);

    // Fetch the next character
    const char nextChar = CharTools::MakeLower(original[index + finding.length()]);

    // Don't replace, if the last char is a letter
    if ((!isFirstChar) && (CharTools::IsLetter(lastChar)))
        return false;

    // Also don't replace if the next char is not a letter
    // This is impowtant to avoid single-letter characters, like "u", as in "you".
    if (!CharTools::IsLetter(nextChar))
        return false;

    // Initialize deterministic prng
    // Can't initialize one for all scopes, they don't seem to play
    // nicely with being passed to lambda functions...
    static std::mt19937 rng(index); // Seed rng based on string position

    // Chance (out of a 100) for the mutation to take place
    // if all preconditions are met
    constexpr int chance = 5;

    // Roll the dice, baby!
    return (rng() % 100) < chance;
}

// The finding is not followed by vowels, which are followed by consunants, which are followed by more vowels, within a word
// e.g. "this" is ok, "thisi" is not ok
// also, the current word must begin with 'th', e.g. the char before is word-breaking
// but does not end with a consonant
// e.g. "this" is ok, "the" is not ok
static inline auto ValidatorFindingIsInOnlySyllableAndEndsWithConsunant(const std::string& original, const std::string& finding, const std::size_t index) -> bool {
    // Quick-accept: Original-string length matches finding-string length
    if (original.length() == finding.length()) {
        return true;
    }

    bool lastCharBreaksWord = true; // Default is true, because this value stays in case there is no last/next char.

    // Check if the last-char is word-breaking, since this is a reject-condition
    if (index > 0) {
        lastCharBreaksWord = !CharTools::IsLetter(original[index - 1]);
    }

    // If the last char does not break the word, reject.
    if (!lastCharBreaksWord) {
        return false;
    }

    const std::size_t indexAfterWord = index + finding.length();
    bool foundFirstVowel = false;
    bool foundConsunant = false;
    for (std::size_t i = index + finding.length(); i < original.length(); i++) {
        const char c = original[i];

        // If we have any vowel, set this to true
        if (CharTools::IsVowel(c)) {
            foundFirstVowel = true; // This can also be set when iterating over a "second-vowel", but then it would already be set to true.

            // If the current syllable is already terminated,
            // break, since this is a reject-condition.
            // should be "if (foundFirstVowel && foundConsunant) " (this is the exit condition), but the "foundFirstVowel" can be optimized out.
            if (foundConsunant) {
                return false; // This is it, a second syllable has been detected.
            }
        }

        // If we have any consunant after finding a vowel, set this to true
        if (foundFirstVowel && CharTools::IsVowel(c, "qwrtzpsdfghjklxcvbnm")) { // Abusing the 'IsVowel'-method to detect consunants
            foundConsunant = true;
        }

        // If we have reached a word-boundary, quick-return
        if (!CharTools::IsLetter(c)) {
            return foundConsunant;
        }
    }

    // Reject-condition has not been reached.
    // If we have found a consonant, replace
    return foundConsunant;
}


//! Will make a boring string look sooper dooper kawaii and cute :3
static inline std::string MakeUwu(std::string boringString) {
    // Easy ones first
    // Skip empty lines
    std::size_t numWhitespaceCharacters = 0;
    for (const char c : boringString) {
        if (c == ' ' || c == '\t') {
            numWhitespaceCharacters++;
        }
    }

    if (numWhitespaceCharacters == boringString.length()) {
        return boringString;
    }

    // Slightly more complex... Multichar replacements, but we have to keep capitalization...
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "ove", "uv");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "have", "haf");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "tr", "tw");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "up", "uwp");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "ude", "ood", ValidatorFindingIsEndOfWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "ers", "as", ValidatorFindingIsEndOfWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "er", "a", ValidatorFindingIsEndOfWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "th", "d", ValidatorFindingIsInOnlySyllableAndEndsWithConsunant);

    // Let's do some language adjustments
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "thank you", "ur twe best <3333 xoxo", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "good", "sooper dooper", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "suwper", "sooper dooper", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "well", "sooper dooper", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "emacs", "vim", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "thanks", "ur twe best :33 xoxo", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "hello", "hiiiiiii", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "dear", "hiiiiiii", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "hi", "hiiiiiii", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "come", "cum", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "coming", "cumming", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "cat", "catto", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "dog", "doggo", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "bunny", "bnuy", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "some", "sum", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "cool", "keewl", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "cute", "kawaii", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "like", "luv", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "likes", "luvs", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "here", "hea", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "your", "ur", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "you", "u", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "you're", "ur", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "youre", "ur", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "yourself", "urself", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "small", "smol", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "sexy", "lewd", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "dirty", "lewd", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "inappropriate", "lewd", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "nice", "awwsum", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "nicely", "awwsumly", ValidatorFindingIsCompleteWord);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "the", "twe", ValidatorFindingIsCompleteWord);

    // Let's extend some phonetics
    // These are quite agressive, so don't do them _every time_
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "ay", "aaay", Validator50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "ey", "eeey", Validator50Percent);

    // Replace R with W, but only if not succeeded by a non-vowel, and if it's not the first character of a word
    boringString = Util::ConditionalReplaceButKeepSigns(
            boringString,
            "r",
            "w",
            [](const std::string& original, const std::string& finding, const std::size_t index) {
                // Don't replace, if we are on the last char
                if (index + finding.length() == original.length())
                    return false;

                // Don't replace if we're at index 0
                if (index == 0)
                    return false;

                const char nextChar = CharTools::MakeLower(original[index + finding.length()]);
                const char lastChar = CharTools::MakeLower(original[index - 1]);

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

    // Replace L with LW, but only if followed or preceded by a vowel, and if it's not the first character of a word
    boringString = Util::ConditionalReplaceButKeepSigns(
            boringString,
            "l",
            "wl",
            [](const std::string& original, const std::string& finding, const std::size_t index) {
                // Our segment has to be at least two characters long
                if (original.length() < finding.length() + 2)
                    return false;

                // Don't replace if we're at index o
                if (index == 0)
                    return false;

                const char lastChar = CharTools::MakeLower(original[index - 1]);
                const char nextChar = CharTools::MakeLower(original[index + finding.length()]);

                // Don't replace if the last char is not a letter
                if (!CharTools::IsLetter(lastChar))
                    return false;

                return CharTools::IsVowel(lastChar) && CharTools::IsVowel(nextChar);
            }
    );

    // Replace LL with WW, but only if followed by a vowel
    boringString = Util::ConditionalReplaceButKeepSigns(
            boringString,
            "ll",
            "ww",
            [](const std::string& original, const std::string& finding, const std::size_t index) {
                // Don't replace, if we are on the last char
                if (index + finding.length() == original.length())
                    return false;

                const char nextChar = CharTools::MakeLower(original[index + finding.length()]);

                return CharTools::IsVowel(nextChar);
            }
    );

    // ", and" with " aaaaaaaand"
    boringString = Util::ConditionalReplaceButKeepSigns(
        boringString,
        ", and",
        " aaaaaaand",
        ValidatorFindingIsEndOfWord
    );

    // ", so" with " sooooooo"
    boringString = Util::ConditionalReplaceButKeepSigns(
        boringString,
        ", so",
        " soooooooo",
        ValidatorFindingIsEndOfWord
    );

    // Replace "," with " uhhh"
    boringString = Util::ConditionalReplaceButKeepSigns(
        boringString,
        ",",
        " uhhh",
        [](const std::string& original, const std::string& finding, const std::size_t index) {
            // Don't replace if we're at the end of the string
            if (index == original.length() - 1)
                return false;

            return true;
        }
    );

    // Replace for example y with y-y (imitates shy stuttering)
    std::stringstream ss;
    for (char c = 'a'; c <= 'z'; c++) {
        ss << c;
        const std::string find = ss.str();    // "y"
        ss << '-' << c;
        const std::string replace = ss.str(); // "y-y"

        boringString = Util::ConditionalReplaceButKeepSigns(boringString, find, replace, ValidatorStutter);
        ss.str("");
    }

    // Replace random punctuation with uwwwwu cute symbols
    // Initialize deterministic prng
    std::mt19937 rng(std::hash<std::string>()(boringString)); // Seed rng based on string
    constexpr int CHANCE = 2;
    for (const char c : boringString)
    {
        if ((c == '.') && (rng() % CHANCE == 0))
        {
            std::size_t n = rng() % 3;
            if (n == 0)
                ss << ' ' << getRandomBoykisserChatter(rng()) << ' ' << getRandomBoykisserChatter(rng());
            else if (n == 1)
                ss << ' ' << getRandomBoykisserChatter(rng()) << " uwu";
            else
                ss << "~";
        }
        else if ((c == '!') && (rng() % (CHANCE*2) == 0))
        {
            ss << "!! thadws impowtant! " << getRandomBoykisserChatter(rng());
        }
        else if ((c == '?') && (rng() % (CHANCE*2) == 0))
        {
            ss << "?? nyow tell me! " << getRandomBoykisserChatter(rng());
        }
        else
            ss << c;
    }
    boringString = ss.str();

    // Also, replace some ascii-"emojis'
    // TODO: Find them individually, and choose a random boykisser chatter emote for each single occurence, rather than replacing
    // all occurences by the same emote, or none at all.
    boringString = StringTools::Replace(boringString, "^^", "^_^");
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":)", ":3", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":)", "x3", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":)", ">.<", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":)", ">///<", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":)", "^.^", ValidatorFindingIsCompleteWordAt50Percent);

    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":-)", ":3", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":-)", "x3", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":-)", ">.<", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":-)", ">///<", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":-)", "^.^", ValidatorFindingIsCompleteWordAt50Percent);

    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":D", ":3", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":D", "x3", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":D", ">.<", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":D", ">///<", ValidatorFindingIsCompleteWordAt50Percent);
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, ":D", "^.^", ValidatorFindingIsCompleteWordAt50Percent);

    // Some language replacement should happen after these more complex rules
    boringString = Util::ConditionalReplaceButKeepSigns(boringString, "c++", "c++ (rust is hella cutewr btw ^^)");

    // Always append an extra boykisser chatter. Can't have enough of those.
    return boringString + " " + getRandomBoykisserChatter();
}

#endif //UWWWU_LIBUWU_H
