#pragma once
#include "VTestLibDoc.h"
#include "resource.h"
class CVTestLibDoc;
// CDlgFind dialog

class CDlgFind : public CDialog
{
	DECLARE_DYNAMIC(CDlgFind)

public:
	CDlgFind(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgFind();

// Dialog Data
	enum { IDD = IDD_DLGFIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bQues;
	BOOL m_bAns;
	BOOL m_bTag;
	CVTestLibDoc* m_pDoc;
	afx_msg void OnBnClickedFind();
	CString m_strFind;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnOK();
	bool FindText(CString strText, CString strFind);
};
