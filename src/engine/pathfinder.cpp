/* Engine side of the interactive music (Pathfinder): starts and stops the music runtime with
   its memory allocator, loads music maps and creates, controls and queries music tracks for
   the game's SndgPathfinder module. */

#include "game/fn_801C68FC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "engine/Resource.h"
#include "engine/sound.h"
#include "engine/pathfinder.h"
#include "engine/fn_801B3234.h"

extern "C" {
#include "engine/list.h"
}

/* Item of the first pool of _Pathfinder_State (0x10 bytes), keyed by a generated handle;
   holds the fn_801EF390 arguments. */
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
    List_801C68FC *mpPool0;
    int mHandle;
    List_801C68FC *mpPool8;
};

struct TagValuePair {
    TagValuePair() : mUnknown0(0), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

/* Abstract allocator interface handed to fn_801B2C18. */
class IAllocator {
public:
    virtual void *Alloc(unsigned int size) = 0;
    virtual void Free(void *p) = 0;
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~IAllocator() {}
};

/* Allocator on an engine heap, with an optional lock callback. */
class TiburonIAllocator13Impl : public IAllocator {
public:
    TiburonIAllocator13Impl(int heap) : mHeap(heap), mpLock(0) {}
    virtual void *Alloc(unsigned int size)
    {
        void *p;

        if (mpLock) {
            mpLock(1);
        }
        p = fn_801D2BB0(mHeap, size, 0, 0);
        if (mpLock) {
            mpLock(0);
        }
        return p;
    }
    virtual void Free(void *p) { fn_801D2BD0(p); }
    virtual int AddRef() { return 0; }
    virtual int Release() { return 0; }

    void *operator new(unsigned int size) { return fn_801D2BB0(1, size, 0, 0); }
    void operator delete(void *p) { fn_801D2BD0(p); }

    int mHeap;
    void (*mpLock)(int lock);
};

extern "C" {
PathfinderState_t _Pathfinder_State;
TiburonIAllocator13Impl *_Pathfinder_pAllocator = 0;
unsigned char _Pathfinder_bInit = 0;

void fn_801B2C18(TiburonIAllocator13Impl *pAllocator, TagValuePair *pConfig);
int fn_801B2B58(void);
int fn_801B2CDC(int a);
int fn_801B2F28(int id);
int fn_801B3AD0(int id, PathfinderTrackData_t *pData, int a);
void *fn_801B3B7C(int id, int a, float b);
int fn_801B3D28(int id, PathfinderTrackData_t *pData, int a);
void *fn_801B3DD8(int id);
void fn_801B45D0(int id, signed char value);
void fn_801B4728(int a, int b, int c, int d);
int fn_801B59B0(int id, int a);
void fn_801B5AB0(int a, unsigned char b);
int fn_801B5BCC(int id, PathfinderStatus_t *pInfo);
void fn_801B5CD0(int a);
int fn_801B5FC0(int id, int a);
void fn_8027D3AC(void);
void fn_8027ECD8(void *p, int b);
void fn_8027ED6C(void);

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
        fn_801C6DCC(_Pathfinder_State.mpPool0, 0, (void *)_Pathfinder_State.mHandle, &pFound,
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
    fn_801B2C18(_Pathfinder_pAllocator, &config);
    fn_8027ED6C();
    fn_8027D3AC();
    fn_801C1F94(&_Pathfinder_State, 0, sizeof(_Pathfinder_State));
    _Pathfinder_State.mpPool0 = (List_801C68FC *)fn_801C68FC(pDesc->mHeap, 0, 4, sizeof(PathfinderMap_t), 0, 0);
    _Pathfinder_State.mpPool8 = (List_801C68FC *)fn_801C68FC(pDesc->mHeap, 0, pDesc->mCount, sizeof(PathfinderTrack_t), 0, 0);
    if (_Pathfinder_State.mpPool0 && _Pathfinder_State.mpPool8) {
        _Pathfinder_bInit = 1;
    }
    return -1;
}

void PathfinderShutdown(void)
{
    PathfinderMap_t *pItem;

    fn_801B2F28(-1);
    if (_Pathfinder_State.mpPool8) {
        fn_801C69E4(_Pathfinder_State.mpPool8);
    }
    if (_Pathfinder_State.mpPool0) {
        pItem = (PathfinderMap_t *)fn_801C6B4C(_Pathfinder_State.mpPool0, 0);
        while (pItem) {
            fn_801F010C((Res_801EDC2C *)pItem->mpData, pItem->mUnknown8);
            pItem = (PathfinderMap_t *)fn_801C6C84(_Pathfinder_State.mpPool0, pItem);
        }
        fn_801C69E4(_Pathfinder_State.mpPool0);
    }
    fn_801B2B58();
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
        pItem = (PathfinderMap_t *)fn_801C6A20(_Pathfinder_State.mpPool0);
        if (pItem) {
            id = fn_801EF390((Res_801EDC2C *)pData, a, b);
            if (id) {
                if (fn_801B2CDC(id) >= 0) {
                    pItem->mHandle = _PathfinderNewMapHandle();
                    pItem->mUnknownC = b;
                    pItem->mpData = pData;
                    pItem->mUnknown8 = a;
                    handle = pItem->mHandle;
                    fn_801C6AA4(_Pathfinder_State.mpPool0, pItem, 0);
                } else {
                    fn_801F010C((Res_801EDC2C *)pData, a);
                    fn_801C6C0C(_Pathfinder_State.mpPool0, pItem);
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
        fn_801C6DCC(_Pathfinder_State.mpPool0, 0, (void *)handle, &pItem,
                    _PathfinderMatchMap);
        if (pItem) {
            result = 0;
            fn_801F010C((Res_801EDC2C *)pItem->mpData, pItem->mUnknown8);
            fn_801C6C0C(_Pathfinder_State.mpPool0, pItem);
        }
    }
    return result;
}

int PathfinderCreateTrack(PathfinderTrackDesc_t *pDesc)
{
    PathfinderTrack_t *pItem;
    int result = 0;

    pItem = (PathfinderTrack_t *)fn_801C6A20(_Pathfinder_State.mpPool8);
    if (pItem) {
        fn_801C1F94(pItem, 0, sizeof(PathfinderTrack_t));
        pItem->mUnknown8 = pDesc->mUnknown24;
        fn_801F50C8((SndBankEntry_801F50C8 *)fn_801F44A4(), pDesc->mUnknown10);
        if (pDesc->mUnknown24) {
            result = fn_801B3D28(pDesc->mId, &pDesc->mUnknown14, pDesc->mUnknown20);
            if (result >= 0) {
                pItem->mpUnknown4 = fn_801B3DD8(pDesc->mId);
                if (!pItem->mpUnknown4) {
                    result = -1;
                }
            }
        } else {
            result = fn_801B3AD0(pDesc->mId, &pDesc->mUnknown14, pDesc->mUnknown04);
            if (result >= 0) {
                pItem->mpUnknown4 = fn_801B3B7C(pDesc->mId, pDesc->mUnknown08, pDesc->mUnknown0C);
                if (!pItem->mpUnknown4) {
                    result = -1;
                }
            }
        }
        if (result >= 0) {
            pItem->mId = pDesc->mId;
            fn_801C6AA4(_Pathfinder_State.mpPool8, pItem, 0);
        } else {
            fn_801C6C0C(_Pathfinder_State.mpPool8, pItem);
        }
    }
    return result;
}

int PathfinderDestroyTrack(int id)
{
    PathfinderTrack_t *pItem = 0;
    int result = -1;

    fn_801C6DCC(_Pathfinder_State.mpPool8, 0, (void *)id, &pItem, _PathfinderMatchTrack);
    if (pItem) {
        fn_801C6C0C(_Pathfinder_State.mpPool8, pItem);
        if (fn_801B2F28(id)) {
            result = 0;
        }
    }
    return result;
}

int PathfinderControl(int id, int a)
{
    return fn_801B59B0(id, a);
}

int PathfinderEvent(int id, int a)
{
    return fn_801B5FC0(id, a);
}

void PathfinderSetVolume(int id, int value)
{
    fn_801B45D0(id, value);
}

void PathfinderFade(int a, int b, int c)
{
    fn_801B4728(a, b, c, 1);
}

void PathfinderPause(int a, int b)
{
    fn_801B5AB0(a, b);
}

void PathfinderStop(int a)
{
    fn_801B5CD0(a);
}

void PathfinderSetStreamValue(int a, int b)
{
    void *p = fn_801B3234(a);

    if (p) {
        fn_8027ECD8(p, b);
    }
}

int PathfinderGetStatus(int id, PathfinderStatus_t *pInfo)
{
    int result = -1;

    if (_Pathfinder_bInit) {
        result = fn_801B5BCC(id, pInfo);
    }
    return result;
}
}
