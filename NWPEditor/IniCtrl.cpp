#include "ChildView.h"
#include "stdafx.h"
#include "IniCtrl.h"


void IniCtrl::sendIni(int lang, bool clang) 
{
	if (clang) keywords = c_keywords;
	else if (lang == SCLEX_CPP) keywords = cpp_keywords;
	else if (lang == SCLEX_PYTHON)keywords = py_keywords;
	
	loadKeywords();
	loadColours();
}

void IniCtrl::loadColours()
{
}

void IniCtrl::loadKeywords()
{
	int buffer_len = _tcslen(cpp_keywords);
	buffer = new TCHAR[buffer_len + 1];

	GetPrivateProfileString(_T("Keywords"), _T("cpp"), cpp_keywords, buffer, buffer_len, _T("config/keywords.ini"));
	delete[] buffer; buffer = nullptr;
}

void IniCtrl::saveColours()
{

}

void IniCtrl::saveKeywords()
{

}