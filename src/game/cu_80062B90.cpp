#include "game/Object_8007A334.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802372EC.h"

struct Name_80063330 {
    Params_80005284 *mUnknown0;
};

struct Record_80062B90 {
    short mUnknown0[2];
    short mUnknown4[2];
};

extern "C" {
int fn_80183360(void);
void fn_80079974(int, short *, short *);
float fn_80237260(int stream);
void fn_80079898(int, int, int);
void fn_80079A50(int *, int);
void fn_80079B2C(int *, int);
void fn_801834DC();
void fn_80183368(int, int);
Object_8007A334 *fn_80182DBC(void);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
void fn_80188CBC(int, int, int, int, char *);
int fn_800788A4();
void fn_800788E8(int);
int fn_801801B4();
int fn_801801BC();
void fn_80077F24();
void fn_8000FCD4(int a);
void fn_8000473C(int, int);
int fn_80078934();
int fn_801787DC(int a);
}

static Record_80062B90 *lbl_803EA610 = 0;
static int lbl_803EA614 = -1;
static int lbl_803EA618 = -1;
static int lbl_803EA61C = 0;
static int lbl_802D4ED8[33] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 32, 30, 31,
    34,
};

extern "C" Record_80062B90 *fn_80062B90(int index)
{
    return &lbl_803EA610[index];
}

extern "C" int fn_80062BA0(int index)
{
    Record_80062B90 *p = fn_80062B90(index);
    return p->mUnknown4[1] != 0 || p->mUnknown4[0] != 0;
}

extern "C" int fn_80062BE4(int index)
{
    int result;
    if (index == lbl_803EA614) {
        result = fn_80183360();
    } else {
        result = lbl_802D4ED8[index];
    }
    return result;
}

extern "C" int fn_80062C24(int index)
{
    int result = -1;
    if (fn_80062BA0(index)) {
        Record_80062B90 *p = fn_80062B90(index);
        if (p->mUnknown4[1] > p->mUnknown4[0]) {
            result = p->mUnknown0[1];
        } else {
            result = p->mUnknown0[0];
        }
    }
    return result;
}

extern "C" int fn_80062C84(int index)
{
    int count = 16;
    int result = 1;
    if (index == 31) {
        result = -1;
    } else {
        while (index >= count) {
            index -= count;
            count /= 2;
            result++;
        }
    }
    return result;
}

extern "C" int fn_80062CC8(int *pSide)
{
    int i;
    *pSide = 2;
    for (i = 0; i <= 31; i++) {
        int played = fn_80062BA0(i);
        if (!played) {
            Record_80062B90 *p = fn_80062B90(i);
            if (p->mUnknown0[1] == lbl_803EA614) {
                *pSide = 1;
                break;
            }
            if (p->mUnknown0[0] == lbl_803EA614) {
                *pSide = 0;
                break;
            }
        }
    }
    return i;
}

extern "C" void fn_80062D54()
{
    int i;
    for (i = 0; i <= 31; i++) {
        Record_80062B90 *p = fn_80062B90(i);
        if (i <= 15) {
            p->mUnknown0[1] = i * 2;
            p->mUnknown0[0] = i * 2 + 1;
        } else if (i == 31) {
            p->mUnknown0[0] = 32;
            p->mUnknown0[1] = fn_80062C24(30);
        } else {
            int j;
            int base = i * 2 - 32;
            for (j = 0; j <= 1; j++) {
                int k = !j;
                p->mUnknown0[k] = fn_80062C24(base + j);
            }
        }
        fn_80079974(i, &p->mUnknown4[1], &p->mUnknown4[0]);
    }
}

extern "C" void fn_80062E34(int index, short *score)
{
    int count = 0;
    int side = 1;
    score[0] = 0;
    score[1] = 0;
    while (score[0] <= 35 && score[1] <= 35 && count <= 99) {
        if (fn_80237260(1) < 0.3f) {
            score[side] += 6;
            if (score[side] <= 35) {
                if (fn_80237260(1) < 0.75f) {
                    score[side] += 2;
                } else if (fn_80237260(1) < 0.5f) {
                    score[side] += 1;
                }
            }
        } else if (fn_80237260(1) < 0.05f) {
            score[side] += 2;
        }
        side ^= 1;
        count++;
    }
    if (count > 99) {
        char winner = fn_802372EC(1, 2);
        score[winner] = 36;
    }
}

extern "C" void fn_80062F94()
{
    short score[2];
    int round = fn_80062C84(lbl_803EA618);
    int i;
    for (i = 0; i <= 30; i++) {
        if (fn_80062C84(i) == round && !fn_80062BA0(i)) {
            Record_80062B90 *p = fn_80062B90(i);
            fn_80062E34(i, score);
            p->mUnknown4[0] = score[0];
            p->mUnknown4[1] = score[1];
            fn_80079898(i, score[1], score[0]);
        }
    }
}

extern "C" void fn_80063034()
{
    lbl_803EA610 = (Record_80062B90 *)fn_801D2B7C(256, 0, 0);
    fn_801C1F94(lbl_803EA610, 0, 256);
    fn_80062D54();
}

extern "C" void fn_80063078()
{
    fn_801D2BD0(lbl_803EA610);
    lbl_803EA610 = 0;
}

extern "C" void fn_800630A4()
{
    int i;
    for (i = 0; i <= 2; i++) {
        int j;
        for (j = 0; j < 32; j++) {
            int k = fn_802372EC(1, 32);
            int value = lbl_802D4ED8[j];
            lbl_802D4ED8[j] = lbl_802D4ED8[k];
            lbl_802D4ED8[k] = value;
        }
    }
}

extern "C" void fn_80063118()
{
    fn_80079A50(lbl_802D4ED8, 32);
}

extern "C" void fn_80063144()
{
    fn_80079B2C(lbl_802D4ED8, 32);
}

extern "C" void fn_80063170(int *pIndex)
{
    int i;
    fn_801834DC();
    fn_80183368(1, 1023);
    if (fn_80084438(fn_80182DBC()) == 0) {
        char values[3];
        values[0] = fn_800841AC(fn_80182DBC());
        values[1] = fn_800841D8(fn_80182DBC());
        values[2] = fn_80084204(fn_80182DBC());
        fn_80188CBC(0, 4, fn_80084158(fn_80182DBC()), 172, values);
    }
    lbl_803EA614 = fn_800788A4();
    if (lbl_803EA614 == -1) {
        lbl_803EA614 = fn_802372EC(1, 32);
        fn_800788E8(lbl_803EA614);
        fn_800630A4();
        fn_80063118();
    } else {
        fn_80063144();
    }
    fn_80063034();
    i = 31;
    do {
        Record_80062B90 *p = fn_80062B90(i);
        if (p != 0 && (p->mUnknown0[0] == lbl_803EA614 || p->mUnknown0[1] == lbl_803EA614)) {
            *pIndex = i;
            break;
        }
    } while (--i >= 0);
}

extern "C" void fn_80063278(int value)
{
    int team = -1;
    int active = 0;
    if (fn_801801B4() == 1) {
        active = fn_801801BC() == 1;
    }
    if (active) {
        char opponent;
        lbl_803EA618 = fn_80062CC8(&lbl_803EA61C);
        opponent = fn_80062B90(lbl_803EA618)->mUnknown0[!lbl_803EA61C];
        team = fn_80062BE4(opponent);
    }
    fn_80063078();
    fn_80077F24();
    fn_801834DC();
    if (active) {
        fn_8000FCD4(value);
        fn_8000473C(team, 11);
    }
}

extern "C" void fn_80063330(int index, int *pIdA, int *pIdB, Name_80063330 nameA, Name_80063330 nameB,
                            int *pScoreA, int *pScoreB, int *pResult)
{
    int *ids[2];
    Name_80063330 names[2];
    Record_80062B90 *p;
    int i;
    char name[24];

    names[0] = nameB;
    ids[0] = pIdB;
    ids[1] = pIdA;
    names[1] = nameA;
    p = fn_80062B90(index);
    for (i = 0; i < 2; i++) {
        int team = p->mUnknown0[i];
        if (team == -1) {
            *ids[i] = team;
            fn_801C3284(names[i].mUnknown0->mpText, "TBD", names[i].mUnknown0->mLength);
        } else {
            *ids[i] = fn_80062BE4(team);
            Object_8007A334 object;
            fn_80083E40(&object, 0, 0x54415453);
            fn_80084034(&object, *ids[i], 0);
            fn_80083F88(&object, name, 18);
            fn_801C3284(names[i].mUnknown0->mpText, name, names[i].mUnknown0->mLength);
            fn_80083F68(&object);
        }
    }
    *pScoreA = p->mUnknown4[1];
    *pScoreB = p->mUnknown4[0];
    if (!fn_80062BA0(index)) {
        *pResult = -1;
    } else if (*pScoreA > *pScoreB) {
        *pResult = 1;
    } else {
        *pResult = 0;
    }
}

extern "C" void fn_800634B4(int *p)
{
    *p = fn_80078934();
}

extern "C" int fn_800634E4()
{
    return lbl_803EA618 == 31;
}

extern "C" void fn_800634F8()
{
    short score[2];
    if (lbl_803EA61C == 1) {
        score[1] = fn_801787DC(1);
        score[0] = fn_801787DC(0);
    } else {
        score[0] = fn_801787DC(1);
        score[1] = fn_801787DC(0);
    }
    fn_80079898(lbl_803EA618, score[1], score[0]);
    fn_80063034();
    fn_80062F94();
    fn_80063078();
}

union Word_80063578 {
    int mValue;
    int *mpValue;
};

struct Params_80063578 {
    Word_80063578 mUnknown0;
    int *mpUnknown4;
    int *mpUnknown8;
    Name_80063330 mUnknown12;
    Name_80063330 mUnknown16;
    int *mpUnknown20;
    int *mpUnknown24;
    int *mpUnknown28;
};

extern "C" int fn_80063578(unsigned int id, Params_80063578 *p)
{
    switch (id) {
    case 0x80000002:
        fn_80063170(p->mUnknown0.mpValue);
        break;
    case 0x80000003:
        fn_80063278(p->mUnknown0.mValue);
        break;
    case 0x80000001:
        fn_80063330(p->mUnknown0.mValue, p->mpUnknown4, p->mpUnknown8, p->mUnknown12, p->mUnknown16,
                    p->mpUnknown20, p->mpUnknown24, p->mpUnknown28);
        break;
    case 0x80000004:
        fn_800634B4(p->mUnknown0.mpValue);
        break;
    default:
        return 0;
    }
    return 1;
}
