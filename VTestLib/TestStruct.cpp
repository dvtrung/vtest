#include "StdAfx.h"
#include "TestStruct.h"
#include "../lib/appfunc.h"


CTestStruct::CTestStruct(void)
{
}

void CTestStruct::FromListView( CListCtrl* lv )
{
	Dispose();
	for (int i=0;i<lv->GetItemCount()-1;i++)
	{
		CStringArray* arrStr=new CStringArray();
		for (int j=1;j<lv->GetHeaderCtrl()->GetItemCount();j++) 
			arrStr->Add(lv->GetItemText(i,j));
		m_arr.Add(arrStr);
	}
}

void CTestStruct::FillListView( CListCtrl* lv )
{
	lv->DeleteAllItems();
	for (int i=0;i<m_arr.GetSize();i++)
	{
		lv->InsertItem(i,L"Câu "+IntToString(i+1));
		for (int j=0;j<m_arr[i]->GetSize();j++)
		{
			lv->SetItemText(i,j+1,m_arr[i]->GetAt(j));
		}
	}
	lv->InsertItem(m_arr.GetSize(),L"<Add>");
}

void CTestStruct::Serialize(CArchive& ar)
{
	if (ar.IsStoring()) {
		ar << m_arr.GetSize();
		for (int i=0;i<m_arr.GetSize();i++) m_arr[i]->Serialize(ar);
	}
	else {
		int count; ar >> count;
		for (int i=0;i<count;i++) { 
			CStringArray* strArr=new CStringArray();
			strArr->Serialize(ar);
			m_arr.Add(strArr);
		}
	}
}

void CTestStructArray::AddFromListView(CListCtrl* lv, CString strName)
{
	CTestStruct* t=new CTestStruct();
	t->FromListView(lv);
	m_arr.Add(t);
	m_arrStructName.Add(strName);
}

void CTestStructArray::UpdateFromListView( CListCtrl* lv, int index )
{
	m_arr[index]->FromListView(lv);
}

void CTestStructArray::RemoveAt( int index )
{
	delete m_arr[index];
	m_arr.RemoveAt(index);
}

void CTestStructArray::Serialize( CArchive& ar )
{
	m_arrStructName.Serialize(ar);
	if (ar.IsStoring()) {
		ar << m_arr.GetSize();
		for (int i=0;i<m_arr.GetSize();i++) m_arr[i]->Serialize(ar);
	}
	else {
		int count; ar >> count;
		for (int i=0;i<count;i++) { 
			CTestStruct* ts=new CTestStruct();
			ts->Serialize(ar);
			m_arr.Add(ts);
		}
	}
}
