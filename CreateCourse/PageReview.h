#pragma once
#include "afxcmn.h"

// CPageReview dialog

class CPageReview : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageReview)

public:
	CPageReview();
	virtual ~CPageReview();

// Dialog Data
	enum { IDD = IDD_PROP_REVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	CImageList m_imgList;
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL OnSetActive();
	void RefreshItems();
	HTREEITEM m_hCurrent;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
//	afx_msg void OnHdnItemdblclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
