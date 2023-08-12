#include "missing_cameo.hpp"
#include "Syringe.hpp"

using namespace minono;

DEFINE_HOOK(0x004A80D0, CD_AlwaysFindYR, 6)
{
	R->EAX(2);
    missing_cameo::missing_cameo::get_instance().log("Disabling copy protection check @004A80D0");
	return 0x4A8265;
}

DEFINE_HOOK(0x004790E0, CD_AlwaysAvailable, 7)
{
	R->AL(1);
    missing_cameo::missing_cameo::get_instance().log("Disabling copy protection check @004790E0");
	return 0x479109;
}

DEFINE_HOOK(0x00479110, CD_NeverAsk, 5)
{
	R->AL(1);
    missing_cameo::missing_cameo::get_instance().log("Disabling copy protection check @00479110");
	return 0x4791EA;
}

DEFINE_HOOK(0x0049F5C0, CopyProtection_IsLauncherRunning, 8)
{
	R->AL(1);
    missing_cameo::missing_cameo::get_instance().log("Disabling copy protection check @0049F5C0");
	return 0x49F61A;
}

DEFINE_HOOK(0x0049F620, CopyProtection_NotifyLauncher, 5)
{
	R->AL(1);
    missing_cameo::missing_cameo::get_instance().log("Disabling copy protection check @0049F620");
	return 0x0049F733;
}

DEFINE_HOOK(0x0049F7A0, CopyProtection_CheckProtectedData, 8)
{
	R->AL(1);
    missing_cameo::missing_cameo::get_instance().log("Disabling copy protection check @0049F7A0");
	return 0x0049F8A7;
}
