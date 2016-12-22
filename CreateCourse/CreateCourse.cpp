
// CreateCourse.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CreateCourse.h"

#include "app.h"
#include "WizardSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCreateCourseApp

BEGIN_MESSAGE_MAP(CCreateCourseApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CPageChooseFiles* m_pgChooseFiles;
CPageChooseOutput* m_pgChooseOutput;
CPageStart* m_pgStart;
CPageInfo* m_pgInfo;
CPageReview* m_pgReview;
CPageProcess* m_pgProcess;
CPageEnd* m_pgEnd;

// CCreateCourseApp construction

CCreateCourseApp::CCreateCourseApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCreateCourseApp object

CCreateCourseApp theApp;


// CCreateCourseApp initialization

BOOL CCreateCourseApp::InitInstance()
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

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

// 	CPageStart pgStart; pgStart.m_psp.dwFlags &= ~(PSH_HASHELP);
// 	CPageInfo pgInfo; pgInfo.m_psp.dwFlags &= ~(PSH_HASHELP);
// 	CPageChooseFiles pgChooseFiles; pgChooseFiles.m_psp.dwFlags &= ~(PSH_HASHELP);
// 	CPageReview pgReview; pgReview.m_psp.dwFlags &= ~(PSH_HASHELP);
// 	CPageChooseOutput pgOutput; pgOutput.m_psp.dwFlags &= ~(PSH_HASHELP);
// 	CPageProcess pgProcess; pgProcess.m_psp.dwFlags &= ~(PSH_HASHELP);
// 	CPageEnd pgEnd; pgEnd.m_psp.dwFlags &= ~(PSH_HASHELP);
 	CWizardSheet sheet(L"VOcean"); sheet.m_psh.dwFlags &= ~(PSH_HASHELP);

	m_pgStart=new CPageStart();
	m_pgInfo=new CPageInfo();
	m_pgChooseFiles=new CPageChooseFiles();
	m_pgReview=new CPageReview();
	m_pgChooseOutput=new CPageChooseOutput();
	m_pgProcess=new CPageProcess();
	m_pgEnd=new CPageEnd();

	//sheet.Construct(L"Test",NULL,0,NULL,0,(HBITMAP)bmp);
	sheet.AddPage(m_pgStart);
	sheet.AddPage(m_pgInfo);
	sheet.AddPage(m_pgChooseFiles);
	sheet.AddPage(m_pgReview);
	sheet.AddPage(m_pgChooseOutput);
	sheet.AddPage(m_pgProcess);
	sheet.AddPage(m_pgEnd);
	sheet.SetWizardMode();
	
	sheet.DoModal();

	delete m_pgStart;
	delete m_pgInfo;
	delete m_pgChooseFiles;
	delete m_pgReview;
	delete m_pgChooseOutput;
	delete m_pgProcess;
	delete m_pgEnd;



	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

