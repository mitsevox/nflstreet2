#include "game/cu_8008E978.h"
#include "game/Object_8017886C.h"

/* View of the 20-byte sequencer item that AnimSeqncrGetItemPtr returns:
   a ground position (+4, +12) and a pointer whose first word is zero for
   the items that mark the play area. */
struct Item_80090558 {
    char mUnknown0[4];
    float mUnknown4;
    char mUnknown8[4];
    float mUnknownC;
    int *mpUnknown10;
};

extern "C" {
float AnimSeqncrGetLength(Actor_801C009C *pActor);
Item_80090558 *AnimSeqncrGetItemPtr(Actor_801C009C *pActor, int index);
int fn_800AD9B4(void);
int fn_800913E8(Vector_80039F5C *pOut, Character_80093BCC *pCharacter, Actor_801C009C *pActor, Object_80039F5C *p,
                float time);
void fn_80227384(void *pOut, void *pIn, int angle);
unsigned int fn_80178D18(int team);
Object_80039F5C *PlyrGet(int team, unsigned short index);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
unsigned int fn_802372EC(int a, int b);
float fn_80178A44(void);
}

extern unsigned char lbl_803EA8C0;
extern int lbl_803EA8C4;
extern Vector_80039F5C lbl_8030C0B4[];
extern Vector_80039F5C lbl_802D72A4;
extern Vector_80039F5C lbl_802D72B0;

/* Builds the play-area outline for character's actor: the spots of p, the
   actor's start sample, its marker items (turned by p's facing and placed
   at p) and its end sample go into lbl_8030C0B4 (at most ten, closed back
   to the first spot) while lbl_802D72A4/lbl_802D72B0 track their minimum
   and maximum, widened by 2. Every other player of either team inside that
   box, and not one of character's own players, is pushed out past the far
   side by a random 2 to 7 units; for character kinds up to 2 the player is
   first stopped. */
extern "C" void fn_80090558(Character_80093BCC *pCharacter, Actor_801C009C *pActor, Object_80039F5C *p)
{
    float length = AnimSeqncrGetLength(pActor);
    unsigned char i;
    unsigned char team;

    lbl_802D72A4.mX = p->mMotion.mPos.mX;
    lbl_802D72A4.mY = p->mMotion.mPos.mY;
    lbl_803EA8C4 = 0;
    lbl_802D72B0.mX = p->mMotion.mPos.mX;
    lbl_802D72B0.mY = p->mMotion.mPos.mY;
    if (fn_800AD9B4() == 4 && fn_800913E8(&lbl_8030C0B4[lbl_803EA8C4], pCharacter, pActor, p, 0.0f)) {
        int index = lbl_803EA8C4++;

        lbl_802D72B0.mX = lbl_802D72A4.mX = lbl_8030C0B4[index].mX;
        lbl_802D72B0.mY = lbl_802D72A4.mY = lbl_8030C0B4[index].mY;
    }
    for (i = 0; i < pActor->mUnknownC[0] && (unsigned int)lbl_803EA8C4 < 10; i++) {
        Item_80090558 *pItem = AnimSeqncrGetItemPtr(pActor, i);

        if (*pItem->mpUnknown10 == 0) {
            lbl_8030C0B4[lbl_803EA8C4].mX = pItem->mUnknown4;
            lbl_8030C0B4[lbl_803EA8C4].mY = -pItem->mUnknownC;
            fn_80227384(&lbl_8030C0B4[lbl_803EA8C4], &lbl_8030C0B4[lbl_803EA8C4], p->mMotion.mFacing + 0x400000);
            lbl_8030C0B4[lbl_803EA8C4].mX += p->mMotion.mPos.mX;
            lbl_8030C0B4[lbl_803EA8C4].mY += p->mMotion.mPos.mY;
            if (lbl_803EA8C4 == 0) {
                lbl_802D72B0.mX = lbl_802D72A4.mX = lbl_8030C0B4[0].mX;
                lbl_802D72B0.mY = lbl_802D72A4.mY = lbl_8030C0B4[0].mY;
            } else {
                lbl_802D72A4.mX = lbl_8030C0B4[lbl_803EA8C4].mX <= lbl_802D72A4.mX ? lbl_8030C0B4[lbl_803EA8C4].mX : lbl_802D72A4.mX;
                lbl_802D72A4.mY = lbl_8030C0B4[lbl_803EA8C4].mY <= lbl_802D72A4.mY ? lbl_8030C0B4[lbl_803EA8C4].mY : lbl_802D72A4.mY;
                lbl_802D72B0.mX = lbl_8030C0B4[lbl_803EA8C4].mX >= lbl_802D72B0.mX ? lbl_8030C0B4[lbl_803EA8C4].mX : lbl_802D72B0.mX;
                lbl_802D72B0.mY = lbl_8030C0B4[lbl_803EA8C4].mY >= lbl_802D72B0.mY ? lbl_8030C0B4[lbl_803EA8C4].mY : lbl_802D72B0.mY;
            }
            lbl_803EA8C4++;
        }
    }
    if (fn_800AD9B4() == 4 && fn_800913E8(&lbl_8030C0B4[lbl_803EA8C4], pCharacter, pActor, p, length - 1.0f)) {
        int index = lbl_803EA8C4;

        lbl_802D72A4.mX = lbl_8030C0B4[index].mX <= lbl_802D72A4.mX ? lbl_8030C0B4[index].mX : lbl_802D72A4.mX;
        lbl_802D72A4.mY = lbl_8030C0B4[index].mY <= lbl_802D72A4.mY ? lbl_8030C0B4[index].mY : lbl_802D72A4.mY;
        lbl_802D72B0.mX = lbl_8030C0B4[index].mX >= lbl_802D72B0.mX ? lbl_8030C0B4[index].mX : lbl_802D72B0.mX;
        lbl_802D72B0.mY = lbl_8030C0B4[index].mY >= lbl_802D72B0.mY ? lbl_8030C0B4[index].mY : lbl_802D72B0.mY;
        lbl_803EA8C4++;
        if (lbl_8030C0B4[index].mX != lbl_8030C0B4[0].mX || lbl_8030C0B4[index].mY != lbl_8030C0B4[0].mY) {
            lbl_8030C0B4[lbl_803EA8C4++] = lbl_8030C0B4[0];
        }
    }
    lbl_802D72A4.mX -= 2.0f;
    lbl_802D72B0.mX += 2.0f;
    lbl_802D72B0.mY += 2.0f;
    lbl_802D72A4.mY -= 2.0f;
    lbl_803EA8C0 = 1;
    for (team = 0; team < 2; team++) {
        unsigned int count = fn_80178D18(team);
        unsigned short j;

        for (j = 0; j < count; j++) {
            Object_80039F5C *pPlayer = PlyrGet(team, j);
            int found = 0;
            unsigned short k;
            Point_8017886C pos;
            float offset;

            if (pPlayer == p) {
                continue;
            }
            for (k = 0; k < pActor->mUnknown4; k++) {
                if (pPlayer == pCharacter->mUnknown14[k]) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                continue;
            }
            if ((unsigned int)pCharacter->mUnknown4 <= 2) {
                pPlayer->mpUnknown4->mUnknown20 &= ~1;
                fn_800EFE60(0, pPlayer->mpState, pPlayer);
                pPlayer->mUnknown512.mUnknown14 = 3;
                pPlayer->mUnknown512.mUnknown8 = pPlayer->mUnknown512.mUnknown4 = pPlayer->mMotion.mFacing;
                pPlayer->mUnknown512.mUnknown0 = 0.0f;
            }
            pos.mX = pPlayer->mMotion.mPos.mX;
            pos.mY = pPlayer->mMotion.mPos.mY;
            if (pos.mX < lbl_802D72A4.mX || pos.mX > lbl_802D72B0.mX || pos.mY < lbl_802D72A4.mY ||
                pos.mY > lbl_802D72B0.mY) {
                continue;
            }
            offset = ((float)fn_802372EC(0, 50) * 0.05f + 1.0f) * 2.0f;
            if (lbl_802D72B0.mX - pos.mX <= pos.mX - lbl_802D72A4.mX) {
                pos.mX = lbl_802D72A4.mX - offset <= pos.mX ? lbl_802D72A4.mX - offset : pos.mX;
            } else {
                pos.mX = lbl_802D72B0.mX + offset >= pos.mX ? lbl_802D72B0.mX + offset : pos.mX;
            }
            offset = ((float)fn_802372EC(0, 50) * 0.05f + 1.0f) * 2.0f;
            if (lbl_802D72B0.mY - pos.mY <= pos.mY - lbl_802D72A4.mY) {
                pos.mY = lbl_802D72A4.mY - offset <= pos.mY ? lbl_802D72A4.mY - offset : pos.mY;
            } else {
                pos.mY = lbl_802D72B0.mY + offset >= pos.mY ? lbl_802D72B0.mY + offset : pos.mY;
            }
            if (pos.mY >= fn_80178A44()) {
                pos.mY = lbl_802D72A4.mY - offset;
            }
            pPlayer->mMotion.mPos.mX = pos.mX;
            pPlayer->mMotion.mPos.mY = pos.mY;
        }
    }
}
