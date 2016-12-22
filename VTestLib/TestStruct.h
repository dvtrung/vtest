#pragma once

class CTestStruct
{
public:
	CTestStruct(void);
	~CTestStruct(void) {
		Dispose();
	}
	void Dispose() {
		for (int i=0;i<m_arr.GetSize();i++) delete m_arr[i];
		m_arr.RemoveAll();
	}

	void Serialize(CArchive& ar);

	void FromListView(CListCtrl* lv);
	void FillListView(CListCtrl* lv);
		
	CArray<CStringArray*,CStringArray*> m_arr;
};

class CTestStructArray
{
public:
	~CTestStructArray(void) {
		Dispose();
	}
	void Dispose() {
		for (int i=0;i<m_arr.GetSize();i++) delete m_arr[i];
		m_arrStructName.RemoveAll();
	}
	CArray<CTestStruct*,CTestStruct*> m_arr;
	CStringArray m_arrStructName;
	void AddFromListView(CListCtrl* lv, CString);
	void UpdateFromListView(CListCtrl* lv, int index);
	void RemoveAt(int index);
	void Serialize(CArchive& ar);
};