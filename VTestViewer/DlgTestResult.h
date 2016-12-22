#pragma once


// CDlgTestResult dialog

class CDlgTestResult : public CDialog
{
	DECLARE_DYNAMIC(CDlgTestResult)

public:
	CDlgTestResult(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTestResult();

// Dialog Data
	enum { IDD = IDD_DIALOG_TEST_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_SoCau;
	int m_SoCauDung;
	int m_SoCauLam;
	int m_ThoiGian;
	int m_ThoiGianLam;

	CFont m_Font;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
