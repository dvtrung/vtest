// DlgMarkStruct.cpp : implementation file
//

#include "stdafx.h"
#include "VTestLib.h"
#include "DlgMarkStruct.h"
#include "afxdialogex.h"
#include "../lib/appfunc.h"
#include "../lib/InputDlg.h"
#include "DlgViewTestStruct.h"

// CDlgMarkStruct dialog

IMPLEMENT_DYNAMIC(CDlgMarkStruct, CDialog)

CDlgMarkStruct::CDlgMarkStruct(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMarkStruct::IDD, pParent)
{

}

CDlgMarkStruct::~CDlgMarkStruct()
{
	for (int i=0;i<m_ItFilterArr.GetSize();i++)
		delete m_ItFilterArr[i];
}

void CDlgMarkStruct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_COMBO1, m_cbStruct);
}


BEGIN_MESSAGE_MAP(CDlgMarkStruct, CDialog)
	ON_BN_CLICKED(IDC_STRUCT_SAVE, &CDlgMarkStruct::OnBnSaveStruct)
	ON_BN_CLICKED(IDOK, &CDlgMarkStruct::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CDlgMarkStruct::OnNMDblclkList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST, &CDlgMarkStruct::OnLvnKeydownList)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgMarkStruct::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_STRUCT_DELETE, &CDlgMarkStruct::OnBnClickedStructDelete)
END_MESSAGE_MAP()


// CDlgMarkStruct message handlers


void CDlgMarkStruct::OnBnSaveStruct()
{
	if (m_cbStruct.GetCurSel()==0)
	{
		CInputDlg dlg(L"VTestLib");
		dlg.AddStatic(L"Tên cấu trúc đề :");
		CString strName;
		dlg.AddEdit(&strName);
		if (dlg.DoModal()==IDOK)
		{
			m_testStructArr->AddFromListView(&m_List,strName);
			m_cbStruct.AddString(strName);
			m_cbStruct.SetCurSel(m_cbStruct.GetCount()-1);
		}
	}
	else
	{
		m_testStructArr->UpdateFromListView(&m_List,m_cbStruct.GetCurSel()-1);
	}
}


void CDlgMarkStruct::OnBnClickedOk()
{
	CDlgViewTestStruct dlg;
	if (m_cbStruct.GetCurSel()>0) dlg.m_struct=m_testStructArr->m_arr[m_cbStruct.GetCurSel()-1];
	else {
		dlg.m_struct=new CTestStruct();
		dlg.m_struct->FromListView(&m_List);
	}
	dlg.m_QuestArray=m_QuestArray;
	dlg.m_TagArray=m_tagArray;
	if (dlg.DoModal()==IDOK)
	{
		CDialog::OnOK();
	}
	if (m_cbStruct.GetCurSel()==0) delete dlg.m_struct;
}


BOOL CDlgMarkStruct::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0,L"Câu");
	m_List.SetColumnWidth(0,50);
	for (int i=0;i<m_tagArray->m_TagName.GetSize();i++)
	{
		m_List.InsertColumn(i+1,m_tagArray->m_TagName[i]);
		m_List.SetColumnWidth(i+1,200);
	}

	m_cbStruct.AddString(L"<Cấu trúc mới>"); m_cbStruct.SetCurSel(0); OnCbnSelchangeCombo1();
	for (int i=0;i<m_testStructArr->m_arr.GetSize();i++) 
		m_cbStruct.AddString(m_testStructArr->m_arrStructName[i]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMarkStruct::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (pNMItemActivate->iSubItem==0)
	{
		if (pNMItemActivate->iItem==m_List.GetItemCount()-1)
		{
			m_List.SetItemText(pNMItemActivate->iItem,-1,L"Câu "+IntToString(pNMItemActivate->iItem+1));
			m_List.InsertItem(m_List.GetItemCount(),L"<Add>");
		}
		return;
	}
	CDlgStructSpecifyItemTag dlg;
	dlg.m_tagArray=m_tagArray;
	dlg.m_nTagItem=pNMItemActivate->iSubItem-1;
	if (dlg.DoModal()==IDOK)
	{
		if (pNMItemActivate->iItem==m_List.GetItemCount()-1)
		{
			m_List.SetItemText(pNMItemActivate->iItem,-1,L"Câu "+IntToString(pNMItemActivate->iItem+1));
			m_List.InsertItem(m_List.GetItemCount(),L"<Add>");
		}
		
		int nRet=m_List.SetItemText(pNMItemActivate->iItem,pNMItemActivate->iSubItem,dlg.m_strReturn);
	}

	*pResult = 0;
}


void CDlgMarkStruct::OnLvnKeydownList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	
	*pResult = 0;
}


void CDlgMarkStruct::OnCbnSelchangeCombo1()
{
	if (m_cbStruct.GetCurSel()==0)
	{
		m_List.DeleteAllItems();
		m_List.InsertItem(0,L"<Add>");
		GetDlgItem(IDC_STRUCT_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STRUCT_SAVE)->SetWindowTextW(L"Lưu lại");
	}
	else
	{
		m_testStructArr->m_arr[m_cbStruct.GetCurSel()-1]->FillListView(&m_List);
		GetDlgItem(IDC_STRUCT_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STRUCT_SAVE)->SetWindowTextW(L"Cập nhật");
	}
}


void CDlgMarkStruct::OnBnClickedStructDelete()
{
	int i=m_cbStruct.GetCurSel();
	if (i!=0)
	{
		m_cbStruct.SetCurSel(0);
		m_cbStruct.DeleteString(i);
		m_testStructArr->RemoveAt(i);
	}
}
