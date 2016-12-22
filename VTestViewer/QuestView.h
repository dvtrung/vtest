#include "../lib/ItemArray.h"
#pragma once

// CQuestView

#define MSG_DONE_QUEST WM_USER+2
#define MSG_DONE_A_QUEST WM_USER+3

#define PAGE_DIS 5

class CQuestView : public CWnd
{
	DECLARE_DYNAMIC(CQuestView)

public:
	CQuestView();
	virtual ~CQuestView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CItemArray m_Items;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL RegisterWndClass();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	int m_Top;

	bool m_bAllowEditRightAns;
	bool m_bAllowSelect;
	int m_nSelectedItem;

public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void RefreshScrollBar();
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
private:
	bool bDoneAQuest, bDoneAllQuest;

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};


