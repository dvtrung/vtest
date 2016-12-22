// DlgEquationEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DlgEquationEdit.h"
#include "afxdialogex.h"
#include "../MathRender/MathDraw.h"


// CDlgEquationEdit dialog

IMPLEMENT_DYNAMIC(CDlgEquationEdit, CDialog)

CDlgEquationEdit::CDlgEquationEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEquationEdit::IDD, pParent)
	, m_Text(_T(""))
{

}

CDlgEquationEdit::~CDlgEquationEdit()
{
}

void CDlgEquationEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Text);
	DDX_Control(pDX, IDC_EDIT1, m_wndText);
}


BEGIN_MESSAGE_MAP(CDlgEquationEdit, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgEquationEdit::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CDlgEquationEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgEquationEdit message handlers


void CDlgEquationEdit::OnEnChangeEdit1()
{
	RefreshImage();
}

void CDlgEquationEdit::RefreshImage()
{
	UpdateData(TRUE);
	CRect rc;
	GetDlgItem(IDC_STATIC_E)->GetWindowRect(rc);
	Graphics gr(GetDlgItem(IDC_STATIC_E)->m_hWnd);
	Bitmap memBmp(rc.Width(),rc.Height(),PixelFormat32bppARGB);
	Graphics memGr(&memBmp);
	memGr.Clear(Color::White);
	Pen pen(Color::Black);
	memGr.DrawRectangle(&pen,0,0,rc.Width()-1,rc.Height()-1);
	Gdiplus::Font font(L"Times New Roman",12,FontStyleRegular);
	int yPos;
	Bitmap* bmp=CMathDraw::Draw_Text(L"$"+m_Text+L"$",&font,rc.Width()-10,yPos,0);
	memGr.DrawImage(bmp,5,5);
	delete bmp;
	gr.DrawImage(&memBmp,0,0);
}

void CDlgEquationEdit::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


BOOL CDlgEquationEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

// 	m_ToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_MATHEQ);
// 	m_ToolBar.LoadToolBar(IDR_MATHEQ, 0, 0, TRUE /* Is locked */);
// 
// 	m_ToolBar.SetPaneStyle(m_ToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
// 	m_ToolBar.SetPaneStyle(m_ToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC));
// 
// 	m_ToolBar.SetOwner(this);
// 
// 	// All commands will be routed via this control , not via the parent frame:
// 	m_ToolBar.SetRouteCommandsViaFrame(FALSE);
// 
// 	CRect rectClient;
// 	GetClientRect(rectClient);
// 
// 	int cyTlb = m_ToolBar.CalcFixedLayout(FALSE, TRUE).cy;
// 
// 	m_ToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgEquationEdit::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CString strText; m_wndText.GetWindowText(strText);
	int s,e; m_wndText.GetSel(s,e);
	CString strSel=strText.Mid(s,e-s);
	switch (wParam)
	{
	case ID_MATHEQ_FRACTION:		strSel=L"\\frac{"+strSel+L"}{}"; break;
	case ID_MATHEQ_SQRT:			strSel=L"\\sqrt{"+strSel+L"}"; break;
	case ID_MATHEQ_SUB:				strSel=L"_{"+strSel+L"}"; break;
	case ID_MATHEQ_SUPER:			strSel=L"^{"+strSel+L"}"; break;
	}

	if (strSel!="") m_wndText.ReplaceSel(strSel,1);

	return CDialog::OnCommand(wParam, lParam);
}
