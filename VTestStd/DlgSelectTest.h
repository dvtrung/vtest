#pragma once
#include "TestArray.h"
#include "afxwin.h"

// CDlgSelectTest dialog

class CDlgSelectTest : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectTest)

public:
	CDlgSelectTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECT_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_Title;
public:
	CString m_Subject;
	CString m_Time;
	CString m_Author;
	CString m_OtherInfo;
	CTestArray m_TestArr;
	int m_nTime;
	CString m_strPath;
	CTreeCtrl m_Tree;
	CImageList m_TreeImgLst;

	BOOL m_bShowAnsIm;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddcategory();
	afx_msg void OnTvnEndlabeleditTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnBeginlabeleditTree(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_cbGroupBy;
	afx_msg void OnCbnSelchangeGroupBy();
};
