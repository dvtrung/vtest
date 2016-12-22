#pragma once


// CPageChooseFiles dialog

class CPageChooseFiles : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageChooseFiles)

public:
	CPageChooseFiles();
	virtual ~CPageChooseFiles();

// Dialog Data
	enum { IDD = IDD_PROP_NEW_COURSE };
public:
	CTreeCtrl m_Tree;
	CArray<CString*> m_arrFilePath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedAddFiles();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddCategory();
	CImageList m_TreeImgLst;
	afx_msg void OnTvnEndlabeleditTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedRemove2();
	afx_msg void OnBnClickedMake();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUp();
	void SerializeTree(CArchive& ar);
	HTREEITEM AddFile(CString str, HTREEITEM hP=NULL, HTREEITEM hA=NULL);
	void ClearTree();
	void SerializeTree2(HTREEITEM, CArchive&);
	int GetTree1ItemIndex(HTREEITEM hi);
	CArray<HTREEITEM,HTREEITEM> m_hItArray;
	virtual BOOL OnSetActive();
	afx_msg void OnTvnBeginlabeleditTree2(NMHDR *pNMHDR, LRESULT *pResult);
	HTREEITEM MoveItem(HTREEITEM hItem, HTREEITEM hItParent, HTREEITEM hItAfter);
	afx_msg void OnBnClickedDown();
	afx_msg void OnTvnBegindragTree2(NMHDR *pNMHDR, LRESULT *pResult);
};
