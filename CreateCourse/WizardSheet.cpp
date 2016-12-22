// WizardSheet.cpp : implementation file
//

#include "stdafx.h"
#include "CreateCourse.h"
#include "WizardSheet.h"


// CWizardSheet

IMPLEMENT_DYNAMIC(CWizardSheet, CPropertySheet)


CWizardSheet::CWizardSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CWizardSheet::CWizardSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CWizardSheet::~CWizardSheet()
{
}

int CALLBACK CWizardSheet::PropSheetProc(HWND hWndDlg, UINT uMsg, LPARAM lParam)
{
	switch(uMsg)
	{
	case PSCB_PRECREATE:
		{
			LPDLGTEMPLATE pResource = (LPDLGTEMPLATE)lParam;
			CDialogTemplate dlgTemplate(pResource);
			dlgTemplate.SetFont(L"Tahoma",10);
			memmove((void*)lParam, dlgTemplate.m_hTemplate, dlgTemplate.m_dwTemplateSize);
		}
		break;
	}
	return 0;
}

void CWizardSheet::BuildPropPageArray()
{
	CPropertySheet::BuildPropPageArray();

		LPCPROPSHEETPAGE ppsp = m_psh.ppsp;
		const int nSize = static_cast<int>(m_pages.GetSize());

		for(int nPage = 0; nPage < nSize; nPage++)
		{
			const DLGTEMPLATE* pResource = ppsp->pResource;
			CDialogTemplate dlgTemplate(pResource);
			dlgTemplate.SetFont(L"Tahoma", 10);
			memmove((void*)pResource, dlgTemplate.m_hTemplate, dlgTemplate.m_dwTemplateSize);

			(BYTE*&)ppsp += ppsp->dwSize;
		}
}


BEGIN_MESSAGE_MAP(CWizardSheet, CPropertySheet)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CWizardSheet message handlers


BOOL CWizardSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	this->SetTitle(L"Create A Course");
	GetDlgItem(IDCANCEL)->SetWindowTextW(L"Thoát");
	GetDlgItem(IDHELP)->SetWindowTextW(L"Trợ giúp");
	GetDlgItem(ID_WIZNEXT)->SetWindowTextW(L"Tiếp");
	GetDlgItem(ID_WIZBACK)->SetWindowTextW(L"Quay lại");

	return bResult;
}


int CWizardSheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


BOOL CWizardSheet::PreCreateWindow(CREATESTRUCT& cs)
{
	return CPropertySheet::PreCreateWindow(cs);
}


INT_PTR CWizardSheet::DoModal()
{
	m_psh.pfnCallback = &CWizardSheet::PropSheetProc;
	m_psh.dwFlags |= (PSH_USECALLBACK | PSH_HEADER | PSH_WATERMARK | PSH_WIZARD | PSH_WIZARD97);
	m_psh.pszbmHeader=MAKEINTRESOURCE(IDB_ICON_HEADER);
	m_psh.pszbmWatermark=MAKEINTRESOURCE(IDB_WATERMARK);
	m_psh.hIcon=AfxGetApp()->LoadIconW(IDI_GLOBE);

	m_psh.hInstance = AfxGetInstanceHandle(); 

	return CPropertySheet::DoModal();
}
