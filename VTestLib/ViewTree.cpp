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
#include "ViewTree.h"
#include "resource.h"
#include "..\lib\appfunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, &CViewTree::OnTvnKeydown)
	//ON_NOTIFY_REFLECT(NM_TVSTATEIMAGECHANGING, &CViewTree::OnNMTVStateImageChanging)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree message handlers

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


int CViewTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitStateImageList();

	return 0;
}

void CViewTree::InitStateImageList()
{
	m_imageState.Create( 16, 15, ILC_COLOR32 | ILC_MASK, 0, 1);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_TRI_STATE_TREE);
	m_imageState.Add(&bmp, RGB(0,255,255));
	SetImageList( &m_imageState, TVSIL_STATE );
}


void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}


void CViewTree::OnTvnKeydown(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	if (pTVKeyDown->wVKey == VK_SPACE)
	{
		ToogleCheckbox(GetSelectedItem());
	}
	*pResult = 0;
}


void CViewTree::OnNMTVStateImageChanging(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVSTATEIMAGECHANGING pTVStateChange = reinterpret_cast<LPNMTVSTATEIMAGECHANGING>(pNMHDR);
	

	*pResult = 1;
}

void CViewTree::SetCheck(HTREEITEM hItem, int iState)
{
	SetItemState( hItem, INDEXTOSTATEIMAGEMASK(iState+1), TVIS_STATEIMAGEMASK );
	//RedrawItem(hItem);
	// TRACE("SetCheck=%u\n", iState);
}

int CViewTree::GetCheck(HTREEITEM hItem) const
{
	return (GetItemState( hItem, TVIS_STATEIMAGEMASK )>>12) - 1;
}

void CViewTree::RedrawItem(HTREEITEM hItem)
{
	CRect r;
	GetItemRect(hItem, &r, FALSE);
	InvalidateRect(r);
}

void CViewTree::CheckRoot(HTREEITEM hParent, bool bCheck)
{
	HTREEITEM hItem=GetChildItem(hParent);
	while (hItem!=NULL)
	{
		CheckRoot(hItem,bCheck);
		SetCheck(hItem,bCheck);
		hItem=GetNextSiblingItem(hItem);
	}
}

void CViewTree::RefreshCheckState(HTREEITEM hParent)
{
	HTREEITEM hItem=GetChildItem(hParent);
	bool bChecked=false; bool bNotChecked=false;
	if (hItem==NULL) return;
	while (hItem!=NULL)
	{
		RefreshCheckState(hItem);
		if (GetCheck(hItem)==0) bNotChecked=true;
		else if (GetCheck(hItem)==1) bChecked=true;
		else { bChecked=true; bNotChecked=true; }
		hItem=GetNextSiblingItem(hItem);
	}
	if (bChecked && !bNotChecked) SetCheck(hParent,1);
	else if (bNotChecked && !bChecked) SetCheck(hParent,0);
	else SetCheck(hParent,2);
}

HTREEITEM CViewTree::FindChildItem(HTREEITEM hParent,CString strText)
{
	HTREEITEM hItemChild=GetChildItem(hParent);
	while (hItemChild!=NULL)
	{
		CString str=GetItemText(hItemChild);
		if (str==strText) return hItemChild;
		hItemChild=GetNextSiblingItem(hItemChild);
	}
	return NULL;
}

HTREEITEM CViewTree::FindItem(HTREEITEM hItem, CString strText)
{
	CStringArray arr;
	SplitString(strText,':',arr);
	for (int i=0;i<arr.GetSize();i++) arr[i]=arr[i].Trim();
	HTREEITEM hParent=hItem;
	for (int i=0;i<arr.GetSize();i++)
	{
		if (arr[i]=="") arr[i]=L"<null>";
		HTREEITEM hIt=FindChildItem(hParent,arr[i]);
		hParent=hIt;
	}
	HTREEITEM hChild=FindChildItem(hParent,L"<null>");
	if (hChild!=NULL) return hChild;
	return hParent;
}


HTREEITEM CViewTree::MoveItem(HTREEITEM hItem, HTREEITEM hItParent, HTREEITEM hItAfter)
{
	int i; GetItemImage(hItem,i,i);
	int state; state=GetItemState(hItem,TVIS_EXPANDED);
	HTREEITEM hNewIt=InsertItem(TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE,
		GetItemText(hItem),
		i,i,
		state,TVIS_EXPANDED,
		GetItemData(hItem),
		hItParent,hItAfter);

	HTREEITEM hi=GetChildItem(hItem);
	HTREEITEM hi2=GetNextSiblingItem(hi);
	while (hi!=NULL)
	{
		MoveItem(hi,hNewIt,TVI_LAST);
		hi=hi2;
		hi2=GetNextSiblingItem(hi);
	}

	DeleteItem(hItem);
	return hNewIt;
}

void CViewTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT nHTFlags = 0;
	HTREEITEM hItem = HitTest(point, &nHTFlags);
	if (hItem && nHTFlags & TVHT_ONITEMSTATEICON)
	{
		SelectItem(hItem);
		ToogleCheckbox(hItem);
	}
	else
		CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CViewTree::ToogleCheckbox(HTREEITEM hItem)
{
	SetRedraw(0);
	this->SelectItem(hItem);
	if (GetChildItem(hItem)==NULL)
	{
		if (GetCheck(hItem)==0) SetCheck(hItem,1);
		else SetCheck(hItem,0);
	}
	else
	{
		if (GetCheck(hItem)==0) 
		{
			SetCheck(hItem,1);
			CheckRoot(hItem,true);
		}
		else if (GetCheck(hItem)==1 || GetCheck(hItem)==2) 
		{
			SetCheck(hItem,0); 
			CheckRoot(hItem,false);
		}
	}

	HTREEITEM hParent=hItem;
	while (GetParentItem(hParent)!=NULL) hParent=GetParentItem(hParent);
	RefreshCheckState(hParent);

	SetRedraw(1);
	AfxGetMainWnd()->SendMessage(WM_COMMAND,ID_SHOW_FILTER);
}