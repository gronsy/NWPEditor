#pragma once
#include <string>
#include <locale>
#include <codecvt>
#include "resource.h"

class IniCtrl 
{
protected:
	std::wstring  m_keywords;
	static std::wstring cpp_keywords, c_keywords, py_keywords;
	int m_lang;
	CString m_ini_path;

public:
	IniCtrl();
	~IniCtrl();
	void SendIni(int lang, bool clang=false);
	const std::string GetKeywords() const;
	COLORREF GetColor(const std::wstring& colorName);
	const std::string GetFont();
	void ChangeColor(const COLORREF color, const std::wstring& field);
	void ChangeFont(const std::wstring& font);

	void WriteDefaultKeywords();
	void WriteDefaultColours();
	void WriteDefaultFont();
};