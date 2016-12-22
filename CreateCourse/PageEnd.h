#pragma once


// CPageEnd dialog

class CPageEnd : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageEnd)

public:
	CPageEnd();
	virtual ~CPageEnd();

// Dialog Data
	enum { IDD = IDD_PROP_END };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
