#pragma once
#include "afxwin.h"


// CDlgRenameTag dialog

class CDlgRenameTag : public CDialog
{
	DECLARE_DYNAMIC(CDlgRenameTag)

public:
	CDlgRenameTag(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRenameTag();

// Dialog Data
	enum { IDD = IDD_DLGRENAMETAG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbTag;
	int m_nTag;
	CString m_strRename;
	afx_msg void OnBnClickedOk();
	CStringArray* m_tagName;
	virtual BOOL OnInitDialog();
};
