
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

	scintillaControl.SetScintillaCtrl(CreateWindowEx(0, _T("Scintilla"), _T(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN,
		0, 0, 0, 0, *this, (HMENU)101, NULL, NULL));
	return 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	::MoveWindow(scintillaControl.GetScintillaCtrl(), 0, 0, cx, cy, FALSE);
	scintillaControl.LoadDefaultState();
}

void CChildView::OnLanguageC()
{
	if (currentLang != SCLEX_CPP)
	{
		scintillaControl.SetLang(SCLEX_CPP, true);
		currentLang = SCLEX_CPP;
	}
}

void CChildView::OnLanguageCpp()
{
	if (currentLang != SCLEX_CPP)
	{
		scintillaControl.SetLang(SCLEX_CPP);
		currentLang = SCLEX_CPP;
	}
}

void CChildView::OnLanguagePython()
{
	if (currentLang != SCLEX_PYTHON)
	{
		scintillaControl.SetLang(SCLEX_PYTHON);
		currentLang = SCLEX_PYTHON;
	}
}

void CChildView::OnLanguagePlaintext()
{
	if (currentLang != SCLEX_NULL)
	{
		scintillaControl.SetLang(SCLEX_NULL);
		currentLang = SCLEX_NULL;
	}
}


void CChildView::OnSettingsFont()
{
	CHARFORMAT cf;
	CFontDialog fontDlg(cf, CF_INITTOLOGFONTSTRUCT|CF_SCREENFONTS|CF_EFFECTS, NULL, this);
	if (fontDlg.DoModal() == IDOK)
	{
		LOGFONT lf;
		fontDlg.GetCurrentFont(&lf);
		scintillaControl.GetIni().ChangeFont(lf.lfFaceName);
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
			scintillaControl.GetIni().ChangeColor(color, clrDlg.GetField());
			scintillaControl.UpdateColor(clrDlg.GetField());
		}else 
			scintillaControl.RestoreDefaults();
	}
}

BOOL CChildView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetAsyncKeyState(VK_CONTROL)) {
			scintillaControl.CutCopyPaste(pMsg->wParam);
			goto returnLab;
		}

		if (GetAsyncKeyState(VK_TAB))
			scintillaControl.CheckTab();

		if (pMsg->wParam<VK_LWIN && pMsg->wParam>VK_HELP || (pMsg->wParam > VK_SLEEP))
			scintillaControl.AutoCompKey(pMsg->wParam);
	}

	returnLab:
	return CWnd::PreTranslateMessage(pMsg);
}


void CChildView::OnEditUndo()
{
	scintillaControl.Undo();
}
