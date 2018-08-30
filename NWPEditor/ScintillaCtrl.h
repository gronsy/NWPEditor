#pragma once
#include "IniCtrl.h"
#include <string>

#define TAB_WIDTH	4

class ScintillaCtrl 
{
protected:
	HWND scintillaCtrl;
	IniCtrl ini;
	int indent;
protected:
	void SetUpEditor();
	void SetAStyle(int style, COLORREF fore, COLORREF back=RGB(255,255,255), int size=NULL, const std::string& face="")const;
	LRESULT SendEditor(int msg, WPARAM wparam, LPARAM lparam = NULL) const;
public:
	//construction and deconstruction
	ScintillaCtrl();
	~ScintillaCtrl();

	void SetScintillaCtrl(HWND wnd);
	void SetLang(int langm, bool clang=false);
	void LoadDefaultState();
	void UpdateColor(const std::wstring& field);
	void AutoCompKey(int wordLength)const;
	void CheckTab()const;
	void CutCopyPaste(UINT key)const;
	void RestoreDefaults();
	void Undo()const;
	void LoadFromFile(const std::string& data, int bytesRead)const;
	void SetUpFOEditor()const;
	bool EditorIsEmpty();
	void ClearEditor()const;
	void SaveFile(const CString& path);
	void AddIndent();
	void RmIndent();
	void Indent();
	IniCtrl GetIni();
	HWND GetScintillaCtrl();
};