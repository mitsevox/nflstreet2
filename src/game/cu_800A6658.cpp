#include "game/Object_80039F5C.h"
#include "game/Block_800A70F4.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8007A334.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_80238174.h"
#include "game/fn_800670B4.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_800B65A0.h"
#include "game/cu_80067C10.h"

struct Record_800B49EC;

extern "C" {
int fn_801787DC(int team);
int fn_801486A0(void);
int fn_80178308(void);
float fn_80178A2C(void);
int fn_8011F37C(void);
int fn_8011F1CC(void);
int fn_8011F1A4(void);
void *fn_8023816C(void *pHandle);
void fn_801476C8(Object_80039F5C *p);
void fn_800A8F70(void);
void fn_800940D8(unsigned short index, unsigned char value);
void fn_800A92E4(void);
void fn_800A636C(int team, Object_80039F5C **ppOut);
void fn_80146114(Object_80146094 *p);
void fn_80147840(Object_8003DEC4 *p);
void fn_801460FC(Object_80146094 *p, float a, float b, float c);
int fn_80178320(void);
int fn_8007C7E8(Object_8007A334 *pCursor, int key, int *pResult);
void fn_8007C84C(Object_8007A334 *pCursor, Block_800A70F4 *pOut);
void fn_800A6B6C(int team);
void fn_800A6C10(int team);
void fn_800A7A0C(int team);
void fn_800A65BC(void);
int fn_800A8408(int team);
int fn_800A8444(int team);
void fn_800A61E8(int value);
int fn_80178348(void);
float fn_800D3F2C(int team);
void fn_8017DE54(int a, float t, int b, int direct);
int fn_800A6590(int value);
void fn_800AE798(int index, int team);
void fn_800AE7F0(int index, int team, Object_80039F5C *p);
void fn_800A7514(int team);
void fn_800AE750(int index, int team);
void fn_8017DA9C(int team);
void fn_80156C78(int id, int value);
void fn_800A9384(int mode);
void fn_80073210(int frames);
void fn_800D4164(int side, float t, int arg);
void fn_800A6D5C(int team);
int fn_80156704(void);
Object_80039F5C *fn_80039FE8(int team, int a, unsigned char n);
void fn_8010B1FC(Object_80039F5C *p, int a, int b);
void fn_80168908(int team, unsigned int index);
void fn_80164940(int team);
void fn_800B0DA4(void);
void fn_800AEEDC(int team);
void fn_8011F3A8(void);
void fn_8003A3F4(int a, int team);
void fn_8009FFD4(void);
Object_800670B4 *fn_80168708(int team);
void fn_80164430(Object_800670B4 *pObject, unsigned char index, unsigned char *pA, unsigned char *pB);
void fn_800B49EC(Record_800B49EC *pDst, const Record_800B49EC *pSrc);
void fn_800B4798(short *pRatings, int team, int index, float *pOut);

extern Block_800A70F4 *lbl_803EC954[2];
extern int lbl_803EC95C;
extern unsigned char lbl_803EAA4D;
extern unsigned char lbl_803EAA4F;
extern unsigned char lbl_803EAA50;
extern unsigned char lbl_803EAA51;
extern int lbl_802D7EFC[][3];
extern void *lbl_803EB688;
extern Object_80039F5C *lbl_8030F404[2][2];
extern void (*lbl_803EAA1C[2])(int team);
extern void (*lbl_803EAA2C[2])(int team);
extern float lbl_803EAA54;
extern float lbl_803EAA58;
extern float lbl_803EAA5C;
extern float lbl_803EAA60;
extern float lbl_803EAA64;
extern float lbl_803EAA68;
extern float lbl_803EAA6C;
extern float lbl_803EAA70;
extern float lbl_803EAA74;
extern float lbl_803EAA78;
extern float lbl_803EAA7C;
extern float lbl_803EAA80;
float fn_80237260(int stream);

extern int lbl_803EAA3C[2];
}

extern "C" unsigned char fn_800A6658(int team)
{
    int other = team == 0;
    int lead = fn_801787DC(team) - fn_801787DC(other);
    unsigned char level;
    signed char count;
    int step;

    for (level = 0; level <= 1 && lead <= lbl_803EAA3C[level]; level++) {
    }
    count = level + 1;
    step = 1;
    if (fn_80237260(0) < 0.5f) {
        step = -1;
    }
    while (fn_80237260(0) < 0.3f) {
        count += step;
    }
    if (count <= 0) {
        count = 1;
    } else if (count > 3) {
        count = 3;
    }
    return count;
}

extern "C" void fn_800A680C(int team)
{
    Object_80039F5C *pair[2];
    unsigned char i;
    Object_8003DEC4 *pObject;

    fn_800A636C(team, pair);
    if (pair[0] == lbl_8030F404[team][1] || pair[1] == lbl_8030F404[team][0]) {
        Object_80039F5C *pSwap = pair[1];

        pair[1] = pair[0];
        pair[0] = pSwap;
    }
    for (i = 0; i <= 1; i++) {
        if (lbl_8030F404[team][i] != pair[i]) {
            if (lbl_8030F404[team][i] != 0) {
                pObject = (Object_8003DEC4 *)lbl_8030F404[team][i]->mpUnknown4;
                fn_80146114(&pObject->mUnknown5188);
                fn_80147840(pObject);
            }
            lbl_8030F404[team][i] = pair[i];
            if (lbl_8030F404[team][i] != 0) {
                pObject = (Object_8003DEC4 *)lbl_8030F404[team][i]->mpUnknown4;
                fn_801460FC(&pObject->mUnknown5188, 20.0f, 20.0f, 20.0f);
            }
        }
    }
    if (team == fn_80178320()) {
        Object_8007A334 cursor;

        fn_8007A308(&cursor, 'KRBG', 'DIBG');
        if (fn_8007C7E8(&cursor, lbl_803EC954[team]->mUnknown4, 0)) {
            fn_800A6B6C(team);
            fn_8007C84C(&cursor, lbl_803EC954[team]);
            lbl_803EC954[team]->mUnknown10 = 10000;
            lbl_803EAA1C[lbl_803EC954[team]->mUnknown8](team);
        } else {
            fn_800A7A0C(team);
        }
        fn_8007A3C4(&cursor);
    }
    fn_800A65BC();
}

extern "C" void fn_800A69BC(int team)
{
    Object_80039F5C *pair[2];
    unsigned char i;
    Object_8003DEC4 *pObject;

    fn_800A636C(team, pair);
    if (pair[0] == lbl_8030F404[team][1] || pair[1] == lbl_8030F404[team][0]) {
        Object_80039F5C *pSwap = pair[1];

        pair[1] = pair[0];
        pair[0] = pSwap;
    }
    for (i = 0; i <= 1; i++) {
        if (lbl_8030F404[team][i] != pair[i]) {
            if (lbl_8030F404[team][i] != 0) {
                pObject = (Object_8003DEC4 *)lbl_8030F404[team][i]->mpUnknown4;
                fn_80146114(&pObject->mUnknown5188);
                fn_80147840(pObject);
            }
            lbl_8030F404[team][i] = pair[i];
            if (lbl_8030F404[team][i] != 0) {
                pObject = (Object_8003DEC4 *)lbl_8030F404[team][i]->mpUnknown4;
                fn_801460FC(&pObject->mUnknown5188, 20.0f, 20.0f, 20.0f);
            }
        }
    }
    if (team == fn_80178308()) {
        Object_8007A334 cursor;

        fn_8007A308(&cursor, 'KRBG', 'DIBG');
        if (fn_8007C7E8(&cursor, lbl_803EC954[team]->mUnknown4, 0)) {
            fn_800A6C10(team);
            fn_8007C84C(&cursor, lbl_803EC954[team]);
            lbl_803EC954[team]->mUnknown10 = 10000;
            lbl_803EAA1C[lbl_803EC954[team]->mUnknown8](team);
        } else {
            fn_800A7A0C(team);
        }
        fn_8007A3C4(&cursor);
    }
    fn_800A65BC();
}

extern "C" int fn_800A6DD0(int team)
{
    int result = 8;
    int allowed = 1;

    if (fn_801486A0() == 4) {
        allowed = 0;
    }
    if (team == fn_80178308()) {
        if (fn_80178A2C() - fn_80177FE0().mY < 10.0f) {
            if (allowed && fn_8011F37C()) {
                result = 5;
            } else if (fn_8011F1CC()) {
                result = 4;
            } else if (fn_8011F1A4()) {
                result = 3;
            }
        } else if (allowed && fn_8011F37C()) {
            result = 2;
        } else if (fn_8011F1CC()) {
            result = 1;
        } else if (fn_8011F1A4()) {
            result = 0;
        }
    } else if (fn_8011F1CC()) {
        result = 7;
    } else if (fn_8011F1A4()) {
        result = 6;
    }
    return result;
}

extern "C" void fn_800A6F04(int team)
{
    if (fn_800A8444(team)) {
        Object_80039F5C *pair[2];
        unsigned char i;

        fn_800A636C(team, pair);
        for (i = 0; i <= 1; i++) {
            if (pair[i] != 0) {
                switch (fn_800A8408(team)) {
                case 0:
                    pair[i]->mRatings[0] = lbl_803EAA5C * 255.0f;
                    pair[i]->mRatings[1] = lbl_803EAA64 * 255.0f;
                    pair[i]->mRatings[2] = lbl_803EAA68 * 255.0f;
                    pair[i]->mRatings[3] = lbl_803EAA58 * 255.0f;
                    pair[i]->mRatings[4] = lbl_803EAA54 * 255.0f;
                    pair[i]->mRatings[6] = lbl_803EAA60 * 255.0f;
                    pair[i]->mRatings[7] = lbl_803EAA6C * 255.0f;
                    break;
                case 1:
                    pair[i]->mRatings[0] = lbl_803EAA78 * 255.0f;
                    pair[i]->mRatings[4] = lbl_803EAA70 * 255.0f;
                    pair[i]->mRatings[8] = lbl_803EAA74 * 255.0f;
                    pair[i]->mRatings[5] = lbl_803EAA7C * 255.0f;
                    pair[i]->mRatings[9] = lbl_803EAA80 * 255.0f;
                    break;
                }
            }
        }
    }
}

extern "C" void fn_800A70F4(void)
{
    unsigned char team;

    for (team = 0; team <= 1; team++) {
        void *pHandle = fn_80238174(0, (void **)&lbl_803EC954[team], sizeof(Block_800A70F4), 0, 'gbrk' + team);
        Block_800A70F4 *pBlock = (Block_800A70F4 *)fn_8023816C(pHandle);
        unsigned int count;
        unsigned short index;
        unsigned char i;

        pBlock->mUnknown0 = 0;
        pBlock->mUnknown8 = 3;
        pBlock->mUnknownC = -1;
        for (i = 0; i <= 9; i++) {
            pBlock->mUnknown24[i] = -1;
            pBlock->mUnknown38[i] = -1;
        }
        pBlock->mUnknown58 = 1.0f;
        pBlock->mUnknown5C = 0;
        pBlock->mUnknown60 = 0;
        pBlock->mUnknown64 = 0;
        pBlock->mUnknown54 = 0;
        pBlock->mUnknown68 = 0;
        pBlock->mUnknown6C = 0;
        for (i = 0; i <= 10; i++) {
            pBlock->mUnknown74[i] = 1;
        }
        pBlock->mUnknownA0 = 0;
        count = fn_80178D18(team);
        for (index = 0; index < count; index++) {
            fn_801476C8(fn_80039F5C(team, index));
        }
        fn_802381E0(pHandle);
    }
    lbl_803EC95C = -1;
    lbl_803EAA4D = 0;
    lbl_803EAA50 = 0;
    lbl_803EAA51 = 0;
    fn_800A8F70();
    for (team = 0; team <= 1; team++) {
        fn_800940D8(lbl_802D7EFC[team][0], 1);
    }
    fn_800A92E4();
}

extern "C" void fn_800A72B4(void)
{
    Object_8007A334 cursor;
    unsigned char team;

    if (lbl_803EAA4D != 0) {
        fn_800A61E8(1);
    }
    lbl_803EAA4D = 0;
    lbl_803EAA4F = 0;
    for (team = 0; team <= 1; team++) {
        if (lbl_803EC954[team]->mUnknown68 == 2) {
            lbl_803EC954[team]->mUnknown68 = 1;
        }
        if (lbl_803EC954[team]->mUnknown68 == 1) {
            if (lbl_803EC954[team]->mUnknown10 == 0) {
                if (fn_80178308() != fn_80178348()) {
                    fn_800A7A0C(team);
                }
            } else if (lbl_803EC954[team]->mUnknown54 == 0) {
                fn_800A7A0C(team);
            } else {
                fn_8017DE54(team, fn_800D3F2C(team), 0, 0);
            }
        }
        if ((lbl_803EC954[team]->mUnknown6C == 1 || lbl_803EC954[team]->mUnknown6C == 2)
            && ((lbl_803EC954[team]->mUnknown8 == 1 && team == fn_80178308())
                || (lbl_803EC954[team]->mUnknown8 == 0 && team == fn_80178320()))
            && lbl_803EC954[team]->mUnknown1C != 0) {
            fn_8007A308(&cursor, 'KRBG', 'DIBG');
            if (fn_8007C7E8(&cursor, lbl_803EC954[team]->mUnknown4, 0)) {
                fn_800AE798(fn_800A6590(fn_800A8408(team)), team);
                if (lbl_803EC954[team]->mUnknown68 != 0) {
                    lbl_803EAA2C[lbl_803EC954[team]->mUnknown8](team);
                }
                fn_8007C84C(&cursor, lbl_803EC954[team]);
                lbl_803EC954[team]->mUnknown10 = 10000;
                lbl_803EC954[team]->mUnknown58 = 1.0f;
                lbl_803EC954[team]->mUnknown64 = 0;
                if (lbl_803EC954[team]->mUnknown68 != 0) {
                    fn_800A7514(team);
                }
            } else {
                fn_800A7A0C(team);
            }
            fn_8007A3C4(&cursor);
            fn_8017DE54(team, fn_800D3F2C(team), 0, 0);
            fn_800AE7F0(fn_800A6590(fn_800A8408(team)), team, 0);
        }
    }
}

extern "C" void fn_800A7514(int team)
{
    int other = team == 0;

    if (lbl_803EC954[team]->mUnknown6C == 1 || lbl_803EC954[team]->mUnknown6C == 2) {
        fn_800AE750(fn_800A6590(fn_800A8408(team)), team);
        fn_8017DA9C(team);
        if (lbl_803EC954[team]->mUnknown68 == 0 && lbl_803EC954[other]->mUnknown68 != 2) {
            float mine = fn_800D3F2C(team);
            float theirs = fn_800D3F2C(other);

            fn_80156C78(34, 1);
            if (lbl_803EC954[team]->mUnknown6C == 2) {
                fn_800A9384(fn_800A6DD0(team));
                fn_80156C78(35, 1);
                if (lbl_803EC954[other]->mUnknown68 != 0) {
                    fn_80067DB8(11, 0, 0, 0, 0);
                } else {
                    fn_80067DB8(10, 0, team, 0, 0);
                }
            } else if (lbl_803EC954[other]->mUnknown68 == 0) {
                fn_80067DB8(8, 0, team, 0, 0);
                fn_80073210(120);
            }
            lbl_803EC954[team]->mUnknown68 = lbl_803EC954[team]->mUnknown6C;
            lbl_803EC954[team]->mUnknown54 = mine * 2.0f * lbl_803EC954[team]->mUnknown10;
            if (lbl_803EC954[other]->mUnknown68 != 0) {
                if (theirs < mine) {
                    mine -= theirs;
                    theirs = 0.0f;
                    lbl_803EC954[team]->mUnknown54 = mine * 2.0f * lbl_803EC954[team]->mUnknown10;
                    fn_800D4164(team, mine, 0);
                    fn_800A7A0C(other);
                } else if (theirs > mine) {
                    theirs -= mine;
                    lbl_803EC954[other]->mUnknown54 = theirs * 2.0f * lbl_803EC954[other]->mUnknown10;
                    fn_800D4164(other, theirs, 0);
                    fn_800A7A0C(team);
                } else {
                    fn_800A7A0C(team);
                    fn_800A7A0C(other);
                }
                if (theirs < 0.5f) {
                    fn_8017DA9C(other);
                }
            }
            fn_800A6D5C(team);
        }
        if (lbl_803EC954[team]->mUnknown68 != 0) {
            int args[2];

            lbl_803EAA1C[lbl_803EC954[team]->mUnknown8](team);
            fn_800A65BC();
            args[0] = team;
            args[1] = 1;
            fn_8021D7B8(lbl_803EB688, 0x80000016, 2, args);
            if (fn_80156704() == 0 && team == fn_80178320() && fn_800B65A0(fn_80178308()) == 0xFF) {
                Object_80039F5C *p = fn_80039FE8(fn_80178308(), 0, 0);
                unsigned char side;

                if (p == 0) {
                    p = fn_80039F5C(fn_80178308(), 0);
                }
                fn_8010B1FC(p, 0, 0);
                fn_80168908(fn_80178308(), 0);
                fn_80164940(fn_80178308());
                fn_800B0DA4();
                fn_800AEEDC(fn_80178308());
                fn_8011F3A8();
                fn_8003A3F4(0, fn_80178308());
                fn_8009FFD4();
                for (side = 0; side <= 1; side++) {
                    Object_800670B4 *pRoster = fn_80168708(side);
                    unsigned int count = fn_80178D18(side);
                    unsigned char i;

                    for (i = 0; i < count; i++) {
                        Object_80039F5C *pPlayer = fn_80039F5C(side, i);
                        unsigned char level;
                        unsigned char secondary;

                        fn_80164430(pRoster, i, &level, &secondary);
                        pPlayer->mUnknown2914 = level;
                        fn_800B49EC((Record_800B49EC *)pPlayer->mRatings, (Record_800B49EC *)pPlayer->mUnknown3020);
                        fn_800B4798(pPlayer->mRatings, side, i, &pPlayer->mUnknown2900);
                    }
                    fn_800A6F04(side);
                }
            }
        }
    }
}
