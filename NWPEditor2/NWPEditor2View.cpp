// NWPEditor2View.cpp : implementation of the CNWPEditor2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "NWPEditor2.h"
#endif

#include "NWPEditor2Doc.h"
#include "NWPEditor2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CNWPEditor2View

IMPLEMENT_DYNCREATE(CNWPEditor2View, CView)

BEGIN_MESSAGE_MAP(CNWPEditor2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNWPEditor2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LANGUAGE_C, &CNWPEditor2View::OnLanguageC)
	ON_COMMAND(ID_LANGUAGE_CPP, &CNWPEditor2View::OnLanguageCpp)
	ON_COMMAND(ID_LANGUAGE_PYTHON, &CNWPEditor2View::OnLanguagePython)
	ON_COMMAND(ID_LANGUAGE_PLAIN, &CNWPEditor2View::OnLanguagePlain)
	ON_COMMAND(ID_SETTINGS_FONTS, &CNWPEditor2View::OnSettingsFonts)
	ON_COMMAND(ID_SETTINGS_COLORS, &CNWPEditor2View::OnSettingsColors)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_UNDO, &CNWPEditor2View::OnEditUndo)
	ON_COMMAND(ID_EDIT_CUT, &CNWPEditor2View::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CNWPEditor2View::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CNWPEditor2View::OnEditPaste)
	ON_COMMAND(ID_FILE_OPEN, &CNWPEditor2View::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CNWPEditor2View::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CNWPEditor2View::OnFileSaveAs)
	ON_COMMAND(ID_FILE_NEW, &CNWPEditor2View::OnFileNew)
	ON_COMMAND(ID_BOOKMARKS_ADDBOOKMARK, &CNWPEditor2View::OnBookmarksAddbookmark)
	ON_COMMAND(ID_EDIT_RENAME, &CNWPEditor2View::OnEditRename)
END_MESSAGE_MAP()

// CNWPEditor2View construction/destruction

CNWPEditor2View::CNWPEditor2View() noexcept
{
	//m_current_lang.curr_lang = SCLEX_NULL;
	//m_current_lang.ext = L"";
	m_buffer_length = 0;
	m_working_file_path = "";
	m_scintlla_default_load = true;
}

CNWPEditor2View::~CNWPEditor2View()
{
}

BOOL CNWPEditor2View::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return CView::PreCreateWindow(cs);
}

// CNWPEditor2View drawing

void CNWPEditor2View::OnDraw(CDC* pDC)
{
	CNWPEditor2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}

int CNWPEditor2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_scintilla_control.SetScintillaCtrl(CreateWindowEx(0, _T("Scintilla"), _T(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN,
		0, 0, 0, 0, *this, (HMENU)101, NULL, NULL));

	return 0;
}

void CNWPEditor2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	::MoveWindow(m_scintilla_control.GetScintillaCtrl(), 0, 0, cx, cy, FALSE);

	if (m_scintlla_default_load)
	{
		m_scintilla_control.LoadDefaultState(m_scintlla_default_load);
		m_scintlla_default_load = false;
	}
}

// CNWPEditor2View printing

void CNWPEditor2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CNWPEditor2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CNWPEditor2View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	m_scintilla_control.SetUpPrintInfo(pDC);
}

void CNWPEditor2View::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	m_scintilla_control.PreparePrinting(pDC, pInfo);
	m_scintilla_control.Print(pDC, pInfo->m_nCurPage);

	CView::OnPrint(pDC, pInfo);
}

void CNWPEditor2View::OnEndPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	pDC->DeleteDC();
	m_scintilla_control.RmInit();
}

void CNWPEditor2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNWPEditor2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CNWPEditor2View diagnostics

#ifdef _DEBUG
void CNWPEditor2View::AssertValid() const
{
	CView::AssertValid();
}

void CNWPEditor2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNWPEditor2Doc* CNWPEditor2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNWPEditor2Doc)));
	return (CNWPEditor2Doc*)m_pDocument;
}
#endif //_DEBUG

// CNWPEditor2View message handlers

void CNWPEditor2View::OnLanguageC()
{
	/*if (m_current_lang.curr_lang != SCLEX_CPP)
		SetCurLang(SCLEX_CPP, true);*/

	CppLanguage* c_language_handler=new CppLanguage(true);
	m_scintilla_control.SetLanguage(c_language_handler);
}

void CNWPEditor2View::OnLanguageCpp()
{
	/*if (m_current_lang.curr_lang != SCLEX_CPP)
		SetCurLang(SCLEX_CPP);*/

	CppLanguage* cpp_language_handler=new CppLanguage();
	m_scintilla_control.SetLanguage(cpp_language_handler);
}

void CNWPEditor2View::OnLanguagePython()
{
	/*if (m_current_lang.curr_lang != SCLEX_PYTHON)
		SetCurLang(SCLEX_PYTHON);*/

	PythonLanguage* python_language_handler=new PythonLanguage();
	m_scintilla_control.SetLanguage(python_language_handler);
}

void CNWPEditor2View::OnLanguagePlain()
{
	/*if (m_current_lang.curr_lang != SCLEX_NULL)
	{
		m_scintilla_control.SetLang(SCLEX_NULL);
		SetCurLang(SCLEX_NULL);
	}*/

	m_scintilla_control.LoadDefaultState();
}

void CNWPEditor2View::OnSettingsFonts()
{
	LOGFONT initial = m_scintilla_control.GetIni().GetFontProps(true);

	CFontDialog fontDlg(&initial, CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS, NULL, this);
	if (fontDlg.DoModal() == IDOK)
	{
		LOGFONT lf;
		fontDlg.GetCurrentFont(&lf);
		m_scintilla_control.GetIni().ChangeFont(lf, fontDlg.GetSize() / 10);
		m_scintilla_control.UpdateFont();
	}
}

void CNWPEditor2View::OnSettingsColors()
{
	COLORREF color;
	ColorPickDlg clrDlg(&color, this);

	if (clrDlg.DoModal() == IDOK)
	{
		if (!clrDlg.GetWriteDefaults())
		{
			m_scintilla_control.GetIni().ChangeColor(color, clrDlg.GetField());
			m_scintilla_control.UpdateColor(clrDlg.GetField());
		}
		else
			m_scintilla_control.RestoreDefaults();
	}
}

BOOL CNWPEditor2View::PreTranslateMessage(MSG* pMsg)
{
	/*if (m_current_lang.curr_lang == SCLEX_NULL)
		goto returnLab;*/

	if (m_scintilla_control.GetCurrentLanguageId() == NULL)
		goto returnLab;

	if (pMsg->message == WM_KEYDOWN)
	{
		char key_char = MapVirtualKeyA(pMsg->wParam, MAPVK_VK_TO_CHAR);
		if (!GetAsyncKeyState(VK_LSHIFT))
			key_char = tolower(key_char);

		if (pMsg->wParam == VK_TAB || pMsg->wParam == VK_RETURN)
		{
			m_scintilla_control.CheckTab();
			m_buffer_length = 0;
		}

		if (pMsg->wParam == VK_SPACE)
		{
			m_buffer_length = 0;
			goto returnLab;
		}

		if (pMsg->wParam<VK_LWIN && pMsg->wParam>VK_HELP || (pMsg->wParam > VK_SLEEP))
		{
			++m_buffer_length;
			m_scintilla_control.AutoCompKey(m_buffer_length);
		}
		else if (pMsg->wParam == VK_BACK && m_buffer_length)
		{
			--m_buffer_length;
			m_scintilla_control.AutoCompKey(m_buffer_length);
		}

		/*if ((pMsg->wParam == VK_OEM_4 && m_current_lang.curr_lang == SCLEX_CPP)
			|| (pMsg->wParam == VK_OEM_1 && m_current_lang.curr_lang == SCLEX_PYTHON) && GetAsyncKeyState(VK_LSHIFT))
			m_scintilla_control.AddIndent();*/

		if ((pMsg->wParam == VK_OEM_4 && m_scintilla_control.GetCurrentLanguageId() == SCLEX_CPP)
			|| (pMsg->wParam == VK_OEM_1 && m_scintilla_control.GetCurrentLanguageId() == SCLEX_PYTHON) && GetAsyncKeyState(VK_LSHIFT))
			m_scintilla_control.AddIndent();

		/*if (pMsg->wParam == VK_OEM_6 && m_language_in_use.language_id == SCLEX_CPP && GetAsyncKeyState(VK_LSHIFT))
			m_scintilla_control.RmIndent();*/

		if (pMsg->wParam == VK_OEM_6 && m_scintilla_control.GetCurrentLanguageId() == SCLEX_CPP && GetAsyncKeyState(VK_LSHIFT))
			m_scintilla_control.RmIndent();
	}

	if (pMsg->wParam == VK_RETURN && pMsg->message == WM_KEYUP)
		m_scintilla_control.Indent();

returnLab:
	m_scintilla_control.SavePosition();

	return CView::PreTranslateMessage(pMsg);
}

void CNWPEditor2View::OnEditUndo()
{
	m_scintilla_control.Undo();
}

void CNWPEditor2View::OnEditCut()
{
	m_scintilla_control.CutCopyPaste(MSG_CUT);
}

void CNWPEditor2View::OnEditCopy()
{
	m_scintilla_control.CutCopyPaste(MSG_COPY);
}

void CNWPEditor2View::OnEditPaste()
{
	m_scintilla_control.CutCopyPaste(MSG_PASTE);
}

bool CNWPEditor2View::ClearEditorWarning()
{
	CString msg, title;
	msg.LoadString(IDS_FOPEN_EMPTYMSG);
	title.LoadString(IDS_FOPEN_EMPTYTITLE);
	if (MessageBox(msg, title, MB_YESNO) == IDYES)
		return true;

	return false;
}

void CNWPEditor2View::OnFileOpen()
{
	CFileDialog file_dlg(TRUE, m_scintilla_control.GetCurrentLanguageExtension().c_str());
	file_dlg.DoModal();

	CFile file;
	m_working_file_path = file_dlg.GetPathName();
	if (m_working_file_path == _T(""))
		return;

	/*auto menu = CreateBookmarkMenu();

	m_scintilla_control.LoadBookmarks(menu, std::wstring(m_working_file_path));*/
	if (file.Open(m_working_file_path, file.modeRead))
	{
		std::wstring extension = file_dlg.GetFileExt();

		if (extension == _T("c"))
			OnLanguageC();
		else if (extension == _T("cpp"))
			OnLanguageCpp();
		else if (extension == _T("py"))
			OnLanguagePython();
		else
			OnLanguagePlain();
		if (extension == _T("h"))
			OnLanguageC();

		if (!m_scintilla_control.EditorIsEmpty()) {
			if (ClearEditorWarning())
				m_scintilla_control.ClearEditor();
			else
				return;
		}

		char buffer[256];
		int bytes_read;
		while (bytes_read = file.Read(buffer, sizeof buffer))
		{
			std::string buffer_conv(buffer);
			m_scintilla_control.LoadFromFile(buffer, bytes_read);
		}

		m_scintilla_control.SetWorkingFile(m_working_file_path);
		m_scintilla_control.SetUpFOEditor();
	}

	//menu->DestroyMenu();
	file.Close();
}

void CNWPEditor2View::OnFileSave()
{
	if (m_working_file_path != _T(""))
		m_scintilla_control.SaveFile(m_working_file_path);
	else
		OnFileSaveAs();
}

void CNWPEditor2View::OnFileSaveAs()
{
	CFileDialog save_dlg(FALSE, _T(""), NULL, OFN_OVERWRITEPROMPT);
	save_dlg.DoModal();

	if (m_working_file_path == _T("") || m_working_file_path != save_dlg.GetPathName())
		m_working_file_path = save_dlg.GetPathName();

	if (m_working_file_path != _T(""))
		m_scintilla_control.SaveFile(m_working_file_path);
}

void CNWPEditor2View::OnFileNew()
{
	if (!m_scintilla_control.EditorIsEmpty() && ClearEditorWarning())
	{
		m_scintilla_control.ClearEditor();
		m_working_file_path = _T("");
	}
}

void CNWPEditor2View::OnBookmarksAddbookmark()
{
	BookmarkAddDlg bmAddDlg;

	if (bmAddDlg.DoModal() == IDOK)
		m_scintilla_control.GiveBookmarkInfo(std::wstring(m_working_file_path), bmAddDlg.GetBmName());

	auto menu = CreateBookmarkMenu();
	m_scintilla_control.LoadBookmarks(menu, std::wstring(m_working_file_path));
}

CMenu* CNWPEditor2View::CreateBookmarkMenu()
{
	CMenu menu;
	menu.LoadMenuW(IDR_MAINFRAME);

	return menu.GetSubMenu(menu.GetMenuItemCount() - 1);
}

void CNWPEditor2View::OnEditRename()
{
	RenameDlg renameDlg;

	if (renameDlg.DoModal() == IDOK)
	{
		try {
			m_scintilla_control.RenameVariableOrFunction(renameDlg.GetRenameTo(), m_scintilla_control.GetCurrentLanguageId());
		}
		catch (EmptyFunctionNameException& e) {
			MessageBoxA(*this, e.GetErrorMessage().c_str(), LPCSTR("Error"), MB_OK);
		}
	}
}