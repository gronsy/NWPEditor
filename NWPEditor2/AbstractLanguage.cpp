#include "stdafx.h"
#include "AbstractLanguage.h"

AbstractLanguage::AbstractLanguage(std::wstring keywords, std::wstring file_extenstion, int language_id):
file_extension(file_extenstion), keywords(keywords), language_id(language_id), is_function_call(false)
{
	
}


AbstractLanguage::~AbstractLanguage()
{
	
}

std::wstring AbstractLanguage::GetFileExtension() { return file_extension; }

std::wstring AbstractLanguage::GetKeywords() { return keywords; }

int AbstractLanguage::GetLanguageId() { return language_id; }

bool AbstractLanguage::CheckIfFunction(std::string line, std::regex language_regex)
{
	const bool is_match = std::regex_match(line, language_regex);
	
	is_function=is_match;

	return is_match;
}

bool AbstractLanguage::CheckIfVariable(std::string line, std::regex language_regex)
{
	return false;
}

std::string AbstractLanguage::ReplaceCurrentLineNameIfMatched(const std::string& line_to_change, std::string replace_to)
{
	if(std::regex_match(line_to_change, regex_in_use))
	{
		// std::string new_line_text = line_to_change.replace(line_to_change.find(name_to_replace),
		// 									  line_to_change.find('(') - ERASE_OFFSET, replace_to);

		std::string new_line_text = ReplaceName(line_to_change, replace_to);

		return new_line_text;
	}
	
	return "";
}

std::string AbstractLanguage::CleanStringOfGarbage(std::string line)
{
	if (line.find("\n") != std::string::npos)
		return line.substr(STRING_BEGINNING, line.find("\n") + ERASE_OFFSET);
	
	return line;
}