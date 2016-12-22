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

// VTestLibDoc.cpp : implementation of the CVTestLibDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VTestLib.h"
#endif

#include "VTestLibDoc.h"
#include "../VTest/DlgAddQuestion.h"
#include "../VTest/DlgAddText.h"
#include "../lib/ItemArray.h"
#include "../lib/TestInfo.h"
#include "DlgFind.h"
#include "DlgRenameTag.h"
#include "DlgMarkRandom.h"
#include "../lib/TestHistory.h"

#include <propkey.h>

extern Gdiplus::Font* m_Font;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVTestLibDoc

IMPLEMENT_DYNCREATE(CVTestLibDoc, CDocument)

BEGIN_MESSAGE_MAP(CVTestLibDoc, CDocument)
	ON_COMMAND(ID_ADDQUEST, &CVTestLibDoc::OnAddquest)
	ON_COMMAND(ID_ADDTEXT, &CVTestLibDoc::OnAddtext)

	ON_COMMAND(ID_FIRST, &CVTestLibDoc::OnFirst)
	ON_COMMAND(ID_LAST, &CVTestLibDoc::OnLast)
	ON_COMMAND(ID_NEXT, &CVTestLibDoc::OnNext)
	ON_COMMAND(ID_PREVIOUS, &CVTestLibDoc::OnPrevious)
	ON_UPDATE_COMMAND_UI(ID_FIRST, &CVTestLibDoc::OnUpdateFirst)
	ON_UPDATE_COMMAND_UI(ID_NEXT, &CVTestLibDoc::OnUpdateNext)
	ON_UPDATE_COMMAND_UI(ID_PREVIOUS, &CVTestLibDoc::OnUpdatePrevious)
	ON_UPDATE_COMMAND_UI(ID_LAST, &CVTestLibDoc::OnUpdateLast)

	ON_COMMAND(ID_QUEST_SLIDER, &CVTestLibDoc::OnQuestSlider)
	ON_UPDATE_COMMAND_UI(ID_QUEST_SLIDER, &CVTestLibDoc::OnUpdateQuestSlider)
	ON_COMMAND(ID_EDITQUEST, &CVTestLibDoc::OnEditquest)
	ON_COMMAND(ID_DELQUEST, &CVTestLibDoc::OnDelquest)
	ON_UPDATE_COMMAND_UI(ID_DELQUEST, &CVTestLibDoc::OnUpdateDelquest)
	ON_UPDATE_COMMAND_UI(ID_EDITQUEST, &CVTestLibDoc::OnUpdateEditquest)
	ON_COMMAND(ID_EDIT_TAG, &CVTestLibDoc::OnEditTag)
	ON_COMMAND(ID_QUEST_RANDOM, &CVTestLibDoc::OnQuestRandom)
	ON_UPDATE_COMMAND_UI(ID_QUEST_RANDOM, &CVTestLibDoc::OnUpdateQuestRandom)
	
	ON_COMMAND(ID_SHOWHIDE_ANS, &CVTestLibDoc::OnShowhideAns)
	ON_UPDATE_COMMAND_UI(ID_SHOWHIDE_ANS, &CVTestLibDoc::OnUpdateShowhideAns)
	ON_COMMAND(ID_SHOW_ALL, &CVTestLibDoc::OnShowAll)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ALL, &CVTestLibDoc::OnUpdateShowAll)
	ON_COMMAND(ID_SHOW_MARKED, &CVTestLibDoc::OnShowMarked)
	ON_UPDATE_COMMAND_UI(ID_SHOW_MARKED, &CVTestLibDoc::OnUpdateShowMarked)
	ON_COMMAND(ID_SHOW_FILTER, &CVTestLibDoc::OnShowFilter)
	ON_UPDATE_COMMAND_UI(ID_SHOW_FILTER, &CVTestLibDoc::OnUpdateShowFilter)
	ON_COMMAND(ID_QUEST_MARK, &CVTestLibDoc::OnQuestMark)
	ON_COMMAND(ID_QUEST_MARK_ALL, &CVTestLibDoc::OnQuestMarkAll)
	ON_UPDATE_COMMAND_UI(ID_QUEST_MARK, &CVTestLibDoc::OnUpdateQuestMark)
	ON_COMMAND(ID_QUEST_QUICKTEST, &CVTestLibDoc::OnQuestQuicktest)
	ON_COMMAND(ID_QUEST_UNMARK_ALL, &CVTestLibDoc::OnQuestUnmarkAll)
	ON_UPDATE_COMMAND_UI(ID_QUEST_MARKEDCOUNT, &CVTestLibDoc::OnUpdateQuestMarkedcount)
	ON_COMMAND(ID_TEST_NEW_TEST, &CVTestLibDoc::OnTestNewTest)
//	ON_COMMAND(ID_EDIT_FIND, &CVTestLibDoc::OnEditFind)
ON_COMMAND(ID_EDIT_RENAME_TAG, &CVTestLibDoc::OnEditRenameTag)
ON_COMMAND(ID_TEST_MARK_RANDOM, &CVTestLibDoc::OnTestMarkRandom)
END_MESSAGE_MAP()


// CVTestLibDoc construction/destruction

CVTestLibDoc::CVTestLibDoc()
{
	Gdiplus::Font f(L"Times New Roman",12, FontStyleRegular);
	m_Font = f.Clone();

	m_currentQuest=-1;
	m_bShowAns=true;
	pView=NULL;

	m_Mode=0;
	m_wndTags=NULL;
}

CVTestLibDoc::~CVTestLibDoc()
{
	delete m_Font;
	for (int i=0;i<m_QuestArray.GetSize();i++)
		delete m_QuestArray[i];
}

void CVTestLibDoc::ClearAll()
{
	for (int i=0;i<m_QuestArray.GetSize();i++)
		delete m_QuestArray[i];
	m_QuestArray.RemoveAll();
	m_TagArray.Free();
	m_Mode=0;
	m_currentQuest=-1;
	m_bShowAns=true;
	if (m_wndTags!=NULL) m_wndTags->m_Tree.DeleteAllItems();

	m_testStructArr.Dispose();
}

BOOL CVTestLibDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	ClearAll();

	return TRUE;
}


BOOL CVTestLibDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	ClearAll();
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	for (int i = 0; i < m_QuestArray.GetSize(); i++) {
		CQuestItemABCD* q = (CQuestItemABCD*)m_QuestArray[i];
		CStringArray arr;
		m_TagArray.GetItemsInTag(arr,3);
		CString str = L"INSERT INTO quest (type, owner content, diff_rate) VALUES ('multi-choice',2,'" + q->m_strQuest + "'," + arr[0] + ")";
		AfxMessageBox(str);
		break;
	}

	return TRUE;
}


// CVTestLibDoc serialization

void CVTestLibDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_QuestArray.GetSize();
		for (int i=0;i<m_QuestArray.GetSize();i++)
		{
			ar << m_QuestArray[i]->m_Type;
			m_QuestArray[i]->Serialize(ar);
		}
		m_TagArray.Serialize(ar);
		m_testStructArr.Serialize(ar);
	}
	else
	{
		m_cIndex=0;
		int count;
		ar >> count;
		int type;
		for (int i=0;i<count;i++)
		{
			ar >> type;
			switch (type)
			{
			case ItemText:
			{
				CTextItem* it=new CTextItem();
				it->Serialize(ar);
				m_QuestArray.Add(it);
				it->m_Font=m_Font;
				break;
			}
			case ItemQuestABCD:
			{
				CQuestItemABCD* it=new CQuestItemABCD();
				it->Serialize(ar);
				m_QuestArray.Add(it);
				it->m_Font=m_Font;
				break;
			}
			}
		}
		m_TagArray.Serialize(ar);
		m_testStructArr.Serialize(ar);
		if (m_wndTags) m_wndTags->RefreshItem();
		RefreshCurrentQuestArray();
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CVTestLibDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CVTestLibDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CVTestLibDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CVTestLibDoc diagnostics

#ifdef _DEBUG
void CVTestLibDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVTestLibDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CVTestLibDoc commands


void CVTestLibDoc::OnAddquest()
{
	CDlgAddQuestion dlg;
	if (dlg.DoModal()==IDOK)
	{
		CQuestItemABCD* item=new CQuestItemABCD();
		int after;
		/*if (after==-1) */after=m_QuestArray.GetSize();
		item->m_strQuest=dlg.m_Question.m_Text;
		item->m_alt.A=dlg.m_AnsA.m_Text;
		item->m_alt.B=dlg.m_AnsB.m_Text;
		item->m_alt.C=dlg.m_AnsC.m_Text;
		item->m_alt.D=dlg.m_AnsD.m_Text;
		item->m_strHint=dlg.m_Hint.m_Text;
		item->m_answer=dlg.ans;

		item->m_Font=m_Font;
		m_QuestArray.InsertAt(after,item);
		m_TagArray.AddItem();
		m_wndTags->RefreshChildItem();
		
		m_Mode=0;
		RefreshCurrentQuestArray();
		SetCurrentQuest(after);

		pView->RefreshScrollBar();
		SetModifiedFlag();
	}
}

void CVTestLibDoc::OnAddtext()
{
	CDlgAddText dlg;
	if (dlg.DoModal()==IDOK)
	{
		CTextItem* it=new CTextItem();
		int after;
		after=m_QuestArray.GetSize();
		it->m_strText=dlg.m_Text.m_Text;
		it->m_Font=m_Font;
		m_QuestArray.InsertAt(after,it);
		m_TagArray.AddItem();
		m_wndTags->RefreshChildItem();

		m_Mode=0;
		RefreshCurrentQuestArray();
		SetCurrentQuest(after);

		pView->RefreshScrollBar();
		SetModifiedFlag();
	}
}


void CVTestLibDoc::OnFirst()
{
	SetCurrentQuest(0);
}


void CVTestLibDoc::OnLast()
{
	SetCurrentQuest(m_cQuestArr.GetSize()-1);
}


void CVTestLibDoc::OnNext()
{
	if (m_currentQuest<m_cQuestArr.GetSize()-1) SetCurrentQuest(m_currentQuest+1);
}


void CVTestLibDoc::OnPrevious()
{
	if (m_currentQuest>0) SetCurrentQuest(m_currentQuest-1);
}


void CVTestLibDoc::OnUpdateFirst(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_currentQuest>0);
}


void CVTestLibDoc::OnUpdateNext(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_currentQuest!=m_cQuestArr.GetSize()-1);
}


void CVTestLibDoc::OnUpdatePrevious(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_currentQuest>0);
}


void CVTestLibDoc::OnUpdateLast(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_currentQuest!=m_cQuestArr.GetSize()-1);
}

void CVTestLibDoc::SetCurrentQuest(int i)
{
	CItemBase* cIt=GetCurrentItem();
	if (cIt!=NULL) cIt->DisposeBmp();
	if (m_cQuestArr.GetSize()==0) { m_currentQuest=-1; pView->RefreshScrollBar(); return; }
	m_currentQuest = i;
	for (int i=0;i<m_QuestArray.GetSize();i++) if (m_cQuestArr[m_currentQuest]==m_QuestArray[i]) { m_cIndex=i; break; }
	m_sliderQuest->SetRange(0,m_cQuestArr.GetSize()-1);
	m_sliderQuest->SetPos(i);
	//m_labelQuestPos->SetText(IntToString(i+1) + L" // " + IntToString(m_cQuestArr.GetSize()));
	if (m_cQuestArr[m_currentQuest]->m_Type==ItemQuestABCD)
	{
		((CQuestItemABCD*)m_cQuestArr[m_currentQuest])->m_Mode=(m_bShowAns ? QuestMode::ShowAnswer : QuestMode::UserAnswer);
		((CQuestItemABCD*)m_cQuestArr[m_currentQuest])->m_bShowHint=m_bShowAns;
		((CQuestItemABCD*)m_cQuestArr[m_currentQuest])->m_userAns=0;
		((CQuestItemABCD*)m_cQuestArr[m_currentQuest])->m_nIndex=0;
	}

	GetCurrentItem()->ReDrawBmp(pView->m_Width);

	pView->RefreshScrollBar();
}


void CVTestLibDoc::OnQuestSlider()
{
	SetCurrentQuest(m_sliderQuest->GetPos());
}


void CVTestLibDoc::OnUpdateQuestSlider(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_cQuestArr.GetSize()!=0);
	if (m_QuestArray.GetSize()==0)
	{
		m_sliderQuest->SetRange(1,3);
		m_sliderQuest->SetPos(2);
	}
}

CItemBase* CVTestLibDoc::GetCurrentItem()
{
	if (m_currentQuest==-1) return NULL;
	if (m_currentQuest>=m_cQuestArr.GetSize()) return NULL;
	return m_cQuestArr[m_currentQuest];
}

void CVTestLibDoc::OnEditquest()
{
	if (m_cQuestArr[m_currentQuest]->m_Type==ItemText)
	{
		CTextItem* it=(CTextItem*)m_cQuestArr[m_currentQuest];

		CDlgAddText dlg;
		dlg.m_Text.m_Text=it->m_strText;
		if (dlg.DoModal()==IDOK)
		{
			it->m_strText=dlg.m_Text.m_Text;
			it->DisposeBmp();
		}
	}
	if (m_cQuestArr[m_currentQuest]->m_Type==ItemQuestABCD)
	{
		CQuestItemABCD* item=(CQuestItemABCD*)m_cQuestArr[m_currentQuest];

		CDlgAddQuestion dlg;
		dlg.m_Question.m_Text=item->m_strQuest;
		dlg.m_AnsA.m_Text=item->m_alt.A;
		dlg.m_AnsB.m_Text=item->m_alt.B;
		dlg.m_AnsC.m_Text=item->m_alt.C;
		dlg.m_AnsD.m_Text=item->m_alt.D;
		dlg.m_Hint.m_Text=item->m_strHint;
		dlg.ans=item->m_answer;

		if (dlg.DoModal()==IDOK)
		{
			SetModifiedFlag();
			item->m_strQuest=dlg.m_Question.m_Text;
			item->m_alt.A=dlg.m_AnsA.m_Text;
			item->m_alt.B=dlg.m_AnsB.m_Text;
			item->m_alt.C=dlg.m_AnsC.m_Text;
			item->m_alt.D=dlg.m_AnsD.m_Text;
			item->m_strHint=dlg.m_Hint.m_Text;
			item->m_answer=dlg.ans;
			item->DisposeBmp();
		}
	}
	SetModifiedFlag(); pView->RefreshScrollBar();
}


void CVTestLibDoc::OnDelquest()
{
	if (AfxMessageBox(L"Bạn muốn xóa câu hỏi này ?",MB_ICONASTERISK | MB_YESNO))
	{
		delete m_QuestArray[m_cIndex];
		m_QuestArray.RemoveAt(m_cIndex);
		m_cQuestArr.RemoveAt(m_currentQuest);
		m_TagArray.RemoveAt(m_cIndex);
		if (m_currentQuest==m_cQuestArr.GetSize()) SetCurrentQuest(m_currentQuest-1);
		else SetCurrentQuest(m_currentQuest);
		SetModifiedFlag();
		pView->RefreshScrollBar();
	}
}


void CVTestLibDoc::OnUpdateDelquest(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_QuestArray.GetSize()!=0);
}


void CVTestLibDoc::OnUpdateEditquest(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_QuestArray.GetSize()!=0);
}


void CVTestLibDoc::OnEditTag()
{

}

void CVTestLibDoc::RefreshCurrentQuestArray()
{
	if (!pView) return;
	CItemBase* cIt=GetCurrentItem();
	m_cQuestArr.RemoveAll();
	if (m_Mode==0)
	{
		for (int i=0;i<m_QuestArray.GetSize();i++) 
		{
			m_cQuestArr.Add(m_QuestArray[i]);
		}
	}
	else if (m_Mode==1)
	{
		for (int i=0;i<m_QuestArray.GetSize();i++) 
		{
			bool b=true;
			for (int j=0;j<m_TagArray.m_TagName.GetSize();j++)
			{
				HTREEITEM hItParent=m_wndTags->m_Tree.FindChildItem(TVI_ROOT,m_TagArray.m_TagName[j]);
				if (m_wndTags->m_Tree.GetCheck(hItParent)==2)
				{
					HTREEITEM hIt=m_wndTags->m_Tree.FindItem(hItParent,m_TagArray.m_Array[i]->m_arrTagItem[j]);
					CString str=m_wndTags->m_Tree.GetItemText(hIt);
					if (m_wndTags->m_Tree.GetCheck(hIt)==0) { b=false; break; }
				}
			}
			if (b) m_cQuestArr.Add(m_QuestArray[i]);
		}
	}
	else if (m_Mode==2)
	{
		for (int i=0;i<m_markedQuestArray.GetSize();i++)
			m_cQuestArr.Add(m_markedQuestArray[i]);
	}

	for (int i=0;i<m_cQuestArr.GetSize();i++)
		if (cIt==m_cQuestArr[i]) { SetCurrentQuest(i); return; }
	SetCurrentQuest(0);
}


void CVTestLibDoc::OnQuestRandom()
{
	int r=rand();
	while (r==m_currentQuest) r=rand();
	SetCurrentQuest(rand() % m_cQuestArr.GetSize());
}


void CVTestLibDoc::OnUpdateQuestRandom(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_cQuestArr.GetSize()>1);
}


void CVTestLibDoc::OnShowhideAns()
{
	m_bShowAns=!m_bShowAns;
	SetCurrentQuest(m_currentQuest);
}


void CVTestLibDoc::OnUpdateShowhideAns(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bShowAns);
}


void CVTestLibDoc::OnShowAll()
{
	m_Mode=0; RefreshCurrentQuestArray();
}
void CVTestLibDoc::OnUpdateShowAll(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Mode==0);
}
void CVTestLibDoc::OnShowMarked()
{
	m_Mode=2; RefreshCurrentQuestArray();
}
void CVTestLibDoc::OnUpdateShowMarked(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Mode==2);
}
void CVTestLibDoc::OnShowFilter()
{
	m_Mode=1; RefreshCurrentQuestArray();
}
void CVTestLibDoc::OnUpdateShowFilter(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_Mode==1);
}


void CVTestLibDoc::OnQuestMark()
{
	if (IsCurrentItemMarked())
	{
		for (int i=0;i<m_markedQuestArray.GetSize();i++)
			if (m_markedQuestArray[i]==GetCurrentItem()) { m_markedQuestArray.RemoveAt(i); break; }
		RefreshCurrentQuestArray();
	}
	else
	{
		m_markedQuestArray.Add(GetCurrentItem());
		pView->Draw();
	}
}
void CVTestLibDoc::OnUpdateQuestMark(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_currentQuest!=-1);
	pCmdUI->SetCheck(IsCurrentItemMarked());
}
void CVTestLibDoc::OnQuestMarkAll()
{
	for (int i=0;i<m_cQuestArr.GetSize();i++)
		if (!IsItemMarked(m_cQuestArr[i])) m_markedQuestArray.Add(m_cQuestArr[i]);
	pView->Draw();
}
void CVTestLibDoc::OnQuestUnmarkAll()
{
	for (int i=0;i<m_cQuestArr.GetSize();i++)
	{
		for (int j=0;j<m_markedQuestArray.GetSize();j++)
			if (m_cQuestArr[i]==m_markedQuestArray[j])
				m_markedQuestArray.RemoveAt(j);
	}
	pView->Draw();
}

void CVTestLibDoc::OnQuestQuicktest()
{
	CItemArray itArr; itArr.m_bDispose=false;
	CTestInfo tInfo;
	itArr.m_tInfo=&tInfo;
	for (int i=0;i<m_markedQuestArray.GetSize();i++) itArr.m_Array.Add(m_markedQuestArray[i]);

	if (m_markedQuestArray.GetSize()==0)
		AfxMessageBox(L"Cần đánh dấu các câu hỏi trước khi tạo đề thi",MB_OK | MB_ICONWARNING);
	else
	{
		tInfo.m_nTime=0;
		tInfo.m_strAuthor=L"VTestLib";

		CFile f; 
		f.Open(GetAppDirectory()+"\\tmp.vtestx",CFile::modeWrite | CFile::modeCreate);
		CArchive ar(&f,CArchive::store);
		tInfo.Serialize(ar);
		CTestHistoryArray th;
		th.Serialize(ar);
		itArr.Serialize(ar);
		ar.Close();
		f.Close();

		if (!ShellExecute(NULL, NULL, GetAppDirectory()+L"\\tmp.vtestx", NULL, NULL, SW_SHOW))
			AfxMessageBox(L"Có lỗi khi mở tập tin");
	}
}


void CVTestLibDoc::OnUpdateQuestMarkedcount(CCmdUI *pCmdUI)
{
	pCmdUI->SetText(IntToString(m_markedQuestArray.GetSize()));
}

void CVTestLibDoc::OnTestNewTest()
{
	CItemArray itArr; itArr.m_bDispose=false;
	CTestInfo tInfo;
	itArr.m_tInfo=&tInfo;
	for (int i=0;i<m_markedQuestArray.GetSize();i++) itArr.m_Array.Add(m_markedQuestArray[i]);

	if (m_markedQuestArray.GetSize()==0)
		AfxMessageBox(L"Cần đánh dấu các câu hỏi trước khi tạo đề thi",MB_OK | MB_ICONWARNING);
	else
	{
		CFileDialog dlgFile(FALSE, NULL , NULL, 
			OFN_OVERWRITEPROMPT | OFN_DONTADDTORECENT,
			L"Test Files (*.vtest)|*.vtest||", AfxGetMainWnd(), 0, FALSE);
		if (dlgFile.DoModal()==IDOK)
		{
			CString strPath=dlgFile.GetPathName();
			if (strPath.Right(6)!=L".vtest") strPath+=L".vtest";
			tInfo.m_nTime=0;
			tInfo.m_strAuthor=L"VTestLib";

			CFile f; 
			f.Open(strPath,CFile::modeWrite | CFile::modeCreate);
			CArchive ar(&f,CArchive::store);
			tInfo.Serialize(ar);
			itArr.Serialize(ar);
			ar.Close();
			f.Close();

			if (!ShellExecute(NULL, NULL, L"VTest.exe", strPath, NULL, SW_SHOW))
				AfxMessageBox(L"Có lỗi khi mở tập tin");
		}
	}
}

//void CVTestLibDoc::OnEditFind()
//{
//	
//}


void CVTestLibDoc::OnEditRenameTag()
{
	CDlgRenameTag dlg;
	dlg.m_tagName=&m_TagArray.m_TagName;
	if (dlg.DoModal()==IDOK)
	{
		for (int i=0;i<m_cQuestArr.GetSize();i++)
			m_TagArray.m_Array[this->GetItemIndexInQuestArray(i)]->m_arrTagItem[dlg.m_nTag]=dlg.m_strRename;
	}
}


void CVTestLibDoc::OnTestMarkRandom()
{
	CDlgMarkRandom dlg;
	if (dlg.DoModal()==IDOK)
	{
		CArray<CItemBase*, CItemBase*> arr;
		for (int i=0;i<m_cQuestArr.GetSize();i++)
			if (!IsItemMarked(m_cQuestArr[i]) && m_cQuestArr[i]->m_Type==ItemQuestABCD) arr.Add(m_cQuestArr[i]);
		if (dlg.m_Number>arr.GetSize()) AfxMessageBox(L"Không đủ số câu hỏi",MB_ICONWARNING);
		else
		{
			srand((unsigned)time(NULL));
			for (int k=0;k<dlg.m_Number;k++)
			{
				int i=rand() % (arr.GetSize());
				m_markedQuestArray.Add(arr[i]); arr.RemoveAt(i);
			}
		}
	}
}

int CVTestLibDoc::GetItemIndexInQuestArray( int cIndex )
{
	for (int i=0;i<m_QuestArray.GetSize();i++) 
		if (m_QuestArray[i]==m_cQuestArr[cIndex]) return i;
}
