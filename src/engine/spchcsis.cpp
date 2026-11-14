/* Speech library Csis binding (spchcsis.cpp): registers a callback on the Csis parameter of every
   entry of a loaded event database, so parameter changes reach the speech event queue. */

#include "engine/spchlib.h"
#include "engine/cu_801B8C18.h"
#include <string.h>

extern "C" {

int fn_801B8C18(Handle_801B8C60 *out, Struct_803EB878 *desc);
int fn_801B9484(Handle_801B8C60 *handle, Node_801B9410 *node);

/* One 32-byte entry of an event database's Csis table: the parameter name and hash, the handle
   fn_801B8C18 fills in and the callback node registered on it. */
struct SpchCsisEntry_t {
    Struct_803EB878 mDesc;
    Handle_801B8C60 mHandle;
    Node_801B9410 mNode;
};

unsigned short *iSPCH_GetOffset16(void *base, unsigned short *offsets, int index)
{
    return (unsigned short *)((char *)base + offsets[index] * 4);
}
}

void iSPCH_CsisCb(int *values, void *context)
{
    Item_801AE3F4 *item;
    int *block;
    int size;

    item = fn_801AE6BC((SpchEventKey_t *)&context);
    if (item != 0) {
        size = item->mUnknownB * 4;
        block = (int *)fn_801AF4A8(size + 4);
        if (block != 0) {
            *block = (int)context;
            memcpy(block + 1, values, size);
            if (fn_801AEAEC(block) == 0)
                fn_801AF500(block);
        }
    }
}

extern "C" {

void iSPCH_InitCsis(Bank_801AE444 *bank)
{
    SpchCsisEntry_t *table;
    char *names;
    int i;

    if (bank != 0 && bank->mUnknown4 != 0 && bank->mUnknownB == 0) {
        table = (SpchCsisEntry_t *)((char *)bank + bank->mUnknown4);
        names = (char *)&table[bank->mUnknown10];
        for (i = 0; i < bank->mUnknown10; i++) {
            Node_801B9410 *node;
            int offset;

            table[i].mDesc.mName = names + (int)table[i].mDesc.mName;
            fn_801B8C18(&table[i].mHandle, &table[i].mDesc);
            node = &table[i].mNode;
            node->mCallback = (void (*)(void *, void *))iSPCH_CsisCb;
            offset = *iSPCH_GetOffset16(bank, bank->mUnknown18, i);
            node->mContext = (void *)fn_801AE5D4(bank->mUnknown8, bank->mUnknown9, offset);
            fn_801B9484(&table[i].mHandle, node);
        }
        bank->mUnknownB = 1;
    }
}
}
