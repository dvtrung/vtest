// DlgProperties.cpp : implementation file
//

#include "stdafx.h"
#include "VTest.h"
#include "DlgProperties.h"
#include "../lib/appfunc.h"

// CDlgProperties dialog

IMPLEMENT_DYNAMIC(CDlgProperties, CDialog)

CDlgProperties::CDlgProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProperties::IDD, pParent)
{

}

CDlgProperties::~CDlgProperties()
{
}

void CDlgProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_tInfo.m_strTitle);
	DDX_CBString(pDX, IDC_COMBO_SUBJECT, m_tInfo.m_strSubject);
	DDX_Text(pDX, IDC_EDIT_TIME, m_tInfo.m_nTime);
	DDX_Text(pDX, IDC_EDIT2, m_tInfo.m_strAuthor);
	DDX_Text(pDX, IDC_EDIT4, m_tInfo.m_strOtherInfo);
	DDX_Control(pDX, IDC_COMBO_SUBJECT, m_cbSubject);
	DDX_Control(pDX, IDC_COMBO_STDTYPE, m_cbStdType);
}


BEGIN_MESSAGE_MAP(CDlgProperties, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CDlgProperties::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgProperties message handlers

int CDlgProperties::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

 	return 0;
}

void CDlgProperties::OnBnClickedOk()
{
	CString str;
	(GetDlgItem(IDC_COMBO_STDTYPE))->GetWindowTextW(str);
	m_tInfo.m_StudentType.RemoveAll();
	SplitString(str,';',m_tInfo.m_StudentType);
	OnOK();
}

BOOL CDlgProperties::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cbSubject.AddString(L"Toán");
	m_cbSubject.AddString(L"Vật lý");
	m_cbSubject.AddString(L"Hóa học");
	m_cbSubject.AddString(L"Sinh học");
	m_cbSubject.AddString(L"Tiếng Anh");

	m_cbStdType.AddString(L"<None>");
	m_cbStdType.AddString(L"Ban cơ bản;Ban nâng cao");
	m_cbStdType.AddString(L"Dễ;Trung bình;Khó");

	CString str; if (m_tInfo.m_StudentType.GetSize()==0) str=L"<None>";
	else
	{
		for (int i=0;i<m_tInfo.m_StudentType.GetSize();i++)
		{
			str+=m_tInfo.m_StudentType[i]+L";";
		}
		str.Delete(str.GetLength()-1,1);
	}
	m_cbStdType.SetWindowTextW(str);

	((CEdit*)GetDlgItem(IDC_EDIT_TIME))->SetLimitText(3);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
