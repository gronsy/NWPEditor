// FieldPickDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NWPEditor.h"
#include "FieldPickDlg.h"
#include "afxdialogex.h"


// FieldPickDlg dialog

IMPLEMENT_DYNAMIC(ColorPickDlg, CDialogEx)

ColorPickDlg::ColorPickDlg(COLORREF* clr, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLORDIALOG, pParent)
{
	color = clr;
	field = new TCHAR[50];
}

ColorPickDlg::~ColorPickDlg()
{
	delete[] field; field = nullptr;
}

BOOL ColorPickDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_fieldCombo.AddString(_T("Plain Text"));
	m_fieldCombo.AddString(_T("Comments"));
	m_fieldCombo.AddString(_T("Operators"));
	m_fieldCombo.AddString(_T("Selected"));
	m_fieldCombo.AddString(_T("Strings"));
	m_fieldCombo.AddString(_T("Numbers"));
	m_fieldCombo.AddString(_T("UUID"));
	m_fieldCombo.AddString(_T("Preprocessors"));
	return UpdateData(FALSE);
}

void ColorPickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FIELDCOMBO, m_fieldCombo);
	DDX_Control(pDX, IDC_COLORPICKBUTTON, m_colorPick);
}

TCHAR* ColorPickDlg::GetField() { return field; }

BEGIN_MESSAGE_MAP(ColorPickDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ColorPickDlg::OnBtnClickedOk)
END_MESSAGE_MAP()


// FieldPickDlg message handlers


void ColorPickDlg::OnBtnClickedOk()
{
	*color = m_colorPick.GetColor();

	switch (m_fieldCombo.GetCurSel()) {
	case 0: wcscpy(field, _T("plain")); break;
	case 1: wcscpy(field, _T("comment")); break;
	case 2: wcscpy(field, _T("operators")); break;
	case 3: wcscpy(field, _T("selection")); break;
	case 4: wcscpy(field, _T("string"));break;
	case 5: wcscpy(field, _T("number"));break;
	case 6: wcscpy(field, _T("uuid")); break;
	case 7: wcscpy(field, _T("preprocessor")); break;
	default: MessageBox(_T("There is nothing selected!"), _T("Warning"), MB_ICONWARNING); break;
	}

	CDialogEx::OnOK();
}