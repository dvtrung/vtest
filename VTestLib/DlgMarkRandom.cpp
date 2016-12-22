// DlgMarkRandom.cpp : implementation file
//

#include "stdafx.h"
#include "VTestLib.h"
#include "DlgMarkRandom.h"
#include "afxdialogex.h"


// CDlgMarkRandom dialog

IMPLEMENT_DYNAMIC(CDlgMarkRandom, CDialog)

CDlgMarkRandom::CDlgMarkRandom(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMarkRandom::IDD, pParent)
	, m_Number(0)
{

}

CDlgMarkRandom::~CDlgMarkRandom()
{
}

void CDlgMarkRandom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Number);
}


BEGIN_MESSAGE_MAP(CDlgMarkRandom, CDialog)
END_MESSAGE_MAP()


// CDlgMarkRandom message handlers
