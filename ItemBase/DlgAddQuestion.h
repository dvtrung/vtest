#pragma once
#include "../EditCtrl/VTestEdit.h"
#include "resource.h"
#include "afxwin.h"

// CDlgAddQuestion dialog

class AFX_EXT_CLASS CDlgAddQuestion : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddQuestion)

public:
	CDlgAddQuestion(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddQuestion();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDQUESTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int ans;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonFromClipboard();
	afx_msg void OnBnClickedButtonClear();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCbSymbol();
	void RefreshList();
public:
	CVTestEdit m_Question;
	CVTestEdit m_Hint;
	CVTestEdit m_Ans;
	double m_nMark;

	CStringArray m_AnsArr;
	CListBox m_List;
	afx_msg void OnLbnSelchangeList();
	int m_nCurrentAns;
};
