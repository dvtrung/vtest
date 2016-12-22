#pragma once


// CPageChooseOutput dialog

class CPageChooseOutput : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageChooseOutput)

public:
	CPageChooseOutput();
	virtual ~CPageChooseOutput();

// Dialog Data
	enum { IDD = IDD_PROP_CHOOSE_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChoose();
	afx_msg void OnBnClickedButtonSaveToFile();
};
