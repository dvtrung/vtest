// DlgSelectCourse.cpp : implementation file
//

#include "stdafx.h"
#include "VTestStd.h"
#include "DlgSelectCourse.h"
#include "afxdialogex.h"
#include "DlgNewCourse.h"
#include "DlgConfirmTest.h"
#include "DlgTest.h"


// CDlgSelectCourse dialog

IMPLEMENT_DYNAMIC(CDlgSelectCourse, CDialog)

CDlgSelectCourse::CDlgSelectCourse(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectCourse::IDD, pParent)
{

}

CDlgSelectCourse::~CDlgSelectCourse()
{
	for (int i=0;i<m_arrFilePath.GetSize();i++) delete m_arrFilePath[i];
}

void CDlgSelectCourse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_TREE, m_Tree);
}


BEGIN_MESSAGE_MAP(CDlgSelectCourse, CDialog)
	ON_BN_CLICKED(IDC_ADDCOURSE, &CDlgSelectCourse::OnBnClickedAddcourse)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CDlgSelectCourse::OnLvnItemchangedList)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, &CDlgSelectCourse::OnNMDblclkTree)
END_MESSAGE_MAP()


// CDlgSelectCourse message handlers


BOOL CDlgSelectCourse::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_imgList.Create(32,32,ILC_COLOR32,0,4);
	m_imgList.Add(AfxGetApp()->LoadIconW(IDI_FOLDER));
	m_imgList.Add(AfxGetApp()->LoadIconW(IDI_EDIT));
	m_imgList.Add(AfxGetApp()->LoadIconW(IDI_FILE));

	m_List.SetImageList(&m_imgList,LVSIL_NORMAL);
	m_List.SetImageList(&m_imgList,LVSIL_SMALL);

	m_Tree.SetImageList(&m_imgList,0);

	m_List.InsertColumn(0,L"Khóa học",0,-1,-1);

	m_List.InsertItem(LVIF_TEXT | LVIF_STATE,0,L"Người dùng",0,0,0,0);
	LoadCourse(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSelectCourse::OnBnClickedAddcourse()
{
	CFileDialog dlgFile(TRUE, NULL , NULL, 
		OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
		L"Data Files|*.d||", 
		this, 0);

	if (dlgFile.DoModal()==IDOK)
	{
		CString strPath=dlgFile.GetPathName();

	}
}

void CDlgSelectCourse::LoadCourse(int nCourse)
{
	/*m_List.InsertItem(m_List.GetItemCount(),GetCourseName(nCourse),-1);*/
	CFile f; 
	f.Open(L"data\\C\\"+IntToString(nCourse)+L"\\"+L"0.d",CFile::modeRead);
	CArchive ar(&f,CArchive::load);
	CString str;
	ar >> str;
	HTREEITEM hi=m_Tree.InsertItem(str,-1,-1,TVI_ROOT,TVI_LAST);
	m_Tree.SetItemImage(hi,0,0);
	ar >> str;
	ar >> str;
	ar >> str;
	SerializeTree2(hi,ar,nCourse);
	// 	ar << m_pgChooseFiles->m_Tree1.GetCount();
	ar.Close();
	f.Close();
}

void CDlgSelectCourse::SerializeTree2(HTREEITEM hNode, CArchive& ar, int nCourse)
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
			SerializeTree2(hi,ar,nCourse);
		}
		else if (index==2)
		{
			CString strPath; ar >> strPath;
			CString strText; ar >> strText;
			
			int i=0;
			if (strPath.Right(3)==L".01") i=1;
			else if (strPath.Right(3)==L".02") i=2;

			m_arrFilePath.Add(new CString(L"data\\C\\"+IntToString(nCourse)+L"\\"+strPath));
			m_Tree.InsertItem(
				TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_TEXT,
				strText,
				i,i,
				0,0,
				(DWORD)m_arrFilePath[m_arrFilePath.GetSize()-1],
				hNode, TVI_LAST);
			m_Tree.Expand(hNode,TVE_EXPAND);
		}
		ar >> index;
	}
}

void CDlgSelectCourse::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CDlgSelectCourse::OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_Tree.GetItemData(m_Tree.GetSelectedItem())!=NULL)
	{
		CString strPath=*(CString*)m_Tree.GetItemData(m_Tree.GetSelectedItem());

		CFile f; 
		f.Open(strPath,CFile::modeRead);
		CArchive ar(&f,CArchive::load);
		CTestInfo tInfo;
		tInfo.Serialize(ar);
		ar.Close();
		f.Close();

		CDlgConfirmTest dlg;
		dlg.m_tInfo=&tInfo;
		if (dlg.DoModal()==IDOK)
		{
			CDlgTest dlgTest;
			dlgTest.m_nRemainingTime=tInfo.m_nTime*60;
			dlgTest.m_bShowAnswerIm=dlg.m_bShowAnswerIm;
			dlgTest.m_filePath=strPath;
			dlgTest.DoModal();
		}
	}

	*pResult = 0;
}
