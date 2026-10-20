#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_801FCE10.h"
#include "game/fn_80178D18.h"
#include "game/fn_801F40F4.h"

/* Four-byte entry of the stream read by fn_800B9F50. */
struct Event_800B9F50 {
    unsigned char mType;
    unsigned char mIndex;
    unsigned short mTime;
};

/* Block allocated by fn_800BA3F0 through fn_80238174 under the id 'prac'
   (392 bytes); only the accessed fields are declared. */
struct Block_800BA3F0 {
    Object_800670B4 *mpUnknown0;
    Object_800670B4 *mpUnknown4;
    Record_80067338 *mpUnknown8;
    Record_80067338 *mpUnknownC;
    int mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15[3];
    Point_8017886C mUnknown18;
    int mUnknown20;
    unsigned char mUnknown24[0x9C];
    int mUnknownC0;
    unsigned char mUnknownC4[0x1C];
    unsigned char mUnknownE0;
    unsigned char mUnknownE1[3];
    int mUnknownE4[37];
    Event_800B9F50 *mpUnknown178;
    int mUnknown17C;
    unsigned char mUnknown180;
    unsigned char mUnknown181[1];
    unsigned char mUnknown182;
    unsigned char mUnknown183;
    unsigned char mUnknown184;
    unsigned char mUnknown185;
    unsigned char mUnknown186[2];
};


extern "C" {
int fn_80178308(void);
int fn_80178320(void);
void fn_800EFE1C(int a, State_80039F5C *pQueue);
float fn_80178A08(void);

extern Block_800BA3F0 *lbl_803EAB88;
}

extern "C" int fn_800B9BBC(void)
{
    int value = 0;

    fn_801FCE10(0, "select 'PYTM' into \x82 from 'NIOM'\n", &value);
    return value;
}

extern "C" unsigned char fn_800B9BFC(void)
{
    unsigned char value = 0;

    fn_801FCE10(0, "select 'BSPG' into \x80 from 'FNIG'\n", &value);
    return value;
}

extern "C" void fn_800B9C3C(void)
{
    fn_801FCE10(0, "update 'FNIG' set 'BSPG' = \x82\n", 0);
}

extern "C" unsigned char fn_800B9C70(void)
{
    unsigned char value = 0;

    fn_801FCE10(0, "select 'PNPG' into \x80 from 'FNIG'\n", &value);
    return value;
}

extern "C" void fn_800B9CB0(void)
{
    fn_801FCE10(0, "update 'FNIG' set 'PNPG' = \x82\n", 0);
}

extern "C" int fn_800B9CE4(void)
{
    int value = 0;

    fn_801FCE10(0, "select 'YTPG' into \x82 from 'FNIG'\n", &value);
    return value;
}

extern "C" void fn_800B9D24(void)
{
    int team = fn_80178320();
    unsigned short i;

    for (i = 0; i < 7; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        Object_80137ABC *pBall = fn_80137C48(p);

        if (pBall != 0) {
            Vector_80039F5C velocity;

            velocity.mX = velocity.mY = velocity.mZ = 0.0f;
            fn_80137EE0(pBall, &velocity);
            fn_8013791C(pBall, 5, 0);
        }
        p->mMotion.mPos.mX = -100.0f;
        p->mMotion.mPos.mY = -100.0f - i * 3.0f;
        p->mpUnknown4->mUnknown20 &= ~1;
        fn_800EFE1C(0, p->mpState);
        p->mUnknown512.mUnknown14 = 0;
        p->mFlags |= 0x40000;
    }
}

extern "C" void fn_800B9E44(void)
{
    int team = fn_80178320();
    unsigned short i;
    unsigned int count = fn_80178D18(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);

        p->mMotion.mPos.mX = fn_80178A08() + 2.0f;
        p->mMotion.mPos.mY = 12.0f - i * 2.0f;
        p->mpUnknown4->mUnknown20 |= 1;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = 0x800000;
        p->mUnknown512.mUnknown4 = 0x800000;
        p->mUnknown512.mUnknown0 = 0.14f;
        p->mFlags &= ~0x40000;
    }
}

/* Effect slot returned by fn_80162DBC (laid out as in src/game/cu_8016174C.cpp). */
struct Object_801618D8 {
    unsigned char mUnknown0[4];
    Vector_80039F5C mUnknown4;
    unsigned char mUnknown10[4];
    int mUnknown14;
    float mUnknown18, mUnknown1C;
    unsigned int mUnknown20;
    void *mUnknown24;
    int mUnknown28, mUnknown2C, mUnknown30, mUnknown34;
    float mUnknown38;
    unsigned char mUnknown3C[192];
    int mUnknownFC;
    Object_80039F5C *mUnknown100;
    int mUnknown104;
};

/* Position that fn_801F4934 writes for a playing stream. */
struct Position_801F4934 {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[8];
};

extern "C" {
void fn_8003A1EC(int on, int team, int index);
void fn_8003A394(int a, int team, int index);
void fn_8003A3F4(int a, int team);
int fn_8006D65C(int idx);
Object_801618D8 *fn_80162DBC(int index);
void fn_80162DD0(Object_801618D8 *item, Vector_80039F5C *point);
void fn_801F4934(int a, Position_801F4934 *pPosition);
}

extern "C" int fn_800B9F50(void)
{
    Status_801F4834 status;
    Position_801F4934 position;
    int done = 0;

    fn_801F4834(fn_8006D65C(4), &status);
    if (status.mUnknown0 == 0) {
        position.mUnknown4 = 0xFFFF;
    } else {
        fn_801F4934(status.mUnknown4, &position);
    }
    while (!done && position.mUnknown4 >= lbl_803EAB88->mpUnknown178->mTime) {
        Event_800B9F50 *pEvent = lbl_803EAB88->mpUnknown178++;
        int team = (pEvent->mType & 0x80) ? fn_80178308() : fn_80178320();
        int mode = 1;
        Object_80039F5C *p;
        Object_801618D8 *pItem;
        int i;
        int j;

        switch (pEvent->mType & 0x7F) {
        case 0:
            mode = 0;
            if (pEvent->mType & 0x80) {
                mode = 8;
            }
        case 1:
            p = fn_80039F5C((unsigned char)team, pEvent->mIndex);
            if (p != 0) {
                for (i = 0; i <= 4; i++) {
                    pItem = fn_80162DBC(i);
                    if (pItem->mUnknown100 == 0) {
                        pItem->mUnknown20 |= 6;
                        pItem->mUnknown100 = p;
                        pItem->mUnknown18 = 5.0f;
                        pItem->mUnknown30 = mode;
                        fn_80162DD0(pItem, &p->mMotion.mPos);
                        break;
                    }
                }
            }
            break;
        case 3:
            team = fn_80178320();
            mode = 0;
            for (j = 0; j <= 10; j++) {
                p = fn_80039F5C((unsigned char)team, j);
                if (p != 0 && (unsigned int)(p->mUnknown2914 - 10) <= 2) {
                    for (i = 0; i <= 4; i++) {
                        pItem = fn_80162DBC(i);
                        if (pItem->mUnknown100 == 0) {
                            pItem->mUnknown20 |= 6;
                            pItem->mUnknown100 = p;
                            pItem->mUnknown18 = 5.0f;
                            pItem->mUnknown30 = mode;
                            fn_80162DD0(pItem, &p->mMotion.mPos);
                            break;
                        }
                    }
                }
            }
            break;
        case 5:
            team = fn_80178320();
            mode = 0;
            for (j = 0; j <= 10; j++) {
                p = fn_80039F5C((unsigned char)team, j);
                if (p != 0 && (unsigned int)(p->mUnknown2914 - 13) <= 2) {
                    for (i = 0; i <= 4; i++) {
                        pItem = fn_80162DBC(i);
                        if (pItem->mUnknown100 == 0) {
                            pItem->mUnknown20 |= 6;
                            pItem->mUnknown100 = p;
                            pItem->mUnknown18 = 5.0f;
                            pItem->mUnknown30 = mode;
                            fn_80162DD0(pItem, &p->mMotion.mPos);
                            break;
                        }
                    }
                }
            }
            break;
        case 2:
            p = fn_80039F5C((unsigned char)team, pEvent->mIndex);
            if (p != 0) {
                for (i = 0; i <= 4; i++) {
                    pItem = fn_80162DBC(i);
                    if (pItem->mUnknown100 == p) {
                        pItem->mUnknown30 = 8;
                        pItem->mUnknown100 = 0;
                        pItem->mUnknown20 &= ~2;
                    }
                }
            }
            break;
        case 4:
            team = fn_80178320();
            for (j = 0; j <= 10; j++) {
                p = fn_80039F5C((unsigned char)team, j);
                if (p != 0 && (unsigned int)(p->mUnknown2914 - 10) <= 2) {
                    for (i = 0; i <= 4; i++) {
                        pItem = fn_80162DBC(i);
                        if (pItem->mUnknown100 == p) {
                            pItem->mUnknown30 = 8;
                            pItem->mUnknown100 = 0;
                            pItem->mUnknown20 &= ~2;
                        }
                    }
                }
            }
            break;
        case 6:
            team = fn_80178320();
            for (j = 0; j <= 10; j++) {
                p = fn_80039F5C((unsigned char)team, j);
                if (p != 0 && (unsigned int)(p->mUnknown2914 - 13) <= 2) {
                    for (i = 0; i <= 4; i++) {
                        pItem = fn_80162DBC(i);
                        if (pItem->mUnknown100 == p) {
                            pItem->mUnknown30 = 8;
                            pItem->mUnknown100 = 0;
                            pItem->mUnknown20 &= ~2;
                        }
                    }
                }
            }
            break;
        case 7:
            fn_8003A394(1, team, pEvent->mIndex);
            break;
        case 8:
            fn_8003A1EC(0, team, pEvent->mIndex);
            break;
        case 9:
            fn_8003A3F4(pEvent->mIndex, team);
            break;
        case 10:
            done = 1;
            break;
        }
    }
    return done;
}
