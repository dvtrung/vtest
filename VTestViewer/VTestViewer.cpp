
// VTestViewer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "VTestViewer.h"
#include "MainFrm.h"

#include "VTestViewerDoc.h"
#include "VTestViewerView.h"

#include "../lib/TestInfo.h"
#include "DlgTest.h"
#include "DlgConfirmTest.h"
#include "DlgWait.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVTestViewerApp

BEGIN_MESSAGE_MAP(CVTestViewerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CVTestViewerApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CVTestViewerApp construction

CVTestViewerApp::CVTestViewerApp()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("VTest.VTestViewer.10"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CVTestViewerApp object

CVTestViewerApp theApp;


// CVTestViewerApp initialization

BOOL CVTestViewerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("VTest"));
	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	int m_lang = 0;
	CFile f; if (f.Open(GetAppDirectory()+L"\\lang.dat",CFile::modeRead)){
		CArchive ar(&f,CArchive::Mode::load);
		ar >> m_lang; ar.Close(); f.Close();
	}

	if (m_lang == 0) {
		::SetThreadUILanguage(LANG_ENGLISH);
	}
	else {
		::SetThreadUILanguage(LANG_VIETNAMESE);
	}


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CVTestViewerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CVTestViewerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;

	// The one and only window has been initialized, so show and update it
	//m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	//m_pMainWnd->DragAcceptFiles();

	CString strPath;

	if (cmdInfo.m_strFileName==L"")
	{
		CFileDialog dlgFile(TRUE, NULL , NULL, 
			OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST,
			L"Test Files (*.vtestx)|*.vtestx||", NULL, 0);
		if (dlgFile.DoModal()==IDOK)
			strPath=dlgFile.GetPathName();
		else return FALSE;
	}
	else
	{
		strPath=cmdInfo.m_strFileName;
	}

	f.Open(strPath,CFile::modeRead);
	CArchive ar(&f,CArchive::load);
	CTestInfo tInfo;
	tInfo.Serialize(ar);
	CTestHistoryArray hisArr;
	hisArr.Serialize(ar);
	ar.Close();
	f.Close();

	CDlgConfirmTest dlg;
	//m_pMainWnd=&dlg;
	dlg.m_tInfo=&tInfo;
	dlg.m_hisArr=&hisArr;
	int nRet=dlg.DoModal();
	if (nRet==IDOK)
	{
		CDlgTest dlgTest;
		dlgTest.m_nRemainingTime=tInfo.m_nTime*60;
		dlgTest.m_bShowAnswerIm=dlg.m_bShowAnswerIm;
		dlgTest.m_nView=dlg.m_nViewStyle;
		dlgTest.m_nStdType=dlg.m_nStdType;
		dlgTest.m_filePath=strPath;
		dlgTest.DoModal();
	}
	else if (nRet==IDC_VIEW_DETAIL)
	{
		CDlgTest dlgTest;
		dlgTest.m_nRemainingTime=tInfo.m_nTime*60;
		dlgTest.m_bShowAnswerIm=dlg.m_bShowAnswerIm;
		dlgTest.m_nView=dlg.m_nViewStyle;
		dlgTest.m_nStdType=dlg.m_nStdType;
		dlgTest.m_filePath=strPath;
		dlgTest.m_nReviewTest=dlg.m_nReviewTest;
		dlgTest.DoModal();
	}

	m_pMainWnd->CloseWindow();

	return TRUE;
}

// CVTestViewerApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CVTestViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

int CVTestViewerApp::ExitInstance()
{
	GdiplusShutdown(gdiplusToken);

	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CVTestViewerApp message handlers



