// DlgFind.cpp : implementation file
//

#include "stdafx.h"
#include "VTestLib.h"
#include "DlgFind.h"
#include "afxdialogex.h"


// CDlgFind dialog

IMPLEMENT_DYNAMIC(CDlgFind, CDialog)

CDlgFind::CDlgFind(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFind::IDD, pParent)
	, m_bQues(TRUE)
	, m_bAns(TRUE)
	, m_bTag(TRUE)
	, m_strFind(_T(""))
{

}

CDlgFind::~CDlgFind()
{
}

void CDlgFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bQues);
	DDX_Check(pDX, IDC_CHECK2, m_bAns);
	DDX_Check(pDX, IDC_CHECK3, m_bTag);
	DDX_Text(pDX, IDC_EDIT1, m_strFind);
}


BEGIN_MESSAGE_MAP(CDlgFind, CDialog)
	ON_BN_CLICKED(ID_FIND, &CDlgFind::OnBnClickedFind)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CDlgFind message handlers


void CDlgFind::OnBnClickedFind()
{
	UpdateData();
	int iStart=m_pDoc->GetCurrentQuestIndex();
	if (iStart==-1) return;
	int i;
	if (iStart>=m_pDoc->m_cQuestArr.GetSize()-1) iStart=-1;
	for (i=iStart+1;1;i++)
	{
		CItemBase* item=m_pDoc->m_cQuestArr[i];
		if (item->m_Type==ItemQuestABCD)
		{
			CQuestItemABCD* it=(CQuestItemABCD*)item;
			if (m_bQues)
			{
				if (FindText(it->m_strQuest,m_strFind)) { m_pDoc->SetCurrentQuest(i); break; }
			}
			if (m_bAns)
			{

			}
		}
		if (i==m_pDoc->m_cQuestArr.GetSize()-1) i=0;
		if (i==iStart) break;
	}
	if (i==iStart) AfxMessageBox(L"Không tìm thấy",MB_OK | MB_ICONINFORMATION);
}

bool CDlgFind::FindText(CString strText, CString strFind)
{
	strText=MakeKhongDau(strText); strText.MakeLower();
	strFind=MakeKhongDau(strFind); strFind.MakeLower();
	return (strText.Find(strFind)!=-1);
}

void CDlgFind::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	//CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDlgFind::OnOK()
{
	//CDialog::OnOK();
}
