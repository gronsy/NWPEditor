#include "stdafx.h"
#include <string>

//Default keyords
static TCHAR* cpp_keywords = _T("asm auto bool break case catch char class const "
	"dynamic_cast else enum explicit extern false finally "
	"float for friend goto if inline int long mutable "
	"namespace new operator private protected public "
	"register reinterpret_cast register return short signed "
	"sizeof static static_cast struct switch template "
	"this throw true try typedef typeid typename "
	"union unsigned using virtual void volatile "
	"wchar_t while");

static TCHAR* c_keywords = _T("auto break case char const continue delete do double "
	"else enum explicit float for goto if int long register "
	"return short signed sizeof static struct switch typedef "
	"return shotrt signed sizeof static struct switch typedef");

static TCHAR* py_keywords = _T("False class finally is return None continue for lambda "
	"try True def from nonlocal while and del global not "
	"with as elif if or yield assert else import pass "
	"break except in raise");

class IniCtrl {
protected:
	TCHAR *buffer, *keywords;
	int lang;

	void WriteDefaultKeywords();
	void WriteDefaultColours();
	void LoadKeywords(TCHAR* keywordsLang);
	void LoadColours(TCHAR* keywordsLang);
public:
	IniCtrl();
	~IniCtrl();
	void SendIni(int lang, bool clang=false);
	TCHAR* GetKeywords();
	COLORREF GetColor(TCHAR* colorName);
	TCHAR* GetFont();
	void AddColor(COLORREF color, TCHAR* name);
	void AddFont(TCHAR* font);
	void SaveEditorState(TCHAR* field, TCHAR* value);
	void SaveEditorState(TCHAR* field, COLORREF value);
};