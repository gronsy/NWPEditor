
// ChildView.h : interface of the CChildView class
//
#pragma 
#include "ScintillaCtrl.h"
#include "ColorPickDlg.h"

// CChildView window

class CChildView : public CWnd
{
protected:
	ScintillaCtrl scintillaControl;
	int currentLang;
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//Language Handlers
	afx_msg void OnLanguageC();
	afx_msg void OnLanguageCpp();
	afx_msg void OnLanguagePython();
	afx_msg void OnLanguagePlaintext();
	afx_msg void OnSettingsFont();
	afx_msg void OnSettingsColors();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};