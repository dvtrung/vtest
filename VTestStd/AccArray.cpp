#include "StdAfx.h"
#include "AccArray.h"
#include "../lib/appfunc.h"

CAccArray::CAccArray(void)
{
}

CAccArray::~CAccArray(void)
{
	SaveAccount();
	for (int i=0;i<m_Array.GetSize();i++)
		delete m_Array[i];
}

void CAccArray::SaveAccount()
{
	CFile f; 
	f.Open(L".\\data\\acc.dat",CFile::modeWrite);
	CArchive ar(&f,CArchive::store);
	ar << m_Array.GetSize();
	for (int i=0;i<m_Array.GetSize();i++)
	{
		m_Array[i]->Serialize(ar);
	}
	ar.Close();
	f.Close();
}

void CAccArray::LoadAccount()
{

	// Reset
// 	CFile f; 
// 	f.Open(GetAppDirectory()+L"\\data\\acc.dat",CFile::modeWrite);
// 	CArchive ar(&f,CArchive::store);
// 	ar << 0;
// 	ar.Close();
// 	f.Close();



	CFile f; 
	f.Open(L".\\data\\acc.dat",CFile::modeRead);
	CArchive ar(&f,CArchive::load);
	int count;
	ar >> count;
	for (int i=0;i<count;i++)
	{
		CAccount* acc=new CAccount();
		m_Array.Add(acc);
		acc->Serialize(ar);
	}
	ar.Close();
	f.Close();
}

CAccount* CAccArray::AddAccount()
{
	CAccount* acc=new CAccount();
	m_Array.Add(acc);
	return acc;
}