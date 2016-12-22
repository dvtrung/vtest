
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

IMPLEMENT_DYNCREATE(CVTestViewerView, CView)

BEGIN_MESSAGE_MAP(CVTestViewerView, CView)
END_MESSAGE_MAP()

// CVTestViewerView construction/destruction

CVTestViewerView::CVTestViewerView()
{
	// TODO: add construction code here

}

CVTestViewerView::~CVTestViewerView()
{
}

BOOL CVTestViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVTestViewerView drawing

void CVTestViewerView::OnDraw(CDC* /*pDC*/)
{
	CVTestViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CVTestViewerView diagnostics

#ifdef _DEBUG
void CVTestViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CVTestViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVTestViewerDoc* CVTestViewerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVTestViewerDoc)));
	return (CVTestViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CVTestViewerView message handlers
