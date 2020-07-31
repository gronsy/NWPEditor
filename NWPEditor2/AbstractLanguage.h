#pragma once
#include <string>
#include <regex>
#include <sstream>

#define ITERATOR_SPACE_OR_DOT_OPERATOR_OFFSET 1
#define ERASE_OFFSET 1
#define STRING_BEGINNING 0
#define NUMBER_OF_CHARS_TO_DELETE_ON_RENAME 1

class AbstractLanguage
{
protected:
	std::string name_to_replace;
	std::regex regex_in_use;
	bool is_function_call, is_function;
	std::wstring file_extension;
	std::wstring keywords;
	int language_id;
	
protected:
	AbstractLanguage(std::wstring keywords, std::wstring file_extenstion, int language_id);
	bool CheckIfVariable(std::string line, std::regex language_regex);
	bool CheckIfFunction(std::string line, std::regex lang_regex);
	std::string CleanStringOfGarbage(std::string line);
	
	virtual void ExtractFunctionName(std::string line) = 0;
	virtual std::string ReplaceName(const std::string& line_text, const std::string& replace_to) = 0;
	virtual void SetIsFunctionCall(const std::string line) = 0;
	
public:
	std::wstring GetFileExtension();
	std::wstring GetKeywords();
	int GetLanguageId();

	std::string ReplaceCurrentLineNameIfMatched(const std::string& line_to_change, std::string replace_to);
	
	virtual ~AbstractLanguage();
	virtual void GenerateRegex(std::string line) = 0;
	virtual void GetCursorLineName(const std::string current_line, int cursor_index) = 0;
};