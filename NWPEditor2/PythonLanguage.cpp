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

void PythonLanguage::SetIsFunctionCall(const std::string line)
{
	
}

std::wstring PythonLanguage::GetPythonKeywords()
{
	return L"";
}

std::string PythonLanguage::ReplaceName(const std::string& line_text, const std::string& replace_to)
{
	return "";
}

void PythonLanguage::GetCursorLineName(const std::string current_line, int cursor_index)
{
	
}