#pragma once
#include "string"
#include "regex"

class RegexHandler 
{
protected:
	void ParseLanguage(int lang);
public:
	bool GenerateRegex(int lang);
};