#pragma once

// CPageStart dialog

class CPageStart : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageStart)

public:
	CPageStart();
	virtual ~CPageStart();

// Dialog Data
	enum { IDD = IDD_PROP_START };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual void OnSetFont(CFont* pFont);
	afx_msg void OnBnClickedSelectfile();
	virtual BOOL OnKillActive();

	CString m_strPath;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	virtual BOOL OnInitDialog();
};
