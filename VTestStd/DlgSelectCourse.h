#pragma once
#include "afxcmn.h"


// CDlgSelectCourse dialog

class CDlgSelectCourse : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectCourse)

public:
	CDlgSelectCourse(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectCourse();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECTCOURSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	afx_msg void OnBnClickedAddcourse();
	void LoadCourse(int nCourse);
	CImageList m_imgList;
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	void SerializeTree2(HTREEITEM hNode, CArchive& ar, int nCourse);
	CTreeCtrl m_Tree;
	CArray<CString*> m_arrFilePath;
	afx_msg void OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
};
