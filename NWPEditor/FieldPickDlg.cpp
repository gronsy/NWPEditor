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
}

ColorPickDlg::~ColorPickDlg()
{
}

BOOL ColorPickDlg::OnInitDialog()
{

	UpdateData(FALSE);
	return CDialogEx::OnInitDialog();
}

void ColorPickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ColorPickDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ColorPickDlg::OnBtnClickedOk)
END_MESSAGE_MAP()


// FieldPickDlg message handlers


void ColorPickDlg::OnBtnClickedOk()
{
	// TODO: Add your control notification handler code here
	BOOL retVal;
	*color = ::GetDlgItemInt(*this, IDC_COLORPICKBUTTON, &retVal, FALSE);
	if (retVal == FALSE) MessageBox(_T("Failed to retrive picked color"), _T("Error"));

	CDialogEx::OnOK();
}