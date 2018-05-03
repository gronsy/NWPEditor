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
public:
	//construction and deconstruction
	ScintillaCtrl();
	~ScintillaCtrl();

	//general methods
	void setScintillaCtrl(HWND wnd);
	void setLang(int langm, bool clang=false);
	HWND getScintillaCtrl();
	LRESULT SendEditor(int msg, WPARAM wparam, LPARAM lparam=NULL);
};