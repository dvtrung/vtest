#pragma once
#include "afxwin.h"


// CDlgChooseTag dialog

class CDlgChooseTag : public CDialog
{
	DECLARE_DYNAMIC(CDlgChooseTag)

public:
	CDlgChooseTag(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgChooseTag();

// Dialog Data
	enum { IDD = IDD_DLGCHOOSETAG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTag;
	CString m_strTagName;
	CStringArray m_arr;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CListBox m_List;
	afx_msg void OnLbnSelchangeList1();
	CString m_strList;
	afx_msg void OnEnChangeEdit1();
};
