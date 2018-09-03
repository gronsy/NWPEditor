
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "NWPEditor.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
	m_current_lang = SCLEX_NULL;
	m_buffer_length = 0;
	m_working_file_path = "";
	m_scinitlla_default_load = true;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_LANGUAGE_C, &CChildView::OnLanguageC)
	ON_COMMAND(ID_LANGUAGE_CPP, &CChildView::OnLanguageCpp)
	ON_COMMAND(ID_LANGUAGE_PYTHON, &CChildView::OnLanguagePython)
	ON_COMMAND(ID_LANGUAGE_PLAINTEXT, &CChildView::OnLanguagePlaintext)
	ON_COMMAND(ID_SETTINGS_FONT, &CChildView::OnSettingsFont)
	ON_COMMAND(ID_SETTINGS_COLORS, &CChildView::OnSettingsColors)
	ON_COMMAND(ID_EDIT_UNDO, &CChildView::OnEditUndo)
	ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CChildView::OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}



int CChildView::OnCreate(LPCREATESTRUCT pcs)
{
	if (CWnd::OnCreate(pcs) == -1)
		return -1;

	m_scintilla_control.SetScintillaCtrl(CreateWindowEx(0, _T("Scintilla"), _T(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN,
		0, 0, 0, 0, *this, (HMENU)101, NULL, NULL));
	return 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	::MoveWindow(m_scintilla_control.GetScintillaCtrl(), 0, 0, cx, cy, FALSE);

	if (m_scinitlla_default_load)
	{
		m_scintilla_control.LoadDefaultState();
		m_scinitlla_default_load = false;
	}
}

void CChildView::OnLanguageC()
{
	if (m_current_lang != SCLEX_CPP)
	{
		m_scintilla_control.SetLang(SCLEX_CPP, true);
		m_current_lang = SCLEX_CPP;
	}
}

void CChildView::OnLanguageCpp()
{
	if (m_current_lang != SCLEX_CPP)
	{
		m_scintilla_control.SetLang(SCLEX_CPP);
		m_current_lang = SCLEX_CPP;
	}
}

void CChildView::OnLanguagePython()
{
	if (m_current_lang != SCLEX_PYTHON)
	{
		m_scintilla_control.SetLang(SCLEX_PYTHON);
		m_current_lang = SCLEX_PYTHON;
	}
}

void CChildView::OnLanguagePlaintext()
{
	if (m_current_lang != SCLEX_NULL)
	{
		m_scintilla_control.SetLang(SCLEX_NULL);
		m_current_lang = SCLEX_NULL;
	}
	m_scintilla_control.LoadDefaultState();
}


void CChildView::OnSettingsFont()
{
	CHARFORMAT cf;
	CFontDialog fontDlg(cf, CF_INITTOLOGFONTSTRUCT|CF_SCREENFONTS|CF_EFFECTS, NULL, this);
	if (fontDlg.DoModal() == IDOK)
	{
		LOGFONT lf;
		fontDlg.GetCurrentFont(&lf);
		m_scintilla_control.GetIni().ChangeFont(lf.lfFaceName);
	}
}


void CChildView::OnSettingsColors()
{
	COLORREF color;
	ColorPickDlg clrDlg(&color, this);

	if (clrDlg.DoModal() == IDOK)
	{
		if (!clrDlg.GetWriteDefaults()) 
		{
			m_scintilla_control.GetIni().ChangeColor(color, clrDlg.GetField());
			m_scintilla_control.UpdateColor(clrDlg.GetField());
		}else 
			m_scintilla_control.RestoreDefaults();
	}
}

BOOL CChildView::PreTranslateMessage(MSG* pMsg)
{
	if (m_current_lang == SCLEX_NULL)
		goto returnLab;

	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetAsyncKeyState(VK_LCONTROL)) 
		{
			m_scintilla_control.CutCopyPaste(pMsg->wParam);
			goto returnLab;
		}

		if (pMsg->wParam==VK_TAB||pMsg->wParam==VK_RETURN) 
		{
			m_scintilla_control.CheckTab();
			m_buffer_length = 0;
		}

		if (pMsg->wParam==VK_SPACE)
		{
			m_buffer_length = 0;
			m_scintilla_control.SavePosition();
			goto returnLab;
		}

		if (pMsg->wParam<VK_LWIN && pMsg->wParam>VK_HELP || (pMsg->wParam > VK_SLEEP))
		{
			++m_buffer_length;
			m_scintilla_control.AutoCompKey(m_buffer_length);
		}
		else if(pMsg->wParam==VK_BACK&&m_buffer_length)
		{
			--m_buffer_length;
			m_scintilla_control.AutoCompKey(m_buffer_length);
		}

		if ((pMsg->wParam == VK_OEM_4 && m_current_lang == SCLEX_CPP)
			|| (pMsg->wParam == VK_OEM_1 && m_current_lang == SCLEX_PYTHON) && GetAsyncKeyState(VK_LSHIFT))
			m_scintilla_control.AddIndent();

		if (pMsg->wParam==VK_OEM_6 && m_current_lang==SCLEX_CPP && GetAsyncKeyState(VK_LSHIFT))
			m_scintilla_control.RmIndent();
	}

	if (pMsg->wParam == VK_RETURN)
		m_scintilla_control.Indent();

	returnLab:
	
	return CWnd::PreTranslateMessage(pMsg);
}


void CChildView::OnEditUndo()
{
	m_scintilla_control.Undo();
}


void CChildView::OnFileOpen()
{
	CFileDialog file_dlg(TRUE, _T(".h\0.c\0.hpp\0.cpp\0.py"));
	file_dlg.DoModal();

	CFile file;
	m_working_file_path=file_dlg.GetPathName();
	if (m_working_file_path == _T(""))
		return;

	if(file.Open(m_working_file_path, file.modeRead))
	{
		std::wstring ext = file_dlg.GetFileExt();
		
		if (ext==_T("c")) 
			OnLanguageC();
		else if (ext== _T("cpp"))
			OnLanguageCpp();
		else if (ext== _T("py"))
			OnLanguagePython();
		else 
			OnLanguagePlaintext();
		if (ext == _T("h"))
			OnLanguageC();

		if (!m_scintilla_control.EditorIsEmpty())
			if (MessageBox(_T("Are you sure you want to clear editor?"), _T("Warrning!"), MB_YESNO) == IDYES)
				m_scintilla_control.ClearEditor();
			else
				return;

		char buffer[256];
		int bytes_read;
		while (bytes_read = file.Read(buffer, sizeof buffer))
		{
			std::string buffer_conv(buffer);
			m_scintilla_control.LoadFromFile(buffer, bytes_read);
		}

		m_scintilla_control.SetUpFOEditor();
	}

	file.Close();
}

void CChildView::OnFileSave()
{
	if (m_working_file_path != _T(""))
		m_scintilla_control.SaveFile(m_working_file_path);
	else
		OnFileSaveas();
}


void CChildView::OnFileSaveas()
{
	CFileDialog save_dlg(FALSE, _T(""), NULL, OFN_OVERWRITEPROMPT);
	save_dlg.DoModal();

	if(m_working_file_path==_T("") || m_working_file_path!=save_dlg.GetPathName())
		m_working_file_path = save_dlg.GetPathName();

	if(m_working_file_path!=_T(""))
		m_scintilla_control.SaveFile(m_working_file_path);
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
