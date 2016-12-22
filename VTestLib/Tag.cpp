#include "stdafx.h"
#include "Tag.h"
#include "../lib/appfunc.h"

CTag::CTag(CTag& other)
{
	*this=other;
}

void CTagArray::Free()
{
	for (int i=0;i<m_Array.GetSize();i++) { delete m_Array[i]; } m_Array.RemoveAll();
	m_TagName.RemoveAll();
}

void CTagArray::operator = (CTagArray& other)
{
	Free();
	for (int i=0;i<other.m_Array.GetSize();i++) 
	{
		CTag* t=new CTag(*other[i]);
		Add(t);
	}
}

void CTagArray::AddTagName(CString name)
{
	m_TagName.Add(name);
	for (int i=0;i<m_Array.GetSize();i++)
		m_Array[i]->m_arrTagItem.Add(L"");
}

void CTagArray::SetTag( int id, int nTagIndex, CString str )
{
	m_Array[id]->m_arrTagItem[nTagIndex]=str;
}

CTag* CTagArray::AddItem()
{
	CTag* t=new CTag();
	for (int i=0;i<m_TagName.GetSize();i++) t->m_arrTagItem.Add(L"");
	m_Array.Add(t);
	return t;
}

void CTagArray::Serialize(CArchive& ar)
{
	m_TagName.Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_Array.GetSize();
		for (int i=0;i<m_Array.GetSize();i++) m_Array[i]->Serialize(ar);
	}
	else
	{
		int count; ar >> count;
		for (int i=0;i<count;i++) { AddItem(); m_Array[i]->Serialize(ar); }
	}
}

void CTagArray::GetItemsInTag(CStringArray& arr, int tagIndex)
{
	arr.RemoveAll();
	for (int i=0;i<m_Array.GetSize();i++)
	{
		CString str=m_Array[i]->m_arrTagItem[tagIndex];
		int j;
		for (j=0;j<arr.GetSize();j++) if (arr[j]==str) break;
		if (j==arr.GetSize()) arr.Add(str);
	}
}

void CTagArray::DeleteTag( CString name )
{
	for (int i=0;i<m_TagName.GetSize();i++)
		if (m_TagName[i]==name)
		{
			m_TagName.RemoveAt(i);
			for (int j=0;j<m_Array.GetSize();j++)
				m_Array[j]->m_arrTagItem.RemoveAt(i);
			return;
		}
}

void CTagArray::Filter(CStringArray& filterArr,CArray<int,int>& idArr)
{
	for (int i=0;i<m_Array.GetSize();i++) 
	{
		bool b=true;
		for (int j=0;j<m_TagName.GetSize();j++)
		{
			CStringArray arr;
			filterArr[j].Replace(L"; ",L";");
			SplitString(filterArr[j],L';',arr);

			bool b2=false;
			if (filterArr[j]!=L"")
			{
				for (int k=0;k<arr.GetSize();k++) 
					if (m_Array[i]->m_arrTagItem.GetAt(j).Find(arr[k])!=-1) { b2=true; break; }
			}
			else b2=true;
			if (!b2) { b=false; break; }
		}
		if (b) idArr.Add(i);
	}
}

void CTag::operator = (CTag& other)
{
	m_arrTagItem.RemoveAll();
	for (int i=0;i<other.m_arrTagItem.GetSize();i++)
		m_arrTagItem.Add(other.m_arrTagItem[i]);
}

void CTag::Serialize(CArchive& ar)
{
	m_arrTagItem.Serialize(ar);
}
