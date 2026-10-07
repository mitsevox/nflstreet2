#include "game/Block_80307980.h"
#include "game/Object_8003DEC4.h"
#include "game/cu_80047E28.h"
#include "game/cu_8015C25C.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80233CBC.h"

#include <string.h>

/* Per-player model request (0x11C bytes). The halfword at +0xFA keeps one
   "needs loading" bit (0x01-0x10) and one "loading" bit (0x20-0x200) for
   each of the five parts loaded asynchronously by fn_8015C498. */
struct Entry_803EB32C {
    int mUnknown0;
    Ids_8015F6E8 mUnknown4;
    int mUnknownC;
    int mUnknown10;
    FMCAPPORTValues mUnknown14;
    int mUnknownE8;
    int mUnknownEC;
    int mUnknownF0;
    unsigned char mUnknownF4;
    unsigned char mUnknownF5;
    unsigned char mUnknownF6;
    unsigned char mUnknownF7;
    unsigned char mUnknownF8;
    unsigned char mUnknownF9;
    unsigned short mUnknownFA;
    unsigned char mUnknownFC;
    unsigned char mUnknownFD;
    char mUnknownFE[30];
};

/* State allocated by fn_8015CBC8 (0x254 bytes). */
struct State_803EB32C {
    Entry_803EB32C mEntries[2];
    int mCurrent;
    Object_8003DEC4 *mpPlayers[2];
    float mUnknown244[2];
    unsigned char mQueue[2];
    unsigned char mQueueCount;
    unsigned char mUnknown24F[2];
    unsigned char mUnknown251[2];
    unsigned char mUnknown253;
};

typedef void (*Callback_8015C25C)(Object_8003DEC4 *pPlayer);

extern "C" {
void fn_80023024(int a);
void fn_8003E194(int index, int value);
void fn_8015F958(int a, Ids_8015F6E8 *pIds, Object_8003DEC4 *pPlayer, Callback_8015C25C pCallback);
void fn_8015FB38(int a, int id, Object_8003DEC4 *pPlayer, Callback_8015C25C pCallback);
void fn_8015FC54(int a, int id, Object_8003DEC4 *pPlayer, Callback_8015C25C pCallback);
void fn_8015FD70(int a, int id, Object_8003DEC4 *pPlayer, Callback_8015C25C pCallback);
int fn_8015F5BC(const char *pName);
void fn_8015FE4C(void);
void fn_8015FFC8(int player, int key, int value);
void fn_8016118C(void);
void fn_801611BC(int index, const char *pName, int a);
void fn_8016130C(int index, int a, int b, int c, int d);
void fn_801613F0(void);
void fn_801A46E0(Object_8003DEC4 *pPlayer, int id, Callback_8015C25C pCallback);
void fn_801A472C(void);
void fn_801A4AD4(Object_8003DEC4 *pPlayer);
void fn_80233C7C(void *p);
void fn_80234A14(void *p, int a);
int fn_8007CB6C(int index);

void fn_8015C498(void);
void fn_8015CB18(int wait);
void fn_8015CCB4(int wait);
}

static unsigned char lbl_803EB328 = 0;
static State_803EB32C *lbl_803EB32C = 0;

extern "C" void fn_8015C25C(Object_8003DEC4 *pPlayer)
{
    State_803EB32C *pState = lbl_803EB32C;
    Entry_803EB32C *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown992[1852], 1);
    fn_80234A14(&pPlayer->mUnknown992[2092], 1);
    fn_80233C7C(&pPlayer->mUnknown992[1872]);
    fn_80233CBC(&pPlayer->mUnknown992[1872], 27, 0);
    fn_80049C50(pPlayer->mUnknown4971, pPlayer->mUnknown4970);
    pEntry->mUnknownFA &= ~0x21;
}

extern "C" void fn_8015C2E0(Object_8003DEC4 *pPlayer)
{
    State_803EB32C *pState = lbl_803EB32C;
    Entry_803EB32C *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown992[1612], 1);
    fn_80233C7C(&pPlayer->mUnknown992[1632]);
    fn_80233CBC(&pPlayer->mUnknown992[1632], 0, 0);
    pEntry->mUnknownFA &= ~0x42;
}

extern "C" void fn_8015C34C(Object_8003DEC4 *pPlayer)
{
    State_803EB32C *pState = lbl_803EB32C;
    Entry_803EB32C *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown992[2332], 1);
    fn_80233C7C(&pPlayer->mUnknown992[2352]);
    fn_80233CBC(&pPlayer->mUnknown992[2352], 28, 0);
    pEntry->mUnknownFA &= ~0x84;
}

extern "C" void fn_8015C3B8(Object_8003DEC4 *pPlayer)
{
    State_803EB32C *pState = lbl_803EB32C;
    Entry_803EB32C *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown992[2812], 1);
    fn_80233C7C(&pPlayer->mUnknown992[2832]);
    fn_80233CBC(&pPlayer->mUnknown992[2832], 29, 0);
    fn_80233C7C(&pPlayer->mUnknown992[2832]);
    fn_80233CBC(&pPlayer->mUnknown992[2832], 30, 0);
    pEntry->mUnknownFA &= ~0x210;
}

extern "C" void fn_8015C43C(Object_8003DEC4 *pPlayer)
{
    State_803EB32C *pState = lbl_803EB32C;
    Entry_803EB32C *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown992[1132], 1);
    fn_80234A14(&pPlayer->mUnknown992[1372], 1);
    pEntry->mUnknownFA &= ~0x108;
}

/* Starts loading the next pending part of the current request. */
extern "C" void fn_8015C498(void)
{
    State_803EB32C *pState = lbl_803EB32C;
    int index = pState->mCurrent;
    Entry_803EB32C *pEntry;
    Object_8003DEC4 *pPlayer;

    if (index == 2) {
        return;
    }
    pEntry = &pState->mEntries[index];
    pPlayer = fn_8003DEC4(index);
    if (!(pEntry->mUnknownFA & 0x1F)) {
        return;
    }
    if (pEntry->mUnknownFA & 0x3E0) {
        return;
    }
    if ((pEntry->mUnknownFA & 0x2) && !(pEntry->mUnknownFA & 0x40)) {
        pEntry->mUnknownFA |= 0x40;
        fn_8015F958(pPlayer->mUnknown4970, &pEntry->mUnknown4, pPlayer, fn_8015C2E0);
    } else if ((pEntry->mUnknownFA & 0x8) && !(pEntry->mUnknownFA & 0x100)) {
        pEntry->mUnknownFA |= 0x100;
        fn_801A46E0(pPlayer, pEntry->mUnknownC, fn_8015C43C);
    } else if ((pEntry->mUnknownFA & 0x1) && !(pEntry->mUnknownFA & 0x20)) {
        pEntry->mUnknownFA |= 0x20;
        fn_8015FB38(pPlayer->mUnknown4970, pEntry->mUnknownE8, pPlayer, fn_8015C25C);
    } else if ((pEntry->mUnknownFA & 0x4) && !(pEntry->mUnknownFA & 0x80)) {
        pEntry->mUnknownFA |= 0x80;
        fn_8015FC54(pPlayer->mUnknown4970, pEntry->mUnknownEC, pPlayer, fn_8015C34C);
    } else if ((pEntry->mUnknownFA & 0x10) && !(pEntry->mUnknownFA & 0x200)) {
        pEntry->mUnknownFA |= 0x200;
        fn_8015FD70(pPlayer->mUnknown4970, pEntry->mUnknownF0, pPlayer, fn_8015C3B8);
    }
}

/* Makes index the current request and works out which parts must be loaded. */
extern "C" void fn_8015C5E8(int index)
{
    State_803EB32C *pState = lbl_803EB32C;
    Entry_803EB32C *pEntry;
    Object_8003DEC4 *pPlayer;
    Block_80307980 block;
    FMCAPPORTValues values;
    Ids_8015F6E8 ids;
    char *pName;
    int head;
    int idE8;
    int idEC;
    int idF0;

    pState->mCurrent = index;
    pEntry = &pState->mEntries[index];
    pName = pEntry->mUnknownFE;
    pEntry->mUnknownFC = 0;
    pEntry->mUnknownF8 = 0;
    pEntry->mUnknownF9 = 0;
    pEntry->mUnknownFA = 0x1F;
    pPlayer = fn_8003DEC4(index);
    fn_8003E194(index, fn_80049BC0(pPlayer->mUnknown4971));
    fn_80049FC8(pPlayer->mUnknown4971, &block);
    fn_80046804(&block, &values);
    if (strlen(pName)) {
        fn_80049E00(pPlayer->mUnknown4971, pName, &ids);
        head = fn_8015F5BC(pName);
    } else {
        fn_80049E00(pPlayer->mUnknown4971, 0, &ids);
        head = 0xFFFF;
    }

    if (pEntry->mUnknownF4 && !memcmp(&pEntry->mUnknown4, &ids, sizeof(ids))) {
        pEntry->mUnknownFA &= ~0x2;
    } else {
        memcpy(&pEntry->mUnknown4, &ids, sizeof(ids));
    }

    if (pEntry->mUnknownF4 && pEntry->mUnknownC == head &&
        pEntry->mUnknown10 == fn_80049C38(pPlayer->mUnknown4970) &&
        !memcmp(&pEntry->mUnknown14, &values, sizeof(values))) {
        pEntry->mUnknownFA &= ~0x8;
    } else {
        pEntry->mUnknownC = head;
        pEntry->mUnknown10 = fn_80049C38(pPlayer->mUnknown4970);
        pPlayer->mUnknown4972 = pEntry->mUnknown10;
        pEntry->mUnknown14 = values;
        pPlayer->mUnknown4976 = pEntry->mUnknown14;
    }

    idE8 = fn_80049888(pPlayer->mUnknown4971);
    if (pEntry->mUnknownF4 && pEntry->mUnknownE8 == idE8) {
        pEntry->mUnknownFA &= ~0x1;
    } else {
        pEntry->mUnknownE8 = idE8;
        if (idE8 == 0xFFFF) {
            pEntry->mUnknownFA &= ~0x1;
            fn_8015FFC8(index, 27, 255);
        }
    }

    idEC = fn_800499A8(pPlayer->mUnknown4971);
    if (pEntry->mUnknownF4 && pEntry->mUnknownEC == idEC) {
        pEntry->mUnknownFA &= ~0x4;
    } else {
        pEntry->mUnknownEC = idEC;
        if (idEC == 0xFFFF) {
            pEntry->mUnknownFA &= ~0x4;
            fn_8015FFC8(index, 28, 255);
        }
    }

    idF0 = fn_800499E8(pPlayer->mUnknown4971);
    if (pEntry->mUnknownF4 && pEntry->mUnknownF0 == idF0) {
        pEntry->mUnknownFA &= ~0x10;
    } else {
        pEntry->mUnknownF0 = idF0;
        if (idEC == 0xFFFF) {
            pEntry->mUnknownFA &= ~0x10;
            fn_8015FFC8(index, 29, 255);
            fn_8015FFC8(index, 30, 255);
        }
    }

    pEntry->mUnknownF4 = 1;
    fn_8015C498();
}

/* Returns the slot of mpPlayers that holds pPlayer. */
extern "C" int fn_8015C9B4(Object_8003DEC4 *pPlayer)
{
    int index = pPlayer->mUnknown4969;
    int slot = index + 1;

    if (lbl_803EB32C->mpPlayers[index] == pPlayer) {
        slot = index;
    }
    return slot;
}

/* Queues (or re-queues) request index, keeping the queue ordered by priority. */
extern "C" void fn_8015C9E0(int index, unsigned int priority, unsigned char queue)
{
    Entry_803EB32C *pEntry = &lbl_803EB32C->mEntries[index];
    unsigned int i;
    int n;

    pEntry->mUnknownF6 = priority;
    if (pEntry->mUnknownFC) {
        for (i = 0; i < lbl_803EB32C->mQueueCount; i++) {
            if (lbl_803EB32C->mQueue[i] == index) {
                lbl_803EB32C->mQueueCount--;
                for (; i < lbl_803EB32C->mQueueCount; i++) {
                    lbl_803EB32C->mQueue[i] = lbl_803EB32C->mQueue[i + 1];
                }
                break;
            }
        }
    } else {
        pEntry->mUnknownFC = queue;
    }
    if (!pEntry->mUnknownFC) {
        return;
    }

    n = lbl_803EB32C->mQueueCount;
    while (n != 0 && lbl_803EB32C->mEntries[lbl_803EB32C->mQueue[n - 1]].mUnknownF6 < priority) {
        lbl_803EB32C->mQueue[n] = lbl_803EB32C->mQueue[n - 1];
        n--;
    }
    lbl_803EB32C->mQueue[n] = index;
    lbl_803EB32C->mQueueCount++;
    if (lbl_803EB32C->mUnknown24F[index] == 0) {
        lbl_803EB32C->mUnknown244[index] = 0.0f;
        lbl_803EB32C->mUnknown251[index] = 0;
    }
}

/* Waits for the current request's loads to finish. */
extern "C" void fn_8015CB18(int wait)
{
    State_803EB32C *pState = lbl_803EB32C;
    Entry_803EB32C *pEntry;
    unsigned int count;

    if (pState->mCurrent == 2) {
        return;
    }
    pEntry = &pState->mEntries[pState->mCurrent];
    if (pEntry->mUnknownFA & 0x3E0) {
        count = 0;
        while (pEntry->mUnknownFA & 0x3E0) {
            fn_8015FE4C();
            count++;
            fn_801A472C();
            if (count > 4) {
                count = 0;
                if (wait) {
                    fn_80023024(1);
                }
            }
        }
    } else if (pEntry->mUnknownF8) {
        fn_8016118C();
        fn_801613F0();
    }
}

extern "C" void fn_8015CBC8(void)
{
    State_803EB32C *pState;

    lbl_803EB328 = 1;
    pState = (State_803EB32C *)fn_801D2B7C(sizeof(State_803EB32C), 0, 0);
    lbl_803EB32C = pState;
    pState->mCurrent = 2;
    pState->mQueueCount = 0;
    fn_8015CCB4(0);
}

extern "C" void fn_8015CC1C(void)
{
    State_803EB32C *pState;
    Entry_803EB32C *pEntry;

    lbl_803EB32C->mQueueCount = 0;
    pState = lbl_803EB32C;
    if (pState->mCurrent != 2) {
        pEntry = &pState->mEntries[pState->mCurrent];
        if (pEntry->mUnknownFA & 0x3E0) {
            while (pEntry->mUnknownFA & 0x3E0) {
                fn_8015FE4C();
                fn_801A472C();
            }
        } else if (pEntry->mUnknownF8) {
            fn_8016118C();
        }
    }
    fn_801D2BD0(lbl_803EB32C);
    lbl_803EB32C = 0;
    lbl_803EB328 = 0;
}

extern "C" void fn_8015CCB4(int wait)
{
    unsigned int i;

    if (!lbl_803EB328) {
        return;
    }
    lbl_803EB32C->mQueueCount = 0;
    fn_8015CB18(wait);
    for (i = 0; i < 2; i++) {
        lbl_803EB32C->mpPlayers[i] = fn_8003DEC4(i);
        lbl_803EB32C->mUnknown244[i] = 0.0f;
        lbl_803EB32C->mUnknown24F[i] = 0;
        lbl_803EB32C->mUnknown251[i] = 0;
        lbl_803EB32C->mEntries[i].mUnknownF8 = 0;
        lbl_803EB32C->mEntries[i].mUnknownFC = 0;
        lbl_803EB32C->mEntries[i].mUnknownF4 = 0;
        lbl_803EB32C->mEntries[i].mUnknownFD = 0;
    }
    lbl_803EB32C->mCurrent = 2;
    lbl_803EB32C->mUnknown253 = 1;
}

extern "C" unsigned char fn_8015CD9C(void)
{
    return lbl_803EB328;
}

/* Per-frame update: steps the two per-player 0..1 ramp values and starts the
   next queued request once the current one has finished. */
extern "C" void fn_8015CDA4(void)
{
    unsigned int i;
    State_803EB32C *pState;
    Entry_803EB32C *pEntry;
    Object_8003DEC4 *pPlayer;
    int current;

    if (!lbl_803EB328) {
        return;
    }
    fn_8015C498();
    fn_8015FE4C();
    fn_801A472C();
    for (i = 0; i < 2; i++) {
        pState = lbl_803EB32C;
        pEntry = &pState->mEntries[i];
        if (pEntry->mUnknownFC) {
            if (pState->mUnknown244[i] > 0.0f) {
                if (pState->mUnknown253) {
                    pState->mUnknown244[i] -= 0.1f;
                } else {
                    pState->mUnknown244[i] = 0.0f;
                }
                if (lbl_803EB32C->mUnknown244[i] <= 0.0f) {
                    lbl_803EB32C->mUnknown244[i] = 0.0f;
                    lbl_803EB32C->mUnknown251[i] = 0;
                }
            } else if (pEntry->mUnknownF7) {
                pEntry->mUnknownF7--;
            }
        } else if (pState->mUnknown251[i]) {
            if (!pEntry->mUnknownFD) {
                if (pState->mUnknown244[i] > 0.0f) {
                    if (pState->mUnknown253) {
                        pState->mUnknown244[i] -= 0.1f;
                    } else {
                        pState->mUnknown244[i] = 0.0f;
                    }
                    if (lbl_803EB32C->mUnknown244[i] <= 0.0f) {
                        lbl_803EB32C->mUnknown244[i] = 0.0f;
                        lbl_803EB32C->mUnknown251[i] = 0;
                    }
                }
            } else if (pState->mUnknown244[i] < 1.0f) {
                pState->mUnknown244[i] += 0.1f;
                if (pState->mUnknown244[i] > 1.0f || !pState->mUnknown253) {
                    pState->mUnknown244[i] = 1.0f;
                }
            }
        }
        lbl_803EB32C->mUnknown24F[i] = 0;
    }

    current = lbl_803EB32C->mCurrent;
    if (current != 2) {
        i = current;
        if (lbl_803EB32C->mEntries[i].mUnknownFA == 0 && lbl_803EB32C->mEntries[i].mUnknownF8 == 0) {
            pPlayer = fn_8003DEC4(i);
            lbl_803EB32C->mEntries[i].mUnknownF8 = 1;
            if (strlen(lbl_803EB32C->mEntries[i].mUnknownFE)) {
                fn_801611BC(pPlayer->mUnknown4971, lbl_803EB32C->mEntries[i].mUnknownFE, 0);
            } else {
                fn_8016130C(pPlayer->mUnknown4971, fn_80049EC8(i), fn_80049EE0(i), fn_80049EF8(i), 0);
            }
            fn_80049124(current);
        }
    } else if (lbl_803EB32C->mQueueCount) {
        i = lbl_803EB32C->mQueue[0];
        if (lbl_803EB32C->mEntries[i].mUnknownF7 == 0) {
            fn_8015C5E8(i);
            lbl_803EB32C->mQueueCount--;
            for (i = 0; i < lbl_803EB32C->mQueueCount; i++) {
                lbl_803EB32C->mQueue[i] = lbl_803EB32C->mQueue[i + 1];
            }
        }
    }
}

/* Queues a request for player index; it counts as changed when forced or when
   the stored name or the compared player values differ. */
extern "C" void fn_8015D060(int index, const char *pName, unsigned char priority, int force)
{
    Entry_803EB32C *pEntry;
    Object_8003DEC4 *pPlayer;
    int flag;

    if (!lbl_803EB328) {
        return;
    }
    pEntry = &lbl_803EB32C->mEntries[index];
    pPlayer = fn_8003DEC4(index);
    flag = pPlayer->mUnknown4968 == fn_8007CB6C(fn_8007CB6C(2) ? 1 : 0);
    if (force || !pEntry->mUnknownFD || pEntry->mUnknown0 != pPlayer->mUnknown4956 ||
        pEntry->mUnknownF5 != flag || strcmp(pEntry->mUnknownFE, pName)) {
        pEntry->mUnknownF5 = flag;
        pEntry->mUnknown0 = pPlayer->mUnknown4956;
        pEntry->mUnknownF7 = 4;
        flag = 1;
        strcpy(pEntry->mUnknownFE, pName);
        pEntry->mUnknownFD = 1;
    } else {
        flag = 0;
    }
    fn_800496A0(index, pPlayer->mUnknown4971, pPlayer->mUnknown4968, pPlayer->mUnknown4956);
    fn_8015C9E0(index, priority, flag);
}

extern "C" void fn_8015D180(int index, unsigned char priority)
{
    Entry_803EB32C *pEntry;

    if (!lbl_803EB328) {
        return;
    }
    pEntry = &lbl_803EB32C->mEntries[index];
    pEntry->mUnknownF7 = 4;
    pEntry->mUnknownFD = 1;
    fn_8015C9E0(index, priority, 1);
}

extern "C" void fn_8015D1CC(int index, unsigned char priority)
{
    if (lbl_803EB328) {
        fn_8015C9E0(index, priority, 0);
    }
}

extern "C" unsigned char fn_8015D1FC(int index)
{
    if (lbl_803EB328) {
        return lbl_803EB32C->mEntries[index].mUnknownFC;
    }
    return 0;
}

extern "C" void fn_8015D224(int index)
{
    if (!lbl_803EB328) {
        return;
    }
    lbl_803EB32C->mEntries[index].mUnknownFD = 0;
    lbl_803EB32C->mEntries[index].mUnknownF4 = 0;
}

extern "C" void fn_8015D254(int index)
{
    State_803EB32C *pState;
    Entry_803EB32C *pEntry;
    int current;

    if (!lbl_803EB328) {
        return;
    }
    pState = lbl_803EB32C;
    current = pState->mCurrent;
    if (current != index) {
        return;
    }
    pEntry = &pState->mEntries[current];
    if (!pEntry->mUnknownF8) {
        return;
    }
    pEntry->mUnknownF9 = 1;
    fn_801A4AD4(fn_8003DEC4(current));
    lbl_803EB32C->mCurrent = 2;
    if (!pEntry->mUnknownFC && pEntry->mUnknownFD) {
        lbl_803EB32C->mUnknown251[current] = 1;
    }
}

extern "C" unsigned char fn_8015D2E8(Object_8003DEC4 *pPlayer)
{
    int slot;

    if (!lbl_803EB328) {
        return 1;
    }
    slot = fn_8015C9B4(pPlayer);
    return lbl_803EB32C->mUnknown251[slot];
}

extern "C" void fn_8015D32C(Object_8003DEC4 *pPlayer, float *pScale)
{
    float scale;
    int slot;

    if (lbl_803EB328) {
        slot = fn_8015C9B4(pPlayer);
        scale = lbl_803EB32C->mUnknown244[slot];
    } else {
        scale = 1.0f;
    }
    pScale[0] = scale;
    pScale[1] = scale;
    pScale[2] = scale;
}

extern "C" unsigned char fn_8015D38C(unsigned char value)
{
    unsigned char old = 1;

    if (lbl_803EB328) {
        old = lbl_803EB32C->mUnknown253;
        lbl_803EB32C->mUnknown253 = value;
    }
    return old;
}

extern "C" void fn_8015D3B0(Object_8003DEC4 *pPlayer)
{
    if (lbl_803EB328) {
        lbl_803EB32C->mUnknown24F[fn_8015C9B4(pPlayer)] = 1;
    }
}
