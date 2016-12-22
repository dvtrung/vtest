#pragma once

// CQuestList
#define BTN_DIS 5
#define BTN_MARGIN 3
#define BTN_TEXT_MARGIN 10

#define MSG_QUEST_TAB_CHANGE WM_USER+5

class CQuestList : public CWnd
{
	DECLARE_DYNAMIC(CQuestList)

public:
	CQuestList();
	virtual ~CQuestList();
	CStringArray m_StrArray;
	CArray<int,int> m_ItemWidthArr;
	Gdiplus::Font* m_Font;
	int m_nMouseMove;
	bool m_bMouseMove;
	int m_nMouseDown;
	int m_nSelected;
	int m_nPos;
	int m_itemWidth; void SetItemWidth(int nWidth) { m_itemWidth=nWidth; }
	int GetItemWidth(int i);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void DrawButton(Graphics* gr, int height, int& x, CString str, Color clr1, Color clr2, Color clrText, int width);
	void CalcAllItemWidth();
	int CalcItemWidth(Graphics* gr,int i);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	int GetItemUnderMouse(int x);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetPos(int nPos);
};


