#pragma once
#include <afxhtml.h>
// CHtmlEditCtrlEx control

class CHtmlEditCtrlEx : public CHtmlEditCtrl
{
	DECLARE_DYNCREATE(CHtmlEditCtrlEx)
protected:
public:
	CHtmlEditCtrlEx() { m_fEnableContextMenu=true; };    
	virtual ~CHtmlEditCtrlEx()  {};

	BOOL CreateFromStatic( UINT nID, CWnd* pParent );
	void EnableContextMenu( BOOL fEnab ) { m_fEnableContextMenu= fEnab; };
	HRESULT GetDocumentHTML( CString& sHtml ); // override discards BOM
	HRESULT SetDocumentHTML( CString& sHtml ); // override discards BOM

protected:
	BOOL m_fEnableContextMenu;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg); // context menu suppression
};