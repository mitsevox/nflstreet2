#include "game/cu_80159F10.h"
#include "game/fn_8016871C.h"
#include "game/fn_800F06F4.h"
#include "game/Object_80039F5C.h"
#include "game/fn_800AD9B4.h"

extern "C" {
void *fn_80147F18(int value);
int fn_8011E9D8(State_80039F5C *pState);
int fn_8011F1F4(void);
int fn_80168E00(int team, int index, unsigned char *pOut);
int fn_80178308(void);
int fn_801784C4(void);
int fn_800C47C4(void);
}

static float lbl_803EB2A0 = 2.5f;
static unsigned char lbl_803EB2A4[3] = { 2, 1, 3 };
static Instance_80159F10 *lbl_8031BD04[3];

extern "C" {

static int fn_80147F2C(Object_80039F5C *pPlayer)
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
                Object_80039F5C *pOther = fn_80039F5C(1, i);
                if (pOther != 0) {
                    Record_80067338 *pRecord = fn_8016871C(fn_80178308());
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

void fn_80148048(void *pOwner)
{
    unsigned char i;

    fn_8015A110(pOwner);
    for (i = 0; i < 3; i++) {
        lbl_8031BD04[i] = fn_8015A1A8(pOwner, i, fn_800C47C4(), i + 1);
    }
}

void fn_801480B0(void *pOwner)
{
    unsigned char i;

    for (i = 0; i < 3; i++) {
        fn_8015A204(pOwner, lbl_8031BD04[i]);
    }
    fn_8015A17C();
}

void fn_80148108(int mode)
{
    unsigned char *pFlags = (unsigned char *)fn_80147F18(0);

    *pFlags |= 1;
    if (mode == 1) {
        *pFlags |= 4;
    }
}

void fn_80148154(void)
{
    int mode = fn_800AD9B4();
    unsigned char *pFlags = (unsigned char *)fn_80147F18(0);

    if (mode == 3 && (*pFlags & 1)) {
        *pFlags |= 2;
    }
    *pFlags &= ~0xD;
}

int fn_801481B0(void)
{
    return *(unsigned char *)fn_80147F18(0) & 1;
}

int fn_801481DC(void)
{
    return (*(unsigned char *)fn_80147F18(0) >> 2) & 1;
}

int fn_80148208(int index, int force)
{
    Object_80039F5C *pPlayer = 0;
    unsigned char *pFlags = (unsigned char *)fn_80147F18(0);
    int team = fn_80178308();
    unsigned char found;
    int slot = fn_80168E00(team, index, &found);

    fn_80178308();
    if (slot != 0xFF) {
        pPlayer = fn_80039F5C(team, slot);
    }
    if (slot == 0xFF || found == 0) {
        int mode = fn_800AD9B4();
        if (mode == 2 || (mode == 3 && fn_8011F1F4() != 0)) {
            if (slot == 0xFF) {
                slot = lbl_803EB2A4[index];
            }
        } else {
            slot = 0xFF;
        }
    }
    if ((*pFlags & 4) && force == 0) {
        slot = 0xFF;
    }
    if (fn_8011F1F4() == 0 && pPlayer != 0 && fn_80147F2C(pPlayer) == 0) {
        slot = 0xFF;
    }
    return slot;
}

int fn_8014830C(int index, Vector_80039F5C *pOut)
{
    int result = 0;
    int slot = fn_80148208(index, 0);

    if (slot != 0xFF) {
        Object_80039F5C *pPlayer = fn_80039F5C(fn_80178308(), slot);
        pOut->mX = pPlayer->mMotion.mPos.mX;
        pOut->mY = pPlayer->mMotion.mPos.mY;
        pOut->mZ = pPlayer->mMotion.mPos.mZ;
        if (fn_801784C4() != 0) {
            pOut->mX = -pOut->mX;
            pOut->mY = -pOut->mY;
        }
        pOut->mZ += lbl_803EB2A0;
        fn_8015A240(lbl_8031BD04[index], 2);
        result = 1;
    }
    return result;
}

void fn_801483C8(void)
{
    *(unsigned char *)fn_80147F18(0) &= ~2;
}

int fn_801483F8(void)
{
    return (*(unsigned char *)fn_80147F18(0) >> 1) & 1;
}
}
