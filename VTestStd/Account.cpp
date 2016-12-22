#include "StdAfx.h"
#include "Account.h"

CAccount::CAccount(void)
{
}

CAccount::~CAccount(void)
{
}

void CAccount::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << userName;
		ar << passWord;
		ar << place;
		ar << note;
		m_CourseArray.Serialize(ar);
	}
	else
	{
		ar >> userName;
		ar >> passWord;
		ar >> place;
		ar >> note;
		m_CourseArray.Serialize(ar);
	}
}