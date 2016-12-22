#pragma once
#include "../EditCtrl/VTestEdit.h"
#include "resource.h"

// CDlgAddQuest dialog

class AFX_EXT_CLASS CDlgAddQuest : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddQuest)

public:
	CDlgAddQuest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddQuest();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDQUEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CVTestEdit m_Text;
	CVTestEdit m_Hint;
	virtual BOOL OnInitDialog();
};
