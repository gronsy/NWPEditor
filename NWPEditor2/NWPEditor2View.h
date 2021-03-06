// NWPEditor2View.h : interface of the CNWPEditor2View class
//

#pragma once
#include "ScintillaCtrl.h"
#include "ColorPickDlg.h"
#include "BookmarkAddDlg.h"
#include "RenameDlg.h"
#include "NWPEditor2Doc.h"

#include "CppLanguage.h"
#include "PythonLanguage.h"

struct Lang
{
	int curr_lang;
	std::wstring ext;
};

class CNWPEditor2View : public CView
{
protected:
	ScintillaCtrl m_scintilla_control;
	int m_buffer_length;
	CString m_working_file_path;
	bool m_scintlla_default_load;

protected: // create from serialization only
	CNWPEditor2View() noexcept;
	DECLARE_DYNCREATE(CNWPEditor2View)
	bool ClearEditorWarning();

	// Attributes
public:
	CNWPEditor2Doc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CNWPEditor2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//void SetCurLang(int lex, bool clang = false);
	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	//Helpers
protected:
	CMenu* CreateBookmarkMenu();
public:
	afx_msg void OnLanguageC();
	afx_msg void OnLanguageCpp();
	afx_msg void OnLanguagePython();
	afx_msg void OnLanguagePlain();
	afx_msg void OnSettingsFonts();
	afx_msg void OnSettingsColors();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEditUndo();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	afx_msg void OnFileNew();
	afx_msg void OnBookmarksAddbookmark();
	afx_msg void OnEditRename();
};

#ifndef _DEBUG  // debug version in NWPEditor2View.cpp
inline CNWPEditor2Doc* CNWPEditor2View::GetDocument() const
{
	return reinterpret_cast<CNWPEditor2Doc*>(m_pDocument);
}
#endif
