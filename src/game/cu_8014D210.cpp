#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "engine/cu_801C2EB4.h"
#include "game/fn_802372EC.h"

struct Record_8014F104 {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    char mUnknown12[40];
    char mUnknown52[4];
};

struct Block_8014F104 {
    char mUnknown0[0x20];
    Object_80039F5C *mpUnknown20;
    char mUnknown24[16];
    Record_8014F104 *mpUnknown34;
};

extern "C" {
Block_8014F104 *fn_8014F104(Class_80148A58 *p);
void fn_8014D024(unsigned short index);
void fn_8014F4D8(Class_80148A58 *p, Object_80039F5C *pPlayer, int kind, int value);
void fn_8017E46C(Object_80039F5C *p, int team, const char *pText, int value, int d);
Object_80039F5C *fn_8003AC84(int id);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
void fn_8017E17C(int slot, const char *pText0, const char *pText1, const char *pText2, int key);
extern const char lbl_802A0DDC[];
extern const char lbl_802A05C8[];
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pPlayer);
void fn_8003AB08(Object_80039F5C *pPlayer, int value);
void fn_80227538(float *pOut, int angle, float length);
float fn_80178A08(void);
float fn_80178A2C(void);
extern const float lbl_802A0DB8;
extern const float lbl_802A0DBC;
extern const float lbl_802A0DC0;
extern const float lbl_802A0DC4;
extern const float lbl_802A0DD8;

void fn_8014D210(Object_80039F5C *p, int kind, int value)
{
    unsigned short i;
    for (i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0 == p->mUnknown2908) {
            fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4 += value;
            break;
        }
    }
    fn_8014D024(i);
}

void fn_8014D298(int kind, int unused, const char *pText, int value, int addValue, int d, int addText)
{
    int credit = 0;
    Object_80039F5C *pFirst = 0;
    Object_80039F5C *pSecond = 0;
    int statA = 11;
    int statB = 11;
    switch (kind) {
    case 29:
        statA = 3;
        credit = 1;
        break;
    case 27:
    case 28:
    case 32:
    case 33:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 44:
    case 45:
    case 48:
    case 49:
    case 55:
    case 56:
    case 58:
    case 59:
    case 61:
    case 62:
    case 64:
    case 65:
    case 66:
    case 108:
        credit = 1;
        break;
    case 30:
    case 31:
        statA = 2;
        credit = 1;
        break;
    case 34:
    case 35:
    case 46:
    case 47:
    case 50:
    case 51:
    case 109:
    case 111:
        statA = 5;
        credit = 1;
        break;
    case 42:
    case 43:
    case 110:
        statA = 5;
        statB = 6;
        credit = 1;
        break;
    case 57:
    case 60:
    case 112:
        statA = 4;
        credit = 1;
        break;
    case 63:
    case 113:
        statA = 4;
        statB = 6;
        credit = 1;
        break;
    case 86:
    case 87:
    case 88:
    case 89:
        statA = 1;
        credit = 1;
        break;
    case 78:
    case 84:
    case 85:
    case 96:
    case 98:
    case 120: {
        Object_80039F5C *pBallPlayer = fn_80137B64();
        if (pBallPlayer) {
            if (pBallPlayer->mpState->mId == 16) {
                for (unsigned short i = 0; i <= 4; i++) {
                    if (!pFirst) {
                        pFirst = fn_80039F5C(0, i);
                        if (pBallPlayer->mpState->mUnknown3[0] != i && pFirst->mpState->mId != 17) {
                            pFirst = 0;
                        } else {
                            fn_8014F4D8(fn_80148A58(), pFirst, 0, 1);
                        }
                    } else if (!pSecond) {
                        pSecond = fn_80039F5C(0, i);
                        if (pBallPlayer->mpState->mUnknown3[0] != i && pSecond->mpState->mId != 17) {
                            pSecond = 0;
                        } else {
                            fn_8014F4D8(fn_80148A58(), pSecond, 0, 1);
                        }
                    } else {
                        break;
                    }
                }
            } else if (pBallPlayer->mUnknown560.mUnknown48) {
                pFirst = fn_8009BCE8(&pBallPlayer->mUnknown560.mUnknown48);
                fn_8014F4D8(fn_80148A58(), pFirst, 0, 1);
            }
        }
        fn_8014F104(fn_80148A58())->mpUnknown20 = pFirst;
        break;
    }
    }
    if (credit == 1) {
        pFirst = fn_80137B40();
        if (!pFirst) {
            pFirst = fn_80137B64();
        }
        if (statA != 11) {
            fn_8014F4D8(fn_80148A58(), pFirst, statA, 1);
        }
        if (statB != 11) {
            fn_8014F4D8(fn_80148A58(), pFirst, statB, 1);
        }
    }
    if (pFirst) {
        if (pSecond) {
            value /= 2;
        }
        if (addValue) {
            fn_8014D210(pFirst, kind, value);
        }
        if (addText) {
            fn_8017E46C(pFirst, pFirst->mIdBytes[2], pText, value, d);
        }
        if (pSecond) {
            if (addValue) {
                fn_8014D210(pSecond, kind, value);
            }
            if (addText) {
                fn_8017E46C(pSecond, pSecond->mIdBytes[2], pText, value, d);
            }
        }
    }
}

// Place one player at the center and the other five within the field bounds.
void PlaceSixPlayerFormation(void)
{
    unsigned int first = fn_802372EC(0, 6);
    float sectorWidth = lbl_802A0DB8;
    Object_80039F5C *pPlayer = fn_80039F5C(1, 0);
    fn_800EFE60(0, pPlayer->mpState, pPlayer);
    fn_8003AB08(pPlayer, 0);
    pPlayer->mMotion.mPos.mX = lbl_802A0DBC;
    pPlayer->mMotion.mPos.mY = lbl_802A0DBC;
    pPlayer->mUnknown512.mUnknown0 = lbl_802A0DC4;
    pPlayer->mUnknown512.mUnknown14 = 1;
    pPlayer->mUnknown512.mUnknown4 = pPlayer->mMotion.mFacing =
        pPlayer->mUnknown512.mUnknown8 = (first * 0x2AAAAA + 0xEAAAAB) & 0xFFFFFF;

    for (unsigned char i = 0; i <= 4; i++) {
        pPlayer = fn_80039F5C(0, i);
        fn_800EFE60(0, pPlayer->mpState, pPlayer);
        fn_8003AB08(pPlayer, 0);
        unsigned int sector = (i + first) % 6;
        float radius = fn_802372EC(0, 2) + lbl_802A0DD8;
        float degrees = sector * sectorWidth + fn_802372EC(0, (unsigned int)sectorWidth);
        fn_80227538(&pPlayer->mMotion.mPos.mX, (int)(degrees * lbl_802A0DC0), radius);
        pPlayer->mMotion.mPos.mX = pPlayer->mMotion.mPos.mX < -fn_80178A08() ? -fn_80178A08() :
            (pPlayer->mMotion.mPos.mX > fn_80178A08() ? fn_80178A08() : pPlayer->mMotion.mPos.mX);
        pPlayer->mMotion.mPos.mY = pPlayer->mMotion.mPos.mY < -fn_80178A2C() ? -fn_80178A2C() :
            (pPlayer->mMotion.mPos.mY > fn_80178A2C() ? fn_80178A2C() : pPlayer->mMotion.mPos.mY);
        pPlayer->mUnknown512.mUnknown0 = lbl_802A0DC4;
        pPlayer->mUnknown512.mUnknown14 = 1;
        pPlayer->mUnknown512.mUnknown4 = pPlayer->mMotion.mFacing =
            pPlayer->mUnknown512.mUnknown8 = ((int)(degrees * lbl_802A0DC0) + 0x800000) & 0xFFFFFF;
    }
}

// Display the six records in their current score order.
void RefreshSixPlayerScoreRows(void *p)
{
    for (unsigned char i = 0; i <= 5; i++) {
        char name[24];
        char score[16];
        fn_801C2EB4(name, fn_8003AC84(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0)->mUnknown2927 + 21);
        fn_801C2E18(score, lbl_802A0DDC, fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4);
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8 != 255) {
            fn_8014F104(fn_80148A58());
        }
        fn_8017E17C(i + 1, name, score, lbl_802A05C8,
                    fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8);
    }
}
}
