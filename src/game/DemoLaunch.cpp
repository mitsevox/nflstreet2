/* Demo-disc launch support carried over from the other consoles: a flag
   the front-end loop clears, a launch check that always says no on
   GameCube, and the Madden 05 demo executable paths the PS2 and Xbox
   versions launch (the copy routine is not linked into this game). */
#include "game/DemoLaunch.h"

#include <string.h>

static unsigned char _DemoLaunch_bFlag = 0;

/* Five 64-byte buffers that FillDemoLaunchPaths fills with executable
   paths; the field labels are neutral. */
struct DemoLaunchPaths {
    char mPath0[64];
    char mPath1[64];
    char mPath2[64];
    char mPath3[64];
    char mPath4[64];
};

extern "C" void DemoLaunchSetFlag(unsigned char value)
{
    _DemoLaunch_bFlag = value;
}

extern "C" bool DemoLaunchIsFlagSet(void)
{
    return _DemoLaunch_bFlag != 0;
}

extern "C" int DemoLaunchIsAllowed(void)
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
