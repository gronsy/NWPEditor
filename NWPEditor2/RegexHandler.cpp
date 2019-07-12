#include "stdafx.h"
#include "RegexHandler.h"

#define _REGEX_MAX_STACK_COUNT 1000

RegexHandler::RegexHandler(int lang, const std::string line)
{
	ParseRegex(lang, line);
}

bool RegexHandler::CheckIfVariable(std::string line, System::Text::RegularExpressions::Regex^ lang_regex)
{
	return true;
}

bool RegexHandler::CheckIfFunction(std::string line, System::Text::RegularExpressions::Regex^ lang_regex)
{
	return lang_regex->IsMatch(msclr::interop::marshal_as<System::String^>(line)) ? true : false;
}

bool RegexHandler::CheckLineMatch(std::string line)
{
	return true;
}

std::string RegexHandler::ExtractCTypeName(std::string::iterator string_iterator)
{
	return "";
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
	using namespace System::Text::RegularExpressions;

	switch (lang) {
	case SCLEX_CPP:
	{
		//Regex used to find if the current selection is function
		//CPP Regex: .*(::)?\(.*\)\{(.*\}|;)?\n?
		Regex^ cregex = gcnew Regex(".*(::)?\(.*\)\{(.*\}|;)?\n?");
		if (CheckIfFunction(line, cregex))
		{
		}
		break;
	}
	case SCLEX_PYTHON:
	{
		//Python Regex: def.*\(.*\):\n?
		Regex^ pyregex = gcnew Regex("def.*\(.*\):\n?");
		if (CheckIfFunction(line, pyregex))
		{
		}
		break;
	}
	default:
		break;
	}
}