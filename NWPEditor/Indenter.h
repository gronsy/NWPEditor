#pragma once

class Indenter
{
protected:
	int indent;
	void AddIndent();
	void RmIndent();
public:
	void Indent(const HWND scintilla);
};