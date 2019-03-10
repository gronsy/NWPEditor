// BookmarkAddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BookmarkAddDlg.h"
#include "afxdialogex.h"

// BookmarkAddDlg dialog

IMPLEMENT_DYNAMIC(BookmarkAddDlg, CDialogEx)

BookmarkAddDlg::BookmarkAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOOKMARKADD, pParent)
{
}

BookmarkAddDlg::~BookmarkAddDlg()
{
}

void BookmarkAddDlg::FillBmName()
{
	CString buffer;
	m_bookmark_name_eb.GetWindowTextW(buffer);
	m_bookmark_name = std::wstring(buffer);
}

std::wstring BookmarkAddDlg::GetBmName()const
{
	return m_bookmark_name;
}

void BookmarkAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITBOOKMARKNAME, m_bookmark_name_eb);
}

BEGIN_MESSAGE_MAP(BookmarkAddDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &BookmarkAddDlg::OnBtnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &BookmarkAddDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

void BookmarkAddDlg::OnBtnClickedOk()
{
	FillBmName();
	if (m_bookmark_name == L"")
	{
		CString msg, title;
		msg.LoadStringW(IDS_BOOKMARKADD_OK_MSGEMPTY);
		title.LoadStringW(IDS_BOOKMARKADD_WARNING);
		if (MessageBox(msg, title, MB_YESNO | MB_ICONWARNING) == IDYES)
			EndDialog(IDCANCEL);
		else
			return;
	}

	CDialogEx::OnOK();
}

void BookmarkAddDlg::OnBnClickedCancel()
{
	FillBmName();
	if (m_bookmark_name != L"")
	{
		CString msg, title;
		msg.LoadStringW(IDS_BOOKMARKADD_CANCEL_NOTEMPTY);
		title.LoadStringW(IDS_BOOKMARKADD_WARNING);
		if (MessageBox(msg, title, MB_YESNO | MB_ICONWARNING) == IDNO)
			return;
	}

	CDialogEx::OnCancel();
}