#pragma once
#include <string>
#include <locale>
#include <codecvt>
#include "resource.h"

#define CHARS_TO_READ 1024

class IniCtrl 
{
protected:
	std::wstring  m_keywords;
	static std::wstring cpp_keywords, c_keywords, py_keywords;
	int m_lang;
	CString m_ini_path;

public:
	IniCtrl(bool init=true);
	~IniCtrl();
	void SendIni(int lang, bool clang=false);
	const std::string GetKeywords() const;
	COLORREF GetColor(const std::wstring& colorName);
	void ChangeColor(const COLORREF color, const std::wstring& field);
	void ChangeFont(const LOGFONT& lf, int size);
	LOGFONT GetFontProps(bool width_height=false);

	void WriteDefaultKeywords();
	void WriteDefaultColours();
	void WriteDefaultFont();
};