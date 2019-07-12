#pragma once
#include <string>
#include <regex>
#include <exception>
#include <algorithm>
#include <msclr/marshal_cppstd.h>

#using <System.dll>
#using <System.Text.RegularExpressions.dll>

#define ITERATOR_CLANG_OFFSET 2

public ref class RegexHandler
{
	System::Text::RegularExpressions::Regex^ regex_in_use;
protected:
	void ParseRegex(int lang, std::string line);
	bool CheckIfVariable(std::string line, System::Text::RegularExpressions::Regex^ lang_regex);
	bool CheckIfFunction(std::string line, System::Text::RegularExpressions::Regex^ lang_regex);
	std::string ExtractFunctionName(int lang, std::string line);
	std::string ExtractCTypeName(std::string::iterator string_iterator);
public:
	RegexHandler(int lang, const std::string line);

	bool CheckLineMatch(std::string line);
};