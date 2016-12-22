
// VTestViewer.h : main header file for the VTestViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// CVTestViewerApp:
// See VTestViewer.cpp for the implementation of this class
//
using namespace Gdiplus;

class CVTestViewerApp : public CWinApp
{
public:
	CVTestViewerApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVTestViewerApp theApp;
