#pragma once
#include <string>

// ColorPickDlg dialog

class ColorPickDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ColorPickDlg)
	COLORREF* m_color;
	std::wstring m_field;
	CMFCColorButton m_colorPick;
	bool m_write_defaults;
	CComboBox m_field_combo;

public:
	ColorPickDlg(COLORREF* clr, CWnd* pParent = nullptr);   // standard constructor
	virtual ~ColorPickDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtondefault();
	std::wstring GetField() const;
	bool GetWriteDefaults() const;
	virtual BOOL OnInitDialog();
};