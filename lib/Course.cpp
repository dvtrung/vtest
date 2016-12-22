#include "StdAfx.h"
#include "Course.h"


CCourse::CCourse(void)
{
}


CCourse::~CCourse(void)
{
}

void CCourse::LoadFromFile(CString strPath)
{
	CFile f; 
	f.Open(strPath,CFile::modeRead);
	CArchive ar(&f,CArchive::load);
	ar >> m_strCourseTitle;
	ar >> m_strAuthor;
	ar >> m_strSubject;
	ar >> m_strDesc;
	
	m_Tree1Arr.RemoveAll();
	int i; CString str;
	ar >> i;
	while (i!=0)
	{
		ar >> str;
		m_Tree1Arr.Add(str);
		ar >> i;
	}

	int index;
	ar >> index;
	while (index!=0)
	{
		m_Tree2ArrType.Add(index);
		if (index==1)
		{
			CString str; ar >> str;
			m_Tree2ArrStr.Add(str);
			m_Tree2ArrIndex.Add(0);
		}
		else if (index==2)
		{
			int i; ar >> i;
			m_Tree2ArrIndex.Add(i);
			m_Tree2ArrStr.Add(NULL);
		}
		ar >> index;
	}
}
