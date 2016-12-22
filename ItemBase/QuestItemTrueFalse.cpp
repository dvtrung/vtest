#include "stdafx.h"
#include "Item.h"
#include "DlgAddQuestTrueFalse.h"

CQuestItemTrueFalse::CQuestItemTrueFalse(void)
{
	m_Mode=ShowAnswer;
	m_Type=ItemQuestTrueFalse;
}
void CQuestItemTrueFalse::ReDrawBmp(int width)
{
	RectF rcFBound;
	int w=width-MARGIN_LEFT-MARGIN_RIGHT;
	rcFBound=GetTextBound(m_arrQuest[0],w,yQ);

	const int boxSize=25;

	height=rcFBound.Height+MARGIN_TOP*2+LINE_SPACING;

	for (int i=1;i<m_arrQuest.GetSize();i++)
	{
		int y;
		RectF rc;
		rc=GetTextBound(m_arrQuest[i],w-boxSize,y);
		height+=max(boxSize,rc.Height)+LINE_SPACING;
	}

	if (m_bmp!=NULL) delete m_bmp;

	m_bmp=new Bitmap(width,height,PixelFormat32bppARGB);
	Graphics bGr(m_bmp);
	bGr.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush br(Color::Black);

	Bitmap* bmp=CMathDraw::Draw_Text(m_arrQuest[0],m_Font,width-MARGIN_LEFT-MARGIN_RIGHT,yQ);
	bGr.DrawImage(bmp,MARGIN_LEFT,MARGIN_TOP);
	delete bmp;

	int hDraw=MARGIN_TOP+rcFBound.Height+LINE_SPACING;
	Pen pen(Color::Black,1);
	m_rcAnsArr.RemoveAll();
	m_rcAnsArr.Add(Rect(0,0,0,0));
	for (int i=1;i<m_arrQuest.GetSize();i++)
	{
		int y;
		bmp=CMathDraw::Draw_Text(m_arrQuest[i],m_Font,width-MARGIN_LEFT-MARGIN_RIGHT-boxSize,y);
		if (boxSize>bmp->GetHeight())
		{
			bGr.DrawImage(bmp,MARGIN_LEFT,hDraw+(boxSize-bmp->GetHeight())/2);
			bGr.DrawRectangle(&pen,width-MARGIN_RIGHT-boxSize,hDraw,25,25);
			m_rcAnsArr.Add(Rect(width-MARGIN_RIGHT-boxSize,hDraw,25,25));
		}
		else
		{
			bGr.DrawImage(bmp,MARGIN_LEFT,hDraw);
			bGr.DrawRectangle(&pen,width-MARGIN_RIGHT-boxSize,hDraw+(bmp->GetHeight()-boxSize)/2,25,25);
			m_rcAnsArr.Add(Rect(width-MARGIN_RIGHT-boxSize,hDraw+(bmp->GetHeight()-boxSize)/2,25,25));
		}

		hDraw+=max(bmp->GetHeight(),boxSize)+LINE_SPACING;
		delete bmp;
	}
}
void CQuestItemTrueFalse::Serialize(CArchive& ar)
{
	CItemBase::Serialize(ar);

	m_arrQuest.Serialize(ar);
	m_arrHint.Serialize(ar);
	m_arrAnsSet.Serialize(ar);
	m_arrAns.Serialize(ar);
}
void CQuestItemTrueFalse::DrawAns(Graphics* gr,CString str, Rect rc, Color clr)
{
	if (str==L"[Tick]")
	{
		Gdiplus::Font f(L"Wingdings", 18);
		SolidBrush br(clr);
		gr->DrawString(L"ü",-1,&f,RectF(rc.X,rc.Y,rc.Width,rc.Height),NULL,&br);
	}
	else if (str==L"[Cross]")
	{
		Gdiplus::Font f(L"Wingdings", 18);
		SolidBrush br(clr);
		gr->DrawString(L"û",-1,&f,RectF(rc.X,rc.Y,rc.Width,rc.Height),NULL,&br);
	}
	else
	{
		SolidBrush brush(clr);
		StringFormat strF;
		strF.SetAlignment(StringAlignmentCenter);
		strF.SetLineAlignment(StringAlignmentCenter);
		RectF rcF(rc.X,rc.Y,rc.Width,rc.Height);
		gr->DrawString(str,-1,m_Font,rcF,&strF,&brush);
	}
}
void CQuestItemTrueFalse::Draw(Graphics* gr, Point pt , int width, bool bHighlight)
{
	CItemBase::Draw(gr,pt,width,bHighlight);

	gr->TranslateTransform(pt.X,pt.Y);
	if (m_Mode==ShowAnswer /*&& m_arrAns[0]!=0*/)
	{
		for (int i=1;i<m_rcAnsArr.GetSize();i++)
		{
			if (m_arrAns[i]>0 && m_arrAns[i]<=m_arrAnsSet.GetSize())
			{
				DrawAns(gr,m_arrAnsSet[m_arrAns[i]-1],m_rcAnsArr[i],Color::Black);
			}
		}
	}
	else if (m_Mode==UserAnswer /*&& m_userAns!=L""*/)
	{
		for (int i=1;i<m_rcAnsArr.GetSize();i++)
		{
			if (m_userAns[i]>0 && m_userAns[i]<=m_arrAnsSet.GetSize())
			{
				DrawAns(gr,m_arrAnsSet[m_userAns[i]-1],m_rcAnsArr[i], Color::Black);
			}
		}
	}
	else if (m_Mode==ShowRightAns)
	{
		for (int i=1;i<m_rcAnsArr.GetSize();i++)
		{
			if (m_userAns[i]>0 && m_userAns[i]<=m_arrAnsSet.GetSize())
			{
				DrawAns(gr,m_arrAnsSet[m_userAns[i]-1],m_rcAnsArr[i],m_userAns[i]==m_arrAns[i] ? Color::Blue : Color::Red);
			}
			if (m_arrAns[i]>0 && m_arrAns[i]<=m_arrAnsSet.GetSize() && m_arrAns[i]!=m_userAns[i])
			{
				Pen pen(Color::Red,2);
				gr->DrawLine(&pen,m_rcAnsArr[i].X,m_rcAnsArr[i].Y,m_rcAnsArr[i].GetRight(),m_rcAnsArr[i].GetBottom());
				DrawAns(gr,m_arrAnsSet[m_arrAns[i]-1],
					Rect(m_rcAnsArr[i].X+25,m_rcAnsArr[i].Y,m_rcAnsArr[i].Width,m_rcAnsArr[i].Height),Color::Blue);
			}
		}
	}

	RectF rcIndexF;
	SolidBrush br(Color::Black);
	Gdiplus::Font* f=SetFontStyle(m_Font,FontStyleBold);
	gr->MeasureString(IntToString(index)+L". ",-1,f,PointF(0,0),&rcIndexF);
	gr->DrawString(IntToString(index)+L". ",-1,f,PointF(MARGIN_LEFT-rcIndexF.Width,MARGIN_TOP-yQ),NULL,&br);
	delete f;

	gr->TranslateTransform(-pt.X,-pt.Y);
}
bool CQuestItemTrueFalse::CheckMouseOver( int x, int y )
{
	for (int i=0;i<m_rcAnsArr.GetSize();i++)
		if (m_rcAnsArr[i].Contains(x,y)) return true;
	return false;
}
bool CQuestItemTrueFalse::OnClick( int x, int y )
{
	for (int i=1;i<m_rcAnsArr.GetSize();i++)
		if (m_rcAnsArr[i].Contains(x,y))
		{
			if (m_Mode==ShowAnswer)
			{
				m_arrAns[i]++;
				m_arrAns[i]%=(m_arrAnsSet.GetSize()+1);
			}
			else if (m_Mode==UserAnswer)
			{
				m_userAns[i]++;
				m_userAns[i]%=(m_arrAnsSet.GetSize()+1);
			}
			return true;
		}
		return false;
}


void CQuestItemTrueFalse::Edit(CWnd* pWnd)
{
	CDlgAddQuestTrueFalse dlg(pWnd);
	dlg.m_arrAns=m_arrAns;
	CopyArray(m_arrQuest,dlg.m_arrQuest);
	CopyArray(m_arrAnsSet,dlg.m_arrAnsSet);
	CopyArray(m_arrHint,dlg.m_arrHint);

	if (dlg.DoModal()==IDOK)
	{
		CopyArray(dlg.m_arrHint,m_arrHint);
		m_arrAns=dlg.m_arrAns;
		CopyArray(dlg.m_arrQuest,m_arrQuest);
		CopyArray(dlg.m_arrAnsSet,m_arrAnsSet);
	}
}
