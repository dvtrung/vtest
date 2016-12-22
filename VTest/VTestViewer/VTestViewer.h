
// VTestViewer.h : main header file for the VTestViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <GdiPlus.h>
using namespace Gdiplus;

#include "DlgHome.h"

// CVTestViewerApp:
// See VTestViewer.cpp for the implementation of this class
//

class CVTestViewerApp : public CWinApp
{
public:
	CVTestViewerApp();


// Overrides
public:
	virtual BOOL InitInstance();

	GdiplusStartupInput GdiplusStartupInput;
	ULONG_PTR GdiplusToken;

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	int ExitInstance();
};

extern CVTestViewerApp theApp;
