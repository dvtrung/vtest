#pragma once
#include "afxwin.h"


// CDlgExportHTML dialog

class CDlgExportHTML : public CDialog
{
	DECLARE_DYNAMIC(CDlgExportHTML)

public:
	CDlgExportHTML(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgExportHTML();

// Dialog Data
	enum { IDD = IDD_DLGEXPORTHTML };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPath;
	afx_msg void OnBnClickedOk2();
	virtual BOOL OnInitDialog();
	CComboBox m_cbTemplate;
	BOOL m_bOpenWhenDone;
	afx_msg void OnBnClickedOk();
	CString m_strFolderName;
	CString m_strTemplate;
	afx_msg void OnBnClickedOk3();
};
