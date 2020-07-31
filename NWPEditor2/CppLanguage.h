#pragma once
#include <string>

#include "AbstractLanguage.h"
#include "EmptyFunctionNameException.h"

#define ITERATOR_CLANG_COLON_OR_ARROW_OPERATOR_OFFSET 2

class CppLanguage : public AbstractLanguage
{
protected:
	bool is_template;
	bool is_dot_method_call;
	bool is_arrow_method_call;
protected:
	void RemoveTypeIfTemplate(std::string& function_name);
	std::string DetermineFilter(const std::string line);
	virtual void ExtractFunctionName(std::string line) override;
	virtual std::string ReplaceName(const std::string& line_text, const std::string& replace_to) override;
	
	std::wstring GetCKeywords();
	std::wstring GetCppKeywords();
	virtual void SetIsFunctionCall(const std::string line) override;
public:
	CppLanguage(bool is_clang = false);
	virtual ~CppLanguage() override;
	
	virtual void GenerateRegex(std::string line) override;
	virtual void GetCursorLineName(const std::string current_line, int cursor_index) override;
};