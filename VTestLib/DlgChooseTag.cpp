// DlgChooseTag.cpp : implementation file
//

#include "stdafx.h"
#include "VTestLib.h"
#include "DlgChooseTag.h"
#include "afxdialogex.h"
#include "../lib/appfunc.h"


// CDlgChooseTag dialog

IMPLEMENT_DYNAMIC(CDlgChooseTag, CDialog)

CDlgChooseTag::CDlgChooseTag(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChooseTag::IDD, pParent)
	, m_strTag(_T(""))
	, m_strTagName(_T(""))
	, m_strList(_T(""))
{

}

CDlgChooseTag::~CDlgChooseTag()
{
}

void CDlgChooseTag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strTag);
	DDX_Text(pDX, IDC_STATIC0, m_strTagName);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_LBString(pDX, IDC_LIST1, m_strList);
}


BEGIN_MESSAGE_MAP(CDlgChooseTag, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgChooseTag::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDlgChooseTag::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgChooseTag::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDlgChooseTag message handlers


void CDlgChooseTag::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


BOOL CDlgChooseTag::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i=0;i<m_arr.GetSize();i++) 
	{
		if (m_arr[i]=="") m_arr[i]=L"<null>";
		m_List.AddString(m_arr[i]);
	}

	OnEnChangeEdit1();

	//for (int i=0;i<((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCount();i++)
	//m_List->SelectString(-1,m_strTag);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgChooseTag::OnLbnSelchangeList1()
{
	UpdateData(TRUE);
	m_strTag=m_strList;
	UpdateData(FALSE);
}


void CDlgChooseTag::OnEnChangeEdit1()
{
	UpdateData(TRUE);
	CString strFind=m_strTag; strFind=MakeKhongDau(strFind); strFind.MakeLower();
	m_List.ResetContent();
	for (int i=0;i<m_arr.GetSize();i++)
	{
		CString str=m_arr[i]; str=MakeKhongDau(str); str.MakeLower();
		if (str.Find(strFind)!=-1) { m_List.AddString(m_arr[i]); }
	}
}
