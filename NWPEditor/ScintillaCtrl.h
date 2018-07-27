#pragma once
#include "IniCtrl.h"
//#include "Snapshot.h"
#include <string>

class ScintillaCtrl {
protected:
	HWND scintillaCtrl;
	IniCtrl ini;
protected:
	void SetUpEditor();
	void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(255,255,255), int size=NULL, const std::string face=NULL);
	LRESULT SendEditor(int msg, WPARAM wparam, LPARAM lparam = NULL);
public:
	//construction and deconstruction
	ScintillaCtrl();
	~ScintillaCtrl();

	void SetScintillaCtrl(HWND wnd);
	void SetLang(int langm, bool clang=false);
	void LoadDefaultState();
	void UpdateColor(TCHAR* field);
	void AutoCompKey(UINT key);
	void CheckTab();
	void CutCopyPaste(UINT key);
	void RestoreDefaults();
	IniCtrl GetIni();
	HWND GetScintillaCtrl();
};