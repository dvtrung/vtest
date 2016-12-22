// PageChooseFiles.cpp : implementation file
//

#include "stdafx.h"
#include "CreateCourse.h"
#include "PageChooseFiles.h"
#include "afxdialogex.h"
#include "..\lib\TestInfo.h"
#include "..\lib\appfunc.h"

extern CPageInfo* m_pgInfo;
// CPageChooseFiles dialog

IMPLEMENT_DYNAMIC(CPageChooseFiles, CPropertyPage)

CPageChooseFiles::CPageChooseFiles()
	: CPropertyPage(CPageChooseFiles::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	m_psp.pszHeaderTitle=L"VOcean";
	m_psp.pszHeaderSubTitle=L"Sắp xếp nội dung";
}

CPageChooseFiles::~CPageChooseFiles()
{
	for (int i=0;i<m_arrFilePath.GetSize();i++) delete m_arrFilePath[i];
}

void CPageChooseFiles::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE2, m_Tree);
}


BEGIN_MESSAGE_MAP(CPageChooseFiles, CDialog)
	ON_BN_CLICKED(IDC_ADD_FILES, &CPageChooseFiles::OnBnClickedAddFiles)
	ON_BN_CLICKED(IDC_ADD_CATEGORY, &CPageChooseFiles::OnBnClickedAddCategory)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE2, &CPageChooseFiles::OnTvnEndlabeleditTree2)
	ON_BN_CLICKED(IDC_REMOVE2, &CPageChooseFiles::OnBnClickedRemove2)
	//ON_BN_CLICKED(IDC_MAKE, &CPageChooseFiles::OnBnClickedMake)
	ON_BN_CLICKED(IDC_UP, &CPageChooseFiles::OnBnClickedUp)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE2, &CPageChooseFiles::OnTvnBeginlabeleditTree2)
	ON_BN_CLICKED(IDC_DOWN, &CPageChooseFiles::OnBnClickedDown)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE2, &CPageChooseFiles::OnTvnBegindragTree2)
END_MESSAGE_MAP()


// CPageChooseFiles message handlers

HTREEITEM CPageChooseFiles::AddFile(CString str, HTREEITEM hP, HTREEITEM hA)
{
	HTREEITEM hRet;
	if (hA==NULL || hP==NULL)
	{
		hP=m_Tree.GetSelectedItem();
		if (hP==NULL) hP=m_Tree.GetChildItem(TVI_ROOT);
		hA=TVI_LAST;
		if (m_Tree.GetItemData(hP)!=NULL) // Folder 
		{ 
			hA=m_Tree.GetPrevSiblingItem(hP); if (hA==NULL) hA=TVI_FIRST;
			hP=m_Tree.GetParentItem(hP); 
		}
	}
	if (str.Right(6)==L".vtest")
	{
		CFile f; 
		f.Open(str,CFile::modeRead);
		CArchive ar(&f,CArchive::load);
		CTestInfo tInfo;
		tInfo.Serialize(ar);
		ar.Close();
		f.Close();
		int i;
		for (i=str.GetLength()-1;i>=0;i--) if (str[i]=='\\') break;
		m_arrFilePath.Add(new CString(str));
		hRet = m_Tree.InsertItem(
			TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_TEXT,
			tInfo.m_strTitle,//+L" ("+str.Right(str.GetLength()-i-1)+L")",
			1,1,
			0,0,
			(DWORD)m_arrFilePath[m_arrFilePath.GetSize()-1],
			hP, hA);
	}
	else if (str.Right(6)==L".vtext")
	{
		m_arrFilePath.Add(new CString(str));
		hRet = m_Tree.InsertItem(
			TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_TEXT,
			str,2,2,
			0,0,
			(DWORD)m_arrFilePath[m_arrFilePath.GetSize()-1],
			hP, hA);
	}
	m_Tree.Expand(hP,TVE_EXPAND);
	return hRet;
}

void CPageChooseFiles::OnBnClickedAddFiles()
{
	CFileDialog dlgFile(TRUE, NULL , NULL, 
		OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
		L"Test Files, Document Files (*.vtest, *.vtext)|*.vtest;*.vtext||", 
		this, 0);

	if (dlgFile.DoModal()==IDOK)
	{
		POSITION pos=dlgFile.GetStartPosition();
		while (pos)
		{
			CString str=dlgFile.GetNextPathName(pos);
			AddFile(str);
		}
	}
}


BOOL CPageChooseFiles::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_TreeImgLst.Create(16,16,ILC_COLOR32,0,2);
	m_TreeImgLst.Add(AfxGetApp()->LoadIconW(IDI_FOLDER));
	m_TreeImgLst.Add(AfxGetApp()->LoadIconW(IDI_EDIT));
	m_TreeImgLst.Add(AfxGetApp()->LoadIconW(IDI_FILE));
	m_Tree.SetImageList(&m_TreeImgLst,0);

	CBitmap bmp; bmp.LoadBitmapW(IDB_ADDFILE);

	((CButton*)GetDlgItem(IDC_ADD_FILES))->SetBitmap((HBITMAP)bmp);

	ClearTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPageChooseFiles::ClearTree()
{
	m_Tree.DeleteAllItems();

	HTREEITEM hItem=m_Tree.InsertItem(m_pgInfo->m_strCourseTitle);
	m_Tree.SelectItem(hItem);
	m_Tree.SetItemData(hItem,NULL);
}

void CPageChooseFiles::OnBnClickedAddCategory()
{
	HTREEITEM hP=m_Tree.GetSelectedItem();
	HTREEITEM hA=TVI_LAST;
	if (m_Tree.GetItemData(hP)!=NULL) {
		hA=m_Tree.GetPrevSiblingItem(hP); if (!hA) hA=TVI_FIRST;
		hP=m_Tree.GetParentItem(hP);
	}

	HTREEITEM hi=m_Tree.InsertItem(L"Mục mới",0,0,hP,hA);
	m_Tree.SelectItem(hi);
	m_Tree.SetItemData(hi,NULL);
	m_Tree.EditLabel(hi);
}


// void CPageChooseFiles::OnBnClickedTotree2()
// {
// 	HTREEITEM hRoot=m_Tree2.GetSelectedItem();
// 	if (m_Tree2.GetItemData(hRoot)!=-1) hRoot=m_Tree2.GetParentItem(hRoot);
// 	HTREEITEM hSource=m_Tree1.GetSelectedItem();
// 	int n1,n2;
// 	m_Tree1.GetItemImage(hSource,n1,n2);
// 	HTREEITEM hI2=m_Tree2.InsertItem(m_Tree1.GetItemText(hSource),n1,n2,hRoot);
// 	m_Tree2.SetItemData(hI2,(DWORD)hSource);
// 	m_Tree1.SetItemState(hSource,0,TVIS_BOLD);
// 	m_Tree2.Expand(hRoot,TVE_EXPAND);
// }


void CPageChooseFiles::OnTvnEndlabeleditTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 1;
}


void CPageChooseFiles::OnBnClickedRemove()
{
	// TODO: Add your control notification handler code here
}


// void CPageChooseFiles::OnBnClickedRemove1()
// {
// 	HTREEITEM hi=m_Tree1.GetSelectedItem();
// 	if (m_Tree1.GetParentItem(hi)!=TVI_ROOT)
// 		m_Tree1.DeleteItem(hi);
// }


void CPageChooseFiles::OnBnClickedRemove2()
{
	m_Tree.DeleteItem(m_Tree.GetSelectedItem());
}


// void CPageChooseFiles::OnBnClickedMake()
// {
// 	CreateDirectory(L"Temp",NULL);
// 	HTREEITEM hi=m_Tree1.GetChildItem(m_hRDoc);
// 	int i=1;
// 	while (hi!=NULL)
// 	{
// 		CString* s=(CString*)m_Tree1.GetItemData(hi);
// 		CopyFile(*s,L"Temp\\"+IntToString(i)+L".d1",false);
// 		*s=IntToString(i)+L".d1";
// 		m_Tree1.SetItemData(hi,i);
// 		i++;
// 		hi=m_Tree1.GetNextSiblingItem(hi);
// 	}
// 
// 	hi=m_Tree1.GetChildItem(m_hRTest);
// 	i=1;
// 	while (hi!=NULL)
// 	{
// 		CString* s=(CString*)m_Tree1.GetItemData(hi);
// 		CopyFile(*s,L"Temp\\"+IntToString(i)+L".d2",false);
// 		*s=IntToString(i)+L".d2";
// 		m_Tree1.SetItemData(hi,i);
// 		i++;
// 		hi=m_Tree1.GetNextSiblingItem(hi);
// 	}
// 
// 	AfxGetApp()->DoMessageBox(L"Tạo chương trình học thành công",MB_OK,0);
// 	OnOK();
// }


// void CPageChooseFiles::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
// 	// TODO: Add your control notification handler code here
// 	*pResult = 0;
// }

HTREEITEM CPageChooseFiles::MoveItem(HTREEITEM hItem, HTREEITEM hItParent, HTREEITEM hItAfter)
{
	int i; m_Tree.GetItemImage(hItem,i,i);
	int state; state=m_Tree.GetItemState(hItem,TVIS_EXPANDED);
	HTREEITEM hNewIt=m_Tree.InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE,
		m_Tree.GetItemText(hItem),
		i,i,
		state,TVIS_EXPANDED,
		m_Tree.GetItemData(hItem),
		hItParent,hItAfter);

	HTREEITEM hi=m_Tree.GetChildItem(hItem);
	HTREEITEM hi2=m_Tree.GetNextSiblingItem(hi);
	while (hi!=NULL)
	{
		MoveItem(hi,hNewIt,TVI_LAST);
		hi=hi2;
		hi2=m_Tree.GetNextSiblingItem(hi);
	}

	m_Tree.DeleteItem(hItem);
	return hNewIt;
}

void CPageChooseFiles::OnBnClickedUp()
{
	HTREEITEM hi=m_Tree.GetSelectedItem();
	HTREEITEM hiA=m_Tree.GetPrevSiblingItem(m_Tree.GetPrevSiblingItem(hi)); if (hiA==NULL) hiA=TVI_FIRST;
	HTREEITEM hiP=m_Tree.GetParentItem(hi);
	
	HTREEITEM hItem=MoveItem(hi,hiP,hiA);
	m_Tree.SelectItem(hItem);
}

void CPageChooseFiles::OnBnClickedDown()
{
	HTREEITEM hi=m_Tree.GetSelectedItem();
	HTREEITEM hiA=m_Tree.GetNextSiblingItem(hi);
	HTREEITEM hiP=m_Tree.GetParentItem(hi);

	HTREEITEM hItem=MoveItem(hi,hiP,hiA);
	m_Tree.SelectItem(hItem);
}

void CPageChooseFiles::SerializeTree(CArchive& ar)
{
	if (ar.IsStoring())
	{
		SerializeTree2(m_Tree.GetChildItem(TVI_ROOT),ar);
		m_Tree.Expand(TVI_ROOT,TVE_EXPAND);
	}
	else
	{
		ClearTree();
		SerializeTree2(m_Tree.GetChildItem(TVI_ROOT),ar);
	}
}
// 
// int CPageChooseFiles::GetTree1ItemIndex(HTREEITEM hi)
// {
// 	for (int i=0;i<m_hItArray.GetSize();i++)
// 		if (m_hItArray[i]==hi) return i;
// 	return -1;
// }

void CPageChooseFiles::SerializeTree2(HTREEITEM hNode, CArchive& ar)
{
	if (ar.IsStoring())
	{
		HTREEITEM hi=m_Tree.GetChildItem(hNode);
		while (hi!=NULL)
		{
			if (m_Tree.GetItemData(hi)==NULL) // Thư mục
			{
				ar << 1;
				ar << m_Tree.GetItemText(hi);
				SerializeTree2(hi,ar);
			}
			else
			{
				ar << 2;
				ar << *(CString*)m_Tree.GetItemData(hi);
				ar << m_Tree.GetItemText(hi);
			}
			hi=m_Tree.GetNextSiblingItem(hi);
		}

		ar << 0;
	}
	else
	{
		int index;
		ar >> index;
		while (index!=0)
		{
			if (index==1)
			{
				CString str; ar >> str;
				HTREEITEM hi=m_Tree.InsertItem(str,0,0,hNode);
				m_Tree.SetItemData(hi,NULL);
				SerializeTree2(hi,ar);
			}
			else if (index==2)
			{
				CString str; ar >> str;
				CString strText; ar >> strText;
				AddFile(str,hNode,TVI_LAST);
			}
			ar >> index;
		}
	}
}

BOOL CPageChooseFiles::OnSetActive()
{
	m_Tree.SetItemText(m_Tree.GetChildItem(TVI_ROOT),m_pgInfo->m_strCourseTitle);

	return CPropertyPage::OnSetActive();
}


void CPageChooseFiles::OnTvnBeginlabeleditTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	pTVDispInfo->item.stateMask |= TVIS_DROPHILITED;
	pTVDispInfo->item.state |= TVIS_DROPHILITED;
	if (pTVDispInfo->item.lParam==NULL && m_Tree.GetParentItem(pTVDispInfo->item.hItem)!=NULL) 
		*pResult = 0;
	else
		*pResult = 1;
}



void CPageChooseFiles::OnTvnBegindragTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;
}
