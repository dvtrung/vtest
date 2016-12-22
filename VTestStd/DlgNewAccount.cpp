// DlgNewAccount.cpp : implementation file
//

#include "stdafx.h"
#include "VTestStd.h"
#include "DlgNewAccount.h"
#include "afxdialogex.h"


// CDlgNewAccount dialog

IMPLEMENT_DYNAMIC(CDlgNewAccount, CDialog)

CDlgNewAccount::CDlgNewAccount(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewAccount::IDD, pParent)
{

}

CDlgNewAccount::~CDlgNewAccount()
{
}

void CDlgNewAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, userName);
	DDX_Text(pDX, IDC_EDIT2, passWord);
	DDX_Text(pDX, IDC_EDIT3, retypePass);
	DDX_Text(pDX, IDC_EDIT4, place);
	DDX_Text(pDX, IDC_EDIT5, note);
}


BEGIN_MESSAGE_MAP(CDlgNewAccount, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgNewAccount::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgNewAccount message handlers


void CDlgNewAccount::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (passWord==retypePass)
		OnOK();
	else AfxGetApp()->DoMessageBox(L"Mật khẩu không khớp",MB_OK | MB_ICONWARNING,0);
	CDialog::OnOK();
}
