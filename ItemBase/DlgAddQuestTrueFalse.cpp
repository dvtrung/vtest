// DlgAddQuestTrueFalse.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAddQuestTrueFalse.h"
#include "afxdialogex.h"


// CDlgAddQuestTrueFalse dialog

IMPLEMENT_DYNAMIC(CDlgAddQuestTrueFalse, CDialog)

CDlgAddQuestTrueFalse::CDlgAddQuestTrueFalse(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddQuestTrueFalse::IDD, pParent)
{

}

CDlgAddQuestTrueFalse::~CDlgAddQuestTrueFalse()
{
}

void CDlgAddQuestTrueFalse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_QUESTION, m_Quest);
	DDX_Control(pDX, IDC_EDIT_HINT, m_Hint);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_COMBO_ANS2, m_cbAns);
	DDX_Control(pDX, IDC_COMBO_ANS, m_cbAnsSet);
}


BEGIN_MESSAGE_MAP(CDlgAddQuestTrueFalse, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgAddQuestTrueFalse::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_ADD, &CDlgAddQuestTrueFalse::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CDlgAddQuestTrueFalse::OnBnClickedBtnDel)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgAddQuestTrueFalse::OnLbnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO_ANS, &CDlgAddQuestTrueFalse::OnCbnSelchangeComboAns)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgAddQuestTrueFalse::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgAddQuestTrueFalse message handlers


void CDlgAddQuestTrueFalse::OnBnClickedOk()
{
	OnLbnSelchangeList1();
	CDialog::OnOK();
}


BOOL CDlgAddQuestTrueFalse::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_List.AddString(L"Câu hỏi chính");
	m_List.SetItemHeight(-1,20);
	m_nSelectedItem=-1;
	m_List.SetCurSel(0);

	for (int i=1;i<m_arrQuest.GetSize();i++) m_List.AddString(L"Câu "+IntToString(i));

	if (m_arrQuest.GetSize()==0)
	{
		m_arrQuest.Add(L"");
		m_arrHint.Add(L"");
		m_arrAns.Add(0);
	}

	OnLbnSelchangeList1();
	m_cbAns.ResetContent();

	if (m_arrAnsSet.GetSize()==0) 
	{
		m_cbAnsSet.SetCurSel(0);
		OnBnClickedButton2();
	}
	else
	{
		CString str;
		m_cbAns.AddString(L"[None]");
		for (int i=0;i<m_arrAnsSet.GetSize();i++) {
			str+=m_arrAnsSet[i]+L"-";
			m_cbAns.AddString(m_arrAnsSet[i]);
		}
		str.Delete(str.GetLength()-1,1);
		m_cbAnsSet.SetWindowTextW(str);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAddQuestTrueFalse::OnBnClickedBtnAdd()
{
	m_List.AddString(L"Câu "+IntToString(m_List.GetCount()));
	m_arrAns.Add(0);
	m_arrQuest.Add(L"");
	m_arrHint.Add(L"");
}


void CDlgAddQuestTrueFalse::OnBnClickedBtnDel()
{
	if (m_List.GetCurSel()>0)
	{
		m_arrAns.RemoveAt(m_List.GetCurSel());
		m_arrHint.RemoveAt(m_List.GetCurSel());
		m_arrQuest.RemoveAt(m_List.GetCurSel());
		m_nSelectedItem=-1;
		m_List.DeleteString(m_List.GetCount()-1);
		OnLbnSelchangeList1();
	}
}

void CDlgAddQuestTrueFalse::SaveData()
{
	m_arrQuest[m_nSelectedItem]=m_Quest.GetText();
	m_arrHint[m_nSelectedItem]=m_Hint.GetText();
	m_arrAns[m_nSelectedItem]=m_cbAns.GetCurSel()==-1 ? 0 : m_cbAns.GetCurSel();
}


void CDlgAddQuestTrueFalse::OnLbnSelchangeList1()
{
	if (m_List.GetCurSel()==-1) m_List.SetCurSel(0);
	if (m_nSelectedItem==-1) m_nSelectedItem=m_List.GetCurSel();
	else
	{
		SaveData();
	}
	
	if (m_List.GetCurSel()==0)
	{
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(0);
		GetDlgItem(IDC_COMBO_ANS2)->EnableWindow(0);
	}
	else
	{
		GetDlgItem(IDC_BTN_DEL)->EnableWindow(1);
		GetDlgItem(IDC_COMBO_ANS2)->EnableWindow(1);
	}

	m_nSelectedItem=m_List.GetCurSel();

	m_Quest.SetText(m_arrQuest[m_nSelectedItem]);
	m_Hint.SetText(m_arrHint[m_nSelectedItem]);
	m_cbAns.SetCurSel(m_arrAns[m_nSelectedItem]);
}


void CDlgAddQuestTrueFalse::OnCbnSelchangeComboAns()
{

}


void CDlgAddQuestTrueFalse::OnBnClickedButton2()
{
	SaveData();
	CString str; m_cbAnsSet.GetWindowTextW(str);
	m_arrAnsSet.RemoveAll();
	SplitString(str,'-',m_arrAnsSet);
	bool b=false;
	for (int i=0;i<m_arrAns.GetSize();i++) if (m_arrAns[i]>m_arrAnsSet.GetSize()) { b=true; break; }
	if (b) 
	{
		if (AfxMessageBox(L"Thay đổi này sẽ làm một số câu trả lời không hợp lệ. Bạn muốn tiếp tục ?",MB_YESNO)==IDYES)
		{
			for (int i=0;i<m_arrAns.GetSize();i++) 
				if (m_arrAns[i]>m_arrAnsSet.GetSize()) { 
					m_arrAns[i]=0; 
				}
			m_cbAns.ResetContent();
			m_cbAns.AddString(L"[None]");
			for (int i=0;i<m_arrAnsSet.GetSize();i++) m_cbAns.AddString(m_arrAnsSet[i]);
		}
	}
	else
	{
		m_cbAns.ResetContent();
		m_cbAns.AddString(L"[None]");
		for (int i=0;i<m_arrAnsSet.GetSize();i++) m_cbAns.AddString(m_arrAnsSet[i]);
	}
	m_nSelectedItem=-1;
	OnLbnSelchangeList1();
}
