// DlgAddQuest.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAddQuest.h"
#include "afxdialogex.h"


// CDlgAddQuest dialog

IMPLEMENT_DYNAMIC(CDlgAddQuest, CDialog)

CDlgAddQuest::CDlgAddQuest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddQuest::IDD, pParent)
{

}

CDlgAddQuest::~CDlgAddQuest()
{
}

void CDlgAddQuest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAddQuest, CDialog)
END_MESSAGE_MAP()


// CDlgAddQuest message handlers


BOOL CDlgAddQuest::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Text.Create(GetDlgItem(IDC_STATIC_TEXT));
	m_Hint.Create(GetDlgItem(IDC_STATIC_HINT));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
