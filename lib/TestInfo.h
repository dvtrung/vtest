#pragma once

class CTestInfo
{
public:
	CTestInfo(void);
public:
	~CTestInfo(void);

	CString m_strTitle;
	CString m_strSubject;
	int m_nTime;
	CString m_strAuthor;
	CStringArray m_StudentType;
	CString m_strOtherInfo;

	void operator = (CTestInfo& o)
	{
		m_strTitle=o.m_strTitle;
		m_strSubject=o.m_strSubject;
		m_nTime=o.m_nTime;
		m_strAuthor=o.m_strAuthor;
		m_strOtherInfo=o.m_strOtherInfo;
		m_StudentType.RemoveAll();
		m_StudentType.Append(o.m_StudentType);
	}

	void Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			ar << m_strTitle;
			ar << m_strSubject;
			ar << m_nTime;
			ar << m_strAuthor;
			ar << m_strOtherInfo;
			ar << m_StudentType.GetSize();
			for (int i=0;i<m_StudentType.GetSize();i++) ar << m_StudentType[i];
		}
		else
		{
			ar >> m_strTitle;
			ar >> m_strSubject;
			ar >> m_nTime;
			ar >> m_strAuthor;
			ar >> m_strOtherInfo;
			/*CString str; ar >> str;*/
			int count; ar >> count;
			for (int i=0;i<count;i++) { CString str; ar >> str; m_StudentType.Add(str); }
		}
	}
};
