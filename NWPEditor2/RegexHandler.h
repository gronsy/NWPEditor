#pragma once
#include <string>
#include <regex>
#include <exception>
#include <exception>
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
	std::string &name_to_replace=std::string(), &replace_to=std::string();
	//Set to true only if rename is called from the function call in editor
	//Set to false if rename is called from function definition in editor
	bool is_function_call;
protected:
	bool CheckIfVariable(std::string line, System::Text::RegularExpressions::Regex^ lang_regex);
	bool CheckIfFunction(std::string line, System::Text::RegularExpressions::Regex^ lang_regex, bool is_call);
	void ExtractFunctionName(int lang, std::string line);
	System::String^ HandleMatch(System::Text::RegularExpressions::Match^ match);
public:
	void GenerateRegex(int lang, std::string line);
	std::string ReplaceInstances(std::string document_text, std::string replace_to);
};

public class EmptyFunctionNameException :std::exception
{
private:
	std::string error_message;
public:
	EmptyFunctionNameException(std::string message) :error_message(message) {};

	std::string GetErrorMessage() { return error_message; }
};