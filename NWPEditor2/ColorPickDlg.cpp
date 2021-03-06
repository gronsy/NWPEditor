// ColorPickDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NWPEditor2.h"
#include "ColorPickDlg.h"
#include "afxdialogex.h"

// ColorPickDlg dialog

IMPLEMENT_DYNAMIC(ColorPickDlg, CDialogEx)

ColorPickDlg::ColorPickDlg(COLORREF* clr, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLORDIALOG, pParent)
{
	m_color = clr;
	m_write_defaults = false;
}

ColorPickDlg::~ColorPickDlg()
{
}

void ColorPickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FIELDCOMBO, m_field_combo);
	DDX_Control(pDX, IDC_COLORPICKBUTTON, m_color_pick);
	DDX_Control(pDX, IDC_COLORPICKBUTTON, m_color_pick);
}

BOOL ColorPickDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_field_combo.AddString(_T("Plain Text"));
	m_field_combo.AddString(_T("Comments"));
	m_field_combo.AddString(_T("Operators"));
	m_field_combo.AddString(_T("Selection"));
	m_field_combo.AddString(_T("Strings"));
	m_field_combo.AddString(_T("Numbers"));
	m_field_combo.AddString(_T("UUID"));
	m_field_combo.AddString(_T("Preprocessors"));
	m_field_combo.AddString(_T("Keywords"));
	return UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(ColorPickDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ColorPickDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONDEFAULT, &ColorPickDlg::OnBnClickedButtondefault)
	ON_CBN_SELCHANGE(IDC_FIELDCOMBO, &ColorPickDlg::OnCbnSelchangeFieldcombo)
END_MESSAGE_MAP()

// ColorPickDlg message handlers

bool ColorPickDlg::PickField()
{
	switch (m_field_combo.GetCurSel()) {
	case 0: m_field = L"comment"; break;
	case 1: m_field = L"keywords"; break;
	case 2: m_field = L"number"; break;
	case 3: m_field = L"operators"; break;
	case 4: m_field = L"plain"; break;
	case 5: m_field = L"preprocessor"; break;
	case 6: m_field = L"selection"; break;
	case 7: m_field = L"string"; break;
	case 8: m_field = L"uuid"; break;
	default:
	{
		CString msg, title;
		msg.LoadString(IDS_COLORDLG_BTNOK_WARRMSG);
		title.LoadString(IDS_COLORDLG_BTNOK_WARRTITLE);
		if (MessageBox(msg, title, MB_ICONWARNING | MB_YESNO) == IDYES)
			EndDialog(0);
		else
			return false;
	}
	}

	return true;
}

void ColorPickDlg::OnBnClickedOk()
{
	*m_color = m_color_pick.GetColor();

	if (!PickField())
		return;

	CDialogEx::OnOK();
}

void ColorPickDlg::OnBnClickedButtondefault()
{
	CString msg, title;
	msg.LoadString(IDS_COLORDLG_DEFAULT_MSG);
	title.LoadString(IDS_COLORDLG_DEFAULT_TITLE);
	if (MessageBox(msg, title, MB_YESNO) == IDYES)
		m_write_defaults = true;
	else
		return;

	EndDialog(IDOK);
}

std::wstring ColorPickDlg::GetField() const { return m_field; }
bool ColorPickDlg::GetWriteDefaults() const { return m_write_defaults; }

void ColorPickDlg::OnCbnSelchangeFieldcombo()
{
	IniCtrl ini(false);

	PickField();

	COLORREF clr = ini.GetColor(m_field);
	m_color_pick.SetColor(clr);
}