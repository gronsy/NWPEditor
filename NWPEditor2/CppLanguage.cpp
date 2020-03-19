#include "stdafx.h"
#include "CppLanguage.h"

CppLanguage::CppLanguage(bool is_clang/*=false*/)
{
	if (is_clang)
		InitializeCLanguage();
	else
		InitializeCppLanguage();

	language_id = SCLEX_CPP;
}

void CppLanguage::InitializeCLanguage()
{
	keywords = L"auto break case char const continue delete do double "
		"else enum explicit float for goto if int long register "
		"return short signed sizeof static struct switch typedef while";

	file_extension = L"c";
}

void CppLanguage::InitializeCppLanguage()
{
	keywords = L"asm auto bool break case catch char class const "
		"dynamic_cast else enum explicit extern false finally "
		"float for friend goto if inline int long mutable "
		"namespace new operator private protected public "
		"register reinterpret_cast register return short signed "
		"sizeof static static_cast struct switch template "
		"this throw true try typedef typeid typename "
		"union unsigned using virtual void volatile "
		"wchar_t while";

	file_extension = L"cpp";
}

void CppLanguage::ExtractFunctionName(std::string line)
{
	std::string function_name;

	char filter = line.find(':') != std::string::npos ? ':' : ' ';

	int offset = filter == ':' ? ITERATOR_CLANG_COLON_OFFSET : ITERATOR_SPACE_OFFSET;

	if (filter == ':') {
		function_name = line;
		while (function_name.find(':') != std::string::npos)
			function_name = line.substr(function_name.find(filter) + offset, function_name.find('('));
	}
	else
		function_name = line.substr(line.find(filter) + offset, line.find('('));

	function_name = function_name.substr(STRING_BEGINNING, function_name.find('('));

	name_to_replace = function_name;
}

void CppLanguage::GenerateRegex(std::string line)
{
	line = line.substr(STRING_BEGINNING, line.find("\n") + ERASE_OFFSET);

	/*Regex^ cregex_function_definition = gcnew Regex(msclr::interop::marshal_as<System::String^>(".*(::)?.*\((\r?\n?).*\)\{?(.*\}|;)?\r?\n?"));
	Regex^ cregex_function_call = gcnew Regex(msclr::interop::marshal_as<System::String^>(".*?.*\(\)?;?"));*/

	std::regex cregex_function_definition = std::regex(R"(.*(::)?.*\((\r?\n?).*\)\{?(.*\}|;)?\r?\n?)");
	std::regex cregex_function_call = std::regex(R"(.*?.*\(\)?;?)");

	if (CheckIfFunction(line, cregex_function_definition, false) || CheckIfFunction(line, cregex_function_call, true))
	{
		ExtractFunctionName(line);

		if (name_to_replace == "")
			throw EmptyFunctionNameException("Function name not found.");

		/*regex_in_use = gcnew Regex(
			msclr::interop::marshal_as<System::String^>(".*(::)?" + name_to_replace + "\(.*\)\{?(.*\}|;)?\r?\n?"));*/
		regex_in_use = std::regex(".*(::)?" + name_to_replace + R"(\(.*\)\{?(.*\}|;)?\r?\n?)");
	}
}