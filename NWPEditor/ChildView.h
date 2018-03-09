
// ChildView.h : interface of the CChildView class
//
#pragma once
#include "ScintillaCtrl.h"

// CChildView window

class CChildView : public CWnd
{
protected:
	ScintillaCtrl scintillaControl;
	wchar_t keywords;
	Color clr[];
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
	afx_msg void OnLanguageC();
};

