#include "ChildView.h"
#include "stdafx.h"
#include "IniCtrl.h"
#include <cstring>

IniCtrl::IniCtrl()
{
	buffer = nullptr;
	keywords = _T("");
}

IniCtrl::~IniCtrl()
{
	delete[] buffer;
	buffer = nullptr;
}

void IniCtrl::SendIni(int lang, bool clang) 
{
	TCHAR* keywordsLang;

	switch (lang) {
	case SCLEX_CPP:
		if (clang) {
			keywords = c_keywords;
			keywordsLang = _T("c");
			break;
		}
		keywordsLang = _T("cpp");
		keywords = cpp_keywords;
		break;
	case SCLEX_PYTHON:
		keywordsLang = _T("python");
		keywords = py_keywords;
		break;
	default:
		keywords = NULL;
	}
	
	LoadKeywords(keywordsLang);
	LoadColours(keywordsLang);
}

void IniCtrl::LoadColours(TCHAR* keywordsLang)
{
}

void IniCtrl::LoadKeywords(TCHAR* keywordsLang)
{
	int buffer_len = _tcslen(keywords) * 2;
	if (PathFileExists(_T("config/keywords.ini")))
		WriteKeywords();

	if (buffer != nullptr) delete[] buffer;

	buffer = new TCHAR[buffer_len];
	GetPrivateProfileString(_T("keywords"), keywordsLang, keywords, buffer, buffer_len, _T("config/keywords.ini"));
}

void IniCtrl::WriteKeywords() 
{
	WritePrivateProfileString(_T("keywords"), _T("cpp"), cpp_keywords, _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("c"), c_keywords, _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("python"), py_keywords, _T("config/keywords.ini"));
}

void IniCtrl::WriteColours() 
{
	
}

TCHAR* IniCtrl::GetKeywords() { return keywords; }