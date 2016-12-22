#include "StdAfx.h"
#include "TestArray.h"
#include "../lib/appfunc.h"

CTestArray::CTestArray(void)
{
}

CTestArray::~CTestArray(void)
{
}

int CTestArray::GetFreeId()
{
	int r=0;
	bool b=true;
	while (b)
	{
		b=false; r++;
		for (int i=0;i<m_Array.GetSize();i++) if (m_Array[i]->m_nID==r) b=true;
	}
	return r;
}

CTestArray::CTestItem* CTestArray::GetByID(int nID)
{
	for (int i=0;i<m_Array.GetSize();i++)
		if (m_Array[i]->m_nID==nID) return m_Array[i];
}

void CTestArray::AddFromFile( CString fPath )
{
	int id=GetFreeId();
	CopyFile(fPath,L".\\data\\T\\"+IntToString(id)+L".dat",FALSE);

	CFile f; 
 	f.Open(fPath,CFile::modeRead);
 	CArchive ar(&f,CArchive::load);
	CTestItem* t=new CTestItem();
	t->m_nID=id;
	t->path=IntToString(id)+L".dat";
	t->m_tInfo.Serialize(ar);
	m_Array.Add(t);
 	ar.Close();
 	f.Close();
}

void CTestArray::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
	else
	{

	}
}

void CTestArray::CTestItem::Serialize( CArchive& ar )
{
	m_tInfo.Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_nID;
	}
	else
	{
		ar >> m_nID;
	}
}
