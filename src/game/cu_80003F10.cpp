#include "game/cu_80003F10.h"

#include <string.h>

static unsigned char lbl_803EB8E8 = 0;

/* Five 64-byte buffers that FillDemoLaunchPaths fills with executable
   paths; the field labels are neutral. */
struct DemoLaunchPaths {
    char mPath0[64];
    char mPath1[64];
    char mPath2[64];
    char mPath3[64];
    char mPath4[64];
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
        strncpy(paths.mPath0, "D:\\MADDEN05\\Madden05.xbe", 64);
        strncpy(paths.mPath1, "D:\\MADDEN05\\Maddem05.xbe", 64);
        strncpy(paths.mPath2, "cdrom0:\\MADDEN05\\Maddem05.ELF;1", 64);
        strncpy(paths.mPath3, "host0:\\PROJ\\NFLBIG\\DATA\\PS2\\MADDEMO\\Madden05.ELF", 64);
        strncpy(paths.mPath4, "host0:\\PROJ\\NFLBIG\\DATA\\PS2\\MADDEMO\\Madden05r.ELF", 64);
    }
}
