#include "ChildView.h"
#include "IniCtrl.h"
#include "stdafx.h"
#include <cstring>
#include <locale>
#include <codecvt>

IniCtrl::IniCtrl()
{
	keywords = _T("");
}

IniCtrl::~IniCtrl()
{
}

void IniCtrl::SendIni(int lang, bool clang) 
{
	std::wstring keywordsLang;

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
		keywords = nullptr;
	}
	
	LoadKeywordsWFont(keywordsLang);
	LoadColours(keywordsLang);
}

void IniCtrl::LoadColours(const std::wstring& keywordsLang)
{
	if (!PathFileExists(_T("config/colors.ini")))
		WriteDefaultColours();
}

void IniCtrl::LoadKeywordsWFont(const std::wstring& keywordsLang)
{
	if (!PathFileExists(_T("config/keywords.ini")))
		WriteDefaultKeywords();

	if (!PathFileExists(_T("config/font.ini")))
		WriteDefaultFont();
}

void IniCtrl::WriteDefaultKeywords() 
{
	WritePrivateProfileString(_T("keywords"), _T("cpp"), cpp_keywords.c_str(), _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("c"), c_keywords.c_str(), _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("python"), py_keywords.c_str(), _T("config/keywords.ini"));
}

void IniCtrl::WriteDefaultFont(){ WritePrivateProfileString(_T("font"), _T("font"), _T("Arial"), _T("config/font.ini")); }

void IniCtrl::WriteDefaultColours() 
{
	std::wstring buffer;

	WritePrivateProfileString(_T("colors"), _T("plain"), std::to_wstring(RGB(0, 0, 0)).c_str(), _T("config/colors.ini"));				//black
	WritePrivateProfileString(_T("colors"), _T("comment"), std::to_wstring(RGB(0, 255, 0)).c_str(), _T("config/colors.ini"));			//green
	WritePrivateProfileString(_T("colors"), _T("operators"), std::to_wstring(RGB(255, 0, 0)).c_str(), _T("config/colors.ini"));		//red
	WritePrivateProfileString(_T("colors"), _T("selection"), std::to_wstring(RGB(51, 153, 255)).c_str(), _T("config/colors.ini"));	//light-blue
	WritePrivateProfileString(_T("colors"), _T("string"), std::to_wstring(RGB(255, 255, 0)).c_str(), _T("config/colors.ini"));		//yellow
	WritePrivateProfileString(_T("colors"), _T("number"), std::to_wstring(RGB(255, 0, 255)).c_str(), _T("config/colors.ini"));		//magenta
	WritePrivateProfileString(_T("colors"), _T("uuid"), std::to_wstring(RGB(0, 255, 255)).c_str(), _T("config/colors.ini"));			//cyan
	WritePrivateProfileString(_T("colors"), _T("preprocessor"), std::to_wstring(RGB(77, 77, 51)).c_str(), _T("config/colors.ini"));	//gray
	WritePrivateProfileString(_T("colors"), _T("keywords"), std::to_wstring(RGB(102, 0, 3)).c_str(), _T("config/colors.ini"));//purple
}

const std::string& IniCtrl::GetKeywords() 
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	return converter.to_bytes(keywords);
}

COLORREF IniCtrl::GetColor(const std::wstring& colorName) 
{ 
	COLORREF color;

	color=GetPrivateProfileInt(_T("colors"), colorName.c_str(), RGB(0, 0, 0), _T("config/colors.ini"));
	return color;
}

const std::wstring& IniCtrl::GetFont()
{
	std::wstring font;

	GetPrivateProfileString(_T("font"), _T("font"), _T("Arial"), &font[0], 50, _T("config/font.ini"));
	return font;
}

void IniCtrl::ChangeColor(const COLORREF color, const std::wstring& field)
{
	std::wstring buffer;

	WritePrivateProfileString(_T("colors"), field.c_str(), std::to_wstring(color).c_str(), _T("config/colors.ini"));
}

void IniCtrl::ChangeFont(const std::wstring& font)const
{
	WritePrivateProfileString(_T("font"), _T("font"), font.c_str(), _T("config/font.ini"));
}