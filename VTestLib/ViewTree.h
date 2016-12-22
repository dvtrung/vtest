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

/////////////////////////////////////////////////////////////////////////////
// CViewTree window

class CViewTree : public CTreeCtrl
{
// Construction
public:
	CViewTree();

// Overrides
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementation
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CImageList m_imageState;
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnKeydown(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMTVStateImageChanging(NMHDR *pNMHDR, LRESULT *pResult);
	void SetCheck(HTREEITEM hItem, int iState);
	void RedrawItem(HTREEITEM hItem);
	int GetCheck(HTREEITEM hItem) const;
	void CheckRoot(HTREEITEM hParent, bool bCheck);
	void RefreshCheckState(HTREEITEM hParent);
	HTREEITEM FindChildItem(HTREEITEM hParent,CString strText);
	HTREEITEM MoveItem(HTREEITEM hItem, HTREEITEM hItParent, HTREEITEM hItAfter);
	HTREEITEM FindItem(HTREEITEM hItem, CString strText);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void ToogleCheckbox(HTREEITEM hItem);
	void InitStateImageList();
};
