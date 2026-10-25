// dllmain.h : Declaration of module class.

class CHotelServerModule : public ATL::CAtlDllModuleT< CHotelServerModule >
{
public :
	DECLARE_LIBID(LIBID_HotelServerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HOTELSERVER, "{f26aa6f4-9f00-4295-85fa-99ee768434bb}")
};

extern class CHotelServerModule _AtlModule;
