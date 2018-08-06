#include "stdafx.h"
#include "IniCtrl.h"

std::wstring IniCtrl::cpp_keywords=_T("asm auto bool break case catch char class const "
	"dynamic_cast else enum explicit extern false finally "
	"float for friend goto if inline int long mutable "
	"namespace new operator private protected public "
	"register reinterpret_cast register return short signed "
	"sizeof static static_cast struct switch template "
	"this throw true try typedef typeid typename "
	"union unsigned using virtual void volatile "
	"wchar_t while");

std::wstring IniCtrl::c_keywords= _T("auto break case char const continue delete do double "
	"else enum explicit float for goto if int long register "
	"return short signed sizeof static struct switch typedef");

std::wstring IniCtrl::py_keywords = _T("False class finally is return None continue for lambda "
	"try True def from nonlocal while and del global not "
	"with as elif if or yield assert else import pass "
	"break except in raise");

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
		keywords = _T("");
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
	WritePrivateProfileString(_T("keywords"), _T("cpp"), IniCtrl::cpp_keywords.c_str(), _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("c"), IniCtrl::c_keywords.c_str(), _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("python"), IniCtrl::py_keywords.c_str(), _T("config/keywords.ini"));
}

void IniCtrl::WriteDefaultFont(){ WritePrivateProfileString(_T("font"), _T("font"), _T("Arial"), _T("config/font.ini")); }

void IniCtrl::WriteDefaultColours() 
{
	std::wstring buffer;

	WritePrivateProfileString(_T("colors"), _T("plain"), std::to_wstring(RGB(0, 0, 0)).c_str(), _T("config/colors.ini"));			//black
	WritePrivateProfileString(_T("colors"), _T("comment"), std::to_wstring(RGB(0, 255, 0)).c_str(), _T("config/colors.ini"));		//green
	WritePrivateProfileString(_T("colors"), _T("operators"), std::to_wstring(RGB(255, 0, 0)).c_str(), _T("config/colors.ini"));		//red
	WritePrivateProfileString(_T("colors"), _T("selection"), std::to_wstring(RGB(51, 153, 255)).c_str(), _T("config/colors.ini"));	//light-blue
	WritePrivateProfileString(_T("colors"), _T("string"), std::to_wstring(RGB(255, 255, 0)).c_str(), _T("config/colors.ini"));		//yellow
	WritePrivateProfileString(_T("colors"), _T("number"), std::to_wstring(RGB(255, 0, 255)).c_str(), _T("config/colors.ini"));		//magenta
	WritePrivateProfileString(_T("colors"), _T("uuid"), std::to_wstring(RGB(0, 255, 255)).c_str(), _T("config/colors.ini"));		//cyan
	WritePrivateProfileString(_T("colors"), _T("preprocessor"), std::to_wstring(RGB(77, 77, 51)).c_str(), _T("config/colors.ini"));	//gray
	WritePrivateProfileString(_T("colors"), _T("keywords"), std::to_wstring(RGB(102, 0, 3)).c_str(), _T("config/colors.ini"));		//purple
}

const std::string IniCtrl::GetKeywords() const
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	return converter.to_bytes(keywords);
}

COLORREF IniCtrl::GetColor(const std::wstring& colorName) 
{ 
	COLORREF color=GetPrivateProfileInt(_T("colors"), colorName.c_str(), RGB(0, 0, 0), _T("config/colors.ini"));
	return color;
}

const std::wstring IniCtrl::GetFont()
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