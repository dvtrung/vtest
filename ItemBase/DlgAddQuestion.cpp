// DlgAddQuestion.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAddQuestion.h"
#include "../lib/appfunc.h"
#include "resource.h"


// CDlgAddQuestion dialog

IMPLEMENT_DYNAMIC(CDlgAddQuestion, CDialog)

CDlgAddQuestion::CDlgAddQuestion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddQuestion::IDD, pParent)
	, m_nMark(0)
{

}

CDlgAddQuestion::~CDlgAddQuestion()
{
}

void CDlgAddQuestion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CDlgAddQuestion, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgAddQuestion::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_FROM_CLIPBOARD, &CDlgAddQuestion::OnBnClickedButtonFromClipboard)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDlgAddQuestion::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgAddQuestion::OnCbnSelchangeCombo1)
	ON_LBN_SELCHANGE(IDC_LIST, &CDlgAddQuestion::OnLbnSelchangeList)
END_MESSAGE_MAP()


// CDlgAddQuestion message handlers

void CDlgAddQuestion::OnBnClickedOk()
{
	OnOK();
}

void CDlgAddQuestion::OnBnClickedButtonFromClipboard()
{
// 	if (IsClipboardFormatAvailable(CF_UNICODETEXT))
// 	{
// 		CString s; 
// 
// 		OpenClipboard();
// 		HGLOBAL   hglb; 
// 		LPCTSTR lptstr;
// 		hglb = GetClipboardData(CF_UNICODETEXT); 
// 		if (hglb != NULL) 
// 		{ 
// 			lptstr = (LPCTSTR)GlobalLock(hglb); 
// 			if (lptstr != NULL) 
// 			{ 
// 				// Call the application-defined ReplaceSelection 
// 				// function to insert the text and repaint the 
// 				// window. 
// 
// 				s=CString(lptstr);
// 			} 
// 		} 
// 		CloseClipboard(); 
// 
// 		
// 			int p1=s.Find(L"\r\nA."); if (p1!=-1) { p1+=2; goto B; }
// 			if (p1==-1) p1=s.Find(L"\tA."); if (p1!=-1) { p1+=1; goto B; }
// 			if (p1==-1) p1=s.Find(L" A."); if (p1!=-1) { p1+=1; goto B; }
// 			if (p1==-1) goto error;
// 		
// 
// 		B:
// 		
// 		
// 			int p2=s.Find(L"\r\nB."); if (p2!=-1) { p2+=2; goto C; }
// 			if (p2==-1) p2=s.Find(L"\tB."); if (p2!=-1) { p2+=1; goto C; }
// 			if (p2==-1) p2=s.Find(L" B."); if (p2!=-1) { p2+=1; goto C; }
// 			if (p2==-1) goto error;
// 		
// 
// 		C:
// 
// 		
// 			int p3=s.Find(L"\r\nC."); if (p3!=-1) { p3+=2; goto D; }
// 			if (p3==-1) p3=s.Find(L"\tC."); if (p3!=-1) { p3+=1; goto D; }
// 			if (p3==-1) p3=s.Find(L" C."); if (p3!=-1) { p3+=1; goto D; }
// 			if (p3==-1) goto error;
// 		
// 
// 		D:
// 
// 		
// 			int p4=s.Find(L"\r\nD."); if (p4!=-1) { p4+=2; goto END; }
// 			if (p4==-1) p4=s.Find(L"\tD."); if (p4!=-1) { p4+=1; goto END; }
// 			if (p4==-1) p4=s.Find(L" D."); if (p4!=-1) { p4+=1; goto END; }
// 			if (p4==-1) goto error;
// 		
// 
// 		END:
// 
// 		CString strQuestion=s.Left(p1); strQuestion.Trim(); m_Question.m_Text=strQuestion;
// 		m_AnsA.m_Text=s.Mid(p1+2,p2-p1-2); m_AnsA.m_Text.Trim();
// 		m_AnsB.m_Text=s.Mid(p2+2,p3-p2-2); m_AnsB.m_Text.Trim();
// 		m_AnsC.m_Text=s.Mid(p3+2,p4-p3-2); m_AnsC.m_Text.Trim();
// 		m_AnsD.m_Text=s.Mid(p4+2,s.GetLength()-p4-2); m_AnsD.m_Text.Trim();
// 		m_Question.Invalidate(); if (m_Question.bEdit) m_Question.m_Edit.SetWindowText(m_Question.m_Text);
// 		m_AnsA.Invalidate(); if (m_AnsA.bEdit) m_AnsA.m_Edit.SetWindowText(m_AnsA.m_Text);
// 		m_AnsB.Invalidate(); if (m_AnsB.bEdit) m_AnsB.m_Edit.SetWindowText(m_AnsB.m_Text);
// 		m_AnsC.Invalidate(); if (m_AnsC.bEdit) m_AnsC.m_Edit.SetWindowText(m_AnsC.m_Text);
// 		m_AnsD.Invalidate(); if (m_AnsD.bEdit) m_AnsD.m_Edit.SetWindowText(m_AnsD.m_Text);
// 		UpdateData(FALSE);
// 	} 
// 	else
// 	{
// 		goto error;
// 	}
// 	return;
// error:
// 	AfxGetApp()->DoMessageBox(StringFromResource(IDS_INVALID_CLIPBOARD),MB_OK,0);
}

void CDlgAddQuestion::OnBnClickedButtonClear()
{
	m_Hint.m_Text="";		if (m_Hint.m_Edit.m_hWnd) m_Hint.m_Edit.SetWindowTextW(NULL);
	m_Question.m_Text="";	if (m_Question.m_Edit.m_hWnd) m_Question.m_Edit.SetWindowTextW(NULL);
	for (int i=0;i<m_AnsArr.GetSize();i++);
	if (m_Ans.m_Edit.m_hWnd) m_Ans.m_Edit.SetWindowTextW(NULL);
	UpdateData(FALSE);
}

BOOL CDlgAddQuestion::OnInitDialog()
{
	CDialog::OnInitDialog();
	RefreshList();
	m_List.SetItemHeight(-1,23);

// 	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
// 	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
// 	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
// 	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
// 	if (ans==1) ((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
// 	else if (ans==2) ((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
// 	else if (ans==3) ((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
// 	else if (ans==4) ((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(1);	

	m_Question.Create(GetDlgItem(IDC_STATIC_QUEST));
	m_Hint.Create(GetDlgItem(IDC_STATIC_HINT));
	m_Ans.Create(GetDlgItem(IDC_STATIC_ANS));

// 	GetDlgItem(IDC_EDIT_QUESTION)->SetFont(&m_Font);
// 	GetDlgItem(IDC_EDIT_A)->SetFont(&m_Font);
// 	GetDlgItem(IDC_EDIT_B)->SetFont(&m_Font);
// 	GetDlgItem(IDC_EDIT_C)->SetFont(&m_Font);
// 	GetDlgItem(IDC_EDIT_D)->SetFont(&m_Font);
// 	GetDlgItem(IDC_EDIT_HINT)->SetFont(&m_Font);

	m_nCurrentAns=0;
	m_Ans.m_Text=m_AnsArr[m_nCurrentAns];
	m_List.SetCurSel(m_nCurrentAns);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAddQuestion::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}

void CDlgAddQuestion::OnCbnSelchangeCbSymbol()
{
	// TODO: Add your control notification handler code here
}

void CDlgAddQuestion::RefreshList()
{
	for (int i=0;i<m_AnsArr.GetSize();i++)
		m_List.AddString(CString((char)('A'+i)));
}


void CDlgAddQuestion::OnLbnSelchangeList()
{
	m_AnsArr[m_nCurrentAns]=m_Ans.m_Text;
	m_nCurrentAns=m_List.GetCurSel();
	m_Ans.m_Text=m_AnsArr[m_nCurrentAns];
	m_Ans.OnTurnToPreview(0,0);
}
