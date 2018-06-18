#pragma once
#include "IniCtrl.h"


struct Color {
	int item;
	COLORREF rgb;
};

class ScintillaCtrl {
protected:
	HWND scintillaCtrl;
	IniCtrl ini;
	Color clr;
protected:
	void SetUpEditor();
	LRESULT SendEditor(int msg, WPARAM wparam, LPARAM lparam = NULL);
	void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(56,57,58), int size=NULL, const char *face=NULL);
public:
	//construction and deconstruction
	ScintillaCtrl();
	~ScintillaCtrl();

	//general methods
	void SetScintillaCtrl(HWND wnd);
	void SetLang(int langm, bool clang=false);
	HWND GetScintillaCtrl();
};