// QuestTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "QuestTabCtrl.h"
#include "VTestViewer.h"

// CQuestTabCtrl

IMPLEMENT_DYNAMIC(CQuestTabCtrl, CMFCButton)

CQuestTabCtrl::CQuestTabCtrl()
{
	m_bShowAll=true;
}

CQuestTabCtrl::~CQuestTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CQuestTabCtrl, CMFCTabCtrl)
	ON_WM_CREATE()
	
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, OnChangeActiveTab)
END_MESSAGE_MAP()



// CQuestTabCtrl message handlers




int CQuestTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_QuestView.Create(L"QuestView",L"",WS_CHILD | WS_VISIBLE,CRect(0,0,0,0),this,2);

	SetActiveTabBoldFont();
	HideNoTabs();

	return 0;
}

LRESULT CQuestTabCtrl::OnChangeActiveTab(WPARAM wp, LPARAM /*lp*/)
{
	RefreshQuest();
	return 0;
}

void CQuestTabCtrl::RefreshQuest()
{
	if (m_TabParam.GetSize()==0) return;
	CItemBase* it=(CItemBase*)m_TabParam[GetActiveTab()];

	m_QuestView.m_Items.m_Array.RemoveAll();
	for (int i=0;i<m_Items->GetSize();i++) 
		if (m_Items->GetAt(i)==it) 
			m_QuestView.m_Items.m_Array.Add(m_Items->GetAt(i));
	m_QuestView.RefreshScrollBar();
}

void CQuestTabCtrl::RefreshView()
{
	static bool bAdd=false;
	if (!bAdd)
	{
		bAdd=true;
		for (int i=0;i<m_Items->GetSize();i++)
			if (m_Items->GetAt(i)->m_Type==ItemQuestABCD 
				&& ((CQuestItemABCD*)m_Items->GetAt(i))->m_userAns==0)
			{
				AddTab(&m_QuestView,
					IntToString(((CQuestItemABCD*)m_Items->GetAt(i))->m_nIndex),-1,1);
				m_TabParam.Add(m_Items->GetAt(i));
			}
	}

	if (m_bShowAll)
	{
		for (int i=0;i<GetTabsNum();i++)
			ShowTab(i,0);
		CRect rc; GetClientRect(rc);
		m_QuestView.MoveWindow(rc);
		m_QuestView.ShowWindow(SW_SHOW);
		//m_Tab.ShowWindow(SW_HIDE);
		m_QuestView.m_Items.m_Array.RemoveAll();
		for (int i=0;i<m_Items->GetSize();i++)
			m_QuestView.m_Items.m_Array.Add(m_Items->GetAt(i));

		if (m_nShowType==1)
		{
			for (int i=0;i<m_QuestView.m_Items.GetSize();i++)
				if (m_QuestView.m_Items[i]->m_Type==ItemQuestABCD && 
					((CQuestItemABCD*)m_QuestView.m_Items[i])->m_userAns!=0)
				{
					m_QuestView.m_Items.m_Array.RemoveAt(i);
					i--;
				}

				for (int i=0;i<m_QuestView.m_Items.GetSize()-1;i++)
					if (m_QuestView.m_Items[i]->m_Type==ItemContainer && 
						((CContainerItemStart*)m_QuestView.m_Items[i])->m_itEnd==m_QuestView.m_Items[i+1])
					{
						m_QuestView.m_Items.m_Array.RemoveAt(i);
						m_QuestView.m_Items.m_Array.RemoveAt(i);
						i-=2;
					}
		}
	}
	else
	{
		//m_Tab.ShowWindow(SW_SHOW);
		int nSel=GetActiveTab();

		if (m_nShowType==1)
		{
			for (int i=0;i<GetTabsNum();i++)
				ShowTab(i,((CQuestItemABCD*)m_TabParam[i])->m_userAns==0);
		}
		else
		{
			for (int i=0;i<GetTabsNum();i++)
				ShowTab(i);
		}
		if (nSel<GetTabsNum()) SetActiveTab(nSel);
		else SetActiveTab(GetTabsNum()-1);
		RefreshQuest();
	}
	m_QuestView.RefreshScrollBar();
}


LRESULT CQuestTabCtrl::OnDoneQuest(WPARAM wParam, LPARAM lParam)
{
	if (!m_bShowAll && m_nShowType==0)
	{
		if (GetActiveTab()!=GetTabsNum()-1)
		{
			SetActiveTab(GetActiveTab()+1);
			RefreshQuest();
		}
	}
	else if (!m_bShowAll)
	{
		RefreshView();
	}
	return 0;
}

LRESULT CQuestTabCtrl::OnDoneAQuest(WPARAM wParam, LPARAM lParam)
{
	if (m_bShowAll)
		RefreshView();
	return 0;
}