// DlgSelectTest.cpp : implementation file
//

#include "stdafx.h"
#include "VTestStd.h"
#include "DlgSelectTest.h"
#include "afxdialogex.h"
#include "../lib/appfunc.h"
#include "DlgConfirmTest.h"
#include "DlgTest.h"


// CDlgSelectTest dialog

IMPLEMENT_DYNAMIC(CDlgSelectTest, CDialog)

CDlgSelectTest::CDlgSelectTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectTest::IDD, pParent)
{

}

CDlgSelectTest::~CDlgSelectTest()
{
}

void CDlgSelectTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Title);
	DDX_Text(pDX, IDC_EDIT2, m_Subject);
	DDX_Text(pDX, IDC_EDIT6, m_Time);
	DDX_Text(pDX, IDC_EDIT7, m_Author);
	DDX_Text(pDX, IDC_EDIT8, m_OtherInfo);
	DDX_Control(pDX, IDC_TREE, m_Tree);
	DDX_Control(pDX, IDC_COMBO2, m_cbGroupBy);
}


BEGIN_MESSAGE_MAP(CDlgSelectTest, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgSelectTest::OnBnClickedButtonAdd)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CDlgSelectTest::OnTvnSelchangedTree)
	ON_BN_CLICKED(IDOK, &CDlgSelectTest::OnBnClickedOk)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_ADDCATEGORY, &CDlgSelectTest::OnBnClickedButtonAddcategory)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE, &CDlgSelectTest::OnTvnEndlabeleditTree)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE, &CDlgSelectTest::OnTvnBeginlabeleditTree)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDlgSelectTest::OnCbnSelchangeGroupBy)
END_MESSAGE_MAP()


// CDlgSelectTest message handlers


void CDlgSelectTest::OnBnClickedButtonAdd()
{
	CFileDialog dlgFile(TRUE, NULL , NULL, 
		OFN_PATHMUSTEXIST,
		L"VTest files (*.vtest)|*.vtest||", this, 0);

	if (dlgFile.DoModal()==IDOK)
	{
		CString path=dlgFile.GetOFN().lpstrFile;
		m_TestArr.AddFromFile(path);
		CTestArray::CTestItem* t=m_TestArr.m_Array.GetAt(m_TestArr.m_Array.GetSize()-1);
		HTREEITEM hP=m_Tree.GetSelectedItem();
		int i;
		m_Tree.GetItemImage(hP,i,i);
		if (i==1) hP=m_Tree.GetNextItem(hP,TVGN_PARENT);
		HTREEITEM tItem=m_Tree.InsertItem(t->m_tInfo.m_strTitle,1,1,hP);
		m_Tree.SetItemData(tItem,(DWORD_PTR)t->m_nID);
		m_Tree.SelectItem(tItem);
	}
}


void CDlgSelectTest::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	int i;
	m_Tree.GetItemImage(pNMTreeView->itemNew.hItem,i,i);
	if (i==1)
	{
		int id=m_Tree.GetItemData(pNMTreeView->itemNew.hItem);
		CTestArray::CTestItem* t=m_TestArr.GetByID(id);
		m_Title=t->m_tInfo.m_strTitle;
		m_Subject=t->m_tInfo.m_strSubject;
		m_Time=IntToString(t->m_tInfo.m_nTime)+L" phút";
		m_nTime=t->m_tInfo.m_nTime;
		m_Author=t->m_tInfo.m_strAuthor;
		m_OtherInfo=t->m_tInfo.m_strOtherInfo;
		m_strPath=t->path;

		GetDlgItem(IDOK)->EnableWindow(1);

		UpdateData(FALSE);
	}
	else
	{
		m_Title=m_Subject=m_Time=m_Author=m_OtherInfo=L"";
		m_nTime=0;
		m_strPath=L"";
		GetDlgItem(IDOK)->EnableWindow(0);

		UpdateData(FALSE);
	}
	*pResult = 0;
}


void CDlgSelectTest::OnBnClickedOk()
{
	CDlgConfirmTest dlg;
	dlg.m_strTitle=m_Title;
	dlg.m_strTime=m_Time;
	dlg.m_strQNum=L"50";
	if (dlg.DoModal()==IDOK)
	{
		m_bShowAnsIm=dlg.m_bShowAnswerIm;
		OnOK();
	}
}


int CDlgSelectTest::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


BOOL CDlgSelectTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	((CButton*)GetDlgItem(IDC_BUTTON_ADD))->SetIcon(AfxGetApp()->LoadIconW(IDI_ADDFILE));
	((CButton*)GetDlgItem(IDC_BUTTON_REMOVE))->SetIcon(AfxGetApp()->LoadIconW(IDI_CROSS));
	((CButton*)GetDlgItem(IDC_BUTTON_ADDCATEGORY))->SetIcon(AfxGetApp()->LoadIconW(IDI_ADDCATEGORY));
	((CButton*)GetDlgItem(IDC_BUTTON_FROM_INTERNET))->SetIcon(AfxGetApp()->LoadIconW(IDI_GLOBE));

	m_Tree.ModifyStyle(0,TVS_HASBUTTONS | TVS_HASLINES | TVS_EDITLABELS | TVS_SHOWSELALWAYS);
	m_TreeImgLst.Create(16,16,ILC_COLOR32,0,2);
	m_TreeImgLst.Add(AfxGetApp()->LoadIconW(IDI_FOLDER));
	m_TreeImgLst.Add(AfxGetApp()->LoadIconW(IDI_FILE));
	m_Tree.SetImageList(&m_TreeImgLst,0);

	m_cbGroupBy.AddString(L"Theo người dùng");
	m_cbGroupBy.AddString(L"Môn học");
	m_cbGroupBy.AddString(L"Người ra đề");
	m_cbGroupBy.AddString(L"Thời gian");

	m_cbGroupBy.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSelectTest::OnBnClickedButtonAddcategory()
{
	HTREEITEM hi=m_Tree.InsertItem(L"Mục mới");
	m_Tree.SetItemImage(hi,0,0);
	m_Tree.SelectItem(hi);
	m_Tree.EditLabel(hi);
}


void CDlgSelectTest::OnTvnEndlabeleditTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	*pResult = 1;
}


void CDlgSelectTest::OnTvnBeginlabeleditTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	if (m_cbGroupBy.GetCurSel()!=0) { *pResult=1; return; }
	int i; m_Tree.GetItemImage(pTVDispInfo->item.hItem,i,i);
	if (i==1) *pResult = 1;
	else *pResult = 0;
}


void CDlgSelectTest::OnCbnSelchangeGroupBy()
{
	if (m_cbGroupBy.GetCurSel()==1)
	{
		m_Tree.DeleteAllItems();
		CArray<HTREEITEM> rootArr;
		CStringArray nameArr;
		for (int i=0;i<m_TestArr.m_Array.GetSize();i++)
		{
			int j;
			for (j=0;j<nameArr.GetSize();j++) if (nameArr[j]==m_TestArr.m_Array[i]->m_tInfo.m_strSubject) break;
			
			HTREEITEM hRoot;
			if (j==nameArr.GetSize())
			{
				hRoot=m_Tree.InsertItem(m_TestArr.m_Array[i]->m_tInfo.m_strSubject,0,0);
				rootArr.Add(hRoot);
				nameArr.Add(m_TestArr.m_Array[i]->m_tInfo.m_strSubject);
			}
			else
				hRoot=rootArr[j];

			HTREEITEM hi=m_Tree.InsertItem(m_TestArr.m_Array[i]->m_tInfo.m_strTitle,1,1,hRoot);
			m_Tree.SetItemData(hi,(LPARAM)m_TestArr.m_Array[i]->m_nID);
		}
	}
}
