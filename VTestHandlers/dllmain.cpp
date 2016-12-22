// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "VTestHandlers_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CVTestHandlersModule _AtlModule;

class CVTestHandlersApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CVTestHandlersApp, CWinApp)
END_MESSAGE_MAP()

CVTestHandlersApp theApp;

BOOL CVTestHandlersApp::InitInstance()
{
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
	return CWinApp::InitInstance();
}

int CVTestHandlersApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
