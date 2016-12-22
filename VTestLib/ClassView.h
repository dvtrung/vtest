// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#pragma once

#include "Tag.h"
#include "ViewTree.h"

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

//class CVTestLibDoc;

class CTagView : public CDockablePane
{
public:
	CTagView();
	virtual ~CTagView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	CTagArray* m_tagArray;
	void RefreshItem();
	void RefreshChildItem();

protected:
	CClassToolBar m_wndToolBar;
	CImageList m_ClassViewImages;
	UINT m_nCurrSort;

// Overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void ResetChildStates(HTREEITEM hItem);
	void AddTreeItem(HTREEITEM hItem, CString strText);
	CString GetTreeItemFullText(HTREEITEM hTreeItem);
	void RecursiveDeleteItem(HTREEITEM hParent, CStringArray& arr);
	void Sort(HTREEITEM hItem);
	void SortItem();
	void ResetCheck(HTREEITEM);
	CViewTree m_Tree;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
	void OnBeginLabelEdit(NMHDR *pNMHDR, LRESULT *pResult);
	void OnEndLabelEdit(NMHDR *pNMHDR, LRESULT *pResult);
	void OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult);
	void OnItemDbClick(NMHDR *PNMHDR, LRESULT *pResult);
	void RemoveNullNode(HTREEITEM hParent);
public:
	afx_msg void OnDeleteFolder();
	afx_msg void OnUpdateDeleteFolder(CCmdUI *pCmdUI);
};
