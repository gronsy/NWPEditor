#pragma once
#include <string>
#include <regex>
#include <exception>

class AbstractLanguage
{
protected:
	std::string name_to_replace, replace_to;
	std::regex regex_in_use;
	bool is_function_call;
	std::wstring file_extension;
	std::wstring keywords;
	int language_id;
protected:
	bool CheckIfVariable(std::string line, std::regex language_regex);
	bool CheckIfFunction(std::string line, std::regex lang_regex, bool is_call);
	virtual void ExtractFunctionName(std::string line) = 0;
	AbstractLanguage(std::wstring keywords, std::wstring file_extenstion, int language_id);
public:
	
	virtual ~AbstractLanguage();

	virtual void GenerateRegex(std::string line) = 0;
	std::string ReplaceInstances(std::string document_text, std::string replace_to);

	std::wstring GetFileExtension();
	std::wstring GetKeywords();
	int GetLanguageId();
};