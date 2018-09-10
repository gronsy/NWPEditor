#pragma once

class FileOpenDlg:public CFileDialog
{
public:
	FileOpenDlg(CWnd* pParent = nullptr);
	virtual BOOL OnInitDialog();
};