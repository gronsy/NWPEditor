#pragma once
#include "ColorPickDlg.h"
#include <string>
#include <locale>
#include <codecvt>

//Default keyords
std::wstring cpp_keywords = _T("asm auto bool break case catch char class const "
	"dynamic_cast else enum explicit extern false finally "
	"float for friend goto if inline int long mutable "
	"namespace new operator private protected public "
	"register reinterpret_cast register return short signed "
	"sizeof static static_cast struct switch template "
	"this throw true try typedef typeid typename "
	"union unsigned using virtual void volatile "
	"wchar_t while");

std::wstring c_keywords = _T("auto break case char const continue delete do double "
	"else enum explicit float for goto if int long register "
	"return short signed sizeof static struct switch typedef"
	);

std::wstring py_keywords = _T("False class finally is return None continue for lambda "
	"try True def from nonlocal while and del global not "
	"with as elif if or yield assert else import pass "
	"break except in raise");

class IniCtrl {
	friend void ColorPickDlg::OnBtnDefault();
protected:
	std::wstring  keywords;
	int lang;

	static void WriteDefaultKeywords();
	static void WriteDefaultColours();
	static void WriteDefaultFont();
	void LoadKeywordsWFont(const std::wstring& keywordsLang);
	void LoadColours(const std::wstring& keywordsLang);
public:
	IniCtrl();
	~IniCtrl();
	void SendIni(int lang, bool clang=false);
	const std::string& GetKeywords();
	COLORREF GetColor(const std::wstring& colorName);
	const std::wstring& GetFont();
	void ChangeColor(const COLORREF color, const std::wstring& field);
	void ChangeFont(const std::wstring& font)const;
};