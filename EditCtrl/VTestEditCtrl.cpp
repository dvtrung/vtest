// VTestEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "VTestEditCtrl.h"
#include "DlgEquationEdit.h"
#include "resource.h"

// CVTestEditCtrl

IMPLEMENT_DYNAMIC(CVTestEditCtrl, CEdit)

CVTestEditCtrl::CVTestEditCtrl()
{

}

CVTestEditCtrl::~CVTestEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CVTestEditCtrl, CEdit)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_CUT, &CVTestEditCtrl::OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CVTestEditCtrl::OnUpdateEditCut)
	ON_COMMAND(ID_EDITCTRL_TURN_TO_PREVIEW, &CVTestEditCtrl::OnEditctrlTurnToPreview)
	ON_COMMAND(ID_EDIT_UNDO, &CVTestEditCtrl::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CVTestEditCtrl::OnUpdateEditUndo)
END_MESSAGE_MAP()



// CVTestEditCtrl message handlers



int CVTestEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	font.CreatePointFont(120,L"Times New Roman");
	SetFont(&font);

	return 0;
}

void CVTestEditCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu m_menu;
	m_menu.LoadMenu(IDR_MENU_POPUP);
	HMENU hMenu=m_menu.Detach();
	CMenu *pPopup = CMenu::FromHandle( hMenu )->GetSubMenu(1);
	//**************   Uncomment these codes if you want to response CmdUI ****************
//      CCmdUI      CmdUI;
//      CmdUI.m_nIndexMax = pPopup->GetMenuItemCount();
//      for( unsigned int nIndex = 0; nIndex < CmdUI.m_nIndexMax; ++nIndex )
//      {
//           CmdUI.m_nIndex = nIndex;
//           CmdUI.m_nID = pPopup->GetMenuItemID(nIndex);
//           CmdUI.m_pMenu = pPopup;
//           CmdUI.DoUpdate( this, TRUE );
//      }
	//*************************************************************************************/
//	::SetMenuDefaultItem(pPopup->m_hMenu,0,TRUE);

	//pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	UINT nCmd=pPopup->TrackPopupMenuEx(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD,point.x,point.y,this,NULL);
	CString strText; GetWindowText(strText);
	int s,e; GetSel(s,e);
	CString strSel=strText.Mid(s,e-s);
	switch (nCmd)
	{
	case ID_POPUPEDIT_FORMAT_FORMULA:	strSel=L"$" + strSel + L"$"; break;
	case ID_POPUPEDIT_FORMAT_BOLD:		strSel=L"[b]" + strSel + L"[\b]"; break;
	case ID_POPUPEDIT_FORMAT_ITALIC:	strSel=L"[i]" + strSel + L"[\i]"; break;
	case ID_POPUPEDIT_FORMAT_UNDERLINE:	strSel=L"[u]" + strSel + L"[\u]"; break;
	case ID_POPUPEDIT_SYMBOLS_A:		strSel=L"α"; break;
	case ID_POPUPEDIT_SYMBOLS_B:		strSel=L"β"; break;
	case ID_POPUPEDIT_SYMBOLS_C:		strSel=L"γ"; break;
	case ID_POPUPEDIT_SYMBOLS_D:		strSel=L"δ"; break;
	case ID_POPUPEDIT_SYMBOLS_D2:		strSel=L"Δ"; break;
	case ID_POPUPEDIT_SYMBOLS_E:		strSel=L"ε"; break;
	case ID_POPUPEDIT_SYMBOLS_F:		strSel=L"φ"; break;
	case ID_POPUPEDIT_SYMBOLS_L:		strSel=L"λ"; break;
	case ID_POPUPEDIT_SYMBOLS_M:		strSel=L"μ"; break;
	case ID_POPUPEDIT_SYMBOLS_O2:		strSel=L"Ω"; break;
	case ID_POPUPEDIT_SYMBOLS_P:		strSel=L"π"; break;
	case ID_POPUPEDIT_SYMBOLS_R:		strSel=L"ρ"; break;
	case ID_POPUPEDIT_SYMBOLS_S:		strSel=L"σ"; break;
	case ID_POPUPEDIT_SYMBOLS_W:		strSel=L"ω"; break;
	case ID_POPUPEDIT_SYMBOLS_LTOE:		strSel=L"≤"; break;
	case ID_POPUPEDIT_SYMBOLS_GTOE:		strSel=L"≥"; break;
	case ID_POPUPEDIT_SYMBOLS_NE:		strSel=L"≠"; break;
	case ID_POPUPEDIT_SYMBOLS_APP:		strSel=L"≈"; break;
	case ID_POPUPEDIT_SYMBOLS_TR:		strSel=L"≡"; break;
	case ID_POPUPEDIT_SYMBOLS_MUL:		strSel=L"×"; break;
	case ID_POPUPEDIT_SYMBOLS_DIVIDE:	strSel=L"÷"; break;
	case ID_POPUPEDIT_SYMBOLS_PM:		strSel=L"±"; break;
	case ID_POPUPEDIT_SYMBOLS_SQUARE:	strSel=L"²"; break;
	case ID_POPUPEDIT_SYMBOLS_CUBE:		strSel=L"³"; break;
	case ID_POPUPEDIT_SYMBOLS_1O2:		strSel=L"½"; break;
	case ID_POPUPEDIT_SYMBOLS_1O4:		strSel=L"¼"; break;
	case ID_POPUPEDIT_SYMBOLS_DEGREE:	strSel=L"º"; break;
	//case ID_POPUPEDIT_SYMBOLS_DOWNARROW:	strSel=L"↓"; break;

	case ID_POPUPEDIT_MATH_SUPERSCRIPT: strSel=L"^{" + strSel + L"}"; break;
	case ID_POPUPEDIT_MATH_SUBSCRIPT:	strSel=L"_{" + strSel + L"}"; break;
	case ID_POPUPEDIT_MATH_SSSCRIPT:	strSel=L"\\SS{" + strSel + L"}{}"; break;
	case ID_POPUPEDIT_MATH_FRAC:		strSel=L"\\frac{" + strSel + L"}{}"; break;
	case ID_POPUPEDIT_MATH_SQRT:		strSel=L"\\sqrt{" + strSel + L"}{}"; break;
	case ID_POPUPEDIT_MATH_RA:			strSel=L"\\RightArrow{" + strSel + L"}{}"; break;
	case ID_POPUPEDIT_MATH_LRA:			strSel=L"\\LRArrow{" + strSel + L"}{}"; break;
	case ID_POPUPEDIT_MATH_UD:			strSel=L"\\UD{" + strSel + L"}{}{}"; break;
	case ID_POPUPEDIT_MATH_ANGLE:		strSel=L"\\Angle{" + strSel + L"}"; break;
	case ID_POPUPEDIT_MATH_DL:			strSel=L"\\DL{" + strSel + L"}"; break;

	case ID_EDIT_CUT: Cut(); break;
	case ID_EDIT_COPY: Copy(); break;
	case ID_EDIT_UNDO: Undo(); break;
	case ID_EDITCTRL_TURN_TO_PREVIEW: OnEditctrlTurnToPreview(); break;
	case ID_EDITCTRL_ADD_FORMULA: 
		CDlgEquationEdit dlg;
		if (dlg.DoModal()==IDOK)
			strSel=L"$"+dlg.m_Text+L"$";
		break;
	}
	if (strSel!="") ReplaceSel(strSel,1);
	
//	PostMessage(WM_NULL);     
//	CEdit::OnContextMenu(pWnd,point);
}

void CVTestEditCtrl::OnEditCut()
{
	Cut();
}

void CVTestEditCtrl::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	
}

void CVTestEditCtrl::OnEditctrlTurnToPreview()
{
	GetParent()->SendMessage(MSG_TURN_TO_PREVIEW);
}

void CVTestEditCtrl::OnEditUndo()
{
	Undo();
}

void CVTestEditCtrl::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CanUndo());
}
