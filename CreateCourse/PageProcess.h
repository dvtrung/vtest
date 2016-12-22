#pragma once

// CPageProcess dialog

class CPageProcess : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageProcess)

public:
	CPageProcess();
	virtual ~CPageProcess();

// Dialog Data
	enum { IDD = IDD_PROP_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	void SaveToFile(CString strPath);
	void MoveFile(HTREEITEM hParent);

	int nFile;
};
