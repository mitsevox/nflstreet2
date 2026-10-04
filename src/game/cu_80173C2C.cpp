#include "game/Object_80039F5C.h"
#include "game/fn_801C1F94.h"

/* One logged play: its type (fn_80173EE0 counts type 8 separately), two
 * signed halfword values and two player references from fn_80174114. */
struct Play_80361694 {
    int mType;
    short mUnknown4;
    short mUnknown6;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
};

/* One block of the log: up to 40 plays and the block state. fn_80173D10
 * copies a finished block into the entry after its +0x1E4 index. */
struct Log_80361694 {
    Play_80361694 mPlays[40];
    int mUnknown1E0;
    unsigned short mUnknown1E4;
    unsigned short mCount;
    unsigned short mUnknown1E8;
    unsigned char mUnknown1EA;
    unsigned char mUnknown1EB;
};

/* Returned in memory by fn_80177FE0. */
struct Pair_80173E24 {
    float mX;
    float mY;
};

extern "C" {
int fn_8009D86C(void);
int fn_8009D990(int index);
int fn_8009D9A8(int index);
void fn_80173C68(void);
int fn_80173CAC(void);
void fn_80173D10(void);
int fn_80174114(int id);
int fn_80177C38(void);
Pair_80173E24 fn_80177FE0(void);
int fn_80178308(void);
void fn_8017C298(unsigned short a, short b);
void fn_8017C2F0(unsigned short a);
int fn_8022DDB4(int tag, void *data);
}

int lbl_803ECB30;
Log_80361694 lbl_80361694[3];
int lbl_80361C58[3];

extern "C" {
void fn_80173C2C(void)
{
    lbl_803ECB30 = 0;
    fn_801C1F94(lbl_80361694, 0, sizeof(lbl_80361694));
    fn_80173C68();
}

void fn_80173C68(void)
{
    fn_801C1F94(&lbl_80361694[1], 0, sizeof(Log_80361694));
    fn_801C1F94(&lbl_80361694[2], 0, sizeof(Log_80361694));
}

int fn_80173CAC(void)
{
    unsigned int count = fn_8009D86C();

    count = count ? count : 1;
    if (count > 5) {
        count = 5;
    }
    return count * fn_8009D9A8(1) - fn_8009D990(1);
}

void fn_80173D10(void)
{
    Log_80361694 *pLog = &lbl_80361694[lbl_803ECB30];
    int value;

    if (pLog->mUnknown1E4 <= 1) {
        lbl_80361694[pLog->mUnknown1E4 + 1] = *pLog;
    }
    lbl_80361694[lbl_803ECB30].mUnknown1E4 = 0xFFFF;
    lbl_80361694[lbl_803ECB30].mCount = 0;
    lbl_80361694[lbl_803ECB30].mUnknown1E8 = 0;
    lbl_80361694[lbl_803ECB30].mUnknown1EA = 0;
    lbl_80361694[lbl_803ECB30].mUnknown1EB = 0;
    value = fn_80173CAC();
    lbl_80361694[lbl_803ECB30].mUnknown1E0 = value;
    lbl_80361C58[lbl_803ECB30] = value;
    fn_8022DDB4(0x4D534447, &lbl_80361694[lbl_803ECB30]);
}

void fn_80173E24(void)
{
    int team = fn_80178308();
    Log_80361694 *pLog = &lbl_80361694[lbl_803ECB30];

    if (pLog->mUnknown1E4 != team && pLog->mUnknown1EB == 0) {
        fn_80173D10();
        lbl_80361694[lbl_803ECB30].mUnknown1E4 = team;
        fn_8017C298(team, (short)fn_80177FE0().mY);
    }
    fn_8022DDB4(0x4D534447, &lbl_80361694[lbl_803ECB30]);
}

void fn_80173EE0(int type, int a, int b, int c, int d)
{
    Log_80361694 *pLog = &lbl_80361694[lbl_803ECB30];

    if (pLog->mCount < 40) {
        lbl_80361694[lbl_803ECB30].mPlays[pLog->mCount].mType = type;
        lbl_80361694[lbl_803ECB30].mPlays[pLog->mCount].mUnknown4 = a;
        lbl_80361694[lbl_803ECB30].mPlays[pLog->mCount].mUnknown6 = b;
        lbl_80361694[lbl_803ECB30].mPlays[lbl_80361694[lbl_803ECB30].mCount].mUnknown8 = fn_80174114(c);
        lbl_80361694[lbl_803ECB30].mPlays[lbl_80361694[lbl_803ECB30].mCount].mUnknownA = fn_80174114(d);
        if (lbl_80361694[lbl_803ECB30].mUnknown1EA == 0 && (float)a >= 30.0f && fn_80177C38() == 0) {
            lbl_80361694[lbl_803ECB30].mUnknown1EA = 1;
            fn_8017C2F0(lbl_80361694[lbl_803ECB30].mUnknown1E4);
        }
        if (type == 8) {
            lbl_80361694[lbl_803ECB30].mUnknown1E8++;
        }
        lbl_80361694[lbl_803ECB30].mCount++;
        fn_8022DDB4(0x4D534447, &lbl_80361694[lbl_803ECB30]);
    }
}

void fn_80174074(void)
{
    lbl_80361C58[lbl_803ECB30] = fn_80173CAC();
}

int fn_801740A8(void)
{
    return lbl_80361694[lbl_803ECB30].mUnknown1EA;
}

void fn_801740C4(int value)
{
    Log_80361694 *pLog = &lbl_80361694[lbl_803ECB30];

    if (pLog->mUnknown1EB == 0) {
        pLog->mUnknown1EB = value;
        fn_8022DDB4(0x4D534447, pLog);
    }
}

int fn_80174114(int id)
{
    if (id != 0 && (id & 0xFF) == 1) {
        return fn_80039F5C(id >> 8 & 0xFF, id >> 16 & 0xFF)->mUnknown2908;
    }
    return 0xFFFF;
}

unsigned char fn_80174160(void)
{
    return lbl_80361694[lbl_803ECB30].mUnknown1E4;
}

void fn_8017417C(void)
{
    lbl_80361694[lbl_803ECB30].mUnknown1EA = 1;
}
}

/* Joint names read in order by fn_80176630. */
const char *lbl_802E99F0[5] = {"headend", "rwrist", "lwrist", "lball", "rball"};
