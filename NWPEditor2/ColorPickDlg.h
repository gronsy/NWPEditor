#pragma once
#include <string>
#include "IniCtrl.h"

// ColorPickDlg dialog

class ColorPickDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ColorPickDlg)
	COLORREF* m_color;
	std::wstring m_field;
	bool m_write_defaults;
	CComboBox m_field_combo;
	CMFCColorButton m_color_pick;

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

	bool PickField();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtondefault();
	std::wstring GetField() const;
	bool GetWriteDefaults() const;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeFieldcombo();
};