#include <windows.h>

#include "missing_cameo.hpp"
#include "version.h"

using namespace minono;

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		missing_cameo::missing_cameo::get_instance().log("MissingCameo launching, rev {}", k_revision);
		missing_cameo::missing_cameo::get_instance().set_module_handle(hInstance);
		missing_cameo::missing_cameo::get_instance().log("Dll attached to process, hInstance = {}", (void*)hInstance);
		break;
	case DLL_PROCESS_DETACH:
		missing_cameo::missing_cameo::get_instance().log("Dll detached...");
		break;
	default:
		break;
	}
	return TRUE;
}