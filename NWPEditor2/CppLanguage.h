#pragma once
#include <string>

#include "AbstractLanguage.h"
#include "EmptyFunctionNameException.h"



class CppLanguage : public AbstractLanguage
{
protected:
	virtual void ExtractFunctionName(std::string line) override;
	virtual std::string ReplaceName(const std::string& line_text) override;
	
	std::wstring GetCKeywords();
	std::wstring GetCppKeywords();
public:
	CppLanguage(bool is_clang = false);
	virtual ~CppLanguage() override;
	
	virtual void GenerateRegex(std::string line) override;
};