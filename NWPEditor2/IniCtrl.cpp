#include "stdafx.h"
#include "IniCtrl.h"

std::wstring IniCtrl::cpp_keywords = L"asm auto bool break case catch char class const "
"dynamic_cast else enum explicit extern false finally "
"float for friend goto if inline int long mutable "
"namespace new operator private protected public "
"register reinterpret_cast register return short signed "
"sizeof static static_cast struct switch template "
"this throw true try typedef typeid typename "
"union unsigned using virtual void volatile "
"wchar_t while";

std::wstring IniCtrl::c_keywords = L"auto break case char const continue delete do double "
"else enum explicit float for goto if int long register "
"return short signed sizeof static struct switch typedef while";

std::wstring IniCtrl::py_keywords = L"False class finally is return None continue for lambda "
"try True def from nonlocal while and del global not "
"with as elif if or yield assert else import pass "
"break except in raise";

IniCtrl::IniCtrl(bool init/*=true*/)
{
	if (init)
	{
		m_keywords = L"";

		if (GetFileAttributesA("config") == INVALID_FILE_ATTRIBUTES)
			CreateDirectoryA("config", NULL);

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
}

IniCtrl::~IniCtrl()
{
}

void IniCtrl::SetKeywords(std::wstring keywords)
{
	m_keywords = keywords;
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
	WritePrivateProfileString(_T("font"), _T("size"), _T("12"), m_ini_path);
	WritePrivateProfileString(_T("font"), _T("isItalic"), _T("0"), m_ini_path);
	WritePrivateProfileString(_T("font"), _T("isUnderline"), _T("0"), m_ini_path);
	WritePrivateProfileString(_T("font"), _T("weight"), _T("400"), m_ini_path);	//Normal weight according to msdn
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
	WritePrivateProfileString(_T("colors"), _T("keywords"), std::to_wstring(RGB(102, 0, 3)).c_str(), m_ini_path);		//purple
}

const std::string IniCtrl::GetKeywords() const
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	return converter.to_bytes(m_keywords);
}

COLORREF IniCtrl::GetColor(const std::wstring & colorName)
{
	m_ini_path.LoadString(IDS_INI_COLOR_PATH);
	COLORREF color = GetPrivateProfileInt(_T("colors"), colorName.c_str(), RGB(0, 0, 0), m_ini_path);
	return color;
}

void IniCtrl::ChangeColor(const COLORREF color, const std::wstring & field)
{
	std::wstring buffer;

	m_ini_path.LoadString(IDS_INI_COLOR_PATH);
	WritePrivateProfileString(_T("colors"), field.c_str(), std::to_wstring(color).c_str(), m_ini_path);
}

void IniCtrl::ChangeFont(const LOGFONT & lf, int size)
{
	m_ini_path.LoadStringW(IDS_INI_FONT_PATH);

	WritePrivateProfileString(_T("font"), _T("font"), lf.lfFaceName, m_ini_path);
	if (size <= 72)
		WritePrivateProfileString(_T("font"), _T("size"), std::to_wstring(size).c_str(), m_ini_path);
	WritePrivateProfileString(_T("font"), _T("weight"), std::to_wstring(lf.lfWeight).c_str(), m_ini_path);

	if (lf.lfItalic == TRUE)
		WritePrivateProfileString(_T("font"), _T("isItalic"), _T("1"), m_ini_path);
	else
		WritePrivateProfileString(_T("font"), _T("isItalic"), _T("0"), m_ini_path);

	if (lf.lfUnderline == TRUE)
		WritePrivateProfileString(_T("font"), _T("isUnderline"), _T("1"), m_ini_path);
	else
		WritePrivateProfileString(_T("font"), _T("isUnderline"), _T("0"), m_ini_path);

	WritePrivateProfileString(_T("font"), _T("height"), std::to_wstring(lf.lfHeight).c_str(), m_ini_path);
	WritePrivateProfileString(_T("font"), _T("width"), std::to_wstring(lf.lfWidth).c_str(), m_ini_path);
}

LOGFONT IniCtrl::GetFontProps(bool width_height/*=false*/)
{
	LOGFONT lf;
	m_ini_path.LoadStringW(IDS_INI_FONT_PATH);
	GetPrivateProfileString(_T("font"), _T("font"), _T("Arial"), lf.lfFaceName, LF_FACESIZE, m_ini_path);
	//Filling Height property of lfHeight so i can just transfer size with structure
	lf.lfHeight = GetPrivateProfileInt(_T("font"), _T("size"), 12, m_ini_path);
	lf.lfItalic = GetPrivateProfileInt(_T("font"), _T("isItalic"), FALSE, m_ini_path);
	lf.lfUnderline = GetPrivateProfileInt(_T("font"), _T("Italic"), FALSE, m_ini_path);
	lf.lfWeight = GetPrivateProfileInt(_T("font"), _T("weight"), FW_NORMAL, m_ini_path);

	if (width_height)
	{
		lf.lfHeight = GetPrivateProfileInt(_T("font"), _T("height"), -12, m_ini_path);
		lf.lfWidth = GetPrivateProfileInt(_T("font"), _T("width"), 0, m_ini_path);
	}

	lf.lfCharSet = NULL;
	lf.lfClipPrecision = NULL;
	lf.lfEscapement = NULL;
	lf.lfOrientation = NULL;
	lf.lfOutPrecision = NULL;
	lf.lfPitchAndFamily = NULL;
	lf.lfQuality = NULL;
	lf.lfStrikeOut = NULL;

	return lf;
}

int IniCtrl::GetFontHeight()
{
	m_ini_path.LoadStringW(IDS_INI_FONT_PATH);
	return -GetPrivateProfileInt(_T("font"), _T("height"), -12, m_ini_path);
}

void IniCtrl::AddBookmarkEntry(const std::wstring & bookmarkName,
	const std::wstring & filePath,
	const int line)
{
	m_ini_path.LoadStringW(IDS_INI_BOOKMARKS_PATH);
	WritePrivateProfileString(filePath.c_str(), bookmarkName.c_str(), std::to_wstring(line).c_str(), m_ini_path);
}

std::vector<Bookmark> IniCtrl::GetBookmarks(const std::wstring & fileName)
{
	m_ini_path.LoadStringW(IDS_INI_BOOKMARKS_PATH);
	wchar_t buffer[BOOKMARK_BUFFER_SIZE];

	GetPrivateProfileString(fileName.c_str(), NULL, NULL, buffer, BOOKMARK_BUFFER_SIZE, m_ini_path);

	wchar_t* bufferPtr = buffer;
	std::vector<Bookmark> bookmarks;

	while (*bufferPtr != L'\0')
	{
		WCHAR lineBuffer[CHARS_TO_READ];
		bookmarks.push_back(Bookmark(bufferPtr, GetPrivateProfileString(fileName.c_str(), bufferPtr, NULL, lineBuffer, CHARS_TO_READ, m_ini_path)));
		bufferPtr = wcschr(bufferPtr, L'\0');
		++bufferPtr;
	}

	return bookmarks;
}