#pragma once
#include "viewtree.h"
#include "Tag.h"

// CDlgStructSpecifyItemTag dialog

class CDlgStructSpecifyItemTag : public CDialog
{
	DECLARE_DYNAMIC(CDlgStructSpecifyItemTag)

public:
	CDlgStructSpecifyItemTag(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStructSpecifyItemTag();

// Dialog Data
	enum { IDD = IDD_DLGSTRUCTSPECIFYITEMTAG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	void RefreshItem();
	void RemoveNullNode(HTREEITEM hParent);
	CString GetTreeItemFullText(HTREEITEM hTreeItem);
	void AddTreeItem(HTREEITEM hItem, CString strText);
	void Sort(HTREEITEM hItem);
public:
	CViewTree m_Tree;
	CTagArray* m_tagArray;
	int m_nTagItem;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void AddItemText(HTREEITEM hItem, CString& str);
	CString m_strReturn;
};
