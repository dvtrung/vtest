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

// VTestLibView.h : interface of the CVTestLibView class
//

#pragma once
#define PAGE_WIDTH 815
#define PAGE_DIS 10

//#include "ClassView.h"
//#include "VTestLibDoc.h"

class CVTestLibDoc;
//class CTagView;

class CVTestLibView : public CScrollView
{
protected: // create from serialization only
	CVTestLibView();
	DECLARE_DYNCREATE(CVTestLibView)

// Attributes
public:
	CVTestLibDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CVTestLibView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	//CTagView* m_wndTagView;
public:
	int m_Left,m_Top,m_Height,m_Width;
	bool m_bShowTags;
	void Draw(bool bCalcOnly=false);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void RefreshScrollBar();
	void Set_Cursor(LPCTSTR id);
	HCURSOR hCursor;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CArray<Rect,Rect> m_rcTag;
	int m_nHighLightTag;
	Rect m_rcQuest;
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnShowhideTag();
	afx_msg void OnUpdateShowhideTag(CCmdUI *pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in VTestLibView.cpp
inline CVTestLibDoc* CVTestLibView::GetDocument() const
   { return reinterpret_cast<CVTestLibDoc*>(m_pDocument); }
#endif

