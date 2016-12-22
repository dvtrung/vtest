#include "VTestEditCtrl.h"
#pragma once

// CVTestEdit

class AFX_EXT_CLASS CVTestEdit : public CWnd
{
	DECLARE_DYNAMIC(CVTestEdit)

public:
	CVTestEdit();
	CVTestEdit(Gdiplus::Font* f);
	virtual ~CVTestEdit();
	CString m_Text;
	bool bEdit;
	bool bCreate;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL RegisterWindowClass();
	CVTestEditCtrl m_Edit;
	void SetText(CString);
	CString GetText();
	Gdiplus::Font* m_Font;
	void Create(CWnd* pStatic);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	LRESULT OnTurnToPreview(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
public:
	afx_msg void OnDestroy();
};


