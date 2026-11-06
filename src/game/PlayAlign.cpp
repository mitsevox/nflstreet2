/* Lines a team up for the snap: sends every player to his spot and facing in the
   called play and staggers when they start moving. */

#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_800670B4.h"
#include "game/PlaySet.h"
#include "game/PlayAlign.h"

extern "C" {
void PlayAlignTeamBegin(Object_800670B4 *pObject, int team);
void PlayAlignResetSetNames(void);
Object_800670B4 *PlayBookGetFormation(int team);
void fn_8016DF34(Object_80039F5C *p);
void fn_800E55B8(Object_80039F5C *p);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800EFEF8(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800FF6D8(Object_80039F5C *p);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_8003977C(int team);
void fn_8003AB08(Object_80039F5C *p, int a);
Object_80039F5C *BallGetCurrentHolder(void);
int fn_80177F70(void);
Point_8017886C fn_80177FFC(int team);
int fn_80178320(void);
int MathAngleDiff(int a, int b);
float fn_80237260(int stream);

}

static const char *_PlayAlign_apSetNames[4];

extern "C" const char *gPlayAlignNormSet[] = { "Norm", 0 };

extern "C" {
void PlayAlignPlayer(Object_80039F5C *p, Entry_8006719C *pEntry, int side)
{
    Message_800F01CC msg;
    Point_8017886C delta;

    if (p->mpState->mId != '*') {
        p->mFlags &= ~0x40000;
        fn_800EFEF8(0, p->mpState, p);
        delta = fn_80177FFC(p->mIdBytes[2]);
        fn_80227638(&delta, side == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10, &delta);
        fn_80227690(&delta, &p->mMotion.mPos, &delta);
        if (fn_802270A4(&delta) > 0.5f) {
            fn_801C1F94(&msg, 0, 4);
            msg.mId = 7;
            fn_800F03D8(0, p->mpState, &msg, p);
            fn_801C1F94(&msg, 0, 4);
            msg.mId = 6;
            msg.mUnknown1[0] = (side == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20) >> 16;
            msg.mUnknown1[1] = 1;
            msg.mUnknown1[2] = 20;
            fn_800F03D8(0, p->mpState, &msg, p);
        } else if (MathAngleDiff(side == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20,
                       p->mMotion.mFacing) > 0xAAAAA) {
            fn_801C1F94(&msg, 0, 4);
            msg.mId = 6;
            msg.mUnknown1[0] = (side == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20) >> 16;
            msg.mUnknown1[1] = 1;
            msg.mUnknown1[2] = 20;
            fn_800F03D8(0, p->mpState, &msg, p);
        }
        PlaySetPointToRoleMate(p);
        fn_801C1F94(&msg, 0, 4);
        msg.mId = 9;
        msg.mUnknown1[0] = side == 1 ? pEntry->mUnknownA : pEntry->mUnknown9;
        msg.mUnknown1[1] = 0;
        msg.mUnknown1[2] = 146;
        fn_800F03D8(0, p->mpState, &msg, p);
        fn_8016DF34(p);
    } else {
        fn_800E55B8(p);
    }
}

void PlayAlignTeamBegin(Object_800670B4 *pObject, int team)
{
}

void PlayAlignTeam(Object_800670B4 *pObject, int team, const char **ppNames)
{
    unsigned char i;
    unsigned int count;
    Message_800F01CC msg;

    if (team == fn_80178320()) {
        PlayAlignResetSetNames();
    }
    PlayAlignTeamBegin(pObject, team);
    fn_8003977C(team);
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        Entry_8006719C *pEntry = PlaySetGetEntry(pObject, i, ppNames);
        Object_80039F5C *p = fn_80039F5C(team, i);

        p->mFlags = (p->mFlags & ~0x4000) | 0x10;
        fn_800EFE60(0, p->mpState, p);
        fn_8003AB08(p, 0);
        if (p == BallGetCurrentHolder()) {
            fn_801C1F94(&msg, 0, 4);
            msg.mId = 49;
            fn_800F03D8(0, p->mpState, &msg, p);
        }
        fn_801C1F94(&msg, 0, 4);
        msg.mId = 7;
        fn_800F03D8(0, p->mpState, &msg, p);
        PlaySetPointToRoleMate(p);
        fn_801C1F94(&msg, 0, 4);
        msg.mId = 87;
        msg.mUnknown1[0] = pObject->mUnknown8.mUnknownF == 1 ? pEntry->mUnknownA : pEntry->mUnknown9;
        msg.mUnknown1[1] = (pObject->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20) >> 16;
        fn_800F03D8(0, p->mpState, &msg, p);
    }
}

void PlayRealignTeam(int team)
{
    unsigned char i;
    unsigned int count;
    int home = fn_80178320();
    Object_800670B4 *pObject = PlayBookGetFormation(team);

    PlayAlignTeamBegin(pObject, team);
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        int update = 1;
        Entry_8006719C *pEntry = PlaySetGetEntry(pObject, i, gPlayAlignNormSet);
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
            PlayAlignPlayer(p, pEntry, pObject->mUnknown8.mUnknownF);
        }
    }
}

void PlayAlignResetSetNames(void)
{
    _PlayAlign_apSetNames[0] = "Norm";
    _PlayAlign_apSetNames[1] = "Norm";
    _PlayAlign_apSetNames[2] = "Norm";
    _PlayAlign_apSetNames[3] = "Norm";
}

void PlayAlignPostStartDelays(int team)
{
    unsigned char i;
    unsigned int count = fn_80178D70(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);

        if (p->mQueue[0].mId != 0) {
            if (p->mQueue[0].mId == 7) {
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

const char *PlayAlignGetSetName(int index)
{
    return _PlayAlign_apSetNames[index];
}
}
