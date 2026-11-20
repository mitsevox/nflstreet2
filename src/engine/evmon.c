/* Event monitors: numbered queues of fixed-size event records, registered
   as 'evmo' blocks in the state registry or allocated directly, with the
   listener callbacks run on each posted event. */

#include "engine/Object_80237EE8.h"
#include "engine/Desc_80238424.h"
#include "engine/fn_80238680.h"
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include "engine/viewport.h"
#include "engine/llmatrix.h"
#include "engine/vec.h"
#include "engine/rand.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_80238174.h"
#include "game/Object_80235588.h"
#include "engine/list.h"
#include "engine/llmemory.h"
#include "engine/dslist.h"

typedef struct Entry_8023850C {
    unsigned int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned int mUnknown12;
    AudmonEventFn_t mpUnknown16[1];
} Entry_8023850C;

typedef struct Table_802382F0 {
    int mUnknown0;
    int mUnknown4;
    Entry_8023850C **mppUnknown8;
} Table_802382F0;

extern Table_802382F0 lbl_803A3A14;
extern unsigned char lbl_803EC140;
extern void *fn_8023816C(void *pHandle);

void fn_802382CC(int *p, const Desc_80238424 *q)
{
    p[0] = q->mUnknown0;
    p[1] = 0;
    p[2] = q->mUnknown4;
    p[3] = q->mUnknown8;
}

void fn_802382F0(int count)
{
    lbl_803A3A14.mUnknown0 = 0;
    lbl_803A3A14.mUnknown4 = count;
    lbl_803A3A14.mppUnknown8 = fn_801D2B7C(count * 4, 0, 0);
    MemFill((char *)lbl_803A3A14.mppUnknown8, count * 4, 0, 4);
    lbl_803EC140 = 1;
}

void fn_80238358(void)
{
    fn_801D2BD0(lbl_803A3A14.mppUnknown8);
    lbl_803EC140 = 0;
}

int fn_80238388(const Desc_80238424 *pDesc)
{
    int index = lbl_803A3A14.mUnknown0;
    void *pHandle = fn_80238174(0, (void **)&lbl_803A3A14.mppUnknown8[index], pDesc->mUnknown0 * pDesc->mUnknown4 + 16 + pDesc->mUnknown8 * 4, 0, 0x65766D6F);
    fn_802382CC(fn_8023816C(pHandle), pDesc);
    fn_802381E0(pHandle);
    lbl_803A3A14.mUnknown0++;
    return index;
}

void fn_80238420(int index)
{
}

int fn_80238424(const Desc_80238424 *pDesc)
{
    int index = lbl_803A3A14.mUnknown0;
    int size = pDesc->mUnknown0 * pDesc->mUnknown4 + 16 + pDesc->mUnknown8 * 4;
    lbl_803A3A14.mppUnknown8[index] = fn_801D2B7C(size, 0, 0);
    memset(lbl_803A3A14.mppUnknown8[index], 0, size);
    fn_802382CC((int *)lbl_803A3A14.mppUnknown8[index], pDesc);
    lbl_803A3A14.mUnknown0++;
    return index;
}

void fn_802384C4(int index)
{
    fn_801D2BD0(lbl_803A3A14.mppUnknown8[index]);
    lbl_803A3A14.mppUnknown8[index] = 0;
}

void *fn_8023850C(int index)
{
    Entry_8023850C *p = lbl_803A3A14.mppUnknown8[index];
    return (char *)p + 16 + p->mUnknown12 * 4 + p->mUnknown8 * p->mUnknown4;
}

void *fn_80238540(int index, int item)
{
    Entry_8023850C *p = lbl_803A3A14.mppUnknown8[index];
    return (char *)p + 16 + p->mUnknown12 * 4 + p->mUnknown8 * item;
}

void fn_80238570(int index, int advance)
{
    Entry_8023850C *p = lbl_803A3A14.mppUnknown8[index];
    unsigned int i;
    AudmonEventFn_t *pCallbacks = p->mpUnknown16;
    for (i = 0; i < p->mUnknown12; i++) {
        AudmonEventFn_t callback = *pCallbacks++;
        if (callback != 0) {
            callback(fn_8023850C(index));
        }
    }
    if (advance != 0) {
        p->mUnknown4++;
    }
}

unsigned int fn_80238604(int index)
{
    return lbl_803A3A14.mppUnknown8[index]->mUnknown4;
}

void fn_8023861C(int index)
{
    Entry_8023850C *p = lbl_803A3A14.mppUnknown8[index];
    MemFill((char *)p + 16 + p->mUnknown12 * 4, p->mUnknown0 * p->mUnknown8, 0, 4);
    p->mUnknown4 = 0;
}

void fn_80238680(int index, AudmonEventFn_t callback)
{
    Entry_8023850C *p = lbl_803A3A14.mppUnknown8[index];
    unsigned int i;
    for (i = 0; i < p->mUnknown12 && p->mpUnknown16[i] != 0; i++) {
    }
    p->mpUnknown16[i] = callback;
}

void fn_802386DC(int index, AudmonEventFn_t callback)
{
    Entry_8023850C *p = lbl_803A3A14.mppUnknown8[index];
    unsigned int i;
    for (i = 0; i < p->mUnknown12 && p->mpUnknown16[i] != callback; i++) {
    }
    p->mpUnknown16[i] = 0;
}
