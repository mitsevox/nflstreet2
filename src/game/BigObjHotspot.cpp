/* Field hotspots: sponsor spots on the level that a team claims by making a
   play on them (tackle, broken tackle, pass, catch, juke, hurdle, dive). A
   claim shows the "Hotspot ...!" alert, swaps the hotspot's sponsor texture
   for the claiming team's logo, fires the sponsor node's particle effects,
   awards style points, and records the hotspot in the team's database bit
   mask; claiming all ten unlocks a team. Passes and catches wait in a queue
   until possession settles who made them. */
#include "game/DbTableCursorInline.h"
#include "game/StyleTracker.h"
#include "game/Object_80039F5C.h"
#include "game/BigObj.h"
#include "game/BigObjInst.h"
#include "game/BigObjNode.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"
#include "game/Record_8011F4F8.h"
#include "game/Ball.h"
#include "game/fn_80177FE0.h"
#include <string.h>
#include "engine/texture.h"
#include "engine/texfile.h"

/* Model data reached through +0 of an object's model (BigObj_t +300):
   the texture file at +324 and the texture library at +332 whose texture
   and clut slots 0 and 1 the team logos replace. */
struct BigObjModelData_t {
    char mUnknown0[324];
    void *mpUnknown324;
    char mUnknown328[4];
    unsigned char mUnknown332[1];
};

/* One hotspot play: the hotspot object, the player reference (+2 byte the
   team), the play kind and the sponsor node. */
struct HotspotPlay_t {
    BigObj_t *mpObject;
    int mRef;
    unsigned int mKind;
    BigObjNode_t *mpNode;
};

static inline unsigned char _PlayerRefTeam(int ref)
{
    return (unsigned char)(ref >> 8);
}

/* A registered hotspot and the team that owns it (2 for none). */
struct HotspotSlot_t {
    BigObj_t *mpObject;
    int mTeam;
};

/* A team logo as a texture and its palette, built from the logo texture. */
struct HotspotLogo_t {
    TexFileImage_t mImage;
    TexFilePalette_t mPalette;
};

extern "C" {
static HotspotLogo_t _Hotspot_aLogo[2];
static HotspotSlot_t _Hotspot_aSlot[5];
static HotspotPlay_t _Hotspot_aPending[15];
static int _Hotspot_iCaptureBit = 0;
static unsigned char _Hotspot_bCaptured = 0;
static int _Hotspot_iPendingNext = 0;

int fn_800AD9B4(void);
Object_80039F5C *BallGetCurrentHolder(void);
int fn_801486A0(void);
int fn_80177C38(void);
void fn_8004CBEC(void *, float, BigObjInst *, BigObj_t *);
void fn_8004E090(BigObj_t *, int, int);
void fn_8005D2C8(int);
void AudmonEventPostId(int, void *, int, int, int, int);
void TeamUnlock(int, int);
void fn_80083E1C(DbCursor *, int);
void fn_8009BD2C(Object_80039F5C *, int *);
int fn_800A3444(void);
int fn_801485D4(void);
int TutorialIsActive(void);
void TutorialSetMoveDone(int, int);
int fn_801784C4(void);
void fn_8017CA3C(int, int);
void HudShowAlert(const char *);
void MsgGameGetPlayerStatus(int, int *, int *);
int fn_80186F7C(unsigned char);
int TeamLogoGetSlot(int);
void *UIGLibraryGetGlobal(int);
unsigned char *fn_80220BFC(int, int);
void *LLUIGTexNodeGet(void *, int, int);
void TMTexLibReplaceClut(void *, TexFilePalette_t *, int, void *);
void TMTexLibReplaceTexture(void *, void *, int, TexFileImage_t *, int, int);
int fn_8022F358(int);
int fn_8022F384(int);
int fn_8022F3D4(int);
int fn_8022F4BC(void);

int HotspotClassifyPlay(HotspotPlay_t *pPlay)
{
    BigObj_t *pObject = pPlay->mpObject;
    int found = 0;
    int *pRef = &pPlay->mRef;
    int state = fn_801486A0();
    if (state == 0 || state == 2 || state == 3 || state == 1) {
        return 0;
    }
    int phase = fn_800AD9B4();
    if (phase != 3) {
        return 0;
    }
    Object_80039F5C *pPlayer = fn_8009BCE8(pRef);
    unsigned short type = fn_801BE648(pPlayer->mpUnknown792);
    if (type == 181) {
        if (pPlayer->mpState->mId == 17) {
            int *pMate = &pPlayer->mUnknown336;
            Object_80039F5C *pCarrier = BallGetCurrentHolder();
            if (pCarrier && pCarrier == fn_8009BCE8(pMate)) {
                pPlay->mKind = 1;
                found = 1;
            }
        } else {
            Object_80039F5C *pCarrier = BallGetCurrentHolder();
            pPlay->mRef = pPlayer->mUnknown336;
            if (pCarrier && pCarrier == pPlayer) {
                pPlay->mKind = 1;
                found = 1;
            }
        }
    } else if (type == 186) {
        if (pPlayer->mpState->mId == 16) {
            Object_80039F5C *pCarrier = BallGetCurrentHolder();
            if (pCarrier && pCarrier == pPlayer) {
                pPlay->mKind = 2;
                found = 1;
            }
        } else {
            int *pMate = &pPlayer->mUnknown336;
            Object_80039F5C *pCarrier = BallGetCurrentHolder();
            pPlay->mRef = *pMate;
            if (pCarrier && pCarrier == fn_8009BCE8(pMate)) {
                pPlay->mKind = 2;
                found = 1;
            }
        }
    } else if (type == 235) {
        if (fn_8011F4F8(BallGetIndex(BallGetCurrent()))->mUnknown1D != 4) {
            pPlay->mKind = phase;
            found = 1;
        }
    } else if (type == 237) {
        pPlay->mKind = 7;
        found = 1;
    } else if (type == 224 || type == 225) {
        pPlay->mKind = 4;
        found = 1;
    } else if (type == 228 || type == 229) {
        if (!fn_80177C38()) {
            if (fn_801784C4()) {
                if (1.5f - pObject->mUnknown472->mUnknown12 <= fn_80177FE0().mY) {
                    goto done;
                }
            } else {
                if (pObject->mUnknown472->mUnknown12 + 1.5f <= fn_80177FE0().mY) {
                    goto done;
                }
            }
        }
        pPlay->mKind = type == 229 ? 5 : 6;
        found = 1;
    }
done:
    return found;
}

void HotspotRecordCapture(HotspotPlay_t *pPlay)
{
    unsigned int index = fn_800A3444();
    int db = fn_80186F7C(_PlayerRefTeam(pPlay->mRef));
    if (fn_801485D4() == 0 && TutorialIsActive() == 0 && db != -1 && index <= 9) {
        int handle = fn_8022F3D4(fn_8022F358(db));
        int bit = 1 << index;
        DbTableCursor cursor;
        cursor.OpenTable(0x464E4955, 0x44494755, 0, 0, handle);
        int value = cursor.DbTableCursor::GetColumnInt(0x504C5555);
        if (!(value & bit)) {
            value |= bit;
            cursor.DbTableCursor::SetColumnInt(0x504C5555, value);
            _Hotspot_bCaptured = 1;
            _Hotspot_iCaptureBit = bit;
            if (value == 0x3FF) {
                fn_8005D2C8(1);
                TeamUnlock(fn_8022F384(fn_8022F4BC()), 34);
            }
        }
    }
}

int HotspotIsNewOwner(HotspotPlay_t *pPlay)
{
    BigObj_t *pObject = pPlay->mpObject;
    int *pRef = &pPlay->mRef;
    int i = 0;
    while (i <= 4 && _Hotspot_aSlot[i].mpObject != pObject) {
        i++;
    }
    if (_Hotspot_aSlot[i].mTeam != _PlayerRefTeam(*pRef)) {
        return 1;
    }
    return 0;
}

void HotspotLoadTeamLogos(BigObj_t *)
{
    DbCursor cursor;
    fn_80083E1C(&cursor, 0);
    for (int i = 0; i <= 1; i++) {
        int id, team;
        MsgGameGetPlayerStatus(i, &id, &team);
        unsigned char *pPalette = 0;
        fn_80084034(&cursor, i, 0);
        int value = fn_80084438(&cursor);
        Texture_t *pTexture = (Texture_t *)LLUIGTexNodeGet(UIGLibraryGetGlobal(1), 4, id);
        if (value == 0) {
            int slot;
            if (i == 0) slot = 0; else slot = 1;
            pPalette = fn_80220BFC(5, TeamLogoGetSlot(slot));
        }
        _Hotspot_aLogo[i].mImage.mWidth = pTexture->mWidth;
        _Hotspot_aLogo[i].mImage.mHeight = pTexture->mHeight;
        _Hotspot_aLogo[i].mImage.mFormat = pTexture->mFormat;
        _Hotspot_aLogo[i].mImage.mType = 0;
        _Hotspot_aLogo[i].mImage.mUnknown8 = pTexture->mWidth * pTexture->mHeight;
        _Hotspot_aLogo[i].mImage.mpUnknownC = pTexture->mpImage;
        _Hotspot_aLogo[i].mPalette.mFormat = pTexture->mFormat;
        _Hotspot_aLogo[i].mPalette.mUnknown2 = pTexture->mTlutFormat;
        _Hotspot_aLogo[i].mPalette.mUnknown4 = 512;
        if (pPalette) {
            _Hotspot_aLogo[i].mPalette.mpUnknown8 = pPalette;
        } else {
            _Hotspot_aLogo[i].mPalette.mpUnknown8 = (unsigned char *)pTexture->mpPalette;
        }
    }
    fn_80083F68(&cursor);
}

void HotspotCapture(HotspotPlay_t *pPlay)
{
    BigObj_t *pObject = pPlay->mpObject;
    int *pRef = &pPlay->mRef;
    int i = 0;
    int changed = 0;
    int count = 0;
    while (i <= 4 && _Hotspot_aSlot[i].mpObject != pObject) {
        i++;
    }
    if (_Hotspot_aSlot[i].mTeam == _PlayerRefTeam(*pRef)) {
        return;
    }
    switch (pPlay->mKind) {
    case 1: HudShowAlert("Hotspot Tackle!"); break;
    case 2: HudShowAlert("Hotspot Broken Tackle!"); break;
    case 3: HudShowAlert("Hotspot Pass!"); break;
    case 7: HudShowAlert("Hotspot Dive!"); break;
    case 4: HudShowAlert("Hotspot Catch!"); break;
    case 5: HudShowAlert("Hotspot Juke!"); break;
    case 6: HudShowAlert("Hotspot Hurdle!"); break;
    default: HudShowAlert("Hotspot Hit!"); break;
    }
    if (_Hotspot_aSlot[i].mTeam != 2) {
        changed = 1;
    }
    _Hotspot_aSlot[i].mTeam = _PlayerRefTeam(*pRef);
    for (int j = 0; j < 5; j++) {
        if (_Hotspot_aSlot[j].mTeam == _PlayerRefTeam(*pRef)) {
            count++;
        }
    }
    if (count == 1) {
        HotspotRecordCapture(pPlay);
    }
    StyleTrackerAwardHotspot(fn_8009BCE8(pRef), count, changed);
    fn_8017CA3C(*pRef, 1);
    BigObj_t *pOther = pObject->mUnknown472->mUnknown152[0];
    if (pOther) {
        pOther->mUnknown232_31 = 0;
    }
    if (_Hotspot_aLogo[0].mImage.mpUnknownC == 0) {
        HotspotLoadTeamLogos(pObject);
        TMTexLibReplaceClut(pObject->mUnknown300->mpUnknown0->mUnknown332, &_Hotspot_aLogo[0].mPalette, 0, 0);
        TMTexLibReplaceTexture(pObject->mUnknown300->mpUnknown0->mpUnknown324, pObject->mUnknown300->mpUnknown0->mUnknown332, 0, &_Hotspot_aLogo[0].mImage, 0, 0);
        TMTexLibReplaceClut(pObject->mUnknown300->mpUnknown0->mUnknown332, &_Hotspot_aLogo[1].mPalette, 1, 0);
        TMTexLibReplaceTexture(pObject->mUnknown300->mpUnknown0->mpUnknown324, pObject->mUnknown300->mpUnknown0->mUnknown332, 1, &_Hotspot_aLogo[1].mImage, 1, 1);
    }
    if (_Hotspot_aSlot[i].mTeam == 0) {
        fn_8004E090(pObject, 0, 0);
    } else {
        fn_8004E090(pObject, 0, 1);
    }
    pObject->mUnknown232_31 = 1;
    Object_80039F5C *pPlayer = fn_8009BCE8(pRef);
    if (pPlayer) {
        AudmonEventPostId(53, &pPlayer->mMotion, *pRef, 0, 0, 0);
    }
}

void HotspotQueuePlay(HotspotPlay_t *pPlay)
{
    if (_Hotspot_iPendingNext == 15) {
        _Hotspot_iPendingNext = 0;
    }
    _Hotspot_aPending[_Hotspot_iPendingNext] = *pPlay;
    _Hotspot_iPendingNext++;
}

void HotspotInitQueue(void)
{
    for (int i = 0; i <= 14; i++) {
        fn_801C1F94(&_Hotspot_aPending[i], 0, sizeof(HotspotPlay_t));
    }
    _Hotspot_iPendingNext = 0;
}

void HotspotClearQueue(void)
{
    for (int i = 0; i <= 14; i++) {
        fn_801C1F94(&_Hotspot_aPending[i], 0, sizeof(HotspotPlay_t));
    }
    _Hotspot_iPendingNext = 0;
}

int BigObjHotspotSponsorUpdate(BigObjInst *, BigObj_t *pOwner, int mode)
{
    switch (mode) {
    case 0:
        break;
    case 4:
        pOwner->mUnknown232_31 = 1;
        break;
    }
    return 1;
}

int BigObjHotspotFrameUpdate(BigObjInst *pInst, BigObj_t *pOwner, int mode)
{
    int i;
    if (mode == 0) {
        for (i = 0; i <= 4; i++) {
            if (_Hotspot_aSlot[i].mpObject == 0) {
                _Hotspot_aSlot[i].mTeam = 2;
                _Hotspot_aSlot[i].mpObject = pOwner;
                break;
            }
        }
        pOwner->mUnknown232_31 = 0;
        _Hotspot_iCaptureBit = 0;
        _Hotspot_aLogo[0].mImage.mpUnknownC = 0;
        _Hotspot_bCaptured = 0;
        _Hotspot_aLogo[1].mImage.mpUnknownC = 0;
        HotspotInitQueue();
        fn_8005D2C8(0);
    } else if (mode == 3) {
        for (i = 0; i <= 4; i++) {
            if (_Hotspot_aSlot[i].mpObject == pOwner) {
                _Hotspot_aSlot[i].mpObject = 0;
                _Hotspot_aSlot[i].mTeam = 2;
                break;
            }
        }
        _Hotspot_aLogo[0].mImage.mpUnknownC = 0;
        _Hotspot_aLogo[1].mImage.mpUnknownC = 0;
    } else if (mode == 4) {
        pOwner->mUnknown232_31 = 0;
        _Hotspot_aLogo[0].mImage.mpUnknownC = 0;
        _Hotspot_aLogo[1].mImage.mpUnknownC = 0;
    } else if (pInst->mUnknown380) {
        Vector_80039F5C position;
        position.mX = pInst->mUnknown360.mX;
        position.mY = pInst->mUnknown360.mY;
        position.mZ = pInst->mUnknown360.mZ;
        if (fn_801784C4()) {
            position.mX = -position.mX;
            position.mY = -position.mY;
        }
        BigObjNode_t *pNode = pInst->mUnknown312;
        pInst->mUnknown380 = 0;
        while (pNode) {
            if (strcmp(pNode->mName, pInst->mUnknown316) == 0 && pInst->mUnknown376 != 0) {
                HotspotPlay_t play;
                play.mpObject = pOwner;
                play.mRef = pInst->mUnknown376;
                play.mKind = 0;
                play.mpNode = pNode;
                if (HotspotClassifyPlay(&play) && HotspotIsNewOwner(&play)) {
                    if (fn_800B65A0(_PlayerRefTeam(pInst->mUnknown376)) != 255) {
                        Object_80039F5C *pPlayer = fn_8009BCE8(&pInst->mUnknown376);
                        if (fn_801BE648(pPlayer->mpUnknown792) == 228 || fn_801BE648(pPlayer->mpUnknown792) == 229) {
                            TutorialSetMoveDone(44, 1);
                        }
                    }
                    if ((unsigned int)(play.mKind - 3) > 1) {
                        fn_8004CBEC(pNode->mUnknown128, 1.0f, pOwner->mUnknown472, pOwner);
                        HotspotCapture(&play);
                    }
                }
            }
            pNode = pNode->mpNext;
        }
    }
    return 1;
}

void HotspotFrameTouch(BigObj_t *pObject, Object_80039F5C *pPlayer)
{
    int ref;
    fn_8009BD2C(pPlayer, &ref);
    BigObjNode_t *pNode = pObject->mUnknown472->mUnknown312;
    while (pNode && strcmp(pNode->mName, "Obj_Hotspot_Sponsor") != 0) {
        pNode = pNode->mpNext;
    }
    HotspotPlay_t play;
    play.mpObject = pObject;
    play.mRef = ref;
    play.mKind = 0;
    play.mpNode = pNode;
    if (HotspotClassifyPlay(&play) && HotspotIsNewOwner(&play)) {
        if (fn_800B65A0(_PlayerRefTeam(ref)) != 255) {
            if (fn_801BE648(pPlayer->mpUnknown792) == 228 || fn_801BE648(pPlayer->mpUnknown792) == 229) {
                TutorialSetMoveDone(44, 1);
            }
        }
        fn_8004CBEC(pNode->mUnknown128, 1.0f, pObject->mUnknown472, pObject);
        if ((unsigned int)(play.mKind - 3) <= 1) {
            HotspotQueuePlay(&play);
        } else {
            HotspotCapture(&play);
        }
    }
}

int HotspotPollCaptured(void)
{
    if (_Hotspot_bCaptured != 0) {
        _Hotspot_bCaptured = 0;
        return 1;
    }
    return 0;
}

void HotspotReset(void)
{
    for (int i = 4; i >= 0; i--) {
        _Hotspot_aSlot[i].mTeam = 2;
    }
    _Hotspot_bCaptured = 0;
    _Hotspot_iCaptureBit = 0;
    HotspotClearQueue();
}

void HotspotResolvePending(Object_80039F5C *pPlayer)
{
    for (int i = 0; i < 15; i++) {
        if (_Hotspot_aPending[i].mpObject) {
            if (_Hotspot_aPending[i].mKind == 3) {
                if (_PlayerRefTeam(_Hotspot_aPending[i].mRef) == pPlayer->mIdBytes[2]) {
                    HotspotCapture(&_Hotspot_aPending[i]);
                }
                fn_801C1F94(&_Hotspot_aPending[i], 0, sizeof(HotspotPlay_t));
            }
            if (_Hotspot_aPending[i].mKind == 4 && fn_8009BCE8(&_Hotspot_aPending[i].mRef) == pPlayer) {
                HotspotCapture(&_Hotspot_aPending[i]);
                fn_801C1F94(&_Hotspot_aPending[i], 0, sizeof(HotspotPlay_t));
            }
        }
    }
}

void HotspotFramePlayEffect(BigObj_t *pObject, int index, int apply)
{
    BigObjNode_t *pNode = pObject->mUnknown472->mUnknown312;
    while (pNode && strcmp(pNode->mName, "Obj_Hotspot_Sponsor") != 0) {
        pNode = pNode->mpNext;
    }
    if (apply) {
        fn_8004CBEC(pNode->mUnknown128, 1.0f, pObject->mUnknown472, pObject);
    }
}
}
