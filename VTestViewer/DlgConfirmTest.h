#pragma once
#include "afxwin.h"
#include "..\lib\TestHistory.h"


// CDlgConfirmTest dialog

class CDlgConfirmTest : public CDialog
{
	DECLARE_DYNAMIC(CDlgConfirmTest)

public:
	CDlgConfirmTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgConfirmTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_COMFIRM_DO_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CTestInfo* m_tInfo;
	BOOL m_bShowAnswerIm;
	afx_msg void OnBnClickedOk();
	CComboBox m_cbViewStyle;
	int m_nViewStyle;
	int m_nReviewTest;
	CComboBox m_cbStdType;
	int m_nStdType;
	CTestHistoryArray* m_hisArr;
	afx_msg void OnBnClickedHistory();
};
