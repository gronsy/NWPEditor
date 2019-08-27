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
	std::string function_name;
	switch (lang) {
	case SCLEX_CPP:
	{
		if (line.find(':') != std::string::npos)
		{
			std::string::iterator iter;
			iter = std::find(line.begin(), line.end(), ':');

			//Extracting function name
			std::copy(iter + ITERATOR_CLANG_OFFSET,
				std::find(iter, line.end(), '('),
				function_name.begin());

			return function_name;
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

	line.erase(std::find(line.begin(), line.end(), '\n') + ERASE_BEGIN_OFFSET);

	switch (lang) {
	case SCLEX_CPP:
	{
		//Regex used to find if the current selection is function
		//CPP Regex: .*(::)?\(.*\)\{(.*\}|;)?\r?\n?
		Regex^ cregex = gcnew Regex(msclr::interop::marshal_as<System::String^>(".*(::)?.*\(.*\)\{(.*\}|;)?\r?\n?"));
		if (cregex->IsMatch(msclr::interop::marshal_as<System::String^>(line)))
		{
			std::string function_name = ExtractFunctionName(lang, line);
			regex_in_use = cregex;
			break;
		}

		break;
	}
	case SCLEX_PYTHON:
	{
		//Python Regex: def.*\(.*\):\r?\n?
		Regex^ pyregex = gcnew Regex("def.*\(.*\):\r?\n?");
		if (pyregex->IsMatch(msclr::interop::marshal_as<System::String^>(line)))
		{
		}
		break;
	}
	default:
		break;
	}
}