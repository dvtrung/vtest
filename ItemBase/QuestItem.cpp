#include "stdafx.h"
#include "Item.h"


void CQuestItem::ReDrawBmp( int width )
{
	RectF rcFBound, rcHint;
	int yH;
	int w=width-MARGIN_LEFT-MARGIN_RIGHT;
	rcFBound=GetTextBound(m_strText,w,yQ);

	height=rcFBound.Height+MARGIN_TOP*2;

	if (m_bmp!=NULL) delete m_bmp;

	m_bmp=new Bitmap(width,height,PixelFormat32bppARGB);
	Graphics bGr(m_bmp);
	bGr.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush br(Color::Black);

	Bitmap* bmp=CMathDraw::Draw_Text(m_strText,m_Font,width-MARGIN_LEFT-MARGIN_RIGHT,yQ);
	bGr.DrawImage(bmp,MARGIN_LEFT,MARGIN_TOP);
	delete bmp;

	if (m_bmpHint!=NULL) { delete m_bmpHint; m_bmpHint=NULL; }
	if (m_strHint!="") DrawText(L"[b]Hướng dẫn : [\\b]\r\n"+m_strHint,m_bmpHint,w,yH,rcHint);
}
void CQuestItem::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar << m_strText;
		ar << m_strHint;
		ar << m_nIndex;
	}
	else
	{
		ar >> m_strText;
		ar >> m_strHint;
		ar >> m_nIndex;
	}
}
void CQuestItem::DisposeBmp()
{
	CItemBase::DisposeBmp(); if (m_bmpHint) { delete m_bmpHint; m_bmpHint=NULL; }
}
void CQuestItem::WriteScriptData(CStdioFile& f,CString imageFolder,CString index, int& imgIndex)
{
	f.WriteString(L"itType[" + index + L"]=1;\n");
	f.WriteString(L"textArr[" + index + L"]=\"" + ToHTML(m_strText,imageFolder,imgIndex) + L"\";\n");
}
void CQuestItem::Draw(Graphics* gr, Point pt, int width , bool bHighlight)
{
	CItemBase::Draw(gr,pt,width,bHighlight);

	gr->TranslateTransform(pt.X,pt.Y);

	if (m_bShowHint && m_bmpHint!=NULL) gr->DrawImage(m_bmpHint,MARGIN_LEFT,m_bmp->GetHeight());

	if (m_nIndex!=-1)
	{
		RectF rcIndexF;
		SolidBrush br(Color::Black);
		Gdiplus::Font* f=SetFontStyle(m_Font,FontStyleBold);
		gr->MeasureString(IntToString(m_nIndex)+L". ",-1,f,PointF(0,0),&rcIndexF);
		gr->DrawString(IntToString(m_nIndex)+L". ",-1,f,PointF(MARGIN_LEFT-rcIndexF.Width,MARGIN_TOP-yQ),NULL,&br);
		delete f;
	}
	gr->TranslateTransform(-pt.X,-pt.Y);
}
void CQuestItem::ReCalcHeight()
{
	//if (m_bShowHint && !m_bShowOnRightAns)
	//{
	//	m_bShowHint=(m_userAns!=m_answer);
	//}
	if (m_bShowHint && m_bmpHint!=NULL) height=m_bmp->GetHeight() + m_bmpHint->GetHeight()+MARGIN_TOP;
	else if (m_bmp!=NULL) height=m_bmp->GetHeight();
}
void CQuestItem::Edit(CWnd* pWnd)
{

}