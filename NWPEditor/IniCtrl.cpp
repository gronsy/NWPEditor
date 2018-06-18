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
	if (!PathFileExists(_T("config/colors.ini")))
		WriteDefaultColours();
}

void IniCtrl::LoadKeywords(TCHAR* keywordsLang)
{
	int buffer_len = _tcslen(keywords) * 2;
	if (!PathFileExists(_T("config/keywords.ini")))
		WriteDefaultKeywords();

	if (buffer != nullptr) 
		delete[] buffer;

	buffer = new TCHAR[buffer_len];
	GetPrivateProfileString(_T("keywords"), keywordsLang, keywords, buffer, buffer_len, _T("config/keywords.ini"));
}

void IniCtrl::WriteDefaultKeywords() 
{
	WritePrivateProfileString(_T("keywords"), _T("cpp"), cpp_keywords, _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("c"), c_keywords, _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("python"), py_keywords, _T("config/keywords.ini"));
}

void IniCtrl::WriteDefaultColours() 
{
	TCHAR* buffer = new TCHAR[RGB(255, 255, 255)];

	WritePrivateProfileString(_T("colors"), _T("black"), _itot(default_colors["black"], buffer, 10), _T("config/colors.ini"));
	WritePrivateProfileString(_T("colors"), _T("green"), _itot(default_colors["green"], buffer, 10), _T("config/colors.ini"));
	WritePrivateProfileString(_T("colors"), _T("red"), _itot(default_colors["red"], buffer, 10), _T("config/colors.ini"));
	WritePrivateProfileString(_T("colors"), _T("blue"), _itot(default_colors["blue"], buffer, 10), _T("config/colors.ini"));
	WritePrivateProfileString(_T("colors"), _T("yellow"), _itot(default_colors["yellow"], buffer, 10), _T("config/colors.ini"));
	WritePrivateProfileString(_T("colors"), _T("magenta"), _itot(default_colors["magenta"], buffer, 10), _T("config/colors.ini"));
	WritePrivateProfileString(_T("colors"), _T("cyan"), _itot(default_colors["cyan"], buffer, 10), _T("config/colors.ini"));

	delete[] buffer; buffer = nullptr;
}

TCHAR* IniCtrl::GetKeywords() { return keywords; }
COLORREF* IniCtrl::GetColor(std::string key) { return &default_colors[key]; }