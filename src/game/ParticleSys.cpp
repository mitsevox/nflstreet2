/* In-game particle system: loads the particle effects and their animated
   textures at start-up, spawns and releases emitters for game events, updates
   and draws the live emitters each frame (with the ground pulse and the
   weather), and records particle spawns in the "Replay Particles" replay
   channel so replays show them again. */
#include "game/ParticleSys.h"
#include <dolphin/mtx.h>
#include "game/bitstream.h"
#include "game/cu_8002B8F8.h"
#include <math.h>
#include <string.h>
#include "game/ParticleRender.h"
#include "game/fn_801D2B7C.h"
#include "engine/animTexLib.h"

/* Header of the emitter list built by ParticleSysAllocDrawList and filled by ParticleSysUpdate. */
struct ParticleSysDrawList_t {
    unsigned short mCount;
    unsigned short mCapacity;
    PsysEmitter_t **mppList;
};

/* Snapshot of _ParticleSys_anReplayCounts taken by ParticleSysReplayRead before it stores the new counts. */
struct ParticleSysReplayCounts_t {
    signed char mUnknown0;
    signed char mUnknown1;
};

/* One 12-byte entry of the 20-entry table at _ParticleSys_aEffectFiles. */
struct ParticleSysEffectFile_t {
    int mIndex;
    int mFile;
    int mUnknown8;
};

/* Descriptor passed to fn_801DE1E0. */
struct PsysEmitterDesc_t {
    int mUnknown00;
    unsigned short mUnknown04;
    unsigned short mUnknown06;
    unsigned short mUnknown08;
    float mUnknown0C;
    unsigned char mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int (*mpUnknown20)(PsysEmitter_t *pObject, int mode);
    unsigned char mUnknown24;
};

/* Pool owner returned by fn_801DFD34. */
struct PsysManager_t {
    void *mpPool;
};

/* Pool item of PsysManager_t::mpPool. */
struct PsysPoolItem_t {
    PsysEmitter_t *mpObject;
};

extern "C" {
extern unsigned char gParticleAnimTexFlag;

int fn_8002D0AC(Type_803EA368 *p);
void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030304(void *pStream, float *pValues, int bits, float scale);
void fn_80030554(void *pStream, float *pValues, int bits, float scale);
void fn_8003065C(void *pStream, float *pValues, int bits, float scale);
void fn_80030ACC(void (*pWrite)(BitStream_t *),
                 void (*pRead)(BitStream_t *, BitStream_t *, BitStream_t *, BitStream_t *, float), int size,
                 const char *pName);
int fn_8004CB98(int index);
void fn_800A3170(void);
void fn_800A3450(void);
int fn_800A34C8(int index);
void *fn_800C47C4(void);
void FxParticleDrawBegin(void);
void FxParticleDrawEnd(void);
void FxAnimTexLoadAll(AnimTexFile_t *pEntries, AnimTex_t **pValues, void *pData);
void FxAnimTexFreeAll(AnimTex_t **pValues);
void GroundPulseDraw(void);
void WeatherInit(void);
void WeatherShutdown(void);
void WeatherUpdate(float rate);
void WeatherRender(void);
void *fn_801C6B4C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
void fn_801D0508(void);
void fn_801D0544(void);
void fn_801D0664(Mtx44 m);
void fn_801D0F80(Mtx44 m);
void *fn_801D2BB0(int a, int size, int c, int d);
int ObjNewType_(int type, int size, int count, void *pCreate, void *pDestroy);
int ObjDelType(int type);
void ObjSetListObjFunc(int handle, int type, int a, int (*pCallback)(void *));
int ObjNewInList(int handle, int type, int a, void *pInit);
void ObjRemoveFromList(int handle, int item);
void ObjSetPriority(int handle, int item, int a);
void fn_801DE1E0(PsysEmitterDesc_t *pDesc);
void fn_801DE410(void);
void fn_801DE4F8(unsigned short a);
void fn_801DEA90(PsysEmitter_t *pObject, int a);
unsigned short fn_801DECFC(unsigned short id, void *pDesc);
PsysEmitter_t *fn_801DEEF8(unsigned short handle);
void fn_801DEF18(PsysEmitter_t *pObject);
void fn_801DF620(void *pDesc, void *pData, int a);
PsysManager_t *fn_801DFD34(void);
void PsysColExtClearAll(PsysEmitter_t *pObject);
void *ResLoadToBuffer(void *pArchive, int file, void *pBuffer);
int ResUnLoad(void *pArchive, int file);
int ResGetSize(void *pArchive, int file);
void VptTrashObject(int handle);
void VptFlushObjectTrashSync(void);

void ParticleSysAllocDrawList(void);
void ParticleSysFreeDrawList(void);
void ParticleSysLoadEffect(int index, int id);
void ParticleSysLoadEffects(void);
int ParticleSysReplayGetSize(void);
void ParticleSysReplayWrite(BitStream_t *pStream);
void ParticleSysReplayRead(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t);
void ParticleSysInit(int handle);
void ParticleSysShutdown(int handle);
int ParticleSysDraw(void *pContext);
void ParticleSysUpdate(float rate);
int ParticleSysGetFootstepEffect(int a);
int ParticleSysGetImpactEffect(int a);
void ParticleSysSetEffectFile(int index, int file);
void ParticleSysReplayRegister(void);
void ParticleSysResetEmitter(PsysEmitter_t *pObject);
void ParticleSysBuildFrame(Mtx44 m, Vector_80039F5C *pDir, Vector_80039F5C *pPos);
void fn_802277DC(void *pOut, void *pA, void *pB);
}

static unsigned char _ParticleSys_bInit = 0;
static AnimTexConfig_t _ParticleSys_AnimTexConfig = { 8, {0, 0}, 0, 0 };
static ParticleSysDrawList_t _ParticleSys_DrawList = { 0, 0, 0 };
static int _ParticleSys_iDrawObj = 0;
static unsigned char _ParticleSys_bDrawEnabled = 1;
static signed char _ParticleSys_nReplayRecords = 0;
static signed char _ParticleSys_anReplayCounts[2] = { 0, 0 };

static PsysEmitterDesc_t _ParticleSys_EmitterDesc = { 24, 172, 70, 60, 32.0f, 1, 200000, 20, 1, ParticleRenderEmitter, 0 };
static ParticleSysEffectFile_t _ParticleSys_aEffectFiles[20] = {
    { 0, 46, 14 },  { 1, 18, 0 },   { 2, 19, 0 },   { 3, 22, 0 },   { 4, 23, 0 },
    { 5, 24, 0 },   { 6, 29, 0 },   { 7, 30, 0 },   { 8, -1, 0 },   { 9, -1, 0 },
    { 10, -1, 0 },  { 11, -1, 0 },  { 12, -1, 0 },  { 13, -1, 0 },  { 14, -1, 0 },
    { 15, -1, 0 },  { 16, -1, 0 },  { 17, -1, 0 },  { 18, -1, 0 },  { 19, -1, 0 },
};
static AnimTexFile_t _ParticleSys_aAnimTexFiles[8] = {
    { 0, 94 }, { 0, 95 }, { 0, 96 }, { 0, 97 }, { 0, 98 }, { 0, 99 }, { 0, 100 }, { 0, 101 },
};
static AnimTex_t *_ParticleSys_apAnimTex[8] = { 0 };

static unsigned short _ParticleSys_aEffectHandles[20];
static ParticleSpawnRecord_t _ParticleSys_aReplayRecords[6];

void ParticleSysAllocDrawList(void)
{
    PsysManager_t *pManager = fn_801DFD34();
    ParticleSysDrawList_t *pList = &_ParticleSys_DrawList;
    int count = 0;
    void *pItem;

    for (pItem = fn_801C6B4C(pManager->mpPool, 0); pItem != 0; pItem = fn_801C6C84(pManager->mpPool, pItem)) {
        count++;
    }
    pList->mCapacity = count;
    pList->mCount = 0;
    if (count != 0) {
        pList->mppList = (PsysEmitter_t **)fn_801D2B7C(count * 4, 0, 0);
    } else {
        pList->mppList = 0;
    }
}

void ParticleSysFreeDrawList(void)
{
    ParticleSysDrawList_t *pList = &_ParticleSys_DrawList;

    if (pList->mppList != 0) {
        fn_801D2BD0(pList->mppList);
        pList->mppList = 0;
        pList->mCapacity = 0;
    }
}

void ParticleSysLoadEffect(int index, int id)
{
    char desc[1632];
    void *pArchive = fn_800C47C4();
    void *pBuffer = fn_801D2BB0(1, ResGetSize(pArchive, _ParticleSys_aEffectFiles[index].mFile), 4, 0);
    void *pData = ResLoadToBuffer(pArchive, _ParticleSys_aEffectFiles[index].mFile, pBuffer);

    ResUnLoad(pArchive, _ParticleSys_aEffectFiles[index].mFile);
    fn_801DF620(desc, pData, 0);
    _ParticleSys_aEffectHandles[index] = fn_801DECFC(id, desc);
    fn_801D2BD0(pBuffer);
}

void ParticleSysLoadEffects(void)
{
    unsigned int i;
    int id;

    for (i = 0; i < 1; i++) {
        ParticleSysLoadEffect(i, _ParticleSys_aEffectFiles[i].mUnknown8);
    }
    for (i = 1; i <= 11; i++) {
        id = fn_800A34C8(i);
        if (id != 0) {
            ParticleSysLoadEffect(i, id);
        }
    }
    for (i = 12; i <= 19; i++) {
        id = fn_8004CB98(i);
        if (id != 0) {
            ParticleSysLoadEffect(i, id);
        }
    }
}

/* Size in bits of one replay frame of this channel. */
int ParticleSysReplayGetSize(void)
{
    int size = 8;
    int i;

    for (i = 0; i < 6; i++) {
        size += 16 + 48 + 48 + 32;
    }
    return size;
}

/* Replay channel writer: the record count and the six spawn records, after
   which the pending count is cleared. */
void ParticleSysReplayWrite(BitStream_t *pStream)
{
    unsigned int i;

    fn_80191068(pStream, _ParticleSys_nReplayRecords, 8);
    for (i = 0; i < 6; i++) {
        fn_80191068(pStream, (short)_ParticleSys_aReplayRecords[i].mId, 16);
        fn_80030554(pStream, _ParticleSys_aReplayRecords[i].mPos, 16, 256.0f);
        fn_8003065C(pStream, _ParticleSys_aReplayRecords[i].mRot, 12, 1024.0f);
        fn_80191068(pStream, (unsigned int)_ParticleSys_aReplayRecords[i].mpSource, 32);
    }
    _ParticleSys_nReplayRecords = 0;
}

/* Replay channel reader: every stream holds the same layout; the records of
   pStream1 are spawned again when the stored counts change. */
void ParticleSysReplayRead(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    ParticleSpawnRecord_t record;
    ParticleSysReplayCounts_t last;
    signed char count;
    signed char value;
    unsigned int i;

    count = ReadBitStream(pStream1, 8);
    value = ReadBitStream(pStream0, 8);
    last.mUnknown0 = _ParticleSys_anReplayCounts[0];
    last.mUnknown1 = _ParticleSys_anReplayCounts[1];
    _ParticleSys_anReplayCounts[1] = value;
    _ParticleSys_anReplayCounts[0] = count;
    if (pStream2 != 0) {
        ReadBitStream(pStream2, 8);
    }
    if (pStream3 != 0) {
        ReadBitStream(pStream3, 8);
    }
    for (i = 0; i < count; i++) {
        record.mId = ReadBitStream(pStream1, 16);
        fn_800301C4(pStream1, record.mPos, 16, 256.0f);
        fn_80030304(pStream1, record.mRot, 12, 1024.0f);
        record.mpSource = (ParticleSource_t *)(unsigned int)ReadBitStream(pStream1, 32);
        if (_ParticleSys_anReplayCounts[0] != last.mUnknown0 || _ParticleSys_anReplayCounts[1] != last.mUnknown1) {
            ParticlesSpawnAt(record.mId, record.mPos, record.mRot, record.mpSource);
        }
        ReadBitStream(pStream0, 16);
        fn_800301C4(pStream0, record.mPos, 16, 256.0f);
        fn_80030304(pStream0, record.mRot, 12, 1024.0f);
        ReadBitStream(pStream0, 32);
        if (pStream2 != 0) {
            ReadBitStream(pStream2, 16);
            fn_800301C4(pStream2, record.mPos, 16, 256.0f);
            fn_80030304(pStream2, record.mRot, 12, 1024.0f);
            ReadBitStream(pStream2, 32);
        }
        if (pStream3 != 0) {
            ReadBitStream(pStream3, 16);
            fn_800301C4(pStream3, record.mPos, 16, 256.0f);
            fn_80030304(pStream3, record.mRot, 12, 1024.0f);
            ReadBitStream(pStream3, 32);
        }
    }
    for (i = count; i <= 5; i++) {
        ReadBitStream(pStream1, 16);
        fn_800301C4(pStream1, record.mPos, 16, 256.0f);
        fn_80030304(pStream1, record.mRot, 12, 1024.0f);
        ReadBitStream(pStream1, 32);
        ReadBitStream(pStream0, 16);
        fn_800301C4(pStream0, record.mPos, 16, 256.0f);
        fn_80030304(pStream0, record.mRot, 12, 1024.0f);
        ReadBitStream(pStream0, 32);
        if (pStream2 != 0) {
            ReadBitStream(pStream2, 16);
            fn_800301C4(pStream2, record.mPos, 16, 256.0f);
            fn_80030304(pStream2, record.mRot, 12, 1024.0f);
            ReadBitStream(pStream2, 32);
        }
        if (pStream3 != 0) {
            ReadBitStream(pStream3, 16);
            fn_800301C4(pStream3, record.mPos, 16, 256.0f);
            fn_80030304(pStream3, record.mRot, 12, 1024.0f);
            ReadBitStream(pStream3, 32);
        }
    }
}

void ParticleSysInit(int handle)
{
    int i;

    for (i = 0; i < 20; i++) {
        _ParticleSys_aEffectHandles[i] = 20;
    }
    _ParticleSys_AnimTexConfig.unk_0x4 = gParticleAnimTexFlag;
    AnimTexLibInit(&_ParticleSys_AnimTexConfig);
    FxAnimTexLoadAll(_ParticleSys_aAnimTexFiles, _ParticleSys_apAnimTex, fn_800C47C4());
    fn_801DE1E0(&_ParticleSys_EmitterDesc);
    ParticleSysLoadEffects();
    ParticleSysAllocDrawList();
    ParticleRenderInit(1200);
    ObjNewType_(22, 20, 1, 0, 0);
    ObjSetListObjFunc(handle, 22, 0, ParticleSysDraw);
    _ParticleSys_iDrawObj = ObjNewInList(handle, 22, 0, 0);
    ObjSetPriority(handle, _ParticleSys_iDrawObj, 12);
    _ParticleSys_bInit = 1;
    WeatherInit();
    fn_800A3170();
    _ParticleSys_nReplayRecords = 0;
    memset(_ParticleSys_aReplayRecords, 0, sizeof(_ParticleSys_aReplayRecords));
}

void ParticleSysShutdown(int handle)
{
    fn_800A3450();
    WeatherShutdown();
    FxAnimTexFreeAll(_ParticleSys_apAnimTex);
    fn_801DE410();
    AnimTexLibShutdown();
    ParticleSysFreeDrawList();
    ParticleRenderShutdown();
    ObjRemoveFromList(handle, _ParticleSys_iDrawObj);
    VptTrashObject(_ParticleSys_iDrawObj);
    VptFlushObjectTrashSync();
    ObjDelType(22);
    _ParticleSys_bInit = 0;
}

PsysEmitter_t *ParticleSysSpawnEmitter(ParticleSpawnArgs_t *pArgs, int b, ParticleSource_t *pSource)
{
    PsysEmitter_t *pObject = 0;
    Mtx44 *pTarget;

    if (_ParticleSys_bInit != 0 && pArgs->mUnknown00 != 21 && _ParticleSys_aEffectHandles[pArgs->mUnknown00] != 20
        && (pObject = fn_801DEEF8(_ParticleSys_aEffectHandles[pArgs->mUnknown00])) != 0) {
        if (pSource != 0) {
            pObject->mUnknown35B = (unsigned char)((pSource->mUnknown0C + pSource->mUnknown10 + pSource->mUnknown14) * 33.333336f);
        } else {
            pObject->mUnknown35B = 100;
        }
        pTarget = pArgs->mUnknown04;
        if (pTarget != 0) {
            pObject->mpUnknown3B4 = pTarget;
            pObject->mUnknown3C8 = (*pTarget)[0][3];
            pObject->mUnknown3CC = (*pTarget)[1][3];
            pObject->mUnknown3D0 = (*pTarget)[2][3];
            pObject->mUnknown2B6 = 1;
        } else {
            pObject->mUnknown3C8 = (*pArgs->mUnknown08)[0][3];
            pObject->mUnknown3CC = (*pArgs->mUnknown08)[1][3];
            pObject->mUnknown3D0 = (*pArgs->mUnknown08)[2][3];
            pObject->mUnknown2B6 = 0;
        }
        if (pObject->mUnknown0F0 != 3) {
            pObject->mUnknown35A = 1;
        }
        fn_801D0508();
        if (pObject->mUnknown03C != 0) {
            fn_801D0664(pObject->mUnknown35C);
        }
        fn_801D0F80(pObject->mUnknown35C);
        fn_801D0544();
        pObject->mUnknown03C = 1;
        PsysColExtClearAll(pObject);
    }
    return pObject;
}

void ParticleSysReleaseEmitter(PsysEmitter_t *pObject)
{
    if (pObject->mUnknown2B4 != 0) {
        fn_801DEF18(pObject);
    }
}

void ParticleSysResetEmitter(PsysEmitter_t *pObject)
{
    pObject->mUnknown4C = 0;
    pObject->mUnknown50 = 1;
    pObject->mUnknown54 = 0.0f;
    pObject->mUnknownB0 = 0.0f;
}

int ParticleSysDraw(void *pContext)
{
    if (_ParticleSys_bDrawEnabled != 0) {
        ParticleSysDrawList_t *pList = &_ParticleSys_DrawList;
        unsigned short count = pList->mCount;
        PsysEmitter_t **ppList = pList->mppList;
        unsigned int i;

        FxParticleDrawBegin();
        for (i = 0; i < count; i++) {
            ParticleRenderEmitter(*ppList++, 1);
        }
        FxParticleDrawEnd();
        GroundPulseDraw();
        WeatherRender();
    }
    return 0;
}

void ParticleSysUpdate(float rate)
{
    int count = 0;
    ParticleSysDrawList_t *pList;
    PsysManager_t *pManager;
    PsysPoolItem_t *pItem;

    fn_801DE4F8((unsigned int)fabsf(1.0f / rate * 60.0f));
    pList = &_ParticleSys_DrawList;
    pManager = fn_801DFD34();
    for (pItem = (PsysPoolItem_t *)fn_801C6B4C(pManager->mpPool, 0); pItem != 0;
         pItem = (PsysPoolItem_t *)fn_801C6C84(pManager->mpPool, pItem)) {
        if (pItem->mpObject->mUnknown2B4 != 0) {
            fn_801DEA90(pItem->mpObject, 1);
            pList->mppList[count++] = pItem->mpObject;
        }
    }
    pList->mCount = count;
    WeatherUpdate(rate);
    fn_801DE4F8(60);
}

extern "C" const Vector_80039F5C gParticleSys_vUp = { 0.0f, 0.0f, 1.0f };

void ParticleSysBuildFrame(Mtx44 m, Vector_80039F5C *pDir, Vector_80039F5C *pPos)
{
    Vector_80039F5C fwd;
    Vector_80039F5C up;
    Vector_80039F5C side;

    fwd.mX = -pDir->mX;
    fwd.mY = -pDir->mY;
    fwd.mZ = -pDir->mZ;
    up = gParticleSys_vUp;
    if (fwd.mZ > 0.5f) {
        up.mY = -1.0f;
        up.mZ = 0.0f;
    }
    fn_802277DC(&side, &fwd, &up);
    fn_802277DC(&up, &side, &fwd);
    m[0][0] = side.mX;
    m[0][1] = side.mY;
    m[0][2] = side.mZ;
    m[0][3] = 0.0f;
    m[1][0] = fwd.mX;
    m[1][1] = fwd.mY;
    m[1][2] = fwd.mZ;
    m[1][3] = 0.0f;
    m[2][0] = up.mX;
    m[2][1] = up.mY;
    m[2][2] = up.mZ;
    m[2][3] = 0.0f;
    m[3][0] = pPos->mX;
    m[3][1] = pPos->mY;
    m[3][2] = pPos->mZ;
    m[3][3] = 1.0f;
}

int ParticleSysGetFootstepEffect(int a)
{
    switch (a) {
    case 0:
        return 21;
    case 1:
        return 21;
    case 2:
        return 6;
    case 3:
        return 1;
    case 4:
        return 3;
    case 5:
        return 21;
    case 6:
        return 21;
    case 7:
        return 21;
    case 8:
        return 21;
    case 9:
        return 21;
    case 10:
        return 21;
    case 11:
        return 21;
    case 12:
        return 21;
    case 13:
        return 21;
    }
    return 21;
}

int ParticleSysGetImpactEffect(int a)
{
    switch (a) {
    case 0:
        return 21;
    case 1:
        return 21;
    case 2:
        return 7;
    case 3:
        return 2;
    case 4:
        return 4;
    case 5:
        return 21;
    case 6:
        return 21;
    case 7:
        return 21;
    case 8:
        return 21;
    case 9:
        return 21;
    case 10:
        return 21;
    case 11:
        return 21;
    case 12:
        return 21;
    case 13:
        return 21;
    }
    return 21;
}

void ParticleSysSetEffectFile(int index, int file)
{
    _ParticleSys_aEffectFiles[index].mFile = file;
}

AnimTex_t *ParticleSysGetAnimTex(int index)
{
    return _ParticleSys_apAnimTex[index];
}

void ParticleSysReplayRegister(void)
{
    fn_80030ACC(ParticleSysReplayWrite, ParticleSysReplayRead, ParticleSysReplayGetSize(), "Replay Particles");
}

void ParticleSysReplayRecordSpawn(ParticleSpawnRecord_t record)
{
    if (fn_8002D0AC(lbl_803EA368)) {
        signed char count = _ParticleSys_nReplayRecords;

        if (count <= 5) {
            float *pRot;
            float *pPos;

            _ParticleSys_aReplayRecords[count].mId = record.mId;
            pRot = _ParticleSys_aReplayRecords[count].mRot;
            pRot[0] = record.mRot[0];
            pRot[1] = record.mRot[1];
            pRot[2] = record.mRot[2];
            pRot[3] = record.mRot[3];
            pPos = _ParticleSys_aReplayRecords[count].mPos;
            pPos[0] = record.mPos[0];
            pPos[1] = record.mPos[1];
            pPos[2] = record.mPos[2];
            _ParticleSys_aReplayRecords[count].mpSource = record.mpSource;
            _ParticleSys_nReplayRecords++;
        }
    }
}
