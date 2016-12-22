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

// VTestDoc.cpp : implementation of the CVTestDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VTest.h"
#endif

#include "VTestDoc.h"
#include "VTestView.h"
#include "DlgProperties.h"

#include "DlgNewWizard.h"
#include "DlgPageSetup.h"
#include <propkey.h>
#include "DlgExportHTML.h"
#include "../lib/TestHistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CVTestView* pView;
extern Gdiplus::Font* m_Font;

// CVTestDoc

IMPLEMENT_DYNCREATE(CVTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CVTestDoc, CDocument)
	ON_COMMAND(ID_EDIT_ADD_QUEST_ABCD, &CVTestDoc::OnEditAddQuestABCD)
	ON_COMMAND(ID_FILE_PROPERTIES, &CVTestDoc::OnFileProperties)
	ON_COMMAND(ID_EDIT_DELETE, &CVTestDoc::OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, &CVTestDoc::OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_ADDTEXT, &CVTestDoc::OnEditAddtext)
	ON_COMMAND(ID_FILE_WIZARD, &CVTestDoc::OnFileWizard)
	ON_COMMAND(ID_ITEM_DOWN, &CVTestDoc::OnItemDown)
	ON_COMMAND(ID_ITEM_UP, &CVTestDoc::OnItemUp)
	ON_COMMAND(ID_EDIT_ADD_CONTAINER, &CVTestDoc::OnEditAddContainer)
	ON_COMMAND(ID_EDIT_EDIT, &CVTestDoc::OnEditEdit)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EDIT, &CVTestDoc::OnUpdateEditEdit)
	ON_COMMAND(ID_EDIT_ADD_QUEST_TRUE_FALSE, &CVTestDoc::OnEditAddQuestTrueFalse)
	ON_COMMAND(ID_EDIT_ADD_QUEST, &CVTestDoc::OnEditAddQuest)
	ON_COMMAND(ID_FILE_PAGE_SETUP, &CVTestDoc::OnFilePageSetup)
	ON_COMMAND(ID_FILE_RUN, &CVTestDoc::OnFileRun)
	ON_COMMAND(ID_VIEW_SHOWANSWER, &CVTestDoc::OnViewShowanswer)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWANSWER, &CVTestDoc::OnUpdateViewShowanswer)
	ON_COMMAND(ID_VIEW_SHOWHINT, &CVTestDoc::OnViewShowhint)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWHINT, &CVTestDoc::OnUpdateViewShowhint)
	ON_COMMAND(ID_FILE_NEW, &CVTestDoc::OnFileNew)
	ON_COMMAND(ID_FILE_NEW_LEC, &CVTestDoc::OnFileNewLec)
	ON_COMMAND(ID_FILE_NEW_TEST, &CVTestDoc::OnFileNewTest)
	ON_COMMAND(ID_EXPORT_HTML, &CVTestDoc::OnExportHtml)
	ON_COMMAND(ID_HOME_TRON_DE_THI, &CVTestDoc::OnHomeTronDeThi)
	ON_COMMAND(ID_EXPORT_VTESTX, &CVTestDoc::OnExportVtestx)
END_MESSAGE_MAP()

// CVTestDoc construction/destruction

CVTestDoc::CVTestDoc()
{
	Gdiplus::Font f(L"Times New Roman",12, FontStyleRegular);
	m_Font = f.Clone();

	m_Items.m_Width=PAGE_WIDTH;
	m_Items.m_Height=0;
	m_Items.m_Font=m_Font;

	m_nMarginLeft=0;
	m_drawnItem=-1;

	m_bShowAns=true;
	m_bShowHint=true;

	DWORD u=WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN;
}

CVTestDoc::~CVTestDoc()
{
	delete m_Font;
}

BOOL CVTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_tInfo.m_strTitle=L"<NHẬP TÊN ĐỀ THI>";
	m_tInfo.m_strSubject=L"<Nhập môn học>";
	m_tInfo.m_nTime=90;
	//OnFileProperties();

	//CEquationEditDlg dlg; dlg.DoModal();
	m_Items.DeleteAllItems();

	//m_Items.AddText(L"[center][b]<Ten_De_Thi>[\\b]\r\n[center]Môn : <Mon_Thi>\r\n[center]Thời gian : <Thoi_Gian> phút");
	//m_Items.AddQuestionABCD(L"Câu hỏi 1",L"",L"",L"",L"",L"",0);

	ReCalcHeight();

	SetModifiedFlag(TRUE);
	//m_QFont=new Font(L"Verdana",10,FontStyleRegular);

	/*AddQuestion(L"Một vật rắn đang quay quanh một trục cố định xuyên qua vật. Các điểm trên vật rắn (không thuộc trục quay)",
		L"ở cùng một thời điểm, không cùng gia tốc góc",
		L"quay được những góc không bằng nhau trong cùng một khoảng thời gian",
		L"ở cùng một thời điểm, có cùng tốc độ góc",
		L"ở cùng một thời điểm, có cùng vận tốc dài", L"");

	AddQuestion(L"Ban đầu một vận động viên trượt băng nghệ thuật hai tay dang rộng đang thực hiện động tác quay quanh trục thẳng đứng đi qua trọng tâm người đó. Sau đó vận động viên khép tay lại thì chuyển động quay sẽ",
		L"dừng lại ngay", L"quay nhanh hơn", L"quay chậm lại", L"không thay đổi", L"");

	AddQuestion(L"Hai dao động điều hòa cùng phương, cùng tần số, có các phương trình dao động là $x_1=3cos(\\wt-\\p/4)$ và $x_2=4cos(\\wt+\\p/4)$(cm). Biên độ dao động tổng hợp của hai dao động trên là",L"5 cm",L"12 cm",L"7 cm",L"1 cm",L"");

	AddQuestion(L"Chiếu bức xạ có bước sóng $\l=0,552\mm$ với công suất P = 1,2W vào catot của một tế bào quang điện, dòng quang điện bão hòa có cường độ Ibh = 2mA. Tính hiệu suất lượng tử của hiện tượng quang điện.\r\nCho h = 6,625.10-34Js , $c=3.10^8$m/s, e = 1,6.10-19C.",
		L"0,37%",L"0,425%",L"0,55%",L"0,65%",L"");

	AddQuestion(L"Con lắc lò xo gồm vật nặng treo dưới lò xo dài, có chu kỳ dao động là T. Nếu lò xo bị cắt bớt một nửa thì chu kỳ dao động của con lắc mới là:",
		L"$T/2$",L"2T",L"T",L"$T/sqrt(2)$",L"");*/
	m_statusText->SetText(L"Sẵn sàng");

	

	return TRUE;
}




// CVTestDoc serialization

void CVTestDoc::Serialize(CArchive& ar)
{
	m_tInfo.Serialize(ar);
	m_Items.Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
		m_Items.ResetIndex();
		m_drawnItem=0;
		m_statusText->SetText(L"Đang nạp file ...");
		m_prog->SetVisible(TRUE);
		m_statusBar->RecalcLayout();
		m_prog->SetRange(0,m_Items.GetSize());
		for (int i=0;i<m_Items.GetSize();i++) { m_Items.RedrawItem(m_Items[i]); m_prog->SetPos(i); AfxGetMainWnd()->Invalidate(); }
		m_prog->SetVisible(FALSE);
		m_statusBar->RecalcLayout();
		//m_prog->SetVisible(FALSE);
		m_statusText->SetText(L"Sẵn sàng");
		ReCalcHeight();
	}
}

void CVTestDoc::OnExportVtestx()
{
	CFileDialog dlgFile(FALSE, NULL , NULL, 
		OFN_DONTADDTORECENT | OFN_OVERWRITEPROMPT,
		L"VTestViewer Files|*.vtestx||", 
		AfxGetMainWnd(), 0);

	if (dlgFile.DoModal()==IDOK)
	{
		CString strPath=dlgFile.GetPathName();
		if (strPath.Right(7)!=L".vtestx") strPath=strPath+L".vtestx";
		
		CFile f; 
		f.Open(strPath,CFile::modeWrite | CFile::modeCreate);
		CArchive ar(&f,CArchive::store);

		m_tInfo.Serialize(ar);
		CTestHistoryArray ha;
		ha.Serialize(ar);
		m_Items.Serialize(ar);
		
		ar.Close();
		f.Close();
	}
}



void CVTestDoc::OnIdleRedrawItem()
{
// 	if (m_drawnItem==-1) return;
// 	if (m_drawnItem==m_Items.GetSize()) 
// 	{
// 		m_drawnItem=-1;
// 		ReCalcHeight();
// 		return;
// 	}
// 	m_Items.RedrawItem(m_Items[m_drawnItem]); pView->Draw(); m_drawnItem++;
}

UINT CVTestDoc::ThreadRedrawItem(LPVOID)
{
	for (int i=0;i<m_Items.GetSize();i++) m_Items.RedrawItem(m_Items[i]);
	ReCalcHeight();
	return 0;
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CVTestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CVTestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CVTestDoc::SetSearchContent(const CString& value)
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

// CVTestDoc diagnostics

#ifdef _DEBUG
void CVTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CVTestDoc commands
void CVTestDoc::OnEditAddQuestABCD()
{
	CQuestItemABCD* i=new CQuestItemABCD();
	m_Items.m_Array.Add(i);
	i->m_Font=m_Font;
	i->Edit(pView);
	m_Items.RedrawItem(i);
	SetModifiedFlag(TRUE);
	ReCalcHeight();
}

void CVTestDoc::OnEditAddQuestTrueFalse()
{
	m_Items.AddItem(ItemQuestTrueFalse,-1,true);
	SetModifiedFlag(TRUE);
	ReCalcHeight();
}

void CVTestDoc::OnEditAddtext()
{
	m_Items.AddItem(ItemText,-1,true);
	SetModifiedFlag(TRUE);
	ReCalcHeight();
}


void CVTestDoc::OnEditAddContainer()
{
	m_Items.AddItem(ItemContainer,-1,true);
	SetModifiedFlag(TRUE);
	ReCalcHeight();
}


void CVTestDoc::OnEditAddQuest()
{
	m_Items.AddItem(ItemQuest,-1,true);
	SetModifiedFlag(TRUE);
	ReCalcHeight();
}


void CVTestDoc::OnFileProperties()
{
	CDlgProperties dlg;
	dlg.m_tInfo=m_tInfo;
	if (dlg.DoModal()==IDOK)
	{
		SetModifiedFlag();
		m_tInfo=dlg.m_tInfo;
	}
}

void CVTestDoc::ReCalcHeight()
{
	int h=m_Items.m_Height;
	m_Items.ReCalcHeight();
	m_Items.RecalcAllContainerDrawHeight();
	if (h!=m_Items.m_Height) { pView->RefreshScrollBar(); }
}

void CVTestDoc::OnEditDelete()
{
	if (AfxGetApp()->DoMessageBox(StringFromResource(IDS_CONFIRM_DELETE), MB_YESNO | MB_ICONQUESTION,0)==IDYES)
	{
		SetModifiedFlag();
		m_Items.DeleteItem(m_Items.m_hlItem);
		m_Items.m_hlItem=-1;
		m_Items.ReCalcHeight();
		pView->RefreshScrollBar();
		pView->Draw();
	}
}

void CVTestDoc::OnUpdateEditDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Items.m_hlItem!=-1);
}

void CVTestDoc::OnCloseDocument()
{
	CDocument::OnCloseDocument();
}

BOOL CVTestDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	while (m_Items.GetSize()!=0) m_Items.DeleteItem(0);

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	SetModifiedFlag(FALSE);

	return TRUE;
}

void CVTestDoc::OnFileWizard()
{
// 	CDlgNewWizard dlg;
// 	if (dlg.DoModal()==IDOK)
// 	{
// 		CString s=dlg.m_strText;
// 
// 		int pStart=0;
// 		int pEndPrev=0;
// 		int pStartNext=0;
// 		int p1,p2,p3,p4,p5;
// 
// 		m_Items.AddText(s.Left(pStart));
// 
// 		do 
// 		{
// 			pStart=s.Find(L"\r\nCâu",pEndPrev); if (pStart==-1) pStart=s.GetLength();
// 			if (pStart!=pEndPrev) m_Items.AddText(s.Mid(pEndPrev,pStart-pEndPrev));
// 			int pStartNext=s.Find(L"\r\nCâu",pStart+1); if (pStartNext==-1) pStartNext=s.GetLength();
// 
// 			p1=s.Find(L"\r\nA.",pStart); if (p1==-1 || p1>pStartNext) p1=s.Find(L"\tA.",pStart); else p1+=2; if (p1==-1 || p1>pStartNext) p1=pStart; else p1+=1;
// 			p2=s.Find(L"\r\nB.",p1); if (p2==-1 || p2>pStartNext) p2=s.Find(L"\tB.",p1); else p2+=2; if (p2==-1 || p2>pStartNext) p2=p1; else p2+=1;
// 			p3=s.Find(L"\r\nC.",p2); if (p3==-1 || p3>pStartNext) p3=s.Find(L"\tC.",p2); else p3+=2; if (p3==-1 || p3>pStartNext) p3=p2; else p3+=1;
// 			p4=s.Find(L"\r\nD.",p3); if (p4==-1 || p4>pStartNext) p4=s.Find(L"\tD.",p3); else p4+=2; if (p4==-1 || p4>pStartNext) p4=p3; else p4+=1;
// 			p5=s.Find(L"\r\n",p4); if (p5==-1) p5=s.GetLength();
// 
// 			CString strQuestion=s.Mid(pStart,p1-pStart); strQuestion.Trim(); if (strQuestion.Left(3)==L"Câu") { int p=strQuestion.Find(L":"); strQuestion=strQuestion.Right(strQuestion.GetLength()-p-1); strQuestion.Trim(); }
// 			CString strA=s.Mid(p1+2,p2-p1-2); strA.Trim();
// 			CString strB=s.Mid(p2+2,p3-p2-2); strB.Trim();
// 			CString strC=s.Mid(p3+2,p4-p3-2); strC.Trim();
// 			CString strD=s.Mid(p4+2,p5-p4-2); strD.Trim();
// 
// 			m_Items.AddQuestionABCD(strQuestion,strA,strB,strC,strD,L"",0);
// 
// 			pEndPrev=p5;
// 
// 		} while ((s.Mid(p5,s.GetLength()-p5)).Trim()!=L"");
// 	}
// 	ReCalcHeight();
// 	m_Items.ResetIndex();
}

void CVTestDoc::OnItemDown()
{
	CItemBase* item=m_Items[m_Items.m_hlItem];
	m_Items.m_Array[m_Items.m_hlItem]=m_Items[m_Items.m_hlItem+1];
	m_Items.m_Array[m_Items.m_hlItem+1]=item;
	m_Items.ResetIndex();
	m_Items.m_hlItem=m_Items.m_hlItem+1;
	pView->Draw();
}

void CVTestDoc::OnItemUp()
{
	CItemBase* item=m_Items[m_Items.m_hlItem];
	m_Items.m_Array[m_Items.m_hlItem]=m_Items[m_Items.m_hlItem-1];
	m_Items.m_Array[m_Items.m_hlItem-1]=item;
	m_Items.ResetIndex();
	m_Items.m_hlItem=m_Items.m_hlItem-1;
	pView->Draw();
}

void CVTestDoc::OnEditEdit()
{
	SetModifiedFlag();
	int i=m_Items.m_hlItem;
	m_Items[i]->Edit(pView);
	m_Items.RedrawItem(m_Items[i]);
	ReCalcHeight();
	pView->Draw();
}

void CVTestDoc::OnUpdateEditEdit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_Items.m_hlItem!=-1);
}



void CVTestDoc::OnFilePageSetup()
{
	CDlgPageSetup dlg;
	dlg.m_nMarginLeft=m_nMarginLeft;
	if (dlg.DoModal()==IDOK)
	{
		m_nMarginLeft=dlg.m_nMarginLeft;
	}
}


void CVTestDoc::OnFileRun()
{
	CString strPath=GetAppDirectory()+L"\\temp.vtestx";

	CFile f; 
	f.Open(strPath,CFile::modeWrite | CFile::modeCreate);
	CArchive ar(&f,CArchive::store);

	m_tInfo.Serialize(ar);
	CTestHistoryArray ha;
	ha.Serialize(ar);
	m_Items.Serialize(ar);

	ar.Close();
	f.Close();
// 	CDlgConfirmTest dlgC;
// 	dlgC.m_tInfo=&m_tInfo;
// 
// 	if (dlgC.DoModal()==IDOK)
// 	{
// 		CDlgTest dlg;
// 		dlg.m_tInfo=m_tInfo;
// 		dlg.m_nRemainingTime=m_tInfo.m_nTime*60;
// 		dlg.m_nView=dlgC.m_nViewStyle;
// 		bool bAdding=true;
// 		CContainerItemEnd* pC;
// 		for (int i=0;i<m_Items.GetSize();i++) 
// 		{
// 			if (bAdding && dlgC.m_nStdType!=-1 && m_Items[i]->m_Type==ItemContainer)
// 			{
// 				if (((CContainerItemStart*)m_Items[i])->m_nStdType!=dlgC.m_nStdType && 
// 					((CContainerItemStart*)m_Items[i])->m_nStdType!=-1)
// 				{
// 					bAdding=false;
// 					pC=((CContainerItemStart*)m_Items[i])->m_itEnd;
// 				}
// 			}
// 
// 			if (bAdding) dlg.m_Items.m_Array.Add(m_Items[i]);
// 
// 			if (!bAdding && m_Items[i]->m_Type==ItemContainerEnd)
// 			{
// 				CContainerItemStart* pS=((CContainerItemEnd*)m_Items[i])->m_itStart;
// 				if (m_Items[i]==pC) bAdding=true;
// 			}
// 		}
// 		dlg.m_bShowAnswerIm=dlgC.m_bShowAnswerIm;
// 		dlg.DoModal();
// 
// 		m_Items.SetQuestMode(ShowAnswer);
// 
// 		for (int i=0;i<m_Items.GetSize();i++)
// 		{
// 			if (m_Items[i]->m_Type==ItemQuestABCD) 
// 			{
// 				((CQuestItemABCD*)m_Items[i])->m_userAns=0;
// 				((CQuestItemABCD*)m_Items[i])->m_alt.bMarkA=0;
// 				((CQuestItemABCD*)m_Items[i])->m_alt.bMarkB=0;
// 				((CQuestItemABCD*)m_Items[i])->m_alt.bMarkC=0;
// 				((CQuestItemABCD*)m_Items[i])->m_alt.bMarkD=0;
// 			}
// 			else if (m_Items[i]->m_Type==ItemQuestTrueFalse)
// 			{
// 				((CQuestItemTrueFalse*)m_Items[i])->m_userAns.RemoveAll();
// 			}
// 		}
// 		m_bShowAns=!m_bShowAns; OnViewShowanswer();
// 		m_bShowHint=!m_bShowHint; OnViewShowhint();
// 	}
	ShellExecute(NULL, NULL, strPath, NULL, NULL, SW_SHOWNORMAL);
}


void CVTestDoc::OnViewShowanswer()
{
	m_bShowAns=!m_bShowAns;
	for (int i=0;i<m_Items.GetSize();i++) 
		if ((IsQuestType(m_Items[i]->m_Type))) ((CQuestItemBase*)m_Items[i])->m_Mode=m_bShowAns ? QuestMode::ShowAnswer : QuestMode::NoAnswer; 
	pView->Draw();
}


void CVTestDoc::OnUpdateViewShowanswer(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bShowAns);
}


void CVTestDoc::OnViewShowhint()
{
	m_bShowHint=!m_bShowHint;
	for (int i=0;i<m_Items.GetSize();i++) 
		if ((IsQuestType(m_Items[i]->m_Type))) ((CQuestItemBase*)m_Items[i])->m_bShowHint=m_bShowHint;
	pView->Draw();
	m_Items.ReCalcHeight();
	pView->RefreshScrollBar();
}


void CVTestDoc::OnUpdateViewShowhint(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bShowHint);
}


void CVTestDoc::OnFileNew()
{
	// TODO: Add your command handler code here
}


void CVTestDoc::OnFileNewLec()
{
	OnNewDocument();
}


void CVTestDoc::OnFileNewTest()
{
	OnNewDocument();
}


void CVTestDoc::OnExportHtml()
{
	CDlgExportHTML dlg;
	if (dlg.DoModal()==IDOK)
	{
		CopyFolder(GetAppDirectory()+"\\templates\\"+dlg.m_strTemplate,dlg.m_strPath,dlg.m_strFolderName);
		if (dlg.m_strPath.Right(1) != "\\")
			dlg.m_strPath += "\\";
		CString strPath = dlg.m_strPath + dlg.m_strFolderName + L"\\";
		CreateDirectory(strPath+L"data\\image",NULL);
		//  	HANDLE hFile = CreateFile( TEXT(".\\tmp\\export.html"),
		//  		GENERIC_WRITE,
		//  		FILE_SHARE_WRITE,
		//  		NULL,
		//  		OPEN_ALWAYS,
		//  		0,
		//  		NULL );

		FILE *fStream;
		errno_t e=_tfopen_s(&fStream,strPath + L"data\\data.js",L"wt,ccs=UNICODE");
		if (e!=0) return;
		CStdioFile f(fStream); 
		int imgIndex=0;
		//BOOL b=f.Open(L".\\tmp\\export.html",CStdioFile::modeWrite);
		f.WriteString(L"var textArr = new Array();\n");
		f.WriteString(L"var itType = new Array();\n");
		f.WriteString(L"var choices = new Array();\n");
		f.WriteString(L"var hint = new Array();\n");
		f.WriteString(L"var answers = new Array();\n");
		f.WriteString(L"var response = new Array();\n");
		f.WriteString(L"var hint = new Array();\n");
		f.WriteString(L"var modeShowAnsIm = true;\n");

		f.WriteString(L"var strTitle = \"" + m_tInfo.m_strTitle + "\";\n");
		f.WriteString(L"var strSubject = \"" + m_tInfo.m_strSubject + "\";\n");
		f.WriteString(L"var nTime = \"" + IntToString(m_tInfo.m_nTime) + "\";\n");
		f.WriteString(L"var otherInfo = \"" + m_tInfo.m_strOtherInfo + "\";\n\n");

		f.WriteString(L"\
			var typeText=1;\n\
			var typeABCD=2;\n\
			var typeContStart=3;\n\
			var typeQuest=4;");

		
		for (int i=0;i<m_Items.GetSize();i++)
		{
			if (m_Items[i]->m_Type==ItemText)
			{
				CTextItem* t=((CTextItem*)m_Items[i]);
				CString str=t->m_strText;
				//t->m_strText=m_Items.ReplaceString(t->m_strText);
				m_Items[i]->WriteScriptData(f,strPath+L"data\\image\\",IntToString(i),imgIndex);
				t->m_strText=str;
			}
			else
				m_Items[i]->WriteScriptData(f,strPath+L"data\\image\\",IntToString(i),imgIndex);
		}
		f.Flush();
		f.Close();
		ShellExecute(NULL, NULL, strPath+L"index.htm", NULL, NULL, SW_SHOWNORMAL);
	}
}


void CVTestDoc::OnHomeTronDeThi()
{
	srand((unsigned)time(NULL));

	for (int i=0;i<m_Items.m_Array.GetSize();i++)
	{
		if (m_Items.m_Array[i]->m_Type==ItemQuestABCD)
		{
			CArray<int,int> arr;
			while (m_Items.m_Array.GetSize()>i && m_Items.m_Array[i]->m_Type==ItemQuestABCD) { arr.Add(i); i++; }

			for (int i=0;i<arr.GetSize();i++)
			{
				int i1=arr[i];
				int i2=arr[rand()%arr.GetSize()];

				CItemBase* tg=m_Items.m_Array[i1];
				m_Items.m_Array[i1]=m_Items.m_Array[i2];
				m_Items.m_Array[i2]=tg;
			}
		}
	}

	m_Items.ResetIndex();
	pView->Draw();
}

