#include "stdafx.h"

const COLORREF black = RGB(0, 0, 0);
const COLORREF white = RGB(255, 255, 255);
const COLORREF green = RGB(0, 255, 0);
const COLORREF red = RGB(255, 0, 0);
const COLORREF blue = RGB(0, 0, 255);
const COLORREF yellow = RGB(255, 255, 0);
const COLORREF magenta = RGB(255, 0, 255);
const COLORREF cyan = RGB(0, 255, 255);

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
	TCHAR* buffer;
	TCHAR* keywords;

	void writeKeywords();
	void writeColours();
public:
	void sendIni(int lang, bool clang=false);
	void loadKeywords();
	void loadColours();
	void saveKeywords();
	void saveColours();
};