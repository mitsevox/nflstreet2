#include "game/Object_8003DEC4.h"
#include "game/DbCursor.h"
#include "game/Object_80233EAC.h"
#include "game/cu_8015D3EC.h"
#include "game/PlayerLook.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"

#include <string.h>

/* Pending model load sorted by id by fn_8015E0B8. */
struct QueueEntry_8031C098 {
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
void fn_801A4690(int a);
void fn_801A46BC(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
char *fn_801C3084(const char *pString, int c);
int fn_801C9DC8(int value);
void fn_801CE910(void);
int fn_801D3148(int a, void *p);
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

void fn_8015DA7C(void);
void fn_8015DA80(int index, int load);
void fn_8015DD3C(int index, int load);
void fn_8015DE3C(int index, int load);
void fn_8015DF3C(int index, int load);
void fn_8015E1F0(void);
void fn_8015E200(void);
void fn_8015E210(void);
void fn_8015E220(void);
void fn_8015E230(void);
void fn_8015EB00(int index);
void fn_8015EC28(int index);
void fn_8015ED50(int index);
void fn_8015FE4C(void);
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
        lbl_802DFD20[set][0], lbl_802DFD20[set][1], lbl_802DFD20[set][2],                   \
        lbl_802DFD20[set][3], lbl_802DFD20[set][4], lbl_802DFD20[set][5],                   \
        lbl_802DFD20[set][6], lbl_802DFD20[set][7], lbl_802DFD20[set][8],                   \
        lbl_802DFD20[set][9], lbl_802DFD20[set][10], lbl_802DFD20[set][11],                 \
        lbl_802DFD20[set][12], lbl_802DFD20[set][13]                                        \
    }

static const char *lbl_802DF180[4] = { "Heavy", "Muscular", "Thin", "Athletic" };

static ModelLod_802DF190 lbl_802DF190[4][3] = {
    { LOD(0.3f, 2700, 63000, 1), LOD(0.0725f, 1500, 32000, 2), LOD_END },
    { LOD(0.3f, 2700, 63000, 3), LOD(0.0725f, 1500, 32000, 4), LOD_END },
    { LOD(0.3f, 2700, 63000, 5), LOD(0.0725f, 1500, 32000, 6), LOD_END },
    { LOD(0.3f, 2700, 63000, 7), LOD(0.0725f, 1500, 32000, 8), LOD_END },
};

static ModelLod_802DF190 lbl_802DF550[4][2][2] = {
    { { LOD(2.0f, 228, 8000, 13), LOD_END }, { LOD(2.0f, 228, 8000, 14), LOD_END } },
    { { LOD(2.0f, 228, 8000, 15), LOD_END }, { LOD(2.0f, 228, 8000, 16), LOD_END } },
    { { LOD(2.0f, 228, 8000, 17), LOD_END }, { LOD(2.0f, 228, 8000, 18), LOD_END } },
    { { LOD(2.0f, 228, 8000, 19), LOD_END }, { LOD(2.0f, 228, 8000, 20), LOD_END } },
};

static ModelLod_802DF190 lbl_802DFA50[3] = {
    LOD(0.3f, 770, 63000, NO_MODEL), LOD(0.0725f, 400, 32000, NO_MODEL), LOD_END,
};

static ModelLod_802DF190 lbl_802DFB40[3] = {
    LOD(0.3f, 770, 63000, 9), LOD(0.0725f, 400, 32000, 10), LOD_END,
};

static ModelLod_802DF190 lbl_802DFC30[3] = {
    LOD(0.3f, 770, 63000, 11), LOD(0.0725f, 400, 32000, 12), LOD_END,
};

static ModelLod_802DF190 lbl_802DFD20[4][14][3] = {
    PLAYER_LODS_14(1), PLAYER_LODS_14(1), PLAYER_LODS_14(1), PLAYER_LODS_14(0x151),
};

static ModelLod_802DF190 *lbl_802E31A0[4] = {
    lbl_802DF190[0], lbl_802DF190[1], lbl_802DF190[2], lbl_802DF190[3],
};

static ModelLod_802DF190 *lbl_802E31B0[4][2] = {
    { lbl_802DF550[0][0], lbl_802DF550[0][1] },
    { lbl_802DF550[1][0], lbl_802DF550[1][1] },
    { lbl_802DF550[2][0], lbl_802DF550[2][1] },
    { lbl_802DF550[3][0], lbl_802DF550[3][1] },
};

static ModelLod_802DF190 *lbl_802E31D0[14] = PLAYER_TABLE(0);
static ModelLod_802DF190 *lbl_802E3208[14] = PLAYER_TABLE(1);
static ModelLod_802DF190 *lbl_802E3240[14] = PLAYER_TABLE(2);
static ModelLod_802DF190 *lbl_802E3278[14] = PLAYER_TABLE(3);

static unsigned char lbl_803EB330 = 0;
static unsigned char lbl_803EB331 = 0;
static unsigned char lbl_803EB332 = 0;
static unsigned char lbl_803EB333 = 0;
static unsigned char lbl_803EB334 = 0;
static ModelLod_802DF190 *lbl_803EB338 = lbl_802DFA50;
static ModelLod_802DF190 *lbl_803EB33C = lbl_802DFB40;
static ModelLod_802DF190 *lbl_803EB340 = lbl_802DFC30;
static unsigned char lbl_803EB344 = 0;
static AnimSkeleton_t *lbl_803EB348 = 0;
static AnimSkeleton_t *lbl_803EB34C[2] = { 0 };
static AnimSkeleton_t *lbl_803EB354 = 0;
static AnimSkeleton_t *lbl_803EB358 = 0;
static unsigned char lbl_803EB35C = 0;
static unsigned char lbl_803EB35D = 1;
static int lbl_803EB360 = 0;

static QueueEntry_8031C098 *lbl_8031C098[4];
static int lbl_8031C0A8[4];
static void *lbl_8031C0B8[4];
static unsigned int lbl_8031C0C8[4];
static Object_80233EAC lbl_8031C0D8[4];
static Object_80233EAC lbl_8031C128[4][2];
static Object_80233EAC lbl_8031C1C8;
static Object_80233EAC lbl_8031C1DC;
static Object_80233EAC lbl_8031C1F0;
static Object_80233EAC lbl_8031C204[14];
static Object_80233EAC lbl_8031C31C[14];
static Object_80233EAC lbl_8031C434[14];
static Object_80233EAC lbl_8031C54C[14];
static void *lbl_8031C664[4][2];
static void *lbl_8031C684[4][2][1];
static void *lbl_8031C6A4[14][2];
static void *lbl_8031C714[14][2];
static void *lbl_8031C784[14][2];
static void *lbl_8031C7F4[14][2];

static Callback_8015F958 lbl_803ECA6C[1];
static Object_8003DEC4 *lbl_803ECA70[1];
static int lbl_803ECA74[1];
static Callback_8015F958 lbl_803ECA78[1];
static Object_8003DEC4 *lbl_803ECA7C[1];
static int lbl_803ECA80[1];
static Callback_8015F958 lbl_803ECA84[1];
static Object_8003DEC4 *lbl_803ECA88[1];
static int lbl_803ECA8C[1];
static Callback_8015F958 lbl_803ECA90[1];
static Object_8003DEC4 *lbl_803ECA94[1];
static int lbl_803ECA98[1];
static Callback_8015F958 lbl_803ECA9C[1];
static Object_8003DEC4 *lbl_803ECAA0[1];
static void *lbl_803ECAA4[2];
static char *lbl_803ECAAC[2];
static void *lbl_803ECAB4[2];
static char *lbl_803ECABC[2];
static int lbl_803ECAC4[2];
static void *lbl_803ECACC;
static void *lbl_803ECAD0;
static void *lbl_803ECAD4;
static void *lbl_803ECAD8;
static void *lbl_803ECADC;
static void *lbl_803ECAE0;
static void *lbl_803ECAE4;

static inline void *HairArchive(unsigned int id)
{
    return id > ROSTER_ID_BASE ? lbl_803ECAD4 : lbl_803ECAD0;
}

static inline unsigned int HairId(unsigned int id)
{
    return id > ROSTER_ID_BASE ? id - ROSTER_ID_BASE : id;
}

extern "C" {

void fn_8015D3EC(int load)
{
    unsigned int i;
    unsigned int j;
    int count;

    switch (lbl_803EB360) {
    case 0:
    case 1:
        count = 1;
        break;
    default:
        count = 2;
        break;
    }

    for (i = 0; i <= 3; i++) {
        if (load) {
            for (j = 0; j < 2; j++) {
                lbl_8031C664[i][j] =
                    fn_801D2B7C(ResGetSize(lbl_803ECACC, lbl_802E31A0[i][j].mId), 4, 0);
            }
        }
        fn_80233EAC(&lbl_8031C0D8[i], lbl_802E31A0[i], "PLYRBODY", 0, lbl_803ECACC, 0,
                    lbl_8031C664[i], 1);
    }
}

void fn_8015D4E0(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
            if (lbl_8031C664[i][j]) {
                fn_801D2BD0(lbl_8031C664[i][j]);
                lbl_8031C664[i][j] = 0;
            }
        }
    }
}

void fn_8015D550(int load)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;
    unsigned int count;

    switch (lbl_803EB360) {
    case 0:
    case 1:
        count = 1;
        break;
    default:
        count = 2;
        break;
    }

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
            if (load) {
                for (k = 0; k < count; k++) {
                    lbl_8031C684[i][j][k] =
                        fn_801D2B7C(ResGetSize(lbl_803ECACC, lbl_802E31B0[i][j][k].mId), 4, 0);
                }
            }
            fn_80233EAC(&lbl_8031C128[i][j], lbl_802E31B0[i][j], "PLYRHAND", 0, lbl_803ECACC, 0,
                        lbl_8031C684[i][j], 1);
        }
    }
}

void fn_8015D68C(void)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;

    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
            for (k = 0; k < 1; k++) {
                if (lbl_8031C684[i][j][k]) {
                    fn_801D2BD0(lbl_8031C684[i][j][k]);
                    lbl_8031C684[i][j][k] = 0;
                }
            }
        }
    }
}

void fn_8015D718(int load)
{
    unsigned int i;

    if (load) {
        for (i = 0; i < 2; i++) {
            if (lbl_803EB33C[i].mId != NO_MODEL) {
                lbl_803ECAA4[i] =
                    fn_801D2B7C(ResGetSize(lbl_803ECACC, lbl_803EB33C[i].mId), 4, 0);
            }
        }
    }
    fn_80233EAC(&lbl_8031C1DC, lbl_803EB33C, "BASEHEAD", 0, lbl_803ECACC, 0, lbl_803ECAA4, 1);
}

void fn_8015D7C0(void)
{
    unsigned int i;

    for (i = 0; i < 1; i++) {
        if (lbl_8031C684[i]) {
            fn_801D2BD0(lbl_803ECAA4[i]);
            lbl_803ECAA4[i] = 0;
        }
    }
}

void fn_8015D81C(unsigned int players)
{
    unsigned int i;
    unsigned int k;
    unsigned int count;

    switch (lbl_803EB360) {
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
            lbl_8031C6A4[i][k] = fn_801D2B7C(sizesA[k], 4, 0);
            lbl_8031C714[i][k] = fn_801D2B7C(sizesB[k], 4, 0);
            lbl_8031C784[i][k] = fn_801D2B7C(sizesC[k], 4, 0);
            lbl_8031C7F4[i][k] = fn_801D2B7C(sizesD[k], 4, 0);
        }
    }
    for (k = 0; k < count; k++) {
    }
}

void fn_8015D998(void)
{
    unsigned int i;
    unsigned int k;

    for (i = 0; i <= 13; i++) {
        for (k = 0; k <= 1; k++) {
            if (lbl_8031C6A4[i][k]) {
                fn_801D2BD0(lbl_8031C6A4[i][k]);
                lbl_8031C6A4[i][k] = 0;
            }
            if (lbl_8031C714[i][k]) {
                fn_801D2BD0(lbl_8031C714[i][k]);
                lbl_8031C714[i][k] = 0;
            }
            if (lbl_8031C784[i][k]) {
                fn_801D2BD0(lbl_8031C784[i][k]);
                lbl_8031C784[i][k] = 0;
            }
            if (lbl_8031C7F4[i][k]) {
                fn_801D2BD0(lbl_8031C7F4[i][k]);
                lbl_8031C7F4[i][k] = 0;
            }
        }
    }
    for (k = 0; k <= 1; k++) {
    }
}

void fn_8015DA7C(void)
{
}

void fn_8015DA80(int index, int load)
{
    ModelLod_802DF190 *pLods;
    unsigned int count;
    unsigned int k;
    unsigned int id0;
    unsigned int id1;

    pLods = lbl_802E31D0[index];
    id0 = pLods[0].mId;
    id1 = pLods[1].mId;
    switch (lbl_803EB360) {
    case 0:
        pLods[1].mId = NO_MODEL;
        id1 = NO_MODEL;
        count = 1;
        break;
    case 1:
        count = 2;
        break;
    default:
        count = 2;
        break;
    }

    if (load) {
        if (lbl_803EB35D) {
            fn_801CE910();
        }
        ResCopyToBuffer(HairArchive(id0), HairId(lbl_802E31D0[index][0].mId), lbl_8031C6A4[index][0]);
        ResCopyToBuffer(HairArchive(id1), HairId(lbl_802E31D0[index][1].mId), lbl_8031C6A4[index][1]);
        fn_80233EAC(&lbl_8031C204[index], lbl_802E31D0[index], "PLYRMODEL", 0, HairArchive(id0),
                    lbl_803EB354, lbl_8031C6A4[index], 0);
        if (lbl_803EB35D) {
            ResSync(0);
        }
    } else {
        fn_80233EAC(&lbl_8031C204[index], lbl_802E31D0[index], "PLYRMODEL", 0, HairArchive(id0),
                    lbl_803EB354, lbl_8031C6A4[index], 0);
    }

    lbl_802E31D0[index][0].mId = id0;
    if (id0 > ROSTER_ID_BASE) {
        lbl_802E31D0[index][0].mId = id0 - ROSTER_ID_BASE;
    }
    lbl_802E31D0[index][1].mId = id1;
    if (id1 > ROSTER_ID_BASE) {
        lbl_802E31D0[index][1].mId = id1 - ROSTER_ID_BASE;
    }
    for (k = 0; k < count; k++) {
        PlyrModelLodBindSkeleton(&lbl_802E31D0[index][k], lbl_803EB354);
    }
    lbl_802E31D0[index][0].mId = id0;
    lbl_802E31D0[index][1].mId = id1;
}

void fn_8015DD3C(int index, int load)
{
    ModelLod_802DF190 *pLods = lbl_802E3208[index];

    if (lbl_803EB360 == 0) {
        pLods[1].mId = NO_MODEL;
    }

    if (load) {
        if (lbl_803EB35D) {
            fn_801CE910();
        }
        fn_80233EAC(&lbl_8031C31C[index], lbl_802E3208[index], "PLYRMODEL", 0, lbl_803ECADC,
                    lbl_803EB348, lbl_8031C714[index], 1);
        if (lbl_803EB35D) {
            ResSync(0);
        }
    } else {
        fn_80233EAC(&lbl_8031C31C[index], lbl_802E3208[index], "PLYRMODEL", 0, lbl_803ECADC,
                    lbl_803EB348, lbl_8031C714[index], 0);
    }
}

void fn_8015DE3C(int index, int load)
{
    ModelLod_802DF190 *pLods = lbl_802E3240[index];

    if (lbl_803EB360 == 0) {
        pLods[1].mId = NO_MODEL;
    }

    if (load) {
        if (lbl_803EB35D) {
            fn_801CE910();
        }
        fn_80233EAC(&lbl_8031C434[index], lbl_802E3240[index], "PLYRMODEL", 0, lbl_803ECAE0,
                    lbl_803EB348, lbl_8031C784[index], 1);
        if (lbl_803EB35D) {
            ResSync(0);
        }
    } else {
        fn_80233EAC(&lbl_8031C434[index], lbl_802E3240[index], "PLYRMODEL", 0, lbl_803ECAE0,
                    lbl_803EB348, lbl_8031C784[index], 0);
    }
}

void fn_8015DF3C(int index, int load)
{
    ModelLod_802DF190 *pLods = lbl_802E3278[index];
    unsigned int count;
    unsigned int k;

    switch (lbl_803EB360) {
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
        if (lbl_803EB35D) {
            fn_801CE910();
        }
        fn_80233EAC(&lbl_8031C54C[index], lbl_802E3278[index], "PLYRMODEL", 0, lbl_803ECAE4,
                    lbl_803EB358, lbl_8031C7F4[index], 1);
        if (lbl_803EB35D) {
            ResSync(0);
        }
    } else {
        fn_80233EAC(&lbl_8031C54C[index], lbl_802E3278[index], "PLYRMODEL", 0, lbl_803ECAE4,
                    lbl_803EB358, lbl_8031C7F4[index], 0);
    }

    for (k = 0; k < count; k++) {
        PlyrModelLodBindSkeleton(&lbl_802E3278[index][k], lbl_803EB358);
    }
}

/* Queues the models of one player part for fn_8015EF10, keeping each
   queue sorted by id so that equal models are read only once. */
void fn_8015E0B8(int type, int index, ModelLod_802DF190 *pLods, void **ppData)
{
    int count;
    int i;
    int j;
    QueueEntry_8031C098 *pQueue;
    int queued;
    QueueEntry_8031C098 entry;

    switch (lbl_803EB360) {
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

    pQueue = lbl_8031C098[type];
    queued = lbl_8031C0A8[type];
    for (i = 0; i < count; i++) {
        entry.mId = pLods[i].mId;
        if (entry.mId == NO_MODEL) {
            break;
        }
        if (entry.mId != 0) {
            entry.mpData = ppData[i];
            for (j = queued - 1; j >= 0 && pQueue[j].mId > entry.mId; j--) {
                pQueue[j + 1] = pQueue[j];
            }
            pQueue[j + 1] = entry;
            queued++;
        }
    }
    lbl_8031C0A8[type] = queued;
    lbl_8031C0C8[type] |= 1 << index;
}

void fn_8015E1F0(void)
{
    lbl_803EB330--;
}

void fn_8015E200(void)
{
    lbl_803EB331--;
}

void fn_8015E210(void)
{
    lbl_803EB332--;
}

void fn_8015E220(void)
{
    lbl_803EB333--;
}

void fn_8015E230(void)
{
    lbl_803EB334--;
}

void fn_8015E240(int load, int flag)
{
    int size0;
    int size1;
    int value;

    if (load) {
        value = 0;
        size0 = ResGetSize(lbl_803ECACC, lbl_803EB340[0].mId);
        size1 = ResGetSize(lbl_803ECACC, lbl_803EB340[1].mId);
        if (flag) {
            value = 4;
        }
        lbl_803ECAB4[0] = fn_801D2B7C(size0, value, 0);
        lbl_803ECAB4[1] = fn_801D2B7C(size1, value, 0);
    }
    fn_80233EAC(&lbl_8031C1F0, lbl_803EB340, "PLYRMODEL", 0, lbl_803ECACC, 0, lbl_803ECAB4, 1);
}

Object_8023417C *fn_8015E2FC(int type, int index, int a)
{
    switch (type) {
    case 0:
        return fn_8023417C(&lbl_8031C0D8[index], a);
    case 1:
        return fn_8023417C(&lbl_8031C128[index][0], a);
    case 2:
        return fn_8023417C(&lbl_8031C128[index][1], a);
    case 3:
        return fn_8023417C(&lbl_8031C204[index], a);
    case 4:
        return fn_8023417C(&lbl_8031C1C8, a);
    case 5:
        return fn_8023417C(&lbl_8031C1DC, a);
    case 6:
        return fn_8023417C(&lbl_8031C1F0, a);
    case 7:
        return fn_8023417C(&lbl_8031C31C[index], a);
    case 8:
        return fn_8023417C(&lbl_8031C434[index], a);
    case 9:
        return fn_8023417C(&lbl_8031C54C[index], a);
    }
    return 0;
}

Object_80233EAC *fn_8015E440(int type, int index)
{
    Object_80233EAC *pObject;

    switch (type) {
    case 0:
        pObject = &lbl_8031C0D8[index];
        break;
    case 1:
        pObject = &lbl_8031C128[type][0];
        break;
    case 2:
        pObject = &lbl_8031C128[type][1];
        break;
    case 3:
        pObject = &lbl_8031C204[index];
        break;
    case 4:
        pObject = &lbl_8031C1C8;
        break;
    case 5:
        pObject = &lbl_8031C1DC;
        break;
    case 7:
        pObject = &lbl_8031C31C[index];
        break;
    case 8:
        pObject = &lbl_8031C434[index];
        break;
    case 9:
        pObject = &lbl_8031C54C[index];
        break;
    default:
        pObject = 0;
        break;
    }
    return pObject;
}

void fn_8015E548(void)
{
    int a = ResSetMemFlags(4);
    int b = fn_801C9DC8(4);

    lbl_803ECACC = ResOpenDevice(lbl_802EC028, 0x2C);
    lbl_803ECAD0 = ResOpenDevice(lbl_802EC044, 0x2C);
    lbl_803ECAD4 = ResOpenDevice(lbl_802EC050, 0x2C);
    lbl_803ECAD8 = ResOpenDevice(lbl_802EC038, 0x2C);
    lbl_803ECADC = ResOpenDevice(lbl_802EC064, 0x2C);
    lbl_803ECAE0 = ResOpenDevice(lbl_802EC070, 0x2C);
    lbl_803ECAE4 = ResOpenDevice(lbl_802EC08C, 0x2C);
    ResSetMemFlags(a);
    fn_801C9DC8(b);
}

void fn_8015E620(unsigned int players, int mode)
{
    lbl_803EB360 = mode;
    fn_8015D81C(players);
    lbl_803EB35C = 1;
    lbl_803EB35D = 1;
    fn_8015DA7C();
}

void fn_8015E654(int mode)
{
    lbl_803EB360 = mode;
}

void fn_8015E65C(void)
{
    fn_8015D998();
    lbl_803EB35C = 0;
}

void fn_8015E684(void)
{
    fn_801A4690(0);
    fn_8015D3EC(1);
    fn_8015D550(1);
    fn_8015D718(1);
    fn_801A46BC();
}

void fn_8015E6C4(void)
{
}

void fn_8015E6C8(void)
{
    unsigned int i;

    for (i = 0; i <= 13; i++) {
        fn_8015EB00(i);
        fn_8015EC28(i);
        fn_8015ED50(i);
    }
}

void fn_8015E714(void)
{
    fn_8015D4E0();
    fn_8015D68C();
    fn_8015D7C0();
}

void fn_8015E73C(int id)
{
    int size0;
    int size1;

    if (lbl_803EB330) {
        ResSync(0);
        fn_8015FE4C();
    }
    lbl_803EB338[0].mId = id;
    lbl_803EB338[1].mId = id + 1;
    size0 = ResGetSize(lbl_803ECAD8, id);
    size1 = ResGetSize(lbl_803ECAD8, lbl_803EB338[1].mId);
    if (lbl_803EB344 && lbl_803ECAC4[0] == 0 && lbl_803ECAC4[1] == 0) {
        lbl_803ECABC[0] = (char *)fn_801D2B7C(size0, 4, 0);
        lbl_803ECABC[1] = (char *)fn_801D2B7C(size1, 4, 0);
        lbl_803ECAC4[0] = lbl_803EB338[0].mId;
        lbl_803ECAC4[1] = lbl_803EB338[1].mId;
        ResCopyToBuffer(lbl_803ECAD8, lbl_803ECAC4[0], lbl_803ECABC[0]);
        ResCopyToBuffer(lbl_803ECAD8, lbl_803ECAC4[1], lbl_803ECABC[1]);
    }
    lbl_803ECAAC[0] = (char *)fn_801D2B7C(size0, 4, 0);
    lbl_803ECAAC[1] = (char *)fn_801D2B7C(size1, 4, 0);
    if (lbl_803EB344) {
        memcpy(lbl_803ECAAC[0], lbl_803ECABC[0], size0);
        memcpy(lbl_803ECAAC[1], lbl_803ECABC[1], size1);
        fn_80233EAC(&lbl_8031C1C8, lbl_803EB338, "PLYRMODEL", 0, lbl_803ECAD8, lbl_803EB348,
                    (void **)lbl_803ECAAC, 0);
    } else {
        fn_80233EAC(&lbl_8031C1C8, lbl_803EB338, "PLYRMODEL", 0, lbl_803ECAD8, lbl_803EB348,
                    (void **)lbl_803ECAAC, 1);
    }
    if (lbl_803EB35D) {
        ResSync(0);
    }
}

void fn_8015E908(int a)
{
    fn_801D2BD0(lbl_803ECAAC[0]);
    fn_801D2BD0(lbl_803ECAAC[1]);
    lbl_803ECAAC[0] = 0;
    lbl_803ECAAC[1] = 0;
}

void fn_8015E950(int load, int flag)
{
    fn_801A4690(0);
    fn_8015E240(load, flag);
    fn_801A46BC();
}

void fn_8015E994(void)
{
    if (lbl_803ECAB4[0]) {
        fn_801D2BD0(lbl_803ECAB4[0]);
        fn_801D2BD0(lbl_803ECAB4[1]);
        lbl_803ECAB4[0] = 0;
        lbl_803ECAB4[1] = 0;
        lbl_802DFC30[0].mpUnknown10 = 0;
        lbl_802DFC30[1].mpUnknown10 = 0;
    }
}

void fn_8015E9F4(int index, PlayerHeadIds_t *pIds)
{
    ModelLod_802DF190 *pLods;

    if (lbl_803EB331) {
        ResSync(0);
        fn_8015FE4C();
    }
    if (lbl_8031C0C8[0] & (1 << index)) {
        fn_8015DA80(index, 0);
    } else if (pIds->mUnknown0 != NO_MODEL) {
        pLods = lbl_802E31D0[index];
        if (pIds->mUnknown0 != pLods[0].mId || !pLods[0].mpUnknown10 ||
            pIds->mUnknown4 != pLods[1].mId || !pLods[1].mpUnknown10) {
            lbl_802E31D0[index][0].mId = pIds->mUnknown0;
            lbl_802E31D0[index][1].mId = pIds->mUnknown4;
            fn_8015DA80(index, 1);
        }
    }
    lbl_8031C0C8[0] &= ~(1 << index);
}

void fn_8015EB00(int index)
{
    unsigned int k;

    for (k = 0; k <= 1; k++) {
        lbl_802E31D0[index][k].mId = NO_MODEL;
        lbl_802E31D0[index][k].mpUnknown10 = 0;
    }
}

void fn_8015EB4C(int index, int id)
{
    ModelLod_802DF190 *pLods;

    if (lbl_803EB332) {
        ResSync(0);
        fn_8015FE4C();
    }
    if (lbl_8031C0C8[1] & (1 << index)) {
        fn_8015DD3C(index, 0);
    } else if (id != NO_MODEL) {
        pLods = lbl_802E3208[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            lbl_802E3208[index][1].mId = id + 1;
            fn_8015DD3C(index, 1);
        }
    }
    lbl_8031C0C8[1] &= ~(1 << index);
}

void fn_8015EC28(int index)
{
    unsigned int k;

    for (k = 0; k <= 1; k++) {
        lbl_802E3208[index][k].mId = NO_MODEL;
        lbl_802E3208[index][k].mpUnknown10 = 0;
    }
}

void fn_8015EC74(int index, int id)
{
    ModelLod_802DF190 *pLods;

    if (lbl_803EB333) {
        ResSync(0);
        fn_8015FE4C();
    }
    if (lbl_8031C0C8[2] & (1 << index)) {
        fn_8015DE3C(index, 0);
    } else if (id != NO_MODEL) {
        pLods = lbl_802E3240[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            lbl_802E3240[index][1].mId = id + 1;
            fn_8015DE3C(index, 1);
        }
    }
    lbl_8031C0C8[2] &= ~(1 << index);
}

void fn_8015ED50(int index)
{
    unsigned int k;

    for (k = 0; k <= 1; k++) {
        lbl_802E3240[index][k].mId = NO_MODEL;
        lbl_802E3240[index][k].mpUnknown10 = 0;
    }
}

void fn_8015ED9C(int index, int id)
{
    ModelLod_802DF190 *pLods;

    if (lbl_803EB334) {
        ResSync(0);
        fn_8015FE4C();
    }
    if (lbl_8031C0C8[3] & (1 << index)) {
        fn_8015DF3C(index, 0);
    } else if (id != NO_MODEL) {
        pLods = lbl_802E3278[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            lbl_802E3278[index][1].mId = NO_MODEL;
            fn_8015DF3C(index, 1);
        }
    }
    lbl_8031C0C8[3] &= ~(1 << index);
}

void fn_8015EE74(void)
{
    unsigned int i;

    for (i = 0; i <= 3; i++) {
        lbl_8031C098[i] = (QueueEntry_8031C098 *)fn_801D2B7C(0xE0, 2, 0);
        lbl_8031C0A8[i] = 0;
        lbl_8031C0C8[i] = 0;
    }
    lbl_8031C0B8[0] = lbl_803ECAD0;
    lbl_8031C0B8[1] = lbl_803ECADC;
    lbl_8031C0B8[2] = lbl_803ECAE0;
    lbl_8031C0B8[3] = lbl_803ECAE4;
}

/* Reads every queued model; a model already read for another player is
   copied from that player's buffer. */
void fn_8015EF10(void)
{
    unsigned int i;
    int j;
    int count;
    QueueEntry_8031C098 *pQueue;
    unsigned int lastId;
    void *pLast;

    for (i = 0; i <= 3; i++) {
        pQueue = lbl_8031C098[i];
        count = lbl_8031C0A8[i];
        pLast = 0;
        lastId = pQueue[0].mId + 1;
        for (j = 0; j < count; j++) {
            if (pQueue[j].mId == lastId) {
                memcpy(pQueue[j].mpData, pLast, fn_801D3148(1, pLast));
            } else {
                lastId = pQueue[j].mId;
                pLast = pQueue[j].mpData;
                if (i == 0) {
                    ResCopyToBuffer(HairArchive(lastId), HairId(lastId), pLast);
                } else {
                    ResCopyToBuffer(lbl_8031C0B8[i], lastId, pLast);
                }
            }
        }
    }
    for (i = 0; i <= 3; i++) {
        fn_801D2BD0(lbl_8031C098[i]);
        lbl_8031C098[i] = 0;
    }
}

void fn_8015F068(int index, PlayerHeadIds_t *pIds)
{
    ModelLod_802DF190 *pLods;

    if (pIds->mUnknown0 != NO_MODEL) {
        pLods = lbl_802E31D0[index];
        if (pIds->mUnknown0 != pLods[0].mId || !pLods[0].mpUnknown10 ||
            pIds->mUnknown4 != pLods[1].mId || !pLods[1].mpUnknown10) {
            lbl_802E31D0[index][0].mId = pIds->mUnknown0;
            lbl_802E31D0[index][1].mId = pIds->mUnknown4;
            fn_8015E0B8(0, index, lbl_802E31D0[index], lbl_8031C6A4[index]);
        }
    }
}

void fn_8015F124(int index, int id)
{
    ModelLod_802DF190 *pLods;

    if (id != NO_MODEL) {
        pLods = lbl_802E3208[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10 || pLods[1].mId != id ||
            !pLods[1].mpUnknown10) {
            lbl_802E3208[index][0].mId = id;
            lbl_802E3208[index][1].mId = id + 1;
            fn_8015E0B8(1, index, lbl_802E3208[index], lbl_8031C714[index]);
        }
    }
}

void fn_8015F1D4(int index, int id)
{
    if ((id == NO_MODEL || (lbl_802E3240[index][0].mId == id && lbl_802E3240[index][0].mpUnknown10)) &&
        lbl_802E3240[index][1].mId == id && lbl_802E3240[index][1].mpUnknown10) {
        return;
    }
    lbl_802E3240[index][0].mId = id;
    lbl_802E3240[index][1].mId = id + 1;
    fn_8015E0B8(2, index, lbl_802E3240[index], lbl_8031C784[index]);
}

void fn_8015F298(int index, int id)
{
    if ((id == NO_MODEL || (lbl_802E3278[index][0].mId == id && lbl_802E3278[index][0].mpUnknown10)) &&
        lbl_802E3278[index][1].mId == id && lbl_802E3278[index][1].mpUnknown10) {
        return;
    }
    lbl_802E3278[index][0].mId = id;
    lbl_802E3278[index][1].mId = NO_MODEL;
    fn_8015E0B8(3, index, lbl_802E3278[index], lbl_8031C7F4[index]);
}

void fn_8015F35C(void)
{
    lbl_803EB344 = 1;
    lbl_803ECAC4[0] = 0;
    lbl_803ECAC4[1] = 0;
    lbl_803ECABC[0] = 0;
    lbl_803ECABC[1] = 0;
}

void fn_8015F388(void)
{
    if (lbl_803ECABC[0]) {
        fn_801D2BD0(lbl_803ECABC[0]);
        lbl_803ECABC[0] = 0;
    }
    if (lbl_803ECABC[1]) {
        fn_801D2BD0(lbl_803ECABC[1]);
        lbl_803ECABC[1] = 0;
    }
    lbl_803EB344 = 0;
    lbl_803ECAC4[0] = 0;
    lbl_803ECAC4[1] = 0;
}

void fn_8015F3FC(int a)
{
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        lbl_8031C1C8.mpUnknown10[i].mpUnknown10 = 0;
        PlyrModelLodClear(&lbl_803EB338[i]);
        lbl_803EB338[i].mId = i + 9;
        PlyrModelLodInit(&lbl_803EB338[i], &lbl_802DFB40[i], lbl_803EB348);
    }
}

void fn_8015F484(AnimSkeleton_t *pSkeleton, AnimSkeleton_t **ppHandSkeletons,
                 AnimSkeleton_t *pHairSkeleton, AnimSkeleton_t *pSkeleton3)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;
    int count;

    switch (lbl_803EB360) {
    case 0:
    case 1:
        count = 1;
        break;
    default:
        count = 2;
        break;
    }

    lbl_803EB348 = pSkeleton;
    lbl_803EB34C[0] = ppHandSkeletons[0];
    lbl_803EB34C[1] = ppHandSkeletons[1];
    lbl_803EB354 = pHairSkeleton;
    lbl_803EB358 = pSkeleton3;

    for (i = 0; i <= 3; i++) {
        for (k = 0; k < 2; k++) {
            PlyrModelLodBindSkeleton(&lbl_802E31A0[i][k], lbl_803EB348);
        }
    }
    for (k = 0; k <= 1; k++) {
        PlyrModelLodBindSkeleton(&lbl_803EB33C[k], lbl_803EB348);
        PlyrModelLodBindSkeleton(&lbl_803EB340[k], lbl_803EB348);
    }
    for (i = 0; i <= 3; i++) {
        for (j = 0; j <= 1; j++) {
            for (k = 0; k < 1; k++) {
                PlyrModelLodBindSkeleton(&lbl_802E31B0[i][j][k], lbl_803EB34C[j]);
            }
        }
    }
}

int fn_8015F5BC(const char *pName)
{
    char name[43];
    char *p;
    int id;

    p = fn_801C3084(pName, ' ');
    if (p) {
        *p = 0;
    }
    name[0] = 0;
    fn_801C2D88(name, sizeof(name), "HEAD_MODEL_%s_2700", pName);
    id = ResFindIndexByName(lbl_803ECAD8, name);
    if (id == -1) {
        id = 0x1D8;
    }
    return id;
}

void fn_8015F638(int style, int shape, int hat, int *pIds)
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

void fn_8015F6E8(const char *pName, int style, int shape, int hat, PlayerHeadIds_t *pIds)
{
    char name[62];
    char *p;
    int id;

    fn_8015F638(style, shape, hat, &pIds->mUnknown0);
    if (pName) {
        p = fn_801C3084(pName, ' ');
        if (p) {
            *p = 0;
        }
        name[0] = 0;
        if (hat) {
            fn_801C2D88(name, sizeof(name), "HAIR_MODEL_%sHAT_2700", pName);
        } else {
            fn_801C2D88(name, sizeof(name), "HAIR_MODEL_%s_2700", pName);
        }
        id = ResFindIndexByName(lbl_803ECAD4, name);
        if (id != -1) {
            pIds->mUnknown0 = id + ROSTER_ID_BASE;
        }
        name[0] = 0;
        if (hat) {
            fn_801C2D88(name, sizeof(name), "HAIR_MODEL_%sHAT_1500", pName);
        } else {
            fn_801C2D88(name, sizeof(name), "HAIR_MODEL_%s_1500", pName);
        }
        id = ResFindIndexByName(lbl_803ECAD4, name);
        if (id != -1) {
            pIds->mUnknown4 = id + ROSTER_ID_BASE;
        }
    }
}

void fn_8015F82C(int id, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback)
{
    int size0;
    int size1;

    lbl_803ECA6C[0] = pCallback;
    lbl_803ECA70[0] = pPlayer;
    if (id != NO_MODEL) {
        lbl_803EB330 = 1;
        lbl_803EB338[0].mId = id;
        lbl_803EB338[1].mId = id + 1;
        size0 = ResGetSize(lbl_803ECAD8, id);
        size1 = ResGetSize(lbl_803ECAD8, lbl_803EB338[1].mId);
        lbl_803ECAAC[0] = (char *)fn_801D2B7C(size0, 2, 0);
        lbl_803ECAAC[1] = (char *)fn_801D2B7C(size1, 2, 0);
        lbl_803EB330++;
        ResCopyAsyncToBuffer(lbl_803ECAD8, lbl_803EB338[0].mId, 1, lbl_803ECAAC[0], 100, fn_8015E1F0, 0);
        lbl_803EB330++;
        ResCopyAsyncToBuffer(lbl_803ECAD8, lbl_803EB338[1].mId, 1, lbl_803ECAAC[1], 100, fn_8015E1F0, 0);
    } else {
        lbl_803EB338[0].mId = id;
        lbl_803EB338[1].mId = id;
        pCallback(pPlayer);
    }
}

void fn_8015F958(int index, PlayerHeadIds_t *pIds, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback)
{
    ModelLod_802DF190 *pLods;

    lbl_803EB331 = 1;
    lbl_803ECA78[0] = pCallback;
    lbl_803ECA7C[0] = pPlayer;
    lbl_803ECA74[0] = index;
    if (pIds->mUnknown0 != NO_MODEL) {
        pLods = lbl_802E31D0[index];
        if (pIds->mUnknown0 != pLods[0].mId || !pLods[0].mpUnknown10 ||
            pIds->mUnknown4 != pLods[1].mId || !pLods[1].mpUnknown10) {
            lbl_802E31D0[index][0].mId = pIds->mUnknown0;
            lbl_802E31D0[index][1].mId = pIds->mUnknown4;
            lbl_803EB331++;
            ResCopyAsyncToBuffer(HairArchive(lbl_802E31D0[index][0].mId), HairId(lbl_802E31D0[index][0].mId), 1,
                        lbl_8031C6A4[index][0], 100, fn_8015E200, 0);
            if (lbl_803EB360) {
                lbl_803EB331++;
                ResCopyAsyncToBuffer(HairArchive(lbl_802E31D0[index][1].mId), HairId(lbl_802E31D0[index][1].mId),
                            1, lbl_8031C6A4[index][1], 100, fn_8015E200, 0);
            }
            return;
        }
    }
    lbl_803EB331 = 0;
    lbl_803ECA78[0](lbl_803ECA7C[0]);
}

void fn_8015FB38(int index, int id, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback)
{
    ModelLod_802DF190 *pLods;

    lbl_803EB332 = 1;
    lbl_803ECA84[0] = pCallback;
    lbl_803ECA88[0] = pPlayer;
    lbl_803ECA80[0] = index;
    if (id != NO_MODEL) {
        pLods = lbl_802E3208[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            lbl_802E3208[index][1].mId = id + 1;
            lbl_803EB332++;
            ResCopyAsyncToBuffer(lbl_803ECADC, lbl_802E3208[index][0].mId, 1, lbl_8031C714[index][0], 100,
                        fn_8015E210, 0);
            if (lbl_803EB360) {
                lbl_803EB332++;
                ResCopyAsyncToBuffer(lbl_803ECADC, lbl_802E3208[index][1].mId, 1, lbl_8031C714[index][1], 100,
                            fn_8015E210, 0);
            }
            return;
        }
    }
    lbl_803EB332 = 0;
    lbl_803ECA84[0](lbl_803ECA88[0]);
}

void fn_8015FC54(int index, int id, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback)
{
    ModelLod_802DF190 *pLods;

    lbl_803EB333 = 1;
    lbl_803ECA90[0] = pCallback;
    lbl_803ECA94[0] = pPlayer;
    lbl_803ECA8C[0] = index;
    if (id != NO_MODEL) {
        pLods = lbl_802E3240[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            lbl_802E3240[index][1].mId = id + 1;
            lbl_803EB333++;
            ResCopyAsyncToBuffer(lbl_803ECAE0, lbl_802E3240[index][0].mId, 1, lbl_8031C784[index][0], 100,
                        fn_8015E220, 0);
            if (lbl_803EB360) {
                lbl_803EB333++;
                ResCopyAsyncToBuffer(lbl_803ECAE0, lbl_802E3240[index][1].mId, 1, lbl_8031C784[index][1], 100,
                            fn_8015E220, 0);
            }
            return;
        }
    }
    lbl_803EB333 = 0;
    lbl_803ECA90[0](lbl_803ECA94[0]);
}

void fn_8015FD70(int index, int id, Object_8003DEC4 *pPlayer, Callback_8015F958 pCallback)
{
    ModelLod_802DF190 *pLods;

    lbl_803EB334 = 1;
    lbl_803ECA9C[0] = pCallback;
    lbl_803ECAA0[0] = pPlayer;
    lbl_803ECA98[0] = index;
    if (id != NO_MODEL) {
        pLods = lbl_802E3278[index];
        if (pLods[0].mId != id || !pLods[0].mpUnknown10) {
            pLods[0].mId = id;
            lbl_802E3278[index][1].mId = id + 1;
            lbl_803EB334++;
            ResCopyAsyncToBuffer(lbl_803ECAE4, lbl_802E3278[index][0].mId, 1, lbl_8031C7F4[index][0], 100,
                        fn_8015E230, 0);
            return;
        }
    }
    lbl_803EB334 = 0;
    lbl_803ECA9C[0](lbl_803ECAA0[0]);
}

/* Finishes the asynchronous loads started above once only the initial
   count of each is left, then calls the stored completion callback. */
void fn_8015FE4C(void)
{
    if (lbl_803EB330 == 1) {
        lbl_803EB330 = 0;
        fn_80233EAC(&lbl_8031C1C8, lbl_803EB338, "PLYRMODEL", 0, lbl_803ECAD8, lbl_803EB348,
                    (void **)lbl_803ECAAC, 0);
        lbl_803ECA6C[0](lbl_803ECA70[0]);
    }
    if (lbl_803EB331 == 1) {
        lbl_803EB331 = 0;
        fn_801A4690(0);
        fn_8015DA80(lbl_803ECA74[0], 0);
        fn_801A46BC();
        lbl_803ECA78[0](lbl_803ECA7C[0]);
    }
    if (lbl_803EB332 == 1) {
        lbl_803EB332 = 0;
        fn_801A4690(0);
        fn_8015DD3C(lbl_803ECA80[0], 0);
        fn_801A46BC();
        lbl_803ECA84[0](lbl_803ECA88[0]);
    }
    if (lbl_803EB333 == 1) {
        lbl_803EB333 = 0;
        fn_801A4690(0);
        fn_8015DE3C(lbl_803ECA8C[0], 0);
        fn_801A46BC();
        lbl_803ECA90[0](lbl_803ECA94[0]);
    }
    if (lbl_803EB334 == 1) {
        lbl_803EB334 = 0;
        fn_801A4690(0);
        fn_8015DF3C(lbl_803ECA98[0], 0);
        fn_801A46BC();
        lbl_803ECA9C[0](lbl_803ECAA0[0]);
    }
}

}
