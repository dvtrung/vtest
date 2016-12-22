// dllmain.h : Declaration of module class.

class CVTestHandlersModule : public ATL::CAtlDllModuleT< CVTestHandlersModule >
{
public :
	DECLARE_LIBID(LIBID_VTestHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_VTESTHANDLERS, "{E085F04F-A25B-445D-BA06-8FC8F5658107}")
};

extern class CVTestHandlersModule _AtlModule;
