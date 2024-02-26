#ifndef STRINGTOOLS_STRINGTOOLS_H
#define STRINGTOOLS_STRINGTOOLS_H

#include <string>

/* Handy utensils to manipulate strings */
class StringTools
{
public:
	//! Will replace every occurence of `find` in `str` by `subst`.
	static std::string Replace(const std::string& str, const char find, const std::string& subst);

	//! Will replace every occurence of `find` in `str` by `subst`.
	static std::string Replace(const std::string& str, const std::string& find, const std::string& subst);
	
	//! Will replace every occurence of `find` in `str` by `subst`.
	static std::string Replace(const std::string& str, const char find, const char subst);

	//! Will replace every occurence of `find` in `str` by `subst`.
	static std::string Replace(const std::string& str, const std::string& find, const char subst);

	//! Will make a string all-lowercase.
	static std::string Lower(const std::string& str);

	//! Will make a string all-uppercase.
	static std::string Upper(const std::string& str);

private:
	// No instanciation! >:(
	StringTools();
};

#endif //STRINGTOOLS_STRINGTOOLS_H
