#pragma once
#include <GdiPlus.h>
#include <vector>

using namespace std;
using namespace Gdiplus;

#define SubFontSize(fs) (fs>=10 ? fs-4 : (fs>=8) ? fs-2 : fs)
#define SubFontSize2(fs) (fs>=8 ? fs-2 : fs)

class AFX_EXT_CLASS CMathDraw
{
private:
	class AFX_EXT_CLASS MDrawingSurface
	{
	public:
		MDrawingSurface(Gdiplus::Font* font);
		~MDrawingSurface();
		void AddLine(Point pt1,Point pt2,Color lineClr);
		void AddDr(MDrawingSurface* gr);
		void Translate(int x, int y);
		void Draw(Graphics* gr);
		Rect GetBounds(Graphics* gr);
		void AddString(CString str, PointF pt, int fontSize, bool bBold, bool bItalic, bool bUnderline, Color color);
		void AddSymbol(CString str, PointF pt, int fontSize);
		void DrawBracket(int type,Point pt,int width,int height,Graphics* gr,Color clr);
		void AddBracket(int type, Point pt,int brWidth, int brHeight);
		void AddBitmap(Bitmap* bmp,Point pos);
		//DrawBracket(Point pt1,Point pt2,Point pt3,Graphics* gr) /* pt2 co toa do Y nam giua pt1 va pt3 */;
		//void AddChar(TCHAR str, PointF pt, int fontSize);
		Gdiplus::Font* m_Font;
	private:	
		vector<Point> m_Pt1;
		vector<Point> m_Pt2;

		vector<int> m_BrType;
		vector<Point> m_BrPt;
		vector<int> m_BrHeight;
		vector<int> m_BrWidth;

		//vector<CString> m_String;
		vector<CString> m_String;
		vector<PointF> m_StringPos; // Vi tri cua ki tu khi in ra man hinh
		vector<bool> m_StringItalic;
		vector<bool> m_StringBold;
		vector<bool> m_StringUnderline;
		vector<Color> m_StringColor;
		vector<Color> m_LineColor;
		vector<int> m_FontSize;

		vector<CString> m_Symbol;
		vector<PointF> m_SymbolPos;
		vector<int>m_SymbolFontSize;
		vector<MDrawingSurface> m_Dr;

		vector<Bitmap*> m_Bmp;
		vector<Point> m_bmpPos;
	};
public:
	CMathDraw();
	~CMathDraw();
	//static Bitmap* DrawExpression(CString strExp, Color clr, Gdiplus::Font* font);
	//static int DrawExp(CString strExp, Gdiplus::Font* font, int fontSize, MDrawingSurface* gr, Graphics* graph, BOOL bFormula=TRUE);
	//static int DrawExp(CString strExp, Gdiplus::Font* font, int fontSize, MDrawingSurface* gr, Graphics* graph, BOOL bFormula, int& endCh);
	Gdiplus::Font* font;
	Graphics* graph;
	int lineSpacing;
	int wlimit;

	int DrawExp(CString strExp, int fontSize, MDrawingSurface* mgr, bool& bMathMode, bool& bBold, bool& bItalic, bool& bUnderline, Color& clr, int* endCh=NULL);
	int GetNextExp(CString strExp);
	Bitmap* DrawText(CString text, int& yPos);
	//static Bitmap* DrawLine(CString strText, Color clr, Graphics* gr, Gdiplus::Font* font, int widthLimit);
	Bitmap* DrawLine(CString strText, Graphics* gr, bool& bModeMath, bool& bBold, bool& bItalic, bool& bUnderline,Color& clr, int* yPos=NULL);
	void AddString(MDrawingSurface* gr, int fontSize, CString& strText, int& x, bool bBold, bool bItalic, bool bUnderline, Color color);
	void AddSymbolString(MDrawingSurface* gr, int fontSize, CString strText, int& x);
	//static Bitmap* DrawObjectName(CString strName, Gdiplus::Font* font);
	bool CheckWidthLimit(MDrawingSurface* gr, int fontSize, CString strText, int& x, bool bModeMath);
	int GetStringWidth(CString strText, Gdiplus::Font* font);
	bool CheckCTHH(CString& str, int start, int length, int& SoKTThemCTHH);
	bool IsLetter(TCHAR c);
	bool IsNumber(CString str);
	void XuLyChuoi(CString& str);
	bool GetNextCommand(CString str, int paraCount, CString& cmdName, CStringArray& paraArr, int& id);
	TCHAR GetCharacterByCommand(CString cmd);
	const CString strFuncList;

	static Bitmap* Draw_Text(CString strText, Gdiplus::Font* font, int widthLimit, int& yPos, int lineSpacing=0);
};