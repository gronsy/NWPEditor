#include "stdafx.h"
#include "FileOpenDlg.h"

FileOpenDlg::FileOpenDlg(CWnd* pParent/*=nullptr*/)
	:CFileDialog(TRUE, _T(""), _T(""), 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T(""), pParent)
{
	
}

BOOL FileOpenDlg::OnInitDialog()
{
	BOOL bRet=CFileDialog::OnInitDialog();

	if (bRet == TRUE)
		GetDlgItem(IDOK)->SetWindowText(_T("Create"));


	return TRUE;
}
