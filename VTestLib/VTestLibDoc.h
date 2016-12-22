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

// VTestLibDoc.h : interface of the CVTestLibDoc class
//
#include "../lib/Item.h"
#include "VTestLibView.h"
#include "ClassView.h"
#include "TestStruct.h"

#pragma once

class CVTestLibView;
class CTagView;

class CVTestLibDoc : public CDocument
{
protected: // create from serialization only
	CVTestLibDoc();
	DECLARE_DYNCREATE(CVTestLibDoc)

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
	virtual ~CVTestLibDoc();
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
	afx_msg void OnAddquest();
protected:
	int m_currentQuest;
	int m_cIndex;
	CTagArray m_TagArray;
	CArray<CItemBase*, CItemBase*> m_markedQuestArray;
public:
	CArray<CItemBase*, CItemBase*> m_QuestArray;
	CArray<CItemBase*, CItemBase*> m_cQuestArr;
	CTagView* m_wndTags;
	CTestStructArray m_testStructArr;
	bool m_bShowAns;
	int m_Mode;
	int GetTagCount() { return m_TagArray.m_TagName.GetSize(); }
	int GetCurrentQuestIndex() { return m_currentQuest + 1; }
	int GetQuestCount() { return m_cQuestArr.GetSize(); }
	CString GetCurrentItemTag(int i) { return m_TagArray.m_Array[m_cIndex]->m_arrTagItem[i]; }
	int GetItemIndexInQuestArray(int cIndex);
	void SetCurrentItemTag(int i,CString str) { m_TagArray.m_Array[m_cIndex]->m_arrTagItem[i]=str; }
	CString GetTagName(int i) { return m_TagArray.m_TagName[i]; }
	CTagArray* GetTagArray() { return &m_TagArray; }
	CItemBase* GetCurrentItem();
	bool IsCurrentItemMarked() { for (int i=0;i<m_markedQuestArray.GetSize();i++) if (m_markedQuestArray[i]==GetCurrentItem()) return true; return false; }
	bool IsItemMarked(CItemBase* it) { for (int i=0;i<m_markedQuestArray.GetSize();i++) if (m_markedQuestArray[i]==it) return true; return false; }
	void RefreshCurrentQuestArray();

	afx_msg void OnFirst();
	afx_msg void OnLast();
	afx_msg void OnNext();
	afx_msg void OnPrevious();

	CVTestLibView* pView;
	CMFCRibbonSlider* m_sliderQuest;
	CMFCRibbonLabel* m_labelQuestPos;
	afx_msg void OnUpdateFirst(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrevious(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLast(CCmdUI *pCmdUI);
	afx_msg void OnQuestSlider();
	afx_msg void OnUpdateQuestSlider(CCmdUI *pCmdUI);
	afx_msg void OnEditquest();
	afx_msg void OnDelquest();
	afx_msg void OnUpdateDelquest(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditquest(CCmdUI *pCmdUI);
	afx_msg void OnEditTag();
	void SetCurrentQuest(int i);
	afx_msg void OnQuestRandom();
	afx_msg void OnUpdateQuestRandom(CCmdUI *pCmdUI);
	afx_msg void OnShowhideAns();
	afx_msg void OnUpdateShowhideAns(CCmdUI *pCmdUI);
	afx_msg void OnShowAll();
	afx_msg void OnUpdateShowAll(CCmdUI *pCmdUI);
	afx_msg void OnShowMarked();
	afx_msg void OnUpdateShowMarked(CCmdUI *pCmdUI);
	afx_msg void OnShowFilter();
	afx_msg void OnUpdateShowFilter(CCmdUI *pCmdUI);
	afx_msg void OnQuestMark();
	afx_msg void OnQuestMarkAll();
	afx_msg void OnUpdateQuestMark(CCmdUI *pCmdUI);
	afx_msg void OnQuestQuicktest();
	afx_msg void OnQuestUnmarkAll();
	afx_msg void OnUpdateQuestMarkedcount(CCmdUI *pCmdUI);
	afx_msg void OnTestNewTest();
	void ClearAll();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
//	afx_msg void OnEditFind();
	afx_msg void OnAddtext();
	afx_msg void OnEditRenameTag();
	afx_msg void OnTestMarkRandom();
};
