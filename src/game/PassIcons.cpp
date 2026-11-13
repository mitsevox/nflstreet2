/* The three pass icons shown above the players the ball can be passed to. */

#include "game/PassIconObj.h"
#include "game/PlayBookGetPlay.h"
#include "game/fn_800F06F4.h"
#include "game/Object_80039F5C.h"
#include "game/fn_800AD9B4.h"

extern "C" {
void *PassIconStateGetFlags(int value);
int fn_8011E9D8(State_80039F5C *pState);
int fn_8011F1F4(void);
int PlayBookGetReceiver(int team, int index, unsigned char *pOut);
int fn_80178308(void);
int fn_801784C4(void);
int fn_800C47C4(void);
}

static float _PassIcon_fHeight = 2.5f;
static unsigned char _PassIcon_DefaultSlots[3] = { 2, 1, 3 };
static PassIconObj_t *_PassIcon_pIcons[3];

extern "C" {

static int _PassIconIsEligible(Object_80039F5C *pPlayer)
{
    int result = 1;
    unsigned char i;

    if (pPlayer != 0) {
        switch (pPlayer->mpState->mId) {
        case 10:
        case 11:
        case 31:
        case 32:
        case 33:
        case 47:
            result = 0;
            break;
        default:
            result = fn_8011E9D8(pPlayer->mpState) == 0;
            break;
        }
        if (result) {
            for (i = 0; i < 7 && result; i++) {
                Object_80039F5C *pOther = PlyrGet(1, i);
                if (pOther != 0) {
                    PlayBookPlay_t *pRecord = PlayBookGetPlay(fn_80178308());
                    void *pResult = fn_80164EC8(pRecord, fn_80178308(), i);
                    if (fn_800F06F4(0, pResult, 0x12, 0xFFFF) != 0xFFFF && pPlayer == pOther
                        && pPlayer->mUnknown2914 == 0) {
                        result = 0;
                    }
                }
            }
        }
    }
    return result;
}

void PassIconsCreate(void *pOwner)
{
    unsigned char i;

    PassIconObjRegister(pOwner);
    for (i = 0; i < 3; i++) {
        _PassIcon_pIcons[i] = PassIconObjNew(pOwner, i, fn_800C47C4(), i + 1);
    }
}

void PassIconsDestroy(void *pOwner)
{
    unsigned char i;

    for (i = 0; i < 3; i++) {
        PassIconObjDelete(pOwner, _PassIcon_pIcons[i]);
    }
    PassIconObjUnregister();
}

void PassIconsShow(int mode)
{
    unsigned char *pFlags = (unsigned char *)PassIconStateGetFlags(0);

    *pFlags |= 1;
    if (mode == 1) {
        *pFlags |= 4;
    }
}

void PassIconsHide(void)
{
    int mode = fn_800AD9B4();
    unsigned char *pFlags = (unsigned char *)PassIconStateGetFlags(0);

    if (mode == 3 && (*pFlags & 1)) {
        *pFlags |= 2;
    }
    *pFlags &= ~0xD;
}

int PassIconsAreShown(void)
{
    return *(unsigned char *)PassIconStateGetFlags(0) & 1;
}

int PassIconsAreLocked(void)
{
    return (*(unsigned char *)PassIconStateGetFlags(0) >> 2) & 1;
}

int PassIconGetSlot(int index, int force)
{
    Object_80039F5C *pPlayer = 0;
    unsigned char *pFlags = (unsigned char *)PassIconStateGetFlags(0);
    int team = fn_80178308();
    unsigned char found;
    int slot = PlayBookGetReceiver(team, index, &found);

    fn_80178308();
    if (slot != 0xFF) {
        pPlayer = PlyrGet(team, slot);
    }
    if (slot == 0xFF || found == 0) {
        int mode = fn_800AD9B4();
        if (mode == 2 || (mode == 3 && fn_8011F1F4() != 0)) {
            if (slot == 0xFF) {
                slot = _PassIcon_DefaultSlots[index];
            }
        } else {
            slot = 0xFF;
        }
    }
    if ((*pFlags & 4) && force == 0) {
        slot = 0xFF;
    }
    if (fn_8011F1F4() == 0 && pPlayer != 0 && _PassIconIsEligible(pPlayer) == 0) {
        slot = 0xFF;
    }
    return slot;
}

int PassIconGetPosition(int index, Vector_80039F5C *pOut)
{
    int result = 0;
    int slot = PassIconGetSlot(index, 0);

    if (slot != 0xFF) {
        Object_80039F5C *pPlayer = PlyrGet(fn_80178308(), slot);
        pOut->mX = pPlayer->mMotion.mPos.mX;
        pOut->mY = pPlayer->mMotion.mPos.mY;
        pOut->mZ = pPlayer->mMotion.mPos.mZ;
        if (fn_801784C4() != 0) {
            pOut->mX = -pOut->mX;
            pOut->mY = -pOut->mY;
        }
        pOut->mZ += _PassIcon_fHeight;
        PassIconObjSetPalette(_PassIcon_pIcons[index], 2);
        result = 1;
    }
    return result;
}

void PassIconsClearReplayFlag(void)
{
    *(unsigned char *)PassIconStateGetFlags(0) &= ~2;
}

int PassIconsWereShown(void)
{
    return (*(unsigned char *)PassIconStateGetFlags(0) >> 1) & 1;
}
}
