// DlgWait.cpp : implementation file
//

#include "stdafx.h"
#include "VTestViewer.h"
#include "DlgWait.h"
#include "afxdialogex.h"


// CDlgWait dialog

IMPLEMENT_DYNAMIC(CDlgWait, CDialog)

CDlgWait::CDlgWait(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWait::IDD, pParent)
{

}

CDlgWait::~CDlgWait()
{
}

void CDlgWait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
}


BEGIN_MESSAGE_MAP(CDlgWait, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS, &CDlgWait::OnNMCustomdrawProgress)
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CDlgWait message handlers


void CDlgWait::OnNMCustomdrawProgress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


BOOL CDlgWait::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgWait::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

}


void CDlgWait::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

}


void CDlgWait::OnSetFocus(CWnd* pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);
}
