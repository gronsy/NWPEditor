#pragma once
#include "string"
#include "regex"
#include "exception"

class RegexHandler
{
	std::regex regex_in_use;
protected:
	void ParseRegex(int lang, std::string line);
	bool ParseLine();
	bool CheckIfVariable(std::string line, std::regex lang_regex);
	bool CheckIfFunction(std::string line, std::regex lang_regex);
public:
	RegexHandler(int lang, std::string line);
	bool CheckLineMatch(std::string line);
};