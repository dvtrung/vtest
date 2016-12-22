// DlgAddText.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAddText.h"
#include "resource.h"

// CDlgAddText dialog

IMPLEMENT_DYNAMIC(CDlgAddText, CDialog)

CDlgAddText::CDlgAddText(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddText::IDD, pParent)
{

}

CDlgAddText::~CDlgAddText()
{
}

void CDlgAddText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAddText, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgAddText::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CDlgAddText message handlers

BOOL CDlgAddText::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Text.Create(GetDlgItem(IDC_STATIC_TEXT));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAddText::OnBnClickedOk()
{
	OnOK();
}

int CDlgAddText::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//AfxInitRichEdit();

	return 0;
}
