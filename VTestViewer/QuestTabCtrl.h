#pragma once
#include "QuestView.h"

// CQuestTabCtrl

class CQuestTabCtrl : public CMFCTabCtrl
{
	DECLARE_DYNAMIC(CQuestTabCtrl)

public:
	CQuestTabCtrl();
	virtual ~CQuestTabCtrl();

	CQuestView m_QuestView;

	bool m_bShowAll;
	
	CArray<CItemBase*> m_TabParam;

	CItemArray* m_Items;

	int m_nShowType;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	void RefreshView();
	LRESULT OnDoneAQuest(WPARAM wParam, LPARAM lParam);
	void RefreshQuest();
	LRESULT OnDoneQuest(WPARAM wParam, LPARAM lParam);
	LRESULT OnChangeActiveTab(WPARAM wp, LPARAM /*lp*/);
};


