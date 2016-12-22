#pragma once
#include "../EditCtrl/VTestEdit.h"
#include "resource.h"

// CDlgAddText dialog

class AFX_EXT_CLASS CDlgAddText : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddText)

public:
	CDlgAddText(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddText();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDTEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	CVTestEdit m_Text;
};
