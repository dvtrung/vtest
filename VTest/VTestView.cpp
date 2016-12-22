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

// VTestView.cpp : implementation of the CVTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VTest.h"
#endif

#include "VTestDoc.h"
#include "VTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CVTestView* pView;
extern Gdiplus::Font* m_Font;

// CVTestView

IMPLEMENT_DYNCREATE(CVTestView, CScrollView)

BEGIN_MESSAGE_MAP(CVTestView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CVTestView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CVTestView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	ON_WM_CHAR()
	ON_COMMAND(ID_ITEM_DOWN, &CVTestView::OnItemDown)
	ON_COMMAND(ID_ITEM_UP, &CVTestView::OnItemUp)
	ON_COMMAND(ID_ITEM_MOVE_DOWN, &CVTestView::OnItemMoveDown)
	ON_COMMAND(ID_ITEM_MOVE_UP, &CVTestView::OnItemMoveUp)
	ON_UPDATE_COMMAND_UI(ID_ITEM_MOVE_DOWN, &CVTestView::OnUpdateItemMoveDown)
	ON_UPDATE_COMMAND_UI(ID_ITEM_MOVE_UP, &CVTestView::OnUpdateItemMoveUp)
END_MESSAGE_MAP()

// CVTestView construction/destruction

CVTestView::CVTestView()
{
	m_Left=0;
	m_Top=PAGE_DIS;
	pView=this;
	m_bDrag=false;
}

CVTestView::~CVTestView()
{
}

void CVTestView::Set_Cursor(LPCTSTR id)
{
	if (AfxGetApp()->LoadStandardCursor(id)!=hCursor)
	{
		hCursor=AfxGetApp()->LoadStandardCursor(id);
	}
}

BOOL CVTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CVTestView drawing

void CVTestView::OnDraw(CDC* pDC)
{
	CVTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDC->IsPrinting())
	{
		
		
	}
	else
	Draw();
}


void CVTestView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	Graphics gr(pDC->m_hDC);
	Gdiplus::Font font(L"Times New Roman",120);
	SolidBrush br(Color::Black);
	gr.DrawString(L"VTest "+IntToString(pInfo->m_nCurPage),-1,&font,PointF(0,0),NULL,&br);
	CRect rc=pInfo->m_rectDraw;
	//gr.DrawString(L"VTest",-1,&font,PointF(0,10000),NULL,&br);

	CScrollView::OnPrint(pDC, pInfo);
}

void CVTestView::Draw()
{
	Graphics gr(this->m_hWnd);
	CRect rc; GetClientRect(rc);

	Bitmap bmp(rc.Width(),rc.Height(),PixelFormat32bppARGB);
	Graphics tmpGr(&bmp);
	tmpGr.SetSmoothingMode(SmoothingModeAntiAlias);
	tmpGr.SetTextRenderingHint(TextRenderingHintAntiAlias);
	tmpGr.Clear(Color::Gray);
	Pen pen(Color::Black);
	Rect rect((rc.Width()-PAGE_WIDTH)/2>0 ? (rc.Width()-PAGE_WIDTH)/2 : m_Left,m_Top,PAGE_WIDTH,GetDocument()->m_Items.m_Height);
	tmpGr.DrawRectangle(&pen,rect);
	SolidBrush wBr(Color::White);
	tmpGr.FillRectangle(&wBr,rect);


	if (!m_bDrag)
		GetDocument()->m_Items.Draw(&tmpGr, Point(rect.GetLeft(),m_Top));
	else
	{
		CPoint pt=GetMessagePos();
		//ScreenToClient(&pt);
		GetDocument()->m_Items.DrawDrag(&tmpGr, Point(rect.GetLeft(),m_Top),m_nDragItem,m_nMouseOverItem);
	}
	gr.DrawImage(&bmp,0,0);
}




// CVTestView printing


void CVTestView::OnFilePrintPreview()
{
	AfxMessageBox(L"Chức năng này chưa được hỗ trợ");
// #ifndef SHARED_HANDLERS
// 	AFXPrintPreview(this);
// #endif
}


void CVTestView::OnFilePrint()
{
	AfxMessageBox(L"Chức năng này chưa được hỗ trợ");
}


BOOL CVTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVTestView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(20);
}

void CVTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	CVTestDoc* pDoc=(CVTestDoc*)GetDocument();
	int id=pDoc->m_Items.GetItemUnderMouse(CPoint(point.x-m_Left,point.y-m_Top));
	pDoc->m_Items.m_hlItem=id;

	Draw();

	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU_POPUP, point.x, point.y, this, TRUE);
#endif

// 	CVTestDoc* pDoc=(CVTestDoc*)GetDocument();
// 	int id=pDoc->m_Items.GetItemUnderMouse(CPoint(point.x-m_Left,point.y-m_Top));
// 
// 	pDoc->m_Items.m_hlItem=id;
// 	Draw();
// 
// 	CMenu menu; menu.LoadMenu(IDR_MENU_POPUP);
// 	CMenu* mn2=menu.GetSubMenu(0);
// 
// 	ClientToScreen(&point);
// 	mn2->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, point.x, point.y, this);
}


// CVTestView diagnostics

#ifdef _DEBUG
void CVTestView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVTestView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVTestDoc* CVTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVTestDoc)));
	return (CVTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CVTestView message handlers


int CVTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	RefreshScrollBar();

	return 0;
}


void CVTestView::OnSize(UINT nType, int cx, int cy)
{
	//CScrollView::OnSize(nType, cx, cy);

	RefreshScrollBar();
	Draw();
}

void CVTestView::RefreshScrollBar()
{
	CRect r;
	GetClientRect(r);
	int width=GetDocument()->m_Items.m_Width;
	int height=GetDocument()->m_Items.m_Height;
	SetScrollSizes(MM_TEXT, CSize(width+2*PAGE_DIS,height+2*PAGE_DIS)
		,CSize(r.Width(),r.Height()),CSize(r.Width(),m_Font->GetSize()*10));

	int h=GetScrollPos(SB_HORZ);
	int v=GetScrollPos(SB_VERT);
	m_Left=width<r.Width() ? (r.Width()-width)/2 : -h+PAGE_DIS;
	m_Top=height<r.Height() ? (r.Height()-height)/2 : -v+PAGE_DIS;

	//SetScrollSizes(MM_TEXT, CSize(PAGE_WIDTH + 2*PAGE_DIS,GetDocument()->m_Items.m_Height + 2*PAGE_DIS));

	Draw();
}


void CVTestView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRect rect;
	GetClientRect(&rect);
	int i=0;
	int pos1=GetScrollPos(SB_VERT);
	switch (nSBCode)
	{
	case SB_LINEDOWN : i=GetDocument()->m_Items.m_Font->GetSize()*4; break;
	case SB_LINEUP : i=-GetDocument()->m_Items.m_Font->GetSize()*4; break;
	case SB_PAGEDOWN : i=rect.Height();break;
	case SB_PAGEUP : i=-rect.Height();break;
	case SB_THUMBTRACK : i=nPos-pos1;
	}
	SetScrollPos(SB_VERT,pos1+i);
	int pos2=GetScrollPos(SB_VERT);
	m_Top+=-(pos2-pos1);

	m_Top=GetDocument()->m_Items.m_Height<rect.Height() ? (rect.Height()-GetDocument()->m_Items.m_Height)/2 : -pos2+PAGE_DIS;
	Draw();

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CVTestView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRect rect;
	GetClientRect(&rect);
	int i=0;
	int pos1=GetScrollPos(SB_HORZ);
	switch (nSBCode)
	{
	case SB_LINEDOWN : i=GetDocument()->m_Items.m_Font->GetSize(); break;
	case SB_LINEUP : i=-GetDocument()->m_Items.m_Font->GetSize(); break;
	case SB_PAGEDOWN : i=rect.Height();break;
	case SB_PAGEUP : i=-rect.Height();break;
	case SB_THUMBTRACK : i=nPos-pos1;
	}
	SetScrollPos(SB_HORZ,pos1+i);
	int pos2=GetScrollPos(SB_HORZ);
	m_Left+=-(pos2-pos1);

	int h=GetScrollPos(SB_HORZ);
	m_Left=GetDocument()->m_Items.m_Width<rect.Width() ? (rect.Width()-GetDocument()->m_Items.m_Width)/2 : -pos2+PAGE_DIS;
	Draw();

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CVTestView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta>0) SendMessage(WM_VSCROLL,SB_LINEUP,NULL);
	else SendMessage(WM_VSCROLL,SB_LINEDOWN,NULL);
	return 1;

	//return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


void CVTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	int id=GetDocument()->m_Items.GetItemUnderMouse(CPoint(point.x-m_Left,point.y-m_Top));
	if (m_bDrag)
	{
		m_nMouseOverItem=id;
		Draw();
	}
	else
	{
		if (id!=-1)
		{
			int top=0;
			for (int i=0;i<id;i++)
			{
				top+=GetDocument()->m_Items[i]->height;
			}

			CRect r; GetClientRect(r);
			CRect rc((r.Width()-PAGE_WIDTH)/2>0 ? (r.Width()-PAGE_WIDTH)/2 : m_Left,top+m_Top,((r.Width()-PAGE_WIDTH)/2>0 ? (r.Width()-PAGE_WIDTH)/2 : m_Left) + PAGE_WIDTH,top+m_Top+GetDocument()->m_Items[id]->height);

			if (GetDocument()->m_Items[id]->CheckMouseOver(point.x-rc.left,point.y-rc.top)) 
				SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
			else SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		}
	}

	CScrollView::OnMouseMove(nFlags, point);
}


void CVTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	int id=GetDocument()->m_Items.GetItemUnderMouse(CPoint(point.x-m_Left,point.y-m_Top));
	if (id!=-1)
	{
		int top=0;
		for (int i=0;i<id;i++)
		{
			top+=GetDocument()->m_Items[i]->height;
		}

		CRect r; GetClientRect(r);
		CRect rc((r.Width()-PAGE_WIDTH)/2>0 ? (r.Width()-PAGE_WIDTH)/2 : m_Left,top+m_Top,((r.Width()-PAGE_WIDTH)/2>0 ? (r.Width()-PAGE_WIDTH)/2 : m_Left) + PAGE_WIDTH,top+m_Top+GetDocument()->m_Items[id]->height);
		if (GetDocument()->m_Items[id]->OnClick(point.x-rc.left,point.y-rc.top))
		{
			GetDocument()->m_Items.RedrawItem(GetDocument()->m_Items[id]);
			GetDocument()->SetModifiedFlag();
			Draw();
		}
		else { this->SetCapture(); m_nDragItem=id; m_bDrag=true; }
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CVTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDrag)
	{
		CVTestDoc* pDoc=(CVTestDoc*)GetDocument();
		int id=pDoc->m_Items.GetItemUnderMouse(CPoint(point.x-m_Left,point.y-m_Top));
		if (id!=-1 && id!=m_nDragItem)
		{
			if (id>m_nDragItem) id--;
			CItemBase* item;
			item=pDoc->m_Items[m_nDragItem];
			pDoc->m_Items.m_Array.RemoveAt(m_nDragItem);
			pDoc->m_Items.m_Array.InsertAt(id,item);
			pDoc->m_Items.ResetIndex();
			pDoc->m_Items.RecalcAllContainerDrawHeight();

			pDoc->m_Items.m_hlItem=id;
		}
		else if (id!=-1)
		{
			int top=0;
			for (int i=0;i<id;i++)
			{
				top+=pDoc->m_Items[i]->height;
			}

			CRect r; GetClientRect(r);
			CRect rc((r.Width()-PAGE_WIDTH)/2>0 ? (r.Width()-PAGE_WIDTH)/2 : m_Left,top+m_Top,((r.Width()-PAGE_WIDTH)/2>0 ? (r.Width()-PAGE_WIDTH)/2 : m_Left) + PAGE_WIDTH,top+m_Top+GetDocument()->m_Items[id]->height);

			pDoc->m_Items.m_hlItem=id;
		}
		else pDoc->m_Items.m_hlItem=-1;

		m_bDrag=false;

		Draw();

		ReleaseCapture();
	}

	CScrollView::OnLButtonUp(nFlags, point);
}


void CVTestView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (GetDocument()->m_Items.CheckMouseOver(point.x-m_Left,point.y-m_Top)) return;

	int i=GetDocument()->m_Items.GetItemUnderMouse(CPoint(point.x-m_Left,point.y-m_Top));
	if (i!=GetDocument()->m_Items.m_hlItem) { GetDocument()->m_Items.m_hlItem=i; Draw(); }

	if (i!=-1)
	{
		GetDocument()->OnEditEdit();
	}

	CScrollView::OnLButtonDblClk(nFlags, point);
}


BOOL CVTestView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	SetCursor(hCursor);

	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
	//return FALSE;
}


void CVTestView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	RefreshScrollBar();
}

void CVTestView::OnItemDown()
{
	if (GetDocument()->m_Items.m_hlItem<GetDocument()->m_Items.GetSize()-1) { GetDocument()->m_Items.m_hlItem++; EnsureHighlightedItemVisible(); Draw(); }
	GetDocument()->m_Items.RecalcAllContainerDrawHeight();
}

void CVTestView::OnItemUp()
{
	if (GetDocument()->m_Items.m_hlItem>0) { GetDocument()->m_Items.m_hlItem--; EnsureHighlightedItemVisible(); Draw(); }
	GetDocument()->m_Items.RecalcAllContainerDrawHeight();
}

void CVTestView::EnsureHighlightedItemVisible()
{
	int top=0;
	for (int i=0;i<GetDocument()->m_Items.m_hlItem;i++)
	{
		top+=GetDocument()->m_Items[i]->height;
	}

	CRect rc; GetClientRect(&rc);
	if (top+m_Top<0) m_Top=-top;
	else if (-top-GetDocument()->m_Items[GetDocument()->m_Items.m_hlItem]->height<m_Top-rc.Height())
		m_Top=-top-GetDocument()->m_Items[GetDocument()->m_Items.m_hlItem]->height+rc.Height();

	SetScrollPos(SB_VERT,PAGE_DIS-m_Top);	
}

void CVTestView::OnItemMoveDown()
{
	CVTestDoc* pDoc=(CVTestDoc*)GetDocument();
	int id=GetDocument()->m_Items.m_hlItem+2;

	if (id>pDoc->m_Items.m_hlItem) id--;
	CItemBase* item;
	item=pDoc->m_Items[pDoc->m_Items.m_hlItem];
	pDoc->m_Items.m_Array.RemoveAt(pDoc->m_Items.m_hlItem);
	pDoc->m_Items.m_Array.InsertAt(id,item);
	pDoc->m_Items.ResetIndex();
	pDoc->m_Items.m_hlItem=id;

	EnsureHighlightedItemVisible(); Draw();
}

void CVTestView::OnItemMoveUp()
{
	CVTestDoc* pDoc=(CVTestDoc*)GetDocument();
	int id=GetDocument()->m_Items.m_hlItem-1;

	if (id>pDoc->m_Items.m_hlItem) id--;
	CItemBase* item;
	item=pDoc->m_Items[pDoc->m_Items.m_hlItem];
	pDoc->m_Items.m_Array.RemoveAt(pDoc->m_Items.m_hlItem);
	pDoc->m_Items.m_Array.InsertAt(id,item);
	pDoc->m_Items.ResetIndex();
	pDoc->m_Items.m_hlItem=id;

	EnsureHighlightedItemVisible(); Draw();
}

void CVTestView::OnUpdateItemMoveDown(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDocument()->m_Items.m_hlItem<GetDocument()->m_Items.GetSize()-1 &&
		GetDocument()->m_Items.m_hlItem!=-1);
}

void CVTestView::OnUpdateItemMoveUp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDocument()->m_Items.m_hlItem>0);
}



void CVTestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (GetDocument()->m_Items.m_hlItem!=-1 && GetDocument()->m_Items[GetDocument()->m_Items.m_hlItem]->m_Type==ItemQuestABCD)
	{
		CQuestItemABCD* item=(CQuestItemABCD*)GetDocument()->m_Items[GetDocument()->m_Items.m_hlItem];
		switch (nChar)
		{
		case 'a': 
		case '1':
			item->m_answer=1; break;
		case 'b': 
		case '2':
			item->m_answer=2; break;
		case 'c':
		case '3':
			item->m_answer=3; break;
		case 'd':
		case '4':
			item->m_answer=4; break;
		case ' ':
			item->m_answer=0; break;
		}
	}
	Draw();

	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}


