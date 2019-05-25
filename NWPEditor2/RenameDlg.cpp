// RenameDlg.cpp : implementation file
//
#pragma once

#include "stdafx.h"
#include "resource.h"
#include "RenameDlg.h"
#include "afxdialogex.h"

// RenameDlg dialog

IMPLEMENT_DYNAMIC(RenameDlg, CDialogEx)

RenameDlg::RenameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RENAME_DIALOG, pParent)
{
}

RenameDlg::~RenameDlg()
{
}

void RenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITBOX_RENAMETO, m_rename_to_eb);
}

BEGIN_MESSAGE_MAP(RenameDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RenameDlg::OnBtnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RenameDlg::OnBtnClickedCancel)
END_MESSAGE_MAP()

// RenameDlg message handlers

void RenameDlg::OnBtnClickedOk()
{
	m_rename_to_eb.GetWindowTextW(m_rename_to);

	if (m_rename_to.IsEmpty())
	{
		CString msg, title;
		msg.LoadStringW(IDS_RENAMEDLG_MSG);
		title.LoadStringW(IDS_RENAMEDLG_TITLE);
		MessageBox(msg, title, MB_OK | MB_ICONWARNING);

		return;
	}

	CDialogEx::OnOK();
}

void RenameDlg::OnBtnClickedCancel()
{
	CDialogEx::OnCancel();
}

CString RenameDlg::GetRenameTo()const
{
	return m_rename_to;
}