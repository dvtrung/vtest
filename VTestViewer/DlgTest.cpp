// DlgTest.cpp : implementation file
//

#include "stdafx.h"
#include "VTestViewer.h"
#include "DlgTest.h"
#include "afxdialogex.h"
#include "DlgTestResult.h"
#include "../lib/appfunc.h"

// CDlgTest dialog

IMPLEMENT_DYNAMIC(CDlgTest, CDialog)

CDlgTest::CDlgTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTest::IDD, pParent)
	, m_nView(0)
{
	m_Font=NULL;
	m_bDone=false;
	m_bShowAnswerIm=false;
	m_nPrevState=-1;
	m_nReviewTest=-1;
}

CDlgTest::~CDlgTest()
{
	if (m_Font) delete m_Font;
	if (m_filePath=="") 
	{
		m_Items.m_Array.RemoveAll();
	}
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TAB, m_Tab);
	DDX_Control(pDX, IDC_COMBO_SHOW, m_cbShow);
	//DDX_Control(pDX, IDC_CUSTOM_QUEST, m_QuestView);
	DDX_Control(pDX, IDC_TAB2, m_TabShow);
	DDX_CBIndex(pDX, IDC_COMBO_SHOW, m_nView);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialog)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_SHOW, &CDlgTest::OnCbnSelchangeComboShow)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CDlgTest::OnTcnSelchangeTab2)
	ON_BN_CLICKED(IDC_BTN_DONE, &CDlgTest::OnBnClickedDone)
	ON_BN_CLICKED(IDCANCEL, &CDlgTest::OnBnClickedCancel)
	ON_MESSAGE(MSG_DONE_QUEST, &CDlgTest::OnDoneQuest)
	ON_MESSAGE(MSG_DONE_A_QUEST, &CDlgTest::OnDoneAQuest)
	ON_MESSAGE(MSG_QUEST_TAB_CHANGE, &CDlgTest::OnMsgQuestTabChange)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDlgTest message handlers

BOOL CDlgTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Font=new Gdiplus::Font(L"Times New Roman",12,FontStyleRegular);

	CRect rectTabLoc;
	GetDlgItem(IDC_STATIC_TAB_LOC)->GetWindowRect(&rectTabLoc);
	ScreenToClient(&rectTabLoc);
	m_Tab.Create(L"QuestList",L"",WS_VISIBLE | WS_CHILD,rectTabLoc,this,1);
	m_Tab.SetItemWidth(25);
	m_Tab.m_nSelected=0;

	CRect rectQView;
	GetDlgItem(IDC_STATIC_QUESTVIEW_LOC)->GetWindowRect(&rectQView);
	ScreenToClient(&rectQView);
	m_QuestView.Create(L"QuestView",L"",WS_CHILD | WS_VISIBLE | WS_VSCROLL, rectQView,this,2);
	m_QuestView.m_Items.m_Width=rectTabLoc.Width();
	m_QuestView.m_Items.m_tInfo=&m_tInfo;
	m_QuestView.m_Items.m_Font=m_Font;

	if (m_filePath!="")
	{
		CFile f; 
		f.Open(m_filePath,CFile::modeRead);
		CArchive ar(&f,CArchive::load);
		m_tInfo.Serialize(ar);
		m_hisArr.Serialize(ar);
		m_Items.m_Width=rectTabLoc.Width();
		m_Items.m_Font=m_Font;
		m_Items.m_tInfo=&m_tInfo;
		m_Items.Serialize(ar);
		CDlgWait dlgWait;
		dlgWait.Create(CDlgWait::IDD);
		dlgWait.ShowWindow(SW_SHOW);
		dlgWait.m_Progress.SetRange(0,m_Items.m_Array.GetSize()-2);
		dlgWait.m_Progress.Invalidate();

		m_Items.ResetIndex();

		bool bRemove=false;
		CContainerItemEnd* pC;
		for (int i=0;i<m_Items.GetSize();i++) 
		{
			if (!bRemove && m_nStdType!=-1 && m_Items[i]->m_Type==ItemContainer)
			{
				if (((CContainerItemStart*)m_Items[i])->m_nStdType!=m_nStdType && 
					((CContainerItemStart*)m_Items[i])->m_nStdType!=-1)
				{
					bRemove=true;
					pC=((CContainerItemStart*)m_Items[i])->m_itEnd;
				}
			}

			if (bRemove && m_Items[i]->m_Type==ItemContainerEnd)
			{
				CContainerItemStart* pS=((CContainerItemEnd*)m_Items[i])->m_itStart;
				if (m_Items[i]==pC) bRemove=false;
			}

			if (bRemove) { m_Items.m_Array.RemoveAt(i); i--; }
		}

		for (int i=0;i<m_Items.m_Array.GetSize();i++)
		{
			m_Items.RedrawItem(m_Items[i]);
			dlgWait.m_Progress.SetPos(i+1); 
			dlgWait.m_Progress.Invalidate();
		}
		dlgWait.CloseWindow();

		ar.Close();
		f.Close();
	}
//  	for (int i=0;i<m_Items.m_Array.GetSize();i++)
//  	{
//  		m_Items[i]->ReDrawBmp(m_Items.m_Width);
//  	}

	m_Items.SetQuestMode(UserAnswer);
	m_Items.ShowHint(false,false);

	for (int i=0;i<m_Items.GetSize();i++)
	{
		if (m_Items[i]->m_Type==ItemQuestTrueFalse) 
		{
			((CQuestItemTrueFalse*)m_Items[i])->m_userAns.RemoveAll();
			for (int j=0;j<((CQuestItemTrueFalse*)m_Items[i])->m_arrAns.GetSize();j++)
				((CQuestItemTrueFalse*)m_Items[i])->m_userAns.Add(0);
		}
	}

	m_cbShow.AddString(StringFromResource(IDS_TYPE_TEST));
	m_cbShow.AddString(StringFromResource(IDS_TYPE_QUEST));
	m_cbShow.SetCurSel(m_nView);

	m_TabShow.InsertItem(0,StringFromResource(IDS_ALL));
	m_TabShow.InsertItem(1,StringFromResource(IDS_UNDONE));
	m_TabShow.InsertItem(2,StringFromResource(IDS_MARKED));
	m_TabShow.SetCurSel(0);

	RefreshView();

	if (m_nReviewTest!=-1)
	{
		m_hisArr.m_Array[m_nReviewTest]->SetToItemArray(&m_Items);
		m_Items.SetQuestMode(ShowRightAns);
		m_Items.ShowHint(true);
		if (!m_bShowAnswerIm) m_TabShow.InsertItem(4,StringFromResource(IDS_WRONG),0);
		m_bDone=true;
		GetDlgItem(IDC_BTN_DONE)->SetWindowTextW(StringFromResource(IDS_RESULT));
		OnOK();
		int rt=m_hisArr.m_Array[m_nReviewTest]->m_ThoiGian-m_hisArr.m_Array[m_nReviewTest]->m_ThoiGianLam;
		((CStatic*)GetDlgItem(IDC_STATIC_TIME))->SetWindowText(SecondToMinuteAndSecond(rt)+L" ("+IntToString(rt*100/(m_tInfo.m_nTime)*60)+L"%)");
	}
	else
	{
		SetTimer(1000,1000,NULL);
		((CStatic*)GetDlgItem(IDC_STATIC_TIME))->SetWindowText(IntToString(m_nRemainingTime/60)+L":00 (100%)");

		CTime t = CTime::GetCurrentTime();
		m_TakenTime=t.Format(L"%H:%M %d/%m/%Y");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTest::OnTimer(UINT_PTR nIDEvent)
{
	if (m_tInfo.m_nTime>0) 
	{
		m_nRemainingTime--;
		if (m_nRemainingTime==0) { KillTimer(nIDEvent); OnOK(); }
		((CStatic*)GetDlgItem(IDC_STATIC_TIME))->SetWindowText(SecondToMinuteAndSecond(m_nRemainingTime)+L" ("+IntToString(m_nRemainingTime*100/(m_tInfo.m_nTime)*60)+L"%)");
	}
	else
		KillTimer(nIDEvent);

	CDialog::OnTimer(nIDEvent);
}


int CDlgTest::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CDlgTest::OnOK()
{

}

void CDlgTest::OnCancel()
{
	//m_Tab.m_QuestView.m_Items.m_Array.RemoveAll();

	CDialog::OnCancel();
}

void CDlgTest::OnCbnSelchangeComboShow()
{
	//if (m_Tab.GetTabsNum()==0) return;
	//m_Tab.m_bShowAll=!m_cbShow.GetCurSel();
	RefreshView();
}

void CDlgTest::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	//m_Tab.m_nShowType=m_TabShow.GetCurSel();
	RefreshView();
	*pResult = 0;
}


void CDlgTest::OnBnClickedDone()
{
	bool b=m_bDone ? true : (AfxMessageBox(L"Bạn chắc chắn muốn dừng bài thi ở đây ?",MB_YESNO)==IDYES);
	if (b)
	{
		KillTimer(1000);
		CDlgTestResult dlg;
		dlg.m_SoCau=0;
		dlg.m_SoCauDung=0;
		dlg.m_SoCauLam=0;
		dlg.m_ThoiGian=m_tInfo.m_nTime*60;
		dlg.m_ThoiGianLam=m_tInfo.m_nTime*60-m_nRemainingTime;
		for (int i=0;i<m_Items.GetSize();i++)
		{	
			if (m_Items[i]->m_Type==ItemQuestABCD)
			{
				dlg.m_SoCau++;
				CQuestItemABCD*	q=(CQuestItemABCD*)m_Items[i];
				if (q->m_userAns!=0) dlg.m_SoCauLam++;
				if (q->m_userAns==q->m_answer && q->m_answer!=0) dlg.m_SoCauDung++;
			}
// 			else if (m_Items[i]->m_Type==ItemQuestTrueFalse)
// 			{
// 				dlg.m_SoCau++;
// 				CQuestItemTrueFalse* q=(CQuestItemTrueFalse*)m_Items[i];
// 				if (q->m_userAns!=0) dlg.m_SoCauLam++;
// 				if (q->m_userAns==q->m_answer && q->m_answer!=0) dlg.m_SoCauDung++;
// 			}

		}

		CTestHistory* th=new CTestHistory();
		th->FromItemArray(&m_Items);
		th->m_SoCau=dlg.m_SoCau;
		th->m_SoCauDung=dlg.m_SoCauDung;
		th->m_SoCauLam=dlg.m_SoCauLam;
		th->m_ThoiGian=dlg.m_ThoiGian;
		th->m_ThoiGianLam=dlg.m_ThoiGianLam;
		th->m_TakenTime=m_TakenTime;
		m_hisArr.m_Array.Add(th);

		dlg.DoModal();

		if (!m_bDone)
		{
			m_Items.SetQuestMode(ShowRightAns);
			m_Items.ShowHint(true);
			if (!m_bShowAnswerIm) m_TabShow.InsertItem(4,L"Câu làm sai",0);
			m_bDone=true;
			GetDlgItem(IDC_BTN_DONE)->SetWindowTextW(L"Kết quả thi");
			OnOK();

			if (m_filePath!=L"")
			{
				CFile f; 
				f.Open(m_filePath,CFile::modeWrite);
				CArchive ar(&f,CArchive::store);
				m_tInfo.Serialize(ar);
				m_hisArr.Serialize(ar);
				m_Items.Serialize(ar);

				ar.Close();
				f.Close();
			}
		}

		//////////////////////////////////////////////////////////////////////////
	}
}


void CDlgTest::OnBnClickedCancel()
{
	if (MessageBox(L"Bạn muốn thoát khỏi chương trình ?",0,MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		m_QuestView.m_Items.m_Array.RemoveAll();
		if (this->GetParent()!=NULL) this->GetParent()->ShowWindow(SW_SHOW);
		CDialog::OnCancel();
	}
}

void CDlgTest::RefreshQuest()
{
	if (m_Tab.m_nSelected==-2) { 
		m_QuestView.m_Items.m_Array.RemoveAll(); 
		m_QuestView.RefreshScrollBar(); return; 
	}
	CItemBase* it=(CItemBase*)m_TabParam[m_Tab.m_nSelected];

	m_QuestView.m_Items.m_Array.RemoveAll();
	for (int i=0;i<m_Items.GetSize();i++) 
		if (m_Items.GetAt(i)==it) 
			m_QuestView.m_Items.m_Array.Add(m_Items.GetAt(i));
	m_QuestView.RefreshScrollBar();
}

void CDlgTest::RefreshView()
{
	CItemBase* currentIt=(m_Tab.m_nSelected>=0 && m_Tab.m_nSelected<m_TabParam.GetSize()) ? m_TabParam[m_Tab.m_nSelected] : NULL;
	CItemBase* nextIt=(m_Tab.m_nSelected+1>=0 && m_Tab.m_nSelected+1<m_TabParam.GetSize()) ? m_TabParam[m_Tab.m_nSelected+1] : NULL;
	if (m_cbShow.GetCurSel()==0)
	{
		if (m_nPrevState!=0)
		{
			m_Tab.ShowWindow(SW_HIDE);
			CRect rectQView;
			GetDlgItem(IDC_STATIC_QUESTVIEW_LOC_2)->GetWindowRect(&rectQView);
			ScreenToClient(&rectQView);
			m_QuestView.MoveWindow(rectQView);
		}
		//for (int i=0;i<GetTabsNum();i++)
		//ShowTab(i,0);
		m_QuestView.m_Items.m_Array.RemoveAll();
		for (int i=0;i<m_Items.GetSize();i++)
			m_QuestView.m_Items.m_Array.Add(m_Items.GetAt(i));

		if (m_TabShow.GetCurSel()==1)
		{
			for (int i=0;i<m_QuestView.m_Items.GetSize();i++)
			{
				if (m_QuestView.m_Items[i]->m_Type==ItemQuestABCD && 
					((CQuestItemABCD*)m_QuestView.m_Items[i])->m_userAns!=0)
				{
					m_QuestView.m_Items.m_Array.RemoveAt(i);
					i--;
				}
			}
		}
		else if (m_TabShow.GetCurSel()==2)
		{
			for (int i=0;i<m_QuestView.m_Items.GetSize();i++)
			{
				if (m_QuestView.m_Items[i]->m_Type==ItemQuestABCD)
				{
					CQuestItemABCD* item=(CQuestItemABCD*)m_QuestView.m_Items[i];
					if ((item->m_alt.bMarkA%3==0 && item->m_alt.bMarkB%3==0 && item->m_alt.bMarkC%3==0 && item->m_alt.bMarkD%3==0) || item->m_userAns!=0)
					{
						m_QuestView.m_Items.m_Array.RemoveAt(i);
						i--;
					}
				}
			}
		}
		else if (m_TabShow.GetCurSel()==3)
		{
			for (int i=0;i<m_QuestView.m_Items.GetSize();i++)
			{
				if (m_QuestView.m_Items[i]->m_Type==ItemQuestABCD)
				{
					CQuestItemABCD* item=(CQuestItemABCD*)m_QuestView.m_Items[i];
					if (!(item->m_Mode==QuestMode::ShowRightAns && item->m_userAns!=item->m_answer && item->m_userAns!=0))
					{
						m_QuestView.m_Items.m_Array.RemoveAt(i);
						i--;
					}
				}
			}
		}

		for (int i=0;i<m_QuestView.m_Items.GetSize()-1;i++)
		{
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
		if (m_nPrevState!=1)
		{
			m_Tab.ShowWindow(SW_SHOW);
			CRect rectQView;
			GetDlgItem(IDC_STATIC_QUESTVIEW_LOC)->GetWindowRect(&rectQView);
			ScreenToClient(&rectQView);
			m_QuestView.MoveWindow(rectQView);
		}

		m_Tab.m_StrArray.RemoveAll();
		m_TabParam.RemoveAll();
		int nSel=m_Tab.m_nSelected;

		if (m_TabShow.GetCurSel()==1)
		{
			for (int i=0;i<m_Items.GetSize();i++)
				if (m_Items[i]->m_Type==ItemQuestABCD && ((CQuestItemABCD*)m_Items[i])->m_userAns==0)
				{
					m_TabParam.Add(m_Items[i]);
					m_Tab.m_StrArray.Add(IntToString(((CQuestItemABCD*)m_Items[i])->m_nIndex));
				}
		}
		else if (m_TabShow.GetCurSel()==0)
		{
			for (int i=0;i<m_Items.GetSize();i++)
				if (m_Items[i]->m_Type==ItemQuestABCD)
				{
					m_TabParam.Add(m_Items[i]);
					m_Tab.m_StrArray.Add(IntToString(((CQuestItemABCD*)m_Items[i])->m_nIndex));
				}
		}
		else if (m_TabShow.GetCurSel()==2)
		{
			for (int i=0;i<m_Items.GetSize();i++)
				if (m_Items[i]->m_Type==ItemQuestABCD)
				{
					CQuestItemABCD* item=(CQuestItemABCD*)m_Items[i];
					if (!(item->m_alt.bMarkA%3==0 && item->m_alt.bMarkB%3==0 && item->m_alt.bMarkC%3==0 && item->m_alt.bMarkD%3==0) && item->m_userAns==0)
					{
						m_TabParam.Add(m_Items[i]);
						m_Tab.m_StrArray.Add(IntToString(((CQuestItemABCD*)m_Items[i])->m_nIndex));
					}
				}
		}
		else if (m_TabShow.GetCurSel()==3)
		{
			for (int i=0;i<m_Items.GetSize();i++)
				if (m_Items[i]->m_Type==ItemQuestABCD)
				{
					CQuestItemABCD* item=(CQuestItemABCD*)m_Items[i];
					if (item->m_Mode==QuestMode::ShowRightAns && item->m_userAns!=item->m_answer && item->m_userAns!=0)
					{
						m_TabParam.Add(m_Items[i]);
						m_Tab.m_StrArray.Add(IntToString(((CQuestItemABCD*)m_Items[i])->m_nIndex));
					}
				}
		}
		
		if (m_Tab.m_StrArray.GetSize()==0) m_Tab.m_nSelected=-2;
		else m_Tab.m_nSelected=0;
		for (int i=0;i<m_Tab.m_StrArray.GetSize();i++)
			if (m_TabParam[i]==nextIt) { m_Tab.m_nSelected=i; break; }
		for (int i=0;i<m_Tab.m_StrArray.GetSize();i++)
			if (m_TabParam[i]==currentIt) { m_Tab.m_nSelected=i; break; }
		//if (nSel<m_Tab.m_StrArray.GetSize()) m_Tab.m_nSelected=nSel;
		//else m_Tab.m_nSelected=m_Tab.m_StrArray.GetSize()-1;
		//if (m_Tab.m_nSelected==-1) m_Tab.m_nSelected=-2;
		m_Tab.Invalidate(0);
		RefreshQuest();
	}

	m_nPrevState=m_cbShow.GetCurSel();
	m_QuestView.RefreshScrollBar();
}


LRESULT CDlgTest::OnDoneQuest(WPARAM wParam, LPARAM lParam)
{
	if (!m_cbShow.GetCurSel()==0 && m_TabShow.GetCurSel()==0)
	{
		if (m_Tab.m_nSelected!=m_Tab.m_StrArray.GetSize()-1)
		{
			m_Tab.m_nSelected++;
			m_Tab.Invalidate(0);
			RefreshQuest();
		}
	}
	else if (!m_cbShow.GetCurSel()==0)
	{
		RefreshView();
	}
	return 0;
}

LRESULT CDlgTest::OnDoneAQuest(WPARAM wParam, LPARAM lParam)
{
	if (m_cbShow.GetCurSel()==0)
		RefreshView();

	if (m_bShowAnswerIm)
	{
		for (int i=0;i<m_Items.GetSize();i++)
			if (m_Items[i]->m_Type==ItemQuestABCD && ((CQuestItemABCD*)m_Items[i])->m_userAns!=0)
			{
				((CQuestItemABCD*)m_Items[i])->m_Mode=ShowRightAns;
				((CQuestItemABCD*)m_Items[i])->m_bShowHint=true;
				((CQuestItemABCD*)m_Items[i])->m_bShowOnRightAns=false;
			}
		m_Items.ReCalcHeight();
		m_Items.RecalcAllContainerDrawHeight();

		m_QuestView.Invalidate(0);
	}
	return 0;
}

afx_msg LRESULT CDlgTest::OnMsgQuestTabChange(WPARAM wParam, LPARAM lParam)
{
	RefreshQuest();
	return 0;
}


void CDlgTest::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
}
