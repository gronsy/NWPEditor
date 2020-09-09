#include "stdafx.h"
#pragma once
#include "CppLanguage.h"

CppLanguage::CppLanguage(bool is_clang/*=false*/) :
	AbstractLanguage(is_clang ? GetCKeywords() : GetCppKeywords(), is_clang ? L"c" : L"cpp", SCLEX_CPP),
	is_template(false), is_dot_method_call(false), is_arrow_method_call(false)
{}

CppLanguage::~CppLanguage()
{
}

std::wstring CppLanguage::GetCKeywords()
{
	return L"auto break case char const continue delete do double "
		"else enum explicit float for goto if int long register "
		"return short signed sizeof static struct switch typedef while";
}

std::wstring CppLanguage::GetCppKeywords()
{
	return L"asm auto bool break case catch char class const "
		"dynamic_cast else enum explicit extern false finally "
		"float for friend goto if inline int long mutable "
		"namespace new operator private protected public "
		"register reinterpret_cast register return short signed "
		"sizeof static static_cast struct switch template "
		"this throw true try typedef typeid typename "
		"union unsigned using virtual void volatile "
		"wchar_t while";
}

void CppLanguage::RemoveTypeIfTemplate(std::string& function_name)
{
	const int template_start_index = function_name.find('<');
	is_template = false;

	if (template_start_index != std::string::npos)
	{
		is_template = true;
		function_name = function_name.substr(STRING_BEGINNING, function_name.find('<'));
	}
}

std::string CppLanguage::DetermineFilter(const std::string line)
{
	if (is_dot_method_call)
		return ".";

	if (is_arrow_method_call)
		return "->";

	return line.find(':') != std::string::npos ? ":" : " ";
}

void CppLanguage::ExtractFunctionName(std::string line)
{
	std::string function_name;

	const std::string filter = DetermineFilter(line);

	const int offset = filter == ":" || filter == "->" ? ITERATOR_CLANG_COLON_OR_ARROW_OPERATOR_OFFSET : ITERATOR_SPACE_OR_DOT_OPERATOR_OFFSET;

	if (filter == ":" || filter == "." || filter == "->" || is_function_call)
	{
		function_name = line;

		if (function_name.find('(') != std::string::npos)
			function_name = function_name.substr(STRING_BEGINNING, function_name.find('('));

		while (function_name.find(filter) != std::string::npos)
			function_name = function_name.substr(function_name.find(filter) + offset, function_name.find('('));

		RemoveTypeIfTemplate(function_name);
	}
	else
	{
		const int filter_index = line.find(filter);
		function_name = line.substr(filter_index + offset, line.find('(') - filter_index - ERASE_OFFSET);
	}

	name_to_replace = function_name;
}

bool CppLanguage::CheckForFunctionCall(const char current_line_next_char)
{
	if (current_line_next_char == '(')
		is_function_call = true;

	return is_function_call;
}

bool CppLanguage::CheckNameBeginningCondition(int name_beginning, int iterator_name_beginning,
	const char current_line_previous_char)
{
	if (name_beginning == NAME_NOT_FOUND_FLAG)
	{
		switch (current_line_previous_char) {
		case DOT_OPERATOR:
		case ARROW_OPERATOR_POINT:
		case SPACE_CHARACTER:
		case COLON_CHARACTER:
			return true;
		}

		if (iterator_name_beginning == STRING_BEGINNING_INDEX)
			return true;
	}

	return false;
}

bool CppLanguage::CheckNameEndingConditions(const std::string& current_line, int name_ending, int iterator_name_ending,
	const char current_line_next_char)
{
	if (name_ending == NAME_NOT_FOUND_FLAG)
	{
		switch (current_line_next_char) {
		case DOT_OPERATOR:
		case ARROW_OPERATOR_BASE:
		case COLON_CHARACTER:
		case TEMPLATE_BEGINNING:
			return true;
		}

		if (CheckForFunctionCall(current_line_next_char))
			return true;

		if (iterator_name_ending == current_line.length() - 1)
			return true;
	}

	return false;
}

//TODO: Integrate new name fetching method to fetch name
void CppLanguage::GetCursorLineName(const std::string& current_line, const int cursor_index)
{
	int name_beginning{ NAME_NOT_FOUND_FLAG }, name_ending{ NAME_NOT_FOUND_FLAG };

	for (int iterator_name_beginning = cursor_index - 1, iterator_name_ending = cursor_index + 1;
		name_beginning != -1 && name_ending != -1;
		--iterator_name_beginning, ++iterator_name_ending)
	{
		char current_line_previous_char{};
		if (name_beginning == -1)
			current_line_previous_char = current_line[iterator_name_beginning];

		char current_line_next_char{};
		if (name_ending == -1)
			current_line_next_char = current_line[iterator_name_ending];

		if (CheckNameBeginningCondition(name_beginning, iterator_name_beginning, current_line_previous_char))
			name_beginning = iterator_name_beginning + NAME_SEARCH_MOVE_OFFSET;

		if (CheckNameEndingConditions(current_line, name_ending, iterator_name_ending, current_line_next_char))
			name_ending = iterator_name_ending - NAME_SEARCH_MOVE_OFFSET;
	}

	name_to_replace = current_line.substr(name_beginning, name_ending);
}

void CppLanguage::SetIsFunctionCall(const std::string line)
{
	is_function_call = false;

	const size_t parenthesis_index = line.find_first_of('(');
	const size_t dot_operator_index = line.find_first_of('.');
	const size_t arrow_operator_index = line.find_first_of("->");

	if (line.find_first_of(' ') > parenthesis_index
		|| dot_operator_index < parenthesis_index
		|| arrow_operator_index < parenthesis_index)
	{
		if (dot_operator_index != std::string::npos)
			is_dot_method_call = true;

		if (arrow_operator_index != std::string::npos && line[arrow_operator_index + 1] == '>')
		{
			is_arrow_method_call = true;
		}

		is_function_call = true;
	}
}

void CppLanguage::GenerateRegex(const std::string& line, const int line_index)
{
	const std::string cleared_line = CleanStringOfGarbage(line);

	const std::regex cregex_function_definition_regex = std::regex(R"(.*(::)?.*\((\r?\n?).*\)\{?(.*\}|;)?\r?\n?)");
	const std::regex cregex_function_call_regex = std::regex(R"(.*?.*\(.*\)?;?)");

	//SetIsFunctionCall(line);
	if (CheckIfFunction(line, cregex_function_definition_regex))
	{
		//ExtractFunctionName(line);
		GetCursorLineName(line, line_index);

		if (name_to_replace == "")
			throw EmptyFunctionNameException("Function name not found.");

		regex_in_use = std::regex(".*(::)?" + name_to_replace + R"(.*\(.*\)\{?(.*\}|;)?\r?\n?)");
	}
}

std::string CppLanguage::ReplaceName(const std::string& line_text, const std::string& replace_to)
{
	const int name_beginning_index = line_text.find(name_to_replace);
	int name_end_index;

	if (is_template)
		name_end_index = line_text.find('<');
	else
		name_end_index = line_text.find('(') != std::string::npos ?
		line_text.find('(') : line_text.find('\n');

	std::string new_line_text{ line_text };

	if (is_function)
	{
		int replace_to_index = 0;
		for (int iterating_index = name_beginning_index; iterating_index < name_end_index; ++iterating_index, ++replace_to_index)
		{
			new_line_text[iterating_index] = replace_to[replace_to_index];
			if (replace_to_index >= replace_to.length())
			{
				new_line_text.erase(iterating_index, static_cast<size_t>(name_end_index) - iterating_index);
				break;
			}
		}
	}

	return new_line_text;
}