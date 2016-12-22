// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "VTestLib.h"
#include "../lib/appfunc.h"

class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CTagView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTagView::CTagView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CTagView::~CTagView()
{
}

BEGIN_MESSAGE_MAP(CTagView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
	ON_NOTIFY(TVN_ENDLABELEDIT,2,&CTagView::OnEndLabelEdit)
	ON_NOTIFY(TVN_BEGINLABELEDIT,2,&CTagView::OnBeginLabelEdit)
	ON_NOTIFY(TVN_ITEMCHANGED,2,&CTagView::OnItemChanged)
	ON_NOTIFY(NM_DBLCLK,2,&CTagView::OnItemDbClick)
	ON_COMMAND(ID_DELETE_FOLDER, &CTagView::OnDeleteFolder)
	ON_UPDATE_COMMAND_UI(ID_DELETE_FOLDER, &CTagView::OnUpdateDeleteFolder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView message handlers

int CTagView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create views:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_CHECKBOXES | TVS_EDITLABELS;

	if (!m_Tree.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create Class View\n");
		return -1;      // fail to create
	}

	//m_Tree.ModifyStyleEx(0,TVS_EX_DIMMEDCHECKBOXES | TVS_EX_EXCLUSIONCHECKBOXES | TVS_EX_PARTIALCHECKBOXES);

	// Load images:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* Is locked */);

	//OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CClassViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	return 0;
}

void CTagView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CTagView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_Tree;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CTagView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_Tree.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CTagView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CTagView::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CClassViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CClassViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CTagView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CTagView::OnClassAddMemberFunction()
{
	AfxMessageBox(_T("Add member function..."));
}

void CTagView::OnClassAddMemberVariable()
{
	// TODO: Add your command handler code here
}

void CTagView::OnClassDefinition()
{
	// TODO: Add your command handler code here
}

void CTagView::OnClassProperties()
{
	// TODO: Add your command handler code here
}

void CTagView::OnNewFolder()
{
	HTREEITEM it=m_Tree.InsertItem(L"New Item");
	m_Tree.SetItemData(it,m_tagArray->m_TagName.GetSize());
	m_tagArray->AddTagName(L"New Item");
	m_Tree.EditLabel(it);
}

void CTagView::OnDeleteFolder()
{
	if (AfxMessageBox(L"Bạn muốn xóa nhãn này ?",MB_YESNO | MB_ICONASTERISK)==IDYES)
	{
		m_tagArray->DeleteTag(m_Tree.GetItemText(m_Tree.GetSelectedItem()));
		m_Tree.DeleteItem(m_Tree.GetSelectedItem());
	}
}

void CTagView::OnUpdateDeleteFolder(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Tree.GetSelectedItem()!=NULL && 
		m_Tree.GetParentItem(m_Tree.GetSelectedItem())==NULL);
}


void CTagView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_Tree.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CTagView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_Tree.SetFocus();
}

void CTagView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	
	//m_ClassViewImages.Add(&bmp, RGB(255, 0, 0));

	//m_ClassViewImages.Add(AfxGetApp()->LoadStandardIcon(MAKEINTRESOURCEW(IDI_CLASS_VIEW)));

	//m_Tree.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	//m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* Locked */);
}

void CTagView::OnEndLabelEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	int i=pTVDispInfo->item.lParam;
	if (pTVDispInfo->item.mask & TVIF_TEXT) m_tagArray->m_TagName[i]=pTVDispInfo->item.pszText;
	*pResult = 1;
}

void CTagView::OnBeginLabelEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	HTREEITEM hIt=m_Tree.GetParentItem(pTVDispInfo->item.hItem);
	*pResult = (hIt!=NULL);
}

void CTagView::OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	HTREEITEM hItem=pTVDispInfo->item.hItem;
// 	if (m_Tree.GetParentItem(hItem)==NULL && m_Tree.GetCheck(hItem))
// 	{
// 		HTREEITEM hItemChild=m_Tree.GetChildItem(hItem);
// 		while (hItemChild!=NULL)
// 		{
// 			m_Tree.SetCheck(hItemChild,1);
// 			hItemChild=m_Tree.GetNextSiblingItem(hItemChild);
// 		}
// 	}
	*pResult = 0;
}

void CTagView::OnItemDbClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	HTREEITEM hItem=pTVDispInfo->item.hItem;

	//int i=m_Tree.SetItem(hItem,TVIF_STATE,NULL,0,0,TVIS_BOLD,TVIS_BOLD,0);
	//m_Tree.SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);
	//ASSERT(TVIS_BOLD & m_Tree.GetItemState(hItem, TVIS_BOLD));
}

void CTagView::RefreshItem()
{
	m_Tree.DeleteAllItems();
	for (int i=0;i<m_tagArray->m_TagName.GetSize();i++)
	{
		HTREEITEM hIt=m_Tree.InsertItem(m_tagArray->m_TagName[i]);
		CStringArray arr;
		m_tagArray->GetItemsInTag(arr,i);
		for (int j=0;j<arr.GetSize();j++) { AddTreeItem(hIt,arr[j]!="" ? arr[j] : L"<null>"); }
		//ResetChildStates(hIt);
		//m_Tree.SortChildren(hIt);
		//m_Tree.Expand(hIt,TVE_EXPAND);
	}
	RemoveNullNode(TVI_ROOT);
	SortItem();
}

void CTagView::AddTreeItem(HTREEITEM hItem, CString strText)
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

CString CTagView::GetTreeItemFullText(HTREEITEM hTreeItem)
{
	HTREEITEM hParent=hTreeItem;
	CString str;
	while (m_Tree.GetParentItem(hParent)!=NULL)
	{
		if (m_Tree.GetItemText(hParent)!=L"<null>")
			str=L" : " + m_Tree.GetItemText(hParent) + str;
		hParent=m_Tree.GetParentItem(hParent);
	}
	str.Delete(0,3);
	if (str.Right(3)==L" : ") str.Delete(str.GetLength()-4,3);
	return str;
}

void CTagView::RefreshChildItem()
{
	m_Tree.SetRedraw(0);
	HTREEITEM hItem=m_Tree.GetChildItem(TVI_ROOT);
	int i=0;
	while (hItem!=NULL)	{
		CStringArray arr;
		m_tagArray->GetItemsInTag(arr,i); i++;
		RecursiveDeleteItem(hItem,arr);
		for (int j=0;j<arr.GetSize();j++) AddTreeItem(hItem,arr[j]);
		hItem=m_Tree.GetNextSiblingItem(hItem);
	}
	RemoveNullNode(TVI_ROOT);
	SortItem();
	m_Tree.RefreshCheckState(TVI_ROOT);
	m_Tree.SetRedraw(1);
}

void CTagView::RemoveNullNode(HTREEITEM hParent)
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

// Xóa node thừa

void CTagView::RecursiveDeleteItem(HTREEITEM hParent, CStringArray& arr)
{
	HTREEITEM hItem=m_Tree.GetChildItem(hParent);
	while (hItem!=NULL)
	{
		RecursiveDeleteItem(hItem,arr);
		CString str=GetTreeItemFullText(hItem);
		bool b=false;
		for (int i=0;i<arr.GetSize();i++) if (arr[i]==str) {b=true; break;}
		if (!b) {
			HTREEITEM hOldIt=hItem;
			hItem=m_Tree.GetNextSiblingItem(hItem);
			m_Tree.DeleteItem(hOldIt);
		}
		else		
			hItem=m_Tree.GetNextSiblingItem(hItem);
	}
}

void CTagView::SortItem()
{
	HTREEITEM hItem=m_Tree.GetChildItem(TVI_ROOT);
	while (hItem!=NULL)	{
		Sort(hItem);
		hItem=m_Tree.GetNextSiblingItem(hItem);
	}
}

void CTagView::Sort(HTREEITEM hItem)
{
	HTREEITEM hChild=m_Tree.GetChildItem(hItem);
	while (hChild!=NULL)
	{
		Sort(hChild);
		m_Tree.SortChildren(hItem);
		hChild=m_Tree.GetNextSiblingItem(hChild);
	}
}