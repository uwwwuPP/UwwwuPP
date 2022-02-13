#include "Util.h"
#include <CharTools.h>
#include <StringTools.h>
#include <sstream>

std::string Util::ConditionalReplaceButKeepSigns(
        const std::string& str,
        std::string find,
        const std::string& sub,
        const std::function<bool(const std::string&, const std::string&, const std::size_t)>& onlyIf
)
{

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
            if (onlyIf(str, foundInText, i))
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

                        ss << CharTools::CopySign(cf, cs);
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
                        if (CharTools::IsLetter(followingChar))
                        {
                            // Copy its sign
                            followingCharsSign = followingChar;
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
                            lastCharCharSign = cf;
                            ss << CharTools::CopySign(cf, cs);
                        }
                        else
                        {
                            // No: Use the last sign seen, or the sign of the following char (the following char within the same word-boundary) (Important for replacing vocals within a word)
                            const char charSignToUse = doHaveFollowingChar ? followingCharsSign : lastCharCharSign;
                            ss << CharTools::CopySign(charSignToUse, cs);
                        }
                    }
                }
            }
            else
            {
                // We do not have an occurrence... just insert the subsection found as is (next iteration will start behind it)
                ss << foundInText;
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
