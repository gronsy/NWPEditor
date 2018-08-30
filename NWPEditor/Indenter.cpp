#include "stdafx.h"
#include "Indenter.h"

void Indenter::AddIndent()
{
	++indent;
}

void Indenter::RmIndent()
{
	--indent;
}

void Indenter::Indent(const HWND scintilla)
{
	for (int i = 0; i < indent; ++i)
		::SendMessage(scintilla, WM_KEYDOWN, VK_TAB, NULL);
}