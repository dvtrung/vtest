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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VTestLib.h"

#include "MainFrm.h"
#include "VTestLibDoc.h"
#include "DlgMarkStruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_VIEW_EXPLORER_PANE, &CMainFrame::OnViewExplorerPane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EXPLORER_PANE, &CMainFrame::OnUpdateViewExplorerPane)
	ON_COMMAND(ID_EDIT_FIND, &CMainFrame::OnEditFind)
	ON_COMMAND(ID_TEST_MARK_STRUCT, &CMainFrame::OnTestMarkStruct)
	ON_COMMAND(ID_VIEW_LANG_ENG, &CMainFrame::OnViewLangEng)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LANG_ENG, &CMainFrame::OnUpdateViewLangEng)
	ON_COMMAND(ID_VIEW_LANG_VIE, &CMainFrame::OnViewLangVie)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LANG_VIE, &CMainFrame::OnUpdateViewLangVie)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	POSITION pos=AfxGetApp()->GetFirstDocTemplatePosition();
	CDocTemplate* docTemp=AfxGetApp()->GetNextDocTemplate(pos);
	POSITION pos2=docTemp->GetFirstDocPosition();
	m_pDoc=(CVTestLibDoc*)docTemp->GetNextDoc(pos2);

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Load menu item image (not placed on any standard toolbars):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);
	CMFCToolBar::AddToolBarForImageCollection(IDR_EDIT_SMALL, theApp.m_bHiColorIcons ? IDR_EDIT_SMALL : 0);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndTags.EnableDocking(CBRS_ALIGN_ANY);

// 	m_wndNavigatePane.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
// 	m_wndNavigatePane.EnableGripper(0);
// 	m_wndNavigatePane.EnableAutohideAll()

	//DockPane(&m_wndNavigatePane);
	
	m_wndTags.m_tagArray=m_pDoc->GetTagArray();
	m_pDoc->m_wndTags=&m_wndTags;
	
 	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	m_wndTags.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndFileView.ShowPane(FALSE,FALSE,FALSE);

	m_pDoc->m_sliderQuest=(CMFCRibbonSlider*)m_wndRibbonBar.FindByID(ID_QUEST_SLIDER);
	m_pDoc->m_labelQuestPos=(CMFCRibbonLabel*)m_wndRibbonBar.GetCategory(0)->GetPanel(1)->GetElement(
		m_wndRibbonBar.GetCategory(0)->GetPanel(1)->GetIndex(m_pDoc->m_sliderQuest)+1);
	m_pDoc->m_sliderQuest->SetRange(1,3);
	m_pDoc->m_sliderQuest->SetPos(2);
	
	m_dlgFind=new CDlgFind();
	m_dlgFind->Create(CDlgFind::IDD,AfxGetMainWnd());
	m_dlgFind->m_pDoc=m_pDoc;

	//m_wndStatusBar.LoadFromResource(IDR_RIBBON_STATUS);
 
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1,StringFromResource(IDS_READY), TRUE), L"Status");
	//m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);
	
	
	m_wndStatusBar.AddElement(new CMFCRibbonButton(ID_PREVIOUS,L"<"),StringFromResource(IDS_PREVQUEST));
	m_wndStatusBar.AddElement(new CMFCRibbonEdit(ID_QUEST_SLIDER,30),StringFromResource(IDS_QUEST));
	m_wndStatusBar.AddElement(new CMFCRibbonButton(ID_NEXT,L">"),StringFromResource(IDS_NEXTQUEST));

	m_wndStatusBar.AddExtendedElement(new CMFCRibbonButton(ID_SHOW_ALL,StringFromResource(IDS_ALL)),StringFromResource(IDS_ALLQUEST));
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonButton(ID_SHOW_FILTER,StringFromResource(IDS_FILTERED)),StringFromResource(IDS_FILTERED));
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonButton(ID_SHOW_MARKED,StringFromResource(IDS_MARKED)),StringFromResource(IDS_MARKED));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Create class view
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndTags.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Class View window\n");
		return FALSE; // failed to create
	}

	// Create file view
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create File View window\n");
		return FALSE; // failed to create
	}

	//m_wndNavigatePane.Create(L"",this,CSize(200,50),FALSE,ID_NAVIGATE_PANE);

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	//HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	//HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	//m_wndTags.SetIcon(hClassViewIcon, FALSE);

}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnViewExplorerPane()
{
	m_wndTags.ShowPane(!m_wndTags.IsWindowVisible(),0,0);
	//m_wndFileView.ShowPane(!m_wndFileView.IsWindowVisible(),0,0);
}


void CMainFrame::OnUpdateViewExplorerPane(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndTags.IsWindowVisible());
}

void CMainFrame::OnFirst()
{
	
}


void CMainFrame::OnEditFind()
{
	m_dlgFind->ShowWindow(SW_SHOW);
}


void CMainFrame::OnTestMarkStruct()
{
	CDlgMarkStruct dlg;
	dlg.m_tagArray=m_pDoc->GetTagArray();
	dlg.m_QuestArray=&m_pDoc->m_QuestArray;
	dlg.m_testStructArr=&m_pDoc->m_testStructArr;
	dlg.DoModal();
	m_pDoc->SetCurrentQuest(m_pDoc->GetCurrentQuestIndex());
}

////////////////////////////////////////////////
// LANGUAGE
////////////////////////////////////////////////

void CMainFrame::SetLanguage(int lang)
{
	m_nLang=lang;

	CFile f; f.Open(GetAppDirectory()+L"\\lang.dat",CFile::modeWrite | CFile::modeCreate);
	CArchive ar(&f,CArchive::store);
	ar << m_nLang; ar.Close(); f.Close();

	AfxMessageBox(IDS_RESTART);
}

void CMainFrame::OnViewLangEng() { SetLanguage(0); }
void CMainFrame::OnUpdateViewLangEng(CCmdUI *pCmdUI) { pCmdUI->SetCheck(m_nLang==0); }
void CMainFrame::OnViewLangVie() { SetLanguage(1); }
void CMainFrame::OnUpdateViewLangVie(CCmdUI *pCmdUI) { pCmdUI->SetCheck(m_nLang==1); }
