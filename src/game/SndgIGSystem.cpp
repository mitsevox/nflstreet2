/* Starts up and shuts down in-game audio for the SndgIG module: sound banks, crowd, ambience, the
   game-event callback and the in-game speech (commentary) system, in a fixed order. */

#include "game/cu_80067C10.h"
#include "game/fn_8017F584.h"
#include "game/SndgCrowd.h"

struct Struct_8006C2C8;

extern "C" {
void fn_8006B664(void);
void fn_8006B790(void);
void fn_8006BCC8(int type);
void fn_8006C2C8(Struct_8006C2C8 *pInit);
void fn_8006C454(void);
void fn_8006D188(int withThird);
void fn_8006D268(void);
void fn_8006EC24(void);
void fn_8006F810(void);
void fn_8006F820(void);
void fn_800710C8(void);
void fn_80071594(void *pRecord);
void fn_80071600(void);
void fn_800716E4(void);
void fn_80071C34(int value);
void SpchIGInit(void);
void SpchIGShutdown(void);
int fn_800A350C(void);
void fn_800B1670(void (*pCallback)(void *));
int fn_800C8704(int *pA, int *pB);
void fn_801F2798(const char *pText);

extern Struct_8006C2C8 lbl_802D6228;
}

static int _SndgIG_iReserved;

extern "C" void SndgIGLogStartupInfo(void)
{
    char s0[19];
    char s1[19];
    char s2[17];
    char s3[17];
    char s4[25];
    char s5[25];
    int a;
    int b;

    a = 0;
    b = 0;
    s0[sizeof(s0) - 1] = 0;
    s1[sizeof(s1) - 1] = 0;
    s2[sizeof(s2) - 1] = 0;
    s3[sizeof(s3) - 1] = 0;
    s4[sizeof(s4) - 1] = 0;
    s5[sizeof(s5) - 1] = 0;
    fn_800C8704(&a, &b);
}

extern "C" void SndgIGInitAudio(void)
{
    fn_8006C2C8(&lbl_802D6228);
    _SndgIG_iReserved = 0;
    fn_80067C70();
    fn_800B1670(fn_80071594);
    fn_8006D188(fn_8017F584() == 11);
    fn_8006B664();
    fn_8006BCC8(0);
    if (fn_800A350C()) {
        fn_8006F394(0, 0);
    }
    fn_8006F810();
    fn_80071600();
    fn_80071C34(0);
    SndgIGLogStartupInfo();
    fn_8006EC24();
    fn_800710C8();
    fn_801F2798("SpchIGInitStart");
    SpchIGInit();
    fn_801F2798("SpchIGInitFinish");
}

extern "C" void SndgIGShutdownAudio(void)
{
    SpchIGShutdown();
    fn_8006B790();
    fn_8006F820();
    fn_800716E4();
    fn_8006D268();
    fn_8006C454();
}
