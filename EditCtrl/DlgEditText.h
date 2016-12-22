#pragma once
#include "afxwin.h"
#include "resource.h"

// CDlgEditText dialog

class AFX_EXT_CLASS CDlgEditText : public CDialog
{
	DECLARE_DYNAMIC(CDlgEditText)

public:
	CDlgEditText(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgEditText();

// Dialog Data
	enum { IDD = IDD_DLGEDITTEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Text;
public:
	CString m_strText;
public:
	virtual BOOL OnInitDialog();
};
