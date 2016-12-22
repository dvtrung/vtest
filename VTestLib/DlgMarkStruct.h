#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DlgStructSpecifyItemTag.h"
#include "TestStruct.h"
#include "../lib/Item.h"

// CDlgMarkStruct dialog

class CDlgMarkStruct : public CDialog
{
	DECLARE_DYNAMIC(CDlgMarkStruct)

public:
	CDlgMarkStruct(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMarkStruct();

// Dialog Data
	enum { IDD = IDD_DLGMARKSTRUCT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnSaveStruct();
	afx_msg void OnBnClickedOk();

	CTagArray* m_tagArray;
	CArray<CItemBase*, CItemBase*>* m_QuestArray;

	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownList(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_cbStruct;
	CArray<CStringArray*,CStringArray*> m_ItFilterArr;
	CTestStructArray* m_testStructArr;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedStructDelete();
};
