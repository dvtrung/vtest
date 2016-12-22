// DlgPageSetup.cpp : implementation file
//

#include "stdafx.h"
#include "VTest.h"
#include "DlgPageSetup.h"
#include "afxdialogex.h"


// CDlgPageSetup dialog

IMPLEMENT_DYNAMIC(CDlgPageSetup, CDialog)

CDlgPageSetup::CDlgPageSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPageSetup::IDD, pParent)
{

}

CDlgPageSetup::~CDlgPageSetup()
{
}

void CDlgPageSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_EDIT_MARGIN_LEFT,m_nMarginLeft);
	DDX_Control(pDX, IDC_SPIN_MARGIN_LEFT, m_spinMarginLeft);
}


BEGIN_MESSAGE_MAP(CDlgPageSetup, CDialog)
END_MESSAGE_MAP()


// CDlgPageSetup message handlers


BOOL CDlgPageSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_spinMarginLeft.SetBuddy(GetDlgItem(IDC_EDIT_MARGIN_LEFT));
	m_spinMarginLeft.SetRange(0,20);
	m_spinMarginLeft.SetBase(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
