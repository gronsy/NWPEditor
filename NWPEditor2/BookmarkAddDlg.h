#pragma once
#include "resource.h"
#include <string>

// BookmarkAddDlg dialog

class BookmarkAddDlg : public CDialogEx
{
	std::wstring m_bookmark_name;
	CEdit m_bookmark_name_eb;

	DECLARE_DYNAMIC(BookmarkAddDlg)

public:
	BookmarkAddDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~BookmarkAddDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOOKMARKADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	void FillBmName();
public:
	afx_msg void OnBtnClickedOk();
	afx_msg void OnBnClickedCancel();
};
