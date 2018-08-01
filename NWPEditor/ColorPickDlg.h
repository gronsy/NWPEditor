
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
	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog()override;
	afx_msg void OnBtnClickedOk();
	TCHAR* GetField() const;
	bool GetWriteDefaults() const;
	afx_msg void OnBtnDefault();
};