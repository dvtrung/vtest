
// VTestStdDlg.h : header file
//

#pragma once
#include "AccArray.h"
#include "DlgUser.h"
#include "QuestList.h"

// CVTestStdDlg dialog
class CVTestStdDlg : public CDialog
{
// Construction
public:
	CVTestStdDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VTESTSTD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void ShowDlgLogin();
	void ShowDlgUser(CString userName);
	void ShowDlgSelectCourse(CString userName);
public:
	CAccArray m_AccArr;
};
