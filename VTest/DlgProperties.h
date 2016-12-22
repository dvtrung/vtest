#pragma once
#include "afxwin.h"
#include "..\lib\TestInfo.h"


// CDlgProperties dialog

class CDlgProperties : public CDialog
{
	DECLARE_DYNAMIC(CDlgProperties)

public:
	CDlgProperties(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProperties();

// Dialog Data
	enum { IDD = IDD_DIALOG_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTestInfo m_tInfo;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	CComboBox m_cbSubject;
public:
	afx_msg void OnBnClickedOk();
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cbStdType;
};
