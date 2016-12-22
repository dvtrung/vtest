
// VTestStdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VTestStd.h"
#include "VTestStdDlg.h"
#include "afxdialogex.h"
#include "DlgLogin.h"
#include "DlgSelectCourse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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
public:
	afx_msg void OnPaint();
//	afx_msg void OnSetFocus(CWnd* pOldWnd);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_PAINT()
//	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CVTestStdDlg dialog




CVTestStdDlg::CVTestStdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVTestStdDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVTestStdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVTestStdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CVTestStdDlg message handlers

BOOL CVTestStdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVTestStdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVTestStdDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		Graphics gr(this->m_hWnd);
		CRect rc; GetClientRect(&rc);
		Rect rect(0,0,rc.Width(),rc.Height());
		LinearGradientBrush br(rect,Color::LightSteelBlue, Color::White, 
			LinearGradientModeVertical);
		gr.FillRectangle(&br,rect);

		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVTestStdDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CVTestStdDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	ShowWindow(SW_MAXIMIZE);
	SetWindowText(L"VTestStd");

	//m_Tab.Create(L"QuestList",L"",
	//	WS_CHILD | WS_VISIBLE, CRect(100,100,800,130),this,1);

	m_AccArr.LoadAccount();

	ShowDlgLogin();
	//m_Tab.SetItemWidth(25);
	//for (int i=0;i<50;i++) m_Tab.m_StrArray.Add(IntToString(i));

	OnOK();

	return 0;
}


void CVTestStdDlg::ShowDlgLogin()
{
	CDlgLogin dlg;
	dlg.m_AccArr=&m_AccArr;
	if (dlg.DoModal()==IDOK)
	{
		//ShowDlgUser(dlg.m_UserName);
		ShowDlgSelectCourse(dlg.m_UserName);
	}
}

void CVTestStdDlg::ShowDlgUser(CString userName)
{
	CDlgUser dlgU;
	for (int i=0;i<m_AccArr.m_Array.GetSize();i++)
		if (m_AccArr.m_Array.GetAt(i)->userName==userName)
		{
			dlgU.acc=m_AccArr.m_Array.GetAt(i);
			break;
		}
		
	dlgU.DoModal();
}

void CVTestStdDlg::ShowDlgSelectCourse(CString userName)
{
	CDlgSelectCourse dlg;
	if (dlg.DoModal()==IDOK)
	{

	}
}

void CAboutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}


//void CAboutDlg::OnSetFocus(CWnd* pOldWnd)
//{
//	CDialog::OnSetFocus(pOldWnd);
//
//	// TODO: Add your message handler code here
//}
