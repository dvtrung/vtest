#include "stdafx.h"
#include "HtmlEditCtrlEx.h"
// CHtmlEditCtrlEx

IMPLEMENT_DYNCREATE(CHtmlEditCtrlEx, CHtmlEditCtrl)
BEGIN_MESSAGE_MAP(CHtmlEditCtrlEx, CHtmlEditCtrl)
END_MESSAGE_MAP()

BOOL CHtmlEditCtrlEx::CreateFromStatic( UINT nID, CWnd* pParent ) {
	CStatic wndStatic;
	if ( !wndStatic.SubclassDlgItem(nID, pParent)) {
		return( FALSE );
	}
	CRect rc;
	wndStatic.GetWindowRect( &rc );
	pParent->ScreenToClient( &rc );
	return Create( 0, (WS_CHILD | WS_VISIBLE), rc, pParent, nID, 0 );
};

BOOL CHtmlEditCtrlEx::PreTranslateMessage(MSG* pMsg)
{
	if ( !m_fEnableContextMenu ) {
		switch (pMsg->message) {
				case WM_CONTEXTMENU:
				case WM_RBUTTONUP:
				case WM_RBUTTONDOWN:
				case WM_RBUTTONDBLCLK:
					if (pMsg->message==WM_RBUTTONUP) {
						// let parent handle context menu
						GetParent()->SendMessage(WM_CONTEXTMENU, pMsg->wParam, pMsg->lParam);
					}
					return TRUE; // eat it
		}
	}
	return CHtmlEditCtrl::PreTranslateMessage(pMsg);
}
// overide to discard BOM
HRESULT CHtmlEditCtrlEx::GetDocumentHTML( CString& sHtml )
{
	HRESULT hr= CHtmlEditCtrl::GetDocumentHTML( sHtml );
	if ( sHtml[0] != '<' ) {
		sHtml= sHtml.Mid(3);
	}
	return hr;
}
HRESULT CHtmlEditCtrlEx::SetDocumentHTML( CString& sHtml )
{
	HRESULT hr;
	int nOffset=0;
	if ( sHtml[0]==0xef && sHtml[1]==0xbb && sHtml[2]==0xbf ) { // BOM may be there
		nOffset= 3;
	}
	hr= CHtmlEditCtrl::SetDocumentHTML( sHtml.Mid(nOffset) );
	return hr;
}
