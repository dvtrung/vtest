// InputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InputDlg.h"


// CInputDlg dialog

IMPLEMENT_DYNAMIC(CInputDlg, CDialog)

CInputDlg::CInputDlg(CString strCaption,CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg::IDD, pParent)
{
	m_Width=300;
	m_strCaption=strCaption;
}

CInputDlg::~CInputDlg()
{
	for (int i=0;i<m_wnd.size();i++)
	{
		delete m_wnd[i];
	}
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	int j=0;
	for (int i=0;i<m_wnd.size();i++)
	{
		if (m_wnd[i]->m_hWnd!=NULL && m_wnd[i]->GetDlgCtrlID()!=0)
		{
			if ((*m_wnd[i]).GetRuntimeClass()==RUNTIME_CLASS(CStatic))
				j++;
			if ((*m_wnd[i]).GetRuntimeClass()==RUNTIME_CLASS(CEdit))
				DDX_Text(pDX,i-j+3,*(CString*)m_Value[i-j]);
			if ((*m_wnd[i]).GetRuntimeClass()==RUNTIME_CLASS(CComboBox))
				DDX_Text(pDX,i-j+3,*(CString*)m_Value[i-j]);
		}
	}
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CInputDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CInputDlg::AddStatic(CString strText)
{
	CStatic* m_static=new CStatic();
	m_wnd.push_back(m_static);
	m_StaticText.push_back(strText);
}

void CInputDlg::AddEdit(CString* strValue, DWORD dwStyle)
{
	CEdit* m_edit=new CEdit();
	m_wnd.push_back(m_edit);
	m_Value.push_back(strValue);
	m_dwStyle.push_back(dwStyle);
}

void CInputDlg::AddComboBox(CString* strValue, CStringArray* arrItem, DWORD dwStyle)
{
	CComboBox* m_combo=new CComboBox();
	m_wnd.push_back(m_combo);
	m_Value.push_back(strValue);
	m_dwStyle.push_back(dwStyle);
	m_comboArray.push_back(arrItem);
}

BOOL CInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_strCaption);
	int top=CTRL_DISTANCE;
	font.DeleteObject();
	font.CreatePointFont(80,L"Tahoma");
	int j=0;
	int comboCount=0;
	for (int i=0;i<m_wnd.size();i++)
	{
		if ((*m_wnd[i]).GetRuntimeClass()==RUNTIME_CLASS(CStatic))
		{
			CStatic* ctrl=(CStatic*)m_wnd[i];
			ctrl->Create(m_StaticText[j],WS_VISIBLE,CRect(CTRL_DISTANCE,top,m_Width-2*CTRL_DISTANCE,top+EDIT_HEIGHT),this,-1);
			ctrl->SetFont(&font);
			top+=CTRL_STEP+STATIC_HEIGHT;
			j++;
		}
		else if ((*m_wnd[i]).GetRuntimeClass()==RUNTIME_CLASS(CEdit))
		{
			CEdit* ctrl=(CEdit*)m_wnd[i];
			ctrl->Create(m_dwStyle[i-j],CRect(CTRL_DISTANCE,top,m_Width-2*CTRL_DISTANCE,top+EDIT_HEIGHT),this,i-j+3);
			ctrl->SetFont(&font);
			//ctrl->ModifyStyleEx(0,WS_EX_CLIENTEDGE);
			top+=CTRL_STEP+EDIT_HEIGHT;
		}
		else if ((*m_wnd[i]).GetRuntimeClass()==RUNTIME_CLASS(CComboBox))
		{
			CComboBox* ctrl=(CComboBox*)m_wnd[i];
			ctrl->Create(m_dwStyle[i-j],CRect(CTRL_DISTANCE,top,m_Width-2*CTRL_DISTANCE,top+EDIT_HEIGHT),this,i-j+3);
			for (int k=0;k<m_comboArray[comboCount]->GetSize();k++)
			{
				ctrl->AddString(m_comboArray[comboCount]->GetAt(k));
				ctrl->SetCurSel(0);
			}
			ctrl->SetFont(&font);
			comboCount++;
			top+=CTRL_STEP+EDIT_HEIGHT;
		}
	}

	top+=CTRL_STEP;

	m_btnOK.Create(L"Chấp nhận",BS_PUSHBUTTON | WS_VISIBLE, CRect(0,0,0,0),this,IDOK);
	m_btnCancel.Create(L"Thôi",BS_PUSHBUTTON | WS_VISIBLE, CRect(0,0,0,0),this,IDCANCEL);
	m_btnOK.SetFont(&font);
	m_btnCancel.SetFont(&font);

	//CRect rect;
	//m_btnOK.GetWindowRect(&rect);
	const int rectWidth=70;
	const int rectHeight=25;

	m_btnCancel.MoveWindow(CRect(m_Width-rectWidth-CTRL_DISTANCE-2*GetSystemMetrics(SM_CXFRAME),top,
		m_Width-CTRL_DISTANCE-2*GetSystemMetrics(SM_CXFRAME),top+rectHeight));
	m_btnOK.MoveWindow(CRect(m_Width-2*rectWidth-2*CTRL_DISTANCE-2*GetSystemMetrics(SM_CXFRAME),top,
		m_Width-rectWidth-2*CTRL_DISTANCE-2*GetSystemMetrics(SM_CXFRAME),top+rectHeight));

	top+=2*CTRL_DISTANCE+rectHeight-GetSystemMetrics(SM_CXFRAME);
			
	CSize size;
	size.cx=m_Width-GetSystemMetrics(SM_CXFRAME);
	size.cy=top+GetSystemMetrics(SM_CYCAPTION);

	MoveWindow(CRect(CPoint(0,0),size));
	
	CenterWindow();

// 	if (m_wnd[1]->GetRuntimeClass()==RUNTIME_CLASS(CEdit)) 
// 	{
// 		m_wnd[1]->SendMessage(WM_KEYDOWN,VK_RIGHT,1);
// // 		CString str;
// // 		((CEdit*)m_wnd[1])->GetWindowText(str);
// // 		((CEdit*)m_wnd[1])->SetSel(str.GetLength(),str.GetLength());
// 	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CInputDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CInputDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnOK();
}
