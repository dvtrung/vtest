// TabCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "VTestStd.h"
#include "TabCtrlEx.h"


// CTabCtrlEx

IMPLEMENT_DYNAMIC(CTabCtrlEx, CTabCtrl)

CTabCtrlEx::CTabCtrlEx()
{

}

CTabCtrlEx::~CTabCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CTabCtrlEx, CTabCtrl)

	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// CTabCtrlEx message handlers

void CTabCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics gr(lpDrawItemStruct->hDC);

	Bitmap bmp(lpDrawItemStruct->rcItem.right-lpDrawItemStruct->rcItem.left,
		lpDrawItemStruct->rcItem.bottom-lpDrawItemStruct->rcItem.top,PixelFormat32bppARGB);
	Graphics memGr(&bmp);
	Pen pen(Color::Gray,1);
	memGr.DrawRectangle(&pen,1,1,bmp.GetWidth(),bmp.GetHeight());

	gr.DrawImage(&bmp,lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top);
}


void CTabCtrlEx::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CTabCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
