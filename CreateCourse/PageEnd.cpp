// PageEnd.cpp : implementation file
//

#include "stdafx.h"
#include "CreateCourse.h"
#include "PageEnd.h"
#include "afxdialogex.h"


// CPageEnd dialog

IMPLEMENT_DYNAMIC(CPageEnd, CPropertyPage)

CPageEnd::CPageEnd()
	: CPropertyPage(CPageEnd::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	m_psp.pszHeaderTitle=L"VOcean";
	m_psp.pszHeaderSubTitle=L"Kết thúc tiến trình";
}

CPageEnd::~CPageEnd()
{
}

void CPageEnd::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageEnd, CPropertyPage)
END_MESSAGE_MAP()


// CPageEnd message handlers


BOOL CPageEnd::OnSetActive()
{
	//((CPropertySheet*)GetParent())->SetWizardButtons(0);
	((CPropertySheet*)GetParent())->SetFinishText(L"Kết thúc");

	return CPropertyPage::OnSetActive();
}
