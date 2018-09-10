#include "stdafx.h"
#include "FileOpenDlg.h"

FileOpenDlg::FileOpenDlg(CWnd* pParent/*=nullptr*/)
	:CFileDialog(FALSE, _T(""), _T(""), 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T(""), pParent)
{
	
}

BOOL FileOpenDlg::OnInitDialog()
{
	BOOL bRet=CFileDialog::OnInitDialog();

	if (bRet == TRUE)
		GetDlgItem(IDOK)->SetWindowText(_T("Create"));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}