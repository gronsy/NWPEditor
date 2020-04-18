#pragma once
#include "AbstractLanguage.h"
#include <string>

class PythonLanguage :public AbstractLanguage
{
	virtual void ExtractFunctionName(std::string line) override;
public:
	PythonLanguage();
	virtual ~PythonLanguage() override;
	void GenerateRegex(std::string line) override;
	std::wstring GetPythonKeywords();
};

