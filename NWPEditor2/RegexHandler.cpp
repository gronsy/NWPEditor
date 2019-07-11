#include "stdafx.h"
#include "RegexHandler.h"

#using <System.dll>
#using <System.Text.RegularExpressions.dll>

#define _REGEX_MAX_STACK_COUNT 1000

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
		if (line.find(':') != std::string::npos)
		{
			/*std::string::iterator iter;
			iter = std::find(line.begin(), line.end(), ':');
			return ExtractCTypeName(iter + ITERATOR_CLANG_OFFSET);*/
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
	{
		//Regex used to find if the current selection is function
		//CPP Regex: .*(::)?\(.*\)\{(.*\}|;)?\n?
		//Python Regex: def.*\(.*\):\n?
		System::Text::RegularExpressions::Regex^ regex = gcnew System::Text::RegularExpressions::Regex(".*(::)?\(.*\)\{(.*\}|;)?\n?");
		if (CheckIfFunction(line, std::regex(".*(::)?(<.*>)?\(", std::regex_constants::extended)))
		{
			regex_in_use = std::regex("");
		}
		break;
	}
	case SCLEX_PYTHON:
		break;
	default:
		break;
	}
}