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

// VTestDoc.h : interface of the CVTestDoc class
//
#include "..\ItemBase\Item.h"
#include "..\ItemBase\ItemArray.h"
#include "..\lib\TestInfo.h"

#pragma once


class CVTestDoc : public CDocument
{
protected: // create from serialization only
	CVTestDoc();
	DECLARE_DYNCREATE(CVTestDoc)

public:
	CItemArray m_Items;
	CTestInfo m_tInfo;
	CMFCRibbonProgressBar* m_prog;
	CMFCRibbonStatusBar* m_statusBar;
	CMFCRibbonStatusBarPane* m_statusText;
public:
	afx_msg void OnEditAddQuestABCD();
public:
	afx_msg void OnFileProperties();
	void ReCalcHeight();
public:
	afx_msg void OnEditDelete();
public:
	afx_msg void OnUpdateEditDelete(CCmdUI *pCmdUI);
public:
	virtual void OnCloseDocument();
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
public:
	afx_msg void OnEditAddtext();
public:
	afx_msg void OnFileWizard();
public:
	afx_msg void OnItemDown();
public:
	afx_msg void OnItemUp();
public:
	afx_msg void OnEditAddContainer();
public:
	afx_msg void OnEditEdit();
public:
	afx_msg void OnUpdateEditEdit(CCmdUI *pCmdUI);

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CVTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS


public:
	afx_msg void OnEditAddQuestTrueFalse();
	afx_msg void OnEditAddQuest();
	afx_msg void OnFilePageSetup();

	int m_nMarginLeft;
	bool m_bShowHint;
	bool m_bShowAns;
	afx_msg void OnFileRun();
	void OnIdleRedrawItem();
	UINT ThreadRedrawItem(LPVOID);
	CWinThread* m_pDrawItThread;
	int m_drawnItem;
	afx_msg void OnViewShowanswer();
	afx_msg void OnUpdateViewShowanswer(CCmdUI *pCmdUI);
	afx_msg void OnViewShowhint();
	afx_msg void OnUpdateViewShowhint(CCmdUI *pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnFileNewLec();
	afx_msg void OnFileNewTest();
	afx_msg void OnExportHtml();
	afx_msg void OnHomeTronDeThi();
	afx_msg void OnExportVtestx();
};
