#include "stdafx.h"
#include "Item.h"
#include "DlgAddCont.h"

void CContainerItemStart::ReDrawBmp(int width)
{
	RectF rcFBound;
	int w=width-MARGIN_LEFT-MARGIN_RIGHT;
	int yT;
	rcFBound=GetTextBound(m_strText,w,yT);

	height=rcFBound.Height+MARGIN_TOP*2;

	if (m_bmp!=NULL) delete m_bmp;

	m_bmp=new Bitmap(width,height,PixelFormat32bppARGB);
	Graphics bGr(m_bmp);
	bGr.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush br(Color::Black);

	Bitmap* bmp=CMathDraw::Draw_Text(m_strText,m_Font,width-MARGIN_LEFT-MARGIN_RIGHT,yT);
	bGr.DrawImage(bmp,MARGIN_LEFT,MARGIN_TOP);
	delete bmp;
}
void CContainerItemStart::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strText;
		ar << m_nStdType;
	}
	else
	{
		ar >> m_strText;
		ar >> m_nStdType;
	}
}
void CContainerItemStart::Draw(Graphics* gr, Point pt , int width, bool bHighlight)
{
	CItemBase::Draw(gr,pt,width,bHighlight);
	if (bHighlight)
	{
		//Rect rc2(pt,Size(width,height));
		//SolidBrush br(Color(240,240,240));
		//gr->FillRectangle(&br,rc2);
		//Pen p(Color::Gray,1);
		//gr->DrawRectangle(&p,rc2);

		Rect rc(pt,Size(width,drawHeight));
		rc.Inflate(1,0);
		Pen pen(Color::DarkBlue,2);
		gr->DrawRectangle(&pen,rc);
	}
	gr->DrawImage(m_bmp,pt);
}
void CContainerItemStart::WriteScriptData(CStdioFile& f,CString imageFolder, CString index, int& imgIndex)
{
	f.WriteString(L"itType[" + index + L"]=3;\n");
	f.WriteString(L"textArr[" + index + L"]=\"" + ToHTML(m_strText,imageFolder,imgIndex) + L"\";\n");
}

void CContainerItemEnd::ReDrawBmp( int width )
{
	height=MARGIN_TOP;
}
void CContainerItemEnd::Serialize( CArchive& ar )
{

}
void CContainerItemEnd::Draw(Graphics* gr, Point pt , int width, bool bHighlight)
{
	// 	if (bHighlight)
	// 	{
	// 		Rect rc(pt,Size(width,height));
	// 		SolidBrush br(Color::LightYellow);
	// 		gr->FillRectangle(&br,rc);
	// 		Pen pen(Color::Gray);
	// 		gr->DrawRectangle(&pen,rc);
	// 	}
}

void CContainerItemStart::Edit(CWnd* pWnd)
{
	CDlgAddCont dlg(pWnd);
	dlg.m_Text.m_Text=m_strText;
	dlg.m_nStdType=m_nStdType+1;

	if (dlg.DoModal()==IDOK)
	{
		m_strText=dlg.m_Text.m_Text;
		m_nStdType=dlg.m_nStdType-1;
	}
}
