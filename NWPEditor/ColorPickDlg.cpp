// FieldPickDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NWPEditor.h"
#include "ColorPickDlg.h"
#include "afxdialogex.h"


// FieldPickDlg dialog

IMPLEMENT_DYNAMIC(ColorPickDlg, CDialogEx)

ColorPickDlg::ColorPickDlg(COLORREF* clr, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLORDIALOG, pParent)
{
	color = clr;
	writeDefaults = false;
}

ColorPickDlg::~ColorPickDlg()
{
}

BOOL ColorPickDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_fieldCombo.AddString(_T("Plain Text"));
	m_fieldCombo.AddString(_T("Comments"));
	m_fieldCombo.AddString(_T("Operators"));
	m_fieldCombo.AddString(_T("Selection"));
	m_fieldCombo.AddString(_T("Strings"));
	m_fieldCombo.AddString(_T("Numbers"));
	m_fieldCombo.AddString(_T("UUID"));
	m_fieldCombo.AddString(_T("Preprocessors"));
	m_fieldCombo.AddString(_T("Keywords"));
	return UpdateData(FALSE);
}

void ColorPickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FIELDCOMBO, m_fieldCombo);
	DDX_Control(pDX, IDC_COLORPICKBUTTON, m_colorPick);
}

std::wstring ColorPickDlg::GetField() const { return field; }

BEGIN_MESSAGE_MAP(ColorPickDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ColorPickDlg::OnBtnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONDEFAULT, &ColorPickDlg::OnBtnDefault)
END_MESSAGE_MAP()


// FieldPickDlg message handlers


void ColorPickDlg::OnBtnClickedOk()
{
	*color = m_colorPick.GetColor();

	switch (m_fieldCombo.GetCurSel()) {
	case 0: field=_T("comment"); break;
	case 1: field=_T("comment"); break;
	case 2: field=_T("operators"); break;
	case 3: field=_T("selection"); break;
	case 4: field=_T("string");break;
	case 5: field=_T("number");break;
	case 6: field=_T("uuid"); break;
	case 7: field=_T("preprocessor"); break;
	case 8: field=_T("keywords"); break;
	default: 
		if(MessageBox(_T("There is nothing selected, are you sure you want to exit?"), _T("Warning"), MB_ICONWARNING|MB_YESNO)==IDYES)
			EndDialog(0); 
		break;
	}

	CDialogEx::OnOK();
}

void ColorPickDlg::OnBtnDefault()
{
	if (MessageBox(_T("Are you sure you want to restore defaults?"), _T("Defaults"), MB_YESNO) == IDYES)
		writeDefaults = true;

	EndDialog(IDOK);
}

bool ColorPickDlg::GetWriteDefaults() const { return writeDefaults; }