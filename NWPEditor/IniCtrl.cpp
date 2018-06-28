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
	if (buffer != nullptr)
	{
		delete[] buffer;
		buffer = nullptr;
	}
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
	TCHAR buffer[sizeof(COLORREF)];

	WritePrivateProfileString(_T("colors"), _T("plain"), _itot(RGB(0, 0, 0), buffer, 10), _T("config/colors.ini"));				//black
	WritePrivateProfileString(_T("colors"), _T("comment"), _itot(RGB(0, 255, 0), buffer, 10), _T("config/colors.ini"));			//green
	WritePrivateProfileString(_T("colors"), _T("operators"), _itot(RGB(255, 0, 0), buffer, 10), _T("config/colors.ini"));		//red
	WritePrivateProfileString(_T("colors"), _T("selection"), _itot(RGB(51, 153, 255), buffer, 10), _T("config/colors.ini"));	//light-blue
	WritePrivateProfileString(_T("colors"), _T("string"), _itot(RGB(255, 255, 0), buffer, 10), _T("config/colors.ini"));		//yellow
	WritePrivateProfileString(_T("colors"), _T("number"), _itot(RGB(255, 0, 255), buffer, 10), _T("config/colors.ini"));		//magenta
	WritePrivateProfileString(_T("colors"), _T("uuid"), _itot(RGB(0, 255, 255), buffer, 10), _T("config/colors.ini"));			//cyan
	WritePrivateProfileString(_T("colors"), _T("preprocessor"), _itot(RGB(77, 77, 51), buffer, 10), _T("config/colors.ini"));	//gray
}

TCHAR* IniCtrl::GetKeywords() { return keywords; }

COLORREF IniCtrl::GetColor(TCHAR* colorName) 
{ 
	COLORREF color;

	color=GetPrivateProfileInt(_T("colors"), colorName, RGB(0, 0, 0), _T("config/colors.ini"));
	return color;
}

TCHAR* IniCtrl::GetFont()
{
	TCHAR font[50];

	GetPrivateProfileString(_T("font"), _T("font"), _T("Arial"), font, 50, _T("config/font.ini"));
	return font;
}

void IniCtrl::ChangeColor(COLORREF color, TCHAR* field)
{
	TCHAR* buffer = new TCHAR[RGB(255, 255, 255)];

	WritePrivateProfileString(_T("colors"), field, _itot(color, buffer, 10), _T("config/colors.ini"));

	delete[] buffer; buffer = nullptr;
}

void IniCtrl::ChangeFont(TCHAR* font)
{
	WritePrivateProfileString(_T("font"), _T("font"), font, _T("config/font.ini"));
}

void IniCtrl::SaveEditorState(TCHAR* field, TCHAR* value) 
{ 
	WritePrivateProfileString(_T("colors"), field, value, _T("config/colors.ini")); 
}

void IniCtrl::SaveEditorState(TCHAR* field, COLORREF value)
{
	TCHAR buffer[sizeof(COLORREF)];
	
	WritePrivateProfileString(_T("colors"), field, _itot(value, buffer, 10), _T("config/colors.ini"));
}