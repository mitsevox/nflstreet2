#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_800670B4.h"

/* Record fn_80163E94 returns; the entries are selected by the side flag. */
struct Record_80163E94 {
    char mUnknown0[9];
    unsigned char mUnknown9[2];
    char mUnknownB[5];
    Point_8017886C mUnknown10[2];
    int mUnknown20[2];
};

extern "C" {
Record_80163E94 *fn_80163E94(Object_800670B4 *pObject, unsigned int index, void *pArg);
void fn_80164568(Object_80039F5C *p, Record_80163E94 *pRecord, int side);
void fn_801644A0(Object_80039F5C *p);
void fn_801647A0(Object_800670B4 *pObject, int team);
void fn_80164A40(void);
Object_800670B4 *fn_80168708(int team);
void fn_8016DF34(Object_80039F5C *p);
void fn_800E55B8(Object_80039F5C *p);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800EFEF8(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800FF6D8(Object_80039F5C *p);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_8003977C(int team);
void fn_8003AB08(Object_80039F5C *p, int a);
Object_80039F5C *fn_80137B40(void);
int fn_80177F70(void);
Point_8017886C fn_80177FFC(int team);
int fn_80178320(void);
int fn_801CFFD0(int a, int b);
float fn_80237260(int stream);

extern char lbl_803EB3B0[];
}

static const char *lbl_8031D360[4];

extern "C" {
void fn_80164568(Object_80039F5C *p, Record_80163E94 *pRecord, int side)
{
    Message_800F01CC msg;
    Point_8017886C delta;

    if (p->mpState->mId != '*') {
        p->mFlags &= ~0x40000;
        fn_800EFEF8(0, p->mpState, p);
        delta = fn_80177FFC(p->mIdBytes[2]);
        fn_80227638(&delta, side == 1 ? &pRecord->mUnknown10[1] : &pRecord->mUnknown10[0], &delta);
        fn_80227690(&delta, &p->mMotion.mPos, &delta);
        if (fn_802270A4(&delta) > 0.5f) {
            fn_801C1F94(&msg, 0, 4);
            msg.mId = 7;
            fn_800F03D8(0, p->mpState, &msg, p);
            fn_801C1F94(&msg, 0, 4);
            msg.mId = 6;
            msg.mUnknown1[0] = (side == 1 ? pRecord->mUnknown20[1] : pRecord->mUnknown20[0]) >> 16;
            msg.mUnknown1[1] = 1;
            msg.mUnknown1[2] = 20;
            fn_800F03D8(0, p->mpState, &msg, p);
        } else if (fn_801CFFD0(side == 1 ? pRecord->mUnknown20[1] : pRecord->mUnknown20[0],
                       p->mMotion.mFacing) > 0xAAAAA) {
            fn_801C1F94(&msg, 0, 4);
            msg.mId = 6;
            msg.mUnknown1[0] = (side == 1 ? pRecord->mUnknown20[1] : pRecord->mUnknown20[0]) >> 16;
            msg.mUnknown1[1] = 1;
            msg.mUnknown1[2] = 20;
            fn_800F03D8(0, p->mpState, &msg, p);
        }
        fn_801644A0(p);
        fn_801C1F94(&msg, 0, 4);
        msg.mId = 9;
        msg.mUnknown1[0] = side == 1 ? pRecord->mUnknown9[1] : pRecord->mUnknown9[0];
        msg.mUnknown1[1] = 0;
        msg.mUnknown1[2] = 146;
        fn_800F03D8(0, p->mpState, &msg, p);
        fn_8016DF34(p);
    } else {
        fn_800E55B8(p);
    }
}

void fn_801647A0(Object_800670B4 *pObject, int team)
{
}

void fn_801647A4(Object_800670B4 *pObject, int team, void *pArg)
{
    unsigned char i;
    unsigned int count;
    Message_800F01CC msg;

    if (team == fn_80178320()) {
        fn_80164A40();
    }
    fn_801647A0(pObject, team);
    fn_8003977C(team);
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        Record_80163E94 *pRecord = fn_80163E94(pObject, i, pArg);
        Object_80039F5C *p = fn_80039F5C(team, i);

        p->mFlags = (p->mFlags & ~0x4000) | 0x10;
        fn_800EFE60(0, p->mpState, p);
        fn_8003AB08(p, 0);
        if (p == fn_80137B40()) {
            fn_801C1F94(&msg, 0, 4);
            msg.mId = 49;
            fn_800F03D8(0, p->mpState, &msg, p);
        }
        fn_801C1F94(&msg, 0, 4);
        msg.mId = 7;
        fn_800F03D8(0, p->mpState, &msg, p);
        fn_801644A0(p);
        fn_801C1F94(&msg, 0, 4);
        msg.mId = 87;
        msg.mUnknown1[0] = pObject->mUnknown8.mUnknownF == 1 ? pRecord->mUnknown9[1] : pRecord->mUnknown9[0];
        msg.mUnknown1[1] = (pObject->mUnknown8.mUnknownF == 1 ? pRecord->mUnknown20[1] : pRecord->mUnknown20[0]) >> 16;
        fn_800F03D8(0, p->mpState, &msg, p);
    }
}

void fn_80164940(int team)
{
    unsigned char i;
    unsigned int count;
    int home = fn_80178320();
    Object_800670B4 *pObject = fn_80168708(team);

    fn_801647A0(pObject, team);
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        int update = 1;
        Record_80163E94 *pRecord = fn_80163E94(pObject, i, lbl_803EB3B0);
        Object_80039F5C *p = fn_80039F5C(team, i);

        if (team != home) {
            if (fn_80177F70() != 0) {
                if (p->mFlags & 0x40000) {
                    if (!(p->mFlags & 0x20000000)) {
                        update = 0;
                    }
                }
            }
        }
        if (update == 1) {
            p->mFlags &= ~0x40000;
            p->mFlags &= ~0x4000;
            p->mFlags |= 0x10;
            fn_80164568(p, pRecord, pObject->mUnknown8.mUnknownF);
        }
    }
}

void fn_80164A40(void)
{
    lbl_8031D360[0] = "Norm";
    lbl_8031D360[1] = "Norm";
    lbl_8031D360[2] = "Norm";
    lbl_8031D360[3] = "Norm";
}

void fn_80164A64(int team)
{
    unsigned char i;
    unsigned int count = fn_80178D70(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);

        if (p->mUnknown3048.mId != 0) {
            if (p->mUnknown3048.mId == 7) {
                Message_800F01CC msg;
                float value;

                fn_800FF6D8(p);
                fn_801C1F94(&msg, 0, 4);
                msg.mId = 51;
                value = fn_80237260(0);
                if (fn_80177F70() == 0) {
                    value *= 2.0f;
                } else {
                    value *= 0.4f;
                }
                msg.mUnknown1[0] = (int)(value * 32.0f);
                fn_800F00D4(0, p->mpState, &msg, p);
            }
        }
    }
}

const char *fn_80164B64(int index)
{
    return lbl_8031D360[index];
}
}
