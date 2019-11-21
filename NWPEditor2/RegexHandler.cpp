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

bool RegexHandler::CheckIfFunction(std::string line, System::Text::RegularExpressions::Regex^ lang_regex, bool is_call)
{
	auto is_match = lang_regex->IsMatch(msclr::interop::marshal_as<System::String^>(line));
	if (is_match && is_call)
		is_function_call = is_call;

	if (!is_call)
		is_function_call = false;

	return is_match;
}

bool RegexHandler::CheckLineMatch(std::string line)
{
	return regex_in_use->IsMatch(msclr::interop::marshal_as<System::String^>(line));
}

std::string RegexHandler::ExtractCTypeName(std::string::iterator string_iterator)
{
	return "";
}

std::string RegexHandler::ExtractFunctionName(int lang, std::string line)
{
	std::string function_name;
	switch (lang)
	{
	case SCLEX_CPP:
	{
		char filter = line.find(':') != std::string::npos ? ':' : ' ';

		int offset = filter == ':' ? ITERATOR_CLANG_COLON_OFFSET : ITERATOR_SPACE_OFFSET;
		function_name = line.substr(line.find(filter) + offset, line.find('('));
		function_name = function_name.substr(STRING_BEGINNING, line.find(')') + ERASE_OFFSET);

		return function_name;
	}
	case SCLEX_PYTHON:
		function_name = line.substr(line.find(" ")+ITERATOR_SPACE_OFFSET, line.find('('));
		function_name = function_name.substr(STRING_BEGINNING, line.find(')') + ERASE_OFFSET);

		return function_name;
	default:
		return "";
	}
}

void RegexHandler::ParseRegex(int lang, std::string line)
{
	using namespace System::Text::RegularExpressions;
	line = line.substr(STRING_BEGINNING, line.find("\n") + ERASE_OFFSET);

	switch (lang) {
	case SCLEX_CPP:
	{
		//Regex used to find if the current selection is function
		//CPP Regex: .*(::)?\(.*\)\{?(.*\}|;)?\r?\n?
		Regex^ cregex_function_definition = gcnew Regex(msclr::interop::marshal_as<System::String^>(".*(::)?.*\(.*\)\{?(.*\}|;)?\r?\n?"));
		Regex^ cregex_function_call = gcnew Regex(msclr::interop::marshal_as<System::String^>(".*?.*\(\)?;?"));

		if (CheckIfFunction(line, cregex_function_definition, false) || CheckIfFunction(line, cregex_function_call, true))
		{
			std::string function_name = ExtractFunctionName(lang, line);

			if (function_name == "")
				throw EmptyFunctionNameException("Function name not found.");
			
			regex_in_use = gcnew Regex(
				msclr::interop::marshal_as<System::String^>(".*(::)?" + function_name + "\(.*\)\{?(.*\}|;)?\r?\n?"));
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