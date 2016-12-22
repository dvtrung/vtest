#include "stdafx.h"
#include "Item.h"
#include "DlgAddQuestion.h"

CQuestItemABCD::CQuestItemABCD( void )
{
	m_bmpHint=NULL;
	m_Type=ItemQuestABCD; m_Mode=ShowAnswer; m_userAns=0;
	m_alt.bMarkA=false; m_alt.bMarkB=false; m_alt.bMarkC=false; m_alt.bMarkD=false; 
	m_nIndex=0;
}
void CQuestItemABCD::Draw(Graphics* gr, Point pt , int width, bool bHighlight)
{
	ReCalcHeight();
	CItemBase::Draw(gr,pt,width,bHighlight);

	gr->TranslateTransform(pt.X,pt.Y);

	if (m_bShowHint && m_bmpHint!=NULL) gr->DrawImage(m_bmpHint,MARGIN_LEFT,m_bmp->GetHeight());

	if (m_Mode==ShowAnswer && m_answer!=0)
	{
		Rect rc;
		switch (m_answer) { case 1: rc=rcC1; break; case 2: rc=rcC2; break; case 3: rc=rcC3; break; case 4: rc=rcC4; break; }
		rc.Inflate(Point(2,2));
		rc.Height-=2;
		Pen pen(Color::Black,2);
		gr->DrawEllipse(&pen,rc);
	}
	else if (m_Mode==UserAnswer && m_userAns!=0)
	{
		Rect rc;
		switch (m_userAns) { case 1: rc=rcC1; break; case 2: rc=rcC2; break; case 3: rc=rcC3; break; case 4: rc=rcC4; break; }
		rc.Inflate(Point(2,2));
		rc.Height-=2;
		Pen pen(Color::Black,2);
		gr->DrawEllipse(&pen,rc);
	}
	else if (m_Mode==ShowRightAns)
	{
		Rect rc1,rc2;
		switch (m_answer) { case 1: rc1=rcC1; break; case 2: rc1=rcC2; break; case 3: rc1=rcC3; break; case 4: rc1=rcC4; break; }
		switch (m_userAns) { case 1: rc2=rcC1; break; case 2: rc2=rcC2; break; case 3: rc2=rcC3; break; case 4: rc2=rcC4; break; }
		if (m_answer==m_userAns)
		{
			rc1.Inflate(2,2);
			rc1.Height-=2;
			Pen pen(Color::Blue,2);
			gr->DrawEllipse(&pen,rc1);
		}
		else if (m_answer!=0)
		{
			if (m_userAns!=0)
			{
				Pen pen(Color::Gray,2);
				rc2.Inflate(2,2);
				rc2.Height-=2;
				gr->DrawEllipse(&pen,rc2);
				gr->DrawLine(&pen,rc2.GetLeft(),rc2.GetTop(),rc2.GetRight(),rc2.GetBottom());
			}

			rc1.Inflate(Point(2,2));
			rc1.Height-=2;
			Pen pen2(Color::Red,2);
			gr->DrawEllipse(&pen2,rc1);
		}
	}

	if (m_userAns==0)
	{
		if (m_alt.bMarkA%3)
		{
			Gdiplus::Font f(L"Wingdings", m_Font->GetSize());
			SolidBrush br(Color::Black);
			if (m_alt.bMarkA%3==1)
				gr->DrawString(L"ü",-1,&f,PointF(rcC1.X-14,rcC1.Y),NULL,&br);
			else if (m_alt.bMarkA%3==2)
				gr->DrawString(L"û",-1,&f,RectF(rcC1.X-14,rcC1.Y,16,16),NULL,&br);
		}
		if (m_alt.bMarkB%3)
		{
			Gdiplus::Font f(L"Wingdings", m_Font->GetSize());
			SolidBrush br(Color::Black);
			if (m_alt.bMarkB%3==1)
				gr->DrawString(L"ü",-1,&f,PointF(rcC2.X-14,rcC1.Y),NULL,&br);
			else if (m_alt.bMarkB%3==2)
				gr->DrawString(L"û",-1,&f,RectF(rcC2.X-14,rcC1.Y,16,16),NULL,&br);
		}
		if (m_alt.bMarkC%3)
		{
			Gdiplus::Font f(L"Wingdings", m_Font->GetSize());
			SolidBrush br(Color::Black);
			if (m_alt.bMarkC%3==1)
				gr->DrawString(L"ü",-1,&f,PointF(rcC3.X-14,rcC1.Y),NULL,&br);
			else if (m_alt.bMarkC%3==2)
				gr->DrawString(L"û",-1,&f,RectF(rcC3.X-14,rcC1.Y,16,16),NULL,&br);
		}
		if (m_alt.bMarkD%3)
		{
			Gdiplus::Font f(L"Wingdings", m_Font->GetSize());
			SolidBrush br(Color::Black);
			if (m_alt.bMarkD%3==1)
				gr->DrawString(L"ü",-1,&f,PointF(rcC4.X-14,rcC1.Y),NULL,&br);
			else if (m_alt.bMarkD%3==2)
				gr->DrawString(L"û",-1,&f,RectF(rcC4.X-14,rcC1.Y,16,16),NULL,&br);
		}
	}

	RectF rcIndexF;
	SolidBrush br(Color::Black);
	Gdiplus::Font* f=SetFontStyle(m_Font,FontStyleBold);
	if (m_nIndex!=0) gr->MeasureString(IntToString(m_nIndex)+L". ",-1,f,PointF(0,0),&rcIndexF);
	if (m_nIndex!=0) gr->DrawString(IntToString(m_nIndex)+L". ",-1,f,PointF(MARGIN_LEFT-rcIndexF.Width,MARGIN_TOP+yQ),NULL,&br);
	delete f;

	gr->TranslateTransform(-pt.X,-pt.Y);
}
void CQuestItemABCD::ReDrawBmp(int width)
{
	PointF m_APos, m_BPos, m_CPos, m_DPos;

	RectF rcFBound, rcHint;
	int w=width-MARGIN_LEFT-MARGIN_RIGHT;

	Bitmap* bmp; Bitmap* bmpA; Bitmap* bmpB; Bitmap* bmpC; Bitmap* bmpD;
	int yA,yB,yC,yD,yH;

	DrawText(m_strQuest,bmp,w,yQ,rcFBound);

	if (m_bmpHint!=NULL) { delete m_bmpHint; m_bmpHint=NULL; }
	if (m_strHint!="") DrawText(L"[b]Hướng dẫn : [\\b]\r\n"+m_strHint,m_bmpHint,w,yH,rcHint);

	RectF rcFA,rcFB,rcFC,rcFD;


	int stdWidth2=(width-MARGIN_LEFT-MARGIN_RIGHT-ALTER_DIS)/2;
	int stdWidth4=(width-MARGIN_LEFT-MARGIN_RIGHT-3*ALTER_DIS)/4;
	DrawText(L"A. "+m_alt.A,bmpA,w,yA,rcFA);
	DrawText(L"B. "+m_alt.B,bmpB,w,yB,rcFB);
	DrawText(L"C. "+m_alt.C,bmpC,w,yC,rcFC);
	DrawText(L"D. "+m_alt.D,bmpD,w,yD,rcFD);

	int y;
	RectF rcFAl=GetTextBound(L"A",w,y);

	if (rcFA.Width<stdWidth4 && rcFB.Width<stdWidth4 && rcFC.Width<stdWidth4 && rcFD.Width<stdWidth4)
	{
		int m=max(yA,max(yB,max(yC,yD)));
		m_APos=PointF(MARGIN_LEFT,							rcFBound.Height+ALTER_QUEST_DIS+MARGIN_TOP + m-yA);
		m_BPos=PointF(MARGIN_LEFT+stdWidth4+ALTER_DIS,		rcFBound.Height+ALTER_QUEST_DIS+MARGIN_TOP + m-yB);
		m_CPos=PointF(MARGIN_LEFT+2*stdWidth4+2*ALTER_DIS,	rcFBound.Height+ALTER_QUEST_DIS+MARGIN_TOP + m-yC);
		m_DPos=PointF(MARGIN_LEFT+3*stdWidth4+3*ALTER_DIS,	rcFBound.Height+ALTER_QUEST_DIS+MARGIN_TOP + m-yD);
		height=rcFBound.Height + ALTER_QUEST_DIS + max(rcFA.Height,max(rcFB.Height,max(rcFC.Height,rcFD.Height))) + MARGIN_TOP*2;
	}
	else if (rcFA.Width<stdWidth2 && rcFB.Width<stdWidth2 && rcFC.Width<stdWidth2 && rcFD.Width<stdWidth2)
	{
		int m1=max(yA,yB);
		int m2=max(yC,yD);
		m_APos=PointF(MARGIN_LEFT,							rcFBound.Height+ALTER_QUEST_DIS+MARGIN_TOP+m1-yA);
		m_BPos=PointF(MARGIN_LEFT+stdWidth2+ALTER_DIS,		rcFBound.Height+ALTER_QUEST_DIS+MARGIN_TOP+m1-yB);
		m_CPos=PointF(MARGIN_LEFT,							rcFBound.Height+ALTER_QUEST_DIS+LINE_SPACING+max(rcFA.Height,rcFB.Height)+MARGIN_TOP+m2-yC);
		m_DPos=PointF(MARGIN_LEFT+stdWidth2+ALTER_DIS,		rcFBound.Height+ALTER_QUEST_DIS+LINE_SPACING+max(rcFA.Height,rcFB.Height)+MARGIN_TOP+m2-yD);
		height=rcFBound.Height + ALTER_QUEST_DIS + max(rcFA.Height,rcFB.Height)+max(rcFC.Height,rcFD.Height) + LINE_SPACING + MARGIN_TOP*2;
	}
	else
	{
		m_APos=PointF(MARGIN_LEFT,rcFBound.Height+ALTER_QUEST_DIS+MARGIN_TOP);
		m_BPos=PointF(MARGIN_LEFT,rcFBound.Height+ALTER_QUEST_DIS+LINE_SPACING+rcFA.Height+MARGIN_TOP);
		m_CPos=PointF(MARGIN_LEFT,rcFBound.Height+ALTER_QUEST_DIS+2*LINE_SPACING+rcFA.Height+rcFB.Height+MARGIN_TOP);
		m_DPos=PointF(MARGIN_LEFT,rcFBound.Height+ALTER_QUEST_DIS+3*LINE_SPACING+rcFA.Height+rcFB.Height+rcFC.Height+MARGIN_TOP);
		height=rcFBound.Height + ALTER_QUEST_DIS + rcFA.Height + rcFB.Height + rcFC.Height + rcFD.Height + 3*LINE_SPACING + MARGIN_TOP*2;
	}


	if (m_bmp!=NULL) delete m_bmp;

	m_bmp=new Bitmap(width,height,PixelFormat32bppARGB);
	Graphics bGr(m_bmp);
	bGr.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush br(Color::Black);

	bGr.DrawImage(bmp,MARGIN_LEFT,MARGIN_TOP); delete bmp;

	bGr.DrawImage(bmpA,m_APos.X,m_APos.Y); delete bmpA;
	bGr.DrawImage(bmpB,m_BPos.X,m_BPos.Y); delete bmpB;
	bGr.DrawImage(bmpC,m_CPos.X,m_CPos.Y); delete bmpC;
	bGr.DrawImage(bmpD,m_DPos.X,m_DPos.Y); delete bmpD;

	rcC1=Rect(m_APos.X-3,m_APos.Y+yA,rcFAl.Height,rcFAl.Height);
	rcC2=Rect(m_BPos.X-3,m_BPos.Y+yB,rcFAl.Height,rcFAl.Height);
	rcC3=Rect(m_CPos.X-3,m_CPos.Y+yC,rcFAl.Height,rcFAl.Height);
	rcC4=Rect(m_DPos.X-3,m_DPos.Y+yD,rcFAl.Height,rcFAl.Height);
}
void CQuestItemABCD::Serialize(CArchive& ar)
{
	CQuestItemBase::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_strQuest;
		ar << m_alt.A;
		ar << m_alt.B;
		ar << m_alt.C;
		ar << m_alt.D;
		ar << m_strHint;
		ar << m_answer;
	}
	else
	{
		ar >> m_strQuest;
		ar >> m_alt.A;
		ar >> m_alt.B;
		ar >> m_alt.C;
		ar >> m_alt.D;
		ar >> m_strHint;
		ar >> m_answer;
	}
}
bool CQuestItemABCD::CheckMouseOver(int x, int y)
{
	Point pt(x,y);
	return (rcC1.Contains(pt) || rcC2.Contains(pt) || rcC3.Contains(pt) || rcC4.Contains(pt));
}
bool CQuestItemABCD::OnClick(int x, int y)
{
	Point pt(x,y);
	if (m_Mode==ShowAnswer)
	{
		if (rcC1.Contains(pt))		m_answer=m_answer==1 ? 0 : 1;
		else if (rcC2.Contains(pt)) m_answer=m_answer==2 ? 0 : 2;
		else if (rcC3.Contains(pt)) m_answer=m_answer==3 ? 0 : 3;
		else if (rcC4.Contains(pt)) m_answer=m_answer==4 ? 0 : 4;
		else return false;
		return true;
	}
	else if (m_Mode==UserAnswer)
	{
		if (rcC1.Contains(pt))		m_userAns=m_userAns==1 ? 0 : 1;
		else if (rcC2.Contains(pt)) m_userAns=m_userAns==2 ? 0 : 2;
		else if (rcC3.Contains(pt)) m_userAns=m_userAns==3 ? 0 : 3;
		else if (rcC4.Contains(pt)) m_userAns=m_userAns==4 ? 0 : 4;
		else return false;
		return m_userAns!=0;
	}
}
bool CQuestItemABCD::OnMark(int x, int y)
{
	if (m_userAns!=0) return false;
	Point pt(x,y);
	if (rcC1.Contains(pt)) m_alt.bMarkA++;
	else if (rcC2.Contains(pt)) m_alt.bMarkB++;
	else if (rcC3.Contains(pt)) m_alt.bMarkC++;
	else if (rcC4.Contains(pt)) m_alt.bMarkD++;
	else return false;
	return true;
}
void CQuestItemABCD::ReCalcHeight()
{
	if (m_bShowHint && !m_bShowOnRightAns)
	{
		m_bShowHint=(m_userAns!=m_answer);
	}
	if (m_bShowHint && m_bmpHint!=NULL) height=m_bmp->GetHeight() + m_bmpHint->GetHeight()+MARGIN_TOP;
	else if (m_bmp!=NULL) height=m_bmp->GetHeight();
}
void CQuestItemABCD::WriteScriptData(CStdioFile& f,CString imageFolder, CString index, int& imgIndex)
{
	f.WriteString(L"itType[" + index + L"]=2;\n");
	f.WriteString(L"textArr[" + index + L"]=\"" + ToHTML(m_strQuest,imageFolder,imgIndex) + L"\";\n");

	f.WriteString(L"choices[" + index + L"]=new Array();\n");
	f.WriteString(L"choices[" + index + L"][0]=\"" + ToHTML(m_alt.A,imageFolder,imgIndex) + L"\";\n");
	f.WriteString(L"choices[" + index + L"][1]=\"" + ToHTML(m_alt.B,imageFolder,imgIndex) + L"\";\n");
	f.WriteString(L"choices[" + index + L"][2]=\"" + ToHTML(m_alt.C,imageFolder,imgIndex) + L"\";\n");
	f.WriteString(L"choices[" + index + L"][3]=\"" + ToHTML(m_alt.D,imageFolder,imgIndex) + L"\";\n");
	f.WriteString(L"answers[" + index + L"]=" + IntToString(m_answer-1) + L";\n");
	f.WriteString(L"hint[" + index + L"]=\"" + ToHTML(m_strHint,imageFolder,imgIndex) + L"\";\n");
}
void CQuestItemABCD::DisposeBmp()
{
	CItemBase::DisposeBmp(); if (m_bmpHint) { delete m_bmpHint; m_bmpHint=NULL; }
}


void CQuestItemABCD::Edit(CWnd* pWnd)
{
	CDlgAddQuestion dlg;
	dlg.m_Question.m_Text=m_strQuest;
	dlg.m_AnsArr.Add(m_alt.A);
	dlg.m_AnsArr.Add(m_alt.B);
	dlg.m_AnsArr.Add(m_alt.C);
	dlg.m_AnsArr.Add(m_alt.D);
	dlg.m_Hint.m_Text=m_strHint;
	dlg.ans=m_answer;

	if (dlg.DoModal()==IDOK)
	{
		m_strQuest=dlg.m_Question.m_Text;
		m_alt.A=dlg.m_AnsArr[0];
		m_alt.B=dlg.m_AnsArr[1];
		m_alt.C=dlg.m_AnsArr[2];
		m_alt.D=dlg.m_AnsArr[3];
		m_strHint=dlg.m_Hint.m_Text;
		m_answer=dlg.ans;
	}
}
