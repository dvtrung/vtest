// PageInfo.cpp : implementation file
//

#include "stdafx.h"
#include "CreateCourse.h"
#include "PageInfo.h"
#include "afxdialogex.h"


// CPageInfo dialog

IMPLEMENT_DYNAMIC(CPageInfo, CPropertyPage)

CPageInfo::CPageInfo()
	: CPropertyPage(CPageInfo::IDD)
	, m_strCourseTitle(_T(""))
	, m_strAuthor(_T(""))
	, m_strSubject(_T(""))
	, m_strDesc(_T(""))
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	m_psp.pszHeaderTitle=L"VOcean";
	m_psp.pszHeaderSubTitle=L"Nhập các thông tin chương trình học";
}

CPageInfo::~CPageInfo()
{
}

void CPageInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strCourseTitle);
	DDX_Text(pDX, IDC_EDIT2, m_strAuthor);
	DDX_Text(pDX, IDC_EDIT3, m_strSubject);
	DDX_Text(pDX, IDC_EDIT4, m_strDesc);
}


BEGIN_MESSAGE_MAP(CPageInfo, CPropertyPage)
END_MESSAGE_MAP()


// CPageInfo message handlers


BOOL CPageInfo::OnSetActive()
{
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}
