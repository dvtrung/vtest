#include "stdafx.h"
#include "MathDraw.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////
//
// MDrawingSurface class
//
//////////////////////////////////////////////////////////////////////////

CMathDraw::MDrawingSurface::MDrawingSurface(Gdiplus::Font* font)
{
	m_Font=font;
}

//Cần cải thiện để tăng tốc độ
void CMathDraw::MDrawingSurface::DrawBracket(int type,Point pt,int width,int height,Graphics* gr,Color clr)
{
	Pen pen(clr);
	if (type==1) // (
	{
		if (width>0) gr->DrawArc(&pen,pt.X,pt.Y,2*width,height,90,180);
		else gr->DrawArc(&pen,pt.X+width,pt.Y,-2*width,height,90,-180);
		// 	if (width>0)
		// 	{
		// 		gr->DrawArc(&pen,pt.X,pt.Y,2*width,2*width,180,90);
		// 		gr->DrawArc(&pen,pt.X,pt.Y+height-2*width,2*width,2*width,90,90);
		// 		gr->DrawLine(&pen,pt.X,pt.Y+width,pt.X,pt.Y+height-width);
		// 	}
		//  	int y=pt2.Y;
		//  	int x=(pow(float(y-pt1.Y),2)+pt1.X*pt1.X-pt2.X*pt2.X)/(2*(pt1.X-pt2.X));
		//  	int r=x-pt2.X;
		// 	Rect rect;
		//  	if (r>=0) rect=Rect(pt2.X,y-r,2*r,2*r);	
		// 	else rect=Rect(pt2.X+2*r,y+r,-2*r,-2*r);
		// 	REAL ang=180*acos(1-(pow(float(pt1.X-pt2.X),2)+pow(float(pt1.Y-pt2.Y),2))/(2*r*r))/pi;
		// 	Pen pen(Color::Black);
		// 	//gr->DrawEllipse(&pen,rect);
		// 	if (pt2.X<pt1.X) gr->DrawArc(&pen,rect,(180-ang),2*ang);
		// 	else gr->DrawArc(&pen,rect,ang,-2*ang);
	}
	else if (type==2) // [
	{
		if (width>0)
		{
			gr->DrawLine(&pen,pt,Point(pt.X+width,pt.Y));
			gr->DrawLine(&pen,pt,Point(pt.X,pt.Y+height));
			gr->DrawLine(&pen,Point(pt.X,pt.Y+height),Point(pt.X+width,pt.Y+height));
		}
	}
	else if (type==3) // {
	{
		if (width>0)
		{
			gr->DrawArc(&pen,Rect(pt.X+width/2,pt.Y,width,width),180,90);
			gr->DrawLine(&pen,Point(pt.X+width/2,pt.Y+width/2),Point(pt.X+width/2,pt.Y+height/2-width/2));
			gr->DrawArc(&pen,Rect(pt.X-width/2,pt.Y+height/2-width,width,width),0,90);
			gr->DrawArc(&pen,Rect(pt.X-width/2,pt.Y+height/2,width,width),0,-90);
			gr->DrawLine(&pen,Point(pt.X+width/2,pt.Y+width/2+height/2),Point(pt.X+width/2,pt.Y+height-width/2));
			gr->DrawArc(&pen,Rect(pt.X+width/2,pt.Y+height-width,width,width),180,-90);
		}
	}
}

void CMathDraw::MDrawingSurface::AddLine(Point pt1,Point pt2,Color lineClr)
{
	m_Pt1.push_back(pt1);
	m_Pt2.push_back(pt2);
	m_LineColor.push_back(lineClr);
}

void CMathDraw::MDrawingSurface::AddBracket(int type, Point pt,int brWidth, int brHeight)
{
	m_BrType.push_back(type);
	m_BrPt.push_back(pt);
	m_BrWidth.push_back(brWidth);
	m_BrHeight.push_back(brHeight);
}

void CMathDraw::MDrawingSurface::AddString(CString str, PointF pt, int fontSize, bool bBold, bool bItalic, bool bUnderline, Color color)
{
	m_String.push_back(str);
	m_StringPos.push_back(pt);
	m_FontSize.push_back(fontSize);
	m_StringItalic.push_back(bItalic);
	m_StringBold.push_back(bBold);
	m_StringUnderline.push_back(bUnderline);
	m_StringColor.push_back(color);
}

void CMathDraw::MDrawingSurface::AddSymbol(CString str, PointF pt, int fontSize)
{
	m_Symbol.push_back(str);
	m_SymbolPos.push_back(pt);
	m_SymbolFontSize.push_back(fontSize);
}

void CMathDraw::MDrawingSurface::AddBitmap(Bitmap* bmp, Point pos)
{
	m_Bmp.push_back(bmp);
	m_bmpPos.push_back(pos);
}


void CMathDraw::MDrawingSurface::AddDr(MDrawingSurface* gr)
{
	m_Dr.push_back(*gr);
}

void CMathDraw::MDrawingSurface::Translate(int x, int y)
{
	Point pt(x,y);
	for (int i=0;i<m_Pt1.size();i++) {
		m_Pt1[i]=m_Pt1[i]+pt;
		m_Pt2[i]=m_Pt2[i]+pt;
	}
	for (int i=0;i<m_BrPt.size();i++) m_BrPt[i]=m_BrPt[i]+pt;
	for (int i=0;i<m_bmpPos.size();i++) m_bmpPos[i]=m_bmpPos[i]+pt;
	for (int i=0;i<m_StringPos.size();i++) m_StringPos[i]=m_StringPos[i]+PointF(pt.X,pt.Y);
	for (int i=0;i<m_SymbolPos.size();i++) m_SymbolPos[i]=m_SymbolPos[i]+PointF(pt.X,pt.Y);
	for (int i=0;i<m_Dr.size();i++) m_Dr[i].Translate(pt.X,pt.Y);
}

void CMathDraw::MDrawingSurface::Draw(Graphics* gr)
{
	StringFormat sf(StringFormat::GenericTypographic()); 

	for (int i=0;i<m_Pt1.size();i++)
	{
		Pen pen(m_LineColor[i]);
		gr->DrawLine(&pen,m_Pt1[i],m_Pt2[i]);
	}
	for (int i=0;i<m_BrPt.size();i++)
	{
		DrawBracket(m_BrType[i],m_BrPt[i],m_BrWidth[i],m_BrHeight[i],gr,Color::Black);
	}
	for (int i=0;i<m_StringPos.size();i++)
	{
		SolidBrush solidBrush(m_StringColor[i]);

		FontFamily family; m_Font->GetFamily(&family);
		int fs=FontStyleRegular; if (m_StringBold[i]) fs=fs|FontStyleBold; if (m_StringItalic[i]) fs=fs|FontStyleItalic; if (m_StringUnderline[i]) fs=fs|FontStyleUnderline;
		Gdiplus::Font font(&family,m_FontSize[i],fs,m_Font->GetUnit());

		gr->DrawString(m_String[i],-1,&font,m_StringPos[i],&sf,&solidBrush);

// 		RectF rc;
// 		gr->MeasureString(m_String[i],-1,&font,m_StringPos[i],&sf,&rc);
// 		Pen pen(Color::Black);
// 		gr->DrawRectangle(&pen,rc);
	}
	for (int i=0;i<m_SymbolPos.size();i++)
	{
		SolidBrush solidBrush(Color::Black);

		Gdiplus::Font font(L"Symbol",m_SymbolFontSize[i],m_Font->GetStyle(),m_Font->GetUnit());
		gr->DrawString(m_Symbol[i],-1,&font,m_SymbolPos[i],NULL,&solidBrush);
	}
	for (int i=0;i<m_bmpPos.size();i++)
	{
		gr->DrawImage(m_Bmp[i],m_bmpPos[i].X,m_bmpPos[i].Y);
	}
	for (int i=0;i<m_Dr.size();i++)
	{
		m_Dr[i].Draw(gr);
	}
}

Rect CMathDraw::MDrawingSurface::GetBounds(Graphics* gr)
{
	StringFormat sf(StringFormat::GenericTypographic()); 

	int t/*,l*/,b,r,i;
	t=b=r=0;
	for (i=0;i<m_Pt1.size();i++)
	{
		if (t>m_Pt1[i].Y) t=m_Pt1[i].Y; //if (l>m_Pt1[i].Y) l=m_Pt1[i].Y;
		if (t>m_Pt2[i].Y) t=m_Pt2[i].Y; //if (l>m_Pt2[i].Y) l=m_Pt2[i].Y;
		if (b<m_Pt1[i].Y) b=m_Pt1[i].Y; if (r<m_Pt1[i].X) r=m_Pt1[i].X;
		if (b<m_Pt2[i].Y) b=m_Pt2[i].Y; if (r<m_Pt2[i].X) r=m_Pt2[i].X;
	}

	RectF stringRect;
	for (i=0;i<m_StringPos.size();i++)
	{
		FontFamily family; m_Font->GetFamily(&family);
		int fs=FontStyleRegular; if (m_StringBold[i]) fs=fs|FontStyleBold; if (m_StringItalic[i]) fs=fs|FontStyleItalic; if (m_StringUnderline[i]) fs=fs|FontStyleUnderline;
		Gdiplus::Font font(&family,m_FontSize[i],fs,m_Font->GetUnit());
		gr->MeasureString(m_String[i],-1,&font,m_StringPos[i],&sf,&stringRect);
		if (stringRect.Y<t) t=stringRect.Y;
		if (stringRect.GetBottom()>b) b=stringRect.GetBottom();
		if (stringRect.GetRight()>r) r=stringRect.GetRight();
	}

	for (i=0;i<m_SymbolPos.size();i++)
	{
		Gdiplus::Font font(L"Symbol",m_SymbolFontSize[i],m_Font->GetStyle(),m_Font->GetUnit());
		gr->MeasureString(m_Symbol[i],-1,&font,m_SymbolPos[i],&stringRect);
		if (stringRect.Y<t) t=stringRect.Y;
		if (stringRect.GetBottom()>b) b=stringRect.GetBottom();
		if (stringRect.GetRight()>r) r=stringRect.GetRight();
	}

	Rect rect(0,t,r,b-t);

	for (i=0;i<m_bmpPos.size();i++)
	{
		Rect::Union(rect,rect,Rect(m_bmpPos[i].X,m_bmpPos[i].Y,m_Bmp[i]->GetWidth(),m_Bmp[i]->GetHeight()));
	}

	for (i=0;i<m_BrPt.size();i++)
	{
		Rect::Union(rect,rect,Rect(m_BrPt[i].X,m_BrPt[i].Y,abs(m_BrWidth[i]),m_BrHeight[i]));
	}

	for (i=0;i<m_Dr.size();i++)
	{
		Rect::Union(rect,rect,m_Dr[i].GetBounds(gr));
	}
	return Rect(rect.X-1,rect.Y,rect.Width,rect.Height+1);
}

CMathDraw::MDrawingSurface::~MDrawingSurface()
{
	for (int i=0;i<m_Bmp.size();i++)
		delete m_Bmp[i];
}

//////////////////////////////////////////////////////////////////////////
//
// CMathDraw
//
//////////////////////////////////////////////////////////////////////////

CMathDraw::CMathDraw()
{

}

CMathDraw::~CMathDraw()
{

}

Bitmap* CMathDraw::DrawLine(CString strText, Graphics* gr, bool& bModeMath, bool& bBold, bool& bItalic, bool& bUnderline,Color& clr, int* yPos)
{
	CArray<MDrawingSurface*>MgrArr;
	int EndCh=-1;
	bool kt=true;
	CString str=strText;
	XuLyChuoi(str);
	bool b=false;
	bool bCenter=false;
	bool bRight=false;
	if (str.Left(8)==L"[center]")  { bCenter=true; str.Delete(0,8); }
	if (str.Left(7)==L"[right]")  { bRight=true; str.Delete(0,7); }
	while (kt)
	{
		MDrawingSurface* Mgr=new MDrawingSurface(font);
		MgrArr.Add(Mgr);
		int y=DrawExp(str,font->GetSize(),Mgr,bModeMath,bBold,bItalic,bUnderline,clr,&EndCh); if (!b && yPos!=NULL) { *yPos=y; b=true; }
		if (EndCh==-1) kt=false;
		else { str.Delete(0,EndCh); EndCh=-1; }
	}
	
	int h=0; int w=0;
	for (int i=0;i<MgrArr.GetSize();i++)
	{
		Rect rect=MgrArr[i]->GetBounds(gr);
		h+=rect.Height;
		if (w<rect.Width) w=rect.Width;
	}

	Bitmap* outBitmap=new Bitmap((bCenter||bRight) ? (wlimit==-1? w : wlimit) : w,h,PixelFormat32bppARGB);
	Graphics grbmp(outBitmap);
	
	grbmp.SetTextRenderingHint(TextRenderingHintAntiAlias);
	grbmp.SetSmoothingMode(SmoothingModeAntiAlias);

	int t=0;
	Rect rect;
	for (int i=0;i<MgrArr.GetSize();i++)
	{
		rect=MgrArr[i]->GetBounds(gr);
		if (bCenter) grbmp.TranslateTransform((outBitmap->GetWidth()-rect.Width)/2,0);
		if (bRight) grbmp.TranslateTransform((outBitmap->GetWidth()-rect.Width),0);
		MgrArr[i]->Draw(&grbmp);
		if (bCenter) grbmp.TranslateTransform(-(outBitmap->GetWidth()-rect.Width)/2,0);
		if (bCenter) grbmp.TranslateTransform((outBitmap->GetWidth()-rect.Width),0);
		grbmp.TranslateTransform(0,rect.Height);
		delete MgrArr[i];
	}
	return outBitmap;
}

Bitmap* CMathDraw::DrawText(CString text, int& yPos)
{
	bool bModeMath=false;
	bool bItalic=false; bool bBold=false; bool bUnderline=false; Color clr=Color::Black;

	int i=0;
	CArray<Bitmap*> m_bmpArr;
	CArray<BOOL> m_bCenter;
	graph=new Graphics(GetDesktopWindow());
	int y;

	while (i<text.GetLength())
	{
		int pos=text.Find(L"\r\n",i);
		if (pos==-1) pos=text.GetLength();
		CString str=text.Mid(i,pos-i);
		int j=0;
		BOOL modeLatexNewLine=FALSE;
		bool b=false;
		if (str==L"")
		{
			m_bmpArr.Add(NULL);
			m_bCenter.Add(FALSE);
		}
		while (j<str.GetLength())
		{
			if (!modeLatexNewLine)
			{
				int pos=str.Find(L"\\[",j);
				if (pos==-1) pos=str.GetLength();
				CString strLine=str.Mid(j,pos-j);
				if (b) m_bmpArr.Add(DrawLine(strLine,graph,bModeMath,bBold,bItalic,bUnderline,clr)); else { b=true; m_bmpArr.Add(DrawLine(strLine,graph,bModeMath,bBold,bItalic,bUnderline,clr,&y)); }
				if (m_bmpArr.GetSize()==1) yPos=y;
				m_bCenter.Add(FALSE);
				modeLatexNewLine=TRUE;
				j=pos+2;
			}
			else
			{
				int pos=str.Find(L"\\]",j);
				if (pos==-1) pos=str.GetLength();
				CString strLine=str.Mid(j,pos-j);
				if (b) m_bmpArr.Add(DrawLine(L"$"+strLine+L"$",graph,bModeMath,bBold,bItalic,bUnderline,clr)); else { b=true; m_bmpArr.Add(DrawLine(L"$"+strLine+L"$",graph,bModeMath,bBold,bItalic,bUnderline,clr,&y)); }
				if (m_bmpArr.GetSize()==1) yPos=y;
				m_bCenter.Add(TRUE);
				modeLatexNewLine=FALSE;
				j=pos+2;
			}
		}
		i=pos+2;
	}
	// DrawExpression các dòng lên Bitmap
	int h=0;
	int w=0;
	for (int i=0;i<m_bmpArr.GetSize();i++) { 
		h+=m_bmpArr[i] ? m_bmpArr[i]->GetHeight() : font->GetSize(); 
		if (m_bmpArr[i]) w=max(w,m_bmpArr[i]->GetWidth()); 
	}
	Bitmap* outBitmap=new Bitmap(w,h,PixelFormat32bppARGB);
	Graphics gr(outBitmap);

	h=0;
	for (int i=0;i<m_bmpArr.GetSize();i++) {
		if (m_bmpArr[i])
		{
			if (!m_bCenter[i])
				gr.DrawImage(m_bmpArr[i],0,h,m_bmpArr[i]->GetWidth(),m_bmpArr[i]->GetHeight());
			else
				gr.DrawImage(m_bmpArr[i],(w-m_bmpArr[i]->GetWidth())/2,h,m_bmpArr[i]->GetWidth(),m_bmpArr[i]->GetHeight());
		}
		h+=(m_bmpArr[i] ? m_bmpArr[i]->GetHeight() : font->GetSize())+lineSpacing;
		if (m_bmpArr[i]) delete m_bmpArr[i];
	}

	//Pen pen(Color::Black);
	//graph.DrawRectangle(&pen,0,0,wLimit,outBitmap->GetHeight()-1);
	delete graph;

	return outBitmap;
}

// Bitmap* CMathDraw::DrawExpression(CString strExp, Color clr, Gdiplus::Font* font)
// {
// 	Graphics gr(AfxGetMainWnd()->m_hWnd);
// 
// 	MDrawingSurface Mgr(font);
// 	DrawExp(strExp,font->GetSize(),&Mgr,&gr,TRUE);
// 	Rect rect=Mgr.GetBounds(&gr);
// 
// 	Bitmap* outBitmap=new Bitmap(rect.Width,rect.Height,PixelFormat32bppARGB);
// 	Graphics grbmp(outBitmap);
// 
// 	Mgr.Draw(&grbmp,clr);
// 	return outBitmap;
// }

int CMathDraw::GetStringWidth(CString strText, Gdiplus::Font* font)
{
	FontFamily ff; font->GetFamily(&ff);
	WCHAR ffName[LF_FACESIZE];
	ff.GetFamilyName(ffName);
	CFont f; f.CreatePointFont(font->GetSize()*10,ffName);

	CDC* dc=AfxGetMainWnd()->GetDC();
	dc->SelectObject(&f);
	CSize s=dc->GetTextExtent(strText);
	return s.cx;
	//StringFormat strF(StringFormat::GenericTypographic());

	//StringFormat strF(StringFormat::GenericTypographic());
// 	StringFormat sf;// (StringFormat::GenericTypographic());
// 	CharacterRange* rng = new CharacterRange[strText.GetLength()];
// 	sf.SetMeasurableCharacterRanges(strText.GetLength(),rng);
// 
// 	int count = sf.GetMeasurableCharacterRangeCount();
// 
// 	RectF rct(0,0,100000.0f,font->GetHeight(graph));
// 	Region* rg=new Region[count];
// 	graph->MeasureCharacterRanges(strText,-1,rct,&sf,count,rg);
// 	SizeF sz;
	//if ( > 0)
	//{
// 	RectF rc;
// 	rg[0].GetBounds(&rc,graph);
// 	sz = SizeF(rc.Width+rc.X,rc.Height+rc.Y);
	//}
// 	delete[] rng;
// 	delete[] rg;
}

void CMathDraw::AddString(MDrawingSurface* gr, int fontSize, CString& strText, int& x, bool bBold, bool bItalic, bool bUnderline, Color color)
{
	//if (!bModeMath)
	{
		gr->AddString(strText,PointF(x,0),fontSize,bBold,bItalic,bUnderline,color);

		RectF outRect;
		FontFamily family; font->GetFamily(&family);
		int fs=FontStyleRegular; if (bBold) fs=fs|FontStyleBold; if (bItalic) fs=fs|FontStyleItalic; if (bUnderline) fs=fs|FontStyleUnderline;
		Gdiplus::Font f(&family,(REAL)fontSize,fs);

		StringFormat sf(StringFormat::GenericTypographic());
		graph->SetTextRenderingHint(TextRenderingHintAntiAlias);
		graph->MeasureString(strText,-1,&f,PointF(0,0),&sf,&outRect);

		int i=strText.GetLength()-1;
		while (i>=0 && strText[i]==' ') i--;
		i=strText.GetLength()-i-1;

		if (i>0)
		{
			RectF rc1; graph->MeasureString(L"! !",3,&f,PointF(0,0),&sf,&rc1);
			RectF rc2; graph->MeasureString(L"!!",2,&f,PointF(0,0),&sf,&rc2);
			x+=(rc1.Width-rc2.Width)*i;
		}
		
		x+=outRect.Width;
		//x+=GetStringWidth(strText,&f);
	}
// 	else
// 	{
// 		int i=0;
// 		int prev=0;
// 		bool bNum='0'<=strText[0] && strText[0]<='9';
// 		while (i<=strText.GetLength())
// 		{
// 			if ((bNum && (i==strText.GetLength() || !('0'<=strText[i] && strText[i]<='9'))) || 
// 				(!bNum && (i==strText.GetLength() || ('0'<=strText[i] && strText[i]<='9'))))
// 			{
// 				CString str=strText.Mid(prev,i-prev);
// 				bool bItalic;
// 				if (bNum) 
// 					bItalic=false;
// 				else
// 				{
// 					CString strFuncList=L"|sin|cos|tan|cot|arcsin|arccos|arctan|arccot|log|ln|";
// 					bItalic=(strFuncList.Find(L"|"+str+L"|")==-1);
// 				}
// 
// 				gr->AddString(str,PointF(x,0),fontSize,/*bItalic*/false); // Bo Italic
// 
// 				RectF outRect;
// 				FontFamily family; font->GetFamily(&family);
// 				Gdiplus::Font f(&family,(REAL)fontSize,font->GetStyle());
// 				graph->MeasureString(str,-1,&f,PointF(0,0),&outRect);
// 				x+=outRect.Width;
// 
// 				prev=i;
// 				bNum=!bNum;
// 			}
// 			i++;
// 		}
// 	}
	strText="";
}

void CMathDraw::AddSymbolString(MDrawingSurface* gr, int fontSize, CString strText, int& x)
{
	gr->AddSymbol(strText,PointF(x,-3),fontSize);

	RectF outRect;
	Gdiplus::Font f(L"Symbol",(REAL)fontSize,(INT)font->GetStyle());
	graph->MeasureString(strText,-1,&f,PointF(0,0),&outRect);
	x+=outRect.Width;
}

bool CMathDraw::CheckWidthLimit(MDrawingSurface* gr, int fontSize, CString strText, int& x, bool bModeMath)
{
	if (wlimit==-1) return true;
	if (!bModeMath)
	{
		RectF outRect;
		FontFamily family; font->GetFamily(&family);
		Gdiplus::Font f(&family,(REAL)fontSize,font->GetStyle());
		graph->MeasureString(strText,-1,&f,PointF(0,0),&outRect);
		if (x+outRect.Width>wlimit) return false;
	}
	else
	{
		int i=0;
		int prev=0;
		bool bNum='0'<=strText[0] && strText[0]<='9';
		while (i<=strText.GetLength())
		{
			if ((bNum && (i==strText.GetLength() || !('0'<=strText[i] && strText[i]<='9'))) || 
				(!bNum && (i==strText.GetLength() || ('0'<=strText[i] && strText[i]<='9'))))
			{
				CString str=strText.Mid(prev,i-prev);
				bool bItalic;
				if (bNum) 
					bItalic=false;
				else
				{
					CString strFuncList=L"|sin|cos|tan|cot|arcsin|arccos|arctan|arccot|log|ln|";
					bItalic=(strFuncList.Find(L"|"+str+L"|")==-1);
				}

				//gr->AddString(str,PointF(x,0),fontSize,bItalic);

				RectF outRect;
				FontFamily family; font->GetFamily(&family);
				Gdiplus::Font f(&family,(REAL)fontSize,font->GetStyle());
				graph->MeasureString(str,-1,&f,PointF(0,0),&outRect);
				if (x+outRect.Width>wlimit) return false;
				//x+=outRect.Width;

				prev=i;
				bNum=!bNum;
			}
			i++;
		}
	}
	return true;
	//strText="";
}

bool CMathDraw::CheckCTHH(CString& str, int start, int length, int& SoKTThemCTHH)
{
	for (int i=start;i<length+start;i++) if (!((str[i]>='0' && str[i]<='9') || IsLetter(str[i])|| (str[i]=='(' || str[i]==')'))) return false;
	if (!(IsLetter(str[start]) || str[start]=='(')) return false;
	int i;
	for (i=start;i<length+start;i++) if (str[i]>='0' && str[i]<='9') break;
	if (i==start+length) return false;
	int cc=0;
	for (int i=start;i<length+start-1+cc;i++) 
	{
		char c=str[i];
		if ((IsLetter(str[i]) || str[i]==')') && (str[i+1]>='0' && str[i+1]<='9')) 
		{ 
			str.Insert(i+1,'_'); i++; cc++;
			SoKTThemCTHH++;
		}
	}
	return true;
}

void CMathDraw::XuLyChuoi(CString& str)
{
	bool bMathMode=false;
	int i=0;
	while (i<str.GetLength())
	{
		if (!bMathMode)
		{
			if (str[i]=='$') bMathMode=true;
			i++;
		}
		else
		{
			if (str[i]=='$') { bMathMode=false; i++; }
			else
			{
				if ((str[i]>='0' && str[i]<='9') && (IsLetter(str[i-1]) || str[i-1]==')')) { str.Insert(i,'_'); i+=2; }
				else i++;
			}
		}
	}
}

int CMathDraw::DrawExp(CString strExp, int fontSize, MDrawingSurface* gr, bool& bMathMode, bool& bBold, bool& bItalic, bool& bUnderline, Color& clr, int* endCh)
{
	SolidBrush solidBrush(Color(255, 0, 0, 0));
	int i=0;
	int x=0;
	_TCHAR chr;
	CString strTmpText;
	int spaceWidth=fontSize/3;

	while (i<strExp.GetLength())
	{
		chr=strExp.GetAt(i);

		if (strExp.Mid(i,3)==L"[b]") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); bBold=true; i+=3; }
		else if (strExp.Mid(i,4)==L"[\\b]") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); bBold=false; i+=4; }

		else if (strExp.Mid(i,3)==L"[i]") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); bItalic=true; i+=3; }
		else if (strExp.Mid(i,4)==L"[\\i]") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); bItalic=false; i+=4; }

		else if (strExp.Mid(i,3)==L"[u]") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); bUnderline=true; i+=3; }
		else if (strExp.Mid(i,4)==L"[\\u]") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); bUnderline=false; i+=4; }

		else if (strExp.Mid(i,6)==L"[img=\"") {
			AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr);
			int pos=strExp.Find(']',i);
			if (pos==-1) pos=strExp.GetLength();
			CString strPath=strExp.Mid(i+6,pos-i-7);
			Bitmap* bmp=new Bitmap(strPath);
			gr->AddBitmap(bmp,Point(x,0));

			i=pos+1;
		}

		//else if (strExp.Mid(i,3)==L"[b]") { bBold=true; i+=3; }
		//else if (strExp.Mid(i,4)==L"[\b]") { bBold=true; i+=4; };

		else if (bMathMode)
		{
			TCHAR c;
			CString cmdName; CStringArray paraArr; int iAdd;
			GetNextCommand(strExp.Right(strExp.GetLength()-i),-1,cmdName,paraArr, iAdd);
			int pos1=GetNextExp(strExp.Right(strExp.GetLength()-i));
			if (pos1+i<strExp.GetLength() && strExp[pos1+i]=='/') {
				if (strTmpText!=L"") AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr);
				//else AddString(gr,fontSize,strTmpText=L" ",x,graph);
				int pos1=GetNextExp(strExp.Right(strExp.GetLength()-i));
				CString str1;
				if (strExp[i]=='(' || strExp[i]=='{') str1=strExp.Mid(i+1,pos1-2); else if (!IsNumber(str1)) goto NormalString;
				else str1=strExp.Mid(i,pos1);
				int pos2=GetNextExp(strExp.Right(strExp.GetLength()-i-pos1-1));
				CString str2;
				if (strExp[i+pos1+1]=='(' || strExp[i+pos1+1]=='{') str2=strExp.Mid(i+pos1+1+1,pos2-2); else if (!IsNumber(str1)) goto NormalString;
				else str2=strExp.Mid(i+pos1+1,pos2);

				MDrawingSurface tmpGr1(font);
				MDrawingSurface tmpGr2(font);
				DrawExp(str1,fontSize,&tmpGr1,bMathMode,bBold,bItalic,bUnderline,clr);
				DrawExp(str2,fontSize,&tmpGr2,bMathMode,bBold,bItalic,bUnderline,clr);

				Rect rect1=tmpGr1.GetBounds(graph);
				Rect rect2=tmpGr2.GetBounds(graph);

				int w=max(rect1.Width,rect2.Width);
				if (wlimit!=-1 && x+w>wlimit) goto ReachWidthLimit;

				x+=spaceWidth;
				gr->AddLine(Point(x,3*fontSize/4),Point(x+w,3*fontSize/4),clr);

				tmpGr1.Translate(x+(w-rect1.Width)/2,-rect1.Height+3*fontSize/4-4);
				tmpGr2.Translate(x+(w-rect2.Width)/2,3*fontSize/4+2);

				i+=pos1+pos2+1;
				
				x+=w; x+=spaceWidth;
				gr->AddDr(&tmpGr1); gr->AddDr(&tmpGr2);
			}
			else if (chr=='^') {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				int pos=GetNextExp(strExp.Right(strExp.GetLength()-i-1));
				CString str=strExp.Mid(i+1,pos);
				if (str.GetAt(0)=='(' || str.GetAt(0)=='{') str=str.Mid(1,str.GetLength()-2);
				int subFontSize=SubFontSize(fontSize); //Font nho
				MDrawingSurface tmpGr(font);
				DrawExp(str,subFontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr); //Ve cong thuc len tmpGr
				i+=pos+1;
				//Dat cong thuc vao dung vi tri
				Rect rect=tmpGr.GetBounds(graph);
				tmpGr.Translate(x,-rect.Height+fontSize*3/4);
				//Ve cong thuc
				gr->AddDr(&tmpGr);
				//Cach mot doan de them tiep cong thuc tiep
				x+=rect.Width+1;
			}
			else if (chr=='_') {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				int pos=GetNextExp(strExp.Right(strExp.GetLength()-i-1));
				CString str=strExp.Mid(i+1,pos);
				if (str.GetAt(0)=='(' || str.GetAt(0)=='{') str=str.Mid(1,str.GetLength()-2);
				int subFontSize=SubFontSize(fontSize); //Font nho
				MDrawingSurface tmpGr(font);
				DrawExp(str,subFontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr); //Ve cong thuc len tmpGr
				i+=pos+1;
				//Dat cong thuc vao dung vi tri
				Rect rect=tmpGr.GetBounds(graph);
				Matrix matrix;
				tmpGr.Translate(x,3*fontSize/4);
				//Ve cong thuc
				gr->AddDr(&tmpGr);
				//Cach mot doan de them tiep cong thuc tiep
				x+=rect.Width+1;
			}
			else if (0) { //(chr=='[' || chr=='(') 
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				//x+=spaceWidth;
				int pos=GetNextExp(strExp.Right(strExp.GetLength()-i));
				CString str=strExp.Mid(i+1,pos);
				if (strExp[i+pos-1]==(chr=='[' ? ']' : ')')) str=strExp.Mid(i+1,pos-2);
				else str=strExp.Mid(i+1,pos-1);
				if (str=="") str=" ";
				MDrawingSurface tmpGr(font);
				int top=DrawExp(str,fontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr);
				i+=pos;
				Rect rect=tmpGr.GetBounds(graph);
				int brLength;
				if (chr=='[')
				{
					brLength=fontSize/3;
					gr->AddLine(Point(x,top-2),Point(x+brLength,top-2),clr);
					gr->AddLine(Point(x,top-2),Point(x,top+rect.Height),clr);
					gr->AddLine(Point(x,top+rect.Height),Point(x+brLength,top+rect.Height),clr);

					if (strExp[i-1]==']')
					{
						x+=spaceWidth;
						gr->AddLine(Point(x+rect.Width+brLength,top-2),Point(x+rect.Width+2*brLength,top-2),clr);
						gr->AddLine(Point(x+rect.Width+2*brLength,top-2),Point(x+rect.Width+2*brLength,top+rect.Height),clr);
						gr->AddLine(Point(x+rect.Width+brLength,top+rect.Height),Point(x+rect.Width+2*brLength,top+rect.Height),clr);
						x-=spaceWidth;
					}
				}
				else if (chr=='(')
				{
					brLength=fontSize/2;
					gr->AddBracket(1,Point(x,top-2),brLength,rect.Height);

					if (strExp[i-1]==')')
					{
						x+=spaceWidth;
						gr->AddBracket(1,Point(x+brLength+rect.Width,top-2),-brLength,rect.Height);
						x-=spaceWidth;
					}
				}

				tmpGr.Translate(x+brLength,top);
				x+=rect.Width+3*brLength;
				gr->AddDr(&tmpGr);
			}
			else if (cmdName==L"frac" && paraArr.GetSize()==2) {
				if (strTmpText!=L"") AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr);

				MDrawingSurface tmpGr1(font); MDrawingSurface tmpGr2(font);
				DrawExp(paraArr[0],fontSize,&tmpGr1,bMathMode,bBold,bItalic,bUnderline,clr,endCh); Rect rect1=tmpGr1.GetBounds(graph);
				DrawExp(paraArr[1],fontSize,&tmpGr2,bMathMode,bBold,bItalic,bUnderline,clr,endCh); Rect rect2=tmpGr2.GetBounds(graph);

				int w=max(rect1.Width,rect2.Width);
				if (wlimit!=-1 && x+spaceWidth+w>wlimit) { goto ReachWidthLimit; }

				x+=spaceWidth; gr->AddLine(Point(x,3*fontSize/4),Point(x+w,3*fontSize/4),clr);

				tmpGr1.Translate(x+(w-rect1.Width)/2,-rect1.Height+3*fontSize/4-2);
				tmpGr2.Translate(x+(w-rect2.Width)/2,3*fontSize/4+4);

				i+=iAdd;
				x+=w; x+=spaceWidth;

				gr->AddDr(&tmpGr1); gr->AddDr(&tmpGr2);
			}
			else if (cmdName==L"array" || cmdName==L"arrayc") {
				if (strTmpText!=L"") AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr);

				int top;
				CArray<MDrawingSurface*,MDrawingSurface*> tmpGrArr;
				CArray<Rect,Rect> rcArr;

				for (int i=0;i<paraArr.GetSize();i++)
				{
					MDrawingSurface* tmpGr=new MDrawingSurface(font); tmpGrArr.Add(tmpGr);
					if (i==0) top=DrawExp(paraArr[i],fontSize,tmpGr,bMathMode,bBold,bItalic,bUnderline,clr);
					else DrawExp(paraArr[i],fontSize,tmpGr,bMathMode,bBold,bItalic,bUnderline,clr);
					rcArr.Add(tmpGr->GetBounds(graph));
				}
				int w=0;
				for (int i=0;i<tmpGrArr.GetSize();i++) if (w<rcArr[i].Width) w=rcArr[i].Width;
				if (wlimit!=-1 && x+w>wlimit) { goto ReachWidthLimit; }
				for (int i=0;i<paraArr.GetSize();i++)
				{
					if (cmdName==L"array") tmpGrArr[i]->Translate(x,top);
					else if (cmdName==L"arrayc") tmpGrArr[i]->Translate(x+(w-rcArr[i].Width)/2,top);
					top+=rcArr[i].Height;
					gr->AddDr(tmpGrArr[i]);
					delete tmpGrArr[i];
				}
				i+=iAdd; x+=w;
			}
			else if ((cmdName==L"and" || cmdName==L"or") && paraArr.GetSize()==1) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				x+=spaceWidth;
				MDrawingSurface tmpGr(font);
				int top = DrawExp(paraArr[0],fontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr);
				Rect rect=tmpGr.GetBounds(graph);
				int brLength;
				if (cmdName==L"or")
				{
					brLength=fontSize/3;
					gr->AddBracket(2,Point(x,3*fontSize/4-rect.Height/2),brLength,rect.Height);
				}
				else if (cmdName==L"and")
				{
					brLength=fontSize/2;
					gr->AddBracket(3,Point(x,3*fontSize/4-rect.Height/2),brLength,rect.Height);
					x+=spaceWidth/2;
				}
				else if (chr=='(')
				{
					brLength=fontSize/2;
					gr->AddBracket(1,Point(x,top-2),brLength,rect.Height);

					if (strExp[i-1]==')')
					{
						x+=spaceWidth;
						gr->AddBracket(1,Point(x+brLength+rect.Width,top-2),-brLength,rect.Height);
						x-=spaceWidth;
					}
				}

				tmpGr.Translate(x+brLength,3*fontSize/4-rect.Height/2);
				i+=iAdd;
				x+=rect.Width+3*brLength;
				gr->AddDr(&tmpGr);
			}
			else if (cmdName==L"sqrt" && paraArr.GetSize()==1) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				//Bieu thuc trong can
				x+=spaceWidth/2;
				MDrawingSurface tmpGr(font);
				int top=DrawExp(paraArr[0],fontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr,endCh);
				i+=iAdd;
				Rect rect=tmpGr.GetBounds(graph);
				int sqrtWidth=fontSize/3;
				gr->AddLine(Point(x+2*sqrtWidth,top-4),Point(x+2*sqrtWidth+rect.Width+spaceWidth/2,top-4),clr);
				gr->AddLine(Point(x+2*sqrtWidth,top-4),Point(x+sqrtWidth,top+rect.Height),clr);
				gr->AddLine(Point(x+sqrtWidth,top+rect.Height),Point(x,top+rect.Height*7/12),clr);
				tmpGr.Translate(x+2*spaceWidth,top);
				x+=rect.Width+2*sqrtWidth;
				x+=spaceWidth;
				gr->AddDr(&tmpGr);
			}
			else if (cmdName==L"boxed" && paraArr.GetSize()==1) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				//Bieu thuc trong can
				x+=spaceWidth/2;
				MDrawingSurface tmpGr(font);
				int top=DrawExp(paraArr[0],fontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr,endCh);
				i+=iAdd;
				Rect rect=tmpGr.GetBounds(graph);
				const int margin=4;
				gr->AddLine(Point(x,top-margin),Point(x+rect.Width+margin,top-margin),clr);
				gr->AddLine(Point(x,top+rect.Height+margin),Point(x+rect.Width+margin,top+rect.Height+margin),clr);
				gr->AddLine(Point(x,top-margin),Point(x,top+rect.Height+margin),clr);
				gr->AddLine(Point(x+rect.Width+margin,top-margin),Point(x+rect.Width+margin,top+rect.Height+margin),clr);
				tmpGr.Translate(x,top);
				x+=rect.Width;
				x+=spaceWidth;
				gr->AddDr(&tmpGr);
			}
			else if ((cmdName==L"RightArrow" || cmdName==L"LRArrow" || cmdName==L"SS") && paraArr.GetSize()<3) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }

				MDrawingSurface tmpGr1(font);
				if (paraArr.GetSize()>=1) DrawExp(paraArr[0],SubFontSize2(fontSize),&tmpGr1,bMathMode,bBold,bItalic,bUnderline,clr,endCh);
				MDrawingSurface tmpGr2(font);
				if (paraArr.GetSize()>=2) DrawExp(paraArr[1],SubFontSize2(fontSize),&tmpGr2,bMathMode,bBold,bItalic,bUnderline,clr,endCh);

				int sp=(cmdName==L"RightArrow" || cmdName==L"LRArrow") ? fontSize : 0;
				Rect rect1=tmpGr1.GetBounds(graph);
				Rect rect2=tmpGr2.GetBounds(graph);
				int w=max(rect1.Width,rect2.Width)+2*sp;
				if (wlimit!=-1 && x+spaceWidth+w>wlimit) { goto ReachWidthLimit; }
				if (cmdName==L"RightArrow" || cmdName==L"LRArrow") x+=spaceWidth;
				if (cmdName==L"RightArrow")
				{
					gr->AddLine(Point(x,fontSize-1),Point(x+w,fontSize-1),clr);
					gr->AddLine(Point(x+w,fontSize-1),Point(x+w-fontSize/3,fontSize-1-fontSize/3),clr);
					gr->AddLine(Point(x+w,fontSize-1),Point(x+w-fontSize/3,fontSize-1+fontSize/3),clr);

					tmpGr1.Translate(x+(w-rect1.Width)/2,-rect1.Height+fontSize-3);
					tmpGr2.Translate(x+(w-rect2.Width)/2,fontSize+3);
				}
				else if (cmdName==L"LRArrow")
				{
					gr->AddLine(Point(x,fontSize-1),Point(x+w,fontSize-1),clr);
					gr->AddLine(Point(x+w,fontSize-1),Point(x+w-fontSize/3,fontSize-1-fontSize/3),clr);
					gr->AddLine(Point(x,fontSize+fontSize/7),Point(x+w,fontSize+fontSize/7),clr);
					gr->AddLine(Point(x,fontSize+fontSize/7),Point(x+fontSize/3,fontSize+fontSize/7+fontSize/3),clr);

					tmpGr1.Translate(x+(w-rect1.Width)/2,-rect1.Height+fontSize-3);
					tmpGr2.Translate(x+(w-rect2.Width)/2,fontSize+3);
				}
				else if (cmdName==L"SS")
				{
					tmpGr1.Translate(x,-rect1.Height+fontSize*3/4);
					tmpGr2.Translate(x,3*fontSize/4);
				}

				i+=iAdd;

				x+=w; x+=spaceWidth;
				gr->AddDr(&tmpGr1); gr->AddDr(&tmpGr2);

			}
			else if (cmdName==L"UD" && paraArr.GetSize()<=3) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				MDrawingSurface tmpGr1(font);
				int top=DrawExp(paraArr[0],(fontSize),&tmpGr1,bMathMode,bBold,bItalic,bUnderline,clr,endCh);

				MDrawingSurface tmpGr2(font);
				DrawExp(paraArr.GetSize()>=2 ? paraArr[1] : L"",(fontSize),&tmpGr2,bMathMode,bBold,bItalic,bUnderline,clr,endCh);

				MDrawingSurface tmpGr3(font);
				DrawExp(paraArr.GetSize()>=3 ? paraArr[2] : L"",(fontSize),&tmpGr3,bMathMode,bBold,bItalic,bUnderline,clr,endCh);

				Rect rect1=tmpGr1.GetBounds(graph);
				Rect rect2=tmpGr2.GetBounds(graph);
				Rect rect3=tmpGr3.GetBounds(graph);
				int w=rect1.Width;
				if (wlimit!=-1 && x+w>wlimit) goto ReachWidthLimit;

				tmpGr1.Translate(x,0);
				if (paraArr.GetSize()>=2)
				{
					gr->AddLine(Point(x+rect1.Width/2,rect1.Height+2),Point(x+rect1.Width/2,rect1.Height+8),clr);
					tmpGr2.Translate(x+(w-rect2.Width)/2,3*rect2.Height/2);
				}
				if (paraArr.GetSize()>=3)
				{
					gr->AddLine(Point(x+rect1.Width/2,-3),Point(x+rect1.Width/2,-9),clr);
					tmpGr3.Translate(x+(w-rect3.Width)/2,-3*rect3.Height/2);
				}

				i+=iAdd;

				x+=w; x+=spaceWidth;
				gr->AddDr(&tmpGr1); gr->AddDr(&tmpGr2); gr->AddDr(&tmpGr3);

			}
			else if (cmdName==L"overline" && paraArr.GetSize()==1) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				x+=spaceWidth;
				MDrawingSurface tmpGr(font);
				int top=DrawExp(paraArr[0],fontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr);
				i+=iAdd;
				Rect rect=tmpGr.GetBounds(graph);
				gr->AddLine(Point(x,top-2),Point(x+rect.Width+1,top-2),clr);

				tmpGr.Translate(x+1,top);
				x+=rect.Width+1;
				gr->AddDr(&tmpGr);
			}
			else if (cmdName==L"overline" && paraArr.GetSize()==1) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				x+=spaceWidth;
				MDrawingSurface tmpGr(font);
				int top=DrawExp(paraArr[0],fontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr);
				i+=iAdd;
				Rect rect=tmpGr.GetBounds(graph);
				gr->AddLine(Point(x,top-2),Point(x+rect.Width+1,top-2),clr);

				tmpGr.Translate(x+1,top);
				x+=rect.Width+1;
				gr->AddDr(&tmpGr);
			}
			else if (cmdName==L"overrightarrow" || cmdName==L"vector" && paraArr.GetSize()==1) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				MDrawingSurface tmpGr(font);
				int top=DrawExp(paraArr[0],fontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr);
				i+=iAdd;
				Rect rect=tmpGr.GetBounds(graph);
				gr->AddLine(Point(x,top-2),Point(x+rect.Width+1,top-2),clr);
				int arrowW=fontSize/5;
				gr->AddLine(Point(x+rect.Width+1,top-2),Point(x+rect.Width+1-arrowW,top-2-arrowW),clr);
				gr->AddLine(Point(x+rect.Width+1,top-2),Point(x+rect.Width+1-arrowW,top-2+arrowW),clr);

				tmpGr.Translate(x+1,top);
				x+=rect.Width+1;
				gr->AddDr(&tmpGr);
			}
			else if (cmdName==L"widehat" && paraArr.GetSize()==1) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				x+=spaceWidth;
				
				MDrawingSurface tmpGr(font);
				int top=DrawExp(paraArr[0],fontSize,&tmpGr,bMathMode,bBold,bItalic,bUnderline,clr);
				Rect rect=tmpGr.GetBounds(graph);
				gr->AddLine(Point(x,top-2),Point(x+rect.Width/2,top-2-fontSize/4),clr);
				gr->AddLine(Point(x+rect.Width/2,top-2-fontSize/4),Point(x+rect.Width,top-2),clr);

				tmpGr.Translate(x+1,top);
				i+=iAdd;
				x+=rect.Width+1;
				gr->AddDr(&tmpGr);
			}
			else if (cmdName==L"text" && paraArr.GetSize()==1) {
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }

				MDrawingSurface tmpGr(font);
				bool mm=false;
				int top=DrawExp(paraArr[0],fontSize,&tmpGr,mm,bBold,bItalic,bUnderline,clr);
				Rect rect=tmpGr.GetBounds(graph);

				tmpGr.Translate(x,top);
				i+=iAdd;
				x+=rect.Width;
				gr->AddDr(&tmpGr);
			}
			else if ((c=GetCharacterByCommand(cmdName))!=NULL && paraArr.GetSize()==0)
			{
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				AddSymbolString(gr,fontSize,CString(c),x);	i+=iAdd;
			}
			else
			{
NormalString:
				if (chr=='$') 
				{
					if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
					bMathMode=!bMathMode;
					i++;
				}
				else //if (!(chr==' ' || chr=='{' || chr=='}'))
				{
					if (chr=='\\' && strExp.GetLength()>i+3 && strExp[i+1]=='{' && strExp[i+3]=='}')
					{
						if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
						AddSymbolString(gr,fontSize,(CString)strExp[i+2],x);
						i+=4;
						//x+=spaceWidth;
					}
// 					else if (strExp.Mid(i,2)==L">=")
// 					{
// 						if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
// 						AddSymbolString(gr,fontSize,L"",x);
// 						i+=2;
// 						x+=spaceWidth;
// 					}
// 					else if (strExp.Mid(i,2)==L"<=")
// 					{
// 						if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
// 						AddSymbolString(gr,fontSize,L"  ",x);
// 						i+=2;
// 					}
					else if (chr=='+' || chr=='-' || chr=='/' || chr=='>' || chr=='=' || chr=='<' || chr=='*' || chr=='=' || chr==L'≡')
					{
						//if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,true); }
						//AddSymbolString(gr,fontSize,CString(chr),x,graph);
						if (i>0) strTmpText+=L" ";
						if (chr=='*') chr=L'·';
						if (chr=='-') chr=L'–';
						strTmpText+=(CString)chr+L" ";
						if (!CheckWidthLimit(gr,fontSize,strTmpText,x,true)) goto ReachWidthLimit; 
						if (i+1<strExp.GetLength() && strExp[i+1]==' ') i+=2; else i++;
						//i++;
						//x+=spaceWidth*2/3;
					}
// 					else if (chr=='*')
// 					{
// 						if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,true); }
// 						AddSymbolString(gr,fontSize,L"",x,graph);
// 						i++;
// 						x+=spaceWidth;
// 					}
					else if (chr!=' ')
					{
						strTmpText+=(CString)chr;
						if (!CheckWidthLimit(gr,fontSize,strTmpText,x,true)) goto ReachWidthLimit; 
						i++;
					}
					else i++;
				}
			}
		}
		
		else
		{
			if (chr=='$') 
			{
				if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
				bMathMode=!bMathMode;
			}
			else if (!(bMathMode && (chr==' ' || chr=='{' || chr=='}')))
			{
				strTmpText+=(CString)chr;
				if (!CheckWidthLimit(gr,fontSize,strTmpText,x,FALSE)) goto ReachWidthLimit; 
			}
			i++;
// 				FontFamily fontFamily(L"Tahoma");
// 				Gdiplus::Font font(&fontFamily,10);
// 				gr->AddString((CString)chr,PointF(x,0),fontSize);
// 				RectF outRect;
// 				graph->MeasureString((CString)chr,1,&font,PointF(0,0),&outRect);
// 				x+=outRect.Width-2;
// 				i++;
		}
	}
	if (strTmpText!=L"") { AddString(gr,fontSize,strTmpText,x,bBold,bItalic,bUnderline,clr); }
	
	Rect rect=gr->GetBounds(graph);
	gr->Translate(-rect.GetLeft(),-rect.GetTop());
	return rect.GetTop();

ReachWidthLimit:
	if (strTmpText!=L"") { 
		if (strTmpText.Find(' ')!=-1)
		{
			int c=0;
			while (strTmpText!=L"" && strTmpText[strTmpText.GetLength()-1]!=' ') { strTmpText.Delete(strTmpText.GetLength()-1); c++; }
			i-=c;
			i++;
		}
		AddString(gr,fontSize,strTmpText.Mid(0,strTmpText.GetLength()-1),x,bBold,bItalic,bUnderline,clr); 
	}

	Rect rct=gr->GetBounds(graph);
	gr->Translate(-rct.GetLeft(),-rct.GetTop());
	*endCh=i;
	return rct.GetTop();
}

bool CMathDraw::IsNumber(CString str)
{
	for (int i=0;i<str.GetLength();i++) if (!((str[i]>='0' && str[i]<='9') || str[i]=='.' || str[i]==',')) return false;
	return true;
}

int CMathDraw::GetNextExp(CString strExp)
{
	int i=0;
	TCHAR chr=strExp.GetAt(0); if (chr=='\\') { i=1; chr=strExp.GetAt(1); }
	bool startByNumber=(chr>='0' && chr<='9');
	if (chr=='{' || chr=='(' || chr=='[')
	{
		char cEnd, cBegin;
		cBegin=chr;
		cEnd=(chr=='{') ? '}' : ((chr=='(') ? ')' : ']');
		int d=1;i++;
		bool bChu=false;
		while (d!=0 && i<strExp.GetLength())
		{
			chr=strExp.GetAt(i);
			if (IsLetter(chr)) bChu=true;
			if (chr==cEnd) d--;
			else if (chr==cBegin) d++;
			i++;
		}
		if (bChu) while (i<strExp.GetLength() && (strExp[i]>='0' && strExp[i]<='9')) i++;
		return (i==0 ? 1:i);
	}
	else
	{
		while (((chr>='0' && chr<='9') /*|| chr==',' || chr=='.'*/) || (IsLetter(chr) && !startByNumber))
		{
			i++;
			if (i<strExp.GetLength()) chr=strExp.GetAt(i);
			else break;
		}
	}

	return (i==0 ? 1:i);
// 	else
// 	{
// 		int i=0;
// 		chr=strExp.GetAt(0);
// 		while ((chr>='0' && chr<='9') || (chr>='a' && chr<='z') || (chr>='A' && chr<='Z') || chr=='(')
// 		{
// 			i++;
// 			if (i<strExp.GetLength()) chr=strExp.GetAt(i);
// 			else break;
// 		}
// 		return i;
// 	}
}

bool CMathDraw::IsLetter(TCHAR c)
{
	if (c>='a' && c<='z') return true;
	if (c>='A' && c<='Z') return true;
	CString s=L"αβγΔδεφλμπρσΩω";
	if (s.Find(c,0)!=-1) return true;
	return false;
}

bool CMathDraw::GetNextCommand(CString str, int paraCount, CString& cmdName, CStringArray& paraArr, int& id)
{
	if (str[0]==L'\\')
	{
		id=1;
		while ((str[id]>='a' && str[id]<='z') || (str[id]>='A' && str[id]<='Z')) id++;
		cmdName=str.Mid(1,id-1);
		if (paraCount==-1) paraCount=MAXINT;
		for (int i=0;i<paraCount;i++)
		{
			if (str[id]=='{') 
			{
				int pos=GetNextExp(str.Right(str.GetLength()-id));
				CString s;
				if (str[id+pos-1]=='}') s=str.Mid(id+1,pos-2);
				else s=str.Mid(id+1,pos-1);
				if (s=="") s=" ";
				paraArr.Add(s);
				id+=pos;
			}
			else break;
		}
	}
	else return false;
}

TCHAR CMathDraw::GetCharacterByCommand(CString cmd)
{
	if (cmd==L"alpha")		return 'a';
	if (cmd==L"beta")		return 'b';
	if (cmd==L"gamma")		return 'g';
	if (cmd==L"delta")		return 'd';
	if (cmd==L"epsilon")	return 'e';
	if (cmd==L"zeta")		return 'z';
	if (cmd==L"eta")		return 'h';
	if (cmd==L"theta")		return 'q';
	if (cmd==L"iota")		return 'i';
	if (cmd==L"kappa")		return 'k';
	if (cmd==L"lambda")		return 'l';
	if (cmd==L"mu")			return 'm';
	if (cmd==L"nu")			return 'n';
	if (cmd==L"xi")			return 'x';
	if (cmd==L"pi")			return 'p';
	if (cmd==L"rho")		return 'r';
	if (cmd==L"sigma")		return 's';
	if (cmd==L"tau")		return 't';
	if (cmd==L"upsilon")	return 'u';
	if (cmd==L"phi")		return 'j';
	if (cmd==L"chi")		return 'c';
	if (cmd==L"psi")		return 'y';
	if (cmd==L"omega")		return 'w';

	if (cmd==L"Alpha")		return 'A';
	if (cmd==L"Beta")		return 'B';
	if (cmd==L"Gamma")		return 'G';
	if (cmd==L"Delta")		return 'D';
	if (cmd==L"Epsilon")	return 'E';
	if (cmd==L"Zeta")		return 'Z';
	if (cmd==L"Eta")		return 'H';
	if (cmd==L"Theta")		return 'Q';
	if (cmd==L"Iota")		return 'I';
	if (cmd==L"Kappa")		return 'K';
	if (cmd==L"Lambda")		return 'L';
	if (cmd==L"Mu")			return 'M';
	if (cmd==L"Nu")			return 'N';
	if (cmd==L"Xi")			return 'X';
	if (cmd==L"Pi")			return 'P';
	if (cmd==L"Rho")		return 'R';
	if (cmd==L"Sigma")		return 'S';
	if (cmd==L"Tau")		return 'T';
	if (cmd==L"Upsilon")	return 'U';
	if (cmd==L"Phi")		return 'F';
	if (cmd==L"Chi")		return 'C';
	if (cmd==L"Psi")		return 'Y';
	if (cmd==L"Omega")		return 'W';

	if (cmd==L"Rightarrow")					return L'Þ';
	if (cmd==L"Leftarrow")					return L'Ü';
	if (cmd==L"Leftrightarrow")				return L'Û';
	if (cmd==L"rightarrow" || cmd==L"to")	return L'®';
	if (cmd==L"leftarrow" || cmd==L"gets")	return L'¬';
	if (cmd==L"leftarrow" || cmd==L"gets")	return L'«';

	if (cmd==L"circ")						return L'°';

	if (cmd==L"ne" || cmd==L"neq")			return L'¹';
	if (cmd==L"neq")						return L'¹';
	if (cmd==L"equiv")						return L'º';
	if (cmd==L"approx")						return L'»';
	if (cmd==L"le" || cmd==L"leq")			return L'£';
	if (cmd==L"ge" || cmd==L"geq")			return L'³';
	
	if (cmd==L"forall")						return '"';
	if (cmd==L"exists")						return L'$';

	if (cmd==L"in")							return L'Î';
	if (cmd==L"notin")						return L'Ï';

	return NULL;
}

Bitmap* CMathDraw::Draw_Text( CString strText, Gdiplus::Font* font, int wLimit, int& yPos, int lineSpacing/*=0*/ )
{
	CMathDraw dr;
	dr.font=font;
	dr.lineSpacing=lineSpacing;
	dr.wlimit=wLimit;
	return dr.DrawText(strText,yPos);
}
