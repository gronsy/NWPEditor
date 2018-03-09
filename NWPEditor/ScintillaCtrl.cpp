#include "ScintillaCtrl.h"
#include "stdafx.h"
#include "ChildView.h"

void ScintillaCtrl::setScintillaCtrl(HWND wnd) {scintillaCtrl = wnd;}
HWND ScintillaCtrl::getScintillaCtrl() { return scintillaCtrl; }

LRESULT ScintillaCtrl::SendEditor(int msg, WPARAM wparam, LPARAM lparam) {
	return ::SendMessage(scintillaCtrl, msg, wparam, lparam);
}

void ScintillaCtrl::setLang(int lex, bool clang=false) {
	switch (lex) {
	case CPPLANG:
		SendEditor(SCI_SETLEXER, SCLEX_CPP, NULL);
		if (clang) {
			SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(c_keywords));
			break;
		}
		SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(cpp_keywords));
		break;
	case PYLANG:
		SendEditor(SCI_SETLEXER, SCLEX_PYTHON, NULL);
		SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(py_keywords));
		break;
	case PLAIN:
		SendEditor(SCI_SETLEXER, SCLEX_NULL, NULL);
		SendEditor(SCI_SETKEYWORDS, NULL, NULL);
	}
}