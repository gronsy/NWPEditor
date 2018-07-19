#pragma once
#include "IniCtrl.h"
#include "Snapshot.h"

class ScintillaCtrl {
protected:
	HWND scintillaCtrl;
	IniCtrl ini;
protected:
	void SetUpEditor();
	LRESULT SendEditor(int msg, WPARAM wparam, LPARAM lparam = NULL);
	void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(255,255,255), int size=NULL, const char *face=NULL);
public:
	//construction and deconstruction
	ScintillaCtrl();
	~ScintillaCtrl();

	void SetScintillaCtrl(HWND wnd);
	void SetLang(int langm, bool clang=false);
	void LoadDefaultState();
	void UpdateColor(TCHAR* field);
	void AutoCompKey(UINT key);
	IniCtrl GetIni();
	HWND GetScintillaCtrl();
};