#include "Item.h"
#pragma once

class AFX_EXT_CLASS CItemArray
{
public:
	CItemArray(void);
public:
	~CItemArray(void);
public:
	CArray<CItemBase*, CItemBase*> m_Array;
	CItemBase* GetAt(int i) { return m_Array[i]; }
	int GetSize() { return m_Array.GetSize(); }
	CItemBase* operator [](int nIndex) { return m_Array[nIndex]; }

	void Draw( Graphics* gr, Point ptTopLeft );
	void Serialize(CArchive& ar);

	void AddItem(ItemType t, int after=-1, bool bEdit=false);
	void DeleteItem(int nIndex);

	void ResetIndex();
	void RecalcAllItems();
	void ReCalcHeight();
	void RedrawItem(CItemBase* item);
	//String ReplaceString(CString str);
	int GetItemUnderMouse(CPoint pt);
	bool CheckMouseOver(int x, int y);
	void DrawDrag(Graphics* gr, Point ptTopLeft, int nItem, int nMouseOverItem);
	void RecalcContainerDrawHeight(int nIndex);
	void RecalcAllContainerDrawHeight();
	int GetItemIndex(CItemBase* it);
	void DeleteAllItems();
	void AddQuestion(CString strText, CString strHint, int after=-1);
	void SetQuestMode(QuestMode mode, bool bHintOnRightAns=true);
	void ShowHint(bool bShowHint, bool bShowOnRightAns=true);
	//CTestInfo* m_tInfo;
	Gdiplus::Font* m_Font;

	int m_Height,m_Width;
	int m_hlItem;
	bool m_bDispose;
};
