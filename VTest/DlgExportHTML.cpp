// DlgExportHTML.cpp : implementation file
//

#include "stdafx.h"
#include "VTest.h"
#include "DlgExportHTML.h"
#include "afxdialogex.h"
#include "../lib/appfunc.h"


// CDlgExportHTML dialog

IMPLEMENT_DYNAMIC(CDlgExportHTML, CDialog)

CDlgExportHTML::CDlgExportHTML(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExportHTML::IDD, pParent)
	, m_strPath(_T(""))
	, m_bOpenWhenDone(FALSE)
	, m_strFolderName(_T(""))
	, m_strTemplate(_T(""))
{

}

CDlgExportHTML::~CDlgExportHTML()
{
}

void CDlgExportHTML::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strPath);
	DDX_Control(pDX, IDC_COMBO_TEMPLATE, m_cbTemplate);
	DDX_Check(pDX, IDC_CHECK_OPEN_WHEN_DONE, m_bOpenWhenDone);
	DDX_Text(pDX, IDC_EDIT6, m_strFolderName);
	DDX_Text(pDX, IDC_COMBO_TEMPLATE, m_strTemplate);
}


BEGIN_MESSAGE_MAP(CDlgExportHTML, CDialog)
	ON_BN_CLICKED(IDOK2, &CDlgExportHTML::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, &CDlgExportHTML::OnBnClickedOk)
//	ON_BN_CLICKED(IDOK3, &CDlgExportHTML::OnBnClickedOk3)
END_MESSAGE_MAP()


// CDlgExportHTML message handlers


void CDlgExportHTML::OnBnClickedOk2()
{
	/*CFileDialog dlgFile(FALSE, NULL , NULL, 
		OFN_DONTADDTORECENT | OFN_OVERWRITEPROMPT | OFN_,
		L"Web Pages (*.htm, *.html)|*.htm;*.html||", this, 0);*/
	CFolderPickerDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		//m_strPath=dlgFile.GetPathName();
		m_strPath=dlg.GetFolderPath();
		UpdateData(FALSE);
	}
}


BOOL CDlgExportHTML::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFileFind ff;

	CString path = GetAppDirectory()+L"\\templates\\*.*";

	BOOL res = ff.FindFile(path);
	while(res)
	{
		res = ff.FindNextFile();
		if (ff.IsDirectory())
		{
			if (ff.GetFileName()!=L"." && ff.GetFileName()!=L"..")
			{
				m_cbTemplate.AddString(ff.GetFileName());
			}
		}
	}
	m_cbTemplate.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgExportHTML::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void CDlgExportHTML::OnBnClickedOk3()
{
	// TODO: Add your control notification handler code here
}
