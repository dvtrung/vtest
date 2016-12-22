#include "../lib/TestInfo.h"
#pragma once

class CTestArray
{
public:
	class CTestItem
	{
	public:
		CTestInfo m_tInfo;
		int m_nID;
		CString path;

		void Serialize(CArchive& ar);
	};
public:
	CTestArray(void);
	CArray<CTestItem*, CTestItem*> m_Array;
	void AddFromFile(CString fPath);
public:
	~CTestArray(void);
	int GetFreeId();
	CTestArray::CTestItem* GetByID(int nID);
	void Serialize(CArchive& ar);
};
