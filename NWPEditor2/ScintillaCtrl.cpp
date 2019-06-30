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
}

HWND ScintillaCtrl::GetScintillaCtrl() const { return m_scintilla_ctrl; }
IniCtrl ScintillaCtrl::GetIni() const { return m_ini; }
std::vector<std::string> ScintillaCtrl::GetFunctions() const { return m_functions; }


LRESULT ScintillaCtrl::SendEditor(int msg, WPARAM wparam, LPARAM lparam/*=NULL*/) const
{
	return ::SendMessage(m_scintilla_ctrl, msg, wparam, lparam);
}

void ScintillaCtrl::SetAStyle(int style, COLORREF fore,
	COLORREF back/*=RGB(255,255,255)*/, int size/*=NULL*/, const std::wstring& face/*=NULL*/) const
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

int ScintillaCtrl::GetCurrentLine()
{
	int position = SendEditor(SCI_GETCURRENTPOS, NULL);

	return SendEditor(SCI_LINEFROMPOSITION, position);
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
	UpdateFont();
	SendEditor(SCI_SETCARETFORE, RGB(0, 0, 0));
	SendEditor(SCI_SETSELBACK, TRUE, m_ini.GetColor(_T("selection")));
}

void ScintillaCtrl::UpdateColor(const std::wstring& field)
{
	if (field == _T("comment"))
	{
		SetAStyle(SCE_C_COMMENT, m_ini.GetColor(field));
		SetAStyle(SCE_C_COMMENTLINE, m_ini.GetColor(field));
		SetAStyle(SCE_C_COMMENTDOC, m_ini.GetColor(field));
	}
	else if (field == _T("string"))
	{
		SetAStyle(SCE_C_STRING, m_ini.GetColor(field));
		SetAStyle(SCE_C_CHARACTER, m_ini.GetColor(field));
	}
	else if (field == _T("number")) SetAStyle(SCE_C_NUMBER, m_ini.GetColor(field));
	else if (field == _T("uuid"))SetAStyle(SCE_C_UUID, m_ini.GetColor(field));
	else if (field == _T("operators"))SetAStyle(SCE_C_OPERATOR, m_ini.GetColor(field));
	else if (field == _T("preprocessor"))SetAStyle(SCE_C_PREPROCESSOR, m_ini.GetColor(field));
	else if (field == _T("keywords"))SetAStyle(SCE_C_WORD, m_ini.GetColor(field));
	else if (field == _T("selection"))SendEditor(SCI_SETSELBACK, TRUE, m_ini.GetColor(field));
}

void ScintillaCtrl::UpdateFont()
{
	LOGFONT lf = m_ini.GetFontProps();
	SetAStyle(STYLE_DEFAULT, RGB(0, 0, 0), RGB(255, 255, 255), lf.lfHeight, lf.lfFaceName);
	SendEditor(SCI_STYLESETSIZE, STYLE_DEFAULT, lf.lfHeight);
	SendEditor(SCI_STYLESETITALIC, STYLE_DEFAULT, lf.lfItalic ? true : false);
	SendEditor(SCI_STYLESETBOLD, STYLE_DEFAULT, lf.lfWeight > FW_NORMAL ? true : false);
	SendEditor(SCI_STYLESETUNDERLINE, STYLE_DEFAULT, lf.lfUnderline ? true : false);

	SendEditor(SCI_STYLECLEARALL, NULL);
}

void ScintillaCtrl::AutoCompKey(int word_length)const
{
	SendEditor(SCI_AUTOCSETAUTOHIDE, true);
	SendEditor(SCI_AUTOCSHOW, word_length - 1, (LPARAM)(LPSTR)m_ini.GetKeywords().c_str());
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

void ScintillaCtrl::LoadFromFile(const std::string& data, int bytes_read)
{
	SendEditor(SCI_ADDTEXT, bytes_read, reinterpret_cast<LPARAM>(data.c_str()));
	//CPP Regex: .*(::)?\(.*\)\{(.*\}|;)?\n?
	//Python Regex: def.*\(.*\):\n?
	const std::regex functionExpression(".*");
	std::smatch match;
	m_functions.clear();

	if(std::regex_search(data, match, functionExpression))
	{
		std::string functionName;
		std::copy(std::find(data.begin(), data.end(), ' ')+1,
			std::find(data.begin(), data.end(), '('), back_inserter(functionName));
		m_functions.push_back(functionName);
	}
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
	char* buffer = new char[doc_size + 1];
	SendEditor(SCI_GETTEXT, doc_size, reinterpret_cast<LPARAM>(buffer));

	CFile save_file;
	save_file.Open(path, CFile::modeWrite | CFile::modeCreate);
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
	SendEditor(SCI_SETINDENT, m_indent * TAB_WIDTH);
	int current_line = SendEditor(SCI_GETCURRENTPOS, NULL);
	current_line = SendEditor(SCI_LINEFROMPOSITION, current_line);

	SendEditor(SCI_SETTABINDENTS, true);
	SendEditor(SCI_SETLINEINDENTATION, current_line, m_indent * TAB_WIDTH);
	SendEditor(SCI_ADDTABSTOP, current_line, m_indent * TAB_WIDTH);
}

void ScintillaCtrl::PreparePrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (!(m_print_info.initialised))
	{
		m_print_info.rect.left = pInfo->m_rectDraw.left;
		m_print_info.rect.right = pInfo->m_rectDraw.right;
		m_print_info.rect.top = pInfo->m_rectDraw.top;
		m_print_info.rect.bottom = pInfo->m_rectDraw.bottom;
		m_print_info.range.chrg.cpMin = 0;
		m_print_info.range.chrg.cpMax = SendEditor(SCI_GETLENGTH, NULL);

		//m_print_info.text_height = SendEditor(SCI_TEXTHEIGHT, 0);
		m_print_info.text_height = m_ini.GetFontHeight();
		m_print_info.text_height = MulDiv(m_print_info.text_height, pDC->GetDeviceCaps(LOGPIXELSY), 72);
		m_print_info.lines_per_page = m_print_info.rect.bottom / m_print_info.text_height - PRINT_OVERFLOW;

		unsigned pages = SendEditor(SCI_GETLINECOUNT, NULL);
		pages *= m_print_info.text_height;
		pages /= m_print_info.rect.bottom;
		++pages;
		if (m_print_info.lines_per_page * pages < SendEditor(SCI_GETLINECOUNT, NULL))
			++pages;
		pInfo->SetMaxPage(pages);

		m_print_info.initialised = true;
	}
}

void ScintillaCtrl::SetUpPrintInfo(CDC* pDC)
{
	m_print_info.range.hdc = pDC->m_hDC;
	m_print_info.range.hdcTarget = pDC->m_hDC;
	m_print_info.range.rc = m_print_info.rect;
	m_print_info.range.rcPage = m_print_info.rect;

	SendEditor(SCI_SETPRINTCOLOURMODE, SC_PRINT_NORMAL);
	SendEditor(SCI_FORMATRANGE, false, reinterpret_cast<LPARAM>(&m_print_info.range));
}

void ScintillaCtrl::Print(CDC* pDC, int page)
{
	int dist = 1;
	bool page_transition = true;
	LOGFONT lf = m_ini.GetFontProps(true);
	SendEditor(SCI_GOTOPOS, 0);

	CFont font;
	font.CreateFont(-m_print_info.text_height, lf.lfWidth, lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, lf.lfClipPrecision,
		lf.lfQuality, lf.lfPitchAndFamily, lf.lfFaceName);
	pDC->SetTextAlign(TA_TOP);
	CFont* old = pDC->SelectObject(&font);
	m_print_info.lines_printed = 0;
	int cur_line = page * m_print_info.lines_per_page - m_print_info.lines_per_page;

	while (m_print_info.lines_printed < m_print_info.lines_per_page && !EditorIsEmpty())
	{
		int line_length = SendEditor(SCI_LINELENGTH, cur_line);

		char* buffer = new char[line_length + 1];
		SendEditor(SCI_GETLINE, cur_line, reinterpret_cast<LPARAM>(buffer));

		buffer[line_length] = '\0';

		pDC->TextOut(m_print_info.rect.left + 50, pDC->GetTextExtent(CString(buffer)).cy * dist, CString(buffer));

		++m_print_info.lines_printed;
		++cur_line;
		++dist;
		delete[] buffer;
	}

	pDC->SelectObject(old);
}

void ScintillaCtrl::RmInit() { m_print_info.initialised = false; }

void ScintillaCtrl::GiveBookmarkInfo(const std::wstring& filePath, const std::wstring& bookmarkName)
{
	auto line = GetCurrentLine();

	m_ini.AddBookmarkEntry(bookmarkName, filePath, line);
}

void ScintillaCtrl::LoadBookmarks(CMenu* menu, const std::wstring& fileName)
{
	//TODO: Finish implementing bookmarks
	auto bookmarks = m_ini.GetBookmarks(fileName);
	for (auto bookmark : bookmarks) {}
	//menu->AppendMenuW(MF_STRING | MF_SEPARATOR, NULL, bookmark.GetBookmarkName().c_str());
}

void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)
{
	const int line = GetCurrentLine();
	const int line_length = SendEditor(SCI_LINELENGTH, line);
	char* buffer = new char[line_length];

	SendEditor(SCI_GETLINE, line, reinterpret_cast<LPARAM>(buffer));

	std::regex regex("");
	std::smatch match;
	const auto line_count = SendEditor(SCI_GETLINECOUNT, NULL);
	for (int current_line = 1; current_line <= line_count; ++current_line)
	{
		const int current_line_length = SendEditor(SCI_LINELENGTH, current_line);
		char* current_line_buffer = new char[current_line_length];
		SendEditor(SCI_GETLINE, current_line, reinterpret_cast<LPARAM>(current_line_buffer));

		std::string tmp(current_line_buffer);
		std::regex_search(tmp, match, regex);



		delete[] current_line_buffer;
	}
}