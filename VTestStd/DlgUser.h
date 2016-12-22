#pragma once
#include "Account.h"
#include "DlgTest.h"

// CDlgUser dialog

class CDlgUser : public CDialog
{
	DECLARE_DYNAMIC(CDlgUser)

public:
	CDlgUser(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgUser();

// Dialog Data
	enum { IDD = IDD_DIALOG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEditInfo();
	afx_msg void OnBnClickedButtonSelectTest();

	CAccount* acc;
	virtual BOOL OnInitDialog();

};
