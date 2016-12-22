// QuestList.cpp : implementation file
//

#include "stdafx.h"
#include "VTestViewer.h"
#include "QuestList.h"

// CQuestList

IMPLEMENT_DYNAMIC(CQuestList, CWnd)

CQuestList::CQuestList()
{
	m_itemWidth=0;
	m_nMouseMove=-2;
	m_nMouseDown=-2;
	m_nSelected=-2;
	m_nPos=0;
	m_bMouseMove=false;
	m_Font=NULL;

	WNDCLASS windowclass;
	HINSTANCE hInst = AfxGetInstanceHandle();

	//Check weather the class is registerd already

	if (!(::GetClassInfo(hInst, L"QuestList", &windowclass)))
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
		windowclass.lpszClassName = L"QuestList";

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
		}
	}
}

CQuestList::~CQuestList()
{
	if (m_Font!=NULL) delete m_Font;
}


BEGIN_MESSAGE_MAP(CQuestList, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CQuestList message handlers




void CQuestList::OnPaint()
{
	Graphics gr(m_hWnd);

	CRect rc; GetClientRect(rc);

	Bitmap bmp(rc.Width(), rc.Height(),PixelFormat32bppARGB);
	Graphics memGr(&bmp);
	memGr.Clear(Color::White);

	Rect RC(0,0,rc.Width()-1,rc.Height()-1);
	LinearGradientBrush bgrBr(RC,Color(132,193,255),Color(204,230,255),LinearGradientModeVertical);
	memGr.FillRectangle(&bgrBr,RC);
	Pen pen(Color::Gray);
	memGr.DrawRectangle(&pen,0,0,rc.Width()-1,rc.Height()-1);
	//memGr.SetSmoothingMode(SmoothingMode::SmoothingModeHighQuality);
	//memGr.SetTextRenderingHint(TextRenderingHint::TextRenderingHintClearTypeGridFit);
	
	int x=BTN_MARGIN;
	for (int i=-1;i<m_StrArray.GetSize()+1;i++)
	{
		Color clr1,clr2,clrText;
		if (i==m_nMouseDown) { clr1=Color::Brown; clr2=Color::SandyBrown; clrText=Color::White; }
		else if (i==m_nSelected) { clr1=Color::SandyBrown; clr2=Color::Brown; clrText=Color::White; }
		else if (i==m_nMouseMove && m_nMouseDown==-2) { clr1=Color::FloralWhite; clr2=Color::FloralWhite; clrText=Color::Black; }
		else { clr1=Color::LightGray; clr2=Color::FloralWhite; clrText=Color::Black; }
	
		if (i==m_StrArray.GetSize()) 
		{
			x=rc.Width()-GetItemWidth(i)-1-BTN_MARGIN;
			memGr.ResetClip();
			memGr.TranslateTransform(m_nPos,0);
		}

		DrawButton(&memGr,rc.Height()-1,x,
			i==-1 ? L"<" : (i==m_StrArray.GetSize() ? L">" : m_StrArray[i]),clr1,clr2,clrText,GetItemWidth(i));

		if (i==-1) { 
			memGr.SetClip(Rect(x,0,rc.Width()-x-GetItemWidth(m_StrArray.GetSize())-BTN_DIS-BTN_MARGIN,rc.Height()));
			memGr.TranslateTransform(-m_nPos,0);
		}
		//if (i<m_StrArray.GetSize()-1 && GetItemWidth(i+1)+x>rc.Width()-GetItemWidth(m_StrArray.GetSize())-BTN_DIS-BTN_MARGIN) i=m_StrArray.GetSize()-1;
	}

	gr.DrawImage(&bmp,0,0);
	CWnd::OnPaint();
}

void CQuestList::DrawButton(Graphics* gr, int height, int& x, CString str, Color clr1, Color clr2, Color clrText, int width)
{
	RectF rc;
	rc=RectF(0,0,width,height);

	Rect drRc(x,BTN_MARGIN,(int)rc.Width,height-2*BTN_MARGIN);
	Pen pen(Color::Gray,1);

	LinearGradientBrush gbr(drRc,clr1, clr2,LinearGradientModeVertical);
	gr->FillRectangle(&gbr,drRc);
	gr->DrawRectangle(&pen,drRc);

	StringFormat strF;
	strF.SetAlignment(StringAlignment::StringAlignmentCenter);
	strF.SetLineAlignment(StringAlignment::StringAlignmentCenter);
	SolidBrush br(clrText);
	gr->DrawString(str,-1,m_Font,RectF(drRc.X,drRc.Y,drRc.Width,drRc.Height),&strF,&br);

	x+=rc.Width+BTN_DIS;
}

int CQuestList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font=new Gdiplus::Font(L"Verdane",10);

	return 0;
}


void CQuestList::CalcAllItemWidth()
{
	Graphics gr(m_hWnd);
	if (m_itemWidth!=0) return;
	m_ItemWidthArr.RemoveAll();
	for (int i=0;i<m_StrArray.GetSize();i++)
		m_ItemWidthArr.Add(CalcItemWidth(&gr,i));
}
int CQuestList::CalcItemWidth(Graphics* gr,int i)
{
	RectF rc;
	gr->MeasureString(m_StrArray[i],-1,m_Font,PointF(0,0),&rc);
	return (int)rc.Width+BTN_TEXT_MARGIN;
}

void CQuestList::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_nMouseDown=GetItemUnderMouse(point.x);
	OnPaint();

	CWnd::OnLButtonDown(nFlags, point);
}

void CQuestList::SetPos(int nPos)
{
	if (m_nPos<nPos)
	{
		//int i=0;
		//int p=m_nPos;
// 		while (m_nPos<nPos) 
// 		{
// 			m_nPos+=5;
// 			OnPaint();
// 			//i++;
// 			//Sleep(1/**i/(nPos-p)*/);
// 		}
		m_nPos=nPos;
		OnPaint();
	}
	else
	{
		//int i=0;
		//int p=m_nPos;
// 		while (m_nPos>nPos)
// 		{
// 			m_nPos-=5;
// 			OnPaint();
// 			//i++;
// 			//Sleep(1/**i/(p-nPos)*/);
// 		}
		m_nPos=nPos;
		OnPaint();
	}
}

void CQuestList::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture()==this)
	{
		ReleaseCapture();
		m_nMouseDown=-2;
		int s=GetItemUnderMouse(point.x);
		if (s>=0 && s<m_StrArray.GetSize()) { m_nSelected=s; GetParent()->SendMessage(MSG_QUEST_TAB_CHANGE); }

		if (s==-1)
		{
			CRect rc;
			GetClientRect(rc);
			SetPos(max(m_nPos-(rc.Width()-GetItemWidth(0)-2*BTN_MARGIN-2*BTN_DIS+1)/3,0));
		}
		else if (s==m_StrArray.GetSize())
		{
			int w=0;
			for (int i=0;i<m_StrArray.GetSize();i++)
				w+=GetItemWidth(i)+BTN_DIS;
			CRect rc;
			GetClientRect(rc);
			SetPos(min(w-(rc.Width()-GetItemWidth(0)-2*BTN_MARGIN-2*BTN_DIS+1),m_nPos+(rc.Width()-GetItemWidth(0)-2*BTN_MARGIN-2*BTN_DIS+1)/3));
		}
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CQuestList::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON==MK_LBUTTON) {
		m_nMouseDown=m_nMouseMove;
	}
	else if (!m_bMouseMove)
	{
		SetTimer(8497,100,NULL);
		m_bMouseMove=true;
	}
	else
	{
		CRect rc;
		GetClientRect(rc);
		if (point.y<rc.Height())
		{
			m_nMouseMove=GetItemUnderMouse(point.x);
		}
	}
	OnPaint();

	CWnd::OnMouseMove(nFlags, point);
}

int CQuestList::GetItemUnderMouse(int x)
{
	int nX=BTN_MARGIN;
	CRect rc; GetClientRect(rc); 
	if (x>rc.Width()-1-GetItemWidth(m_StrArray.GetSize())-BTN_MARGIN) return m_StrArray.GetSize();
	if (x<GetItemWidth(-1)+BTN_MARGIN) return -1;
	x+=m_nPos;
	for (int i=-1;i<m_StrArray.GetSize()+1;i++)
	{
		if (x<nX) return -2;
		nX+=GetItemWidth(i);
		if (x<nX) return i;
		nX+=BTN_DIS;
	}
}


void CQuestList::OnMouseLeave()
{
	if (GetCapture()!=this)
	{
		m_nMouseMove=-1;
		m_nMouseDown=-1;
		OnPaint();
	}

	CWnd::OnMouseLeave();
}

int CQuestList::GetItemWidth(int i)
{
	if (i==-1 || i==m_StrArray.GetSize()) return 15;
	if (m_itemWidth!=0) return m_itemWidth;
	else return m_ItemWidthArr[i];
}


void CQuestList::OnTimer(UINT_PTR nIDEvent)
{
	CPoint pt(GetMessagePos());
	ScreenToClient(&pt);
	CRect rc; GetClientRect(rc);
	if (!PtInRect(rc,pt))
	{
		KillTimer(nIDEvent);
		m_nMouseDown=-2;
		m_nMouseMove=-2;
		m_bMouseMove=false;
		Invalidate(0);
	}

	CWnd::OnTimer(nIDEvent);
}
