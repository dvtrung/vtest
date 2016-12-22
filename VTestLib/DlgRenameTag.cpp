// DlgRenameTag.cpp : implementation file
//

#include "stdafx.h"
#include "VTestLib.h"
#include "DlgRenameTag.h"
#include "afxdialogex.h"


// CDlgRenameTag dialog

IMPLEMENT_DYNAMIC(CDlgRenameTag, CDialog)

CDlgRenameTag::CDlgRenameTag(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRenameTag::IDD, pParent)
	, m_nTag(0)
	, m_strRename(_T(""))
{

}

CDlgRenameTag::~CDlgRenameTag()
{
}

void CDlgRenameTag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_cbTag);
	DDX_CBIndex(pDX, IDC_COMBO, m_nTag);
	DDX_Text(pDX, IDC_EDIT1, m_strRename);
}


BEGIN_MESSAGE_MAP(CDlgRenameTag, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgRenameTag::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRenameTag message handlers


void CDlgRenameTag::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


BOOL CDlgRenameTag::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i=0;i<m_tagName->GetSize();i++)
		m_cbTag.AddString(m_tagName->GetAt(i));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
