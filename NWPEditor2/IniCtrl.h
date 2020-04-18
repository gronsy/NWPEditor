#pragma once
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include "Bookmark.h"
#include "resource.h"

#define CHARS_TO_READ 1024
#define BOOKMARK_BUFFER_SIZE 32767

class IniCtrl
{
protected:
	std::wstring  m_keywords;
	static std::wstring cpp_keywords, c_keywords, py_keywords;
	int m_lang;
	CString m_ini_path;

public:
	IniCtrl(bool init = true);
	~IniCtrl();
	void SetKeywords(std::wstring keywords);
	const std::string GetKeywords() const;
	COLORREF GetColor(const std::wstring& colorName);
	void ChangeColor(const COLORREF color, const std::wstring& field);
	void ChangeFont(const LOGFONT& lf, int size);
	LOGFONT GetFontProps(bool widthHeight = false);
	int GetFontHeight();

	void WriteDefaultKeywords();
	void WriteDefaultColours();
	void WriteDefaultFont();

	void AddBookmarkEntry(const std::wstring& bookmarkName,
		const std::wstring& fileName,
		const int line);
	std::vector<Bookmark> GetBookmarks(const std::wstring& fileName);
};