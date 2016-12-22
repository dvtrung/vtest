// PageChooseOutput.cpp : implementation file
//

#include "stdafx.h"
#include "CreateCourse.h"
#include "PageChooseOutput.h"
#include "afxdialogex.h"

extern CPageProcess* m_pgProcess;
// CPageChooseOutput dialog

IMPLEMENT_DYNAMIC(CPageChooseOutput, CPropertyPage)

CPageChooseOutput::CPageChooseOutput()
	: CPropertyPage(CPageChooseOutput::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	m_psp.pszHeaderTitle=L"VOcean";
	m_psp.pszHeaderSubTitle=L"Thiết lập tập tin xuất";
}

CPageChooseOutput::~CPageChooseOutput()
{
}

void CPageChooseOutput::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageChooseOutput, CPropertyPage)
	ON_BN_CLICKED(IDC_CHOOSE, &CPageChooseOutput::OnBnClickedChoose)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TO_FILE, &CPageChooseOutput::OnBnClickedButtonSaveToFile)
END_MESSAGE_MAP()


// CPageChooseOutput message handlers


void CPageChooseOutput::OnBnClickedChoose()
{
	CFileDialog dlg(FALSE,NULL,NULL,
		OFN_DONTADDTORECENT | OFN_OVERWRITEPROMPT,
		L"VOcean Course Files|*.voc||",this,0);
	if (dlg.DoModal()==IDOK)
	{
		CString strPath=dlg.GetPathName();
	}
}


void CPageChooseOutput::OnBnClickedButtonSaveToFile()
{
	CFileDialog dlg(FALSE,NULL,NULL,
		OFN_DONTADDTORECENT | OFN_OVERWRITEPROMPT,
		L"Data Files|*.dat||",this,0);
	if (dlg.DoModal()==IDOK)
	{
		CString strPath=dlg.GetPathName();
		m_pgProcess->SaveToFile(strPath);
		AfxGetApp()->DoMessageBox(L"Đã lưu xong",MB_OK | MB_ICONINFORMATION,0);
	}
}
