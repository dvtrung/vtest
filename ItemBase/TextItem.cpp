#include "stdafx.h"
#include "Item.h"
#include "DlgAddText.h"

void CTextItem::ReDrawBmp(int width)
{
	RectF rcFBound;
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
}
void CTextItem::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strText;
		ar << m_nIndex;
	}
	else
	{
		ar >> m_strText;
		ar >> m_nIndex;
	}
}
void CTextItem::Draw(Graphics* gr, Point pt, int width , bool bHighlight)
{
	CItemBase::Draw(gr,pt,width,bHighlight);

	if (m_nIndex!=-1)
	{
		gr->TranslateTransform(pt.X,pt.Y);
		RectF rcIndexF;
		SolidBrush br(Color::Black);
		Gdiplus::Font* f=SetFontStyle(m_Font,FontStyleBold);
		gr->MeasureString(IntToString(m_nIndex)+L". ",-1,f,PointF(0,0),&rcIndexF);
		gr->DrawString(IntToString(m_nIndex)+L". ",-1,f,PointF(MARGIN_LEFT-rcIndexF.Width,MARGIN_TOP-yQ),NULL,&br);
		delete f;
		gr->TranslateTransform(-pt.X,-pt.Y);
	}
}

void CTextItem::WriteScriptData(CStdioFile& f,CString imageFolder,CString index, int& imgIndex)
{
	f.WriteString(L"itType[" + index + L"]=1;\n");
	f.WriteString(L"textArr[" + index + L"]=\"" + ToHTML(m_strText,imageFolder,imgIndex) + L"\";\n");
}

void CTextItem::Edit(CWnd* pWnd)
{
	CDlgAddText dlg(pWnd);
//	dlg.m_Text.m_Text=m_strText;

	if (dlg.DoModal()==IDOK)
	{
//		m_strText=dlg.m_Text.m_Text;
	}
}
