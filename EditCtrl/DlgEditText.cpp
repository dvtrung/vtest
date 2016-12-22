// DlgEditText.cpp : implementation file
//

#include "stdafx.h"
#include "DlgEditText.h"


// CDlgEditText dialog

IMPLEMENT_DYNAMIC(CDlgEditText, CDialog)

CDlgEditText::CDlgEditText(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditText::IDD, pParent)
	, m_strText(_T(""))
{

}

CDlgEditText::~CDlgEditText()
{
}

void CDlgEditText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT, m_Text);
	//DDX_Text(pDX, IDC_EDIT, m_strText);
}


BEGIN_MESSAGE_MAP(CDlgEditText, CDialog)
END_MESSAGE_MAP()


// CDlgEditText message handlers

BOOL CDlgEditText::OnInitDialog()
{
	CDialog::OnInitDialog();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
