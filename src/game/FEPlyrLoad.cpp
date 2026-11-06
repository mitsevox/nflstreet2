/* Front-end player model loading: keeps one appearance request for each of the
   two front-end player models, queued by priority, and loads one at a time. A
   request compares the player's look with what the model already shows and
   streams only the head, face, hat, slot-1 and accessory parts that changed,
   then rebuilds the model's textures. Once a request is done the model
   scales in from 0 to 1, and it scales back out while a new request for it
   waits in the queue. */

#include "game/FaceFeatures.h"
#include "game/FEPlyrLoad.h"
#include "game/Object_8003DEC4.h"
#include "game/PlayerLook.h"
#include "game/cu_8015D3EC.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80233CBC.h"

#include <string.h>

/* Per-player model request (0x11C bytes). The halfword at +0xFA keeps one
   "needs loading" bit (0x01-0x10) and one "loading" bit (0x20-0x200) for
   each of the five parts loaded asynchronously by FEPlyrLoadStartNextPart. */
struct FEPlyrLoadRequest_t {
    int mUnknown0;
    PlayerHeadIds_t mUnknown4;
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

/* State allocated by FEPlyrLoadInit (0x254 bytes). */
struct FEPlyrLoadState_t {
    FEPlyrLoadRequest_t mEntries[2];
    int mCurrent;
    Object_8003DEC4 *mpPlayers[2];
    float mUnknown244[2];
    unsigned char mQueue[2];
    unsigned char mQueueCount;
    unsigned char mUnknown24F[2];
    unsigned char mUnknown251[2];
    unsigned char mUnknown253;
};

extern "C" {
void FESndUpdate(int a);
void fn_8003E194(int index, int value);
void fn_8015FFC8(int player, int key, int value);
void fn_8016118C(void);
void fn_801611BC(int index, const char *pName, int a);
void fn_8016130C(int index, int a, int b, int c, int d);
void fn_801613F0(void);
void fn_801A46E0(Object_8003DEC4 *pPlayer, int id, Callback_8015F958 pCallback);
void fn_801A472C(void);
void PlyrTexRequestNameplate(Object_8003DEC4 *pPlayer);
void fn_80233C7C(void *p);
void fn_80234A14(void *p, int a);
int GameInfoGet(int index);

void FEPlyrLoadStartNextPart(void);
void FEPlyrLoadWait(int wait);
void FEPlyrLoadReset(int wait);
}

static unsigned char _FEPlyrLoad_bActive = 0;
static FEPlyrLoadState_t *_FEPlyrLoad_pState = 0;

extern "C" void FEPlyrLoadHatDone(Object_8003DEC4 *pPlayer)
{
    FEPlyrLoadState_t *pState = _FEPlyrLoad_pState;
    FEPlyrLoadRequest_t *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown1164[7], 1);
    fn_80234A14(&pPlayer->mUnknown1164[8], 1);
    fn_80233C7C(&pPlayer->mUnknown1164[7].mUnknown20);
    fn_80233CBC(&pPlayer->mUnknown1164[7].mUnknown20, 27, 0);
    PlayerLookApplyHeadDecal(pPlayer->mUnknown4971, pPlayer->mUnknown4970);
    pEntry->mUnknownFA &= ~0x21;
}

extern "C" void FEPlyrLoadHeadDone(Object_8003DEC4 *pPlayer)
{
    FEPlyrLoadState_t *pState = _FEPlyrLoad_pState;
    FEPlyrLoadRequest_t *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown1164[6], 1);
    fn_80233C7C(&pPlayer->mUnknown1164[6].mUnknown20);
    fn_80233CBC(&pPlayer->mUnknown1164[6].mUnknown20, 0, 0);
    pEntry->mUnknownFA &= ~0x42;
}

extern "C" void FEPlyrLoadSlot1Done(Object_8003DEC4 *pPlayer)
{
    FEPlyrLoadState_t *pState = _FEPlyrLoad_pState;
    FEPlyrLoadRequest_t *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown1164[9], 1);
    fn_80233C7C(&pPlayer->mUnknown1164[9].mUnknown20);
    fn_80233CBC(&pPlayer->mUnknown1164[9].mUnknown20, 28, 0);
    pEntry->mUnknownFA &= ~0x84;
}

extern "C" void FEPlyrLoadAccessoryDone(Object_8003DEC4 *pPlayer)
{
    FEPlyrLoadState_t *pState = _FEPlyrLoad_pState;
    FEPlyrLoadRequest_t *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown1164[11], 1);
    fn_80233C7C(&pPlayer->mUnknown1164[11].mUnknown20);
    fn_80233CBC(&pPlayer->mUnknown1164[11].mUnknown20, 29, 0);
    fn_80233C7C(&pPlayer->mUnknown1164[11].mUnknown20);
    fn_80233CBC(&pPlayer->mUnknown1164[11].mUnknown20, 30, 0);
    pEntry->mUnknownFA &= ~0x210;
}

extern "C" void FEPlyrLoadFaceDone(Object_8003DEC4 *pPlayer)
{
    FEPlyrLoadState_t *pState = _FEPlyrLoad_pState;
    FEPlyrLoadRequest_t *pEntry = &pState->mEntries[pState->mCurrent];

    fn_80234A14(&pPlayer->mUnknown1164[4], 1);
    fn_80234A14(&pPlayer->mUnknown1164[5], 1);
    pEntry->mUnknownFA &= ~0x108;
}

/* Starts loading the next pending part of the current request. */
extern "C" void FEPlyrLoadStartNextPart(void)
{
    FEPlyrLoadState_t *pState = _FEPlyrLoad_pState;
    int index = pState->mCurrent;
    FEPlyrLoadRequest_t *pEntry;
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
        fn_8015F958(pPlayer->mUnknown4970, &pEntry->mUnknown4, pPlayer, FEPlyrLoadHeadDone);
    } else if ((pEntry->mUnknownFA & 0x8) && !(pEntry->mUnknownFA & 0x100)) {
        pEntry->mUnknownFA |= 0x100;
        fn_801A46E0(pPlayer, pEntry->mUnknownC, FEPlyrLoadFaceDone);
    } else if ((pEntry->mUnknownFA & 0x1) && !(pEntry->mUnknownFA & 0x20)) {
        pEntry->mUnknownFA |= 0x20;
        fn_8015FB38(pPlayer->mUnknown4970, pEntry->mUnknownE8, pPlayer, FEPlyrLoadHatDone);
    } else if ((pEntry->mUnknownFA & 0x4) && !(pEntry->mUnknownFA & 0x80)) {
        pEntry->mUnknownFA |= 0x80;
        fn_8015FC54(pPlayer->mUnknown4970, pEntry->mUnknownEC, pPlayer, FEPlyrLoadSlot1Done);
    } else if ((pEntry->mUnknownFA & 0x10) && !(pEntry->mUnknownFA & 0x200)) {
        pEntry->mUnknownFA |= 0x200;
        fn_8015FD70(pPlayer->mUnknown4970, pEntry->mUnknownF0, pPlayer, FEPlyrLoadAccessoryDone);
    }
}

/* Makes index the current request and works out which parts must be loaded. */
extern "C" void FEPlyrLoadBegin(int index)
{
    FEPlyrLoadState_t *pState = _FEPlyrLoad_pState;
    FEPlyrLoadRequest_t *pEntry;
    Object_8003DEC4 *pPlayer;
    FaceFeatures_t block;
    FMCAPPORTValues values;
    PlayerHeadIds_t ids;
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
    fn_8003E194(index, PlayerLookGetBodyType(pPlayer->mUnknown4971));
    PlayerLookGetFeatures(pPlayer->mUnknown4971, &block);
    FaceMorphBuildWeights(&block, &values);
    if (strlen(pName)) {
        PlayerLookGetHeadIds(pPlayer->mUnknown4971, pName, &ids);
        head = fn_8015F5BC(pName);
    } else {
        PlayerLookGetHeadIds(pPlayer->mUnknown4971, 0, &ids);
        head = 0xFFFF;
    }

    if (pEntry->mUnknownF4 && !memcmp(&pEntry->mUnknown4, &ids, sizeof(ids))) {
        pEntry->mUnknownFA &= ~0x2;
    } else {
        memcpy(&pEntry->mUnknown4, &ids, sizeof(ids));
    }

    if (pEntry->mUnknownF4 && pEntry->mUnknownC == head &&
        pEntry->mUnknown10 == PlayerLookGetPlex(pPlayer->mUnknown4970) &&
        !memcmp(&pEntry->mUnknown14, &values, sizeof(values))) {
        pEntry->mUnknownFA &= ~0x8;
    } else {
        pEntry->mUnknownC = head;
        pEntry->mUnknown10 = PlayerLookGetPlex(pPlayer->mUnknown4970);
        pPlayer->mUnknown4972 = pEntry->mUnknown10;
        pEntry->mUnknown14 = values;
        pPlayer->mUnknown4976 = pEntry->mUnknown14;
    }

    idE8 = PlayerLookGetHatModel(pPlayer->mUnknown4971);
    if (pEntry->mUnknownF4 && pEntry->mUnknownE8 == idE8) {
        pEntry->mUnknownFA &= ~0x1;
    } else {
        pEntry->mUnknownE8 = idE8;
        if (idE8 == 0xFFFF) {
            pEntry->mUnknownFA &= ~0x1;
            fn_8015FFC8(index, 27, 255);
        }
    }

    idEC = PlayerLookGetSlot1Model(pPlayer->mUnknown4971);
    if (pEntry->mUnknownF4 && pEntry->mUnknownEC == idEC) {
        pEntry->mUnknownFA &= ~0x4;
    } else {
        pEntry->mUnknownEC = idEC;
        if (idEC == 0xFFFF) {
            pEntry->mUnknownFA &= ~0x4;
            fn_8015FFC8(index, 28, 255);
        }
    }

    idF0 = PlayerLookGetAccessoryModel(pPlayer->mUnknown4971);
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
    FEPlyrLoadStartNextPart();
}

/* Returns the slot of mpPlayers that holds pPlayer. */
extern "C" int FEPlyrLoadGetSlot(Object_8003DEC4 *pPlayer)
{
    int index = pPlayer->mUnknown4969;
    int slot = index + 1;

    if (_FEPlyrLoad_pState->mpPlayers[index] == pPlayer) {
        slot = index;
    }
    return slot;
}

/* Queues (or re-queues) request index, keeping the queue ordered by priority. */
extern "C" void FEPlyrLoadQueue(int index, unsigned int priority, unsigned char queue)
{
    FEPlyrLoadRequest_t *pEntry = &_FEPlyrLoad_pState->mEntries[index];
    unsigned int i;
    int n;

    pEntry->mUnknownF6 = priority;
    if (pEntry->mUnknownFC) {
        for (i = 0; i < _FEPlyrLoad_pState->mQueueCount; i++) {
            if (_FEPlyrLoad_pState->mQueue[i] == index) {
                _FEPlyrLoad_pState->mQueueCount--;
                for (; i < _FEPlyrLoad_pState->mQueueCount; i++) {
                    _FEPlyrLoad_pState->mQueue[i] = _FEPlyrLoad_pState->mQueue[i + 1];
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

    n = _FEPlyrLoad_pState->mQueueCount;
    for (;;) {
        if (n == 0 || _FEPlyrLoad_pState->mEntries[_FEPlyrLoad_pState->mQueue[n - 1]].mUnknownF6 >= priority) {
            _FEPlyrLoad_pState->mQueue[n] = index;
            break;
        }
        _FEPlyrLoad_pState->mQueue[n] = _FEPlyrLoad_pState->mQueue[n - 1];
        n--;
    }
    _FEPlyrLoad_pState->mQueueCount++;
    if (_FEPlyrLoad_pState->mUnknown24F[index] == 0) {
        _FEPlyrLoad_pState->mUnknown244[index] = 0.0f;
        _FEPlyrLoad_pState->mUnknown251[index] = 0;
    }
}

/* Waits for the current request's loads to finish. */
extern "C" void FEPlyrLoadWait(int wait)
{
    FEPlyrLoadState_t *pState = _FEPlyrLoad_pState;
    FEPlyrLoadRequest_t *pEntry;
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
                    FESndUpdate(1);
                }
            }
        }
    } else if (pEntry->mUnknownF8) {
        fn_8016118C();
        fn_801613F0();
    }
}

extern "C" void FEPlyrLoadInit(void)
{
    FEPlyrLoadState_t *pState;

    _FEPlyrLoad_bActive = 1;
    pState = (FEPlyrLoadState_t *)fn_801D2B7C(sizeof(FEPlyrLoadState_t), 0, 0);
    _FEPlyrLoad_pState = pState;
    pState->mCurrent = 2;
    pState->mQueueCount = 0;
    FEPlyrLoadReset(0);
}

extern "C" void FEPlyrLoadShutdown(void)
{
    FEPlyrLoadState_t *pState;
    FEPlyrLoadRequest_t *pEntry;

    _FEPlyrLoad_pState->mQueueCount = 0;
    pState = _FEPlyrLoad_pState;
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
    fn_801D2BD0(_FEPlyrLoad_pState);
    _FEPlyrLoad_pState = 0;
    _FEPlyrLoad_bActive = 0;
}

extern "C" void FEPlyrLoadReset(int wait)
{
    unsigned int i;

    if (!_FEPlyrLoad_bActive) {
        return;
    }
    _FEPlyrLoad_pState->mQueueCount = 0;
    FEPlyrLoadWait(wait);
    for (i = 0; i < 2; i++) {
        _FEPlyrLoad_pState->mpPlayers[i] = fn_8003DEC4(i);
        _FEPlyrLoad_pState->mUnknown244[i] = 0.0f;
        _FEPlyrLoad_pState->mUnknown24F[i] = 0;
        _FEPlyrLoad_pState->mUnknown251[i] = 0;
        _FEPlyrLoad_pState->mEntries[i].mUnknownF8 = 0;
        _FEPlyrLoad_pState->mEntries[i].mUnknownFC = 0;
        _FEPlyrLoad_pState->mEntries[i].mUnknownF4 = 0;
        _FEPlyrLoad_pState->mEntries[i].mUnknownFD = 0;
    }
    _FEPlyrLoad_pState->mCurrent = 2;
    _FEPlyrLoad_pState->mUnknown253 = 1;
}

extern "C" unsigned char FEPlyrLoadIsActive(void)
{
    return _FEPlyrLoad_bActive;
}

/* Per-frame update: steps the two per-player 0..1 ramp values and starts the
   next queued request once the current one has finished. */
extern "C" void FEPlyrLoadUpdate(void)
{
    unsigned int i;
    FEPlyrLoadState_t *pState;
    FEPlyrLoadRequest_t *pEntry;
    Object_8003DEC4 *pPlayer;
    int current;

    if (!_FEPlyrLoad_bActive) {
        return;
    }
    FEPlyrLoadStartNextPart();
    fn_8015FE4C();
    fn_801A472C();
    for (i = 0; i < 2; i++) {
        pState = _FEPlyrLoad_pState;
        pEntry = &pState->mEntries[i];
        if (pEntry->mUnknownFC) {
            if (pState->mUnknown244[i] > 0.0f) {
                if (pState->mUnknown253) {
                    pState->mUnknown244[i] -= 0.1f;
                } else {
                    pState->mUnknown244[i] = 0.0f;
                }
                if (_FEPlyrLoad_pState->mUnknown244[i] <= 0.0f) {
                    _FEPlyrLoad_pState->mUnknown244[i] = 0.0f;
                    _FEPlyrLoad_pState->mUnknown251[i] = 0;
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
                    if (_FEPlyrLoad_pState->mUnknown244[i] <= 0.0f) {
                        _FEPlyrLoad_pState->mUnknown244[i] = 0.0f;
                        _FEPlyrLoad_pState->mUnknown251[i] = 0;
                    }
                }
            } else if (pState->mUnknown244[i] < 1.0f) {
                pState->mUnknown244[i] += 0.1f;
                if (pState->mUnknown244[i] > 1.0f || !pState->mUnknown253) {
                    pState->mUnknown244[i] = 1.0f;
                }
            }
        }
        _FEPlyrLoad_pState->mUnknown24F[i] = 0;
    }

    current = _FEPlyrLoad_pState->mCurrent;
    if (current != 2) {
        i = current;
        if (_FEPlyrLoad_pState->mEntries[i].mUnknownFA == 0 && _FEPlyrLoad_pState->mEntries[i].mUnknownF8 == 0) {
            pPlayer = fn_8003DEC4(i);
            _FEPlyrLoad_pState->mEntries[i].mUnknownF8 = 1;
            if (strlen(_FEPlyrLoad_pState->mEntries[i].mUnknownFE)) {
                fn_801611BC(pPlayer->mUnknown4971, _FEPlyrLoad_pState->mEntries[i].mUnknownFE, 0);
            } else {
                fn_8016130C(pPlayer->mUnknown4971, PlayerLookGetSkin(i), PlayerLookGetFace(i), PlayerLookGetBrow(i), 0);
            }
            PlayerLookApply(current);
        }
    } else if (_FEPlyrLoad_pState->mQueueCount) {
        i = _FEPlyrLoad_pState->mQueue[0];
        if (_FEPlyrLoad_pState->mEntries[i].mUnknownF7 == 0) {
            FEPlyrLoadBegin(i);
            _FEPlyrLoad_pState->mQueueCount--;
            for (i = 0; i < _FEPlyrLoad_pState->mQueueCount; i++) {
                _FEPlyrLoad_pState->mQueue[i] = _FEPlyrLoad_pState->mQueue[i + 1];
            }
        }
    }
}

/* Queues a request for player index; it counts as changed when forced or when
   the stored name or the compared player values differ. */
extern "C" void FEPlyrLoadRequest(int index, const char *pName, unsigned char priority, int force)
{
    FEPlyrLoadRequest_t *pEntry;
    Object_8003DEC4 *pPlayer;
    unsigned char team;
    int changed;

    if (!_FEPlyrLoad_bActive) {
        return;
    }
    pEntry = &_FEPlyrLoad_pState->mEntries[index];
    pPlayer = fn_8003DEC4(index);
    if (!GameInfoGet(2)) {
        team = pPlayer->mUnknown4968 == GameInfoGet(0);
    } else {
        team = pPlayer->mUnknown4968 == GameInfoGet(1);
    }
    if (force || !pEntry->mUnknownFD || pEntry->mUnknown0 != pPlayer->mUnknown4956 ||
        pEntry->mUnknownF5 != team || strcmp(pEntry->mUnknownFE, pName)) {
        pEntry->mUnknown0 = pPlayer->mUnknown4956;
        pEntry->mUnknownF5 = team;
        pEntry->mUnknownF7 = 4;
        strcpy(pEntry->mUnknownFE, pName);
        pEntry->mUnknownFD = 1;
        changed = 1;
    } else {
        changed = 0;
    }
    PlayerLookLoadForPlayer(index, pPlayer->mUnknown4971, pPlayer->mUnknown4968, pPlayer->mUnknown4956);
    FEPlyrLoadQueue(index, priority, changed);
}

extern "C" void FEPlyrLoadRequestReload(int index, unsigned char priority)
{
    FEPlyrLoadRequest_t *pEntry;

    if (!_FEPlyrLoad_bActive) {
        return;
    }
    pEntry = &_FEPlyrLoad_pState->mEntries[index];
    pEntry->mUnknownF7 = 4;
    pEntry->mUnknownFD = 1;
    FEPlyrLoadQueue(index, priority, 1);
}

extern "C" void FEPlyrLoadSetPriority(int index, unsigned char priority)
{
    if (_FEPlyrLoad_bActive) {
        FEPlyrLoadQueue(index, priority, 0);
    }
}

extern "C" unsigned char FEPlyrLoadIsQueued(int index)
{
    if (_FEPlyrLoad_bActive) {
        return _FEPlyrLoad_pState->mEntries[index].mUnknownFC;
    }
    return 0;
}

extern "C" void FEPlyrLoadInvalidate(int index)
{
    if (!_FEPlyrLoad_bActive) {
        return;
    }
    _FEPlyrLoad_pState->mEntries[index].mUnknownFD = 0;
    _FEPlyrLoad_pState->mEntries[index].mUnknownF4 = 0;
}

extern "C" void FEPlyrLoadFinish(int index)
{
    FEPlyrLoadState_t *pState;
    FEPlyrLoadRequest_t *pEntry;
    int current;

    if (!_FEPlyrLoad_bActive) {
        return;
    }
    pState = _FEPlyrLoad_pState;
    current = pState->mCurrent;
    if (current != index) {
        return;
    }
    pEntry = &pState->mEntries[current];
    if (!pEntry->mUnknownF8) {
        return;
    }
    pEntry->mUnknownF9 = 1;
    PlyrTexRequestNameplate(fn_8003DEC4(current));
    _FEPlyrLoad_pState->mCurrent = 2;
    if (!pEntry->mUnknownFC && pEntry->mUnknownFD) {
        _FEPlyrLoad_pState->mUnknown251[current] = 1;
    }
}

extern "C" unsigned char FEPlyrLoadIsShown(Object_8003DEC4 *pPlayer)
{
    int slot;

    if (!_FEPlyrLoad_bActive) {
        return 1;
    }
    slot = FEPlyrLoadGetSlot(pPlayer);
    return _FEPlyrLoad_pState->mUnknown251[slot];
}

extern "C" void FEPlyrLoadGetScale(Object_8003DEC4 *pPlayer, float *pScale)
{
    float scale;
    int slot;

    if (_FEPlyrLoad_bActive) {
        slot = FEPlyrLoadGetSlot(pPlayer);
        scale = _FEPlyrLoad_pState->mUnknown244[slot];
    } else {
        scale = 1.0f;
    }
    pScale[0] = scale;
    pScale[1] = scale;
    pScale[2] = scale;
}

extern "C" unsigned char FEPlyrLoadSetScaleRamp(unsigned char value)
{
    unsigned char old = 1;

    if (_FEPlyrLoad_bActive) {
        old = _FEPlyrLoad_pState->mUnknown253;
        _FEPlyrLoad_pState->mUnknown253 = value;
    }
    return old;
}

extern "C" void FEPlyrLoadMarkDrawn(Object_8003DEC4 *pPlayer)
{
    if (_FEPlyrLoad_bActive) {
        _FEPlyrLoad_pState->mUnknown24F[FEPlyrLoadGetSlot(pPlayer)] = 1;
    }
}
