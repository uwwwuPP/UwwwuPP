#ifndef UWWWU_UTIL_H
#define UWWWU_UTIL_H

#include <string>
#include <functional>
#include <cstddef>


class Util {
public:
    //! Will replace all occurrences of a substring `find` in `str` with `sub`, but it will try to keep the characters signs.
    //! Like (pay attention to the capitalization):.
    //! ("Hello World", "hello", "hi") -> "Hi World".
    //! ("hello World", "hello", "hi") -> "hi World".
    //! ("HELLO World", "hello", "hi") -> "HI World".
    //! You can also supply a callback to only perform a replacement if certain conditions apply.
    static std::string ConditionalReplaceButKeepSigns(
            const std::string& str,
            std::string find,
            const std::string& sub,
            const std::function<bool(const std::string&, const std::size_t)>& onlyIf =
                    [](const std::string &, const std::size_t) { return true; } // Default is: replace always
    );
};


#endif //UWWWU_UTIL_H
