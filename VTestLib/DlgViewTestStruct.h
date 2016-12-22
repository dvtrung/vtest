#pragma once
#include "../VTestViewer/QuestView.h"
#include "TestStruct.h"
#include "Tag.h"
#include "viewtree.h"

// CDlgViewTestStruct dialog

class CDlgViewTestStruct : public CDialog
{
	DECLARE_DYNAMIC(CDlgViewTestStruct)

public:
	CDlgViewTestStruct(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewTestStruct();

// Dialog Data
	enum { IDD = IDD_DLGVIEWTESTSTRUCT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	Gdiplus::Font* m_Font;

	CQuestView m_QuestView;

	CTagArray* m_TagArray;
	CArray<CItemBase*, CItemBase*>* m_QuestArray;

	CTestStruct* m_struct;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnChangequest();
	afx_msg void OnBnClickedBtnViewInfo();
	CViewTree m_Tree;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedExport();
};
