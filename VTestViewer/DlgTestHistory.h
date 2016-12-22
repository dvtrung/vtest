#pragma once
#include "afxwin.h"
#include "../lib/TestHistory.h"

// CDlgTestHistory dialog

class CDlgTestHistory : public CDialog
{
	DECLARE_DYNAMIC(CDlgTestHistory)

public:
	CDlgTestHistory(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTestHistory();

// Dialog Data
	enum { IDD = IDD_DLGTESTHISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedViewResult();
	virtual BOOL OnInitDialog();
	CListBox m_List;
	CTestHistoryArray* m_hisArr;
	afx_msg void OnBnClickedClearHistory();
	int m_nHistoryIndex;
	afx_msg void OnBnClickedViewDetail();
};
