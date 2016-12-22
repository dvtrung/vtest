#pragma once


// CDlgMarkRandom dialog

class CDlgMarkRandom : public CDialog
{
	DECLARE_DYNAMIC(CDlgMarkRandom)

public:
	CDlgMarkRandom(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMarkRandom();

// Dialog Data
	enum { IDD = IDD_DLGMARKRANDOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_Number;
};
