#pragma once
#include <string>
#include <regex>
#include <exception>
#include <algorithm>

#define ITERATOR_CLANG_OFFSET 2

class RegexHandler
{
	std::regex regex_in_use;
protected:
	void ParseRegex(int lang, std::string line);
	bool CheckIfVariable(std::string line, std::regex lang_regex);
	bool CheckIfFunction(std::string line, std::regex lang_regex);
	std::string ExtractFunctionName(int lang, std::string line);
	std::string ExtractCTypeName(std::string::iterator string_iterator);
public:
	RegexHandler(int lang, std::string line);

	bool CheckLineMatch(std::string line);
};