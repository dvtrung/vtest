#pragma once

class CAccount
{
public:
	CAccount(void);
public:
	~CAccount(void);

public:
	CString userName;
	CString passWord;
	CString place;
	CString note;
	CStringArray m_CourseArray;

public:
	void Serialize(CArchive& ar);
};
