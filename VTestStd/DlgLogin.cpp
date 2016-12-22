// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "VTestStd.h"
#include "DlgLogin.h"
#include "afxdialogex.h"
#include "DlgNewAccount.h"


// CDlgLogin dialog

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbUserName);
	DDX_Text(pDX, IDC_EDIT2, m_Pass);
	DDX_CBString(pDX, IDC_COMBO1, m_UserName);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	ON_BN_CLICKED(IDC_BTN_NEW_ACCOUNT, &CDlgLogin::OnBnClickedBtnNewAccount)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLogin message handlers


void CDlgLogin::OnBnClickedBtnNewAccount()
{
	CDlgNewAccount dlg;
	if (dlg.DoModal()==IDOK)
	{
		CAccount* acc=m_AccArr->AddAccount();
		acc->userName=dlg.userName;
		acc->passWord=dlg.passWord;
		acc->place=dlg.place;
		acc->note=dlg.note;
		m_AccArr->SaveAccount();
	}
}


void CDlgLogin::OnOK()
{
	UpdateData();
	for (int i=0;i<m_AccArr->m_Array.GetSize();i++)
		if (m_AccArr->m_Array.GetAt(i)->userName==m_UserName)
		{
			if (m_AccArr->m_Array.GetAt(i)->passWord==m_Pass) CDialog::OnOK();
			else
			{
				AfxGetApp()->DoMessageBox(L"Mật khẩu không đúng",MB_OK | MB_ICONWARNING,0);
				return;
			}
		}

	CDialog::OnOK();
}


BOOL CDlgLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i=0;i<m_AccArr->m_Array.GetSize();i++)
		m_cbUserName.AddString(m_AccArr->m_Array.GetAt(i)->userName);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgLogin::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
