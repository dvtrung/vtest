#pragma once
#include "afxcmn.h"


// CDlgPageSetup dialog

class CDlgPageSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgPageSetup)

public:
	CDlgPageSetup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPageSetup();

// Dialog Data
	enum { IDD = IDD_DLGPAGESETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_nMarginLeft;
	CSpinButtonCtrl m_spinMarginLeft;
};
