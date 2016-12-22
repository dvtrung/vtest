
// VTestViewerView.h : interface of the CVTestViewerView class
//

#pragma once

#include "resource.h"


class CVTestViewerView : public CFormView
{
protected: // create from serialization only
	CVTestViewerView();
	DECLARE_DYNCREATE(CVTestViewerView)

public:
	enum{ IDD = IDD_VTESTVIEWER_FORM };

// Attributes
public:
	CVTestViewerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

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

