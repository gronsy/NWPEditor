#pragma once
#include <string>
#include <regex>
#include <sstream>

#define ITERATOR_CLANG_COLON_OFFSET 2
#define ITERATOR_SPACE_OFFSET 1
#define ERASE_OFFSET 1
#define STRING_BEGINNING 0

class AbstractLanguage
{
protected:
	std::string name_to_replace;
	std::regex regex_in_use;
	bool is_function_call;
	std::wstring file_extension;
	std::wstring keywords;
	int language_id;
	
protected:
	AbstractLanguage(std::wstring keywords, std::wstring file_extenstion, int language_id);
	bool CheckIfVariable(std::string line, std::regex language_regex);
	bool CheckIfFunction(std::string line, std::regex lang_regex, bool is_call);
	std::string CleanStringOfGarbage(std::string line);
	
	virtual void ExtractFunctionName(std::string line) = 0;
	
	public:
	std::wstring GetFileExtension();
	std::wstring GetKeywords();
	int GetLanguageId();

	std::string ReplaceCurrentLineNameIfMatched(std::string line_to_change, std::string replace_to) const;
	
	virtual ~AbstractLanguage();
	virtual void GenerateRegex(std::string line) = 0;
};