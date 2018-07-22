#include "ScintillaCtrl.h"
#include "stdafx.h"
#include "ChildView.h"

//construction and deconstruction
ScintillaCtrl::ScintillaCtrl() {}

ScintillaCtrl::~ScintillaCtrl() {}

//general methods implementation(public)
void ScintillaCtrl::SetScintillaCtrl(HWND wnd) {scintillaCtrl = wnd;}
HWND ScintillaCtrl::GetScintillaCtrl() { return scintillaCtrl; }
IniCtrl ScintillaCtrl::GetIni() { return ini; }

LRESULT ScintillaCtrl::SendEditor(int msg, WPARAM wparam, LPARAM lparam/*=NULL*/)
{
	return ::SendMessage(scintillaCtrl, msg, wparam, lparam);
}

void ScintillaCtrl::SetAStyle(int style, COLORREF fore, 
	COLORREF back/*=RGB(255,255,255)*/, int size/*=NULL*/, const char *face/*=NULL*/)
{
	SendEditor(SCI_STYLESETFORE, style, fore);
	SendEditor(SCI_STYLESETBACK, style, back);

	if (size >= 1)
		SendEditor(SCI_STYLESETSIZE, style, size);
	else
		SendEditor(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(face));
}

void ScintillaCtrl::SetLang(int lex, bool clang/*=false*/) 
{
	switch (lex) {
	case SCLEX_CPP:
		SendEditor(SCI_SETLEXER, SCLEX_CPP, NULL);
		if (clang) ini.SendIni(SCLEX_CPP, true);
		else ini.SendIni(SCLEX_CPP);
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
	//TODO: Change types of all keywords
	SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(ini.GetKeywords()));
	
	SetAStyle(SCE_C_COMMENT, ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_COMMENTLINE, ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_COMMENTDOC, ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_NUMBER, ini.GetColor(_T("number")));
	SetAStyle(SCE_C_STRING, ini.GetColor(_T("string")));
	SetAStyle(SCE_C_CHARACTER, ini.GetColor(_T("string")));
	SetAStyle(SCE_C_UUID, ini.GetColor(_T("uuid")));
	SetAStyle(SCE_C_OPERATOR, ini.GetColor(_T("operators")));
	SetAStyle(SCE_C_PREPROCESSOR, ini.GetColor(_T("preprocessor")));
	SetAStyle(SCE_C_WORD, ini.GetColor(_T("keywords")));
}

void ScintillaCtrl::LoadDefaultState()
{
	SendEditor(SCI_SETLEXER, SCLEX_NULL);
	SendEditor(SCI_SETTABWIDTH,4);
	SetAStyle(STYLE_DEFAULT, RGB(0, 0, 0), RGB(255, 255, 255), 10, "Arial");
	SendEditor(SCI_SETCARETFORE, RGB(0, 0, 0));
	SendEditor(SCI_STYLECLEARALL, NULL);
	SendEditor(SCI_SETSELBACK, TRUE, ini.GetColor(_T("selection")));
}

void ScintillaCtrl::UpdateColor(TCHAR* field)
{
	if (!wcscmp(field, _T("comment")))
	{
		SetAStyle(SCE_C_COMMENT, ini.GetColor(field));
		SetAStyle(SCE_C_COMMENTLINE, ini.GetColor(field));
		SetAStyle(SCE_C_COMMENTDOC, ini.GetColor(field));
	}else if (!wcscmp(field, _T("string")))
	{
		SetAStyle(SCE_C_STRING, ini.GetColor(field));
		SetAStyle(SCE_C_CHARACTER, ini.GetColor(field));
	}
	else if (!wcscmp(field, _T("number"))) SetAStyle(SCE_C_NUMBER, ini.GetColor(field));
	else if (!wcscmp(field, _T("uuid")))SetAStyle(SCE_C_UUID, ini.GetColor(field));
	else if (!wcscmp(field, _T("operators")))SetAStyle(SCE_C_OPERATOR, ini.GetColor(field));
	else if (!wcscmp(field, _T("preprocessor")))SetAStyle(SCE_C_PREPROCESSOR, ini.GetColor(field));
	else if (!wcscmp(field, _T("keywords")))SetAStyle(SCE_C_WORD, ini.GetColor(field));
}

void ScintillaCtrl::AutoCompKey(UINT key)
{
	SendEditor(SCI_AUTOCSHOW, 1, reinterpret_cast<LPARAM>(ini.GetKeywords()));
	SendEditor(SCI_AUTOCSETIGNORECASE, true);
	SendEditor(SCI_AUTOCSETORDER, SC_ORDER_PERFORMSORT);
}