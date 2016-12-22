#pragma once


// CVTestEditCtrl
#define MSG_TURN_TO_PREVIEW WM_USER+3

class AFX_EXT_CLASS CVTestEditCtrl : public CEdit
{
	DECLARE_DYNAMIC(CVTestEditCtrl)

public:
	CVTestEditCtrl();
	virtual ~CVTestEditCtrl();
	CFont font;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
public:
	afx_msg void OnEditCut();
public:
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
public:
	afx_msg void OnEditctrlTurnToPreview();
public:
	afx_msg void OnEditUndo();
public:
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
};


