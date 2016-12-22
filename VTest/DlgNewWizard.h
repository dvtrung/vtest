#include "HtmlEditCtrlEx.h"
#pragma once


// CDlgNewWizard dialog

class CDlgNewWizard : public CDialog
{
	DECLARE_DYNAMIC(CDlgNewWizard)

public:
	CDlgNewWizard(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgNewWizard();

// Dialog Data
	enum { IDD = IDD_DLGNEWWIZARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	virtual BOOL OnInitDialog();
public:
	CString m_strText;
};
