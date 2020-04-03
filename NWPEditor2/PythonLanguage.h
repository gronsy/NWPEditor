#pragma once
#include "AbstractLanguage.h"

class PythonLanguage :public AbstractLanguage
{
	virtual void ExtractFunctionName(std::string line) override;
public:
	PythonLanguage();
	virtual ~PythonLanguage();
	virtual void GenerateRegex(std::string line) override;
};

