#include "stdafx.h"
#include "IniCtrl.h"

std::wstring IniCtrl::cpp_keywords=L"asm auto bool break case catch char class const "
	"dynamic_cast else enum explicit extern false finally "
	"float for friend goto if inline int long mutable "
	"namespace new operator private protected public "
	"register reinterpret_cast register return short signed "
	"sizeof static static_cast struct switch template "
	"this throw true try typedef typeid typename "
	"union unsigned using virtual void volatile "
	"wchar_t while";

std::wstring IniCtrl::c_keywords= L"auto break case char const continue delete do double "
	"else enum explicit float for goto if int long register "
	"return short signed sizeof static struct switch typedef while";

std::wstring IniCtrl::py_keywords = L"False class finally is return None continue for lambda "
	"try True def from nonlocal while and del global not "
	"with as elif if or yield assert else import pass "
	"break except in raise";

IniCtrl::IniCtrl()
{
	m_keywords = L"";
	m_ini_path.LoadStringW(IDS_INI_COLOR_PATH);
	if (!PathFileExists(m_ini_path))
		WriteDefaultColours();

	m_ini_path.LoadStringW(IDS_INI_KW_PATH);
	if (!PathFileExists(m_ini_path))
		WriteDefaultKeywords();

	m_ini_path.LoadStringW(IDS_INI_FONT_PATH);
	if (!PathFileExists(m_ini_path))
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
			keywordsLang = L"c";
			break;
		}
		keywordsLang = L"cpp";
		m_keywords = cpp_keywords;
		break;
	case SCLEX_PYTHON:
		keywordsLang = L"python";
		m_keywords = py_keywords;
		break;
	default:
		m_keywords = L"";
	}
}

void IniCtrl::WriteDefaultKeywords() 
{
	m_ini_path.LoadString(IDS_INI_KW_PATH);
	WritePrivateProfileString(_T("keywords"), _T("cpp"), cpp_keywords.c_str(), m_ini_path);
	WritePrivateProfileString(_T("keywords"), _T("c"), c_keywords.c_str(), m_ini_path);
	WritePrivateProfileString(_T("keywords"), _T("python"), py_keywords.c_str(), m_ini_path);
}

void IniCtrl::WriteDefaultFont()
{
	m_ini_path.LoadString(IDS_INI_FONT_PATH);
	WritePrivateProfileString(_T("font"), _T("font"), _T("Arial"), m_ini_path);
}

void IniCtrl::WriteDefaultColours() 
{
	std::wstring buffer;
	m_ini_path.LoadString(IDS_INI_COLOR_PATH);
	WritePrivateProfileString(_T("colors"), _T("plain"), std::to_wstring(RGB(0, 0, 0)).c_str(), m_ini_path);				//black
	WritePrivateProfileString(_T("colors"), _T("comment"), std::to_wstring(RGB(0, 255, 0)).c_str(), m_ini_path);			//green
	WritePrivateProfileString(_T("colors"), _T("operators"), std::to_wstring(RGB(255, 0, 0)).c_str(), m_ini_path);		//red
	WritePrivateProfileString(_T("colors"), _T("selection"), std::to_wstring(RGB(51, 153, 255)).c_str(), m_ini_path);		//light-blue
	WritePrivateProfileString(_T("colors"), _T("string"), std::to_wstring(RGB(255, 255, 0)).c_str(), m_ini_path);			//yellow
	WritePrivateProfileString(_T("colors"), _T("number"), std::to_wstring(RGB(255, 0, 255)).c_str(), m_ini_path);			//magenta
	WritePrivateProfileString(_T("colors"), _T("uuid"), std::to_wstring(RGB(0, 255, 255)).c_str(), m_ini_path);			//cyan
	WritePrivateProfileString(_T("colors"), _T("preprocessor"), std::to_wstring(RGB(77, 77, 51)).c_str(), m_ini_path);	//gray
	WritePrivateProfileString(_T("colors"), _T("m_keywords"), std::to_wstring(RGB(102, 0, 3)).c_str(), m_ini_path);		//purple
}

const std::string IniCtrl::GetKeywords() const
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	return converter.to_bytes(m_keywords);
}

COLORREF IniCtrl::GetColor(const std::wstring& colorName) 
{ 
	m_ini_path.LoadString(IDS_INI_COLOR_PATH);
	COLORREF color=GetPrivateProfileInt(_T("colors"), colorName.c_str(), RGB(0, 0, 0), m_ini_path);
	return color;
}

const std::string IniCtrl::GetFont()
{
	std::wstring font;

	m_ini_path.LoadString(IDS_INI_FONT_PATH);
	GetPrivateProfileString(L"font", L"font", L"Arial", &font[0], 50, m_ini_path);
	return std::string(font.begin(), font.end());
}

void IniCtrl::ChangeColor(const COLORREF color, const std::wstring& field)
{
	std::wstring buffer;

	m_ini_path.LoadString(IDS_INI_COLOR_PATH);
	WritePrivateProfileString(_T("colors"), field.c_str(), std::to_wstring(color).c_str(), m_ini_path);
}

void IniCtrl::ChangeFont(const std::wstring& font)
{
	m_ini_path.LoadStringW(IDS_INI_FONT_PATH);
	WritePrivateProfileString(_T("font"), _T("font"), font.c_str(), m_ini_path);
}