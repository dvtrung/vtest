
// VTestViewerView.cpp : implementation of the CVTestViewerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VTestViewer.h"
#endif

#include "VTestViewerDoc.h"
#include "VTestViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVTestViewerView

IMPLEMENT_DYNCREATE(CVTestViewerView, CFormView)

BEGIN_MESSAGE_MAP(CVTestViewerView, CFormView)
END_MESSAGE_MAP()

// CVTestViewerView construction/destruction

CVTestViewerView::CVTestViewerView()
	: CFormView(CVTestViewerView::IDD)
{
	// TODO: add construction code here

}

CVTestViewerView::~CVTestViewerView()
{
}

void CVTestViewerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CVTestViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CVTestViewerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CVTestViewerView diagnostics

#ifdef _DEBUG
void CVTestViewerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVTestViewerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVTestViewerDoc* CVTestViewerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVTestViewerDoc)));
	return (CVTestViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CVTestViewerView message handlers
