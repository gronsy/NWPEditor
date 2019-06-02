#include "stdafx.h"
#include "RegexHandler.h"

std::regex RegexHandler::ParseLanguage(int lang)
{
	switch(lang) {
	case SCLEX_CPP:
		break;
	default:
		break;
	}

	return std::regex();
}

bool RegexHandler::GenerateRegex(int lang, std::string line) 
{
	auto regex = ParseLanguage(lang);
}