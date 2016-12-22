// PageStart.cpp : implementation file
//

#include "stdafx.h"
#include "CreateCourse.h"
#include "PageStart.h"
#include "afxdialogex.h"

extern CPageInfo* m_pgInfo;
extern CPageChooseFiles* m_pgChooseFiles;

// CPageStart dialog

IMPLEMENT_DYNAMIC(CPageStart, CPropertyPage)

CPageStart::CPageStart()
	: CPropertyPage(CPageStart::IDD)
	, m_strPath(_T(""))
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	m_psp.pszHeaderTitle=L"VOcean";
	m_psp.pszHeaderSubTitle=L"Tạo chương trình học";
	//m_psp.pszHeaderSubTitle=L"Bắt đầu tiến trình tạo khóa học mới";
	//m_psp.pszIcon=MAKEINTRESOURCE(IDI_FOLDER);
	//m_psp.pszTitle=L"VOcean";
	//m_psp.dwFlags |= PSP_DEFAULT|PSP_HIDEHEADER;
}

CPageStart::~CPageStart()
{
}

void CPageStart::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Text(pDX,IDC_EDIT1,m_strPath);
}


BEGIN_MESSAGE_MAP(CPageStart, CPropertyPage)
	ON_BN_CLICKED(IDC_SELECTFILE, &CPageStart::OnBnClickedSelectfile)
	ON_BN_CLICKED(IDC_RADIO1, &CPageStart::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CPageStart::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CPageStart message handlers


BOOL CPageStart::OnSetActive()
{
	((CPropertySheet*)GetParent())->SetWizardButtons(PSWIZB_NEXT);

	return CPropertyPage::OnSetActive();
}


void CPageStart::OnSetFont(CFont* pFont)
{
	// TODO: Add your specialized code here and/or call the base class

	CPropertyPage::OnSetFont(pFont);
}


void CPageStart::OnBnClickedSelectfile()
{
	CFileDialog dlgFile(TRUE, NULL , NULL, 
		OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
		L"Data Files|*.dat||", 
		this, 0);

	if (dlgFile.DoModal()==IDOK)
	{
		m_strPath=dlgFile.GetPathName();
		UpdateData(FALSE);
	}
}


BOOL CPageStart::OnKillActive()
{
	UpdateData(FALSE);
	static bool bKill=true;
	if (!bKill) return CPropertyPage::OnKillActive();
	if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck()==1)
	{

	}
	else
	{
		bKill=false;
		CFile f; 
		f.Open(m_strPath,CFile::modeRead);
		CArchive ar(&f,CArchive::load);
		ar >> m_pgInfo->m_strCourseTitle;
		ar >> m_pgInfo->m_strAuthor;
		ar >> m_pgInfo->m_strSubject;
		ar >> m_pgInfo->m_strDesc;
		if (m_pgChooseFiles->m_hWnd!=NULL)
			m_pgChooseFiles->SerializeTree(ar);
		else
		{
			((CPropertySheet*)GetParent())->SetActivePage(m_pgChooseFiles);
			//((CPropertySheet*)GetParent())->SetActivePage(3);
			m_pgChooseFiles->SerializeTree(ar);
			((CPropertySheet*)GetParent())->SetActivePage(this);
		}
		ar.Close();
		f.Close();
		bKill=true;
	}

	return CPropertyPage::OnKillActive();
}


void CPageStart::OnBnClickedRadio1()
{
	if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck()==1)
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(0);
		GetDlgItem(IDC_SELECTFILE)->EnableWindow(0);
	}
	else
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(1);
		GetDlgItem(IDC_SELECTFILE)->EnableWindow(1);
	}
}


void CPageStart::OnBnClickedRadio2()
{
	OnBnClickedRadio1();
}


BOOL CPageStart::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	OnBnClickedRadio1();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
