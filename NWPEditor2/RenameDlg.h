#pragma once
#include <string>

// RenameDlg dialog

class RenameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RenameDlg)

public:
	RenameDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RenameDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_rename_from_eb;
	CEdit m_rename_to_eb;

	CString m_rename_to_string;
	CString m_rename_from_string;
public:
	afx_msg void OnBtnClickedOk();
	afx_msg void OnBtnClickedCancel();

	CString GetRenameTo()const;
	CString GetRenameFrom()const;

	bool CheckRenameCondition()const;
};
