// DlgTestResult.cpp : implementation file
//

#include "stdafx.h"
#include "VTestViewer.h"
#include "DlgTestResult.h"
#include "afxdialogex.h"
#include "../lib/appfunc.h"


// CDlgTestResult dialog

IMPLEMENT_DYNAMIC(CDlgTestResult, CDialog)

CDlgTestResult::CDlgTestResult(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTestResult::IDD, pParent)
{

}

CDlgTestResult::~CDlgTestResult()
{
}

void CDlgTestResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTestResult, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgTestResult::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTestResult message handlers


BOOL CDlgTestResult::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Font.CreatePointFont(180,L"Times New Roman");
	GetDlgItem(IDC_STATIC_MARK)->SetFont(&m_Font);

	CString d=IntToString(m_SoCauDung*100/m_SoCau);
	GetDlgItem(IDC_STATIC_MARK)->SetWindowText(d.Left(1)+L","+d.Right(1));
	GetDlgItem(IDC_STATIC_RIGHT)->SetWindowText(IntToString(m_SoCauDung)+L"/"+IntToString(m_SoCau));
	GetDlgItem(IDC_STATIC_DONED)->SetWindowText(IntToString(m_SoCauLam));
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS_DONED))->SetRange(0,100);
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS_DONED))->SetPos(m_SoCauLam*100/m_SoCau);
	GetDlgItem(IDC_STATIC_RIGHT_PER)->SetWindowText(m_SoCauLam==0 ? 0 : IntToString(m_SoCauDung*100/m_SoCauLam)+L"%");
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS_CORRECT_PER))->SetRange(0,100);
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS_CORRECT_PER))->SetPos(m_SoCauLam==0 ? 0 : (m_SoCauDung*100/m_SoCauLam));
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(SecondToMinuteAndSecond(m_ThoiGianLam));
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS_TIME))->SetRange(0,100);
	if (m_ThoiGian!=0) ((CProgressCtrl*)GetDlgItem(IDC_PROGRESS_TIME))->SetPos(m_ThoiGianLam*100/m_ThoiGian);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTestResult::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
