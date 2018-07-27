
// FieldPickDlg dialog

class ColorPickDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ColorPickDlg)
	COLORREF* color;
	TCHAR* field;
	CComboBox m_fieldCombo;
	CMFCColorButton m_colorPick;
	bool writeDefaults;
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
	BOOL OnInitDialog()override;
	afx_msg void OnBtnClickedOk();
	TCHAR* GetField();
	bool GetWriteDefaults();
	afx_msg void OnBtnDefault();
};