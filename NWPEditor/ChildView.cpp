
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
	currentLang = SCLEX_NULL;
	bufferLength = 0;
	workingFilePath = "";
	scintillaDefaultLoad = true;
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

	if (scintillaDefaultLoad)
	{
		scintillaControl.LoadDefaultState();
		scintillaDefaultLoad = false;
	}
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
	scintillaControl.LoadDefaultState();
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
	if (currentLang == SCLEX_NULL)
		goto returnLab;

	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetAsyncKeyState(VK_LCONTROL)) 
		{
			scintillaControl.CutCopyPaste(pMsg->wParam);
			goto returnLab;
		}

		if (pMsg->wParam==VK_TAB||pMsg->wParam==VK_RETURN) 
		{
			scintillaControl.CheckTab();
			bufferLength = 0;
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			bufferLength = 0;
			goto returnLab;
		}

		if (pMsg->wParam<VK_LWIN && pMsg->wParam>VK_HELP || (pMsg->wParam > VK_SLEEP))
		{
			++bufferLength;
			scintillaControl.AutoCompKey(bufferLength);
		}
		else if(pMsg->wParam==VK_BACK&&bufferLength)
		{
			--bufferLength;
			scintillaControl.AutoCompKey(bufferLength);
		}

		if ((pMsg->wParam == VK_OEM_4 && currentLang == SCLEX_CPP)
			|| (pMsg->wParam == VK_OEM_1 && currentLang == SCLEX_PYTHON) && GetAsyncKeyState(VK_LSHIFT))
			scintillaControl.AddIndent();

		if (pMsg->wParam==VK_OEM_6 && currentLang==SCLEX_CPP && GetAsyncKeyState(VK_LSHIFT))
			scintillaControl.RmIndent();
	}

	returnLab:
	if (pMsg->wParam == VK_RETURN)
		scintillaControl.Indent();
	return CWnd::PreTranslateMessage(pMsg);
}


void CChildView::OnEditUndo()
{
	scintillaControl.Undo();
}


void CChildView::OnFileOpen()
{
	CFileDialog fileDlg(TRUE, _T(".h\0.c\0.hpp\0.cpp\0.py"));
	fileDlg.DoModal();

	CFile file;
	workingFilePath=fileDlg.GetPathName();
	if(file.Open(workingFilePath, file.modeRead))
	{
		std::wstring ext=fileDlg.GetPathName().Mid(workingFilePath.Find('.'));
		
		if (ext==_T(".c")) 
			OnLanguageC();
		else if (ext== _T(".cpp"))
			OnLanguageCpp();
		else if (ext== _T(".py"))
			OnLanguagePython();
		else 
			OnLanguagePlaintext();
		if (ext == _T(".h"))
			OnLanguageC();

		if (!scintillaControl.EditorIsEmpty())
			if (MessageBox(_T("Are you sure you want to clear editor?"), _T("Warrning!"), MB_YESNO) == IDYES)
				scintillaControl.ClearEditor();
			else
				return;

		char buffer[256];
		int bytesRead;
		while (bytesRead = file.Read(buffer, sizeof buffer))
		{
			std::string bufferConv(buffer);
			scintillaControl.LoadFromFile(buffer, bytesRead);
		}

		scintillaControl.SetUpFOEditor();
	}

	file.Close();
}

void CChildView::OnFileSave()
{
	if (workingFilePath != _T(""))
		scintillaControl.SaveFile(workingFilePath);
	else
		OnFileSaveas();
}


void CChildView::OnFileSaveas()
{
	CFileDialog saveDlg(FALSE, _T(""), NULL, OFN_OVERWRITEPROMPT);
	saveDlg.DoModal();

	if(workingFilePath==_T("") || workingFilePath!=saveDlg.GetPathName())
		workingFilePath = saveDlg.GetPathName();

	if(workingFilePath!=_T(""))
		scintillaControl.SaveFile(workingFilePath);
}