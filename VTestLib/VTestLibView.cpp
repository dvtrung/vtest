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

// VTestLibView.cpp : implementation of the CVTestLibView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VTestLib.h"
#endif

#include "VTestLibDoc.h"
#include "VTestLibView.h"
#include "DlgChooseTag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern Gdiplus::Font* m_Font;

// CVTestLibView

IMPLEMENT_DYNCREATE(CVTestLibView, CScrollView)

BEGIN_MESSAGE_MAP(CVTestLibView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_SHOWHIDE_TAG, &CVTestLibView::OnShowhideTag)
	ON_UPDATE_COMMAND_UI(ID_SHOWHIDE_TAG, &CVTestLibView::OnUpdateShowhideTag)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CVTestLibView construction/destruction

CVTestLibView::CVTestLibView()
{
	m_Width=PAGE_WIDTH;
	m_Height=0;

	m_bShowTags=true;
}

CVTestLibView::~CVTestLibView()
{
}

void CVTestLibView::Set_Cursor(LPCTSTR id)
{
	if (AfxGetApp()->LoadStandardCursor(id)!=hCursor)
	{
		hCursor=AfxGetApp()->LoadStandardCursor(id);
	}
}

BOOL CVTestLibView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CVTestLibView drawing

void CVTestLibView::OnDraw(CDC* /*pDC*/)
{
	CVTestLibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Draw();
}

void CVTestLibView::Draw(bool bCalcOnly)
{
	const int titleHeight=30;


	Graphics gr(this->m_hWnd);
	CRect rc; GetClientRect(rc);

	Bitmap bmp(rc.Width(),rc.Height(),PixelFormat32bppARGB);
	Graphics tmpGr(&bmp);
	tmpGr.SetSmoothingMode(SmoothingModeAntiAlias);
	tmpGr.SetTextRenderingHint(TextRenderingHintAntiAlias);
	tmpGr.Clear(Color::White);

	CVTestLibDoc* pDoc=GetDocument();

	if (pDoc->GetCurrentQuestIndex()!=0)
	{
		m_Width=min(PAGE_WIDTH,rc.Width()-2*PAGE_DIS);
		m_Height=0;

		Gdiplus::Font fontBold(L"Times New Roman",12,FontStyleBold);
		CString strText=L"Câu " + IntToString(pDoc->GetCurrentQuestIndex()) + " / " + IntToString(pDoc->GetQuestCount());
		RectF boundingBox;
		tmpGr.MeasureString(strText,-1,&fontBold,PointF(0,0),&boundingBox);
		//m_Height+=MARGIN_TOP + boundingBox.Height + PARA_SPACING;
		m_Height=titleHeight;

		Gdiplus::Font fontRegular(L"Times New Roman",12,FontStyleRegular);

		CStringArray arrTextTag;
		CArray<RectF,RectF> boundingBoxTag;
		
		if (m_bShowTags)
		{
			for (int i=0;i<GetDocument()->GetTagCount();i++)
			{
				arrTextTag.Add(pDoc->GetTagName(i) + L" : " + pDoc->GetCurrentItemTag(i));
				boundingBoxTag.Add(RectF(0,0,0,0));
				tmpGr.MeasureString(arrTextTag[i],-1,&fontRegular,PointF(0,0),&boundingBoxTag[i]);
				m_Height+=boundingBoxTag[i].Height;
			}
			m_Height+=PARA_SPACING;
		}

		if (pDoc->GetCurrentItem()->m_bmp==NULL || pDoc->GetCurrentItem()->m_bmp->GetWidth()!=m_Width) 
			pDoc->GetCurrentItem()->ReDrawBmp(m_Width);
		m_Height+=pDoc->GetCurrentItem()->m_bmp->GetHeight();

		// If there's hint
		if (pDoc->GetCurrentItem()->m_Type==ItemQuestABCD && 
			((CQuestItemABCD*)pDoc->GetCurrentItem())->m_bShowHint && ((CQuestItemABCD*)pDoc->GetCurrentItem())->m_bmpHint!=NULL)
			m_Height+=((CQuestItemABCD*)pDoc->GetCurrentItem())->m_bmpHint->GetHeight() + LINE_SPACING;

		m_Height+=MARGIN_BOTTOM + PARA_SPACING;

		if (!bCalcOnly)
		{
			//Draw Box
			Pen penBorder(Color::Black);
			Rect rect((rc.Width()-m_Width)/2>0 ? (rc.Width()-m_Width)/2 : m_Left,m_Top,m_Width,m_Height);
			tmpGr.DrawRectangle(&penBorder,rect);

			LinearGradientBrush wBr(rect,Color(255,255,255),Color(230,250,255),LinearGradientModeVertical);
			tmpGr.FillRectangle(&wBr,rect);

			// Draw image
			int top=m_Top;
			//top+=MARGIN_TOP;

			// DrawTitle
			SolidBrush brText(Color::Black);
			SolidBrush brTextTitle(pDoc->IsCurrentItemMarked() ? Color::Red : Color::Black);
			RectF rcTitle=RectF(rect.GetLeft(),rect.GetTop(),rect.Width,titleHeight);
			LinearGradientBrush tBr(rcTitle,Color(215,231,245),Color::LightBlue,LinearGradientModeVertical);
			tmpGr.DrawRectangle(&penBorder,rcTitle);
			tmpGr.FillRectangle(&tBr,rcTitle);
			StringFormat strTitleF; strTitleF.SetAlignment(StringAlignmentCenter); strTitleF.SetLineAlignment(StringAlignmentCenter);
			tmpGr.DrawString(strText,-1,&fontBold,rcTitle,&strTitleF,&brTextTitle);
			//top+=boundingBox.Height+PARA_SPACING*2;
			top+=titleHeight + MARGIN_TOP;
			if (m_bShowTags)
			{
				m_rcTag.RemoveAll();
				for (int i=0;i<arrTextTag.GetSize();i++)
				{
					m_rcTag.Add(Rect(rect.GetLeft()+20,top,boundingBoxTag[i].Width,boundingBoxTag[i].Height));
					if (m_nHighLightTag==i)
					{
						Pen pen(Color::Black);
						LinearGradientBrush brHl(m_rcTag[i], Color(215,231,245),Color(225,241,255), LinearGradientModeVertical);
						tmpGr.FillRectangle(&brHl,m_rcTag[i]);
						tmpGr.DrawRectangle(&pen,m_rcTag[i]);
					}
					tmpGr.DrawString(arrTextTag[i],-1,&fontRegular,PointF(rect.GetLeft() + 20,top),NULL,&brText);
					top+=m_rcTag[i].Height;
				}
				top+=PARA_SPACING;
			}

			m_rcQuest=Rect(rect.GetLeft(),top,m_Width,GetDocument()->GetCurrentItem()->m_bmp->GetHeight());
			GetDocument()->GetCurrentItem()->Draw(&tmpGr, Point(rect.GetLeft(),top),m_Width);
		}
	}
	else
	{
		Gdiplus::Font fontRegular(L"Times New Roman",12,FontStyleRegular);
		SolidBrush br(Color::Black);
		CString str=L"Không có câu hỏi nào !";
		StringFormat strF; strF.SetAlignment(StringAlignmentCenter); strF.SetLineAlignment(StringAlignmentCenter);
		tmpGr.DrawString(str,-1,&fontRegular,RectF(0,0,rc.Width(),rc.Height()),&strF,&br);
	}


// 	if (!m_bDrag)
// 		GetDocument()->m_Items.Draw(&tmpGr, Point(rect.GetLeft(),m_Top));
// 	else
// 	{
// 		CPoint pt=GetMessagePos();
// 		//ScreenToClient(&pt);
// 		GetDocument()->m_Items.DrawDrag(&tmpGr, Point(rect.GetLeft(),m_Top),m_nDragItem,m_nMouseOverItem);
// 	}
	if (!bCalcOnly) gr.DrawImage(&bmp,0,0);
}


void CVTestLibView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	RefreshScrollBar();

	GetDocument()->pView=this;
	GetDocument()->RefreshCurrentQuestArray();
}

void CVTestLibView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVTestLibView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVTestLibView diagnostics

#ifdef _DEBUG
void CVTestLibView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVTestLibView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVTestLibDoc* CVTestLibView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVTestLibDoc)));
	return (CVTestLibDoc*)m_pDocument;
}
#endif //_DEBUG


// CVTestLibView message handlers


void CVTestLibView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	RefreshScrollBar();
}

void CVTestLibView::RefreshScrollBar()
{
	Draw(true);
	SetRedraw(FALSE);

	CRect r;
	GetClientRect(r);
	int width=m_Width;
	int height=m_Height;
	SetScrollSizes(MM_TEXT, CSize(width+2*PAGE_DIS,height+2*PAGE_DIS)
		,CSize(r.Width(),r.Height()),CSize(r.Width(),m_Font->GetSize()*10));

	Draw(true);
	CRect r2; GetClientRect(r2);
	if (r2!=r)
	{
		int width=m_Width;
		int height=m_Height;
		SetScrollSizes(MM_TEXT, CSize(width+2*PAGE_DIS,height+2*PAGE_DIS)
			,CSize(r.Width(),r.Height()),CSize(r.Width(),m_Font->GetSize()*10));
	}

	int h=GetScrollPos(SB_HORZ);
	int v=GetScrollPos(SB_VERT);
	m_Left=width<r.Width() ? (r.Width()-width)/2 : -h+PAGE_DIS;
	//m_Top=height<r.Height() ? (r.Height()-height)/2 : -v+PAGE_DIS;
	m_Top=PAGE_DIS;

	SetRedraw();
	Draw();
}



void CVTestLibView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRect rect;
	GetClientRect(&rect);
	int i=0;
	int pos1=GetScrollPos(SB_VERT);
	switch (nSBCode)
	{
	case SB_LINEDOWN : i=m_Font->GetSize()*4; break;
	case SB_LINEUP : i=-m_Font->GetSize()*4; break;
	case SB_PAGEDOWN : i=rect.Height();break;
	case SB_PAGEUP : i=-rect.Height();break;
	case SB_THUMBTRACK : i=nPos-pos1;
	}
	SetScrollPos(SB_VERT,pos1+i);
	int pos2=GetScrollPos(SB_VERT);
	m_Top+=-(pos2-pos1);

	m_Top=m_Height<rect.Height() ? PAGE_DIS : -pos2+PAGE_DIS;
	Draw();

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CVTestLibView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRect rect;
	GetClientRect(&rect);
	int i=0;
	int pos1=GetScrollPos(SB_HORZ);
	switch (nSBCode)
	{
	case SB_LINEDOWN : i=m_Font->GetSize(); break;
	case SB_LINEUP : i=-m_Font->GetSize(); break;
	case SB_PAGEDOWN : i=rect.Height();break;
	case SB_PAGEUP : i=-rect.Height();break;
	case SB_THUMBTRACK : i=nPos-pos1;
	}
	SetScrollPos(SB_HORZ,pos1+i);
	int pos2=GetScrollPos(SB_HORZ);
	m_Left+=-(pos2-pos1);

	int h=GetScrollPos(SB_HORZ);
	m_Left=m_Width<rect.Width() ? (rect.Width()-m_Width)/2 : -pos2+PAGE_DIS;
	Draw();

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CVTestLibView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta>0) SendMessage(WM_VSCROLL,SB_LINEUP,NULL);
	else SendMessage(WM_VSCROLL,SB_LINEDOWN,NULL);
	return 1;

	//return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


void CVTestLibView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (GetDocument()->GetCurrentItem()!=NULL)
	{
		//CRect r; GetClientRect(r);
		//CRect rc((r.Width()-PAGE_WIDTH)/2>0 ? (r.Width()-PAGE_WIDTH)/2 : m_Left,m_Top,((r.Width()-PAGE_WIDTH)/2>0 ? (r.Width()-PAGE_WIDTH)/2 : m_Left) + PAGE_WIDTH,m_Top+GetDocument()->GetCurrentItem()->height);

		LPWSTR cursor=IDC_ARROW;
		bool bDraw=false;

		if (GetDocument()->GetCurrentItem()->CheckMouseOver(point.x-m_rcQuest.X,point.y-m_rcQuest.Y)) cursor=IDC_HAND;
		else
		{
			if (m_nHighLightTag!=-1) { m_nHighLightTag=-1; bDraw=true; }
			for (int i=0;i<m_rcTag.GetSize();i++) if (m_rcTag[i].Contains(Point(point.x,point.y)))
			{
				cursor=IDC_HAND;
				m_nHighLightTag=i;
				bDraw=true;	break;
			}
		}
		
		if (bDraw) Draw();
		Set_Cursor(cursor);

	}

	CScrollView::OnMouseMove(nFlags, point);
}


void CVTestLibView::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	CScrollView::OnLButtonDblClk(nFlags, point);
}


void CVTestLibView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (GetDocument()->GetCurrentQuestIndex()!=0)
	{
		//CRect r; GetClientRect(r);
		if (GetDocument()->GetCurrentItem()->OnClick(point.x-m_rcQuest.X,point.y-m_rcQuest.Y))
		{
			if (!GetDocument()->m_bShowAns)
			{
				((CQuestItemABCD*)GetDocument()->GetCurrentItem())->m_bShowHint=true;
				((CQuestItemABCD*)GetDocument()->GetCurrentItem())->m_Mode=QuestMode::ShowRightAns;
			}
			GetDocument()->SetModifiedFlag();
			Draw();
		}
		else
		{
			if (m_bShowTags)
			{
				for (int i=0;i<m_rcTag.GetSize();i++)
					if (m_rcTag[i].Contains(Point(point.x,point.y)))
					{
						CDlgChooseTag dlg;
						dlg.m_strTagName=GetDocument()->GetTagName(i) + L" :";
						dlg.m_strTag=GetDocument()->GetCurrentItemTag(i);
						GetDocument()->GetTagArray()->GetItemsInTag(dlg.m_arr,i);

						if (dlg.DoModal()==IDOK)
						{
							CString str=dlg.m_strTag;
							while (str.Find(L": ")!=-1) str.Replace(L": ",L":");
							while (str.Find(L" :")!=-1) str.Replace(L" :",L":");
							str.Replace(L":",L" : ");
							GetDocument()->SetCurrentItemTag(i,(str==L"<null>") ? L"" : str);
							GetDocument()->m_wndTags->RefreshChildItem();
							GetDocument()->RefreshCurrentQuestArray();
							GetDocument()->SetModifiedFlag();
						}
						break;
					}
			}
		}
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CVTestLibView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CScrollView::OnLButtonUp(nFlags, point);
}


BOOL CVTestLibView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	SetCursor(hCursor);
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
	//return TRUE;
}


void CVTestLibView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar==VK_LEFT) GetDocument()->OnPrevious();
	else if (nChar==VK_RIGHT) GetDocument()->OnNext();

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CVTestLibView::OnShowhideTag()
{
	m_bShowTags=!m_bShowTags;
	RefreshScrollBar();
}


void CVTestLibView::OnUpdateShowhideTag(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bShowTags);
}


int CVTestLibView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= WS_VSCROLL;
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}
