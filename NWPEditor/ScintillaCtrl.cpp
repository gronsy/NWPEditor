#include "ScintillaCtrl.h"
#include "stdafx.h"
#include "ChildView.h"

//construction and deconstruction
ScintillaCtrl::ScintillaCtrl() {}

ScintillaCtrl::~ScintillaCtrl() {}

//general methods implementation(public)
void ScintillaCtrl::setScintillaCtrl(HWND wnd) {scintillaCtrl = wnd;}
HWND ScintillaCtrl::getScintillaCtrl() { return scintillaCtrl; }

LRESULT ScintillaCtrl::SendEditor(int msg, WPARAM wparam, LPARAM lparam) {
	return ::SendMessage(scintillaCtrl, msg, wparam, lparam);
}

void ScintillaCtrl::setLang(int lex, bool clang) {
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
		break;
	case SCLEX_NULL:
		SendEditor(SCI_SETLEXER, SCLEX_NULL);
	}

	SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(ini.GetKeywords()));
}