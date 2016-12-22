// DlgStructSpecifyItemTag.cpp : implementation file
//

#include "stdafx.h"
#include "VTestLib.h"
#include "DlgStructSpecifyItemTag.h"
#include "afxdialogex.h"
#include "../lib/appfunc.h"


// CDlgStructSpecifyItemTag dialog

IMPLEMENT_DYNAMIC(CDlgStructSpecifyItemTag, CDialog)

CDlgStructSpecifyItemTag::CDlgStructSpecifyItemTag(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStructSpecifyItemTag::IDD, pParent)
{

}

CDlgStructSpecifyItemTag::~CDlgStructSpecifyItemTag()
{
}

void CDlgStructSpecifyItemTag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
}


BEGIN_MESSAGE_MAP(CDlgStructSpecifyItemTag, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgStructSpecifyItemTag::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgStructSpecifyItemTag message handlers

void CDlgStructSpecifyItemTag::RefreshItem()
{
	m_Tree.DeleteAllItems();
	
	//HTREEITEM hIt=m_Tree.InsertItem(m_tagArray->m_TagName[i]);
	CStringArray arr;
	m_tagArray->GetItemsInTag(arr,m_nTagItem);
	for (int j=0;j<arr.GetSize();j++) { AddTreeItem(TVI_ROOT,arr[j]!="" ? arr[j] : L"<null>"); }

	RemoveNullNode(TVI_ROOT);
	Sort(TVI_ROOT);
}

void CDlgStructSpecifyItemTag::AddTreeItem(HTREEITEM hItem, CString strText)
{
	CStringArray arr;
	SplitString(strText,':',arr);
	for (int i=0;i<arr.GetSize();i++) arr[i]=arr[i].Trim();
	HTREEITEM hParent=hItem;
	for (int i=0;i<arr.GetSize();i++)
	{
		if (arr[i]=="") arr[i]=L"<null>";
		HTREEITEM hIt=m_Tree.FindChildItem(hParent,arr[i]);
		if (hIt==NULL) hIt=m_Tree.InsertItem(arr[i],hParent,TVI_LAST);
		hParent=hIt;
	}
	if (m_Tree.FindChildItem(hParent,L"<null>")==NULL) m_Tree.InsertItem(L"<null>",hParent);
}

CString CDlgStructSpecifyItemTag::GetTreeItemFullText(HTREEITEM hTreeItem)
{
	HTREEITEM hParent=hTreeItem;
	CString str;
	while (hParent!=NULL)
	{
		//if (m_Tree.GetItemText(hParent)!=L"<null>")
		str=L" : " + m_Tree.GetItemText(hParent) + str;
		hParent=m_Tree.GetParentItem(hParent);
	}
	str.Delete(0,3);
	if (str.Right(3)==L" : ") str.Delete(str.GetLength()-4,3);
	return str;
}


void CDlgStructSpecifyItemTag::RemoveNullNode(HTREEITEM hParent)
{
	HTREEITEM hItem=m_Tree.GetChildItem(hParent);
	if (hItem==NULL) return;
	if (m_Tree.GetNextSiblingItem(hItem)==NULL && m_Tree.GetItemText(hItem)==L"<null>") m_Tree.DeleteItem(hItem);
	else
	{
		while (hItem!=NULL)
		{
			RemoveNullNode(hItem);
			hItem=m_Tree.GetNextSiblingItem(hItem);
		}
	}
}

void CDlgStructSpecifyItemTag::Sort(HTREEITEM hItem)
{
	HTREEITEM hChild=m_Tree.GetChildItem(hItem);
	while (hChild!=NULL)
	{
		Sort(hChild);
		m_Tree.SortChildren(hItem);
		hChild=m_Tree.GetNextSiblingItem(hChild);
	}
}

BOOL CDlgStructSpecifyItemTag::OnInitDialog()
{
	CDialog::OnInitDialog();

	RefreshItem();
	m_Tree.InitStateImageList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgStructSpecifyItemTag::OnBnClickedOk()
{
	m_strReturn=L"";
	AddItemText(TVI_ROOT,m_strReturn);
	m_strReturn.Delete(0,2);

	CDialog::OnOK();
}

void CDlgStructSpecifyItemTag::AddItemText(HTREEITEM hItem, CString& str)
{
	HTREEITEM hChild=m_Tree.GetChildItem(hItem);
	while (hChild!=NULL)
	{
		if (m_Tree.GetCheck(hChild)==1) str+=L"; "+GetTreeItemFullText(hChild);
		else if (m_Tree.GetChildItem(hChild)!=NULL)	AddItemText(hChild,str);

		hChild=m_Tree.GetNextSiblingItem(hChild);
	}
}