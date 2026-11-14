/* Game sound layer of the SndgPathfinder module. It loads the sound banks and plays the
   sound effects of the menus and the match from a table of effect ids, mixes them through
   nine positional sound channels heard from the camera, and runs the stadium ambience
   (the stadium track and the sound objects around the field, such as the ball in flight and
   idling vehicles). It also wraps the Pathfinder interactive music runtime (maps, tracks and their
   callbacks), records the effects for replays, applies the audio volume options and turns
   game events into commentary lines. */

#include "engine/pathfinder.h"
#include <string.h>
#include "game/fn_8009D990.h"

#include "game/SndgPathfinder.h"
#include "game/cu_8002B8F8.h"
#include "game/GameCamera.h"
#include "game/CsisClassHandle.h"
#include "engine/cu_801B8C18.h"
#include "game/Object_8017886C.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/PlayBookGetPlay.h"
#include "game/GameModeType.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"
#include "game/ResLoad.h"
#include "game/fn_801F40F4.h"
#include "game/LevelSurface.h"
#include "game/fn_802270D4.h"

void *operator new(unsigned int size, int unknown);

struct Vec2 {
    float x;
    float y;
};

extern "C" {
int fn_801B8DA8(CsisClassHandle *list, Struct_803EB878 *desc);

extern Struct_803EB878 lbl_803EB878;
extern Struct_803EB878 lbl_803EB888;
extern Struct_803EB878 lbl_803EB890;
extern Struct_803EB878 lbl_803EB898;
extern Struct_803EB878 lbl_803EB8A0;
extern Struct_803EB878 lbl_803EB8A8;
extern Struct_803EB878 lbl_803EB8B0;
extern Struct_803EB878 lbl_803EB8B8;
extern Struct_803EB878 lbl_803EB8C0;
}

static inline int AddSound(CsisClassHandle *list, Struct_803EB878 *desc, void *params, Object_801B9068 **handle)
{
    int err = fn_801B95AC(list, params, handle);
    if (err < 0) {
        fn_801B8DA8(list, desc);
        err = fn_801B95AC(list, params, handle);
    }
    return err;
}

struct SoundObject {
    static void *operator new(unsigned int size)
    {
        Allocator *alloc;
        fn_801B90CC(&alloc);
        fn_801B9148();
        void *p = alloc->Alloc(size, AllocParams());
        fn_801B9174();
        return p;
    }

    static void operator delete(void *p)
    {
        Allocator *alloc;
        fn_801B90CC(&alloc);
        fn_801B9148();
        alloc->Free(p, 0);
        fn_801B9174();
    }

    Object_801B9068 *mHandle;
};

// The fields after mHandle form the parameter block that is registered with
// the per-type list and pushed to the playing handle by Commit().
struct Sound0 : SoundObject {
    void SetVolume(int volume)
    {
        if (volume < 0) {
            volume = 0;
        } else if (volume > 99) {
            volume = 99;
        }
        mVolume = volume;
    }

    void SetPan(int pan)
    {
        if (pan < 0) {
            pan = 0;
        } else if (pan > 0xfffe) {
            pan = 0xfffe;
        }
        mPan = pan;
    }

    Sound0(int volume, unsigned short pan)
    {
        mUnknown4 = 0;
        SetVolume(volume);
        mUnknownC = 0;
        mUnknown10 = 0;
        SetPan(pan);
        AddSound(&gSndgBallThrow, &lbl_803EB878, &mUnknown4, &mHandle);
    }

    ~Sound0()
    {
        if (mHandle != 0) {
            fn_801B96E4(mHandle);
        }
    }

    void Commit()
    {
        if (mHandle != 0) {
            fn_801B983C(mHandle, &mUnknown4);
        }
    }

    int mUnknown4;
    int mVolume;
    int mUnknownC;
    int mUnknown10;
    int mPan;
};

struct SoundVP : SoundObject {
    void SetVolume(int volume)
    {
        if (volume < 0) {
            volume = 0;
        } else if (volume > 99) {
            volume = 99;
        }
        mVolume = volume;
    }

    void SetPan(int pan)
    {
        if (pan < 0) {
            pan = 0;
        } else if (pan > 0xfffe) {
            pan = 0xfffe;
        }
        mPan = pan;
    }

    SoundVP(CsisClassHandle *list, Struct_803EB878 *desc, int volume, unsigned short pan)
    {
        SetVolume(volume);
        SetPan(pan);
        AddSound(list, desc, &mVolume, &mHandle);
    }

    ~SoundVP()
    {
        if (mHandle != 0) {
            fn_801B96E4(mHandle);
        }
    }

    void Commit()
    {
        if (mHandle != 0) {
            fn_801B983C(mHandle, &mVolume);
        }
    }

    int mVolume;
    int mPan;
};

struct SoundVFP : SoundObject {
    void SetVolume(int volume)
    {
        if (volume < 0) {
            volume = 0;
        } else if (volume > 99) {
            volume = 99;
        }
        mVolume = volume;
    }

    void SetUnknown8(int value)
    {
        if (value < 0) {
            value = 0;
        } else if (value > 150) {
            value = 150;
        }
        mUnknown8 = value;
    }

    void SetPan(int pan)
    {
        if (pan < 0) {
            pan = 0;
        } else if (pan > 0xfffe) {
            pan = 0xfffe;
        }
        mPan = pan;
    }

    SoundVFP(CsisClassHandle *list, Struct_803EB878 *desc, int volume, int f, unsigned short pan)
    {
        SetVolume(volume);
        SetUnknown8(f);
        SetPan(pan);
        AddSound(list, desc, &mVolume, &mHandle);
    }

    ~SoundVFP()
    {
        if (mHandle != 0) {
            fn_801B96E4(mHandle);
        }
    }

    void Commit()
    {
        if (mHandle != 0) {
            fn_801B983C(mHandle, &mVolume);
        }
    }

    int mVolume;
    int mUnknown8;
    int mPan;
};

struct Sound3 : SoundObject {
    void SetVolume(int volume)
    {
        if (volume < 0) {
            volume = 0;
        } else if (volume > 99) {
            volume = 99;
        }
        mVolume = volume;
    }

    void SetPan(int pan)
    {
        if (pan < 0) {
            pan = 0;
        } else if (pan > 0xfffe) {
            pan = 0xfffe;
        }
        mPan = pan;
    }

    void SetMode(int mode)
    {
        if (mode < 0) {
            mode = 0;
        } else if (mode > 3) {
            mode = 3;
        }
        mMode = mode;
    }

    Sound3(int volume, unsigned short pan, int mode)
    {
        SetVolume(volume);
        SetPan(pan);
        SetMode(mode);
        AddSound(&gSndgFan, &lbl_803EB888, &mVolume, &mHandle);
    }

    ~Sound3()
    {
        if (mHandle != 0) {
            fn_801B96E4(mHandle);
        }
    }

    void Commit()
    {
        if (mHandle != 0) {
            fn_801B983C(mHandle, &mVolume);
        }
    }

    int mVolume;
    int mPan;
    int mMode;
};

/* Ambient sound bank state (0x8C bytes), allocated by SndgAmbInit. */
struct SndgAmbState_t {
    void *mpUnknown0;
    void *mpUnknown4;
    int mUnknown8;
    int mUnknownC;
    void *mpUnknown10;
    int mHandles[9];
    Sound0 **mSound0;
    SoundVFP **mSound1;
    SoundVP **mSound2;
    Sound3 **mSound3;
    SoundVFP **mSound4;
    SoundVFP **mSound5;
    SoundVFP **mSound6;
    SoundVFP **mSound7;
    SoundVP **mSound8;
    float mScales[9];
    unsigned char mCounts[9];
};

struct SndgAmbLevelObj_t {
    unsigned int mCount;
    float mScale;
};

/* Per sound slot: create, update and stop functions. */
struct SndgAmbTypeFuncs_t {
    void (*mCreate)(int index, Vector_80039F5C *pPos, void *pObject);
    void (*mUpdate)(int index, Vector_80039F5C *pPos, void *pObject);
    void (*mStop)(int index);
};

typedef void (*SndgBankLoadedFn)(int handle);
typedef void (*SndgUpdateFn)(int unknown);

/* 0x1C-byte table entry; the table ends with an entry whose m10 is 3. */
struct SndgResource_t {
    int m0;
    const char *m4;
    void *m8;
    int mC;
    int m10;
    int m14;
    int m18;
};

struct SndgSfx_t {
    int m0;
    int m4;
    int m8;
    unsigned char mC;
    unsigned char mD;
    unsigned char mE[2];
    unsigned int m10;
    int m14;
};

struct SndgConfig_t {
    unsigned int m0;
    unsigned int m4;
    SndgSfx_t *m8;
    SndgAramRegion_t *mC;
    SndgResource_t *m10;
    SndgUpdateFn *m14;
};

struct SndgState_t {
    int m0;
    unsigned int m4;
    unsigned int m8;
    SndgSfx_t *mC;
    SndgResource_t *m10;
    SndgUpdateFn *m14;
    int m18;
    void *m1C;
    unsigned char m20;
    int *m24;
    int *m28;
};

/* Pool node queued by SndgLoadQueueAdd. */
struct SndgLoadRequest_t {
    unsigned int m0;
    void *m4;
    int m8;
    SndgBankLoadedFn mC;
};

struct SndgFalloff_t {
    float mDistance;
    float mFactor;
    float mScaleNoPos;
    float mScalePositional;
};

struct SndgListener_t;
typedef void (*SndgListenerUpdateFn)(SndgListener_t *);

struct SndgListener_t {
    SndgFalloff_t *mParams;
    SndgListenerUpdateFn mUpdate;
    Vector_80039F5C mOrigin;
    int mAngle;
};

struct SndgChannel_t {
    int mHandle;
    int m04;
    SndgListener_t mSource;
    Vector_80039F5C mPosition;
    unsigned char m2C;
    unsigned char mScale;
    unsigned char m2E[2];
};

struct SndgChannelDesc_t {
    unsigned char mScale;
    SndgFalloff_t *mParams;
    SndgListenerUpdateFn mUpdate;
};

struct SndgPathCallback_t {
    void (*mFunc)(int, int);
};

struct SndgPathCallbackKey_t {
    int mKey;
};

/* A sound request queued for replication through the "Sounds" stream (0x14 bytes). */
struct SndgReplaySfx_t {
    unsigned int mId;
    Vector_80039F5C mPos;
    unsigned short mFlags;
    unsigned char mUnknown12;
};

struct SndgReplayQueue_t {
    SndgReplaySfx_t mEntries[12];
    unsigned char mCount;
};

struct SndgSituation_t {
    short mUnknown0;
    short mUnknown2;
    short mUnknown4;
    short mUnknown6;
    short mUnknown8;
    short mUnknownA;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    unsigned char mUnknownE;
    unsigned char mUnknownF;
    char mUnknown10;
    char mUnknown11;
    char mUnknown12;
    char mUnknown13;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    int mFlags;
    float mUnknown1C;
    float mUnknown20;
    Vector_80039F5C mUnknown24;
    int mUnknown30;
    unsigned char mUnknown34;
};

struct SndgPathfinderState {
    void *mpPool[3];
};

extern "C" {
extern char lbl_802EBFCC[];
extern char lbl_802EBFE4[];
extern char lbl_802EBFF4[];
extern char lbl_802EC000[];
extern char lbl_802EC00C[];

int abs(int value);
int fn_8002D060(void *p);
int fn_8002D0AC(void *p);
void fn_800300D4(void *pStream, float *pValues, int bits, float scale);
void fn_80030490(void *pStream, float *pValues, int bits, float scale);
void fn_80030ACC(void (*write)(void *), void (*read)(void *, void *, void *, void *, float), int size,
                 const char *pName);
int ReplayCursorGetPos(float *pValue);
void SndgCrowdSetVolume(unsigned char value);
void fn_8006F850(AudmonEvent_t *pEvent);
void fn_80070C40(AudmonEvent_t *pEvent);
void fn_800717E0(Vector_80039F5C *pPos);
int fn_80071BA0(int a, int b);
void SndgMusicUpdate(void);
void SndgMusicSetVolume(int value);
void SndgMusicRampCutoff(int a, int b);
void SpchIGSaySceneLine(int a, int b, int c);
void SpchIGStopSceneLine(void);
void SpchIGEndSceneLine(void);
void SpchIGPurgeChannel(int a);
unsigned char SpchIGIsEnabled(void);
unsigned char SpchIGIsCommentaryOn(void);
void SpchIGSayTutorialIntro(int a, int b);
void SpchIGSayTutorialPassed(void);
void SpchIGSayTutorialFailed(void);
void SpchIGSayTutorialAdvance(void);
void SpchIGSayCatch(int a);
void SpchIGSayInterception(int a);
void SpchIGSayWallHurdle(int a);
void SpchIGSayStiffArm(int a);
void SpchIGSayJukeSpin(int a);
void SpchIGSayWallHurdleMiss(int a);
void SpchIGSayPassThrown(int a);
void SpchIGSayBallStrip(int a);
void SpchIGSayFumble(void);
void SpchIGSayWallTackle(void);
void SpchIGSetWallTacklePlayer(int a);
void SpchIGSayReceiverOpen(void);
void SpchIGSetReceiverOpenPlayer(int a);
void SpchIGSayStyling(void);
void SpchIGSetStylingPlayer(int a);
void SpchIGSayMissedCatch(Vector_80039F5C *pPos);
void SpchIGSetMissedCatchPlayer(int a);
void SpchIGSayStruggleCarrier(void);
void SpchIGSetStruggleCarrier(int a);
void SpchIGSayStruggleTackler(void);
void SpchIGSetStruggleTackler(int a);
void SpchIGSayPlayResult(void);
void SpchIGSetScorer(int a);
void SpchIGSetDownedCarrier(int a);
void SpchIGSayTeamSceneLine(int a, int b, int c, int d);
void SpchIGStopTeamSceneLine(int a);
void SpchIGEndTeamSceneLine(int a);
void SpchIGSayDownAndDistance(void);
void SpchIGSayPreSnap(int a);
void SpchIGSayDefenseShift(void);
void SpchIGSayOffenseMotion(void);
int GameOptionsGet(int a);
int fn_8009D86C(void);
int fn_800A3444(void);
int fn_800A8444(int a);
int fn_800AD9B4(void);
int fn_800BA6F8(void);
int CamGameGetCurrentSlot(void);
GameCamera_t *CamGameGetCamera(int index);
int CamGameGetHeading(int index);
unsigned int TutorialGetLesson(void);
int fn_80177F70(void);
Vec2 fn_80177FE0(void);
Point_8017886C fn_80178070(void);
float fn_80178298(void);
int fn_80178308(void);
void GetScores(int *pHome, int *pAway);
int fn_80178348(void);
int fn_801784C4(void);
unsigned long long fn_80190F18(void *pStream, int bits);
void fn_80191068(void *pStream, unsigned long long value, int bits);
void fn_801B2F18(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int));
void fn_801B3084(int flags, const char *pName, int value);
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
int fn_801C6DCC(void *pool, int a, int key, void *pResult, int (*match)(SndgPathCallbackKey_t *, int, SndgPathCallbackKey_t **));
void fn_801CE7D0(int a);
int fn_801CFE40(float y, float x);
unsigned int fn_801D27F4(int a);
int MemFill(void *p, int size, int value, int align);
int ResGetSize(void *a, int b);
void ResSetFlags(void *pData, int a);
void SndUnloadAll(void);
int SndEnabled(void);
int SndIsActive(void);
int SndLoadBank(void *pData, int b, int c);
void SndALoadBank(void *pData, int *pSlot, int b, int c, SndgBankLoadedFn cb);
void SndUnloadBank(int handle);
int SndIsBankLoaded(int handle);
void SndStopPatch(int handle);
int SndPatchOver(int handle);
void SndSetPatchPitchMult(int handle, int value);
void SndSetPatchParam(int handle, int a, int value);
void SndSetPatchRate(int handle, int value);
int SndLoadSeq(void *pData, int b);
int SndCreateStream(int a, int b, int c, int d);
void SndDestroyStream(int handle);
void SndPurgeStream(int handle);
void SndStreamAutoVol(int handle, int a, int volume);
void SndStreamSetPan(int handle, int pan, int c);
int SndStreamGetVol(int handle);
void SndStreamSetParam(int handle, int a, int b);
void SndStreamSetControl(int handle, int a);
void SndSetOutputMode(int a, int b);
void SndService(void);
void SndAemsLoadSystem(void *pData, int a, int b);
void SndAemsUnloadSystem(void);
int SndAemsLoadBank(void *pData, int b, int c);
void SndAemsUnloadBank(int handle);
int fn_801F7ABC(void);
int Vec3GetAngle(Vector_80039F5C *a, Vector_80039F5C *b);
int fn_802275D8(Vector_80039F5C *a, Vector_80039F5C *b, float eps);
void fn_80227690(void *pOut, void *a, void *b);
float fn_8022785C(Vector_80039F5C *pPos, Vector_80039F5C *pOther);
unsigned int fn_802372EC(int a, int b);
void SndgReplayReadEntry(SndgReplaySfx_t *pEntry, void *pStream0, void *pStream1, void *pStream2, void *pStream3,
                 float unknown);
void SndgAmbAllocObjects(void);
void SndgAmbFreeObjects(void);
void SndgAmbStartStadiumTrack(void);
void SndgAmbOpenBanks(void);
void SndgAmbCloseBanks(void);
void SndgAmbCalcPan(Vector_80039F5C *pPos, unsigned short *pPan, short *pSpan);
float SndgAmbCameraDistance(Vector_80039F5C *pPos);
int SndgAmbType4CalcParams(Sound0 *pEntry, void *pObject, int index, int init);
void SndgAmbType4Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType4Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType4Stop(int index);
void SndgAmbType5Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType6Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType7Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType8Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType9Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType10Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType11Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType12Create(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType5Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType6Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType7Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType8Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType9Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType10Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType11Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbType12Update(int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbSilenceAll(void);
void SndgAmbType5Stop(int index);
void SndgAmbType6Stop(int index);
void SndgAmbType7Stop(int index);
void SndgAmbType8Stop(int index);
void SndgAmbType9Stop(int index);
void SndgAmbType10Stop(int index);
void SndgAmbType11Stop(int index);
void SndgAmbType12Stop(int index);
int SndgAmbIsActive(void);
void SndgAmbInit(void);
void SndgAmbShutdown(void);
int SndgAmbObjExists(int type, unsigned int index);
void SndgAmbObjCreate(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject);
void SndgAmbObjUpdate(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject);
unsigned int SndgAmbObjFindSlot(int type, int value);
int SndgAmbTypeUsesPathNodes(int type);
int SndgAmbIsPathNodeName(SndgAmbObjInfo_t *p);
void SndgAmbObjStop(int type, unsigned int index);
void SndgAmbPostCue(int type);
void SndgAmbStopAllAndCue(void);
void SndgAmbStopAllObjs(void);
void SndgAmbSetVolume(unsigned int volume);
float SndgAmbGetTypeThreshold(int type);
SndgResource_t *SndgFindResource(int type, int id);
int SndgLoadQueueCompare(void *a, void *b);
void SndgLoadQueueCreate(void);
void SndgLoadQueueDestroy(void);
int SndgLoadQueueAdd(unsigned int index, void *a, int b, SndgBankLoadedFn cb);
void SndgLoadQueueRemove(void *item);
void SndgLoadQueueStart(SndgLoadRequest_t *pNode);
void SndgLoadQueueService(int a);
void SndgLoadQueueFlush(void);
void SndgOpenResources(SndgResource_t *pEntry);
void SndgCloseResources(SndgResource_t *pEntry);
void SndgInit(SndgConfig_t *pInit);
void SndgLoadResources(SndgResource_t *pEntry);
void SndgShutdown(void);
void SndgLoadBank(unsigned int index);
int SndgRequestBank(unsigned int index, int a, SndgBankLoadedFn cb);
int SndgIsBankIndexLoaded(int index, int a);
void SndgUnloadBank(unsigned int index);
int SndgGetBank(unsigned int index);
int SndgIsBankLoaded(unsigned int index);
int SndgIsBankReady(unsigned int index);
int SndgSfxPlay(int index, Vector_80039F5C *pPos);
int SndgSfxPlayVolume(int index, Vector_80039F5C *pPos, unsigned char c);
void SndgSfxStop(int index);
void SndgSfxSetVolume(int index, int a, unsigned char volume);
void SndgUpdate(int a);
void SndgNullHook(void);
void SndgLoadSequence(int index);
void SndgCalcPan(Vector_80039F5C *a, Vector_80039F5C *b, int angle, unsigned short *pOut0, short *pOut1);
unsigned char SndgIsInit(void);
int SndgSfxIsPlaying(int index);
unsigned char SndgSfxGetVolume(int index);
void SndgSetSfxRate(float value);
void SndgHandleBallEvent(AudmonEvent_t *p);
void SndgHandleEvent(AudmonEvent_t *p);
void SndgListenerUpdate(SndgListener_t *src);
void SndgCenterPanNear(Vector_80039F5C *origin, Vector_80039F5C *pos, unsigned short *pan, short *span);
void SndgChannelsReset(void);
void SndgChannelsCreateStreams(int withThird);
void SndgChannelsDestroyStreams(void);
void SndgChannelsCreateFEStream(void);
void SndgChannelsDestroyFEStream(void);
void SndgChannelsInitFE(void);
void SndgChannelsShutdownFE(void);
void SndgChannelsUpdate(int unknown);
unsigned char SndgListenerAttenuate(SndgListener_t *src, Vector_80039F5C *pos, unsigned char volume);
void SndgChannelSetPatchOpts(int idx, Vector_80039F5C *pos, Info_801F40F4 *out);
unsigned char SndgChannelScaleVolume(int idx, unsigned char volume);
int SndgChannelGetStream(int idx);
void SndgChannelSetStream(int idx, int handle);
void SndgChannelSetVolume(int idx, unsigned char percent);
void SndgChannelFadeStream(int idx, int a, int volume);
void SndgChannelSetPosition(int idx, Vector_80039F5C *pos);
void SndgChannelUpdatePan(int idx);
int SndgChannelIsStreamBusy(int idx);
void SndgChannelPurgeStream(int idx);
void SndgPathCallList0(int a, int b);
void SndgPathCallList1(int a, int b);
void SndgPathCallList2(int a, int b);
int SndgPathMatchCallback(SndgPathCallbackKey_t *pItem, int key, SndgPathCallbackKey_t **ppResult);
void SndgPathFadeTrack(int a, int b, int c);
void SndgPathSetStreamValue(int a, int b);
void SndgPathPauseTrack(int a);
void SndgPathResumeTrack(int a);
void SndgPathStopTrack(int a);
void SndgPathAddCallback(int value);
void SndgPathRemoveCallback(int value);
void SndgSituationReset(void);
void SndgSituationUpdate(int unknown);
void SndgSituationSetFlags(int flags);
void SndgSituationHandleEvent(AudmonEvent_t *pEvent);
int SndgReplayFindFreeSlot(void);
void SndgReplayStopAll(void);
void SndgReplayPlayEntry(SndgReplaySfx_t *pEntry);
void SndgReplayWriteEntry(SndgReplaySfx_t *pEntry, void *pStream);
void SndgReplayWriteFrame(void *pStream);
void SndgReplayReadFrame(void *pStream0, void *pStream1, void *pStream2, void *pStream3, float unknown);
void SndgReplayClearQueue(SndgReplayQueue_t *pList);
void SndgReplayInit(void);
void SndgReplayShutdown(void);
void SndgReplayRegister(void);
int SndgReplayGetFrameSize(void);
void SndgReplayQueueEntry(SndgReplaySfx_t *pEntry);
void SndgReplayRecordSfx(int id, Vector_80039F5C *pPos, unsigned char unknown);
void SndgReplayReset(void);
void SndgReplayUpdate(int unknown);
void SndgSetVolumeOption(unsigned int index, unsigned int value);
void SndgApplyVolumeOptions(void);
void SndgSpchHandleEvent(AudmonEvent_t *pEvent);
void SndgSpchSetPlayFlags(int flags);
void SndgSpchClearPlayFlags(int flags);
int SndgSpchGetPlayFlags(void);

void fn_80071748(int unknown);
void SpchIGUpdate(void);
void SpchIGUpdateFrontEnd(void);
void OptAudioUpdate(int unknown);

}

extern "C" {
const char *_SndgAmb_apszPathNodeNames[] = {
    "REC_Car_PathNode09",
    "REC_Car_PathNode11",
    "REC_Car_PathNode14",
    "EAR_GolfCart_pathnode06",
    "CAG_Car_PathNode03",
    "CAG_Car_PathNode06",
    "CAG_Car_PathNode16",
    "AQA_Cars_Pathnode01",
    "AQA_Cars_Pathnode04",
    "AQA_Cars_Pathnode07",
    "AQA_Cars_Pathnode10",
    "AQA_Cars_Pathnode13",
    "AQA_Cars_Pathnode16",
    "STR_Car_PathNode05",
    "STR_Car_PathNode01",
    "ALL_Car_PathNode02",
    "ALL_Car_PathNode09",
    "Leg_Car_PathNode12",
    "Leg_Car_PathNode15",
    0,
};

unsigned char _SndgAmb_aTypeVolume[13] = { 70, 70, 0, 0, 80, 99, 99, 8, 99, 99, 99, 99, 30 };

SndgAmbTypeFuncs_t _SndgAmb_aTypeFuncs[9] = {
    { SndgAmbType4Create, SndgAmbType4Update, SndgAmbType4Stop },
    { SndgAmbType5Create, SndgAmbType5Update, SndgAmbType5Stop },
    { SndgAmbType6Create, SndgAmbType6Update, SndgAmbType6Stop },
    { SndgAmbType7Create, SndgAmbType7Update, SndgAmbType7Stop },
    { SndgAmbType8Create, SndgAmbType8Update, SndgAmbType8Stop },
    { SndgAmbType9Create, SndgAmbType9Update, SndgAmbType9Stop },
    { SndgAmbType10Create, SndgAmbType10Update, SndgAmbType10Stop },
    { SndgAmbType11Create, SndgAmbType11Update, SndgAmbType11Stop },
    { SndgAmbType12Create, SndgAmbType12Update, SndgAmbType12Stop },
};

int _SndgAmb_aCueEvents[4] = { 0x02D2BB24, 0x028C7A9A, 0x02EDEB7B, 0x02F323C1 };
float _SndgAmb_afType4Range[3] = { 0.0f };

SndgSfx_t _Sndg_aSfxTable[145] = {
    { 0, 7, 0, 0x51, 1 },
    { 1, 7, 1, 0x51, 1 },
    { 2, 7, 2, 0x61, 1 },
    { 3, 7, 3, 0x6B, 1 },
    { 4, 7, 4, 0x6B, 1 },
    { 5, 6, 0, 0x5B, 1 },
    { 6, 3, 0, 0x6B, 1 },
    { 7, 4, 0, 0x6B, 1 },
    { 8, 3, 1, 0x5B, 1 },
    { 9, 4, 1, 0x5B, 1 },
    { 10, 3, 2, 0x66, 1 },
    { 11, 4, 2, 0x66, 1 },
    { 12, 5, 0, 0x5B, 1 },
    { 13, 5, 1, 0x5B, 1 },
    { 14, 5, 2, 0x5B, 1 },
    { 15, 5, 3, 0x5B, 1 },
    { 16, 5, 4, 0x5B, 1 },
    { 17, 5, 5, 0x5B, 1 },
    { 18, 13, 0, 0x51, 1 },
    { 19, 13, 1, 0x51, 1 },
    { 20, 13, 2, 0x51, 1 },
    { 21, 14, 0, 0x51, 1 },
    { 22, 14, 1, 0x51, 1 },
    { 23, 14, 2, 0x51, 1 },
    { 24, 13, 3, 0x5B, 1 },
    { 25, 13, 4, 0x5B, 1 },
    { 26, 14, 3, 0x5B, 1 },
    { 27, 14, 4, 0x5B, 1 },
    { 28, 13, 5, 0x5B, 1 },
    { 29, 13, 6, 0x5B, 1 },
    { 30, 13, 7, 0x5B, 1 },
    { 31, 14, 5, 0x5B, 1 },
    { 32, 14, 6, 0x5B, 1 },
    { 33, 14, 7, 0x5B, 1 },
    { 34, 15, 0, 0x5B, 1 },
    { 35, 15, 1, 0x5B, 1 },
    { 36, 8, 0, 0x6B, 1 },
    { 37, 8, 1, 0x6B, 1 },
    { 38, 8, 2, 0x6B, 1 },
    { 39, 8, 3, 0x6B, 1 },
    { 40, 8, 4, 0x6B, 1 },
    { 41, 8, 5, 0x6B, 1 },
    { 42, 17, 0, 0x1F, 1 },
    { 43, 17, 1, 0x1F, 1 },
    { 44, 17, 2, 0x1F, 1 },
    { 45, 11, 0, 0x7F, 1 },
    { 46, 11, 4, 0x7F, 1 },
    { 47, 11, 1, 0x7F, 1 },
    { 48, 11, 5, 0x7F, 1 },
    { 49, 11, 2, 0x7F, 1 },
    { 50, 11, 6, 0x7F, 1 },
    { 51, 11, 3, 0x7F, 1 },
    { 52, 11, 7, 0x7F, 1 },
    { 53, 11, 8, 0x7F, 1 },
    { 54, 11, 9, 0x7F, 1 },
    { 55, 11, 10, 0x7F, 1 },
    { 56, 11, 11, 0x7F, 1 },
    { 57, 11, 12, 0x7F, 1 },
    { 58, 10, 0, 0x51, 1 },
    { 59, 10, 3, 0x51, 1 },
    { 60, 10, 4, 0x5B, 1 },
    { 61, 10, 5, 0x51, 1 },
    { 62, 10, 10, 0x5B, 1 },
    { 63, 10, 15, 0x6B, 1 },
    { 64, 12, 4, 0x39, 1 },
    { 65, 2, 4, 0x52, 5 },
    { 66, 16, 0, 0x52, 5 },
    { 67, 16, 1, 0x52, 5 },
    { 68, 9, 0, 0x6B, 1 },
    { 69, 9, 1, 0x6B, 1 },
    { 70, 9, 2, 0x6B, 1 },
    { 71, 9, 3, 0x6B, 1 },
    { 72, 9, 4, 0x5B, 1 },
    { 73, 9, 5, 0x5B, 1 },
    { 74, 9, 6, 0x5B, 1 },
    { 75, 9, 7, 0x5B, 1 },
    { 76, 9, 8, 0x5B, 1 },
    { 77, 9, 9, 0x5B, 1 },
    { 78, 9, 10, 0x45, 1 },
    { 79, 9, 11, 0x45, 1 },
    { 80, 9, 12, 0x5B, 1 },
    { 81, 9, 13, 0x5B, 1 },
    { 82, 9, 14, 0x5B, 1 },
    { 83, 9, 15, 0x5B, 1 },
    { 84, 9, 16, 0x5B, 1 },
    { 85, 9, 17, 0x5B, 1 },
    { 86, 9, 18, 0x5B, 1 },
    { 87, 9, 19, 0x5B, 1 },
    { 88, 9, 20, 0x5B, 1 },
    { 89, 9, 21, 0x5B, 1 },
    { 90, 9, 22, 0x5B, 1 },
    { 91, 9, 23, 0x5B, 1 },
    { 92, 9, 24, 0x5B, 1 },
    { 93, 9, 25, 0x5B, 1 },
    { 94, 9, 26, 0x5B, 1 },
    { 95, 9, 27, 0x5B, 1 },
    { 96, 9, 28, 0x5B, 1 },
    { 97, 9, 29, 0x5B, 1 },
    { 98, 9, 30, 0x5B, 1 },
    { 99, 9, 31, 0x5B, 1 },
    { 100, 9, 32, 0x5B, 1 },
    { 101, 9, 33, 0x5B, 1 },
    { 102, 9, 34, 0x5B, 1 },
    { 103, 9, 35, 0x5B, 1 },
    { 104, 9, 36, 0x5B, 1 },
    { 105, 9, 37, 0x7F, 1 },
    { 106, 9, 38, 0x5B, 1 },
    { 107, 9, 39, 0x5B, 1 },
    { 108, 9, 40, 0x5B, 1 },
    { 109, 9, 41, 0x5B, 1 },
    { 110, 9, 42, 0x5B, 1 },
    { 111, 9, 43, 0x5B, 1 },
    { 112, 9, 44, 0x5B, 1 },
    { 113, 6, 0, 0x61, 1 },
    { 114, 0, 0, 0x6B, 1 },
    { 115, 0, 1, 0x6B, 1 },
    { 116, 0, 2, 0x6B, 1 },
    { 117, 0, 3, 0x6B, 1 },
    { 118, 0, 4, 0x6B, 1 },
    { 119, 0, 5, 0x6B, 1 },
    { 120, 0, 6, 0x6B, 1 },
    { 121, 0, 12, 0x6B, 1 },
    { 122, 0, 13, 0x6B, 1 },
    { 123, 0, 14, 0x6B, 1 },
    { 124, 0, 15, 0x6B, 1 },
    { 125, 0, 16, 0x6B, 1 },
    { 126, 0, 17, 0x5B, 1 },
    { 127, 0, 18, 0x5B, 1 },
    { 128, 0, 19, 0x6B, 1 },
    { 129, 0, 20, 0x6B, 1 },
    { 130, 0, 21, 0x6B, 1 },
    { 131, 0, 22, 0x5B, 1 },
    { 132, 0, 32, 0x6B, 1 },
    { 133, 0, 33, 0x6B, 1 },
    { 134, 0, 34, 0x7F, 1 },
    { 135, 0, 36, 0x6B, 1 },
    { 136, 0, 37, 0x5B, 1 },
    { 137, 0, 38, 0x6B, 1 },
    { 138, 0, 39, 0x6B, 1 },
    { 139, 1, 3, 0x6B, 1 },
    { 140, 1, 4, 0x6B, 1 },
    { 141, 1, 5, 0x6B, 1 },
    { 142, 1, 6, 0x6B, 1 },
    { 143, 1, 7, 0x6B, 1 },
    { 144, 1, 8, 0x6B, 1 },
};

SndgResource_t _Sndg_aIGResources[18] = {
    { 0, lbl_802EBFCC, 0, 0, 0, 1, 0 },
    { 2, lbl_802EBFE4, 0, -1, 0, 2, 2 },
    { 3, lbl_802EBFE4, 0, 0, 0, 3, 2 },
    { 4, lbl_802EBFE4, 0, 15, 0, 4, 2 },
    { 5, lbl_802EBFE4, 0, 30, 0, 5, 2 },
    { 6, lbl_802EBFE4, 0, 72, 0, 6, 2 },
    { 7, lbl_802EBFE4, 0, 77, 0, 7, 2 },
    { 8, lbl_802EBFE4, 0, -1, 0, 8, 2 },
    { 9, lbl_802EBFE4, 0, 193, 0, 9, 2 },
    { 10, lbl_802EBFE4, 0, 143, 0, 11, 2 },
    { 11, lbl_802EBFE4, 0, 142, 0, 12, 2 },
    { 12, lbl_802EBFE4, 0, 144, 0, 13, 2 },
    { 13, lbl_802EBFE4, 0, 145, 0, 14, 2 },
    { 14, lbl_802EBFE4, 0, 146, 0, 15, 2 },
    { 15, lbl_802EBFE4, 0, 155, 0, 16, 2 },
    { 16, lbl_802EBFE4, 0, -1, 0, 17, 2 },
    { 17, lbl_802EBFE4, 0, 191, 0, 18, 2 },
    { 0, 0, 0, 0, 3, 0, 0 },
};
SndgAramRegion_t gSndgAramRegions[20] = {
    { 0, 0xC00000, 0xe4b800 },
    { 1, 0xe4b800, 0xe89c00 },
    { 2, 0xe89c00, 0xe8c400 },
    { 3, 0xe8c400, 0xe9e400 },
    { 4, 0xe9e400, 0xeb0400 },
    { 5, 0xeb0400, 0xec3000 },
    { 6, 0xec3000, 0xede000 },
    { 7, 0xede000, 0xee4000 },
    { 8, 0xee4000, 0xf00400 },
    { 9, 0xf00400, 0xf81000 },
    { 10, 0xf81000, 0xf81400 },
    { 11, 0xf81400, 0xf93000 },
    { 12, 0xf93000, 0xfb0800 },
    { 13, 0xfb0800, 0xfb1400 },
    { 14, 0xfb1400, 0xfc3800 },
    { 15, 0xfc3800, 0xfd5c00 },
    { 16, 0xfd5c00, 0xfea400 },
    { 17, 0xfea400, 0xffd800 },
    { 18, 0xffd800, 0x1000000 },
    { -1, 0xFFFFFFFF, 0xFFFFFFFF },
};
SndgUpdateFn _Sndg_apfnIGUpdate[] = { SndgChannelsUpdate, SndgSituationUpdate, (SndgUpdateFn)SpchIGUpdate, fn_80071748, SndgReplayUpdate, OptAudioUpdate, 0 };

SndgConfig_t gSndgIGConfig = { 18, 1, _Sndg_aSfxTable, gSndgAramRegions, _Sndg_aIGResources, _Sndg_apfnIGUpdate };

SndgResource_t _Sndg_aFEResources[3] = {
    { 0, lbl_802EBFCC, 0, 0, 0, 1, 0 },
    { 1, lbl_802EBFCC, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 3, 0, 0 },
};
SndgUpdateFn _Sndg_apfnFEUpdate[] = { (SndgUpdateFn)SpchIGUpdateFrontEnd, OptAudioUpdate, 0 };

SndgConfig_t gSndgFEConfig = { 18, 1, _Sndg_aSfxTable, gSndgAramRegions, _Sndg_aFEResources, _Sndg_apfnFEUpdate };

SndgFalloff_t _Sndg_sFalloff = { 10.0f, 0.3f, 1.0f, 1.0f };
SndgFalloff_t _Sndg_sFalloffCh45 = { 10.0f, 0.1f, 1.0f, 1.0f };

SndgChannelDesc_t _Sndg_aChannelDefaults[9] = {
    { 0xFF, &_Sndg_sFalloff, SndgListenerUpdate },
    { 0xFF, &_Sndg_sFalloff, SndgListenerUpdate },
    { 0xFF, &_Sndg_sFalloff, SndgListenerUpdate },
    { 0xFF, 0, 0 },
    { 0xFF, &_Sndg_sFalloffCh45, SndgListenerUpdate },
    { 0xFF, &_Sndg_sFalloffCh45, SndgListenerUpdate },
    { 0xFF, &_Sndg_sFalloff, SndgListenerUpdate },
    { 0xFF, 0, 0 },
    { 0xFF, 0, 0 },
};

Vector_80039F5C _Sndg_vNoPosition = { 3.4028235e38f, 3.4028235e38f, 3.4028235e38f };

}

static ModuleDependency sDependencies[] = { &gSnd, 0 };

SndgPathfinder gSndgPathfinder;

extern "C" {
unsigned char _SndgAmb_aSlotKeys[9][6];
SndgState_t _Sndg_sState;
SndgChannel_t _Sndg_aChannels[9];
SndgSituation_t _SndgSituation_sState;
int _SndgReplay_aHandles[128];

SndgAmbState_t *_SndgAmb_pState = 0;
unsigned int _SndgAmb_uVolume = 99;
int _SndgAmb_iType4Volume = -1;
unsigned int _SndgAmb_uObjVolume = 0xFFFFFFFF;
unsigned int _SndgAmb_uTrackLevel = 100;
int _Sndg_iSfxRate = 0x1000;
}

static void *sLinks[] = { 0 };

extern "C" {
SndgPathfinderState *_SndgPathfinder_pState = 0;
SndgSituation_t *_SndgSituation_pState = &_SndgSituation_sState;
SndgReplayQueue_t *_SndgReplay_pQueue = 0;
int _SndgReplay_iLastHalfFrame = -1;
unsigned char _Sndg_aVolumeCurveMid[4] = { 1, 50, 50, 50 };
int _SndgSpch_iPlayFlags = 0;
unsigned char _SndgSpch_bOffenseMotionSaid = 0;
unsigned char _SndgSpch_bDefenseShiftSaid = 0;
int _SndgPathfinder_iUnused = 0;
int _SndgReplay_iLastFrameParity;
}

static const int _SndgAmb_aLevelTrackVolume[12] = { 70, 70, 61, 70, 70, 70, 55, 70, 60, 67, 70, 70 };

static const SndgAmbLevelObj_t _SndgAmb_aLevelObjects[12][9] = {
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 2, 9.0f } },
    { { 3, 0.0f }, { 3, 2.0f }, { 0, 0.0f }, { 1, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 3, 2.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 4, 5.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 2, 2.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 4, 2.0f }, { 1, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.2f } },
    { { 3, 0.0f }, { 3, 0.5f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.5f }, { 1, 0.5f }, { 1, 0.5f }, { 1, 0.5f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 0, 2.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 1, 2.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 2.0f }, { 0, 0.0f }, { 0, 0.0f }, { 6, 2.0f }, { 1, 0.2f } },
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.5f }, { 0, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 6, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f } },
};

#define ALLOC_LIST(list, Type, slot)                                                      \
    if (_SndgAmb_pState->mCounts[slot] != 0) {                                               \
        _SndgAmb_pState->list = (Type **)fn_801D2B7C(_SndgAmb_pState->mCounts[slot] * 4, 0, 0); \
        memset(_SndgAmb_pState->list, 0, _SndgAmb_pState->mCounts[slot] * 4);                   \
    }

extern "C" void SndgAmbAllocObjects(void)
{
    int level = fn_800A3444();
    int i;
    int j;

    for (i = 0; i < 9; i++) {
        _SndgAmb_pState->mCounts[i] = _SndgAmb_aLevelObjects[level][i].mCount;
        _SndgAmb_pState->mScales[i] = _SndgAmb_aLevelObjects[level][i].mScale;
        for (j = 0; j < 6; j++) {
            _SndgAmb_aSlotKeys[i][j] = 0xFF;
        }
    }
    ALLOC_LIST(mSound0, Sound0, 0);
    ALLOC_LIST(mSound3, Sound3, 3);
    ALLOC_LIST(mSound1, SoundVFP, 1);
    ALLOC_LIST(mSound2, SoundVP, 2);
    ALLOC_LIST(mSound4, SoundVFP, 4);
    ALLOC_LIST(mSound5, SoundVFP, 5);
    ALLOC_LIST(mSound6, SoundVFP, 6);
    ALLOC_LIST(mSound7, SoundVFP, 7);
    ALLOC_LIST(mSound8, SoundVP, 8);
}

#define FREE_LIST(list, Type, slot)                         \
    if (_SndgAmb_pState->mCounts[slot] != 0) {                 \
        unsigned int i;                                     \
        for (i = 0; i < _SndgAmb_pState->mCounts[slot]; i++) { \
            Type *s = _SndgAmb_pState->list[i];                \
            if (s != 0) {                                   \
                delete s;                                   \
            }                                               \
        }                                                   \
        fn_801D2BD0(_SndgAmb_pState->list);                    \
        _SndgAmb_pState->list = 0;                             \
    }

extern "C" void SndgAmbFreeObjects(void)
{
    FREE_LIST(mSound8, SoundVP, 8);
    FREE_LIST(mSound7, SoundVFP, 7);
    FREE_LIST(mSound6, SoundVFP, 6);
    FREE_LIST(mSound5, SoundVFP, 5);
    FREE_LIST(mSound4, SoundVFP, 4);
    FREE_LIST(mSound2, SoundVP, 2);
    FREE_LIST(mSound1, SoundVFP, 1);
    FREE_LIST(mSound3, Sound3, 3);
    FREE_LIST(mSound0, Sound0, 0);
}

extern "C" void SndgAmbStartStadiumTrack(void)
{
    int level = fn_800A3444();

    switch (level) {
    case 0:
        fn_801B3084(0x2000000, "Ambnum", 2);
        break;
    case 1:
        fn_801B3084(0x2000000, "Ambnum", 4);
        break;
    case 3:
        fn_801B3084(0x2000000, "Ambnum", 6);
        break;
    case 2:
        fn_801B3084(0x2000000, "Ambnum", 1);
        break;
    case 4:
        fn_801B3084(0x2000000, "Ambnum", 7);
        break;
    case 9:
        fn_801B3084(0x2000000, "Ambnum", 3);
        break;
    case 5:
        fn_801B3084(0x2000000, "Ambnum", 5);
        break;
    case 6:
        fn_801B3084(0x2000000, "Ambnum", 8);
        break;
    case 7:
        fn_801B3084(0x2000000, "Ambnum", 9);
        break;
    case 8:
        fn_801B3084(0x2000000, "Ambnum", 10);
        break;
    case 11:
        fn_801B3084(0x2000000, "Ambnum", 11);
        break;
    case 10:
        fn_801B3084(0x2000000, "Ambnum", 12);
        break;
    default:
        fn_801B3084(0x2000000, "Ambnum", 1);
        break;
    }
    _SndgAmb_uTrackLevel = _SndgAmb_aLevelTrackVolume[level];
    _SndgAmb_pState->mUnknownC = 0x12000001;
    SndgPathCreateTrack(_SndgAmb_pState->mpUnknown4, 2, 0x12000001, 1.0f);
}

extern "C" void SndgAmbOpenBanks(void)
{
    int level = fn_800A3444();

    _SndgAmb_pState->mHandles[0] = 0;
    _SndgAmb_pState->mHandles[1] = 0;
    _SndgAmb_pState->mHandles[2] = 0;
    _SndgAmb_pState->mHandles[3] = 0;
    _SndgAmb_pState->mHandles[4] = 0;
    _SndgAmb_pState->mHandles[5] = 0;
    _SndgAmb_pState->mHandles[8] = 0;
    _SndgAmb_pState->mHandles[7] = 0;
    _SndgAmb_pState->mHandles[6] = 0;
    if (_SndgAmb_aLevelObjects[level][0].mCount != 0) {
        _SndgAmb_pState->mHandles[0] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 0, 0);
    }
    if (_SndgAmb_aLevelObjects[level][1].mCount != 0) {
        _SndgAmb_pState->mHandles[1] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 3, 0);
    }
    if (_SndgAmb_aLevelObjects[level][2].mCount != 0) {
        _SndgAmb_pState->mHandles[2] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 6, 0);
    }
    if (_SndgAmb_aLevelObjects[level][3].mCount != 0) {
        _SndgAmb_pState->mHandles[3] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 1, 0);
    }
    if (_SndgAmb_aLevelObjects[level][8].mCount != 0) {
        _SndgAmb_pState->mHandles[4] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 7, 0);
    }
    if (_SndgAmb_aLevelObjects[level][4].mCount != 0) {
        _SndgAmb_pState->mHandles[5] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 2, 0);
    }
    if (_SndgAmb_aLevelObjects[level][5].mCount != 0) {
        _SndgAmb_pState->mHandles[6] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 4, 0);
    }
    if (_SndgAmb_aLevelObjects[level][6].mCount != 0) {
        _SndgAmb_pState->mHandles[7] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 5, 0);
    }
    if (_SndgAmb_aLevelObjects[level][7].mCount != 0) {
        _SndgAmb_pState->mHandles[8] = SndAemsLoadBank(_SndgAmb_pState->mpUnknown10, 8, 0);
    }
}

extern "C" void SndgAmbCloseBanks(void)
{
    if (_SndgAmb_pState->mHandles[0] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[0]);
    }
    if (_SndgAmb_pState->mHandles[1] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[1]);
    }
    if (_SndgAmb_pState->mHandles[2] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[2]);
    }
    if (_SndgAmb_pState->mHandles[3] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[3]);
    }
    if (_SndgAmb_pState->mHandles[4] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[4]);
    }
    if (_SndgAmb_pState->mHandles[5] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[5]);
    }
    if (_SndgAmb_pState->mHandles[8] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[8]);
    }
    if (_SndgAmb_pState->mHandles[7] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[7]);
    }
    if (_SndgAmb_pState->mHandles[6] != 0) {
        SndAemsUnloadBank(_SndgAmb_pState->mHandles[6]);
    }
}

extern "C" void SndgAmbCalcPan(Vector_80039F5C *pPos, unsigned short *pPan, short *pSpan)
{
    Vector_80039F5C position;
    GameCamera_t *pCamera;
    int angle;

    pCamera = CamGameGetCamera(CamGameGetCurrentSlot());
    position.mX = pCamera->mHeader.mUnknown04[0];
    position.mY = pCamera->mHeader.mUnknown04[1];
    position.mZ = pCamera->mHeader.mUnknown04[2];
    angle = CamGameGetHeading(CamGameGetCurrentSlot());
    if (fn_801784C4()) {
        angle = (angle + 0x800000) & 0xFFFFFF;
        position.mX = -position.mX;
        position.mY = -position.mY;
    }
    SndgCalcPan(&position, pPos, angle, pPan, pSpan);
}

extern "C" float SndgAmbCameraDistance(Vector_80039F5C *pPos)
{
    Vector_80039F5C position;
    GameCamera_t *pCamera;

    pCamera = CamGameGetCamera(CamGameGetCurrentSlot());
    position.mX = pCamera->mHeader.mUnknown04[0];
    position.mY = pCamera->mHeader.mUnknown04[1];
    position.mZ = pCamera->mHeader.mUnknown04[2];
    if (fn_801784C4()) {
        position.mX = -position.mX;
        position.mY = -position.mY;
    }
    return fn_8022785C(&position, pPos);
}

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

static inline int ClampVolume(int volume)
{
    if (volume < 0) {
        volume = 0;
    } else if (volume > 127) {
        volume = 127;
    }
    return volume;
}

extern "C" int SndgAmbType4CalcParams(Sound0 *pEntry, void *pObject, int index, int init)
{
    Vector_80039F5C position;
    Vector_80039F5C other;
    float height;
    float distance;
    int result;

    BallGetPosition((Ball_t *)pObject, &position);
    height = position.mZ;
    BallGetLandingPoint((Ball_t *)pObject, &other);
    result = 1;
    distance = fn_8022785C(&position, &other);
    if (init) {
        _SndgAmb_afType4Range[index] = distance;
        if (fn_800A8444(fn_80178308()) == 0) {
            pEntry->mUnknown4 = ClampVolume(MIN((int)(MIN(distance, 50.0f) * (127.0f / 50.0f)), 124));
        } else {
            pEntry->mUnknown4 = 127;
        }
    }
    pEntry->mUnknown10 = ClampVolume(height >= 1.5f ? (int)((MIN(height, 15.0f) - 1.5f) * (127.0f / (15.0f - 1.5f))) : 0);
    if (!init) {
        if (pEntry->mUnknownC < (int)(distance * 127.0f / _SndgAmb_afType4Range[index])) {
            result = 0;
        }
    }
    pEntry->mUnknownC = ClampVolume((int)(distance * 127.0f / _SndgAmb_afType4Range[index]));
    return result;
}

static inline unsigned int SoundVolume(int type)
{
    unsigned int volume = _SndgAmb_uObjVolume * _SndgAmb_aTypeVolume[type] / 100;
    if (volume > 99) {
        volume = 99;
    }
    return volume;
}

extern "C" void SndgAmbType4Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound0[index] == 0) {
        unsigned short pan;
        short unk;
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_iType4Volume = SoundVolume(4);
        if (_SndgAmb_iType4Volume != 0) {
            _SndgAmb_pState->mSound0[index] = new Sound0(_SndgAmb_iType4Volume, pan);
            SndgAmbType4CalcParams(_SndgAmb_pState->mSound0[index], pObject, index, 1);
            _SndgAmb_pState->mSound0[index]->Commit();
        }
    }
}

extern "C" void SndgAmbType4Update(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound0[index] != 0) {
        int volume = _SndgAmb_iType4Volume;
        unsigned short pan;
        short unk;
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound0[index]->SetPan(pan);
        _SndgAmb_pState->mSound0[index]->SetVolume(volume);
        if (SndgAmbType4CalcParams(_SndgAmb_pState->mSound0[index], pObject, index, 0)) {
            _SndgAmb_pState->mSound0[index]->Commit();
            int v = _SndgAmb_pState->mSound0[index]->mUnknown10;
            int cutoff;
            if (v >= 0) {
                if (v <= 127) {
                    cutoff = (int)(((127.0f - v) * (17500.0f / 127.0f) + 2500.0f) * 0.002f * 500.0f);
                } else {
                    cutoff = 2500;
                }
            } else {
                cutoff = 20000;
            }
            SndgMusicRampCutoff(cutoff, 0);
            float level = GameOptionsGet(4);
            int w = _SndgAmb_pState->mSound0[index]->mUnknown10;
            SndgChannelSetVolume(1, (w >= 0 ? (w <= 127 ? (int)(level / (w * 2.0f * (1.0f / 127.0f) + 1.0f))
                                                : (int)(level * (1.0f / 3.0f)))
                                    : (int)level) * 10);
        } else {
            SndgAmbObjStop(4, index);
        }
    }
}

extern "C" void SndgAmbType4Stop(int index)
{
    Sound0 *s = _SndgAmb_pState->mSound0[index];
    if (s != 0) {
        delete s;
        _SndgAmb_pState->mSound0[index] = 0;
        SndgMusicRampCutoff(20000, 0);
        SndgChannelSetVolume(1, GameOptionsGet(4) * 10);
    }
}

extern "C" void SndgAmbType5Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound1[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(5);
        float f = SndgAmbCameraDistance(pPos);
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound1[index] = new SoundVFP(&gSndgIdleVehicle, &lbl_803EB8C0, volume, (int)f, pan);
        _SndgAmb_pState->mSound1[index]->Commit();
    }
}

extern "C" void SndgAmbType6Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound2[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(6);
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound2[index] = new SoundVP(&gSndgIdleIdleTruck, &lbl_803EB8B8, volume, pan);
        _SndgAmb_pState->mSound2[index]->Commit();
    }
}

extern "C" void SndgAmbType7Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound3[index] == 0) {
        unsigned int volume = SoundVolume(7);
        unsigned short pan = 0;
        short unk = 0;
        int mode = 2;
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound3[index] = new Sound3(volume, pan, mode);
        _SndgAmb_pState->mSound3[index]->Commit();
    }
}

extern "C" void SndgAmbType8Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound4[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(8);
        float f = SndgAmbCameraDistance(pPos);
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound4[index] = new SoundVFP(&gSndgIdleBus, &lbl_803EB890, volume, (int)f, pan);
        _SndgAmb_pState->mSound4[index]->Commit();
    }
}

extern "C" void SndgAmbType9Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound5[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(9);
        float f = SndgAmbCameraDistance(pPos);
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound5[index] = new SoundVFP(&gSndgIdlePolice, &lbl_803EB8A8, volume, (int)f, pan);
        _SndgAmb_pState->mSound5[index]->Commit();
    }
}

extern "C" void SndgAmbType10Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound6[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(10);
        float f = SndgAmbCameraDistance(pPos);
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound6[index] = new SoundVFP(&gSndgIdleGolfCart, &lbl_803EB8B0, volume, (int)f, pan);
        _SndgAmb_pState->mSound6[index]->Commit();
    }
}

extern "C" void SndgAmbType11Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound7[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(11);
        float f = SndgAmbCameraDistance(pPos);
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound7[index] = new SoundVFP(&gSndgIdleTruck, &lbl_803EB8A0, volume, (int)f, pan);
        _SndgAmb_pState->mSound7[index]->Commit();
    }
}

extern "C" void SndgAmbType12Create(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (_SndgAmb_pState->mSound8[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(12);
        SndgAmbCalcPan(pPos, &pan, &unk);
        _SndgAmb_pState->mSound8[index] = new SoundVP(&gSndgIdleTrain, &lbl_803EB898, volume, pan);
        _SndgAmb_pState->mSound8[index]->Commit();
    }
}

#define UPDATE_VFP(name, list, type)                                      \
    extern "C" void name(int index, Vector_80039F5C *pPos, void *pObject) \
    {                                                                     \
        if (_SndgAmb_pState->list[index] != 0) {                             \
            unsigned short pan = 0;                                       \
            short unk = 0;                                                \
            unsigned int volume = SoundVolume(type);                      \
            float f = SndgAmbCameraDistance(pPos);                                  \
            SndgAmbCalcPan(pPos, &pan, &unk);                                \
            _SndgAmb_pState->list[index]->SetUnknown8((int)f);               \
            _SndgAmb_pState->list[index]->SetPan(pan);                       \
            _SndgAmb_pState->list[index]->SetVolume(volume);                 \
            _SndgAmb_pState->list[index]->Commit();                          \
        }                                                                 \
    }

#define UPDATE_VP(name, list, type)                                       \
    extern "C" void name(int index, Vector_80039F5C *pPos, void *pObject) \
    {                                                                     \
        if (_SndgAmb_pState->list[index] != 0) {                             \
            unsigned short pan;                                           \
            short unk;                                                    \
            unsigned int volume = SoundVolume(type);                      \
            SndgAmbCalcPan(pPos, &pan, &unk);                                \
            _SndgAmb_pState->list[index]->SetPan(pan);                       \
            _SndgAmb_pState->list[index]->SetVolume(volume);                 \
            _SndgAmb_pState->list[index]->Commit();                          \
        }                                                                 \
    }

UPDATE_VFP(SndgAmbType5Update, mSound1, 5)
UPDATE_VP(SndgAmbType6Update, mSound2, 6)
UPDATE_VP(SndgAmbType7Update, mSound3, 7)
UPDATE_VFP(SndgAmbType8Update, mSound4, 8)
UPDATE_VFP(SndgAmbType9Update, mSound5, 9)
UPDATE_VFP(SndgAmbType10Update, mSound6, 10)
UPDATE_VFP(SndgAmbType11Update, mSound7, 11)
UPDATE_VP(SndgAmbType12Update, mSound8, 12)

#define SILENCE(list, type)                                                   \
    if (_SndgAmb_pState->list != 0) {                                            \
        for (unsigned int i = 0; i < _SndgAmb_aLevelObjects[level][type].mCount; i++) { \
            if (_SndgAmb_pState->list[i] != 0) {                                 \
                _SndgAmb_pState->list[i]->SetVolume(0);                          \
                _SndgAmb_pState->list[i]->Commit();                              \
            }                                                                 \
        }                                                                     \
    }

extern "C" void SndgAmbSilenceAll(void)
{
    int level = fn_800A3444();
    SILENCE(mSound0, 0)
    SILENCE(mSound1, 1)
    SILENCE(mSound2, 2)
    SILENCE(mSound3, 3)
    SILENCE(mSound4, 4)
    SILENCE(mSound5, 5)
    SILENCE(mSound6, 6)
    SILENCE(mSound7, 7)
    SILENCE(mSound8, 8)
}

#define STOP(name, list, Type)               \
    extern "C" void name(int index)          \
    {                                        \
        Type *s = _SndgAmb_pState->list[index]; \
        if (s != 0) {                        \
            delete s;                        \
            _SndgAmb_pState->list[index] = 0;   \
        }                                    \
    }

STOP(SndgAmbType5Stop, mSound1, SoundVFP)
STOP(SndgAmbType6Stop, mSound2, SoundVP)
STOP(SndgAmbType7Stop, mSound3, Sound3)
STOP(SndgAmbType8Stop, mSound4, SoundVFP)
STOP(SndgAmbType9Stop, mSound5, SoundVFP)
STOP(SndgAmbType10Stop, mSound6, SoundVFP)
STOP(SndgAmbType11Stop, mSound7, SoundVFP)
STOP(SndgAmbType12Stop, mSound8, SoundVP)

extern "C" int SndgAmbIsActive(void)
{
    return _SndgAmb_pState != 0;
}

extern "C" void SndgAmbInit(void)
{
    if (SndEnabled()) {
        _SndgAmb_pState = (SndgAmbState_t *)fn_801D2B7C(sizeof(SndgAmbState_t), 0, 0);
        memset(_SndgAmb_pState, 0, sizeof(SndgAmbState_t));
        _SndgAmb_pState->mpUnknown0 = (void *)-1;
        _SndgAmb_pState->mpUnknown4 = (void *)-1;
        _SndgAmb_pState->mpUnknown10 = (void *)-1;
        _SndgAmb_pState->mpUnknown0 = ResOpenDevice(lbl_802EBFF4, 44);
        _SndgAmb_pState->mpUnknown4 = ResOpenDevice(lbl_802EC00C, 44);
        _SndgAmb_pState->mpUnknown10 = ResOpenDevice(lbl_802EC000, 44);
        SndAemsLoadSystem(_SndgAmb_pState->mpUnknown0, 1, 0);
        _SndgAmb_pState->mUnknown8 = SndgPathLoadMap(_SndgAmb_pState->mpUnknown4, 1);
        SndgAmbStartStadiumTrack();
        SndgAmbOpenBanks();
        SndgAmbAllocObjects();
        SndgPathSetTrackVolume(_SndgAmb_pState->mUnknownC, _SndgAmb_uVolume * _SndgAmb_uTrackLevel / 100);
        _SndgAmb_iType4Volume = (unsigned char)(GameOptionsGet(4) * 10);
        _SndgAmb_uObjVolume = (unsigned char)(GameOptionsGet(4) * 10);
    }
}

extern "C" void SndgAmbShutdown(void)
{
    if (SndgAmbIsActive()) {
        SndgAmbFreeObjects();
        SndgPathDestroyTrack(_SndgAmb_pState->mUnknownC);
        SndgPathUnloadMap(_SndgAmb_pState->mUnknown8);
        SndgAmbCloseBanks();
        SndAemsUnloadSystem();
        ResClose(_SndgAmb_pState->mpUnknown0);
        ResClose(_SndgAmb_pState->mpUnknown4);
        ResClose(_SndgAmb_pState->mpUnknown10);
        fn_801D2BD0(_SndgAmb_pState);
        _SndgAmb_pState = 0;
    }
}

static inline int IsActive(SoundObject *pSound) { return pSound != 0; }

extern "C" int SndgAmbObjExists(int type, unsigned int index)
{
    int result = 0;
    if (SndgAmbIsActive() && index < _SndgAmb_pState->mCounts[type - 4]) {
        switch (type) {
        case 4:
            result = IsActive(_SndgAmb_pState->mSound0[index]);
            break;
        case 5:
            result = IsActive(_SndgAmb_pState->mSound1[index]);
            break;
        case 6:
            result = IsActive(_SndgAmb_pState->mSound2[index]);
            break;
        case 7:
            result = IsActive(_SndgAmb_pState->mSound3[index]);
            break;
        case 8:
            result = IsActive(_SndgAmb_pState->mSound4[index]);
            break;
        case 9:
            result = IsActive(_SndgAmb_pState->mSound5[index]);
            break;
        case 10:
            result = IsActive(_SndgAmb_pState->mSound6[index]);
            break;
        case 11:
            result = IsActive(_SndgAmb_pState->mSound7[index]);
            break;
        case 12:
            result = IsActive(_SndgAmb_pState->mSound8[index]);
            break;
        }
    }
    return result;
}

extern "C" void SndgAmbObjCreate(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject)
{
    if (SndgAmbIsActive() && _SndgAmb_aTypeFuncs[type - 4].mCreate && index < _SndgAmb_pState->mCounts[type - 4]) {
        _SndgAmb_aTypeFuncs[type - 4].mCreate(index, pPos, pObject);
    }
}

extern "C" void SndgAmbObjUpdate(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject)
{
    if (SndgAmbIsActive() && SndgAmbObjExists(type, index) && _SndgAmb_aTypeFuncs[type - 4].mUpdate &&
        index < _SndgAmb_pState->mCounts[type - 4]) {
        _SndgAmb_aTypeFuncs[type - 4].mUpdate(index, pPos, pObject);
    }
}

extern "C" unsigned int SndgAmbObjFindSlot(int type, int value)
{
    unsigned int result = 0;
    if (SndgAmbIsActive() && _SndgAmb_pState->mCounts[type - 4] != 0) {
        int found = 0;
        unsigned int i;
        for (i = 0; i <= 5 && !found; i++) {
            if (_SndgAmb_aSlotKeys[type - 4][i] == value) {
                result = i;
                found = 1;
            }
        }
        if (!found) {
            for (i = 0; i <= 5; i++) {
                if (_SndgAmb_aSlotKeys[type - 4][i] == 0xFF) {
                    _SndgAmb_aSlotKeys[type - 4][i] = value;
                    result = i;
                    break;
                }
            }
        }
    }
    return result;
}

extern "C" int SndgAmbTypeUsesPathNodes(int type)
{
    int result = 0;
    int level = fn_800A3444();
    if (type != 12) {
        switch (level) {
        case 2:
        case 4:
        case 5:
        case 7:
        case 9:
        case 10:
        case 11:
            result = 1;
            break;
        default:
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" int SndgAmbIsPathNodeName(SndgAmbObjInfo_t *p)
{
    const char *str = p->mUnknown8;
    int i;
    for (i = 0; _SndgAmb_apszPathNodeNames[i]; i++) {
        if (!strcmp(str, _SndgAmb_apszPathNodeNames[i])) {
            return 1;
        }
    }
    return 0;
}

extern "C" void SndgAmbObjStop(int type, unsigned int index)
{
    if (SndgAmbIsActive() && SndgAmbObjExists(type, index) && _SndgAmb_aTypeFuncs[type - 4].mStop &&
        index < _SndgAmb_pState->mCounts[type - 4]) {
        _SndgAmb_aTypeFuncs[type - 4].mStop(index);
    }
}

extern "C" void SndgAmbPostCue(int type)
{
    if (SndgAmbIsActive()) {
        if (type == 2) {
            SndgAmbSilenceAll();
        }
        SndgPathPostEvent(_SndgAmb_pState->mUnknownC, _SndgAmb_aCueEvents[type]);
    }
}

extern "C" void SndgAmbStopAllAndCue(void)
{
    SndgAmbStopAllObjs();
    SndgAmbPostCue(2);
}

extern "C" void SndgAmbStopAllObjs(void)
{
    if (SndgAmbIsActive()) {
        unsigned char type;
        for (type = 4; type <= 12; type++) {
            unsigned char i;
            for (i = 0; i < _SndgAmb_pState->mCounts[type - 4]; i++) {
                SndgAmbObjStop(type, i);
            }
        }
    }
}

extern "C" void SndgAmbSetVolume(unsigned int volume)
{
    _SndgAmb_uVolume = volume;
    if (SndgAmbIsActive()) {
        SndgPathSetTrackVolume(_SndgAmb_pState->mUnknownC, volume * _SndgAmb_uTrackLevel / 100);
        _SndgAmb_iType4Volume = _SndgAmb_uObjVolume = volume;
    }
}

extern "C" float SndgAmbGetTypeThreshold(int type)
{
    if (_SndgAmb_pState) {
        return _SndgAmb_pState->mScales[type - 4];
    }
    return 0.5f;
}

extern "C" SndgResource_t *SndgFindResource(int type, int id)
{
    SndgResource_t *pEntry = _Sndg_sState.m10;

    while (pEntry->m10 != 3) {
        if (pEntry->m10 == type && pEntry->m0 == id) {
            break;
        }
        pEntry++;
    }
    return pEntry;
}

extern "C" int SndgLoadQueueCompare(void *a, void *b)
{
    return -1;
}

extern "C" void SndgLoadQueueCreate(void)
{
    _Sndg_sState.m1C = fn_801C68FC(1, 0, 20, sizeof(SndgLoadRequest_t), SndgLoadQueueCompare, 0);
}

extern "C" void SndgLoadQueueDestroy(void)
{
    if (_Sndg_sState.m1C != 0) {
        fn_801C69E4(_Sndg_sState.m1C);
        _Sndg_sState.m1C = 0;
    }
}

extern "C" int SndgLoadQueueAdd(unsigned int index, void *a, int b, SndgBankLoadedFn cb)
{
    int result = 0;
    int isNew = 1;
    SndgLoadRequest_t *pNode;

    if (index >= _Sndg_sState.m4) {
        return 0;
    }
    if (_Sndg_sState.m1C == 0) {
        return 0;
    }
    for (pNode = (SndgLoadRequest_t *)fn_801C6B4C(_Sndg_sState.m1C, 0); pNode != 0;
         pNode = (SndgLoadRequest_t *)fn_801C6C84(_Sndg_sState.m1C, pNode)) {
        if (pNode->m4 == a && pNode->m8 == b) {
            isNew = 0;
        }
    }
    if (isNew) {
        pNode = (SndgLoadRequest_t *)fn_801C6A20(_Sndg_sState.m1C);
        if (pNode != 0) {
            pNode->m0 = index;
            pNode->m4 = a;
            pNode->m8 = b;
            pNode->mC = cb;
            fn_801C6AA4(_Sndg_sState.m1C, pNode, 0);
            result = 1;
        }
    }
    return result;
}

extern "C" void SndgLoadQueueRemove(void *item)
{
    if (_Sndg_sState.m1C != 0) {
        fn_801C6C0C(_Sndg_sState.m1C, item);
    }
}

extern "C" void SndgLoadQueueStart(SndgLoadRequest_t *pNode)
{
    if (_Sndg_sState.m1C != 0) {
        if (ResGetSize(pNode->m4, pNode->m8) < fn_801D27F4(1)) {
            int *pSlot;
            SndgResource_t *pEntry;

            if (SndgGetBank(pNode->m0)) {
                SndgUnloadBank(pNode->m0);
            }
            pSlot = &_Sndg_sState.m24[pNode->m0];
            pEntry = SndgFindResource(0, pNode->m0);
            SndALoadBank(pNode->m4, pSlot, pNode->m8, pEntry->m14, pNode->mC);
            _Sndg_sState.m18 = pNode->m0;
        }
    }
}

extern "C" void SndgLoadQueueService(int a)
{
    SndgLoadRequest_t *pNode;

    if (_Sndg_sState.m1C == 0) {
        return;
    }
    if (_Sndg_sState.m18 != 0x7FFFFFFF) {
        pNode = (SndgLoadRequest_t *)fn_801C6B4C(_Sndg_sState.m1C, 0);
        if (SndgIsBankLoaded(pNode->m0)) {
            _Sndg_sState.m18 = 0x7FFFFFFF;
            SndgLoadQueueRemove(pNode);
        }
        if (_Sndg_sState.m18 != 0x7FFFFFFF) {
            return;
        }
    }
    pNode = (SndgLoadRequest_t *)fn_801C6B4C(_Sndg_sState.m1C, 0);
    if (pNode != 0) {
        int start = 1;
        if (a && fn_800AD9B4() == 3) {
            start = 0;
        }
        if (start) {
            SndgLoadQueueStart(pNode);
        }
    }
}

extern "C" void SndgLoadQueueFlush(void)
{
    while (fn_801C6B4C(_Sndg_sState.m1C, 0) != 0) {
        SndgLoadQueueService(0);
        SndService();
    }
}

extern "C" void SndgOpenResources(SndgResource_t *pEntry)
{
    while (pEntry->m10 != 3) {
        pEntry->m8 = ResOpenDevice(pEntry->m4, 44);
        ResSetFlags(pEntry->m8, 1);
        pEntry++;
    }
}

extern "C" void SndgCloseResources(SndgResource_t *pEntry)
{
    while (pEntry->m10 != 3) {
        ResClose(pEntry->m8);
        pEntry++;
    }
}

extern "C" void SndgInit(SndgConfig_t *pInit)
{
    _Sndg_sState.m4 = pInit->m0;
    _Sndg_sState.m8 = pInit->m4;
    _Sndg_sState.mC = pInit->m8;
    _Sndg_sState.m10 = pInit->m10;
    _Sndg_sState.m14 = pInit->m14;
    _Sndg_sState.m24 = (int *)fn_801D2B7C(pInit->m0 * 4, 0, 0);
    _Sndg_sState.m28 = (int *)fn_801D2B7C(pInit->m4 * 4, 0, 0);
    MemFill(_Sndg_sState.m24, pInit->m0 * 4, 0, 4);
    MemFill(_Sndg_sState.m28, pInit->m4 * 4, 0, 4);
    SndgLoadQueueCreate();
    _Sndg_sState.m0 = 0;
    _Sndg_sState.m18 = 0x7FFFFFFF;
    _Sndg_sState.m20 = 1;
    SndgOpenResources(_Sndg_sState.m10);
    SndgLoadResources(_Sndg_sState.m10);
    _Sndg_sState.m0 = -1;
    _Sndg_iSfxRate = 0x1000;
    SndgLoadQueueFlush();
}

extern "C" void SndgLoadResources(SndgResource_t *pEntry)
{
    while (pEntry->m10 != 3) {
        switch (pEntry->m10) {
        case 0:
            if (pEntry->mC != -1) {
                if (pEntry->m18 & 2) {
                    SndgRequestBank(pEntry->m0, pEntry->mC, 0);
                } else {
                    SndgLoadBank(pEntry->m0);
                }
            }
            break;
        case 2:
            SndgLoadSequence(pEntry->m0);
            break;
        }
        pEntry++;
    }
}

extern "C" void SndgShutdown(void)
{
    int i;

    if (_Sndg_sState.m20) {
        for (i = 0; i < 20; i++) {
            fn_801CE7D0(1);
            SndService();
        }
        SndUnloadAll();
        SndgLoadQueueDestroy();
        fn_801D2BD0(_Sndg_sState.m24);
        fn_801D2BD0(_Sndg_sState.m28);
        _Sndg_sState.m24 = 0;
        _Sndg_sState.m28 = 0;
        _Sndg_sState.m20 = 0;
        SndgCloseResources(_Sndg_sState.m10);
    }
}

extern "C" void SndgLoadBank(unsigned int index)
{
    if (_Sndg_sState.m20 && index < _Sndg_sState.m4) {
        SndgResource_t *pEntry = SndgFindResource(0, index);
        _Sndg_sState.m24[index] = SndLoadBank(pEntry->m8, pEntry->mC, pEntry->m14);
    }
}

extern "C" int SndgRequestBank(unsigned int index, int a, SndgBankLoadedFn cb)
{
    SndgResource_t *pEntry;
    int *pSlot;
    int queue;
    int result;
    int canQueue;

    if (!SndEnabled() || !_Sndg_sState.m20 || index >= _Sndg_sState.m4) {
        return 0;
    }
    pEntry = SndgFindResource(0, index);
    pSlot = &_Sndg_sState.m24[index];
    queue = 0;
    result = 0;
    canQueue = ResGetSize(pEntry->m8, a) < fn_801D27F4(1);
    if (*pSlot != 0) {
        if (ResIsLoaded(pEntry->m8, a)) {
            result = 1;
            if (cb != 0) {
                cb(*pSlot);
            }
        } else if (canQueue) {
            queue = 1;
            result = 1;
        }
    } else if (canQueue) {
        result = 1;
        queue = 1;
    }
    if (queue) {
        result = SndgLoadQueueAdd(index, pEntry->m8, a, cb);
    }
    return result;
}

extern "C" int SndgIsBankIndexLoaded(int index, int a)
{
    if (SndEnabled()) {
        int *pSlot = &_Sndg_sState.m24[index];
        if (*pSlot != 0 && ResIsLoaded(SndgFindResource(0, index)->m8, a)) {
            return 1;
        }
    }
    return 0;
}

extern "C" void SndgUnloadBank(unsigned int index)
{
    if (_Sndg_sState.m20 && index < _Sndg_sState.m4) {
        SndUnloadBank(_Sndg_sState.m24[index]);
        _Sndg_sState.m24[index] = 0;
    }
}

extern "C" int SndgGetBank(unsigned int index)
{
    if (!_Sndg_sState.m20) {
        return 0;
    }
    if (index >= _Sndg_sState.m4) {
        return 0;
    }
    return _Sndg_sState.m24[index];
}

extern "C" int SndgIsBankLoaded(unsigned int index)
{
    int result;
    int handle;

    if (!_Sndg_sState.m20 || index >= _Sndg_sState.m4) {
        return 0;
    }
    result = 0;
    handle = SndgGetBank(index);
    if (handle != 0) {
        result = SndIsBankLoaded(handle);
    }
    return result;
}

extern "C" int SndgIsBankReady(unsigned int index)
{
    if (!_Sndg_sState.m20 || !SndEnabled() || !SndIsActive()) {
        return 1;
    }
    return SndgIsBankLoaded(index);
}

extern "C" int SndgSfxPlay(int index, Vector_80039F5C *pPos)
{
    int result;

    if (_Sndg_sState.m20) {
        SndgSfx_t *pEntry = &_Sndg_sState.mC[index];
        result = SndgSfxPlayVolume(index, pPos, pEntry->mC);
    } else {
        result = 0x7FFFFFFF;
    }
    return result;
}

extern "C" int SndgSfxPlayVolume(int index, Vector_80039F5C *pPos, unsigned char c)
{
    int result = 0x7FFFFFFF;
    SndgSfx_t *pEntry;
    unsigned int now;
    Info_801F40F4 params;

    if (!_Sndg_sState.m20) {
        return 0x7FFFFFFF;
    }
    pEntry = &_Sndg_sState.mC[index];
    now = fn_801F7ABC();
    if (SndPatchOver(pEntry->m14) != 0 || (unsigned int)(index - 0x72) <= 30 ||
        now - pEntry->m10 > fn_802372EC(1, 15) + 10) {
        SndFillPatchOpts(&params);
        params.mVolume = c;
        SndgChannelSetPatchOpts(pEntry->mD, pPos, &params);
        if (params.mVolume != 0 && _Sndg_sState.m24[pEntry->m4] != 0) {
            result = pEntry->m14 = SndPlayPatch(_Sndg_sState.m24[pEntry->m4], pEntry->m8, &params);
            pEntry->m10 = now;
            SndgReplayRecordSfx(index, pPos, c);
            if (_Sndg_iSfxRate != 0x1000) {
                SndSetPatchRate(result, _Sndg_iSfxRate);
            }
        }
    }
    return result;
}

extern "C" void SndgSfxStop(int index)
{
    if (_Sndg_sState.m20) {
        SndgSfx_t *pEntry = &_Sndg_sState.mC[index];
        SndStopPatch(pEntry->m14);
    }
}

extern "C" void SndgSfxSetVolume(int index, int a, unsigned char volume)
{
    SndgSfx_t *pEntry = &_Sndg_sState.mC[index];
    int value = SndgChannelScaleVolume(pEntry->mD, volume);

    if (a == 0) {
        SndSetPatchPitchMult(pEntry->m14, value);
    } else {
        SndSetPatchParam(pEntry->m14, a, value);
    }
}

extern "C" void SndgUpdate(int a)
{
    SndgUpdateFn *pHandler;

    for (pHandler = _Sndg_sState.m14; *pHandler != 0; pHandler++) {
        (*pHandler)(a);
    }
    SndgMusicUpdate();
    SndgLoadQueueService(1);
    SndService();
}

extern "C" void SndgNullHook(void)
{
}

extern "C" void SndgLoadSequence(int index)
{
    SndgResource_t *pEntry = SndgFindResource(2, index);
    _Sndg_sState.m28[index] = SndLoadSeq(pEntry->m8, pEntry->mC);
}

extern "C" void SndgCalcPan(Vector_80039F5C *a, Vector_80039F5C *b, int angle, unsigned short *pOut0, short *pOut1)
{
    Vector_80039F5C dir;
    Vector_80039F5C flat;
    Vec2 delta;
    int rot;

    fn_80227690(&delta, b, a);
    rot = (fn_801CFE40(delta.y, delta.x) - angle + 0x400000) & 0xFFFFFF;
    *pOut0 = -(((rot - 0x400000) & 0xFFFFFF) / 256);

    fn_802276B4(&dir, b, a);
    flat.mX = dir.mX;
    flat.mY = dir.mY;
    flat.mZ = 0.0f;
    rot = Vec3GetAngle(&flat, &dir);
    if (rot > 0x800000) {
        rot = 0x1000000 - rot;
    }
    if (dir.mZ < 0.0f) {
        *pOut1 = -(rot / 256);
    } else {
        *pOut1 = rot / 256;
    }
}

extern "C" unsigned char SndgIsInit(void)
{
    return _Sndg_sState.m20;
}

extern "C" int SndgSfxIsPlaying(int index)
{
    SndgSfx_t *pEntry = &_Sndg_sState.mC[index];
    return SndPatchOver(pEntry->m14) == 0;
}

extern "C" unsigned char SndgSfxGetVolume(int index)
{
    return _Sndg_sState.mC[index].mC;
}

extern "C" void SndgSetSfxRate(float value)
{
    _Sndg_iSfxRate = (int)(value * 4096.0f);
}

extern "C" void SndgHandleBallEvent(AudmonEvent_t *p)
{
    switch (p->mType) {
    case 0x1F:
        if (p->mUnknown10.mValue > 0x50000) {
            if (p->mUnknown10.mValue > 0x200000) {
                int id = 15;
                Ball_t *pBall = BallGetCurrent();
                if (pBall != 0 && pBall->mpUnknown00 != 0 && pBall->mpUnknown00->mUnknown660 != 0) {
                    id = pBall->mpUnknown00->mUnknown660->mSurface;
                }
                SndgSfxPlay(fn_80071BA0(fn_800A3444(), id), &p->mPos);
            } else {
                SndgSfxPlay(0x69, &p->mPos);
            }
        }
        break;
    case 0x20: {
        Vector_80039F5C vec;
        BallGetVelocity((Ball_t *)p->mUnknown10.mpObject, &vec);
        if (fn_802270D4(&vec) > 0.42f) {
            fn_800717E0(&p->mPos);
        }
        SndgAmbObjCreate(4, (unsigned char)p->mUnknown18, &p->mPos, p->mUnknown10.mpObject);
        break;
    }
    case 0x21:
        SndgAmbObjUpdate(4, (unsigned char)p->mUnknown18, &p->mPos, p->mUnknown10.mpObject);
        break;
    case 0x22:
        SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
        break;
    case 0x1D:
        SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
        SndgSfxPlay(4, &p->mPos);
        break;
    case 0x1C:
        SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
        SndgSfxPlay(3, &p->mPos);
        break;
    case 0x1E:
        fn_8009BCE8(&p->mUnknown0);
        if (p->mUnknown10.mValue != 0) {
            SndgSfxPlay(2, &p->mPos);
        } else {
            SndgSfxPlay(3, &p->mPos);
        }
        break;
    }
}

extern "C" void SndgHandleEvent(AudmonEvent_t *p)
{
    SndgHandleBallEvent(p);
    fn_8006F850(p);
    fn_80070C40(p);
    SndgSituationHandleEvent(p);
}

extern "C" void SndgListenerUpdate(SndgListener_t *src)
{
    if (fn_8002D060(lbl_803EA368) == 0) {
        GameCamera_t *obj = CamGameGetCamera(CamGameGetCurrentSlot());
        int angle;

        src->mOrigin.mX = obj->mHeader.mUnknown04[0];
        src->mOrigin.mY = obj->mHeader.mUnknown04[1];
        src->mOrigin.mZ = obj->mHeader.mUnknown04[2];
        if (fn_801784C4()) {
            src->mOrigin.mX = -src->mOrigin.mX;
            src->mOrigin.mY = -src->mOrigin.mY;
        }
        angle = CamGameGetHeading(CamGameGetCurrentSlot());
        if (fn_801784C4()) {
            angle = (angle + 0x800000) & 0xFFFFFF;
        }
        src->mAngle = angle;
    } else if (ReplayCursorGetPos(&src->mOrigin.mX) == 0) {
        Block_80170E64 *pBlock = BallGetModel(BallGetCurrent());

        src->mOrigin.mX = pBlock->mUnknown4.mX;
        src->mOrigin.mY = pBlock->mUnknown4.mY;
        src->mOrigin.mZ = pBlock->mUnknown4.mZ;
    }
}

extern "C" void SndgCenterPanNear(Vector_80039F5C *origin, Vector_80039F5C *pos, unsigned short *pan, short *span)
{
    Vector_80039F5C delta;
    float dist;
    short scale;

    fn_802276B4(&delta, pos, origin);
    dist = fn_802270D4(&delta);
    if (dist < 5.0f) {
        scale = (short)(dist * 51.0f);
        *span = (*span * scale) / 255;
        switch (*pan >> 14) {
        case 0:
            *pan = (*pan * scale) / 255;
            break;
        case 1:
            *pan = 0x7FFF - ((0x7FFF - *pan) * scale) / 255;
            break;
        case 2:
            *pan = ((*pan - 0x8000) * scale) / 255 + 0x8000;
            break;
        case 3:
            *pan = 0xFFFF - ((0xFFFF - *pan) * scale) / 255;
            break;
        }
    }
}

extern "C" void SndgChannelsReset(void)
{
    int i;

    for (i = 0; i < 9; i++) {
        SndgChannelDesc_t *rec = &_Sndg_aChannelDefaults[i];
        SndgChannel_t *e = &_Sndg_aChannels[i];
        Vector_80039F5C *origin = &e->mSource.mOrigin;

        e->mHandle = 0;
        e->m04 = 0;
        e->mScale = rec->mScale;
        e->m2C = rec->mScale;
        e->mSource.mUpdate = rec->mUpdate;
        e->mSource.mParams = rec->mParams;
        e->mSource.mAngle = 0x400000;
        origin->mX = origin->mY = origin->mZ = 0.0f;
        e->mPosition.mX = _Sndg_vNoPosition.mX;
        e->mPosition.mY = _Sndg_vNoPosition.mY;
        e->mPosition.mZ = _Sndg_vNoPosition.mZ;
    }
}

extern "C" void SndgChannelsCreateStreams(int withThird)
{
    int handle;

    SndgChannelsReset();

    handle = SndCreateStream(0x10000, 20, 150, 0);
    _Sndg_aChannels[4].mHandle = handle;
    SndStreamSetParam(handle, 0, 15);
    SndStreamSetControl(handle, 0x55);

    handle = SndCreateStream(0x10000, 20, 150, 0);
    _Sndg_aChannels[5].mHandle = handle;
    SndStreamSetParam(handle, 0, 15);
    SndStreamSetControl(handle, 0x55);

    if (withThird) {
        handle = SndCreateStream(0x10000, 20, 150, 0);
        _Sndg_aChannels[6].mHandle = handle;
        SndStreamSetParam(handle, 0, 15);
        SndStreamSetControl(handle, 0x55);
    } else {
        _Sndg_aChannels[6].mHandle = 0;
    }
}

extern "C" void SndgChannelsDestroyStreams(void)
{
    if (_Sndg_aChannels[6].mHandle) {
        SndDestroyStream(_Sndg_aChannels[6].mHandle);
    }
    SndDestroyStream(_Sndg_aChannels[4].mHandle);
    SndDestroyStream(_Sndg_aChannels[5].mHandle);
}

extern "C" void SndgChannelsCreateFEStream(void)
{
    _Sndg_aChannels[4].mHandle = SndCreateStream(0x10000, 20, 150, 0);
}

extern "C" void SndgChannelsDestroyFEStream(void)
{
    SndDestroyStream(_Sndg_aChannels[4].mHandle);
}

extern "C" void SndgChannelsInitFE(void)
{
    SndgChannelsReset();
    SndgChannelsCreateFEStream();
}

extern "C" void SndgChannelsShutdownFE(void)
{
    SndgChannelsDestroyFEStream();
}

extern "C" void SndgChannelsUpdate(int unknown)
{
    unsigned int i;

    for (i = 0; i < 9; i++) {
        if (i == 6 && SndgChannelGetStream(6) && SndgChannelIsStreamBusy(6) && !SndStreamGetVol(SndgChannelGetStream(6))) {
            SndPurgeStream(SndgChannelGetStream(6));
        }

        SndgListener_t *src = &_Sndg_aChannels[i].mSource;
        if (src->mParams && src->mUpdate) {
            src->mUpdate(src);
        }
    }
}

extern "C" unsigned char SndgListenerAttenuate(SndgListener_t *src, Vector_80039F5C *pos, unsigned char volume)
{
    if (src->mParams) {
        float level = volume;

        if (pos && !fn_802275D8(pos, &_Sndg_vNoPosition, 1e-7f)) {
            Vector_80039F5C delta;
            float dist;
            SndgFalloff_t *params;

            fn_802276B4(&delta, pos, &src->mOrigin);
            dist = fn_802270D4(&delta);
            params = src->mParams;
            if (dist > params->mDistance && params->mFactor > 0.0f) {
                float t = (dist + (1.0f - params->mFactor) * (params->mDistance - dist)) / params->mDistance;
                level /= t * t;
            }
            level *= src->mParams->mScalePositional;
        } else {
            level *= src->mParams->mScaleNoPos;
        }
        volume = (int)(level > 127.0f ? 127.0f : level);
    }
    return volume;
}

extern "C" void SndgChannelSetPatchOpts(int idx, Vector_80039F5C *pos, Info_801F40F4 *out)
{
    SndgChannel_t *e = &_Sndg_aChannels[idx];

    out->mVolume = (out->mVolume * e->mScale) / 255;
    out->mVolume = SndgListenerAttenuate(&e->mSource, pos, out->mVolume);
    if (pos) {
        SndgCalcPan(&e->mSource.mOrigin, pos, e->mSource.mAngle, &out->mPan, &out->mSpan);
        SndgCenterPanNear(&e->mSource.mOrigin, pos, &out->mPan, &out->mSpan);
    }
}

extern "C" unsigned char SndgChannelScaleVolume(int idx, unsigned char volume)
{
    SndgChannel_t *e = &_Sndg_aChannels[idx];

    return SndgListenerAttenuate(&e->mSource, &e->mPosition, (volume * e->mScale) / 255);
}

extern "C" int SndgChannelGetStream(int idx)
{
    return _Sndg_aChannels[idx].mHandle;
}

extern "C" void SndgChannelSetStream(int idx, int handle)
{
    _Sndg_aChannels[idx].mHandle = handle;
}

extern "C" void SndgChannelSetVolume(int idx, unsigned char percent)
{
    _Sndg_aChannels[idx].mScale = percent * 255U / 100;
    if (SndgChannelGetStream(idx)) {
        SndgChannelFadeStream(idx, 0, 127);
    }
}

extern "C" void SndgChannelFadeStream(int idx, int a, int volume)
{
    int handle = SndgChannelGetStream(idx);

    if (handle) {
        if (volume) {
            volume = SndgChannelScaleVolume(idx, volume);
        }
        SndStreamAutoVol(handle, a, volume);
    }
}

extern "C" void SndgChannelSetPosition(int idx, Vector_80039F5C *pos)
{
    SndgChannel_t *e = &_Sndg_aChannels[idx];

    if (pos) {
        e->mPosition.mX = pos->mX;
        e->mPosition.mY = pos->mY;
        e->mPosition.mZ = pos->mZ;
    } else {
        e->mPosition.mX = _Sndg_vNoPosition.mX;
        e->mPosition.mY = _Sndg_vNoPosition.mY;
        e->mPosition.mZ = _Sndg_vNoPosition.mZ;
    }
    SndgChannelUpdatePan(idx);
}

extern "C" void SndgChannelUpdatePan(int idx)
{
    SndgChannel_t *e = &_Sndg_aChannels[idx];

    if (e->mHandle) {
        unsigned short pan;
        short span;

        if (!fn_802275D8(&e->mPosition, &_Sndg_vNoPosition, 1e-7f)) {
            SndgCalcPan(&e->mSource.mOrigin, &e->mPosition, e->mSource.mAngle, &pan, &span);
            SndgCenterPanNear(&e->mSource.mOrigin, &e->mPosition, &pan, &span);
        } else {
            span = pan = 0;
        }
        SndStreamSetPan(e->mHandle, pan, 0);
    }
}

extern "C" int SndgChannelIsStreamBusy(int idx)
{
    if (SndgChannelGetStream(idx)) {
        Status_801F4834 status;

        SndStreamGetStatus(SndgChannelGetStream(idx), &status);
        if (status.mUnknown0 == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" void SndgChannelPurgeStream(int idx)
{
    if (SndgChannelGetStream(idx)) {
        SndPurgeStream(SndgChannelGetStream(idx));
    }
}

extern "C" void SndgPathCallList0(int a, int b)
{
    SndgPathCallback_t *entry;

    for (entry = (SndgPathCallback_t *)fn_801C6B4C(_SndgPathfinder_pState->mpPool[0], 0); entry;
         entry = (SndgPathCallback_t *)fn_801C6C84(_SndgPathfinder_pState->mpPool[0], entry)) {
        entry->mFunc(a, b);
    }
}

extern "C" void SndgPathCallList1(int a, int b)
{
    SndgPathCallback_t *entry;

    for (entry = (SndgPathCallback_t *)fn_801C6B4C(_SndgPathfinder_pState->mpPool[1], 0); entry;
         entry = (SndgPathCallback_t *)fn_801C6C84(_SndgPathfinder_pState->mpPool[1], entry)) {
        entry->mFunc(a, b);
    }
}

extern "C" void SndgPathCallList2(int a, int b)
{
    SndgPathCallback_t *entry;

    for (entry = (SndgPathCallback_t *)fn_801C6B4C(_SndgPathfinder_pState->mpPool[2], 0); entry;
         entry = (SndgPathCallback_t *)fn_801C6C84(_SndgPathfinder_pState->mpPool[2], entry)) {
        entry->mFunc(a, b);
    }
}

extern "C" int SndgPathMatchCallback(SndgPathCallbackKey_t *pItem, int key, SndgPathCallbackKey_t **ppResult)
{
    if (pItem->mKey == key) {
        *ppResult = pItem;
        return 0;
    }
    return -1;
}

ModuleDependency *SndgPathfinder::GetDependencies() { return sDependencies; }
ModuleDependency *SndgPathfinder::GetLinks() { return (ModuleDependency *)sLinks; }
const char *SndgPathfinder::GetName() { return "SndgPathfinder"; }

int SndgPathfinder::Init()
{
    _SndgPathfinder_pState = new (0) SndgPathfinderState;
    memset(_SndgPathfinder_pState, 0, sizeof(SndgPathfinderState));
    _SndgPathfinder_pState->mpPool[0] = fn_801C68FC(1, 0, 4, 4, 0, 0);
    _SndgPathfinder_pState->mpPool[1] = fn_801C68FC(1, 0, 4, 4, 0, 0);
    _SndgPathfinder_pState->mpPool[2] = fn_801C68FC(1, 0, 4, 4, 0, 0);
    if (SndEnabled()) {
        PathfinderInitDesc_t desc;
        desc.mHeap = 1;
        desc.mCount = 3;
        PathfinderInit(&desc);
        fn_801B2F18(SndgPathCallList0, SndgPathCallList1, SndgPathCallList2);
    }
    return 1;
}

int SndgPathfinder::Shutdown()
{
    if (SndEnabled()) {
        PathfinderShutdown();
    }
    fn_801C69E4(_SndgPathfinder_pState->mpPool[0]);
    fn_801C69E4(_SndgPathfinder_pState->mpPool[1]);
    fn_801C69E4(_SndgPathfinder_pState->mpPool[2]);
    delete _SndgPathfinder_pState;
    _SndgPathfinder_pState = 0;
    return 1;
}

extern "C" int SndgPathLoadMap(void *pData, int unknown)
{
    int result = -1;
    if (PathfinderIsInit()) {
        result = PathfinderLoadMap(pData, unknown, 1);
    }
    return result;
}

extern "C" int SndgPathUnloadMap(int handle)
{
    int result = 0;
    if (PathfinderIsInit()) {
        result = PathfinderUnloadMap(handle) >= 0;
    }
    return result;
}

extern "C" int SndgPathCreateTrack(void *pData, int unknown, int id, float value)
{
    int result = 0;
    if (PathfinderIsInit()) {
        PathfinderTrackDesc_t desc;
        desc.mUnknown24 = 0;
        desc.mUnknown10 = 0;
        desc.mUnknown14.mUnknown8 = 0;
        desc.mUnknown14.mpData = pData;
        desc.mUnknown14.mUnknown4 = unknown;
        desc.mId = id;
        desc.mUnknown0C = value;
        desc.mUnknown04 = 1000;
        desc.mUnknown08 = 2;
        result = PathfinderCreateTrack(&desc) >= 0;
    }
    return result;
}

extern "C" int SndgPathDestroyTrack(int id)
{
    int result = 0;
    if (PathfinderIsInit()) {
        result = PathfinderDestroyTrack(id) >= 0;
    }
    return result;
}

extern "C" void SndgPathSetTrackVolume(int id, unsigned int value)
{
    if (PathfinderIsInit()) {
        PathfinderSetVolume(id, value);
    }
}

extern "C" void SndgPathFadeTrack(int a, int b, int c)
{
    if (PathfinderIsInit()) {
        PathfinderFade(a, b, c);
    }
}

extern "C" int SndgPathPostEvent(int id, int unknown)
{
    int result = 1;
    if (PathfinderIsInit()) {
        result = PathfinderEvent(id, unknown) >= 0;
    }
    return result;
}

extern "C" int SndgPathControl(int id, int unknown)
{
    int result = 1;
    if (PathfinderIsInit()) {
        result = PathfinderControl(id, unknown) >= 0;
    }
    return result;
}

extern "C" void SndgPathSetStreamValue(int a, int b)
{
    if (PathfinderIsInit()) {
        PathfinderSetStreamValue(a, b);
    }
}

extern "C" void SndgPathPauseTrack(int a)
{
    if (PathfinderIsInit()) {
        PathfinderPause(a, 1);
    }
}

extern "C" void SndgPathResumeTrack(int a)
{
    if (PathfinderIsInit()) {
        PathfinderPause(a, 0);
    }
}

extern "C" void SndgPathStopTrack(int a)
{
    if (PathfinderIsInit()) {
        PathfinderStop(a);
    }
}

extern "C" void SndgPathAddCallback(int value)
{
    if (gSndgPathfinder.IsStarted()) {
        SndgPathCallbackKey_t *pItem = (SndgPathCallbackKey_t *)fn_801C6A20(_SndgPathfinder_pState->mpPool[0]);
        if (pItem) {
            pItem->mKey = value;
            fn_801C6AA4(_SndgPathfinder_pState->mpPool[0], pItem, 0);
        }
    }
}

extern "C" void SndgPathRemoveCallback(int value)
{
    if (gSndgPathfinder.IsStarted()) {
        SndgPathCallbackKey_t *pFound = 0;
        fn_801C6DCC(_SndgPathfinder_pState->mpPool[0], 0, value, &pFound, SndgPathMatchCallback);
        if (pFound) {
            fn_801C6C0C(_SndgPathfinder_pState->mpPool[0], pFound);
        }
    }
}

extern "C" void SndgSituationReset(void)
{
    _SndgSituation_pState->mUnknown34 = PlayBookGetPlay(fn_80178308())->mUnknown17;
    _SndgSituation_pState->mUnknown30 = 0;
    _SndgSituation_pState->mFlags = 0;
    _SndgSituation_pState->mUnknown24.mX = 0.0f;
    _SndgSituation_pState->mUnknown24.mY = 0.0f;
}

extern "C" void UpdateGameSituation(void)
{
    Vec2 spot = fn_80177FE0();
    Point_8017886C prevSpot = fn_80178070();
    int home;
    int away;

    _SndgSituation_pState->mUnknownF = _SndgSituation_pState->mUnknownE;
    _SndgSituation_pState->mUnknownE = fn_80178308();
    _SndgSituation_pState->mUnknown4 = _SndgSituation_pState->mUnknown0;
    _SndgSituation_pState->mUnknown6 = _SndgSituation_pState->mUnknown2;
    GetScores(&home, &away);
    _SndgSituation_pState->mUnknown0 = home;
    _SndgSituation_pState->mUnknown2 = away;
    if (_SndgSituation_pState->mUnknownE == 0) {
        _SndgSituation_pState->mUnknown8 = _SndgSituation_pState->mUnknown0 - _SndgSituation_pState->mUnknown2;
    } else {
        _SndgSituation_pState->mUnknown8 = _SndgSituation_pState->mUnknown2 - _SndgSituation_pState->mUnknown0;
    }
    _SndgSituation_pState->mUnknown11 = (char)prevSpot.mY;
    _SndgSituation_pState->mUnknown10 = (char)spot.y;
    _SndgSituation_pState->mUnknown12 = _SndgSituation_pState->mUnknown10 - _SndgSituation_pState->mUnknown11;
    _SndgSituation_pState->mUnknown15 = _SndgSituation_pState->mUnknown14;
    _SndgSituation_pState->mUnknown14 = fn_80177F70();
    _SndgSituation_pState->mUnknown13 = (char)(fn_80178298() - spot.y + 0.001f);
}

extern "C" void SndgSituationUpdate(int unknown)
{
    unsigned char value;

    _SndgSituation_pState->mUnknownA = fn_8009D990(1);
    _SndgSituation_pState->mUnknownD = fn_8009D86C();
    value = fn_8009D990(0);
    if (value != _SndgSituation_pState->mUnknownC) {
        _SndgSituation_pState->mUnknownC = value;
    }
}

extern "C" void SndgSituationSetFlags(int flags)
{
    _SndgSituation_pState->mFlags |= flags;
}

extern "C" void SndgSituationHandleEvent(AudmonEvent_t *pEvent)
{
    switch (pEvent->mType) {
    case 0x1F:
        BallGetPosition(BallGetCurrent(), &_SndgSituation_pState->mUnknown24);
        break;
    case 0x8E:
        _SndgSituation_pState->mFlags |= 1;
        break;
    case 0x8F:
        _SndgSituation_pState->mUnknown1C = pEvent->mPos.mX;
        _SndgSituation_pState->mUnknown20 = pEvent->mPos.mY;
        break;
    case 0x8C: {
        Vec2 v;
        v = fn_80177FE0();
        _SndgSituation_pState->mUnknown1C = v.x;
        _SndgSituation_pState->mUnknown20 = v.y;
        _SndgSituation_pState->mFlags = 0;
        break;
    }
    case 0x92:
    case 0x95:
    case 0x97:
        _SndgSituation_pState->mFlags |= 2;
        break;
    case 0xA2:
        _SndgSituation_pState->mFlags |= 0x10;
        break;
    }
}

extern "C" int SndgReplayFindFreeSlot(void)
{
    unsigned int i;

    if (lbl_803EA368->mUnknownD94 & 0x10000) {
        return 0;
    }
    for (i = 0; i < 128; i++) {
        if (_SndgReplay_aHandles[i] == -1) {
            return i;
        }
    }
    return 0;
}

extern "C" void SndgReplayStopAll(void)
{
    unsigned int i;

    for (i = 0; i < 128; i++) {
        if (_SndgReplay_aHandles[i] != -1) {
            SndStopPatch(_SndgReplay_aHandles[i]);
            _SndgReplay_aHandles[i] = -1;
        }
    }
}

extern "C" void SndgReplayPlayEntry(SndgReplaySfx_t *pEntry)
{
    int slot = SndgReplayFindFreeSlot();

    if (pEntry->mFlags & 1) {
        _SndgReplay_aHandles[slot] = SndgSfxPlayVolume(pEntry->mId, 0, pEntry->mUnknown12);
    } else {
        _SndgReplay_aHandles[slot] = SndgSfxPlayVolume(pEntry->mId, &pEntry->mPos, pEntry->mUnknown12);
    }
}

extern "C" void SndgReplayWriteEntry(SndgReplaySfx_t *pEntry, void *pStream)
{
    fn_80191068(pStream, pEntry->mId, 8);
    fn_80030490(pStream, &pEntry->mPos.mX, 8, 1.0f);
    fn_80191068(pStream, pEntry->mUnknown12, 8);
    fn_80191068(pStream, pEntry->mFlags, 1);
}

extern "C" void SndgReplayReadEntry(SndgReplaySfx_t *pEntry, void *pStream0, void *pStream1, void *pStream2,
                            void *pStream3, float unknown)
{
    float pos[2];
    Vector_80039F5C *pPos;

    pEntry->mId = fn_80190F18(pStream1, 8);
    pPos = &pEntry->mPos;
    pPos->mX = pPos->mY = pPos->mZ = 0.0f;
    fn_800300D4(pStream1, &pPos->mX, 8, 1.0f);
    pEntry->mUnknown12 = fn_80190F18(pStream1, 8);
    pEntry->mFlags = (unsigned char)fn_80190F18(pStream1, 1);

    fn_80190F18(pStream0, 8);
    fn_800300D4(pStream0, pos, 8, 1.0f);
    fn_80190F18(pStream0, 8);
    fn_80190F18(pStream0, 1);
    if (pStream2) {
        fn_80190F18(pStream2, 8);
        fn_800300D4(pStream2, pos, 8, 1.0f);
        fn_80190F18(pStream2, 8);
        fn_80190F18(pStream2, 1);
    }
    if (pStream3) {
        fn_80190F18(pStream3, 8);
        fn_800300D4(pStream3, pos, 8, 1.0f);
        fn_80190F18(pStream3, 8);
        fn_80190F18(pStream3, 1);
    }
}

extern "C" void SndgReplayWriteFrame(void *pStream)
{
    unsigned int i;

    fn_80191068(pStream, _SndgReplay_pQueue->mCount, 4);
    for (i = 0; i < 12; i++) {
        SndgReplayWriteEntry(&_SndgReplay_pQueue->mEntries[i], pStream);
    }
    SndgReplayClearQueue(_SndgReplay_pQueue);
}

extern "C" void SndgReplayReadFrame(void *pStream0, void *pStream1, void *pStream2, void *pStream3, float unknown)
{
    unsigned int count;
    unsigned int i;
    int frames;
    int half;
    int parity;
    SndgReplaySfx_t entry;

    count = (unsigned char)fn_80190F18(pStream1, 4);
    fn_80190F18(pStream0, 4);
    if (pStream2) {
        fn_80190F18(pStream2, 4);
    }
    if (pStream3) {
        fn_80190F18(pStream3, 4);
    }
    frames = lbl_803EA368->mUnknownD74 - lbl_803EA368->mUnknownD70;
    half = frames / 2;
    parity = frames % 2;
    for (i = 0; i < 12; i++) {
        SndgReplayReadEntry(&entry, pStream0, pStream1, pStream2, pStream3, unknown);
        if ((parity != _SndgReplay_iLastFrameParity || half != _SndgReplay_iLastHalfFrame) && i < count && fn_8002D060(lbl_803EA368)) {
            SndgReplayPlayEntry(&entry);
        }
    }
    _SndgReplay_iLastHalfFrame = half;
    _SndgReplay_iLastFrameParity = parity;
}

extern "C" void SndgReplayClearQueue(SndgReplayQueue_t *pList)
{
    if (pList) {
        memset(pList, 0, sizeof(pList->mEntries));
        pList->mCount = 0;
    }
}

extern "C" void SndgReplayInit(void)
{
    static SndgReplayQueue_t sQueue;
    unsigned int i;

    _SndgReplay_pQueue = &sQueue;
    for (i = 0; i < 128; i++) {
        _SndgReplay_aHandles[i] = -1;
    }
    SndgReplayClearQueue(_SndgReplay_pQueue);
}

extern "C" void SndgReplayShutdown(void)
{
    SndgReplayClearQueue(_SndgReplay_pQueue);
    _SndgReplay_pQueue = 0;
}

extern "C" void SndgReplayRegister(void)
{
    fn_80030ACC(SndgReplayWriteFrame, SndgReplayReadFrame, SndgReplayGetFrameSize(), "Sounds");
}

extern "C" int SndgReplayGetFrameSize(void)
{
    return 400;
}

extern "C" void SndgReplayQueueEntry(SndgReplaySfx_t *pEntry)
{
    if (fn_8002D0AC(lbl_803EA368) && _SndgReplay_pQueue->mCount < 12) {
        _SndgReplay_pQueue->mEntries[_SndgReplay_pQueue->mCount] = *pEntry;
        if (fn_801784C4()) {
            _SndgReplay_pQueue->mEntries[_SndgReplay_pQueue->mCount].mPos.mX = -_SndgReplay_pQueue->mEntries[_SndgReplay_pQueue->mCount].mPos.mX;
            _SndgReplay_pQueue->mEntries[_SndgReplay_pQueue->mCount].mPos.mY = -_SndgReplay_pQueue->mEntries[_SndgReplay_pQueue->mCount].mPos.mY;
        }
        _SndgReplay_pQueue->mCount++;
    }
}

extern "C" void SndgReplayRecordSfx(int id, Vector_80039F5C *pPos, unsigned char unknown)
{
    SndgReplaySfx_t entry;

    if (id == 5 || id == 0x3E || (id >= 0x72 && id <= 0x90)) {
        return;
    }
    entry.mId = id;
    entry.mUnknown12 = unknown;
    entry.mFlags = 0;
    if (pPos) {
        entry.mPos.mX = pPos->mX;
        entry.mPos.mY = pPos->mY;
        entry.mPos.mZ = pPos->mZ;
    } else {
        entry.mFlags = 1;
    }
    SndgReplayQueueEntry(&entry);
}

extern "C" void SndgReplayReset(void)
{
    _SndgReplay_iLastHalfFrame = -1;
}

extern "C" void SndgReplayUpdate(int unknown)
{
    Type_803EA368 *p = lbl_803EA368;
    int rate;
    unsigned int i;

    if (!fn_8002D060(p)) {
        SndgReplayStopAll();
        return;
    }
    if (p->mUnknownD94 & 0x10000) {
        return;
    }
    rate = abs(p->mUnknownD88);
    if (rate != 0) {
        if (rate < 10) {
            rate = 10;
        }
        rate *= 4096;
        rate /= 60;
    }
    for (i = 0; i < 128; i++) {
        if (_SndgReplay_aHandles[i] != -1) {
            if (SndPatchOver(_SndgReplay_aHandles[i])) {
                _SndgReplay_aHandles[i] = -1;
            } else {
                SndSetPatchRate(_SndgReplay_aHandles[i], rate);
            }
        }
    }
}

extern "C" void SndgSetVolumeOption(unsigned int index, unsigned int value)
{
    switch (index) {
    case 0:
        SndSetOutputMode(value ? 2 : 1, 0);
        break;
    case 1:
        if (value > 100) {
            value = 100;
        }
        value = value > 50 ? (value - 50) * (100 - _Sndg_aVolumeCurveMid[index]) / 50 + _Sndg_aVolumeCurveMid[index]
                           : value * _Sndg_aVolumeCurveMid[index] / 50;
        SndgChannelSetVolume(0, value);
        SndgChannelSetVolume(1, value);
        SndgAmbSetVolume(value * 99 / 100);
        SndgCrowdSetVolume(value * 83 / 100);
        break;
    case 2:
        if (value > 100) {
            value = 100;
        }
        value = value > 50 ? (value - 50) * (100 - _Sndg_aVolumeCurveMid[index]) / 50 + _Sndg_aVolumeCurveMid[index]
                           : value * _Sndg_aVolumeCurveMid[index] / 50;
        value = value * 75 / 100;
        SndgMusicSetVolume(value);
        SndgChannelSetVolume(8, value);
        break;
    case 3:
        if (value > 100) {
            value = 100;
        }
        value = value > 50 ? (value - 50) * (100 - _Sndg_aVolumeCurveMid[index]) / 50 + _Sndg_aVolumeCurveMid[index]
                           : value * _Sndg_aVolumeCurveMid[index] / 50;
        value = value * 95 / 100;
        SndgChannelSetVolume(4, value);
        SndgChannelSetVolume(5, value);
        break;
    }
}

extern "C" void SndgApplyVolumeOptions(void)
{
    unsigned int values[4];
    unsigned int i;

    values[0] = GameOptionsGet(11);
    values[1] = (unsigned char)(GameOptionsGet(4) * 10);
    values[2] = (unsigned char)(GameOptionsGet(5) * 10);
    values[3] = (unsigned char)(GameOptionsGet(3) * 10);
    for (i = 0; i < 4; i++) {
        SndgSetVolumeOption(i, values[i]);
    }
}

extern "C" void SndgSpchHandleEvent(AudmonEvent_t *pEvent)
{
    if (!fn_800BA6F8() && SpchIGIsEnabled()) {
        if (GameModeTypeGet() == 11 && TutorialGetLesson() <= 4) {
            switch (pEvent->mType) {
            case 0x85:
                SpchIGSayTutorialIntro(pEvent->mUnknown10.mValue, pEvent->mUnknown14);
                break;
            case 0x86:
                SpchIGSayTutorialPassed();
                break;
            case 0x88:
                SpchIGSayTutorialAdvance();
                break;
            case 0x87:
                SpchIGSayTutorialFailed();
                break;
            case 0x80:
                SpchIGSaySceneLine(pEvent->mUnknown10.mValue, pEvent->mUnknown0, pEvent->mUnknown18);
                break;
            case 0x81:
                SpchIGStopSceneLine();
                break;
            case 0x82:
                SpchIGEndSceneLine();
                break;
            }
        } else {
            if (SpchIGIsCommentaryOn()) {
                switch (pEvent->mType) {
                case 0x73:
                    _SndgSpch_bOffenseMotionSaid = 0;
                    _SndgSpch_bDefenseShiftSaid = 0;
                    SpchIGSayDownAndDistance();
                    break;
                case 0x75:
                    SpchIGSayPreSnap(fn_80178348());
                    break;
                case 0x78:
                    if (!_SndgSpch_bDefenseShiftSaid) {
                        SpchIGSayDefenseShift();
                        _SndgSpch_bDefenseShiftSaid = 1;
                    }
                    break;
                case 0x77:
                    if (!_SndgSpch_bOffenseMotionSaid) {
                        SpchIGSayOffenseMotion();
                        _SndgSpch_bOffenseMotionSaid = 1;
                    }
                    break;
                case 0x2A: {
                    unsigned char kind = fn_8009BCE8(&pEvent->mUnknown0)->mpState->mId;
                    if (kind != 0x3A && kind != 0x10 && !(SndgSpchGetPlayFlags() & 8)) {
                        SpchIGSetDownedCarrier(pEvent->mUnknown0);
                        SndgSpchSetPlayFlags(0x40);
                    }
                    break;
                }
                case 0x68:
                    SpchIGSayFumble();
                    break;
                case 0x62:
                    SpchIGSetReceiverOpenPlayer(pEvent->mUnknown0);
                    SpchIGSayReceiverOpen();
                    break;
                case 0x27:
                    SpchIGSetStylingPlayer(pEvent->mUnknown0);
                    SpchIGSayStyling();
                    break;
                case 0x2D:
                    SpchIGSetWallTacklePlayer(pEvent->mUnknown0);
                    SpchIGSayWallTackle();
                    break;
                case 0x36:
                    SpchIGSayCatch(pEvent->mUnknown0);
                    break;
                case 0x37:
                    SpchIGSayInterception(pEvent->mUnknown0);
                    break;
                case 0x38:
                    SpchIGSayWallHurdle(pEvent->mUnknown0);
                    break;
                case 0x39:
                    SpchIGSayStiffArm(pEvent->mUnknown0);
                    break;
                case 0x3A:
                    SpchIGSayJukeSpin(pEvent->mUnknown0);
                    break;
                case 0x3B:
                    SpchIGSayWallHurdleMiss(pEvent->mUnknown0);
                    break;
                case 0x3C:
                    SpchIGSayPassThrown(pEvent->mUnknown0);
                    break;
                case 0x3D:
                    SpchIGSayBallStrip(pEvent->mUnknown0);
                    break;
                case 0x61:
                    if (pEvent->mUnknown10.mValue == 0x22) {
                        SpchIGSayJukeSpin(pEvent->mUnknown0);
                    } else if (pEvent->mUnknown10.mValue == 0x23) {
                        SpchIGSayJukeSpin(pEvent->mUnknown0);
                    } else if (pEvent->mUnknown10.mValue == 0x2B) {
                        SpchIGSayStiffArm(pEvent->mUnknown0);
                    }
                    break;
                case 0x2F:
                    SpchIGSetMissedCatchPlayer(pEvent->mUnknown0);
                    SpchIGSayMissedCatch(&pEvent->mPos);
                    break;
                case 0x65:
                    SpchIGSetStruggleCarrier(pEvent->mUnknown10.mValue);
                    SpchIGSetStruggleTackler(pEvent->mUnknown14);
                    if (fn_802372EC(1, 2)) {
                        SpchIGSayStruggleCarrier();
                    } else {
                        SpchIGSayStruggleTackler();
                    }
                    break;
                case 0x5F:
                    SpchIGSetScorer(pEvent->mUnknown0);
                    break;
                case 0x7C:
                    SpchIGSayPlayResult();
                    break;
                }
            }
            switch (pEvent->mType) {
            case 0x80:
                SpchIGSaySceneLine(pEvent->mUnknown10.mValue, pEvent->mUnknown0, pEvent->mUnknown18);
                break;
            case 0x81:
                SpchIGStopSceneLine();
                break;
            case 0x82:
                SpchIGEndSceneLine();
                break;
            case 0x6B:
                SpchIGSayTeamSceneLine(pEvent->mUnknown10.mValue, pEvent->mUnknown0, pEvent->mUnknown18, pEvent->mUnknown14);
                break;
            case 0x6C:
                SpchIGStopTeamSceneLine(pEvent->mUnknown10.mValue);
                break;
            case 0x6D:
                SpchIGEndTeamSceneLine(pEvent->mUnknown10.mValue);
                break;
            }
        }
    }
    if (pEvent->mType == 0x84) {
        SpchIGPurgeChannel(0);
        SpchIGPurgeChannel(1);
        SpchIGPurgeChannel(2);
    }
}

extern "C" void SndgSpchSetPlayFlags(int flags)
{
    _SndgSpch_iPlayFlags |= flags;
}

extern "C" void SndgSpchClearPlayFlags(int flags)
{
    _SndgSpch_iPlayFlags &= ~flags;
}

extern "C" int SndgSpchGetPlayFlags(void)
{
    return _SndgSpch_iPlayFlags;
}

