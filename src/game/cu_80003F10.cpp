#include "game/cu_80003F10.h"

#include <string.h>

static unsigned char lbl_803EB8E8 = 0;

/* Boot paths of the other platforms' demo and retail executables. */
struct DemoLaunchPaths {
    char mXboxRetail[64];
    char mXboxDemo[64];
    char mPs2Demo[64];
    char mPs2HostDemo[64];
    char mPs2HostRetail[64];
};

extern "C" void fn_80003F10(unsigned char value)
{
    lbl_803EB8E8 = value;
}

extern "C" bool fn_80003F18(void)
{
    return lbl_803EB8E8 != 0;
}

extern "C" int fn_80003F30(void)
{
    return 0;
}

void FillDemoLaunchPaths(int mode)
{
    DemoLaunchPaths paths;

    if (mode == 0) {
        strncpy(paths.mXboxRetail, "D:\\MADDEN05\\Madden05.xbe", 64);
        strncpy(paths.mXboxDemo, "D:\\MADDEN05\\Maddem05.xbe", 64);
        strncpy(paths.mPs2Demo, "cdrom0:\\MADDEN05\\Maddem05.ELF;1", 64);
        strncpy(paths.mPs2HostDemo, "host0:\\PROJ\\NFLBIG\\DATA\\PS2\\MADDEMO\\Madden05.ELF", 64);
        strncpy(paths.mPs2HostRetail, "host0:\\PROJ\\NFLBIG\\DATA\\PS2\\MADDEMO\\Madden05r.ELF", 64);
    }
}
