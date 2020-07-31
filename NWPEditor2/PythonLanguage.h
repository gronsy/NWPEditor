#pragma once
#include "AbstractLanguage.h"
#include <string>

class PythonLanguage :public AbstractLanguage
{
	virtual void ExtractFunctionName(std::string line) override;
	virtual std::string ReplaceName(const std::string& line_text, const std::string& replace_to) override;
	virtual void SetIsFunctionCall(const std::string line) override;
public:
	PythonLanguage();
	virtual ~PythonLanguage() override;
	void GenerateRegex(std::string line) override;
	std::wstring GetPythonKeywords();
	void GetCursorLineName(const std::string current_line, int cursor_index) override;
};

