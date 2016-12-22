// QuestView.cpp : implementation file
//

#include "stdafx.h"
#include "QuestView.h"
#include "../lib/ItemArray.h"


// CQuestView

IMPLEMENT_DYNAMIC(CQuestView, CWnd)

CQuestView::CQuestView()
{
	m_Top=0;
	RegisterWndClass();
	m_bAllowEditRightAns=false;
	m_bAllowSelect=false;
	m_nSelectedItem=-1;
}

BOOL CQuestView::RegisterWndClass()
{
	WNDCLASS windowclass;
	HINSTANCE hInst = AfxGetInstanceHandle();

	//Check weather the class is registerd already

	if (!(::GetClassInfo(hInst, L"QuestView", &windowclass)))
	{
		//If not then we have to register the new class

		windowclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInst;
		windowclass.hIcon = NULL;
		windowclass.hCursor = LoadCursor(hInst,MAKEINTRESOURCE(IDC_IBEAM));
		windowclass.hbrBackground = NULL;
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = L"QuestView";

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

CQuestView::~CQuestView()
{
}


BEGIN_MESSAGE_MAP(CQuestView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_CHAR()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// CQuestView message handlers


void CQuestView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CQuestView::OnPaint()
{
	Graphics gr(this->m_hWnd);
	CRect rc; GetClientRect(rc);

	Bitmap bmp(rc.Width(),rc.Height(),PixelFormat32bppARGB);
	Graphics tmpGr(&bmp);
	tmpGr.SetSmoothingMode(SmoothingModeAntiAlias);
	tmpGr.SetTextRenderingHint(TextRenderingHintAntiAlias);
	tmpGr.Clear(Color::White);
	Pen pen(Color::Gray);
	Rect rect(0,0,rc.Width()-1,rc.Height()-1);
	tmpGr.DrawRectangle(&pen,rect);

	m_Items.Draw(&tmpGr,Point(0,m_Top));
// 	SolidBrush wBr(Color::White);
// 	tmpGr.FillRectangle(&wBr,rect);
// 
// 	int top=0;
// 	for (int i=0;i<GetDocument()->m_Items.GetSize();i++)
// 	{
// 		GetDocument()->m_Items[i]->Draw(&tmpGr,Point(rect.GetLeft(),top+m_Top),i==m_hlItem);
// 		top+=GetDocument()->m_Items[i]->height;
// 	}

	gr.DrawImage(&bmp,0,0);

	CWnd::OnPaint();
}

void CQuestView::RefreshScrollBar()
{
	CRect r;
	GetClientRect(r);
	m_Items.ReCalcHeight();
	int width=m_Items.m_Width;
	int height=m_Items.m_Height;

	int p=GetScrollPos(SB_VERT);
	
	SCROLLINFO scrollInfo;
	scrollInfo.cbSize=sizeof(SCROLLINFO);
	scrollInfo.fMask=SIF_RANGE | SIF_PAGE | SIF_DISABLENOSCROLL | SIF_POS;
	scrollInfo.nMin=0;
	scrollInfo.nMax=height+2*PAGE_DIS;
	scrollInfo.nPage=r.Height();
	scrollInfo.nPos=p;
	SetScrollInfo(SB_VERT,&scrollInfo); 

	int v=GetScrollPos(SB_VERT);
	m_Top=-v+PAGE_DIS;

	OnPaint();
}

int CQuestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
void CQuestView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_Items.CheckMouseOver(point.x,point.y-m_Top))
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
	else 
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));

	CWnd::OnMouseMove(nFlags, point);
}

void CQuestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	int id=m_Items.GetItemUnderMouse(CPoint(point.x,point.y-m_Top));


	if (id!=-1)
	{
		int top=0;
		for (int i=0;i<id;i++)
		{
			top+=m_Items[i]->height;
		}

		if (!(!m_bAllowEditRightAns && m_Items[id]->m_Type==ItemQuestABCD && 
			((CQuestItemABCD*)m_Items[id])->m_Mode==QuestMode::ShowAnswer) && m_Items[id]->OnClick(point.x,point.y-m_Top-top))
		{
			bDoneAQuest=true;
			bDoneAllQuest=true;
			for (int i=0;i<m_Items.GetSize();i++) 
				if (m_Items[i]->m_Type==ItemQuestABCD)
					if (((CQuestItemABCD*)m_Items[i])->m_userAns==0) {bDoneAllQuest=false; break;}
		}
		else if (m_bAllowSelect)
		{
			m_Items.m_hlItem=id;
		}
	}

	OnPaint();

	CWnd::OnLButtonDown(nFlags, point);
}

void CQuestView::OnRButtonUp(UINT nFlags, CPoint point)
{
	int id=m_Items.GetItemUnderMouse(CPoint(point.x,point.y-m_Top));

	if (id!=-1)
	{
		int top=0;
		for (int i=0;i<id;i++)
		{
			top+=m_Items[i]->height;
		}

		if (m_Items[id]->m_Type==ItemQuestABCD)
		{
			if (((CQuestItemABCD*)m_Items[id])->OnMark(point.x,point.y-m_Top-top))
			{
			}
		}
	}

	OnPaint();

	CWnd::OnRButtonUp(nFlags, point);
}


void CQuestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (bDoneAQuest) GetParent()->SendMessage(MSG_DONE_A_QUEST);
	if (bDoneAllQuest) GetParent()->SendMessage(MSG_DONE_QUEST);
	bDoneAllQuest=bDoneAQuest=false;

	CWnd::OnLButtonUp(nFlags, point);
}

void CQuestView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

}

void CQuestView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CRect rect;
	GetClientRect(&rect);
	int i=0;
	int pos1=GetScrollPos(SB_VERT);
	switch (nSBCode)
	{
	case SB_LINEDOWN : i=m_Items.m_Font->GetSize()*4; break;
	case SB_LINEUP : i=-m_Items.m_Font->GetSize()*4; break;
	case SB_PAGEDOWN : i=rect.Height();break;
	case SB_PAGEUP : i=-rect.Height();break;
	case SB_THUMBTRACK : i=nPos-pos1;
	}
	SetScrollPos(SB_VERT,pos1+i);
	int pos2=GetScrollPos(SB_VERT);
	m_Top+=-(pos2-pos1);

	m_Top=m_Items.m_Height<rect.Height() ? (rect.Height()-m_Items.m_Height)/2 : -pos2+PAGE_DIS;
	OnPaint();

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CQuestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
