/* Engine side of the interactive music (Pathfinder): starts and stops the music runtime with
   its memory allocator, loads music maps and creates, controls and queries music tracks for
   the game's SndgPathfinder module. */

#include "engine/dslist.h"
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "engine/Resource.h"
#include "engine/sound.h"
#include "engine/pathfinder.h"
#include "engine/IAllocator.h"

extern "C" {
#include "engine/list.h"
}

/* Item of the first pool of _Pathfinder_State (0x10 bytes), keyed by a generated handle;
   holds the ResLoad arguments. */
struct PathfinderMap_t {
    int mHandle;
    void *mpData;
    int mUnknown8;
    int mUnknownC;
};

/* Item of the second pool of _Pathfinder_State (0xC bytes), keyed by a caller id. */
struct PathfinderTrack_t {
    int mId;
    void *mpUnknown4;
    unsigned char mUnknown8;
};

struct PathfinderState_t {
    DSList_t *mpPool0;
    int mHandle;
    DSList_t *mpPool8;
};

struct TagValuePair {
    TagValuePair() : mUnknown0(0), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
PathfinderState_t _Pathfinder_State;
TiburonIAllocator13Impl *_Pathfinder_pAllocator = 0;
unsigned char _Pathfinder_bInit = 0;

void PATH_setallocator(TiburonIAllocator13Impl *pAllocator, TagValuePair *pConfig);
int PATH_shutdown(void);
int PATH_addmapfile(int a);
int PATH_destroy(int id);
int PATH_createstreamtrack(int id, PathfinderTrackData_t *pData, int a);
void *PATH_createstreamimp(int id, int a, float b);
int PATH_createbanktrack(int id, PathfinderTrackData_t *pData, int a);
void *PATH_createbankobject(int id);
void PATH_volume(int id, signed char value);
void PATH_fade(int a, int b, int c, int d);
int PATH_control(int id, int a);
void PATH_pause(int a, unsigned char b);
int PATH_status(int id, PathfinderStatus_t *pInfo);
void PATH_stop(int a);
int PATH_event(int id, int a);
void *PATHI_gettrackimp(int flags);
void fn_8027D3AC(void);
void fn_8027ECD8(void *p, int b);
extern "C++" void PATH_vectortoreal5(void);

static int _PathfinderMatchMap(void *p, void *key, void *result)
{
    PathfinderMap_t *pItem = (PathfinderMap_t *)p;
    int handle = (int)key;
    PathfinderMap_t **ppFound = (PathfinderMap_t **)result;
    if (pItem->mHandle == handle) {
        *ppFound = pItem;
        return 0;
    }
    return -1;
}

static int _PathfinderMatchTrack(void *p, void *key, void *result)
{
    PathfinderTrack_t *pItem = (PathfinderTrack_t *)p;
    int id = (int)key;
    PathfinderTrack_t **ppFound = (PathfinderTrack_t **)result;
    if (pItem->mId == id) {
        *ppFound = pItem;
        return 0;
    }
    return -1;
}

static int _PathfinderNewMapHandle(void)
{
    int handle = _Pathfinder_State.mHandle;
    PathfinderMap_t *pFound;

    do {
        _Pathfinder_State.mHandle++;
        pFound = 0;
        DSSearchList(_Pathfinder_State.mpPool0, 0, (void *)_Pathfinder_State.mHandle, &pFound,
                    _PathfinderMatchMap);
    } while (pFound || _Pathfinder_State.mHandle == -1);
    return handle;
}

int PathfinderIsInit(void)
{
    return _Pathfinder_bInit;
}

int PathfinderInit(PathfinderInitDesc_t *pDesc)
{
    _Pathfinder_pAllocator = new TiburonIAllocator13Impl(pDesc->mHeap);
    TagValuePair config;
    PATH_setallocator(_Pathfinder_pAllocator, &config);
    PATH_vectortoreal5();
    fn_8027D3AC();
    memset(&_Pathfinder_State, 0, sizeof(_Pathfinder_State));
    _Pathfinder_State.mpPool0 = (DSList_t *)DSNewList(pDesc->mHeap, 0, 4, sizeof(PathfinderMap_t), 0, 0);
    _Pathfinder_State.mpPool8 = (DSList_t *)DSNewList(pDesc->mHeap, 0, pDesc->mCount, sizeof(PathfinderTrack_t), 0, 0);
    if (_Pathfinder_State.mpPool0 && _Pathfinder_State.mpPool8) {
        _Pathfinder_bInit = 1;
    }
    return -1;
}

void PathfinderShutdown(void)
{
    PathfinderMap_t *pItem;

    PATH_destroy(-1);
    if (_Pathfinder_State.mpPool8) {
        DSDelList(_Pathfinder_State.mpPool8);
    }
    if (_Pathfinder_State.mpPool0) {
        pItem = (PathfinderMap_t *)DSGetListNode(_Pathfinder_State.mpPool0, 0);
        while (pItem) {
            ResUnLoad((ResFile_t *)pItem->mpData, pItem->mUnknown8);
            pItem = (PathfinderMap_t *)DSNextListNode(_Pathfinder_State.mpPool0, pItem);
        }
        DSDelList(_Pathfinder_State.mpPool0);
    }
    PATH_shutdown();
    if (_Pathfinder_pAllocator) {
        delete _Pathfinder_pAllocator;
    }
    _Pathfinder_pAllocator = 0;
    _Pathfinder_bInit = 0;
}

int PathfinderLoadMap(void *pData, int a, int b)
{
    PathfinderMap_t *pItem;
    int id;
    int handle = -1;

    if (_Pathfinder_bInit) {
        pItem = (PathfinderMap_t *)DSNewListNode(_Pathfinder_State.mpPool0);
        if (pItem) {
            id = ResLoad((ResFile_t *)pData, a, b);
            if (id) {
                if (PATH_addmapfile(id) >= 0) {
                    pItem->mHandle = _PathfinderNewMapHandle();
                    pItem->mUnknownC = b;
                    pItem->mpData = pData;
                    pItem->mUnknown8 = a;
                    handle = pItem->mHandle;
                    DSAddListNode(_Pathfinder_State.mpPool0, pItem, 0);
                } else {
                    ResUnLoad((ResFile_t *)pData, a);
                    DSDelListNode(_Pathfinder_State.mpPool0, pItem);
                }
            }
        }
    }
    return handle;
}

int PathfinderUnloadMap(int handle)
{
    PathfinderMap_t *pItem;
    int result = -1;

    if (_Pathfinder_bInit) {
        pItem = 0;
        DSSearchList(_Pathfinder_State.mpPool0, 0, (void *)handle, &pItem,
                    _PathfinderMatchMap);
        if (pItem) {
            result = 0;
            ResUnLoad((ResFile_t *)pItem->mpData, pItem->mUnknown8);
            DSDelListNode(_Pathfinder_State.mpPool0, pItem);
        }
    }
    return result;
}

int PathfinderCreateTrack(PathfinderTrackDesc_t *pDesc)
{
    PathfinderTrack_t *pItem;
    int result = 0;

    pItem = (PathfinderTrack_t *)DSNewListNode(_Pathfinder_State.mpPool8);
    if (pItem) {
        memset(pItem, 0, sizeof(PathfinderTrack_t));
        pItem->mUnknown8 = pDesc->mUnknown24;
        SndSetHeap((SndBankHeap_t *)SndGetBankTable(), pDesc->mUnknown10);
        if (pDesc->mUnknown24) {
            result = PATH_createbanktrack(pDesc->mId, &pDesc->mUnknown14, pDesc->mUnknown20);
            if (result >= 0) {
                pItem->mpUnknown4 = PATH_createbankobject(pDesc->mId);
                if (!pItem->mpUnknown4) {
                    result = -1;
                }
            }
        } else {
            result = PATH_createstreamtrack(pDesc->mId, &pDesc->mUnknown14, pDesc->mUnknown04);
            if (result >= 0) {
                pItem->mpUnknown4 = PATH_createstreamimp(pDesc->mId, pDesc->mUnknown08, pDesc->mUnknown0C);
                if (!pItem->mpUnknown4) {
                    result = -1;
                }
            }
        }
        if (result >= 0) {
            pItem->mId = pDesc->mId;
            DSAddListNode(_Pathfinder_State.mpPool8, pItem, 0);
        } else {
            DSDelListNode(_Pathfinder_State.mpPool8, pItem);
        }
    }
    return result;
}

int PathfinderDestroyTrack(int id)
{
    PathfinderTrack_t *pItem = 0;
    int result = -1;

    DSSearchList(_Pathfinder_State.mpPool8, 0, (void *)id, &pItem, _PathfinderMatchTrack);
    if (pItem) {
        DSDelListNode(_Pathfinder_State.mpPool8, pItem);
        if (PATH_destroy(id)) {
            result = 0;
        }
    }
    return result;
}

int PathfinderControl(int id, int a)
{
    return PATH_control(id, a);
}

int PathfinderEvent(int id, int a)
{
    return PATH_event(id, a);
}

void PathfinderSetVolume(int id, int value)
{
    PATH_volume(id, value);
}

void PathfinderFade(int a, int b, int c)
{
    PATH_fade(a, b, c, 1);
}

void PathfinderPause(int a, int b)
{
    PATH_pause(a, b);
}

void PathfinderStop(int a)
{
    PATH_stop(a);
}

void PathfinderSetStreamValue(int a, int b)
{
    void *p = PATHI_gettrackimp(a);

    if (p) {
        fn_8027ECD8(p, b);
    }
}

int PathfinderGetStatus(int id, PathfinderStatus_t *pInfo)
{
    int result = -1;

    if (_Pathfinder_bInit) {
        result = PATH_status(id, pInfo);
    }
    return result;
}
}
