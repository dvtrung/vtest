#include "stdafx.h"
#include "Item.h"
#include "../MathRender/MathDraw.h"

CString CItemBase::ToHTML(CString str, CString imageFolder, int& imgIndex)
{
	str.Replace(L"[b]",L"<b>");
	str.Replace(L"[/b]",L"</b>");
	str.Replace(L"[\\b]",L"</b>");
	str.Replace(L"[i]",L"<i>");
	str.Replace(L"[/i]",L"</i>");
	str.Replace(L"[\\i]",L"</i>");
	str.Replace(L"[u]",L"<u>");
	str.Replace(L"[/u]",L"</u>");
	str.Replace(L"[\\u]",L"</u>");
	str.Replace(L"\"",L"\\\"");

	int pos=0;
	pos=str.Find(L"[center]");
	while (pos!=-1)
	{
		str.Delete(pos,8);
		str.Insert(pos,L"<div style=\\\"text-align:center\\\">");
		int pos2=str.Find(L"\n",pos+1);
		if (pos2==-1) pos2=str.GetLength()+1;
		str.Insert(pos2-1,L"</div>");
		pos=str.Find(L"[center]",pos2+1);
	}

	str.Replace(L"\r\n",L"<br>");
	str.Replace(L"\n",L"<br>");
	
	int pos1=0;
	pos1=str.Find(L"$",pos1);
	int pos2=0;
	Gdiplus::Font font(L"Times New Roman",12);
	int yPos;
	while (pos1!=-1)
	{
		pos2=str.Find(L"$",pos1+1);
		if (pos2==-1) pos2=str.GetLength();
		CString strMid=str.Mid(pos1,pos2-pos1+1);
		Bitmap* bmp=CMathDraw::Draw_Text(strMid,&font,-1,yPos);
		CLSID jpgClsid;
		GetEncoderClsid(L"image/png", &jpgClsid);
		bmp->Save(imageFolder+IntToString(imgIndex)+L".png", &jpgClsid, NULL);
		str.Delete(pos1,pos2-pos1+1);
		Graphics gr(bmp);
		int x=-((bmp->GetHeight()+yPos)*72/gr.GetDpiY()-12)-4;
		str.Insert(pos1,L"<img src=\\\"image/"+IntToString(imgIndex)+L".png\\\" style=\\\"vertical-align: " + 
			IntToString(x) + L"px\\\" />");
		pos2=pos1;
		pos1=str.Find(L"$",pos1);
		delete bmp;
	}

	return str;
}


void CItemBase::Draw( Graphics* gr, Point pt, int width , bool bHighlight)
{
	if (bHighlight)
	{
		Rect rc(pt,Size(width,height));
		//SolidBrush br(Color(240,240,240));
		LinearGradientBrush br(rc,Color::AliceBlue,Color(255,255,255),LinearGradientModeVertical);
		gr->FillRectangle(&br,rc);
		Pen pen(Color::Gray);
		gr->DrawRectangle(&pen,rc);
	}
	gr->DrawImage(m_bmp,pt);
}

void CItemBase::DisposeBmp()
{
	if (m_bmp) { delete m_bmp; m_bmp=NULL; }
}

RectF CItemBase::GetTextBound( CString strText, int width, int& y )
{
	Bitmap* bmp=CMathDraw::Draw_Text(strText,m_Font,width,y);
	y=-y;
	RectF rcf; Unit u; bmp->GetBounds(&rcf,&u);
	delete bmp;
	return rcf;
}

void CItemBase::DrawText( CString strText, Bitmap*& bmp, int width, int& y, RectF& rcF )
{
	bmp=CMathDraw::Draw_Text(strText,m_Font,width,y);
	y=-y;
	Unit u; bmp->GetBounds(&rcF,&u);
}
