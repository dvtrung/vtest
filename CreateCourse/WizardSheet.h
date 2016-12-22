#pragma once


// CWizardSheet
class CWizardSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizardSheet)

public:
	CWizardSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWizardSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CWizardSheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void BuildPropPageArray();
	CFont font;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	static int CALLBACK PropSheetProc(HWND hWndDlg, UINT uMsg, LPARAM lParam);
	virtual INT_PTR DoModal();
};


