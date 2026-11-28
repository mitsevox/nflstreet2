/* Player models: opens the pla*.dat model archives (plamodel, plaface, plahair, plarosterhair,
   plahat, plaglass, plajewel), loads the body, hand and base head models, each player's hair,
   face, hat, glasses and jewellery models (directly, queued and read once per id, or
   asynchronously with a completion callback), binds them to their skeletons and looks up the
   face and hair models of real players by name. */
#include "game/Object_8003DEC4.h"
#include "game/DbCursor.h"
#include "game/Object_80233EAC.h"
#include "game/PlaModel.h"
#include "game/PlayerLook.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

#include <string.h>

/* Pending model load sorted by id by PlaModelQueuePart. */
struct PlaModelQueueEntry_t {
    unsigned int mId;
    void *mpData;
};

#define ROSTER_ID_BASE 50000U
#define NO_MODEL 0xFFFF

extern "C" {
void HairListOpen(DbCursor *pObject);
void HairListClose(DbCursor *pObject);
void HairListFind(DbCursor *pObject, int id, int *pResult);
int HairListGetModel(DbCursor *pObject);
void PlyrModelLodClear(ModelLod_802DF190 *pLod);
void PlyrModelLodInit(ModelLod_802DF190 *pLod, ModelLod_802DF190 *pSource, AnimSkeleton_t *pSkeleton);
void PlyrModelLodBindSkeleton(ModelLod_802DF190 *pLod, AnimSkeleton_t *pSkeleton);
void PlyrRenderBindPartTable(int a);
void PlyrRenderUnbindPartTable(void);
int snprintf(char *pBuffer, int size, const char *pFormat, ...);
int FileSetMemAllocFlags(int value);
void GlibSyncFrame(void);
int MemGetSizeByAddr(int a, void *p);
void ResCopyAsyncToBuffer(void *pArchive, int id, int a, void *pDest, int b, void (*pCallback)(void), int c);
int ResCopyToBuffer(void *pArchive, int id, void *pDest);
int ResFindIndexByName(void *pArchive, char *pName);
int ResGetSize(void *pArchive, int id);
int ResSync(int a);
int ResSetMemFlags(int value);

extern char lbl_802EC028[];
extern char lbl_802EC038[];
extern char lbl_802EC044[];
extern char lbl_802EC050[];
extern char lbl_802EC064[];
extern char lbl_802EC070[];
extern char lbl_802EC08C[];

void PlaModelPostInit(void);
void PlaModelLoadHair(int index, int load);
void PlaModelLoadHat(int index, int load);
void PlaModelLoadGlasses(int index, int load);
void PlaModelLoadJewel(int index, int load);
void PlaModelFaceReadDone(void);
void PlaModelHairReadDone(void);
void PlaModelHatReadDone(void);
void PlaModelGlassesReadDone(void);
void PlaModelJewelReadDone(void);
void PlaModelClearHair(int index);
void PlaModelClearHat(int index);
void PlaModelClearGlasses(int index);
void PlaModelFinishAsyncLoads(void);
}

#define LOD(scale, a, b, id) { scale, a, b, id, 0, { 0 } }
#define LOD_END { 0.0f, 0, 0, NO_MODEL, 0, { 0 } }
#define PLAYER_LODS(id) { LOD(0.3f, 600, 63000, id), LOD(0.0725f, 300, 32000, id + 1), LOD_END }
#define PLAYER_LODS_14(id)                                                                  \
    {                                                                                       \
        PLAYER_LODS(id), PLAYER_LODS(id), PLAYER_LODS(id), PLAYER_LODS(id), PLAYER_LODS(id), \
        PLAYER_LODS(id), PLAYER_LODS(id), PLAYER_LODS(id), PLAYER_LODS(id), PLAYER_LODS(id), \
        PLAYER_LODS(id), PLAYER_LODS(id), PLAYER_LODS(id), PLAYER_LODS(id)                  \
    }
#define PLAYER_TABLE(set)                                                                   \
    {                                                                                       \
        _PlaModel_aPlayerPartLods[set][0], _PlaModel_aPlayerPartLods[set][1], _PlaModel_aPlayerPartLods[set][2],                   \
        _PlaModel_aPlayerPartLods[set][3], _PlaModel_aPlayerPartLods[set][4], _PlaModel_aPlayerPartLods[set][5],                   \
        _PlaModel_aPlayerPartLods[set][6], _PlaModel_aPlayerPartLods[set][7], _PlaModel_aPlayerPartLods[set][8],                   \
        _PlaModel_aPlayerPartLods[set][9], _PlaModel_aPlayerPartLods[set][10], _PlaModel_aPlayerPartLods[set][11],                 \
        _PlaModel_aPlayerPartLods[set][12], _PlaModel_aPlayerPartLods[set][13]                                        \
    }

static const char *_PlaModel_apszBodyTypes[4] = { "Heavy", "Muscular", "Thin", "Athletic" };

static ModelLod_802DF190 _PlaModel_aBodyLods[4][3] = {
    { LOD(0.3f, 2700, 63000, 1), LOD(0.0725f, 1500, 32000, 2), LOD_END },
    { LOD(0.3f, 2700, 63000, 3), LOD(0.0725f, 1500, 32000, 4), LOD_END },
    { LOD(0.3f, 2700, 63000, 5), LOD(0.0725f, 1500, 32000, 6), LOD_END },
    { LOD(0.3f, 2700, 63000, 7), LOD(0.0725f, 1500, 32000, 8), LOD_END },
};

static ModelLod_802DF190 _PlaModel_aHandLods[4][2][2] = {
    { { LOD(2.0f, 228, 8000, 13), LOD_END }, { LOD(2.0f, 228, 8000, 14), LOD_END } },
    { { LOD(2.0f, 228, 8000, 15), LOD_END }, { LOD(2.0f, 228, 8000, 16), LOD_END } },
    { { LOD(2.0f, 228, 8000, 17), LOD_END }, { LOD(2.0f, 228, 8000, 18), LOD_END } },
    { { LOD(2.0f, 228, 8000, 19), LOD_END }, { LOD(2.0f, 228, 8000, 20), LOD_END } },
};

static ModelLod_802DF190 _PlaModel_aFaceLods[3] = {
    LOD(0.3f, 770, 63000, NO_MODEL), LOD(0.0725f, 400, 32000, NO_MODEL), LOD_END,
};

static ModelLod_802DF190 _PlaModel_aBaseHeadLods[3] = {
    LOD(0.3f, 770, 63000, 9), LOD(0.0725f, 400, 32000, 10), LOD_END,
};

static ModelLod_802DF190 _PlaModel_aMorphHeadLods[3] = {
    LOD(0.3f, 770, 63000, 11), LOD(0.0725f, 400, 32000, 12), LOD_END,
};

static ModelLod_802DF190 _PlaModel_aPlayerPartLods[4][14][3] = {
    PLAYER_LODS_14(1), PLAYER_LODS_14(1), PLAYER_LODS_14(1), PLAYER_LODS_14(0x151),
};

static ModelLod_802DF190 *_PlaModel_apBodyLods[4] = {
    _PlaModel_aBodyLods[0], _PlaModel_aBodyLods[1], _PlaModel_aBodyLods[2], _PlaModel_aBodyLods[3],
};

static ModelLod_802DF190 *_PlaModel_apHandLods[4][2] = {
    { _PlaModel_aHandLods[0][0], _PlaModel_aHandLods[0][1] },
    { _PlaModel_aHandLods[1][0], _PlaModel_aHandLods[1][1] },
    { _PlaModel_aHandLods[2][0], _PlaModel_aHandLods[2][1] },
    { _PlaModel_aHandLods[3][0], _PlaModel_aHandLods[3][1] },
};

static ModelLod_802DF190 *_PlaModel_apHairLods[14] = PLAYER_TABLE(0);
static ModelLod_802DF190 *_PlaModel_apHatLods[14] = PLAYER_TABLE(1);
static ModelLod_802DF190 *_PlaModel_apGlassesLods[14] = PLAYER_TABLE(2);
static ModelLod_802DF190 *_PlaModel_apJewelLods[14] = PLAYER_TABLE(3);

static unsigned char _PlaModel_uFaceLoadsPending = 0;
static unsigned char _PlaModel_uHairLoadsPending = 0;
static unsigned char _PlaModel_uHatLoadsPending = 0;
static unsigned char _PlaModel_uGlassesLoadsPending = 0;
static unsigned char _PlaModel_uJewelLoadsPending = 0;
static ModelLod_802DF190 *_PlaModel_pFaceLods = _PlaModel_aFaceLods;
static ModelLod_802DF190 *_PlaModel_pBaseHeadLods = _PlaModel_aBaseHeadLods;
static ModelLod_802DF190 *_PlaModel_pMorphHeadLods = _PlaModel_aMorphHeadLods;
static unsigned char _PlaModel_bCacheFace = 0;
static AnimSkeleton_t *_PlaModel_pBodySkeleton = 0;
static AnimSkeleton_t *_PlaModel_apHandSkeletons[2] = { 0 };
static AnimSkeleton_t *_PlaModel_pHairSkeleton = 0;
static AnimSkeleton_t *_PlaModel_pJewelSkeleton = 0;
static unsigned char _PlaModel_bPlayerBuffersAllocated = 0;
static unsigned char _PlaModel_bSyncLoads = 1;
static int _PlaModel_iLodMode = 0;

static PlaModelQueueEntry_t *_PlaModel_apLoadQueues[4];
static int _PlaModel_aiLoadQueueCounts[4];
static void *_PlaModel_apLoadQueueArchives[4];
static unsigned int _PlaModel_auLoadQueuedPlayers[4];
static Object_80233EAC _PlaModel_aBodies[4];
static Object_80233EAC _PlaModel_aHands[4][2];
static Object_80233EAC _PlaModel_Face;
static Object_80233EAC _PlaModel_BaseHead;
static Object_80233EAC _PlaModel_MorphHead;
static Object_80233EAC _PlaModel_aHair[14];
static Object_80233EAC _PlaModel_aHats[14];
static Object_80233EAC _PlaModel_aGlasses[14];
static Object_80233EAC _PlaModel_aJewels[14];
static void *_PlaModel_apBodyData[4][2];
static void *_PlaModel_apHandData[4][2][1];
static void *_PlaModel_apHairData[14][2];
static void *_PlaModel_apHatData[14][2];
static void *_PlaModel_apGlassesData[14][2];
static void *_PlaModel_apJewelData[14][2];

static PlaModelLoadCallback_t _PlaModel_apFaceCallback[1];
static Object_8003DEC4 *_PlaModel_apFacePlayer[1];
static int _PlaModel_aiHairPlayerIndex[1];
static PlaModelLoadCallback_t _PlaModel_apHairCallback[1];
static Object_8003DEC4 *_PlaModel_apHairPlayer[1];
static int _PlaModel_aiHatPlayerIndex[1];
static PlaModelLoadCallback_t _PlaModel_apHatCallback[1];
static Object_8003DEC4 *_PlaModel_apHatPlayer[1];
static int _PlaModel_aiGlassesPlayerIndex[1];
static PlaModelLoadCallback_t _PlaModel_apGlassesCallback[1];
static Object_8003DEC4 *_PlaModel_apGlassesPlayer[1];
static int _PlaModel_aiJewelPlayerIndex[1];
static PlaModelLoadCallback_t _PlaModel_apJewelCallback[1];
static Object_8003DEC4 *_PlaModel_apJewelPlayer[1];
static void *_PlaModel_apBaseHeadData[2];
static char *_PlaModel_apFaceData[2];
static void *_PlaModel_apMorphHeadData[2];
static char *_PlaModel_apFaceCache[2];
static int _PlaModel_aiFaceCacheIds[2];
static void *_PlaModel_pModelArchive;
static void *_PlaModel_pHairArchive;
static void *_PlaModel_pRosterHairArchive;
static void *_PlaModel_pFaceArchive;
static void *_PlaModel_pHatArchive;
static void *_PlaModel_pGlassesArchive;
static void *_PlaModel_pJewelArchive;

static inline void *HairArchive(unsigned int id)
{
    return id > ROSTER_ID_BASE ? _PlaModel_pRosterHairArchive : _PlaModel_pHairArchive;
}

static inline unsigned int HairId(unsigned int id)
{
    return id > ROSTER_ID_BASE ? id - ROSTER_ID_BASE : id;
}

extern "C" {

void PlaModelLoadBodies(int load)
{
    unsigned int i;
    unsigned int j;
    unsigned int count;
    ModelLod_802DF190 **tbl;

    // FAKEMATCH: both switch arms set the same table pointer and count; the
    // per-arm assignments keep the target's dead LOD-mode compares and blt 2.
    switch (_PlaModel_iLodMode) {
    case 0:
    case 1:
        tbl = _PlaModel_apBodyLods;
        count = 2;
        break;
    default:
        tbl = _PlaModel_apBodyLods;
        count = 2;
        break;
    }

    for (i = 0; i <= 3; i++) {
        if (load) {
            for (j = 0; j < count; j++) {
                _PlaModel_apBodyData[i][j] =
                    fn_801D2B7C(ResGetSize(_PlaModel_pModelArchive, tbl[i][j].mId), 4, 0);
            }
        }
        fn_80233EAC(&_PlaModel_aBodies[i], tbl[i], "PLYRBODY", 0, _PlaModel_pModelArchive, 0,
                    _PlaModel_apBodyData[i], 1);
    }
}

void PlaModelFreeBodies(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
            if (_PlaModel_apBodyData[i][j]) {
                fn_801D2BD0(_PlaModel_apBodyData[i][j]);
                _PlaModel_apBodyData[i][j] = 0;
            }
        }
    }
}

void PlaModelLoadHands(int load)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;
    unsigned int count;
    ModelLod_802DF190 *(*tbl)[2];

    // FAKEMATCH: both switch arms set the same table pointer; the per-arm
    // assignment puts the table's lis in each arm as the target does.
    switch (_PlaModel_iLodMode) {
    case 0:
    case 1:
        tbl = _PlaModel_apHandLods;
        count = 1;
        break;
    default:
        tbl = _PlaModel_apHandLods;
        count = 2;
        break;
    }

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
            if (load) {
                for (k = 0; k < count; k++) {
                    _PlaModel_apHandData[i][j][k] =
                        fn_801D2B7C(ResGetSize(_PlaModel_pModelArchive, tbl[i][j][k].mId), 4, 0);
                }
            }
            fn_80233EAC(&_PlaModel_aHands[i][j], tbl[i][j], "PLYRHAND", 0, _PlaModel_pModelArchive, 0,
                        _PlaModel_apHandData[i][j], 1);
        }
    }
}

void PlaModelFreeHands(void)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
            for (k = 0; k < 1; k++) {
                if (_PlaModel_apHandData[i][j][k]) {
                    fn_801D2BD0(_PlaModel_apHandData[i][j][k]);
                    _PlaModel_apHandData[i][j][k] = 0;
                }
            }
        }
    }
}

void PlaModelLoadBaseHead(int load)
{
    unsigned int i;

    if (load) {
        for (i = 0; i < 2; i++) {
            if (_PlaModel_pBaseHeadLods[i].mId != NO_MODEL) {
                _PlaModel_apBaseHeadData[i] =
                    fn_801D2B7C(ResGetSize(_PlaModel_pModelArchive, _PlaModel_pBaseHeadLods[i].mId), 4, 0);
            }
        }
    }
    fn_80233EAC(&_PlaModel_BaseHead, _PlaModel_pBaseHeadLods, "BASEHEAD", 0, _PlaModel_pModelArchive, 0, _PlaModel_apBaseHeadData, 1);
}

void PlaModelFreeBaseHead(void)
{
    unsigned int i;

    for (i = 0; i < 1; i++) {
        if (_PlaModel_apHandData[i]) {
            fn_801D2BD0(_PlaModel_apBaseHeadData[i]);
            _PlaModel_apBaseHeadData[i] = 0;
        }
    }
}

void PlaModelAllocPlayerBuffers(unsigned int players)
{
    unsigned int i;
    unsigned int k;
    unsigned int count;

    switch (_PlaModel_iLodMode) {
    case 0:
        count = 1;
        break;
    case 1:
        count = 2;
        break;
    default:
        count = 2;
        break;
    }

    int sizesA[2] = { 0x3EC6, 0x3408 };
    int sizesB[2] = { 0x3D04, 0x34E4 };
    int sizesC[2] = { 0x2A85, 0x29A4 };
    int sizesD[2] = { 0x4FE7, 0x64 };

    for (i = 0; i < players; i++) {
        for (k = 0; k < count; k++) {
            _PlaModel_apHairData[i][k] = fn_801D2B7C(sizesA[k], 4, 0);
            _PlaModel_apHatData[i][k] = fn_801D2B7C(sizesB[k], 4, 0);
            _PlaModel_apGlassesData[i][k] = fn_801D2B7C(sizesC[k], 4, 0);
            _PlaModel_apJewelData[i][k] = fn_801D2B7C(sizesD[k], 4, 0);
        }
    }
    for (k = 0; k < count; k++) {
    }
}

void PlaModelFreePlayerBuffers(void)
{
    unsigned int i;
    unsigned int k;

    for (i = 0; i <= 13; i++) {
        for (k = 0; k <= 1; k++) {
            if (_PlaModel_apHairData[i][k]) {
                fn_801D2BD0(_PlaModel_apHairData[i][k]);
                _PlaModel_apHairData[i][k] = 0;
            }
            if (_PlaModel_apHatData[i][k]) {
                fn_801D2BD0(_PlaModel_apHatData[i][k]);
                _PlaModel_apHatData[i][k] = 0;
            }
            if (_PlaModel_apGlassesData[i][k]) {
                fn_801D2BD0(_PlaModel_apGlassesData[i][k]);
                _PlaModel_apGlassesData[i][k] = 0;
            }
            if (_PlaModel_apJewelData[i][k]) {
                fn_801D2BD0(_PlaModel_apJewelData[i][k]);
                _PlaModel_apJewelData[i][k] = 0;
            }
        }
    }
    for (k = 0; k <= 1; k++) {
    }
}

void PlaModelPostInit(void)
{
}

void PlaModelLoadHair(int index, int load)
{
    ModelLod_802DF190 *pLods;
    unsigned int count;
    unsigned int k;
    unsigned int id0;
    unsigned int id1;

    pLods = _PlaModel_apHairLods[index];
    id0 = pLods[0].mId;
    id1 = pLods[1].mId;
    switch (_PlaModel_iLodMode) {
    case 0:
        pLods[1].mId = NO_MODEL;
        count = 1;
        id1 = NO_MODEL;
        break;
    case 1:
        count = 2;
        break;
    default:
        count = 2;
        break;
    }

    if (load) {
        if (_PlaModel_bSyncLoads) {
            GlibSyncFrame();
        }
        ResCopyToBuffer(HairArchive(id0), HairId(_PlaModel_apHairLods[index][0].mId), _PlaModel_apHairData[index][0]);
        ResCopyToBuffer(HairArchive(id1), HairId(_PlaModel_apHairLods[index][1].mId), _PlaModel_apHairData[index][1]);
        fn_80233EAC(&_PlaModel_aHair[index], _PlaModel_apHairLods[index], "PLYRMODEL", 0, HairArchive(id0),
                    _PlaModel_pHairSkeleton, _PlaModel_apHairData[index], 0);
        if (_PlaModel_bSyncLoads) {
            ResSync(0);
        }
    } else {
        fn_80233EAC(&_PlaModel_aHair[index], _PlaModel_apHairLods[index], "PLYRMODEL", 0, HairArchive(id0),
                    _PlaModel_pHairSkeleton, _PlaModel_apHairData[index], 0);
    }

    _PlaModel_apHairLods[index][0].mId = id0 > ROSTER_ID_BASE ? id0 - ROSTER_ID_BASE : id0;
    _PlaModel_apHairLods[index][1].mId = id1 > ROSTER_ID_BASE ? id1 - ROSTER_ID_BASE : id1;
    for (k = 0; k < count; k++) {
        PlyrModelLodBindSkeleton(&_PlaModel_apHairLods[index][k], _PlaModel_pHairSkeleton);
    }
    _PlaModel_apHairLods[index][0].mId = id0;
    _PlaModel_apHairLods[index][1].mId = id1;
}

void PlaModelLoadHat(int index, int load)
{
    ModelLod_802DF190 *pLods = _PlaModel_apHatLods[index];

    if (_PlaModel_iLodMode == 0) {
        pLods[1].mId = NO_MODEL;
    }

    if (load) {
        if (_PlaModel_bSyncLoads) {
            GlibSyncFrame();
        }
        fn_80233EAC(&_PlaModel_aHats[index], _PlaModel_apHatLods[index], "PLYRMODEL", 0, _PlaModel_pHatArchive,
                    _PlaModel_pBodySkeleton, _PlaModel_apHatData[index], 1);
        if (_PlaModel_bSyncLoads) {
            ResSync(0);
        }
    } else {
        fn_80233EAC(&_PlaModel_aHats[index], _PlaModel_apHatLods[index], "PLYRMODEL", 0, _PlaModel_pHatArchive,
                    _PlaModel_pBodySkeleton, _PlaModel_apHatData[index], 0);
    }
}

void PlaModelLoadGlasses(int index, int load)
{
    ModelLod_802DF190 *pLods = _PlaModel_apGlassesLods[index];

    if (_PlaModel_iLodMode == 0) {
        pLods[1].mId = NO_MODEL;
    }

    if (load) {
        if (_PlaModel_bSyncLoads) {
            GlibSyncFrame();
        }
        fn_80233EAC(&_PlaModel_aGlasses[index], _PlaModel_apGlassesLods[index], "PLYRMODEL", 0, _PlaModel_pGlassesArchive,
                    _PlaModel_pBodySkeleton, _PlaModel_apGlassesData[index], 1);
        if (_PlaModel_bSyncLoads) {
            ResSync(0);
        }
    } else {
        fn_80233EAC(&_PlaModel_aGlasses[index], _PlaModel_apGlassesLods[index], "PLYRMODEL", 0, _PlaModel_pGlassesArchive,
                    _PlaModel_pBodySkeleton, _PlaModel_apGlassesData[index], 0);
    }
}

void PlaModelLoadJewel(int index, int load)
{
    ModelLod_802DF190 *pLods = _PlaModel_apJewelLods[index];
    unsigned int count;
    unsigned int k;

    switch (_PlaModel_iLodMode) {
    case 0:
        pLods[1].mId = NO_MODEL;
        count = 1;
        break;
    case 1:
        pLods[1].mId = NO_MODEL;
        count = 2;
        break;
    default:
        count = 2;
        break;
    }

    if (load) {
        if (_PlaModel_bSyncLoads) {
            GlibSyncFrame();
        }
        fn_80233EAC(&_PlaModel_aJewels[index], _PlaModel_apJewelLods[index], "PLYRMODEL", 0, _PlaModel_pJewelArchive,
                    _PlaModel_pJewelSkeleton, _PlaModel_apJewelData[index], 1);
        if (_PlaModel_bSyncLoads) {
            ResSync(0);
        }
    } else {
        fn_80233EAC(&_PlaModel_aJewels[index], _PlaModel_apJewelLods[index], "PLYRMODEL", 0, _PlaModel_pJewelArchive,
                    _PlaModel_pJewelSkeleton, _PlaModel_apJewelData[index], 0);
    }

    for (k = 0; k < count; k++) {
        PlyrModelLodBindSkeleton(&_PlaModel_apJewelLods[index][k], _PlaModel_pJewelSkeleton);
    }
}

static inline void CopyEntry(PlaModelQueueEntry_t *pDest, PlaModelQueueEntry_t *pSource)
{
    unsigned int id = pSource->mId;
    void *pData = pSource->mpData;

    pDest->mId = id;
    pDest->mpData = pData;
}

/* Queues the models of one player part for fn_8015EF10, keeping each
   queue sorted by id so that equal models are read only once. */
void PlaModelQueuePart(int type, int index, ModelLod_802DF190 *pLods, void **ppData)
{
    int count;
    int i;
    int j;
    PlaModelQueueEntry_t *pQueue;
    int queued;

    switch (_PlaModel_iLodMode) {
    case 0:
        count = 1;
        break;
    case 1:
        count = 2;
        break;
    default:
        count = 2;
        break;
    }
    if (type == 3) {
        count = 1;
    }

    pQueue = _PlaModel_apLoadQueues[type];
    queued = _PlaModel_aiLoadQueueCounts[type];
    for (i = 0; i < count; i++) {
        PlaModelQueueEntry_t entry;

        entry.mId = pLods[i].mId;
        if (entry.mId == NO_MODEL) {
            goto done;
        }
        if (entry.mId != 0) {
            entry.mpData = ppData[i];
            if (entry.mpData != 0) {
                j++;
            }
            j = queued - 1;
            queued++;
            goto test;
        next:
            j--;
        test:
            if (j >= 0 && pQueue[j].mId > entry.mId) {
                CopyEntry(&pQueue[j + 1], &pQueue[j]);
                goto next;
            }
            PlaModelQueueEntry_t *pEntry = &entry;
            unsigned int id = pEntry->mId;
            void *pData = pEntry->mpData;
            pQueue[j + 1].mId = id;
            pQueue[j + 1].mpData = pData;
        }
    }
done:
    _PlaModel_aiLoadQueueCounts[type] = queued;
    _PlaModel_auLoadQueuedPlayers[type] |= 1 << index;
}

void PlaModelFaceReadDone(void)
{
    _PlaModel_uFaceLoadsPending--;
}

void PlaModelHairReadDone(void)
{
    _PlaModel_uHairLoadsPending--;
}

void PlaModelHatReadDone(void)
{
    _PlaModel_uHatLoadsPending--;
}

void PlaModelGlassesReadDone(void)
{
    _PlaModel_uGlassesLoadsPending--;
}

void PlaModelJewelReadDone(void)
{
    _PlaModel_uJewelLoadsPending--;
}

void PlaModelLoadMorphHead(int load, int flag)
{
    int size0;
    int size1;
    int value;

    if (load) {
        value = 0;
        size0 = ResGetSize(_PlaModel_pModelArchive, _PlaModel_pMorphHeadLods[0].mId);
        size1 = ResGetSize(_PlaModel_pModelArchive, _PlaModel_pMorphHeadLods[1].mId);
        if (flag) {
            value = 4;
        }
        _PlaModel_apMorphHeadData[0] = fn_801D2B7C(size0, value, 0);
        _PlaModel_apMorphHeadData[1] = fn_801D2B7C(size1, value, 0);
    }
    fn_80233EAC(&_PlaModel_MorphHead, _PlaModel_pMorphHeadLods, "PLYRMODEL", 0, _PlaModel_pModelArchive, 0, _PlaModel_apMorphHeadData, 1);
}

Object_8023417C *fn_8015E2FC(int type, int index, int a)
{
    switch (type) {
    case 0:
        return fn_8023417C(&_PlaModel_aBodies[index], a);
    case 1:
        return fn_8023417C(&_PlaModel_aHands[index][0], a);
    case 2:
        return fn_8023417C(&_PlaModel_aHands[index][1], a);
    case 3:
        return fn_8023417C(&_PlaModel_aHair[index], a);
    case 4:
        return fn_8023417C(&_PlaModel_Face, a);
    case 5:
        return fn_8023417C(&_PlaModel_BaseHead, a);
    case 6:
        return fn_8023417C(&_PlaModel_MorphHead, a);
    case 7:
        return fn_8023417C(&_PlaModel_aHats[index], a);
    case 8:
        return fn_8023417C(&_PlaModel_aGlasses[index], a);
    case 9:
        return fn_8023417C(&_PlaModel_aJewels[index], a);
    }
    return 0;
}

Object_80233EAC *fn_8015E440(int type, int index)
{
    Object_80233EAC *pObject;

    switch (type) {
    case 0:
        pObject = &_PlaModel_aBodies[index];
        break;
    case 1:
        pObject = &_PlaModel_aHands[type][0];
        break;
    case 2:
        pObject = &_PlaModel_aHands[type][1];
        break;
    case 3:
        pObject = &_PlaModel_aHair[index];
        break;
    case 4:
        pObject = &_PlaModel_Face;
        break;
    case 5:
        pObject = &_PlaModel_BaseHead;
        break;
    case 7:
        pObject = &_PlaModel_aHats[index];
        break;
    case 8:
        pObject = &_PlaModel_aGlasses[index];
        break;
    case 9:
        pObject = &_PlaModel_aJewels[index];
        break;
    default:
        pObject = 0;
        break;
    }
    return pObject;
}

void PlaModelOpenArchives(void)
{
    int a = ResSetMemFlags(4);
    int b = FileSetMemAllocFlags(4);

    _PlaModel_pModelArchive = ResOpenDevice(lbl_802EC028, 0x2C);
    _PlaModel_pHairArchive = ResOpenDevice(lbl_802EC044, 0x2C);
    _PlaModel_pRosterHairArchive = ResOpenDevice(lbl_802EC050, 0x2C);
    _PlaModel_pFaceArchive = ResOpenDevice(lbl_802EC038, 0x2C);
    _PlaModel_pHatArchive = ResOpenDevice(lbl_802EC064, 0x2C);
    _PlaModel_pGlassesArchive = ResOpenDevice(lbl_802EC070, 0x2C);
    _PlaModel_pJewelArchive = ResOpenDevice(lbl_802EC08C, 0x2C);
    ResSetMemFlags(a);
    FileSetMemAllocFlags(b);
}

void PlaModelInit(unsigned int players, int mode)
{
    _PlaModel_iLodMode = mode;
    PlaModelAllocPlayerBuffers(players);
    _PlaModel_bPlayerBuffersAllocated = 1;
    _PlaModel_bSyncLoads = 1;
    PlaModelPostInit();
}

void PlaModelSetLodMode(int mode)
{
    _PlaModel_iLodMode = mode;
}

void PlaModelShutdown(void)
{
    PlaModelFreePlayerBuffers();
    _PlaModel_bPlayerBuffersAllocated = 0;
}

void PlaModelLoadSharedModels(void)
{
    PlyrRenderBindPartTable(0);
    PlaModelLoadBodies(1);
    PlaModelLoadHands(1);
    PlaModelLoadBaseHead(1);
    PlyrRenderUnbindPartTable();
}

void PlaModelInitPlayerModels(void)
{
}

void PlaModelResetPlayerModels(void)
{
    unsigned int i;

    for (i = 0; i <= 13; i++) {
        PlaModelClearHair(i);
        PlaModelClearHat(i);
        PlaModelClearGlasses(i);
    }
}

void PlaModelFreeSharedModels(void)
{
    PlaModelFreeBodies();
    PlaModelFreeHands();
    PlaModelFreeBaseHead();
}

void fn_8015E73C(int id)
{
    int size0;
    int size1;

    if (_PlaModel_uFaceLoadsPending) {
        ResSync(0);
        PlaModelFinishAsyncLoads();
    }
    _PlaModel_pFaceLods[0].mId = id;
    _PlaModel_pFaceLods[1].mId = id + 1;
    size0 = ResGetSize(_PlaModel_pFaceArchive, id);
    size1 = ResGetSize(_PlaModel_pFaceArchive, _PlaModel_pFaceLods[1].mId);
    if (_PlaModel_bCacheFace && _PlaModel_aiFaceCacheIds[0] == 0 && _PlaModel_aiFaceCacheIds[1] == 0) {
        _PlaModel_apFaceCache[0] = (char *)fn_801D2B7C(size0, 4, 0);
        _PlaModel_apFaceCache[1] = (char *)fn_801D2B7C(size1, 4, 0);
        _PlaModel_aiFaceCacheIds[0] = _PlaModel_pFaceLods[0].mId;
        _PlaModel_aiFaceCacheIds[1] = _PlaModel_pFaceLods[1].mId;
        ResCopyToBuffer(_PlaModel_pFaceArchive, _PlaModel_aiFaceCacheIds[0], _PlaModel_apFaceCache[0]);
        ResCopyToBuffer(_PlaModel_pFaceArchive, _PlaModel_aiFaceCacheIds[1], _PlaModel_apFaceCache[1]);
    }
    _PlaModel_apFaceData[0] = (char *)fn_801D2B7C(size0, 4, 0);
    _PlaModel_apFaceData[1] = (char *)fn_801D2B7C(size1, 4, 0);
    if (_PlaModel_bCacheFace) {
        memcpy(_PlaModel_apFaceData[0], _PlaModel_apFaceCache[0], size0);
        memcpy(_PlaModel_apFaceData[1], _PlaModel_apFaceCache[1], size1);
        fn_80233EAC(&_PlaModel_Face, _PlaModel_pFaceLods, "PLYRMODEL", 0, _PlaModel_pFaceArchive, _PlaModel_pBodySkeleton,
                    (void **)_PlaModel_apFaceData, 0);
    } else {
        fn_80233EAC(&_PlaModel_Face, _PlaModel_pFaceLods, "PLYRMODEL", 0, _PlaModel_pFaceArchive, _PlaModel_pBodySkeleton,
                    (void **)_PlaModel_apFaceData, 1);
    }
    if (_PlaModel_bSyncLoads) {
        ResSync(0);
    }
}

void fn_8015E908(int a)
{
    fn_801D2BD0(_PlaModel_apFaceData[0]);
    fn_801D2BD0(_PlaModel_apFaceData[1]);
    _PlaModel_apFaceData[0] = 0;
    _PlaModel_apFaceData[1] = 0;
}

void PlaModelInitMorphHead(int load, int flag)
{
    PlyrRenderBindPartTable(0);
    PlaModelLoadMorphHead(load, flag);
    PlyrRenderUnbindPartTable();
}

void PlaModelFreeMorphHead(void)
{
    if (_PlaModel_apMorphHeadData[0]) {
        fn_801D2BD0(_PlaModel_apMorphHeadData[0]);
        fn_801D2BD0(_PlaModel_apMorphHeadData[1]);
        _PlaModel_apMorphHeadData[0] = 0;
        _PlaModel_apMorphHeadData[1] = 0;
        _PlaModel_aMorphHeadLods[0].mpUnknown10 = 0;
        _PlaModel_aMorphHeadLods[1].mpUnknown10 = 0;
    }
}

void fn_8015E9F4(int index, PlayerHeadIds_t *pIds)
{
    ModelLod_802DF190 *pLods;

    if (_PlaModel_uHairLoadsPending) {
        ResSync(0);
        PlaModelFinishAsyncLoads();
    }
    if (_PlaModel_auLoadQueuedPlayers[0] & (1 << index)) {
        PlaModelLoadHair(index, 0);
    } else if (pIds->mUnknown0 != NO_MODEL) {
        pLods = _PlaModel_apHairLods[index];
        if (pIds->mUnknown0 != pLods[0].mId || !pLods[0].mpUnknown10 ||
            pIds->mUnknown4 != pLods[1].mId || !pLods[1].mpUnknown10) {
            _PlaModel_apHairLods[index][0].mId = pIds->mUnknown0;
            _PlaModel_apHairLods[index][1].mId = pIds->mUnknown4;
            PlaModelLoadHair(index, 1);
        }
    }
    _PlaModel_auLoadQueuedPlayers[0] &= ~(1 << index);
}

void PlaModelClearHair(int index)
{
    unsigned int k;

    for (k = 0; k <= 1; k++) {
        _PlaModel_apHairLods[index][k].mId = NO_MODEL;
        _PlaModel_apHairLods[index][k].mpUnknown10 = 0;
    }
}

void fn_8015EB4C(int index, int id)
{
    ModelLod_802DF190 *pLods;

    if (_PlaModel_uHatLoadsPending) {
        ResSync(0);
        PlaModelFinishAsyncLoads();
    }
    if (_PlaModel_auLoadQueuedPlayers[1] & (1 << index)) {
        PlaModelLoadHat(index, 0);
    } else if (id != NO_MODEL) {
        pLods = _PlaModel_apHatLods[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            _PlaModel_apHatLods[index][1].mId = id + 1;
            PlaModelLoadHat(index, 1);
        }
    }
    _PlaModel_auLoadQueuedPlayers[1] &= ~(1 << index);
}

void PlaModelClearHat(int index)
{
    unsigned int k;

    for (k = 0; k <= 1; k++) {
        _PlaModel_apHatLods[index][k].mId = NO_MODEL;
        _PlaModel_apHatLods[index][k].mpUnknown10 = 0;
    }
}

void fn_8015EC74(int index, int id)
{
    ModelLod_802DF190 *pLods;

    if (_PlaModel_uGlassesLoadsPending) {
        ResSync(0);
        PlaModelFinishAsyncLoads();
    }
    if (_PlaModel_auLoadQueuedPlayers[2] & (1 << index)) {
        PlaModelLoadGlasses(index, 0);
    } else if (id != NO_MODEL) {
        pLods = _PlaModel_apGlassesLods[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            _PlaModel_apGlassesLods[index][1].mId = id + 1;
            PlaModelLoadGlasses(index, 1);
        }
    }
    _PlaModel_auLoadQueuedPlayers[2] &= ~(1 << index);
}

void PlaModelClearGlasses(int index)
{
    unsigned int k;

    for (k = 0; k <= 1; k++) {
        _PlaModel_apGlassesLods[index][k].mId = NO_MODEL;
        _PlaModel_apGlassesLods[index][k].mpUnknown10 = 0;
    }
}

void fn_8015ED9C(int index, int id)
{
    ModelLod_802DF190 *pLods;

    if (_PlaModel_uJewelLoadsPending) {
        ResSync(0);
        PlaModelFinishAsyncLoads();
    }
    if (_PlaModel_auLoadQueuedPlayers[3] & (1 << index)) {
        PlaModelLoadJewel(index, 0);
    } else if (id != NO_MODEL) {
        pLods = _PlaModel_apJewelLods[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            _PlaModel_apJewelLods[index][1].mId = NO_MODEL;
            PlaModelLoadJewel(index, 1);
        }
    }
    _PlaModel_auLoadQueuedPlayers[3] &= ~(1 << index);
}

void fn_8015EE74(void)
{
    unsigned int i;

    for (i = 0; i <= 3; i++) {
        _PlaModel_apLoadQueues[i] = (PlaModelQueueEntry_t *)fn_801D2B7C(0xE0, 2, 0);
        _PlaModel_aiLoadQueueCounts[i] = 0;
        _PlaModel_auLoadQueuedPlayers[i] = 0;
    }
    _PlaModel_apLoadQueueArchives[0] = _PlaModel_pHairArchive;
    _PlaModel_apLoadQueueArchives[1] = _PlaModel_pHatArchive;
    _PlaModel_apLoadQueueArchives[2] = _PlaModel_pGlassesArchive;
    _PlaModel_apLoadQueueArchives[3] = _PlaModel_pJewelArchive;
}

/* Reads every queued model; a model already read for another player is
   copied from that player's buffer. */
void fn_8015EF10(void)
{
    unsigned int i;
    int j;
    int count;
    PlaModelQueueEntry_t *pQueue;
    unsigned int lastId;
    void *pLast;

    for (i = 0; i <= 3; i++) {
        pQueue = _PlaModel_apLoadQueues[i];
        count = _PlaModel_aiLoadQueueCounts[i];
        pLast = 0;
        lastId = pQueue[0].mId + 1;
        for (j = 0; j < count; j++) {
            if (pQueue[j].mId == lastId) {
                memcpy(pQueue[j].mpData, pLast, MemGetSizeByAddr(1, pLast));
            } else {
                lastId = pQueue[j].mId;
                pLast = pQueue[j].mpData;
                if (i == 0) {
                    ResCopyToBuffer(HairArchive(lastId), HairId(lastId), pLast);
                } else {
                    ResCopyToBuffer(_PlaModel_apLoadQueueArchives[i], lastId, pLast);
                }
            }
        }
    }
    for (i = 0; i <= 3; i++) {
        fn_801D2BD0(_PlaModel_apLoadQueues[i]);
        _PlaModel_apLoadQueues[i] = 0;
    }
}

void fn_8015F068(int index, PlayerHeadIds_t *pIds)
{
    ModelLod_802DF190 *pLods;

    if (pIds->mUnknown0 != NO_MODEL) {
        pLods = _PlaModel_apHairLods[index];
        if (pIds->mUnknown0 != pLods[0].mId || !pLods[0].mpUnknown10 ||
            pIds->mUnknown4 != pLods[1].mId || !pLods[1].mpUnknown10) {
            _PlaModel_apHairLods[index][0].mId = pIds->mUnknown0;
            _PlaModel_apHairLods[index][1].mId = pIds->mUnknown4;
            PlaModelQueuePart(0, index, _PlaModel_apHairLods[index], _PlaModel_apHairData[index]);
        }
    }
}

void fn_8015F124(int index, int id)
{
    ModelLod_802DF190 *pLods;

    if (id != NO_MODEL) {
        pLods = _PlaModel_apHatLods[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10 || pLods[1].mId != id ||
            !pLods[1].mpUnknown10) {
            _PlaModel_apHatLods[index][0].mId = id;
            _PlaModel_apHatLods[index][1].mId = id + 1;
            PlaModelQueuePart(1, index, _PlaModel_apHatLods[index], _PlaModel_apHatData[index]);
        }
    }
}

void fn_8015F1D4(int index, int id)
{
    if ((id == NO_MODEL || (_PlaModel_apGlassesLods[index][0].mId == id && _PlaModel_apGlassesLods[index][0].mpUnknown10)) &&
        _PlaModel_apGlassesLods[index][1].mId == id && _PlaModel_apGlassesLods[index][1].mpUnknown10) {
        return;
    }
    _PlaModel_apGlassesLods[index][0].mId = id;
    _PlaModel_apGlassesLods[index][1].mId = id + 1;
    PlaModelQueuePart(2, index, _PlaModel_apGlassesLods[index], _PlaModel_apGlassesData[index]);
}

void fn_8015F298(int index, int id)
{
    if ((id == NO_MODEL || (_PlaModel_apJewelLods[index][0].mId == id && _PlaModel_apJewelLods[index][0].mpUnknown10)) &&
        _PlaModel_apJewelLods[index][1].mId == id && _PlaModel_apJewelLods[index][1].mpUnknown10) {
        return;
    }
    _PlaModel_apJewelLods[index][0].mId = id;
    _PlaModel_apJewelLods[index][1].mId = NO_MODEL;
    PlaModelQueuePart(3, index, _PlaModel_apJewelLods[index], _PlaModel_apJewelData[index]);
}

void PlaModelBeginFaceCache(void)
{
    _PlaModel_bCacheFace = 1;
    _PlaModel_aiFaceCacheIds[0] = 0;
    _PlaModel_aiFaceCacheIds[1] = 0;
    _PlaModel_apFaceCache[0] = 0;
    _PlaModel_apFaceCache[1] = 0;
}

void PlaModelEndFaceCache(void)
{
    if (_PlaModel_apFaceCache[0]) {
        fn_801D2BD0(_PlaModel_apFaceCache[0]);
        _PlaModel_apFaceCache[0] = 0;
    }
    if (_PlaModel_apFaceCache[1]) {
        fn_801D2BD0(_PlaModel_apFaceCache[1]);
        _PlaModel_apFaceCache[1] = 0;
    }
    _PlaModel_bCacheFace = 0;
    _PlaModel_aiFaceCacheIds[0] = 0;
    _PlaModel_aiFaceCacheIds[1] = 0;
}

void fn_8015F3FC(int a)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        _PlaModel_Face.mpUnknown10[i].mpUnknown10 = 0;
        PlyrModelLodClear(&_PlaModel_pFaceLods[i]);
        _PlaModel_pFaceLods[i].mId = i + 9;
        PlyrModelLodInit(&_PlaModel_pFaceLods[i], &_PlaModel_aBaseHeadLods[i], _PlaModel_pBodySkeleton);
    }
}

void fn_8015F484(AnimSkeleton_t *pSkeleton, AnimSkeleton_t **ppHandSkeletons,
                 AnimSkeleton_t *pHairSkeleton, AnimSkeleton_t *pSkeleton3)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;
    unsigned int nBody = 2;
    unsigned int nHand = 1;
    ModelLod_802DF190 **bodyTbl;
    ModelLod_802DF190 *(*handTbl)[2];

    // FAKEMATCH: both switch arms set the same table pointers; the per-arm
    // assignment keeps the switch compares and hoists both tables' addresses
    // as the target does. nBody and nHand are the loop bounds as locals.
    switch (_PlaModel_iLodMode) {
    case 0:
    case 1:
        bodyTbl = _PlaModel_apBodyLods;
        handTbl = _PlaModel_apHandLods;
        break;
    default:
        bodyTbl = _PlaModel_apBodyLods;
        handTbl = _PlaModel_apHandLods;
        break;
    }

    _PlaModel_pBodySkeleton = pSkeleton;
    _PlaModel_apHandSkeletons[0] = ppHandSkeletons[0];
    _PlaModel_apHandSkeletons[1] = ppHandSkeletons[1];
    _PlaModel_pHairSkeleton = pHairSkeleton;
    _PlaModel_pJewelSkeleton = pSkeleton3;

    for (i = 0; i <= 3; i++) {
        for (k = 0; k < nBody; k++) {
            PlyrModelLodBindSkeleton(&bodyTbl[i][k], _PlaModel_pBodySkeleton);
        }
    }
    for (k = 0; k <= 1; k++) {
        PlyrModelLodBindSkeleton(&_PlaModel_pBaseHeadLods[k], _PlaModel_pBodySkeleton);
        PlyrModelLodBindSkeleton(&_PlaModel_pMorphHeadLods[k], _PlaModel_pBodySkeleton);
    }
    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
            for (k = 0; k < nHand; k++) {
                PlyrModelLodBindSkeleton(&handTbl[i][j][k], _PlaModel_apHandSkeletons[j]);
            }
        }
    }
}

int fn_8015F5BC(const char *pName)
{
    char name[43];
    char *p;
    int id;

    p = strchr(pName, ' ');
    if (p) {
        *p = 0;
    }
    name[0] = 0;
    snprintf(name, sizeof(name), "HEAD_MODEL_%s_2700", pName);
    id = ResFindIndexByName(_PlaModel_pFaceArchive, name);
    if (id == -1) {
        id = 0x1D8;
    }
    return id;
}

// FAKEMATCH: linker-discarded user of the unreferenced .rodata string at 0x802A3F9C, modelled on fn_8015F5BC; only its string reaches the target.
static int _PlayerHeadFindCapModel(int cap, const char *pName)
{
    char name[43];
    int id;

    name[0] = 0;
    snprintf(name, sizeof(name), "HEAD_MODEL_CAP%02d_%s_2700", cap, pName);
    id = ResFindIndexByName(_PlaModel_pFaceArchive, name);
    if (id == -1) {
        id = 0x1D8;
    }
    return id;
}

void PlaModelGetHairStyleModels(int style, int shape, int hat, int *pIds)
{
    DbCursor cursor;

    HairListOpen(&cursor);
    HairListFind(&cursor, style, 0);
    style = HairListGetModel(&cursor);
    HairListClose(&cursor);
    style = style * 28 + shape * 4;
    pIds[0] = style + 1;
    if (hat) {
        pIds[0] = style + 3;
    }
    pIds[1] = pIds[0] + 1;
}

void PlayerHeadGetHairModels(const char *pName, int style, int shape, int hat, PlayerHeadIds_t *pIds)
{
    char name[62];
    char *p;
    int id;

    PlaModelGetHairStyleModels(style, shape, hat, &pIds->mUnknown0);
    if (pName) {
        p = strchr(pName, ' ');
        if (p) {
            *p = 0;
        }
        name[0] = 0;
        if (hat) {
            snprintf(name, sizeof(name), "HAIR_MODEL_%sHAT_2700", pName);
        } else {
            snprintf(name, sizeof(name), "HAIR_MODEL_%s_2700", pName);
        }
        id = ResFindIndexByName(_PlaModel_pRosterHairArchive, name);
        if (id != -1) {
            pIds->mUnknown0 = id + ROSTER_ID_BASE;
        }
        name[0] = 0;
        if (hat) {
            snprintf(name, sizeof(name), "HAIR_MODEL_%sHAT_1500", pName);
        } else {
            snprintf(name, sizeof(name), "HAIR_MODEL_%s_1500", pName);
        }
        id = ResFindIndexByName(_PlaModel_pRosterHairArchive, name);
        if (id != -1) {
            pIds->mUnknown4 = id + ROSTER_ID_BASE;
        }
    }
}

void fn_8015F82C(int id, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback)
{
    int size0;
    int size1;

    _PlaModel_apFaceCallback[0] = pCallback;
    _PlaModel_apFacePlayer[0] = pPlayer;
    if (id != NO_MODEL) {
        _PlaModel_uFaceLoadsPending = 1;
        _PlaModel_pFaceLods[0].mId = id;
        _PlaModel_pFaceLods[1].mId = id + 1;
        size0 = ResGetSize(_PlaModel_pFaceArchive, id);
        size1 = ResGetSize(_PlaModel_pFaceArchive, _PlaModel_pFaceLods[1].mId);
        _PlaModel_apFaceData[0] = (char *)fn_801D2B7C(size0, 2, 0);
        _PlaModel_apFaceData[1] = (char *)fn_801D2B7C(size1, 2, 0);
        _PlaModel_uFaceLoadsPending++;
        ResCopyAsyncToBuffer(_PlaModel_pFaceArchive, _PlaModel_pFaceLods[0].mId, 1, _PlaModel_apFaceData[0], 100, PlaModelFaceReadDone, 0);
        _PlaModel_uFaceLoadsPending++;
        ResCopyAsyncToBuffer(_PlaModel_pFaceArchive, _PlaModel_pFaceLods[1].mId, 1, _PlaModel_apFaceData[1], 100, PlaModelFaceReadDone, 0);
    } else {
        _PlaModel_pFaceLods[0].mId = id;
        _PlaModel_pFaceLods[1].mId = id;
        pCallback(pPlayer);
    }
}

void PlaModelLoadHairAsync(int index, PlayerHeadIds_t *pIds, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback)
{
    ModelLod_802DF190 *pLods;

    _PlaModel_uHairLoadsPending = 1;
    _PlaModel_apHairCallback[0] = pCallback;
    _PlaModel_apHairPlayer[0] = pPlayer;
    _PlaModel_aiHairPlayerIndex[0] = index;
    if (pIds->mUnknown0 != NO_MODEL) {
        pLods = _PlaModel_apHairLods[index];
        if (pIds->mUnknown0 != pLods[0].mId || !pLods[0].mpUnknown10 ||
            pIds->mUnknown4 != pLods[1].mId || !pLods[1].mpUnknown10) {
            _PlaModel_apHairLods[index][0].mId = pIds->mUnknown0;
            _PlaModel_apHairLods[index][1].mId = pIds->mUnknown4;
            _PlaModel_uHairLoadsPending++;
            ResCopyAsyncToBuffer(HairArchive(_PlaModel_apHairLods[index][0].mId), HairId(_PlaModel_apHairLods[index][0].mId), 1,
                        _PlaModel_apHairData[index][0], 100, PlaModelHairReadDone, 0);
            if (_PlaModel_iLodMode) {
                _PlaModel_uHairLoadsPending++;
                ResCopyAsyncToBuffer(HairArchive(_PlaModel_apHairLods[index][1].mId), HairId(_PlaModel_apHairLods[index][1].mId),
                            1, _PlaModel_apHairData[index][1], 100, PlaModelHairReadDone, 0);
            }
            return;
        }
    }
    _PlaModel_uHairLoadsPending = 0;
    _PlaModel_apHairCallback[0](_PlaModel_apHairPlayer[0]);
}

void PlaModelLoadHatAsync(int index, int id, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback)
{
    ModelLod_802DF190 *pLods;

    _PlaModel_uHatLoadsPending = 1;
    _PlaModel_apHatCallback[0] = pCallback;
    _PlaModel_apHatPlayer[0] = pPlayer;
    _PlaModel_aiHatPlayerIndex[0] = index;
    if (id != NO_MODEL) {
        pLods = _PlaModel_apHatLods[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            _PlaModel_apHatLods[index][1].mId = id + 1;
            _PlaModel_uHatLoadsPending++;
            ResCopyAsyncToBuffer(_PlaModel_pHatArchive, _PlaModel_apHatLods[index][0].mId, 1, _PlaModel_apHatData[index][0], 100,
                        PlaModelHatReadDone, 0);
            if (_PlaModel_iLodMode) {
                _PlaModel_uHatLoadsPending++;
                ResCopyAsyncToBuffer(_PlaModel_pHatArchive, _PlaModel_apHatLods[index][1].mId, 1, _PlaModel_apHatData[index][1], 100,
                            PlaModelHatReadDone, 0);
            }
            return;
        }
    }
    _PlaModel_uHatLoadsPending = 0;
    _PlaModel_apHatCallback[0](_PlaModel_apHatPlayer[0]);
}

void PlaModelLoadGlassesAsync(int index, int id, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback)
{
    ModelLod_802DF190 *pLods;

    _PlaModel_uGlassesLoadsPending = 1;
    _PlaModel_apGlassesCallback[0] = pCallback;
    _PlaModel_apGlassesPlayer[0] = pPlayer;
    _PlaModel_aiGlassesPlayerIndex[0] = index;
    if (id != NO_MODEL) {
        pLods = _PlaModel_apGlassesLods[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            _PlaModel_apGlassesLods[index][1].mId = id + 1;
            _PlaModel_uGlassesLoadsPending++;
            ResCopyAsyncToBuffer(_PlaModel_pGlassesArchive, _PlaModel_apGlassesLods[index][0].mId, 1, _PlaModel_apGlassesData[index][0], 100,
                        PlaModelGlassesReadDone, 0);
            if (_PlaModel_iLodMode) {
                _PlaModel_uGlassesLoadsPending++;
                ResCopyAsyncToBuffer(_PlaModel_pGlassesArchive, _PlaModel_apGlassesLods[index][1].mId, 1, _PlaModel_apGlassesData[index][1], 100,
                            PlaModelGlassesReadDone, 0);
            }
            return;
        }
    }
    _PlaModel_uGlassesLoadsPending = 0;
    _PlaModel_apGlassesCallback[0](_PlaModel_apGlassesPlayer[0]);
}

void PlaModelLoadJewelAsync(int index, int id, Object_8003DEC4 *pPlayer, PlaModelLoadCallback_t pCallback)
{
    ModelLod_802DF190 *pLods;

    _PlaModel_uJewelLoadsPending = 1;
    _PlaModel_apJewelCallback[0] = pCallback;
    _PlaModel_apJewelPlayer[0] = pPlayer;
    _PlaModel_aiJewelPlayerIndex[0] = index;
    if (id != NO_MODEL) {
        pLods = _PlaModel_apJewelLods[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            _PlaModel_apJewelLods[index][1].mId = id + 1;
            _PlaModel_uJewelLoadsPending++;
            ResCopyAsyncToBuffer(_PlaModel_pJewelArchive, _PlaModel_apJewelLods[index][0].mId, 1, _PlaModel_apJewelData[index][0], 100,
                        PlaModelJewelReadDone, 0);
            return;
        }
    }
    _PlaModel_uJewelLoadsPending = 0;
    _PlaModel_apJewelCallback[0](_PlaModel_apJewelPlayer[0]);
}

/* Finishes the asynchronous loads started above once only the initial
   count of each is left, then calls the stored completion callback. */
void PlaModelFinishAsyncLoads(void)
{
    if (_PlaModel_uFaceLoadsPending == 1) {
        _PlaModel_uFaceLoadsPending = 0;
        fn_80233EAC(&_PlaModel_Face, _PlaModel_pFaceLods, "PLYRMODEL", 0, _PlaModel_pFaceArchive, _PlaModel_pBodySkeleton,
                    (void **)_PlaModel_apFaceData, 0);
        _PlaModel_apFaceCallback[0](_PlaModel_apFacePlayer[0]);
    }
    if (_PlaModel_uHairLoadsPending == 1) {
        _PlaModel_uHairLoadsPending = 0;
        PlyrRenderBindPartTable(0);
        PlaModelLoadHair(_PlaModel_aiHairPlayerIndex[0], 0);
        PlyrRenderUnbindPartTable();
        _PlaModel_apHairCallback[0](_PlaModel_apHairPlayer[0]);
    }
    if (_PlaModel_uHatLoadsPending == 1) {
        _PlaModel_uHatLoadsPending = 0;
        PlyrRenderBindPartTable(0);
        PlaModelLoadHat(_PlaModel_aiHatPlayerIndex[0], 0);
        PlyrRenderUnbindPartTable();
        _PlaModel_apHatCallback[0](_PlaModel_apHatPlayer[0]);
    }
    if (_PlaModel_uGlassesLoadsPending == 1) {
        _PlaModel_uGlassesLoadsPending = 0;
        PlyrRenderBindPartTable(0);
        PlaModelLoadGlasses(_PlaModel_aiGlassesPlayerIndex[0], 0);
        PlyrRenderUnbindPartTable();
        _PlaModel_apGlassesCallback[0](_PlaModel_apGlassesPlayer[0]);
    }
    if (_PlaModel_uJewelLoadsPending == 1) {
        _PlaModel_uJewelLoadsPending = 0;
        PlyrRenderBindPartTable(0);
        PlaModelLoadJewel(_PlaModel_aiJewelPlayerIndex[0], 0);
        PlyrRenderUnbindPartTable();
        _PlaModel_apJewelCallback[0](_PlaModel_apJewelPlayer[0]);
    }
}

}
