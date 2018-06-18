#include "stdafx.h"
#include <map>

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
	std::map<std::string, COLORREF> default_colors;
	int lang;

	void WriteKeywords();
	void WriteColours();
	void LoadKeywords(TCHAR* keywordsLang);
	void LoadColours(TCHAR* keywordsLang);
public:
	IniCtrl();
	~IniCtrl();
	//Chooses language to load from ini files
	void SendIni(int lang, bool clang=false);
	TCHAR* GetKeywords();
	COLORREF* GetColor(std::string key);
};