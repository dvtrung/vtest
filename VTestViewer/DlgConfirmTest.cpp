// DlgConfirmTest.cpp : implementation file
//

#include "stdafx.h"
#include "VTestViewer.h"
#include "DlgConfirmTest.h"
#include "afxdialogex.h"
#include "DlgTestHistory.h"

// CDlgConfirmTest dialog

IMPLEMENT_DYNAMIC(CDlgConfirmTest, CDialog)

CDlgConfirmTest::CDlgConfirmTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfirmTest::IDD, pParent)
	, m_bShowAnswerIm(FALSE)
	, m_nViewStyle(0)
	, m_nStdType(0)
{

}

CDlgConfirmTest::~CDlgConfirmTest()
{
}

void CDlgConfirmTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bShowAnswerIm);
	DDX_Control(pDX, IDC_COMBO_SHOW, m_cbViewStyle);
	DDX_CBIndex(pDX, IDC_COMBO_SHOW, m_nViewStyle);
	DDX_Control(pDX, IDC_COMBO_SHOW2, m_cbStdType);
	DDX_CBIndex(pDX, IDC_COMBO_SHOW2, m_nStdType);
}


BEGIN_MESSAGE_MAP(CDlgConfirmTest, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgConfirmTest::OnBnClickedOk)
	ON_BN_CLICKED(IDC_HISTORY, &CDlgConfirmTest::OnBnClickedHistory)
END_MESSAGE_MAP()


// CDlgConfirmTest message handlers


BOOL CDlgConfirmTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	((CStatic*)GetDlgItem(IDC_STATIC_TITLE))->SetWindowText(m_tInfo->m_strTitle);
	((CStatic*)GetDlgItem(IDC_STATIC_TIME))->SetWindowText(StringFromResource(IDS_TIME)+" : "+IntToString(m_tInfo->m_nTime)+L" "+StringFromResource(IDS_MINUTE));
	//((CStatic*)GetDlgItem(IDC_STATIC_QNUM))->SetWindowText(L"(Đề thi gồm "+m_tInfo->m_+L" câu)");
	((CStatic*)GetDlgItem(IDC_STATIC_SUBJECT))->SetWindowText(StringFromResource(IDS_SUBJECT)+" : "+m_tInfo->m_strSubject);
	((CStatic*)GetDlgItem(IDC_EDIT_INFO))->SetWindowText(m_tInfo->m_strOtherInfo==L"" ? StringFromResource(IDS_NO_EXTRA_INFORMATION) : m_tInfo->m_strOtherInfo);
	((CStatic*)GetDlgItem(IDC_STATIC_HISTORY_NUM))->SetWindowText(StringFromResource(IDS_TAKEN_COUNT)+" "+IntToString(m_hisArr->m_Array.GetSize())+L" "+StringFromResource(IDS_TAKEN_COUNT_TIMES));

	m_cbViewStyle.AddString(StringFromResource(IDS_TYPE_TEST));
	m_cbViewStyle.AddString(StringFromResource(IDS_TYPE_QUEST));
	m_cbViewStyle.SetCurSel(0);

	if (m_tInfo->m_StudentType.GetSize()==0)
		m_cbStdType.EnableWindow(FALSE);
	else
	{
		for (int i=0;i<m_tInfo->m_StudentType.GetSize();i++)
			m_cbStdType.AddString(m_tInfo->m_StudentType[i]);
		m_cbStdType.SetCurSel(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgConfirmTest::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CDlgConfirmTest::OnBnClickedHistory()
{
	CDlgTestHistory dlg;
	dlg.m_hisArr=m_hisArr;
	if (dlg.DoModal()==IDC_VIEW_DETAIL)
	{
		m_nReviewTest=dlg.m_nHistoryIndex;
		EndDialog(IDC_VIEW_DETAIL);
	}
}
