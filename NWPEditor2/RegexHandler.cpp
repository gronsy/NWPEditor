#include "stdafx.h"
#include "RegexHandler.h"

RegexHandler::RegexHandler(int lang, std::string line)
{
	ParseRegex(lang, line);
}

bool RegexHandler::CheckIfVariable(std::string line, std::regex lang_regex)
{
	return true;
}

bool RegexHandler::CheckIfFunction(std::string line, std::regex lang_regex)
{
	return true;
}

bool RegexHandler::CheckLineMatch(std::string line)
{
	return true;
}

std::string RegexHandler::ExtractFunctionName(int lang, std::string line)
{
	switch (lang) {
	case SCLEX_CPP:
	{
		std::string::iterator iter;
		if (line.find(':') != std::string::npos)
		{
			iter = std::find(line.begin(), line.end(), ':');
			return ExtractCTypeName(iter + ITERATOR_CLANG_OFFSET);
		}
	}
	case SCLEX_PYTHON:
	default:
		return "";
	}
}

void RegexHandler::ParseRegex(int lang, std::string line)
{
	switch (lang) {
	case SCLEX_CPP:
		if (CheckIfFunction(line, std::regex("*(*::*)?\(\)*\n?*\{*\}")))
		{
			regex_in_use = std::regex("");
		}
		break;
	case SCLEX_PYTHON:
		break;
	default:
		break;
	}
}