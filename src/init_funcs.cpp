#include "missing_cameo.hpp"
#include "Syringe.hpp"

#include <span>
#include <windows.h>

using namespace minono;

DEFINE_HOOK(0x007c979c, FUN_007c979c, 5)
{
    *(DWORD**)0x00b78bc0 = new DWORD[32];
    *(DWORD**)0x00b78bbc = *(DWORD**)0x00b78bc0;
    return 0;
}

// DEFINE_HOOK(0x007cb33d, FUN_007cb33d, 5)
// {

// }

DEFINE_HOOK(0x007d386a, FUN_007d386a, 5)
{
    if (*(DWORD*)0x00b78bb8 == 0)
    {
        ((void(*)(int))0x007d3482)(-3);
    }
    *(DWORD*)0x00b78bb8 = 1;
    return 0x007d3885;
}

// int FUN_007d3482(int param_1)
// {

//     return 0;
// }

// FUN_007cbed3(&DAT_00815da8,&DAT_00815dbc);
// FUN_007cbed3(&DAT_00812000,&DAT_00815da4);
#if 0
DEFINE_HOOK(0x007cbed3, PreWinMain, 5)
{
    using func_ptr = void(*)();
    func_ptr** begin = R->lea_Stack<func_ptr**>(0x4);
    func_ptr** end = R->lea_Stack<func_ptr**>(0x8);

    if (begin > end)
    {
        return 0x007cbeec;
    }
    std::span<func_ptr*> span { begin, end };
    for (const auto& func : span)
    {
        if (func != nullptr && *func != nullptr)
        {
            (*func)();
        }
    }
    return 0x007cbeec;
}
#endif
