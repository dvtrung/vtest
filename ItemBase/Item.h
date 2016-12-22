#include "../MathRender/MathDraw.h"

#pragma once
#define MARGIN_LEFT 50
#define MARGIN_RIGHT 30
#define MARGIN_TOP 10
#define MARGIN_BOTTOM 10
#define ALTER_DIS 30
#define ALTER_QUEST_DIS 5
#define LINE_SPACING 5
#define PARA_SPACING 5

#define IsQuestType(a) (a==ItemQuestABCD || a==ItemQuestTrueFalse || a==ItemQuest)

class CIntArray : public CArray<int,int>
{
public:
	void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			ar << GetSize();
			for (int i=0;i<GetSize();i++) ar << GetAt(i);
		}
		else
		{
			int count; ar >> count; int a;
			for (int i=0;i<count;i++)
			{
				ar >> a; Add(a);
			}
		}
	}

	int operator=(CIntArray& o)
	{
		RemoveAll();
		for (int i=0;i<o.GetSize();i++) Add(o[i]);
		return 1;
	}
};

class CContainerItemStart; class CContainerItemEnd;

enum ItemType { ItemText, ItemQuestABCD, ItemContainer, ItemContainerEnd, ItemQuestTrueFalse, ItemQuest };
enum QuestMode { UserAnswer, ShowAnswer, ShowRightAns, NoAnswer };

class AFX_EXT_CLASS CItemBase
{
public:
	CItemBase() { m_bmp=NULL; }
	~CItemBase() { if (m_bmp!=NULL) delete m_bmp; }
	CString ToHTML(CString str, CString imageFolder, int& imgIndex);
	ItemType m_Type;
	int top, height;
	Gdiplus::Font* m_Font;
	virtual void Draw(Graphics* gr, Point pt , int width, bool bHighlight=false);
	virtual void ReDrawBmp(int width) {}
	virtual void Serialize(CArchive& ar) {}
	virtual bool CheckMouseOver(int x, int y) { return false; }
	virtual bool OnClick(int x, int y) { return false; }
	virtual void ReCalcHeight() {}
	virtual void WriteScriptData(CStdioFile& f,CString imageFolder, CString index, int& imgIndex) {  }
	virtual void DisposeBmp();
	virtual void Edit(CWnd* pWnd) {}
	Bitmap* m_bmp;
	int yQ;
	
	RectF GetTextBound(CString strText, int width, int& y);

	void DrawText(CString strText, Bitmap*& bmp, int width, int& y, RectF& rcF);
};

class AFX_EXT_CLASS CContainerItemStart : public CItemBase
{
public:
	CContainerItemStart(void) { m_Type=ItemContainer; m_nStdType=-1; }
	~CContainerItemStart(void) {}

	CString m_strText;
	CContainerItemEnd* m_itEnd;
	int drawHeight;
	int m_nStdType;

	void ReDrawBmp(int width);
	void Serialize(CArchive& ar);

	void Draw(Graphics* gr, Point pt , int width, bool bHighlight);
	void WriteScriptData(CStdioFile& f,CString imageFolder, CString index, int& imgIndex);
	virtual void Edit(CWnd* pWnd);
};

class AFX_EXT_CLASS CContainerItemEnd : public CItemBase
{
public:
	CContainerItemEnd(void) { m_Type=ItemContainerEnd; }
	~CContainerItemEnd(void) {}

	CContainerItemStart* m_itStart;

	void ReDrawBmp(int width);
	void Serialize(CArchive& ar);

	void Draw(Graphics* gr, Point pt , int width, bool bHighlight);
};

class AFX_EXT_CLASS CTextItem : public CItemBase
{
public:
	CTextItem() { m_Type=ItemText; m_nIndex=-1; }
	void ReDrawBmp(int width);
	void Serialize(CArchive& ar);
	void Draw(Graphics* gr, Point pt, int width , bool bHighlight);
	virtual void WriteScriptData(CStdioFile& f,CString imageFolder, CString index, int& imgIndex);
	CString m_strText;
	int m_nIndex;

	virtual void Edit(CWnd* pWnd);
};

class AFX_EXT_CLASS CQuestItemBase : public CItemBase
{
public:
	QuestMode m_Mode;
	bool m_bShowHint;
	bool m_bShowOnRightAns;
	int m_nMark;
	CQuestItemBase() { m_nMark=1; }
	virtual void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			ar << m_nMark;
		}
		else 
		{
			ar >> m_nMark;
		}
	}
};

class AFX_EXT_CLASS CQuestItem : public CQuestItemBase
{
public:
	CQuestItem() { m_Type=ItemQuest; m_bmpHint=NULL; m_nIndex=0; }
	~CQuestItem() { if (m_bmpHint!=NULL) delete m_bmpHint; }

	Bitmap* m_bmpHint;
	int m_nIndex;
	CString m_strHint;
	CString m_strText;
	void ReDrawBmp(int width);
	void Serialize(CArchive& ar);
	void DisposeBmp();
	virtual void WriteScriptData(CStdioFile& f,CString imageFolder,CString index, int& imgIndex);
	virtual void Draw(Graphics* gr, Point pt, int width , bool bHighlight);
	void ReCalcHeight();
	virtual void Edit(CWnd* pWnd);
};
class AFX_EXT_CLASS CQuestItemABCD : public CQuestItemBase
{
public:
	CQuestItemABCD(void);
	~CQuestItemABCD() { if (m_bmpHint!=NULL) delete m_bmpHint; }

	struct Alternative
	{
		CString A,B,C,D;
		int bMarkA, bMarkB, bMarkC, bMarkD;
	};

	int m_nIndex;
	void ReDrawBmp(int width);
	void Serialize(CArchive& ar);
	bool CheckMouseOver(int x, int y);
	bool OnClick(int x, int y);
	void Draw(Graphics* gr, Point pt , int width, bool bHighlight);
	void ReCalcHeight();
	virtual void WriteScriptData(CStdioFile& f,CString imageFolder, CString index, int& imgIndex);
	bool OnMark(int x, int y);
	Rect rcC1,rcC2,rcC3,rcC4;
	CString m_strQuest;
	Alternative m_alt;
	int m_answer;
	CString m_strHint;
	
	int m_userAns;

	Bitmap* m_bmpHint;
	virtual void DisposeBmp();
	virtual void Edit(CWnd* pWnd);
};
class AFX_EXT_CLASS CQuestItemTrueFalse : public CQuestItemBase
{
public:
	CQuestItemTrueFalse();

	int index;
	CStringArray m_arrQuest;
	CStringArray m_arrHint;
	CStringArray m_arrAnsSet;
	CIntArray m_arrAns;
	CIntArray m_userAns;
	CArray<Rect,Rect> m_rcAnsArr;

	void ReDrawBmp(int width);
	void Serialize(CArchive& ar);
	void Draw(Graphics* gr, Point pt , int width, bool bHighlight);
	bool CheckMouseOver(int x, int y);
	bool OnClick(int x, int y);
	void DrawAns(Graphics* gr,CString str, Rect rc, Color clr);
	virtual void Edit(CWnd* pWnd);
};
