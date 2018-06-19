#include "ScintillaCtrl.h"
#include "stdafx.h"
#include "ChildView.h"

//construction and deconstruction
ScintillaCtrl::ScintillaCtrl() {}

ScintillaCtrl::~ScintillaCtrl() {}

//general methods implementation(public)
void ScintillaCtrl::SetScintillaCtrl(HWND wnd) {scintillaCtrl = wnd;}
HWND ScintillaCtrl::GetScintillaCtrl() { return scintillaCtrl; }

LRESULT ScintillaCtrl::SendEditor(int msg, WPARAM wparam, LPARAM lparam) {
	return ::SendMessage(scintillaCtrl, msg, wparam, lparam);
}

void ScintillaCtrl::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char *face)
{
	SendEditor(SCI_STYLESETFORE, style, fore);
	SendEditor(SCI_STYLESETBACK, style, back);

	if (size >= 1)
		SendEditor(SCI_STYLESETSIZE, style, size);
	else
		SendEditor(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(face));
}

void ScintillaCtrl::SetLang(int lex, bool clang) {
	switch (lex) {
	case SCLEX_CPP:
		SendEditor(SCI_SETLEXER, SCLEX_CPP, NULL);
		if (clang) {
			ini.SendIni(SCLEX_CPP, true);
			break;
		}else
			ini.SendIni(SCLEX_CPP);
		break;
	case SCLEX_PYTHON:
		SendEditor(SCI_SETLEXER, SCLEX_PYTHON, NULL);
		ini.SendIni(SCLEX_PYTHON);
		break;
	case SCLEX_NULL:
		SendEditor(SCI_SETLEXER, SCLEX_NULL);
	}

	SetUpEditor();
}

void ScintillaCtrl::SetUpEditor()
{
	SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(ini.GetKeywords()));

	//Background parameter is set by default value (can be seen in ScintillaCtrl.h)
	SetAStyle(SCE_C_COMMENT, ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_COMMENTLINE, ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_COMMENTDOC, ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_NUMBER, ini.GetColor(_T("number")));
	SetAStyle(SCE_C_STRING, ini.GetColor(_T("strings")));
	SetAStyle(SCE_C_CHARACTER, ini.GetColor(_T("string")));
	SetAStyle(SCE_C_UUID, ini.GetColor(_T("uuid")));
	SetAStyle(SCE_C_OPERATOR, ini.GetColor(_T("variables")));
	SetAStyle(SCE_C_PREPROCESSOR, ini.GetColor(_T("variables")));
	SetAStyle(SCE_C_WORD, ini.GetColor(_T("variables")));
}

void ScintillaCtrl::LoadDefaultState()
{
	SendEditor(SCI_SETLEXER, SCLEX_NULL);
	SendEditor(SCI_SETTABWIDTH, 4);
	SetAStyle(STYLE_DEFAULT, RGB(0, 0, 0), RGB(255, 255, 255), 10, "Arial");
	SendEditor(SCI_SETCARETFORE, RGB(0, 0, 0));
	SendEditor(SCI_STYLECLEARALL, NULL);
	SendEditor(SCI_SETSELBACK, TRUE, ini.GetColor(_T("selection")));
}