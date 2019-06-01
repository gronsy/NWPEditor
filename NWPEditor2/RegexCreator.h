#pragma once
#include "string"
#include "regex"

class RegexHandler 
{
	std::regex regex_in_use;
protected:
	std::regex ParseLanguage(int lang);
	bool ParseLine();
public:
	RegexHandler(int line, std::string);
	bool GenerateRegex(int lang, std::string line);
	bool CheckIfFunctionOrLine(int lang, std::string line);
};