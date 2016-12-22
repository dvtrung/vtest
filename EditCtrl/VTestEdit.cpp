// VTestEdit.cpp : implementation file
//

#include "stdafx.h"
#include "VTestEdit.h"
#include "../MathRender/MathDraw.h"
#include "DlgEditText.h"

#define EDIT_CLASSNAME    L"VTestEdit"  // Window class name

// CVTestEdit

IMPLEMENT_DYNAMIC(CVTestEdit, CStatic)

CVTestEdit::~CVTestEdit()
{
	delete m_Font;
}

CVTestEdit::CVTestEdit(Gdiplus::Font* f)
{
	RegisterWindowClass();
	bEdit=false;
	bCreate=false;

	m_Font=f;
}

CVTestEdit::CVTestEdit()
{
	RegisterWindowClass();
	bEdit=false;
	bCreate=false;

	Gdiplus::Font* f=new Gdiplus::Font(L"Times New Roman",(REAL)12);
	m_Font=f;
}


void CVTestEdit::Create( CWnd* pStatic )
{
	WINDOWPLACEMENT wpl;
	pStatic->GetWindowPlacement(&wpl);
	Create(NULL,NULL,WS_VISIBLE | WS_CHILD,wpl.rcNormalPosition,pStatic->GetParent(),1);
}

BOOL CVTestEdit::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, EDIT_CLASSNAME, &wndcls)))
	{
		// otherwise we need to register a new class

		wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = EDIT_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}


BEGIN_MESSAGE_MAP(CVTestEdit, CWnd)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(MSG_TURN_TO_PREVIEW, &CVTestEdit::OnTurnToPreview)
	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CVTestEdit message handlers



void CVTestEdit::OnPaint()
{
	CWnd::OnPaint();
	if (!bEdit)
	{
		Graphics gr(this->m_hWnd);

		CRect rc; this->GetClientRect(rc);
		Bitmap bmp(rc.Width(),rc.Height(),PixelFormat32bppARGB);
		Graphics memGr(&bmp);

		memGr.Clear(Color::White);
		Pen pen(Color::Black);
		memGr.DrawRectangle(&pen,0,0,rc.Width()-1,rc.Height()-1);

		int yP;
		Bitmap* bmpText=CMathDraw::Draw_Text(m_Text,m_Font,rc.Width()-6,yP);
		memGr.DrawImage(bmpText,3,3); delete bmpText;

		gr.DrawImage(&bmp,0,0);
	}
	else
	{
		Graphics gr(this->m_hWnd);

		CRect rc; this->GetClientRect(rc);
		Bitmap bmp(rc.Width(),rc.Height(),PixelFormat32bppARGB);
		Graphics memGr(&bmp);

		Color clr; clr.SetFromCOLORREF(GetSysColor(COLOR_3DFACE));

		memGr.Clear(clr);
		Pen pen(Color::Black);
		memGr.DrawRectangle(&pen,0,0,rc.Width()-1,rc.Height()-1);

		gr.DrawImage(&bmp,0,0);
	}
}

BOOL CVTestEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CVTestEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!bCreate)
	{
		CRect rc; GetWindowRect(rc);
		m_Edit.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN, CRect(1,1,rc.Width()-2,rc.Height()-2),this, 1);
		bCreate=true;
	}

	if (!bEdit)
	{
		//this->GetParent()->ShowWindow(SW_HIDE);
		m_Edit.SetWindowText(m_Text);
		m_Edit.ShowWindow(SW_SHOWNORMAL);
		bEdit=true;
		m_Edit.SetFocus();
	}
// 	CDlgEditText dlg;
// 	dlg.m_strText=m_Text;
// 	if (dlg.DoModal()==IDOK)
// 	{
// 		m_Text=dlg.m_strText;
// 	}
// 	//this->GetParent()->ShowWindow(SW_SHOW);
// 	AfxGetMainWnd()->Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}

int CVTestEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!bCreate)
	{
		CRect rc; GetWindowRect(rc);
		m_Edit.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN, CRect(0,0,0,0),this, 1);
		bCreate=true;
		OnTurnToPreview(0,0);
	}

	return 0;
}

void CVTestEdit::OnSize(UINT nType, int cx, int cy)
{
	m_Edit.MoveWindow(1,1,cx-2,cy-2);
	CWnd::OnSize(nType, cx, cy);
}

BOOL CVTestEdit::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

LRESULT CVTestEdit::OnTurnToPreview(WPARAM wParam, LPARAM lParam)
{
	bEdit=false;
	m_Edit.GetWindowText(m_Text);
	m_Edit.ShowWindow(SW_HIDE);
	return 0;
}

BOOL CVTestEdit::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CWnd::OnEraseBkgnd(pDC);
}

void CVTestEdit::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CVTestEdit::OnDestroy()
{
	if (bEdit) m_Edit.GetWindowText(m_Text);
	CWnd::OnDestroy();
}

void CVTestEdit::SetText(CString str)
{
	if (m_Edit.m_hWnd) m_Edit.SetWindowText(str);
	m_Text=str;
	OnPaint();
}

CString CVTestEdit::GetText()
{
	if (bEdit) m_Edit.GetWindowText(m_Text);
	return m_Text;
}
