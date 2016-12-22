#pragma once
#include "../EditCtrl/VTestEdit.h"
#include "../lib/TestInfo.h"
#include "resource.h"
// CDlgAddCont dialog

class AFX_EXT_CLASS CDlgAddCont : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddCont)

public:
	CDlgAddCont(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddCont();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDCONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CVTestEdit m_Text;
	int m_nStdType;
	virtual BOOL OnInitDialog();
	CComboBox m_cbStdType;
	CTestInfo* m_tInfo;
};
