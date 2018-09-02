#include <string>
// FieldPickDlg dialog

class ColorPickDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ColorPickDlg)
	COLORREF* m_color;
	std::wstring m_field;
	CComboBox m_fieldCombo;
	CMFCColorButton m_colorPick;
	bool m_write_defaults;
public:
	ColorPickDlg(COLORREF* clr, CWnd* pParent = nullptr);   // standard constructor
	virtual ~ColorPickDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog()override;
	afx_msg void OnBtnClickedOk();
	std::wstring GetField() const;
	bool GetWriteDefaults() const;
	afx_msg void OnBtnDefault();
};