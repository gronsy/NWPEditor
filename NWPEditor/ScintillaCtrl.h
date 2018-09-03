#pragma once
#include "IniCtrl.h"
#include <string>

#define TAB_WIDTH			4
#define MARGIN_PIXEL_WIDTH	16
#define LINE_MOVE_INDEX		1

//Message defines
#define MSG_COPY			100
#define MSG_CUT				101
#define MSG_PASTE			102

class ScintillaCtrl 
{
protected:
	HWND m_scintilla_ctrl;
	IniCtrl m_ini;
	int m_indent;
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
	void UpdateFont();
	void AutoCompKey(int wordLength)const;
	void CheckTab()const;
	void CutCopyPaste(int msg)const;
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
	void SavePosition()const;
	IniCtrl GetIni();
	HWND GetScintillaCtrl();
};