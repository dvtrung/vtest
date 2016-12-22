// DlgTestHistory.cpp : implementation file
//

#include "stdafx.h"
#include "VTestViewer.h"
#include "DlgTestHistory.h"
#include "afxdialogex.h"
#include "DlgTestResult.h"


// CDlgTestHistory dialog

IMPLEMENT_DYNAMIC(CDlgTestHistory, CDialog)

CDlgTestHistory::CDlgTestHistory(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTestHistory::IDD, pParent)
	, m_nHistoryIndex(0)
{

}

CDlgTestHistory::~CDlgTestHistory()
{
}

void CDlgTestHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_LBIndex(pDX, IDC_LIST1, m_nHistoryIndex);
}


BEGIN_MESSAGE_MAP(CDlgTestHistory, CDialog)
	ON_BN_CLICKED(IDC_VIEW_RESULT, &CDlgTestHistory::OnBnClickedViewResult)
	ON_BN_CLICKED(IDC_CLEAR_HISTORY, &CDlgTestHistory::OnBnClickedClearHistory)
	ON_BN_CLICKED(IDC_VIEW_DETAIL, &CDlgTestHistory::OnBnClickedViewDetail)
END_MESSAGE_MAP()


// CDlgTestHistory message handlers


void CDlgTestHistory::OnBnClickedViewResult()
{
	int i=m_List.GetCurSel();
	if (i==-1) return;
	CDlgTestResult dlg;
	dlg.m_SoCau=m_hisArr->m_Array.GetAt(i)->m_SoCau;
	dlg.m_SoCauDung=m_hisArr->m_Array.GetAt(i)->m_SoCauDung;
	dlg.m_SoCauLam=m_hisArr->m_Array.GetAt(i)->m_SoCauLam;
	dlg.m_ThoiGian=m_hisArr->m_Array.GetAt(i)->m_ThoiGian;
	dlg.m_ThoiGianLam=m_hisArr->m_Array.GetAt(i)->m_ThoiGianLam;
	dlg.DoModal();
}


BOOL CDlgTestHistory::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i=0;i<m_hisArr->m_Array.GetSize();i++)
	{
		m_List.AddString(L"Lần "+IntToString(i+1)+L" ("+m_hisArr->m_Array[i]->m_TakenTime+")");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTestHistory::OnBnClickedClearHistory()
{
	for (int i=0;i<m_hisArr->m_Array.GetSize();i++) m_hisArr->m_Array.RemoveAt(i);
	m_hisArr->m_Array.RemoveAll();
	m_List.ResetContent();
}


void CDlgTestHistory::OnBnClickedViewDetail()
{
	UpdateData(TRUE);
	if (m_nHistoryIndex==-1) return;
	else EndDialog(IDC_VIEW_DETAIL);
}
