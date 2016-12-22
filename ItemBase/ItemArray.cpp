#include "StdAfx.h"
#include "ItemArray.h"
#include "../lib/appfunc.h"

CItemArray::CItemArray(void)
{
	m_hlItem=-1;
	m_bDispose=true;
}

CItemArray::~CItemArray(void)
{
	if (m_bDispose)
		for (int i=0;i<m_Array.GetSize();i++) delete m_Array[i];
}

void CItemArray::Draw( Graphics* gr, Point ptTopLeft)
{
	int top=0;
	for (int i=0;i<m_Array.GetSize();i++)
	{
// 		if (m_Array[i]->m_Type==ItemContainer)
// 		{
// 			int idEnd=GetItemIndex(((CContainerItemStart*)m_Array[i])->m_itEnd);
// 			if (i<=m_hlItem && m_hlItem<=idEnd)
// 				m_Array[i]->Draw(gr,Point(ptTopLeft.X,top+ptTopLeft.Y),m_Width,true);
// 			else m_Array[i]->Draw(gr,Point(ptTopLeft.X,top+ptTopLeft.Y),m_Width,i==m_hlItem);
// 		}
// 		else
			m_Array[i]->Draw(gr,Point(ptTopLeft.X,top+ptTopLeft.Y),m_Width,i==m_hlItem);
		
		top+=m_Array[i]->height;
	}
}

int CItemArray::GetItemIndex(CItemBase* it)
{
	for (int i=0;i<m_Array.GetSize();i++) if (m_Array[i]==it) return i;
}

void CItemArray::DrawDrag(Graphics* gr, Point ptTopLeft, int nItem, int nMouseOverItem)
{
	int top=0;
	for (int i=0;i<m_Array.GetSize();i++)
	{
		if (nMouseOverItem==m_hlItem) nMouseOverItem=-1;

		if (m_Array[i]->m_Type==ItemContainer)
		{
			int idEnd=GetItemIndex(((CContainerItemStart*)m_Array[i])->m_itEnd);
			if ((i<=nMouseOverItem && nMouseOverItem<=idEnd))
				m_Array[i]->Draw(gr,Point(ptTopLeft.X,top+ptTopLeft.Y),m_Width,true);
			else m_Array[i]->Draw(gr,Point(ptTopLeft.X,top+ptTopLeft.Y),m_Width,i==m_hlItem || i==nMouseOverItem);
		}
		else
			m_Array[i]->Draw(gr,Point(ptTopLeft.X,top+ptTopLeft.Y),m_Width,i==m_hlItem || i==nMouseOverItem);

		if (i==nMouseOverItem)
		{
			Pen pen(Color::Black,2);
			gr->DrawLine(&pen,Point(ptTopLeft.X,ptTopLeft.Y+top),Point(ptTopLeft.X+m_Width,ptTopLeft.Y+top));
		}

		top+=m_Array[i]->height;
	}
}

void CItemArray::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar << m_Array.GetSize();
		ItemType type;
		for (int i=0;i<m_Array.GetSize();i++) 
		{
			ar << m_Array[i]->m_Type;
			m_Array[i]->Serialize(ar);
			if (m_Array[i]->m_Type==ItemContainer)
				ar << GetItemIndex(((CContainerItemStart*)m_Array[i])->m_itEnd);
		}
		ar << m_Height;
	}
	else
	{
		int count; ar >> count;
		int type;
		for (int i=0;i<count;i++)
		{
			ar >> type;
			if (type==ItemQuestABCD)
			{
				CQuestItemABCD* it=new CQuestItemABCD();
				it->Serialize(ar);
				m_Array.Add(it);
			}
			else if (type==ItemQuestTrueFalse)
			{
				CQuestItemTrueFalse* it=new CQuestItemTrueFalse();
				it->Serialize(ar);
				m_Array.Add(it);
			}
			else if (type==ItemText)
			{
				CTextItem* it=new CTextItem();
				it->Serialize(ar);
				m_Array.Add(it);
			}
			else if (type==ItemContainer)
			{
				CContainerItemStart* it=new CContainerItemStart();
				it->Serialize(ar);
				int i;
				ar >> i;
				it->m_itEnd=(CContainerItemEnd*)i;
				m_Array.Add(it);
			}
			else if (type==ItemContainerEnd)
			{
				CContainerItemEnd* it=new CContainerItemEnd();
				m_Array.Add(it);
			}
		}

		ar >> m_Height;

		for (int i=0;i<m_Array.GetSize();i++)
			if (m_Array[i]->m_Type==ItemContainer)
			{
				((CContainerItemStart*)m_Array[i])->m_itEnd=(CContainerItemEnd*)m_Array[(int)((CContainerItemStart*)m_Array[i])->m_itEnd];
			}

		for (int i=0;i<m_Array.GetSize();i++) { m_Array[i]->m_Font=m_Font; }
	}
}

void CItemArray::AddItem(ItemType t, int after, bool bEdit)
{
	if (after==-1) after=m_Array.GetSize();

	CItemBase* it;
	if (t==ItemContainer)
	{
		it=new CContainerItemStart();
		CContainerItemEnd* itEnd=new CContainerItemEnd();
		itEnd->m_Font=m_Font;
		((CContainerItemStart*)it)->m_itEnd=itEnd;
		itEnd->m_itStart=(CContainerItemStart*)it;

		RedrawItem(itEnd);
	}
	else
	{
		switch (t)
		{
		case ItemText:				it=new CTextItem(); break;
		case ItemQuestABCD:			it=new CQuestItemABCD(); break;
		case ItemQuestTrueFalse:	it=new CQuestItemTrueFalse(); break;
		case ItemQuest:				it=new CQuestItem(); break;
		}
		it->m_Font=m_Font;

		m_Array.InsertAt(after,it);
	}

	ResetIndex();
	RedrawItem(it);

	if (bEdit) it->Edit(NULL);
}

// CString CItemArray::ReplaceString(CString str)
// {
// 	CString s=str;
// 	s.Replace(L"<Ten_De_Thi>",m_tInfo->m_strTitle);
// 	s.Replace(L"<Mon_Thi>",m_tInfo->m_strSubject);
// 	s.Replace(L"<Thoi_Gian>",IntToString(m_tInfo->m_nTime));
// 	return s;
// }

void CItemArray::RedrawItem(CItemBase* item)
{
	if (item->m_Type==ItemText)
	{
		CString s=/*ReplaceString*/(((CTextItem*)item)->m_strText);
		CString s0=((CTextItem*)item)->m_strText;
		((CTextItem*)item)->m_strText=s;
		item->ReDrawBmp(m_Width);
		((CTextItem*)item)->m_strText=s0;
	}
	else item->ReDrawBmp(m_Width);
}

void CItemArray::ResetIndex()
{
	int c=0;
	for (int i=0;i<m_Array.GetSize();i++) 
	{
		switch (m_Array[i]->m_Type)
		{
		case ItemQuestTrueFalse:
			c++; 
			((CQuestItemTrueFalse*)m_Array[i])->index=c; 
			break;
		case ItemQuestABCD:
			c++; 
			((CQuestItemABCD*)m_Array[i])->m_nIndex=c; 
			break;
		case ItemQuest:
			c++; 
			((CQuestItem*)m_Array[i])->m_nIndex=c; 
			break;
		case ItemText:
			if (((CTextItem*)m_Array[i])->m_nIndex!=-1)
			{
				c++;
				((CTextItem*)m_Array[i])->m_nIndex=c;
				break;
			}
		}
	}
}

void CItemArray::DeleteItem(int nIndex)
{
	delete m_Array[nIndex]; m_Array.RemoveAt(nIndex);
	ResetIndex();
}

void CItemArray::DeleteAllItems()
{
	for (int i=0;i<m_Array.GetSize();i++) delete m_Array[i];
	m_Array.RemoveAll();
}

void CItemArray::RecalcAllItems()
{
	if (AfxGetMainWnd()==NULL) return;
	Graphics gr(AfxGetMainWnd()->m_hWnd);
	for (int i=0;i<m_Array.GetSize();i++) RedrawItem(m_Array[i]);
}

void CItemArray::ReCalcHeight()
{
	m_Height=0;
	for (int i=0;i<m_Array.GetSize();i++) { m_Array[i]->ReCalcHeight(); m_Height+=m_Array[i]->height; }
	RecalcAllContainerDrawHeight();
}

int CItemArray::GetItemUnderMouse(CPoint pt)
{
	int top=0;
	for (int i=0;i<m_Array.GetSize();i++)
	{
		CRect rc(0,top,m_Width,top+m_Array[i]->height);
		if (PtInRect(&rc,pt)) return i;
		top+=m_Array[i]->height;
	}
	return -1;
}

bool CItemArray::CheckMouseOver(int x, int y)
{
	int top=0;
	for (int i=0;i<m_Array.GetSize();i++)
	{
		CRect rc(0,top,m_Width,top+m_Array[i]->height);
		if (PtInRect(&rc,CPoint(x,y)))
		{
			return m_Array[i]->CheckMouseOver(x,y-top);
		}
		top+=m_Array[i]->height;
	}
	return false;
}

void CItemArray::RecalcContainerDrawHeight(int nIndex)
{
	CContainerItemStart* itStart=(CContainerItemStart*)m_Array[nIndex];
	CContainerItemEnd* itEnd=itStart->m_itEnd;

	int h=0;
	for (int i=nIndex;i<m_Array.GetSize();i++)
	{
		h+=m_Array[i]->height;
		if (m_Array[i]==itEnd) break;
	}
	itStart->drawHeight=h;
}

void CItemArray::RecalcAllContainerDrawHeight()
{
	for (int i=0;i<m_Array.GetSize();i++)
		if (m_Array[i]->m_Type==ItemContainer) RecalcContainerDrawHeight(i);
}

void CItemArray::SetQuestMode(QuestMode mode, bool bHintOnRightAns)
{
	for (int i=0;i<m_Array.GetSize();i++)
	{
		if (IsQuestType(m_Array[i]->m_Type))
		{
			((CQuestItemBase*)m_Array[i])->m_Mode=mode;
		}
	}

	ReCalcHeight();
}

void CItemArray::ShowHint(bool bShowHint, bool bShowOnRightAns)
{
	for (int i=0;i<m_Array.GetSize();i++)
	{
		if (IsQuestType(m_Array[i]->m_Type))
		{
			((CQuestItemBase*)m_Array[i])->m_bShowHint=bShowHint;
			((CQuestItemBase*)m_Array[i])->m_bShowOnRightAns=bShowOnRightAns;			
		}
	}

	ReCalcHeight();
}