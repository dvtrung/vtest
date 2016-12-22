// PageProcess.cpp : implementation file
//

#include "stdafx.h"
#include "CreateCourse.h"
#include "PageProcess.h"
#include "afxdialogex.h"
#include "..\lib\appfunc.h"
#include "app.h"

extern CPageChooseFiles* m_pgChooseFiles;
extern CPageInfo* m_pgInfo;

// CPageProcess dialog

IMPLEMENT_DYNAMIC(CPageProcess, CPropertyPage)

CPageProcess::CPageProcess()
	: CPropertyPage(CPageProcess::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	m_psp.pszHeaderTitle=L"VOcean";
	m_psp.pszHeaderSubTitle=L"Tạo tập tin chứa chương trình học";
}

CPageProcess::~CPageProcess()
{
}

void CPageProcess::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageProcess, CPropertyPage)
END_MESSAGE_MAP()


// CPageProcess message handlers


BOOL CPageProcess::OnSetActive()
{
	int nRet=CPropertyPage::OnSetActive();

	((CPropertySheet*)GetParent())->SetWizardButtons(NULL);

	RecursiveDelete(L"Temp");

	CreateDirectory(L"Temp",NULL);
	
	nFile=1;
	MoveFile(m_pgChooseFiles->m_Tree.GetChildItem(TVI_ROOT));

	SaveToFile(L"Temp\\0.d");

	((CPropertySheet*)GetParent())->SetActivePage(((CPropertySheet*)GetParent())->GetActiveIndex()-1);
	//RecursiveDelete(L"Temp");
	
	return nRet;
}

void CPageProcess::MoveFile(HTREEITEM hParent)
{
	HTREEITEM hi=m_pgChooseFiles->m_Tree.GetChildItem(hParent);
	while (hi!=NULL)
	{
		CString str=m_pgChooseFiles->m_Tree.GetItemText(hi);
		if (m_pgChooseFiles->m_Tree.GetItemData(hi)!=NULL)
		{
			CString* s=(CString*)m_pgChooseFiles->m_Tree.GetItemData(hi);
			CString strExt;
			if ((*s).Right(6)==L".vtest") strExt=L"01";
			else if ((*s).Right(6)==L".vtext") strExt=L"02";
			CopyFile((*s),L"Temp\\"+IntToString(nFile)+L"."+strExt,false);
			*s=IntToString(nFile)+L"."+strExt;
			nFile++;
		}
		else
			MoveFile(hi);
		hi=m_pgChooseFiles->m_Tree.GetNextSiblingItem(hi);
	}
}

void CPageProcess::SaveToFile(CString strPath)
{
	CFile f; 
	f.Open(strPath,CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&f,CArchive::store);
	ar << m_pgInfo->m_strCourseTitle;
	ar << m_pgInfo->m_strAuthor;
	ar << m_pgInfo->m_strSubject;
	ar << m_pgInfo->m_strDesc;
	m_pgChooseFiles->SerializeTree(ar);
	ar.Close();
	f.Close();
}
