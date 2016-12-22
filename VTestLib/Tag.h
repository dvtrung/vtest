#pragma once

class CTag
{
public:
	CTag(void) { }
	CTag(CTag& other);

	CStringArray m_arrTagItem;
	void operator = (CTag& other);
	CString operator [] (int i)
	{
		return m_arrTagItem[i];
	}
	void Serialize(CArchive& ar);
};

class CTagArray
{
public:
	~CTagArray() { Free(); }
	CStringArray m_TagName;
	CArray<CTag*> m_Array;
	CTag* operator [] (int i) { return m_Array[i]; }
	void Free();
	void operator = (CTagArray& other);
	void Add(CTag* it) { m_Array.Add(it); }
	void RemoveAt(int i) { delete m_Array[i]; m_Array.RemoveAt(i); }
	int GetSize() { return m_Array.GetSize(); }
	void AddTagName(CString name);
	void DeleteTag(CString name);
	void SetTag(int id, int nTagIndex, CString str);
	CTag* AddItem();
	void Serialize(CArchive& ar);
	void GetItemsInTag(CStringArray& arr, int tagIndex);
	void Filter(CStringArray& filterArr,CArray<int,int>& idArr);
};
