/* Event monitors: numbered queues of fixed-size event records, registered
   as 'evmo' blocks in the state registry or allocated directly, with the
   listener callbacks run on each posted event. */

#include "engine/SyncStateGroup.h"
#include "engine/EvMonDesc.h"
#include "engine/EvMonAddListener.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/SyncStateRegister.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

typedef struct EvMon_t {
    unsigned int mNumRecords;
    int mNumPosted;
    int mRecordSize;
    unsigned int mNumListeners;
    AudmonEventFn_t mpListeners[1];
} EvMon_t;

typedef struct EvMonTable_t {
    int mCount;
    int mCapacity;
    EvMon_t **mppMonitors;
} EvMonTable_t;

static EvMonTable_t _EvMon_Table;
static unsigned char _EvMon_bInit = 0;
extern void *SyncStateGetData(void *pHandle);

void EvMonInitHeader(EvMon_t *p, const EvMonDesc_t *q)
{
    p->mNumRecords = q->mNumRecords;
    p->mNumPosted = 0;
    p->mRecordSize = q->mRecordSize;
    p->mNumListeners = q->mNumListeners;
}

void EvMonInit(int count)
{
    _EvMon_Table.mCount = 0;
    _EvMon_Table.mCapacity = count;
    _EvMon_Table.mppMonitors = fn_801D2B7C(count * 4, 0, 0);
    MemFill((char *)_EvMon_Table.mppMonitors, count * 4, 0, 4);
    _EvMon_bInit = 1;
}

void EvMonShutdown(void)
{
    fn_801D2BD0(_EvMon_Table.mppMonitors);
    _EvMon_bInit = 0;
}

int EvMonCreate(const EvMonDesc_t *pDesc)
{
    int index = _EvMon_Table.mCount;
    int size = pDesc->mNumRecords * pDesc->mRecordSize + 16 + pDesc->mNumListeners * 4;
    void *pHandle = SyncStateRegister(0, (void **)&_EvMon_Table.mppMonitors[index], size, 0, 0x65766D6F);
    EvMonInitHeader(SyncStateGetData(pHandle), pDesc);
    SyncStateCommit(pHandle);
    _EvMon_Table.mCount++;
    return index;
}

void EvMonDestroy(int index)
{
}

int EvMonAlloc(const EvMonDesc_t *pDesc)
{
    int index = _EvMon_Table.mCount;
    int size = pDesc->mNumRecords * pDesc->mRecordSize + 16 + pDesc->mNumListeners * 4;
    _EvMon_Table.mppMonitors[index] = fn_801D2B7C(size, 0, 0);
    memset(_EvMon_Table.mppMonitors[index], 0, size);
    EvMonInitHeader(_EvMon_Table.mppMonitors[index], pDesc);
    _EvMon_Table.mCount++;
    return index;
}

void EvMonFree(int index)
{
    fn_801D2BD0(_EvMon_Table.mppMonitors[index]);
    _EvMon_Table.mppMonitors[index] = 0;
}

void *EvMonGetCurrentRecord(int index)
{
    EvMon_t *p = _EvMon_Table.mppMonitors[index];
    return (char *)p + 16 + p->mNumListeners * 4 + p->mRecordSize * p->mNumPosted;
}

void *EvMonGetRecord(int index, int item)
{
    EvMon_t *p = _EvMon_Table.mppMonitors[index];
    return (char *)p + 16 + p->mNumListeners * 4 + p->mRecordSize * item;
}

void EvMonFire(int index, int advance)
{
    EvMon_t *p = _EvMon_Table.mppMonitors[index];
    unsigned int i;
    for (i = 0; i < p->mNumListeners; i++) {
        AudmonEventFn_t callback = p->mpListeners[i];
        if (callback != 0) {
            callback(EvMonGetCurrentRecord(index));
        }
    }
    if (advance != 0) {
        p->mNumPosted++;
    }
}

unsigned int EvMonGetCount(int index)
{
    return _EvMon_Table.mppMonitors[index]->mNumPosted;
}

void EvMonClear(int index)
{
    EvMon_t *p = _EvMon_Table.mppMonitors[index];
    MemFill((char *)p + 16 + p->mNumListeners * 4, p->mNumRecords * p->mRecordSize, 0, 4);
    p->mNumPosted = 0;
}

void EvMonAddListener(int index, AudmonEventFn_t callback)
{
    EvMon_t *p = _EvMon_Table.mppMonitors[index];
    unsigned int i;
    for (i = 0; i < p->mNumListeners && ((AudmonEventFn_t *)p)[i + 4] != 0; i++) {
    }
    ((AudmonEventFn_t *)p)[i + 4] = callback;
}

void EvMonRemoveListener(int index, AudmonEventFn_t callback)
{
    EvMon_t *p = _EvMon_Table.mppMonitors[index];
    unsigned int i;
    for (i = 0; i < p->mNumListeners && ((AudmonEventFn_t *)p)[i + 4] != callback; i++) {
    }
    ((AudmonEventFn_t *)p)[i + 4] = 0;
}
