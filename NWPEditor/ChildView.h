
// ChildView.h : interface of the CChildView class
//
#pragma once
#include <Windows.h>
#include "ScintillaCtrl.h"
#include "ColorPickDlg.h"
#include <string>

// CChildView window

class CChildView : public CWnd
{
protected:
	ScintillaCtrl m_scintilla_control;
	int m_current_lang, m_buffer_length;
	CString m_working_file_path;
	bool m_scinitlla_default_load;
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

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
	virtual BOOL PreTranslateMessage(MSG* pMsg) override;
	afx_msg void OnEditUndo();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};