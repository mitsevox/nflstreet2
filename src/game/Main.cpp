/* Program entry: main initializes the console (OS, the paired-single quantization registers, DVD,
   video and virtual memory) and then runs the game's main loop until it returns. */
#include <dolphin/os.h>
#include <dolphin/dvd.h>
#include <dolphin/vi.h>
#include <dolphin/__vm.h>

/* Defined with C++ linkage in src/game/MainLoop.cpp. */
void MainLoopRun(void);

extern "C" void GlibSetTvMode(int value);

void _MainInitFastCast(void)
{
    asm volatile("li 3,4\n\toris 3,3,4\n\tmtspr GQR2,3\n\t"
                 "li 3,5\n\toris 3,3,5\n\tmtspr GQR3,3\n\t"
                 "li 3,6\n\toris 3,3,6\n\tmtspr GQR4,3\n\t"
                 "li 3,7\n\toris 3,3,7\n\tmtspr GQR5,3\n\t"
                 "li 3,7\n\toris 3,3,3847\n\tmtspr GQR6,3\n\t"
                 "li 3,7\n\toris 3,3,7\n\tmtspr GQR7,3"
                 : : : "r3");
}

extern "C" void MainInitPlatform(void)
{
    OSInit();
    _MainInitFastCast();
    DVDInit();
    VIInit();
    VMInit(0x41000, 0xAFC000, 0x104000);
    VMSetPageReplacementPolicy(0);
}

int main(void)
{
    MainInitPlatform();
    GlibSetTvMode(0);
    MainLoopRun();
    return 0;
}
