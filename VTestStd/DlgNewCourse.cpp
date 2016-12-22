// DlgNewCourse.cpp : implementation file
//

#include "stdafx.h"
#include "VTestStd.h"
#include "DlgNewCourse.h"
#include "afxdialogex.h"


// CDlgNewCourse dialog

IMPLEMENT_DYNAMIC(CDlgNewCourse, CDialog)

CDlgNewCourse::CDlgNewCourse(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewCourse::IDD, pParent)
{

}

CDlgNewCourse::~CDlgNewCourse()
{
	for (int i=0;i<m_arrFilePath.GetSize();i++)
		delete m_arrFilePath[i];
}

void CDlgNewCourse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree1);
	DDX_Control(pDX, IDC_TREE2, m_Tree2);
}


BEGIN_MESSAGE_MAP(CDlgNewCourse, CDialog)
	ON_BN_CLICKED(IDC_ADD_FILES, &CDlgNewCourse::OnBnClickedAddFiles)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE1, &CDlgNewCourse::OnTvnBegindragTree1)
	ON_BN_CLICKED(IDC_ADD_CATEGORY, &CDlgNewCourse::OnBnClickedAddCategory)
	ON_BN_CLICKED(IDC_TOTREE2, &CDlgNewCourse::OnBnClickedTotree2)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE2, &CDlgNewCourse::OnTvnEndlabeleditTree2)
	ON_BN_CLICKED(IDC_REMOVE1, &CDlgNewCourse::OnBnClickedRemove1)
	ON_BN_CLICKED(IDC_REMOVE2, &CDlgNewCourse::OnBnClickedRemove2)
	ON_BN_CLICKED(IDC_MAKE, &CDlgNewCourse::OnBnClickedMake)
END_MESSAGE_MAP()


// CDlgNewCourse message handlers


void CDlgNewCourse::OnBnClickedAddFiles()
{
	CFileDialog dlgFile(TRUE, NULL , NULL, 
		OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
		L"Test Files, Document Files (*.vtest, *.vtext)|*.vtest;*.vtext||", this, 0);

	if (dlgFile.DoModal()==IDOK)
	{
		POSITION pos=dlgFile.GetStartPosition();
		while (pos)
		{
			CString str=dlgFile.GetNextPathName(pos);
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
				HTREEITEM hi=m_Tree1.InsertItem(tInfo.m_strTitle+L" ("+str.Right(str.GetLength()-i-1)+L")",1,1,m_hRTest);
				m_arrFilePath.Add(new CString(str));
				m_Tree1.SetItemState(hi,TVIS_BOLD,TVIS_BOLD);
				m_Tree1.SetItemData(hi,(DWORD)m_arrFilePath[m_arrFilePath.GetSize()-1]);
			}
			else if (str.Right(6)==L".vtext")
			{
				HTREEITEM hi=m_Tree1.InsertItem(str,2,2,m_hRDoc);
				m_arrFilePath.Add(new CString(str));
				m_Tree1.SetItemState(hi,TVIS_BOLD,TVIS_BOLD);
				m_Tree1.SetItemData(hi,(DWORD)m_arrFilePath[m_arrFilePath.GetSize()-1]);
			}
		}
	}

	m_Tree1.Expand(m_hRDoc,TVE_EXPAND);
	m_Tree1.Expand(m_hRTest,TVE_EXPAND);
}


BOOL CDlgNewCourse::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_TreeImgLst.Create(16,16,ILC_COLOR32,0,2);
	m_TreeImgLst.Add(AfxGetApp()->LoadIconW(IDI_FOLDER));
	m_TreeImgLst.Add(AfxGetApp()->LoadIconW(IDI_EDIT));
	m_TreeImgLst.Add(AfxGetApp()->LoadIconW(IDI_FILE));
	m_Tree1.SetImageList(&m_TreeImgLst,0);
	m_Tree2.SetImageList(&m_TreeImgLst,0);

	CBitmap bmp; bmp.LoadBitmapW(IDB_ADDFILE);

	((CButton*)GetDlgItem(IDC_ADD_FILES))->SetBitmap((HBITMAP)bmp);

	m_hRDoc=m_Tree1.InsertItem(L"Tài liệu",0,0);
	m_Tree1.Expand(m_hRDoc,TVE_EXPAND);
	m_hRTest=m_Tree1.InsertItem(L"Đề thi",0,0);
	m_Tree1.Expand(m_hRTest,TVE_EXPAND);

	HTREEITEM hItem=m_Tree2.InsertItem(L"Nội dung học");
	m_Tree2.SelectItem(hItem);
	m_Tree2.SetItemData(hItem,-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgNewCourse::OnTvnBegindragTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult = 0;
}


void CDlgNewCourse::OnBnClickedAddCategory()
{
	HTREEITEM hRoot=m_Tree2.GetSelectedItem();
	if (m_Tree2.GetItemData(hRoot)!=-1) hRoot=m_Tree2.GetParentItem(hRoot);
	HTREEITEM hi=m_Tree2.InsertItem(L"Mục mới",0,0,hRoot);
	m_Tree2.SelectItem(hi);
	m_Tree2.SetItemData(hi,-1);
	m_Tree2.EditLabel(hi);
}


void CDlgNewCourse::OnBnClickedTotree2()
{
	HTREEITEM hRoot=m_Tree2.GetSelectedItem();
	if (m_Tree2.GetItemData(hRoot)!=-1) hRoot=m_Tree2.GetParentItem(hRoot);
	HTREEITEM hSource=m_Tree1.GetSelectedItem();
	int n1,n2;
	m_Tree1.GetItemImage(hSource,n1,n2);
	HTREEITEM hI2=m_Tree2.InsertItem(m_Tree1.GetItemText(hSource),n1,n2,hRoot);
	m_Tree2.SetItemData(hI2,(DWORD)hSource);
	m_Tree1.SetItemState(hSource,0,TVIS_BOLD);
	m_Tree2.Expand(hRoot,TVE_EXPAND);
}


void CDlgNewCourse::OnTvnEndlabeleditTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 1;
}


void CDlgNewCourse::OnBnClickedRemove()
{
	// TODO: Add your control notification handler code here
}


void CDlgNewCourse::OnBnClickedRemove1()
{
	// TODO: Add your control notification handler code here
}


void CDlgNewCourse::OnBnClickedRemove2()
{
	// TODO: Add your control notification handler code here
}


void CDlgNewCourse::OnBnClickedMake()
{
	CreateDirectory(L"Temp",NULL);
	HTREEITEM hi=m_Tree1.GetChildItem(m_hRDoc);
	int i=1;
	while (hi!=NULL)
	{
		CString* s=(CString*)m_Tree1.GetItemData(hi);
		CopyFile(*s,L"Temp\\"+IntToString(i)+L".d1",false);
		*s=IntToString(i)+L".d1";
		m_Tree1.SetItemData(hi,i);
		i++;
		hi=m_Tree1.GetNextSiblingItem(hi);
	}

	hi=m_Tree1.GetChildItem(m_hRTest);
	i=1;
	while (hi!=NULL)
	{
		CString* s=(CString*)m_Tree1.GetItemData(hi);
		CopyFile(*s,L"Temp\\"+IntToString(i)+L".d2",false);
		*s=IntToString(i)+L".d2";
		m_Tree1.SetItemData(hi,i);
		i++;
		hi=m_Tree1.GetNextSiblingItem(hi);
	}

	AfxGetApp()->DoMessageBox(L"Tạo chương trình học thành công",MB_OK,0);
	OnOK();
}
