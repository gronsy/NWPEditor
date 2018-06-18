#include "ChildView.h"
#include "stdafx.h"
#include "IniCtrl.h"
#include <cstring>

IniCtrl::IniCtrl()
{
	buffer = nullptr;
	keywords = _T("");

	default_colors["black"] = RGB(0, 0, 0);
	default_colors["green"] = RGB(0, 255, 00);
	default_colors["red"] = RGB(255, 0, 0);
	default_colors["blue"] = RGB(0, 0, 255);
	default_colors["yellow"] = RGB(255, 255, 0);
	default_colors["magenta"] = RGB(255, 0, 255);
	default_colors["cyan"] = RGB(0, 255, 255);
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
	if (PathFileExists(wcscat(_T("config/"), wcscat(keywordsLang, _T(".ini")))))
		WriteColours();

	
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
COLORREF* IniCtrl::GetColor(std::string key) { return &default_colors[key]; }