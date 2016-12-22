#pragma once
#include "afxwin.h"
#include "resource.h"

// CDlgEquationEdit dialog

class AFX_EXT_CLASS CDlgEquationEdit : public CDialog
{
	DECLARE_DYNAMIC(CDlgEquationEdit)

public:
	CDlgEquationEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgEquationEdit();

// Dialog Data
	enum { IDD = IDD_DIALOG_EQUATION_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Text;
	CToolBar m_ToolBar;
	CStatic m_staticTBar;
	afx_msg void OnEnChangeEdit1();
	void RefreshImage();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CEdit m_wndText;
};
