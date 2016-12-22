
// VTestViewerView.h : interface of the CVTestViewerView class
//

#pragma once


class CVTestViewerView : public CView
{
protected: // create from serialization only
	CVTestViewerView();
	DECLARE_DYNCREATE(CVTestViewerView)

// Attributes
public:
	CVTestViewerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CVTestViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VTestViewerView.cpp
inline CVTestViewerDoc* CVTestViewerView::GetDocument() const
   { return reinterpret_cast<CVTestViewerDoc*>(m_pDocument); }
#endif

