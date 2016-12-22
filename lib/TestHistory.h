#pragma once
#include "../ItemBase/ItemArray.h"

class CTestHistory
{
public:
	CTestHistory();
	CArray<int,int> m_hisArr;
	void SetToItemArray(CItemArray* itArr);
	void FromItemArray(CItemArray* itArr);
	void Serialize(CArchive& ar);

	int m_SoCau;
	int m_SoCauDung;
	int m_SoCauLam;
	int m_ThoiGian;
	int m_ThoiGianLam;
	CString m_TakenTime;
};

class CTestHistoryArray
{
public:
	CTestHistoryArray() {}
	~CTestHistoryArray() { for (int i=0;i<m_Array.GetSize();i++) delete m_Array[i]; }

	CArray<CTestHistory*, CTestHistory*> m_Array;

	void Serialize(CArchive& ar);
};