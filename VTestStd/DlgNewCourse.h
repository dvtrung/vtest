#pragma once
#include "afxcmn.h"


// CDlgNewCourse dialog

class CDlgNewCourse : public CDialog
{
	DECLARE_DYNAMIC(CDlgNewCourse)

public:
	CDlgNewCourse(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgNewCourse();

// Dialog Data
	enum { IDD = IDD_DIALOG_NEWCOURSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddFiles();
	CTreeCtrl m_Tree1;
	CArray<CString*> m_arrFilePath;
	virtual BOOL OnInitDialog();
	HTREEITEM m_hRTest,m_hRDoc;
	afx_msg void OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddCategory();
	CTreeCtrl m_Tree2;
	CImageList m_TreeImgLst;
	afx_msg void OnBnClickedTotree2();
	afx_msg void OnTvnEndlabeleditTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedRemove1();
	afx_msg void OnBnClickedRemove2();
	afx_msg void OnBnClickedMake();
};
