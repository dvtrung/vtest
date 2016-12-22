// DlgUser.cpp : implementation file
//

#include "stdafx.h"
#include "VTestStd.h"
#include "DlgUser.h"
#include "afxdialogex.h"
#include "DlgNewAccount.h"
#include "DlgTest.h"
#include "DlgSelectTest.h"
#include "../lib/appfunc.h"


// CDlgUser dialog

IMPLEMENT_DYNAMIC(CDlgUser, CDialog)

CDlgUser::CDlgUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUser::IDD, pParent)
{

}

CDlgUser::~CDlgUser()
{
}

void CDlgUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgUser, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_INFO, &CDlgUser::OnBnClickedButtonEditInfo)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_TEST, &CDlgUser::OnBnClickedButtonSelectTest)
END_MESSAGE_MAP()


// CDlgUser message handlers


void CDlgUser::OnBnClickedButtonEditInfo()
{
	CDlgNewAccount dlg;
	dlg.userName=acc->userName;
	dlg.passWord=acc->passWord;
	dlg.retypePass=acc->passWord;
	dlg.place=acc->place;
	dlg.note=acc->note;
	if (dlg.DoModal()==IDOK)
	{
		acc->userName=dlg.userName;
		acc->passWord=dlg.passWord;
		acc->place=dlg.place;
		acc->note=dlg.note;
	}
}


void CDlgUser::OnBnClickedButtonSelectTest()
{
	this->ShowWindow(SW_HIDE);
	CDlgSelectTest dlg;
	if (dlg.DoModal()==IDOK)
	{
		CDlgTest dlgTest;
		dlgTest.m_nRemainingTime=dlg.m_nTime*60;
		dlgTest.m_bShowAnswerIm=dlg.m_bShowAnsIm;
		dlgTest.m_filePath=L".\\data\\T\\"+dlg.m_strPath;
		dlgTest.DoModal();
	}
	this->ShowWindow(SW_SHOW);
}


BOOL CDlgUser::OnInitDialog()
{
	CDialog::OnInitDialog();

	//((CButton*)GetDlgItem(IDC_BUTTON_EDIT_INFO))->SetIcon(AfxGetApp()->LoadIconW(IDI_ICON_CLOCK));
	//((CButton*)GetDlgItem(IDC_BUTTON_EDIT_INFO))->SetNote(L"Sửa các thông tin người dùng (mật khẩu, thông tin cá nhân, ...)");
	//((CButton*)GetDlgItem(IDC_BUTTON_SELECT_TEST))->SetNote(L"Làm các đề thi trong thư viện có sẵn hoặc tải đề từ Internet");
	//((CButton*)GetDlgItem(IDC_BUTTON_STATISTIC))->SetNote(L"Thống kê quá trình học, các bài thi đã làm, tỉ lệ làm đúng, ...");
	//((CButton*)GetDlgItem(IDC_BUTTON_TEST_FROM_LIB))->SetNote(L"Tạo một đề thi với các câu hỏi nằm trong đề thi bạn đã làm");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
