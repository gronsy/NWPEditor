#pragma once
#include <string>
#include <regex>
#include <exception>
#include <exception>
#include <algorithm>
#include <msclr/marshal_cppstd.h>

#using <System.dll>
#using <System.Text.RegularExpressions.dll>

#define ITERATOR_CLANG_COLON_OFFSET 2
#define ITERATOR_SPACE_OFFSET 1
#define ERASE_OFFSET 1
#define STRING_BEGINNING 0

public ref class RegexHandler
{
	System::Text::RegularExpressions::Regex^ regex_in_use;
	//Set to true only if rename is called from the function call in editor
	//Set to false if rename is called from function definition in editor
	bool is_function_call;
protected:
	
	bool CheckIfVariable(std::string line, System::Text::RegularExpressions::Regex^ lang_regex);
	bool CheckIfFunction(std::string line, System::Text::RegularExpressions::Regex^ lang_regex, bool is_call);
	std::string ExtractFunctionName(int lang, std::string line);
	std::string ExtractCTypeName(std::string::iterator string_iterator);
public:
	void ParseRegex(int lang, std::string line);
	System::Text::RegularExpressions::Regex^ GetRegexInUse();
};

public class EmptyFunctionNameException :std::exception
{
private:
	std::string error_message;
public:
	EmptyFunctionNameException(std::string message) :error_message(message) {};

	std::string GetErrorMessage() { return error_message; }
};