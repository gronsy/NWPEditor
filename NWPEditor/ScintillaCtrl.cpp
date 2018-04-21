#include "ScintillaCtrl.h"
#include "stdafx.h"
#include "ChildView.h"

//construction and deconstruction
ScintillaCtrl::ScintillaCtrl() {
	ini.loadKeywords();
	ini.loadColours();
}

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
			SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(c_keywords));
			break;
		}
		SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(cpp_keywords));
		break;
	case SCLEX_PYTHON:
		SendEditor(SCI_SETLEXER, SCLEX_PYTHON, NULL);
		SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(py_keywords));
		break;
	case SCLEX_NULL:
		SendEditor(SCI_SETLEXER, SCLEX_NULL);
		SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(""));
	}
}