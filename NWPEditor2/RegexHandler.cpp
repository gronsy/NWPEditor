#include "stdafx.h"
#include "RegexHandler.h"

RegexHandler::RegexHandler(int lang, std::string line)
{
	ParseRegex(lang, line);
}

void RegexHandler::ParseRegex(int lang, std::string line)
{
	switch (lang) {
	case SCLEX_CPP:
		break;
	case SCLEX_PYTHON:
		break;
	default:
		break;
	}
}