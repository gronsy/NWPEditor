#pragma once
#include <string>

#include "AbstractLanguage.h"
#include "EmptyFunctionNameException.h"


class CppLanguage : public AbstractLanguage
{
protected:
	bool is_template;
protected:
	void RemoveTypeIfTemplate(std::string& function_name);
	virtual void ExtractFunctionName(std::string line) override;
	virtual std::string ReplaceName(const std::string& line_text, const std::string& replace_to) override;
	
	std::wstring GetCKeywords();
	std::wstring GetCppKeywords();
	virtual void SetIsFunctionCall(const std::string line) override;
public:
	CppLanguage(bool is_clang = false);
	virtual ~CppLanguage() override;
	
	virtual void GenerateRegex(std::string line) override;
};