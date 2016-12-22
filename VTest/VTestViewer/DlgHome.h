#pragma once


// CDlgHome dialog

class CDlgHome : public CDialog
{
	DECLARE_DYNAMIC(CDlgHome)

public:
	CDlgHome(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgHome();

// Dialog Data
	enum { IDD = IDD_DLGHOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
