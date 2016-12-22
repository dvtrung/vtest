// DlgAddCont.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAddCont.h"
#include "afxdialogex.h"
#include "../lib/appfunc.h"
#include "resource.h"

// CDlgAddCont dialog

IMPLEMENT_DYNAMIC(CDlgAddCont, CDialog)

CDlgAddCont::CDlgAddCont(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddCont::IDD, pParent)
	, m_nStdType(0)
{

}

CDlgAddCont::~CDlgAddCont()
{
}

void CDlgAddCont::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nStdType);
	DDX_Control(pDX, IDC_COMBO1, m_cbStdType);
}


BEGIN_MESSAGE_MAP(CDlgAddCont, CDialog)
END_MESSAGE_MAP()


// CDlgAddCont message handlers


BOOL CDlgAddCont::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Text.Create(GetDlgItem(IDC_STATIC_TEXT));

	m_cbStdType.AddString(L"Tất cả");
// 	for (int i=0;i<m_tInfo->m_StudentType.GetSize();i++)
// 		m_cbStdType.AddString(m_tInfo->m_StudentType[i]);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
