#include "stdafx.h"
#pragma once
#include "PythonLanguage.h"

PythonLanguage::PythonLanguage():
AbstractLanguage(GetPythonKeywords(), L"py", SCLEX_PYTHON)
{
	
}

PythonLanguage::~PythonLanguage()
{
	
}


void PythonLanguage::ExtractFunctionName(std::string line)
{
	
}

void PythonLanguage::GenerateRegex(std::string line)
{
	
}

std::wstring PythonLanguage::GetPythonKeywords()
{
	return L"";
}
