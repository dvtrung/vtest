#include "stdafx.h"
#include "TestHistory.h"

CTestHistory::CTestHistory()
{

}

void CTestHistory::SetToItemArray( CItemArray* itArr )
{
	for (int i=0;i<itArr->GetSize();i++)
	{
		if (itArr->GetAt(i)->m_Type==ItemQuestABCD) ((CQuestItemABCD*)itArr->GetAt(i))->m_userAns=m_hisArr[i];
	}
}

void CTestHistory::FromItemArray( CItemArray* itArr )
{
	for (int i=0;i<itArr->GetSize();i++)
	{
		if (itArr->GetAt(i)->m_Type==ItemQuestABCD) m_hisArr.Add(((CQuestItemABCD*)itArr->GetAt(i))->m_userAns);
		else m_hisArr.Add(-1);
	}
}

void CTestHistory::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar << m_hisArr.GetSize();
		for (int i=0;i<m_hisArr.GetSize();i++) ar << m_hisArr[i];
		ar << m_SoCau;
		ar << m_SoCauDung;
		ar << m_SoCauLam;
		ar << m_ThoiGian;
		ar << m_ThoiGianLam;
		ar << m_TakenTime;
	}
	else
	{
		int count; ar >> count;
		for (int i=0;i<count;i++) { int x; ar >> x; m_hisArr.Add(x); }
		ar >> m_SoCau;
		ar >> m_SoCauDung;
		ar >> m_SoCauLam;
		ar >> m_ThoiGian;
		ar >> m_ThoiGianLam;
		ar >> m_TakenTime;
	}
}

void CTestHistoryArray::Serialize( CArchive& ar )
{
	if (ar.IsStoring())
	{
		ar << m_Array.GetSize();
		for (int i=0;i<m_Array.GetSize();i++) m_Array[i]->Serialize(ar);
	}
	else
	{
		int count; ar >> count;
		for (int i=0;i<count;i++) { CTestHistory* t=new CTestHistory(); t->Serialize(ar); m_Array.Add(t); }
	}
}
