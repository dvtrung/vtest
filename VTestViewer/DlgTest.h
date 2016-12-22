#pragma once
#include "../lib/ItemArray.h"
#include "../lib/TestInfo.h"
#include "DlgWait.h"
#include "QuestList.h"
#include "QuestView.h"
#include "../lib/TestHistory.h"

// CDlgTest dialog

class CDlgTest : public CDialog
{
	DECLARE_DYNAMIC(CDlgTest)

public:
	CDlgTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTest();

// Dialog Data
	enum { IDD = IDD_DIALOG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCbnSelchangeComboShow();
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
public:
	int m_nRemainingTime;
	CString m_filePath;
	CItemArray m_Items;
	CTestInfo m_tInfo;
	CTestHistoryArray m_hisArr;
	bool m_bDone;
	bool m_bShowAnswerIm;
	int m_nPrevState;
	int m_nStdType;
	CString m_TakenTime;
	int m_nReviewTest;
	
	CQuestList m_Tab;
	CArray<CItemBase*> m_TabParam;

	CComboBox m_cbShow;
	CTabCtrl m_TabShow;
	Gdiplus::Font* m_Font;
	afx_msg void OnBnClickedDone();
	afx_msg void OnBnClickedCancel();
	LRESULT OnTabChangeSel(WPARAM wp, LPARAM /*lp*/);
	void RefreshQuest();
	void RefreshView();
	LRESULT OnDoneQuest(WPARAM wParam, LPARAM lParam);
	LRESULT OnDoneAQuest(WPARAM wParam, LPARAM lParam);
	CQuestView m_QuestView;
protected:
	afx_msg LRESULT OnMsgQuestTabChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	int m_nView;
};
