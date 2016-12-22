#pragma once
#include "../EditCtrl/VTestEdit.h"
#include "afxwin.h"
#include "..\ItemBase\Item.h"
#include "resource.h"
// CDlgAddQuestTrueFalse dialog

class AFX_EXT_CLASS CDlgAddQuestTrueFalse : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddQuestTrueFalse)

public:
	CDlgAddQuestTrueFalse(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddQuestTrueFalse();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADDQUESTION_TRUE_FALSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CVTestEdit m_Quest;
	CVTestEdit m_Hint;
	CStringArray m_arrQuest;
	CStringArray m_arrHint;
	CStringArray m_arrAnsSet;
	CIntArray m_arrAns;
	int m_nSelectedItem;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CListBox m_List;
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnLbnSelchangeList1();
	CComboBox m_cbAns;
	afx_msg void OnCbnSelchangeComboAns();
	CComboBox m_cbAnsSet;
	afx_msg void OnBnClickedButton2();
	void SaveData();
};
