#include "stdafx.h"
#include "ScintillaCtrl.h"


//construction and deconstruction
ScintillaCtrl::ScintillaCtrl()
{
	m_indent = 0;
	m_print_info.initialised = false;
}

ScintillaCtrl::~ScintillaCtrl() {}

//general methods implementation(public)
void ScintillaCtrl::SetScintillaCtrl(HWND wnd)
{
	m_scintilla_ctrl = wnd;
	DisableShortcuts();
}

HWND ScintillaCtrl::GetScintillaCtrl() { return m_scintilla_ctrl; }
IniCtrl ScintillaCtrl::GetIni() { return m_ini; }

LRESULT ScintillaCtrl::SendEditor(int msg, WPARAM wparam, LPARAM lparam/*=NULL*/) const
{
	return ::SendMessage(m_scintilla_ctrl, msg, wparam, lparam);
}

void ScintillaCtrl::SetAStyle(int style, COLORREF fore, 
	COLORREF back/*=RGB(255,255,255)*/, int size/*=NULL*/, const std::string& face/*=NULL*/) const
{
	SendEditor(SCI_STYLESETFORE, style, fore);
	SendEditor(SCI_STYLESETBACK, style, back);

	if (size >= 1)
		SendEditor(SCI_STYLESETSIZE, style, size);
	else
		SendEditor(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(face.c_str()));
}

void ScintillaCtrl::SetLang(int lex, bool clang/*=false*/) 
{
	SendEditor(SCI_SETLEXER, lex, NULL);
	m_ini.SendIni(lex, clang);
	SetUpEditor();
}

void ScintillaCtrl::SetUpEditor()
{
	SendEditor(SCI_SETKEYWORDS, NULL, reinterpret_cast<LPARAM>(m_ini.GetKeywords().c_str()));
	
	SetAStyle(SCE_C_COMMENT, m_ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_COMMENTLINE, m_ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_COMMENTDOC, m_ini.GetColor(_T("comment")));
	SetAStyle(SCE_C_NUMBER, m_ini.GetColor(_T("number")));
	SetAStyle(SCE_C_STRING, m_ini.GetColor(_T("string")));
	SetAStyle(SCE_C_CHARACTER, m_ini.GetColor(_T("string")));
	SetAStyle(SCE_C_UUID, m_ini.GetColor(_T("uuid")));
	SetAStyle(SCE_C_OPERATOR, m_ini.GetColor(_T("operators")));
	SetAStyle(SCE_C_PREPROCESSOR, m_ini.GetColor(_T("preprocessor")));
	SetAStyle(SCE_C_WORD, m_ini.GetColor(_T("keywords")));
}

void ScintillaCtrl::LoadDefaultState()
{
	SendEditor(SCI_SETLEXER, SCLEX_NULL);
	SendEditor(SCI_SETTABWIDTH, TAB_WIDTH);
	SetAStyle(STYLE_DEFAULT, RGB(0, 0, 0), RGB(255, 255, 255), 10, m_ini.GetFont());
	SendEditor(SCI_SETCARETFORE, RGB(0, 0, 0));
	SendEditor(SCI_STYLECLEARALL, NULL);
	SendEditor(SCI_SETSELBACK, TRUE, m_ini.GetColor(_T("selection")));
}

void ScintillaCtrl::DisableShortcuts()
{
	SendEditor(SCI_CLEARCMDKEY, VK_CONTROL | 0x46);
}


void ScintillaCtrl::UpdateColor(const std::wstring& field)
{
	if (field==_T("comment"))
	{
		SetAStyle(SCE_C_COMMENT, m_ini.GetColor(field));
		SetAStyle(SCE_C_COMMENTLINE, m_ini.GetColor(field));
		SetAStyle(SCE_C_COMMENTDOC, m_ini.GetColor(field));
	}else if (field==_T("string"))
	{
		SetAStyle(SCE_C_STRING, m_ini.GetColor(field));
		SetAStyle(SCE_C_CHARACTER, m_ini.GetColor(field));
	}
	else if (field==_T("number")) SetAStyle(SCE_C_NUMBER, m_ini.GetColor(field));
	else if (field==_T("uuid"))SetAStyle(SCE_C_UUID, m_ini.GetColor(field));
	else if (field==_T("operators"))SetAStyle(SCE_C_OPERATOR, m_ini.GetColor(field));
	else if (field==_T("preprocessor"))SetAStyle(SCE_C_PREPROCESSOR, m_ini.GetColor(field));
	else if (field==_T("keywords"))SetAStyle(SCE_C_WORD, m_ini.GetColor(field));
	else if (field == _T("selection"))SendEditor(SCI_SETSELBACK,TRUE, m_ini.GetColor(field));
}

void ScintillaCtrl::UpdateFont()
{
	SetAStyle(STYLE_DEFAULT, RGB(0, 0, 0), RGB(255, 255, 255), 10, m_ini.GetFont());
}

void ScintillaCtrl::AutoCompKey(int word_length)const
{
	SendEditor(SCI_AUTOCSETAUTOHIDE, true);
	SendEditor(SCI_AUTOCSHOW, word_length-1, (LPARAM)(LPSTR)m_ini.GetKeywords().c_str());
	SendEditor(SCI_AUTOCSETIGNORECASE, true);
	SendEditor(SCI_AUTOCSETORDER, SC_ORDER_PERFORMSORT);
}

void ScintillaCtrl::CheckTab()const
{
	if (SendEditor(SCI_AUTOCACTIVE, NULL))
		SendEditor(SCI_AUTOCCOMPLETE, NULL);
}

void ScintillaCtrl::CutCopyPaste(int msg)const
{
	switch (msg) {
	case MSG_COPY: SendEditor(SCI_COPY, NULL); return;
	case MSG_PASTE: SendEditor(SCI_PASTE, NULL); return;
	case MSG_CUT: SendEditor(SCI_CUT, NULL);
	}
}

void ScintillaCtrl::RestoreDefaults()
{
	m_ini.WriteDefaultColours();
	m_ini.WriteDefaultKeywords();
	m_ini.WriteDefaultFont();
}

void ScintillaCtrl::Undo()const { SendEditor(SCI_UNDO, NULL); }

void ScintillaCtrl::LoadFromFile(const std::string& data, int bytes_read)const
{
	SendEditor(SCI_ADDTEXT, bytes_read, reinterpret_cast<LPARAM>(data.c_str()));
}

void ScintillaCtrl::SetUpFOEditor() const
{
	SavePosition();
	SendEditor(SCI_GOTOPOS, 0);
}

void ScintillaCtrl::SavePosition() const
{
	SendEditor(SCI_SETUNDOCOLLECTION, 1);
	SendEditor(SCI_SETSAVEPOINT, NULL);
}


//Returns true if editor is empty, false if it isn't empty.
bool ScintillaCtrl::EditorIsEmpty()
{
	char chk_buffer[2];
	chk_buffer[0] = '\0';
	SendEditor(SCI_GETTEXT, 2, reinterpret_cast<LPARAM>(chk_buffer));

	if (chk_buffer[0]) return false;

	return true;
}

void ScintillaCtrl::ClearEditor()const
{
	SendEditor(SCI_CLEARALL, NULL);
}

void ScintillaCtrl::SaveFile(const CString& path)
{
	SavePosition();

	int doc_size = SendEditor(SCI_GETLENGTH, NULL);
	char* buffer=new char[doc_size+1];
	SendEditor(SCI_GETTEXT, doc_size, reinterpret_cast<LPARAM>(buffer));

	CFile save_file;
	save_file.Open(path, CFile::modeWrite|CFile::modeCreate);
	save_file.Write(buffer, doc_size);
	save_file.Close();
	delete[] buffer;
}

void ScintillaCtrl::AddIndent()
{
	++m_indent;
}

void ScintillaCtrl::RmIndent()
{
	if (!m_indent)	
		return;

	--m_indent;
}

void ScintillaCtrl::Indent()
{
	SendEditor(SCI_SETINDENT, m_indent*TAB_WIDTH);
	SendEditor(SCI_SETTABINDENTS, false);
	int current_line = SendEditor(SCI_GETCURRENTPOS, NULL);
	current_line = SendEditor(SCI_LINEFROMPOSITION, current_line)+ LINE_MOVE_INDEX;
	SendEditor(SCI_SETLINEINDENTATION, current_line+1, m_indent);
}

void ScintillaCtrl::PreparePrinting(CDC* pDC,CPrintInfo* pInfo)
{
	if (!(m_print_info.initialised))
	{
		m_print_info.rect.left = pInfo->m_rectDraw.left;
		m_print_info.rect.right = pInfo->m_rectDraw.right;
		m_print_info.rect.top = pInfo->m_rectDraw.top;
		m_print_info.rect.bottom = pInfo->m_rectDraw.bottom;
		m_print_info.range.chrg.cpMin = 0;
		m_print_info.range.chrg.cpMax = SendEditor(SCI_GETLENGTH, NULL);

	
		m_print_info.line_height = SendEditor(SCI_TEXTHEIGHT, 0);
		m_print_info.line_height = MulDiv(m_print_info.line_height, pDC->GetDeviceCaps(LOGPIXELSY), 72);
		m_print_info.lines_per_page = m_print_info.rect.bottom/m_print_info.line_height;
		unsigned pages = SendEditor(SCI_GETLINECOUNT, NULL);
		pages *= m_print_info.line_height;
		pages /= m_print_info.rect.bottom;
		++pages;
		if (m_print_info.lines_per_page*pages < SendEditor(SCI_GETLINECOUNT, NULL))
			++pages;
		pInfo->SetMaxPage(pages);

		m_print_info.initialised = true;
	}
}

void ScintillaCtrl::SetUpPrintInfo(CDC* pDC)
{
	m_print_info.range.hdc = pDC;
	m_print_info.range.hdcTarget = pDC;
	m_print_info.range.rc = m_print_info.rect;
	m_print_info.range.rcPage = m_print_info.rect;

	SendEditor(SCI_SETPRINTCOLOURMODE, SC_PRINT_NORMAL);
	SendEditor(SCI_FORMATRANGE, false, reinterpret_cast<LPARAM>(&m_print_info));
}

void ScintillaCtrl::Print(CDC* pDC, int page)
{
	//TODO: fix character overlaping
	//TODO: fix line going over paper edge
	int dist = m_print_info.line_height;
	bool page_transition = true;
	SendEditor(SCI_GOTOPOS, 0);
	pDC->SetTextAlign(TA_TOP);
	m_print_info.lines_printed = 0;
	int cur_line = page * m_print_info.lines_per_page - m_print_info.lines_per_page;

	while(m_print_info.lines_printed<= m_print_info.lines_per_page && !EditorIsEmpty())
	{
		int line_length = SendEditor(SCI_LINELENGTH, cur_line);
		
		char *buffer = new char[line_length+1];
		SendEditor(SCI_GETLINE, cur_line, reinterpret_cast<LPARAM>(buffer));

		buffer[line_length] = '\0';
		
		pDC->TextOut(m_print_info.rect.left+50, dist, CString(buffer));


		++m_print_info.lines_printed;
		++cur_line;
		dist += m_print_info.line_height;
		delete[] buffer;
	}
}

void ScintillaCtrl::RmInit() { m_print_info.initialised = false; }