#pragma once
#include "IniCtrl.h"
#include "RegexHandler.h"
#include <string>
#include <vector>
#include <regex>

#define TAB_WIDTH			4
#define PRINT_OVERFLOW		7
#define MARGIN_PIXEL_WIDTH	16
#define PRINTING_LINE_FIT	30

//Message defines
#define MSG_COPY			100
#define MSG_CUT				101
#define MSG_PASTE			102

struct Sci_Print_Info
{
	int lines_printed, text_height, lines_per_page;
	bool initialised;
	Sci_Rectangle rect;
	Sci_RangeToFormat range;
};

class ScintillaCtrl
{
protected:
	HWND m_scintilla_ctrl;
	IniCtrl m_ini;
	Sci_Print_Info m_print_info;
	int m_indent;
protected:
	void SetUpEditor();
	void SetAStyle(int style, COLORREF fore, COLORREF back = RGB(255, 255, 255), int size = NULL, const std::wstring& face = L"")const;
	LRESULT SendEditor(int msg, WPARAM wparam, LPARAM lparam = NULL) const;
	int GetCurrentLineNumber();
public:
	ScintillaCtrl();
	~ScintillaCtrl();

	void SetScintillaCtrl(HWND wnd);
	void SetLang(int langm, bool clang = false);
	void LoadDefaultState();
	void UpdateColor(const std::wstring& field);
	void UpdateFont();
	void AutoCompKey(int wordLength)const;
	void CheckTab()const;
	void CutCopyPaste(int msg)const;
	void RestoreDefaults();
	void Undo()const;
	void LoadFromFile(const std::string& data, int bytesRead);
	void SetUpFOEditor()const;
	bool EditorIsEmpty();
	void ClearEditor()const;
	void SaveFile(const CString& path);
	void AddIndent();
	void RmIndent();
	void Indent();
	void SavePosition()const;
	void PreparePrinting(CDC* pDC, CPrintInfo* pInfo);
	void SetUpPrintInfo(CDC* pDC);
	void Print(CDC* pDC, int page);
	void RmInit();
	IniCtrl GetIni()const;
	HWND GetScintillaCtrl()const;
	void GiveBookmarkInfo(const std::wstring& filePath, const std::wstring& bookmarkName);
	void LoadBookmarks(CMenu* menu, const std::wstring& fileName);
	std::string GetAllDocumentText();
	void RenameVariableOrFunction(const CString& renameTo, int language);
};