// DlgNewWizard.cpp : implementation file
//

#include "stdafx.h"
#include "VTest.h"
#include "DlgNewWizard.h"


// CDlgNewWizard dialog

IMPLEMENT_DYNAMIC(CDlgNewWizard, CDialog)

CDlgNewWizard::CDlgNewWizard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewWizard::IDD, pParent)
{

}

CDlgNewWizard::~CDlgNewWizard()
{
}

void CDlgNewWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_TEXT,m_strText);
}


BEGIN_MESSAGE_MAP(CDlgNewWizard, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgNewWizard::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CDlgNewWizard message handlers

void CDlgNewWizard::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

BOOL CDlgNewWizard::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(lpszTemplateName, pParentWnd);
}

int CDlgNewWizard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	AfxInitRichEdit2();


	return 0;
}

BOOL CDlgNewWizard::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
