#include "stdafx.h"
#include "AbstractLanguage.h"

AbstractLanguage::AbstractLanguage(std::wstring keywords, std::wstring file_extenstion, int language_id):
file_extension(file_extenstion), keywords(keywords), language_id(language_id)
{
	
}


AbstractLanguage::~AbstractLanguage()
{
	
}


std::wstring AbstractLanguage::GetFileExtension() { return file_extension; }

std::wstring AbstractLanguage::GetKeywords() { return keywords; }

int AbstractLanguage::GetLanguageId() { return language_id; }

bool AbstractLanguage::CheckIfFunction(std::string line, std::regex language_regex, bool is_call)
{
	const bool is_match = std::regex_match(line, language_regex);
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

std::string AbstractLanguage::ReplaceInstances(std::string document_text, std::string replace_to)
{
	this->replace_to = replace_to;
	std::smatch matches;

	std::string replaced_instances_text=std::regex_replace(document_text, regex_in_use, replace_to);
	
	return replaced_instances_text;
}

std::string AbstractLanguage::CleanStringOfGarbage(std::string line)
{
	if (line.find("\n") != std::string::npos)
		return line.substr(STRING_BEGINNING, line.find("\n") + ERASE_OFFSET);
	
	return line;
}