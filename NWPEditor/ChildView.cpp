
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "NWPEditor.h"
#include "ChildView.h"
#include "FieldPickDlg.h"

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
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
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
	scintillaControl.SetLang(SCLEX_CPP, true);
}

void CChildView::OnLanguageCpp() 
{
	scintillaControl.SetLang(SCLEX_CPP);
}

void CChildView::OnLanguagePython()
{
	scintillaControl.SetLang(SCLEX_PYTHON);
}

void CChildView::OnLanguagePlaintext()
{
	scintillaControl.SetLang(SCLEX_NULL);
}


void CChildView::OnSettingsFont()
{
	CHARFORMAT cf;
	CFontDialog fontDlg(cf, CF_INITTOLOGFONTSTRUCT|CF_SCREENFONTS|CF_EFFECTS, NULL, this);
	if (fontDlg.DoModal() == IDOK) scintillaControl.GetIni().AddFont(cf.szFaceName);
}


void CChildView::OnSettingsColors()
{
	COLORREF color;
	ColorPickDlg clrDlg(&color, this);

	if (clrDlg.DoModal() == IDOK) scintillaControl.GetIni().AddColor(color, clrDlg.GetField());
}