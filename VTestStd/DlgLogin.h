#pragma once
#include "AccArray.h"

// CDlgLogin dialog

class CDlgLogin : public CDialog
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLogin();

// Dialog Data
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnNewAccount();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
public:
	CComboBox m_cbUserName;
	CString m_Pass;
	CString m_UserName;
	CAccArray* m_AccArr;
	afx_msg void OnBnClickedOk();
};
