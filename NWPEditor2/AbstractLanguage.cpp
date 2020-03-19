#include "stdafx.h"
#include "AbstractLanguage.h"

std::wstring AbstractLanguage::GetFileExtension() { return file_extension; }

std::wstring AbstractLanguage::GetKeywords() { return keywords; }

int AbstractLanguage::GetLanguageId() { return language_id; }

bool AbstractLanguage::CheckIfFunction(std::string line, std::regex language_regex, bool is_call)
{
	auto is_match = std::regex_match(line, language_regex);
	if (is_match && is_call)
		is_function_call = is_call;

	if (!is_call)
		is_function_call = false;

	return is_match;
}

bool AbstractLanguage::CheckIfVariable(std::string line, std::regex language_regex)
{
	return false;
}