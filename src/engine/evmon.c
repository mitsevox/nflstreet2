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
    unsigned int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mUnknown12;
    AudmonEventFn_t mpUnknown16[1];
} EvMon_t;

typedef struct EvMonTable_t {
    int mUnknown0;
    int mUnknown4;
    EvMon_t **mppUnknown8;
} EvMonTable_t;

extern EvMonTable_t _EvMon_Table;
extern unsigned char _EvMon_bInit;
extern void *SyncStateGetData(void *pHandle);

void EvMonInitHeader(int *p, const EvMonDesc_t *q)
{
    p[0] = q->mUnknown0;
    p[1] = 0;
    p[2] = q->mUnknown4;
    p[3] = q->mUnknown8;
}

void EvMonInit(int count)
{
    _EvMon_Table.mUnknown0 = 0;
    _EvMon_Table.mUnknown4 = count;
    _EvMon_Table.mppUnknown8 = fn_801D2B7C(count * 4, 0, 0);
    MemFill((char *)_EvMon_Table.mppUnknown8, count * 4, 0, 4);
    _EvMon_bInit = 1;
}

void EvMonShutdown(void)
{
    fn_801D2BD0(_EvMon_Table.mppUnknown8);
    _EvMon_bInit = 0;
}

int EvMonCreate(const EvMonDesc_t *pDesc)
{
    int index = _EvMon_Table.mUnknown0;
    int size = pDesc->mUnknown0 * pDesc->mUnknown4 + 16 + pDesc->mUnknown8 * 4;
    void *pHandle = SyncStateRegister(0, (void **)&_EvMon_Table.mppUnknown8[index], size, 0, 0x65766D6F);
    EvMonInitHeader(SyncStateGetData(pHandle), pDesc);
    SyncStateCommit(pHandle);
    _EvMon_Table.mUnknown0++;
    return index;
}

void EvMonDestroy(int index)
{
}

int EvMonAlloc(const EvMonDesc_t *pDesc)
{
    int index = _EvMon_Table.mUnknown0;
    int size = pDesc->mUnknown0 * pDesc->mUnknown4 + 16 + pDesc->mUnknown8 * 4;
    _EvMon_Table.mppUnknown8[index] = fn_801D2B7C(size, 0, 0);
    memset(_EvMon_Table.mppUnknown8[index], 0, size);
    EvMonInitHeader((int *)_EvMon_Table.mppUnknown8[index], pDesc);
    _EvMon_Table.mUnknown0++;
    return index;
}

void EvMonFree(int index)
{
    fn_801D2BD0(_EvMon_Table.mppUnknown8[index]);
    _EvMon_Table.mppUnknown8[index] = 0;
}

void *EvMonGetCurrentRecord(int index)
{
    EvMon_t *p = _EvMon_Table.mppUnknown8[index];
    return (char *)p + 16 + p->mUnknown12 * 4 + p->mUnknown8 * p->mUnknown4;
}

void *EvMonGetRecord(int index, int item)
{
    EvMon_t *p = _EvMon_Table.mppUnknown8[index];
    return (char *)p + 16 + p->mUnknown12 * 4 + p->mUnknown8 * item;
}

void EvMonFire(int index, int advance)
{
    EvMon_t *p = _EvMon_Table.mppUnknown8[index];
    unsigned int i;
    for (i = 0; i < p->mUnknown12; i++) {
        AudmonEventFn_t callback = p->mpUnknown16[i];
        if (callback != 0) {
            callback(EvMonGetCurrentRecord(index));
        }
    }
    if (advance != 0) {
        p->mUnknown4++;
    }
}

unsigned int EvMonGetCount(int index)
{
    return _EvMon_Table.mppUnknown8[index]->mUnknown4;
}

void EvMonClear(int index)
{
    EvMon_t *p = _EvMon_Table.mppUnknown8[index];
    MemFill((char *)p + 16 + p->mUnknown12 * 4, p->mUnknown0 * p->mUnknown8, 0, 4);
    p->mUnknown4 = 0;
}

void EvMonAddListener(int index, AudmonEventFn_t callback)
{
    EvMon_t *p = _EvMon_Table.mppUnknown8[index];
    unsigned int i;
    for (i = 0; i < p->mUnknown12 && ((AudmonEventFn_t *)p)[i + 4] != 0; i++) {
    }
    ((AudmonEventFn_t *)p)[i + 4] = callback;
}

void EvMonRemoveListener(int index, AudmonEventFn_t callback)
{
    EvMon_t *p = _EvMon_Table.mppUnknown8[index];
    unsigned int i;
    for (i = 0; i < p->mUnknown12 && ((AudmonEventFn_t *)p)[i + 4] != callback; i++) {
    }
    ((AudmonEventFn_t *)p)[i + 4] = 0;
}
