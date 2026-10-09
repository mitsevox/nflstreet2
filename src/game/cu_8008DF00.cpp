#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801BE60C.h"

extern "C" {
int fn_800C4B6C(Object_80039F5C *p);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
int fn_800DC080(Object_80039F5C *p);
int fn_80178320(void);
float fn_801BE7C8(void *p, unsigned short key);
int fn_801CFFD0(int a, int b);
}

#define MAX(a, b) ((a) >= (b) ? (a) : (b))

extern float lbl_803ECB0C;
extern float lbl_803ECB10;

/* fn_8008E424, fn_8008E510, fn_8008E598, fn_8008E6D8, fn_8008E6FC,
   fn_8008E858 and fn_8008E8D8 are words of the .data table 0x80297D68, which
   fn_8008E978 indexes by the byte +14 of the record at +528. The others are
   called from fn_8008E598. The 16-bit keys are the values fn_801BE648 returns
   and fn_801BE068 takes. */

extern "C" int fn_8008DF00(Object_80039F5C *p, int key)
{
    Object_8016D8B0 *pNext = &p->mUnknown528;
    Object_800B26B0 *pMotion = &p->mMotion;
    int result = 0;

    if (key == 74 && p->mUnknown528.mUnknown0 != 0.0f
        && fn_801CFFD0(pMotion->mFacing, pNext->mUnknown8) > 0x5FFFFF) {
        int diff = fn_801CFFD0(pMotion->mUnknown32, pNext->mUnknown4);
        unsigned char team = p->mIdBytes[2];

        if (diff > 0x755555 && team == fn_80178320() && pMotion->mUnknown28 >= 0.05f
            && fn_800C4B6C(p)) {
            result = 1;
        }
        if (diff <= 0xAAAA9 && team == fn_80178320() && fn_800C4B6C(p)) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_8008DFF8(Object_80039F5C *p, unsigned short key)
{
    int result = 0;

    if (p->mIdBytes[3] == 1 && p->mpState->mId != 61) {
        result = fn_8008DF00(p, key);
    }
    return result;
}

extern "C" int fn_8008E040(Object_80039F5C *p, int diff, unsigned short *pKey)
{
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;
    int result = 0;

    if (diff <= 0x1C71C6 || p->mUnknown512.mUnknown0 == 0.0f) {
        *pKey = 74;
        pNext->mUnknown14 = 1;
        pNext->mUnknown4 = pCur->mUnknown4;
        pNext->mUnknown8 = pCur->mUnknown4;
        p->mUnknown528.mUnknown0 = p->mUnknown512.mUnknown0;
    } else {
        if (diff <= 0x56C16B && pCur->mUnknown4 > 0x800000) {
            *pKey = 84;
            if (fn_801BE648(p->mpUnknown792) == 84 && fn_801BE7C8(p->mpUnknown792, 84) != 0.0f) {
                pCur->mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown0 = 0.0f;
            }
            if (fn_801CFFD0(pCur->mUnknown4, pNext->mUnknown4) > 0x400000) {
                result = 1;
            }
            pNext->mUnknown14 = pCur->mUnknown14;
            pNext->mUnknown4 = pCur->mUnknown4;
            pNext->mUnknown8 = pCur->mUnknown8;
            pNext->mUnknown0 = pCur->mUnknown0;
        } else {
            *pKey = 74;
            pNext->mUnknown14 = pCur->mUnknown14;
            pNext->mUnknown4 = pCur->mUnknown4;
            pNext->mUnknown8 = pCur->mUnknown8;
            pNext->mUnknown0 = pCur->mUnknown0;
        }
    }
    return result;
}

extern "C" int fn_8008E188(Object_80039F5C *p, int flag)
{
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;
    int handled = 0;
    int key = 74;
    int diff;

    pCur->mUnknown8 &= 0xFFFFFF;
    pCur->mUnknown4 &= 0xFFFFFF;
    if (flag) {
        pCur->mUnknown8 = 0xC00000;
    }
    diff = fn_801CFFD0(pCur->mUnknown4, pCur->mUnknown8);

    if (fn_80137B40() != p && diff > 0x2E38E2 && p->mUnknown512.mUnknown0 > 0.0f) {
        if (diff <= 0x56C16B) {
            if (flag || p->mUnknown492 <= lbl_803ECB0C) {
                if (p->mIdBytes[2] == fn_80178320() || flag) {
                    key = 160;
                    p->mUnknown528.mUnknown0 = MAX(p->mUnknown512.mUnknown0, lbl_803ECB0C * 0.18f / lbl_803ECB0C);
                } else {
                    key = 73;
                    p->mUnknown528.mUnknown0 = MAX(p->mUnknown512.mUnknown0, lbl_803ECB0C * 0.4f / lbl_803ECB0C);
                }
                handled = 1;
                pNext->mUnknown14 = pCur->mUnknown14;
                pNext->mUnknown8 = pCur->mUnknown8;
                pNext->mUnknown4 = pCur->mUnknown4;
            }
        } else if (diff <= 0x71C71B && p->mIdBytes[2] == fn_80178320()) {
            if (flag || p->mUnknown492 <= lbl_803ECB10) {
                int offset;
                fn_800C89F0(p, pCur->mUnknown8, 2, 0, 1.0f);
                key = 159;
                offset = diff - 0x400000;
                if (((pCur->mUnknown8 - pCur->mUnknown4) & 0xFFFFFF) <= 0x800000) {
                    key = 157;
                    offset = -offset;
                }
                p->mUnknown528.mUnknown0 = MAX(p->mUnknown512.mUnknown0, lbl_803ECB0C * 0.18f / lbl_803ECB0C);
                handled = 1;
                pNext->mUnknown14 = pCur->mUnknown14;
                pNext->mUnknown8 = (pCur->mUnknown8 + offset) & 0xFFFFFF;
                pNext->mUnknown4 = pCur->mUnknown4;
            }
        } else if (flag || p->mUnknown492 <= lbl_803ECB10) {
            key = 74;
            handled = 1;
            pNext->mUnknown0 = pCur->mUnknown0;
            pNext->mUnknown14 = pCur->mUnknown14;
            pNext->mUnknown8 = pCur->mUnknown8;
            pNext->mUnknown4 = pCur->mUnknown4;
        }
    }

    if (!handled) {
        if (pCur->mUnknown8 != pCur->mUnknown4) {
            fn_800C89F0(p, pCur->mUnknown8, 2, 0, 1.0f);
        }
        key = 74;
        pNext->mUnknown14 = 1;
        pNext->mUnknown4 = pCur->mUnknown4;
        pNext->mUnknown8 = pCur->mUnknown4;
        pNext->mUnknown0 = pCur->mUnknown0;
    }
    return key;
}

extern "C" void fn_8008E424(Object_80039F5C *p)
{
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;
    unsigned short key;

    p->mUnknown528.mUnknown0 = p->mUnknown512.mUnknown0;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown8;
    pNext->mUnknown14 = pCur->mUnknown14;

    key = fn_801BE648(p->mpUnknown792);
    switch (key) {
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 59:
    case 60:
    case 73:
    case 84:
    case 100:
    case 106:
    case 107:
    case 160:
        key = 74;
        break;
    }
    if (fn_801BE648(p->mpUnknown792) != key) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, p, 1.0f);
    }
}

extern "C" void fn_8008E510(Object_80039F5C *p)
{
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;

    pNext->mUnknown14 = pCur->mUnknown14;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown4;
    p->mUnknown528.mUnknown0 = p->mUnknown512.mUnknown0;

    fn_801BE648(p->mpUnknown792);
    if (fn_801BE648(p->mpUnknown792) != 74) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, p, 1.0f);
    }
}

extern "C" void fn_8008E8D8(Object_80039F5C *p);

extern "C" void fn_8008E598(Object_80039F5C *p)
{
    int changed = 0;
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;
    unsigned short key = fn_801BE648(p->mpUnknown792);
    int diff = fn_801CFFD0(pCur->mUnknown4, pCur->mUnknown8);

    if (p->mIdBytes[3] == 2) {
        pNext->mUnknown14 = 1;
        key = 74;
        pNext->mUnknown4 = pCur->mUnknown4;
        pNext->mUnknown8 = pCur->mUnknown4;
        p->mUnknown528.mUnknown0 = p->mUnknown512.mUnknown0;
    } else if (fn_800DC080(p)) {
        changed = fn_8008E040(p, diff, &key);
    } else {
        int flag = pCur->mUnknown15 == 4 || pCur->mUnknown15 == 5;
        if (flag && p->mUnknown512.mUnknown0 == 0.0f) {
            fn_8008E8D8(p);
            return;
        }
        key = fn_8008E188(p, flag);
    }

    if (fn_8008DFF8(p, key) == 0) {
        if (fn_801BE648(p->mpUnknown792) != key || changed) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, p, 1.0f);
        }
    }
}

extern "C" void fn_8008E6D8(Object_80039F5C *p)
{
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;

    pNext->mUnknown14 = pCur->mUnknown14;
    pNext->mUnknown4 = pCur->mUnknown4;
    p->mUnknown528.mUnknown0 = p->mUnknown512.mUnknown0;
}

extern "C" void fn_8008E6FC(Object_80039F5C *p)
{
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;
    unsigned short key = fn_801BE648(p->mpUnknown792);

    switch (key) {
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 59:
    case 60:
    case 106:
    case 107:
        if (p->mUnknown1032 != 4) {
            key = 74;
        }
        break;
    case 25:
    case 56:
    case 61:
    case 79:
        if (p->mUnknown1032 != 5) {
            key = 74;
        }
        break;
    case 62:
    case 63:
    case 66:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
    case 123:
    case 124:
    case 125:
    case 130:
    case 131:
    case 146:
    case 147:
    case 148:
    case 149:
    case 150:
    case 151:
    case 161:
    case 241:
        key = 74;
        break;
    default:
        key = 74;
        break;
    }

    pNext->mUnknown0 = pCur->mUnknown0;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown8;
    pNext->mUnknown14 = pCur->mUnknown14;
    if (fn_801BE648(p->mpUnknown792) != key) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, p, 1.0f);
    }
}

extern "C" void fn_8008E858(Object_80039F5C *p)
{
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;

    pNext->mUnknown14 = pCur->mUnknown14;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown8;
    p->mUnknown528.mUnknown0 = p->mUnknown512.mUnknown0;

    if (fn_801BE648(p->mpUnknown792) != 74) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, p, 1.0f);
    }
}

extern "C" void fn_8008E8D8(Object_80039F5C *p)
{
    Object_8016D8B0 *pCur = &p->mUnknown512;
    Object_8016D8B0 *pNext = &p->mUnknown528;

    p->mUnknown528.mUnknown0 = p->mUnknown512.mUnknown0;
    pNext->mUnknown4 = pCur->mUnknown4;
    pNext->mUnknown8 = pCur->mUnknown8;
    pNext->mUnknown14 = pCur->mUnknown14;

    switch (p->mIdBytes[3]) {
    case 1:
    case 2:
        if (fn_801BE648(p->mpUnknown792) != 100) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 100, p, 1.0f);
        }
        break;
    default:
        fn_8008E424(p);
        break;
    }
}
