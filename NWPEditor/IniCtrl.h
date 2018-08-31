#pragma once
#include <string>
#include <locale>
#include <codecvt>

class IniCtrl 
{
protected:
	std::wstring  keywords;
	static std::wstring cpp_keywords, c_keywords, py_keywords;
	int lang;

public:
	IniCtrl();
	~IniCtrl();
	void SendIni(int lang, bool clang=false);
	const std::string GetKeywords() const;
	COLORREF GetColor(const std::wstring& colorName);
	const std::string GetFont();
	void ChangeColor(const COLORREF color, const std::wstring& field);
	void ChangeFont(const std::wstring& font)const;

	static void WriteDefaultKeywords();
	static void WriteDefaultColours();
	static void WriteDefaultFont();
};