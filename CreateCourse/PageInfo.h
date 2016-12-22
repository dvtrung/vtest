#pragma once


// CPageInfo dialog

class CPageInfo : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageInfo)

public:
	CPageInfo();
	virtual ~CPageInfo();

// Dialog Data
	enum { IDD = IDD_PROP_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();

	CString m_strCourseTitle;
	CString m_strAuthor;
	CString m_strSubject;
	CString m_strDesc;
};
