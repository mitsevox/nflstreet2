#include "game/Block_801BE60C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/Object_80039F5C.h"

struct Object_800DC36C {
    char mUnknown0[36];
    unsigned short mUnknown36;
    char mUnknown38[2];
    int mUnknown40;
};

struct Entry_800DC36C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Object_800DC36C *mpUnknown4;
};

struct List_800DC36C {
    unsigned short mCount;
    char mUnknown2[2];
    Entry_800DC36C mEntries[1];
};

extern "C" {
extern float lbl_803ECB08;

void fn_8009BD60(Object_80039F5C *p);
int fn_800A7EF4(unsigned char a);
void fn_800ADB90(Object_80039F5C *p, int a, int b, int c);
float fn_800C495C(Object_80039F5C *p, float value);
void fn_800C89F0(Object_80039F5C *p, int a, int b, int c, float value);
void fn_800CABF4(Object_80039F5C *p, unsigned char *pOut, int a);
int fn_800D0B90(Object_80039F5C *p);
int fn_800DC080(Object_80039F5C *p);
int fn_8011F1CC(void);
int fn_8011F1F4(void);
int fn_8011F2C4(void);
int fn_801481B0(void);
int fn_801483F8(void);
int fn_801486A0(void);
void fn_80156C78(int index, int value);
Object_80039F5C *fn_8016444C(Object_800670B4 *p);
Object_800670B4 *fn_80168708(int team);
float fn_8016D9F4(Object_80039F5C *p, float a, float b);
int fn_801783AC(int bit);
int fn_801BA2A8(void *a, void *b, unsigned short c, unsigned short d,
                unsigned short key, Object_80039F5C *p, float value);
void fn_801BD81C(void *p, float value);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *p, float value);
int fn_801BE648(void *p);
void fn_801BE760(void *p, unsigned short key, int flag);
float fn_801CFFA0(float value);
int fn_801CFFD0(int a, int b);
}

static unsigned int lbl_803EAD1C = 0;

extern "C" int fn_800DBB74(Object_80039F5C *p, unsigned char *pOut)
{
    int result;

    *pOut = 0;
    if (p->mUnknown8 == 255 || !(p->mFlags & 0x4000)) {
        int mode = fn_800AD9B4();
        result = 1;
        if (!fn_801783AC(0)) {
            unsigned char kind = p->mUnknown2914;
            if ((kind == 0 || kind == 20 || kind == 1 || kind == 3)
                && (fn_8011F1CC() || fn_8011F1F4())
                && mode == 3 && p->mpState->mId == 18 && p->mUnknown360 == 1) {
                *pOut = 1;
            }
        }
    } else {
        result = 0;
    }
    return result;
}

extern "C" void fn_800DBC4C(Object_80039F5C *p, int angle, float value)
{
    int dir = 0x755555;
    int result;
    int target;

    if (p->mUnknown2910[3] == 0) {
        dir = 0xAAAAA;
    }
    if (fn_801BE648(p->mpUnknown792) != 217 || value > 0.0f) {
        if (value <= 0.0f) {
            lbl_803EAD1C++;
            if (fn_801CFFD0(p->mMotion.mFacing, dir) > 0x400000) {
                if (lbl_803EAD1C > 15) {
                    int base = 0x800000;
                    if (p->mUnknown2910[3] == 0) {
                        base = 0;
                    }
                    fn_8009BD60(p);
                    if (p->mUnknown2910[3] == 0) {
                        p->mUnknown1008 = 1;
                    } else {
                        p->mUnknown1008 = 2;
                    }
                    p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4 = base;
                    p->mUnknown512.mUnknown14 = 6;
                    p->mUnknown512.mUnknown0 = 1.0f;
                    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 217, p, 1.0f);
                    p->mUnknown512.mUnknown14 = 0;
                    p->mFlags &= ~4;
                } else {
                    if ((p->mFlags & 4) || fn_801BE648(p->mpUnknown792) != 222) {
                        p->mFlags &= ~4;
                        if (p->mUnknown2910[3] == 0) {
                            p->mUnknown1008 = 1;
                        } else {
                            p->mUnknown1008 = 2;
                        }
                        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 222, p, 1.0f);
                    }
                    p->mUnknown512.mUnknown14 = 0;
                }
                return;
            }
            angle = -0x400000;
        } else {
            lbl_803EAD1C = 0;
        }
        result = fn_800DC080(p);
        if (result == 1 && p->mUnknown512.mUnknown15 != 1) {
            if (fn_801CFFD0(angle, -0x38E38E) <= 0x155554) {
                if (p->mUnknown2910[3] == 0) {
                    int facing = p->mMotion.mFacing & 0xFFFFFF;
                    if (facing >= 0x6E38E4 && facing <= 0xC38E38
                        && p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
                        target = 0x6AAAAB;
                    } else {
                        target = (angle + 0x38E38E) & 0xFFFFFF;
                    }
                } else {
                    int facing = p->mMotion.mFacing & 0xFFFFFF;
                    if ((facing < 0x11C71C || facing > 0xBC71C7)
                        && p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
                        target = 0x155555;
                    } else {
                        target = (angle - 0x38E38E) & 0xFFFFFF;
                    }
                }
                p->mUnknown512.mUnknown14 = 3;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown8 = target;
                p->mUnknown512.mUnknown0 = value;
            } else {
                p->mUnknown512.mUnknown14 = result;
                p->mUnknown512.mUnknown8 = angle;
                p->mUnknown512.mUnknown4 = angle;
                p->mUnknown512.mUnknown0 = value;
                if (p->mUnknown512.mUnknown15 != 1) {
                    fn_800C89F0(p, 0x400000, 2, 0, 1.0f);
                }
            }
        } else if (p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
            angle = -0x400000;
            if (p->mUnknown2910[3] == 0) {
                int facing = p->mMotion.mFacing & 0xFFFFFF;
                if (facing >= 0x6E38E4 && facing <= 0xC38E38
                    && p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
                    target = 0x6AAAAB;
                } else {
                    target = (angle + 0x38E38E) & 0xFFFFFF;
                }
            } else {
                int facing = p->mMotion.mFacing & 0xFFFFFF;
                if ((facing < 0x11C71C || facing > 0xBC71C7)
                    && p->mMotion.mUnknown28 <= fn_8016D9F4(p, 0.0f, 1.0f)) {
                    target = 0x155555;
                } else {
                    target = (angle - 0x38E38E) & 0xFFFFFF;
                }
            }
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown8 = target;
            p->mUnknown512.mUnknown0 = value;
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown0 = value;
            if (p->mUnknown512.mUnknown15 != 1) {
                fn_800C89F0(p, 0x400000, 2, 0, 1.0f);
            }
        }
    } else if (p->mFlags & 4) {
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown8 = dir;
        p->mUnknown512.mUnknown0 = value;
    }
}

extern "C" int fn_800DC080(Object_80039F5C *p)
{
    int result = 0;
    unsigned char flag;

    if (p->mIdBytes[3] == 1) {
        int mode = fn_800AD9B4();
        Object_800670B4 *pTeam = fn_80168708(p->mIdBytes[2]);
        if (!fn_801783AC(0) && fn_80137C48(p)
            && (p == fn_8016444C(pTeam)
                || ((p->mUnknown2914 == 1 || p->mUnknown2914 == 3) && fn_8011F2C4()
                    && (fn_801481B0() || !(p->mFlags & 0x400))))
            && (fn_8011F1CC() || fn_8011F1F4())
            && mode == 3 && p->mpState->mId != 1 && p->mUnknown512.mUnknown15 != 1) {
            if (!fn_800DBB74(p, &flag)) {
                if (!fn_801483F8()) {
                    result = 1;
                } else if (fn_801481B0() == 1) {
                    if (!(p->mFlags & 0x200000)) {
                        result = 1;
                    } else if (p->mMotion.mUnknown28 < lbl_803ECB08 * 0.4f) {
                        p->mFlags &= ~0x200000;
                        result = 1;
                    }
                } else {
                    p->mFlags |= 0x200000;
                }
            } else {
                result = flag == 0;
            }
        } else if (fn_801486A0() == 1 && p->mpState->mId == 51) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_800DC21C(Object_80039F5C *p)
{
    int result = 0;
    unsigned char flag;
    unsigned char shown;
    int mode = fn_800AD9B4();
    Object_800670B4 *pTeam = fn_80168708(p->mIdBytes[2]);

    if (!fn_801783AC(0) && fn_80137C48(p)
        && (p == fn_8016444C(pTeam)
            || ((p->mUnknown2914 == 1 || p->mUnknown2914 == 3) && fn_8011F2C4()
                && (fn_801481B0() || !(p->mFlags & 0x400))))
        && fn_8011F1CC() && mode == 3 && p->mpState->mId != 1 && p->mpState->mId != 91) {
        if (!fn_800DBB74(p, &flag)) {
            if (!fn_800DC080(p)) {
                result = 1;
            }
        } else {
            result = flag;
        }
    }
    if (result && p && !fn_800D0B90(p)) {
        fn_800CABF4(p, &shown, 0);
        if (shown) {
            fn_80156C78(21, 1);
        }
    }
    return result;
}

extern "C" int fn_800DC36C(List_800DC36C *pList, unsigned short key, void *pA,
                           Record_800DC36C *pRecords, Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *pBlock = fn_801BE60C(p->mpUnknown792, key);
    int side;
    int i;

    switch (phase) {
    case 0:
        if (p->mUnknown2910[3] == 0) {
            side = 1;
            fn_800ADB90(p, 5, 8, 1);
        } else {
            side = 0;
            fn_800ADB90(p, 5, 8, 0);
        }
        for (i = 0; i < pList->mCount; i++) {
            Object_800DC36C *pObject = pList->mEntries[i].mpUnknown4;
            if (pObject->mUnknown36 == side
                && fn_801CFFD0(pObject->mUnknown40, p->mUnknown512.mUnknown4) <= 0x400000) {
                break;
            }
        }
        fn_801BE760(p->mpUnknown792, key, 1);
        pBlock->mUnknown0 = fn_801BA2A8(pA, pRecords, pList->mEntries[i].mUnknown0,
                                        pList->mEntries[i].mUnknown2, key, p, 1.0f);
        pBlock->mUnknown4 = p->mMotion.mFacing;
        break;
    case 1:
        break;
    case 2:
        if (pBlock->mUnknown4 != p->mMotion.mFacing) {
            p->mpUnknown800[pBlock->mUnknown0].mUnknown12 =
                (p->mpUnknown800[pBlock->mUnknown0].mUnknown12 + (p->mMotion.mFacing - pBlock->mUnknown4))
                & 0xFFFFFF;
            pBlock->mUnknown4 = p->mMotion.mFacing;
        }
        fn_801BD81C(pRecords[pBlock->mUnknown0].mUnknown76, fn_801CFFA0(fn_800C495C(p, 1.0f)));
        if (fn_800A7EF4(p->mIdBytes[2]) == 2) {
            fn_801BD81C(pRecords[pBlock->mUnknown0].mUnknown76, fn_801CFFA0(2.0f));
        } else if (fn_800A7EF4(p->mIdBytes[2]) == 0) {
            fn_801BD81C(pRecords[pBlock->mUnknown0].mUnknown76, fn_801CFFA0(0.5f));
        }
        break;
    }
    return 0;
}

extern "C" void fn_800DC578(void)
{
    lbl_803EAD1C = 0;
}
