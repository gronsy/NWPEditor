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
	"return short signed sizeof static struct switch typedef while");

std::wstring IniCtrl::py_keywords = _T("False class finally is return None continue for lambda "
	"try True def from nonlocal while and del global not "
	"with as elif if or yield assert else import pass "
	"break except in raise");

IniCtrl::IniCtrl()
{
	m_keywords = _T("");
	if (!PathFileExists(_T("config/colors.ini")))
		WriteDefaultColours();

	if (!PathFileExists(_T("config/m_keywords.ini")))
		WriteDefaultKeywords();

	if (!PathFileExists(_T("config/font.ini")))
		WriteDefaultFont();
}

IniCtrl::~IniCtrl()
{
}

void IniCtrl::SendIni(int lang, bool clang/*=false*/) 
{
	std::wstring keywordsLang;

	switch (lang) {
	case SCLEX_CPP:
		if (clang) {
			m_keywords = c_keywords;
			keywordsLang = _T("c");
			break;
		}
		keywordsLang = _T("cpp");
		m_keywords = cpp_keywords;
		break;
	case SCLEX_PYTHON:
		keywordsLang = _T("python");
		m_keywords = py_keywords;
		break;
	default:
		m_keywords = _T("");
	}
}

CString IniCtrl::LoadPath(int id)
{
	CString path;
	path.LoadString(id);
	return path;
}

void IniCtrl::WriteDefaultKeywords() 
{
	CString path=LoadPath(IDS_INI_KW_PATH);
	WritePrivateProfileString(_T("keywords"), _T("cpp"), cpp_keywords.c_str(), path);
	WritePrivateProfileString(_T("keywords"), _T("c"), c_keywords.c_str(), path);
	WritePrivateProfileString(_T("keywords"), _T("python"), py_keywords.c_str(), path);
}

void IniCtrl::WriteDefaultFont()
{
	CString path=LoadPath(IDS_INI_FONT_PATH);

	WritePrivateProfileString(_T("font"), _T("font"), _T("Arial"), path);
}

void IniCtrl::WriteDefaultColours() 
{
	std::wstring buffer;
	CString path=LoadPath(IDS_INI_COLOR_PATH);
	WritePrivateProfileString(_T("colors"), _T("plain"), std::to_wstring(RGB(0, 0, 0)).c_str(), path);				//black
	WritePrivateProfileString(_T("colors"), _T("comment"), std::to_wstring(RGB(0, 255, 0)).c_str(), path);			//green
	WritePrivateProfileString(_T("colors"), _T("operators"), std::to_wstring(RGB(255, 0, 0)).c_str(), path);		//red
	WritePrivateProfileString(_T("colors"), _T("selection"), std::to_wstring(RGB(51, 153, 255)).c_str(), path);		//light-blue
	WritePrivateProfileString(_T("colors"), _T("string"), std::to_wstring(RGB(255, 255, 0)).c_str(), path);			//yellow
	WritePrivateProfileString(_T("colors"), _T("number"), std::to_wstring(RGB(255, 0, 255)).c_str(), path);			//magenta
	WritePrivateProfileString(_T("colors"), _T("uuid"), std::to_wstring(RGB(0, 255, 255)).c_str(), path);			//cyan
	WritePrivateProfileString(_T("colors"), _T("preprocessor"), std::to_wstring(RGB(77, 77, 51)).c_str(), path);	//gray
	WritePrivateProfileString(_T("colors"), _T("m_keywords"), std::to_wstring(RGB(102, 0, 3)).c_str(), path);		//purple
}

const std::string IniCtrl::GetKeywords() const
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	return converter.to_bytes(m_keywords);
}

COLORREF IniCtrl::GetColor(const std::wstring& colorName) 
{ 
	CString path = LoadPath(IDS_INI_COLOR_PATH);
	COLORREF color=GetPrivateProfileInt(_T("colors"), colorName.c_str(), RGB(0, 0, 0), path);
	return color;
}

const std::string IniCtrl::GetFont()
{
	std::wstring font;

	CString path = LoadPath(IDS_INI_FONT_PATH);
	GetPrivateProfileString(_T("font"), _T("font"), _T("Arial"), &font[0], 50, path);
	return std::string(font.begin(), font.end());
}

void IniCtrl::ChangeColor(const COLORREF color, const std::wstring& field)
{
	std::wstring buffer;

	CString path = LoadPath(IDS_INI_COLOR_PATH);
	WritePrivateProfileString(_T("colors"), field.c_str(), std::to_wstring(color).c_str(), path);
}

void IniCtrl::ChangeFont(const std::wstring& font)const
{
	CString path = LoadPath(IDS_INI_FONT_PATH);
	WritePrivateProfileString(_T("font"), _T("font"), font.c_str(), path);
}