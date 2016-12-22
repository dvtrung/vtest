
// VTestStd.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "../lib/ItemArray.h"


// CVTestStdApp:
// See VTestStd.cpp for the implementation of this class
//

class CVTestStdApp : public CWinApp
{
public:
	CVTestStdApp();

// Overrides
public:
	virtual BOOL InitInstance();

	GdiplusStartupInput GdiplusStartupInput;
	ULONG_PTR GdiplusToken;

// Implementation

	DECLARE_MESSAGE_MAP()
	int ExitInstance();
};

extern CVTestStdApp theApp;