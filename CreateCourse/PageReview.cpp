// PageReview.cpp : implementation file
//

#include "stdafx.h"
#include "CreateCourse.h"
#include "PageReview.h"
#include "afxdialogex.h"

// CPageReview dialog

extern CPageChooseFiles* m_pgChooseFiles;

IMPLEMENT_DYNAMIC(CPageReview, CPropertyPage)

CPageReview::CPageReview()
	: CPropertyPage(CPageReview::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;
	m_psp.pszHeaderTitle=L"VOcean";
	m_psp.pszHeaderSubTitle=L"Xem lại nội dung";
}

CPageReview::~CPageReview()
{
}

void CPageReview::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CPageReview, CPropertyPage)
//	ON_WM_ACTIVATE()
	ON_WM_CREATE()
//	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CPageReview::OnHdnItemdblclickList)
ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CPageReview::OnNMDblclkList)
END_MESSAGE_MAP()


// CPageReview message handlers


//void CPageReview::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CPropertyPage::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO: Add your message handler code here
//}


BOOL CPageReview::OnSetActive()
{
	m_hCurrent=TVI_ROOT;
	RefreshItems();

	return CPropertyPage::OnSetActive();
}

void CPageReview::RefreshItems()
{
	m_List.DeleteAllItems();
	CTreeCtrl* tree=&m_pgChooseFiles->m_Tree;
	if (m_hCurrent!=TVI_ROOT)
		m_List.InsertItem(LVIF_TEXT | LVIF_STATE,m_List.GetItemCount(),L"...",0,0,0,0);
	HTREEITEM hi=tree->GetChildItem(m_hCurrent);
	while (hi!=NULL)
	{
		int n1,n2; tree->GetItemImage(hi,n1,n2);
		int i=m_List.InsertItem(LVIF_TEXT | LVIF_STATE | LVIF_IMAGE | LVIF_PARAM,
			m_List.GetItemCount(),tree->GetItemText(hi),0,0,n1,(DWORD)hi);
		hi=tree->GetNextSiblingItem(hi);
	}
}


int CPageReview::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


BOOL CPageReview::OnInitDialog()
{
	CPropertyPage::OnInitDialog();


	m_imgList.Create(32,32,ILC_COLOR32,0,4);
	m_imgList.Add(AfxGetApp()->LoadIconW(IDI_FOLDER));
	m_imgList.Add(AfxGetApp()->LoadIconW(IDI_EDIT));
	m_imgList.Add(AfxGetApp()->LoadIconW(IDI_FILE));

	m_List.SetImageList(&m_imgList,LVSIL_NORMAL);
	m_List.SetImageList(&m_imgList,LVSIL_SMALL);

	m_List.InsertColumn(0,L"Tiêu đề",0,-1,-1);
	m_List.SetColumnWidth(0,LVSCW_AUTOSIZE_USEHEADER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPageReview::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (m_List.GetItemState(pNMItemActivate->iItem,LVIS_SELECTED)!=LVIS_SELECTED) return;
	if (pNMItemActivate->iItem!=-1)
	{
		if (m_List.GetItemData(pNMItemActivate->iItem)==NULL) //Back
		{
			m_hCurrent=m_pgChooseFiles->m_Tree.GetParentItem(m_hCurrent);
			if (m_hCurrent==NULL) m_hCurrent=TVI_ROOT;
			RefreshItems();
		}
		else
		{
			HTREEITEM hi = (HTREEITEM)m_List.GetItemData(pNMItemActivate->iItem);
			if (m_pgChooseFiles->m_Tree.GetItemData(hi)==NULL)
			{
				m_hCurrent = hi;
				RefreshItems();
			}
			else
			{
				CString str=*(CString*)m_pgChooseFiles->m_Tree.GetItemData(hi);
				ShellExecute(NULL,NULL,str,NULL,NULL,SW_SHOW);
			}
		}
	}
	*pResult = 0;
}
