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

public:
	//construction and deconstruction
	ScintillaCtrl();
	~ScintillaCtrl();

	//general methods
	void SetScintillaCtrl(HWND wnd);
	void SetLang(int langm, bool clang=false);
	HWND GetScintillaCtrl();
	LRESULT SendEditor(int msg, WPARAM wparam, LPARAM lparam=NULL);
};