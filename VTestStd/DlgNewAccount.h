#pragma once


// CDlgNewAccount dialog

class CDlgNewAccount : public CDialog
{
	DECLARE_DYNAMIC(CDlgNewAccount)

public:
	CDlgNewAccount(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgNewAccount();

// Dialog Data
	enum { IDD = IDD_DIALOG_NEW_ACC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	CString userName;
public:
	CString passWord;
public:
	CString retypePass;
public:
	CString place;
public:
	CString note;
};
