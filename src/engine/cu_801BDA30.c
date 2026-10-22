#include <string.h>
#include "engine/cu_801BDA30.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

extern Handlers_801BDA30 **lbl_803EBB98;
extern int lbl_803ECEBC;
extern List_801BAB88 lbl_8037EC7C;

int fn_801BDA30(unsigned short type, unsigned short key, void *pOwner, int event, Object_801BA03C *pObject,
                Record_800D81C8 *pRecords)
{
    if (key & 0x8000) {
        return 0;
    }
    fn_801BBC3C(type, key, &lbl_8037EC7C);
    return lbl_803EBB98[type]->mpUnknown4[key](&lbl_8037EC7C, key, pObject, pRecords, pOwner, event);
}

void fn_801BDAC0(Collection_801BE594 *p)
{
    int count;
    int i;
    int j;

    for (count = 3; count >= 0; count--) {
        if (p->mUnknown4[count].mUnknown2 != 0) {
            break;
        }
    }
    if (count > 0) {
        i = 0;
        while (i < count) {
            if (p->mUnknown4[i].mUnknown2 == 0) {
                for (j = i; j < count; j++) {
                    p->mUnknown4[j] = p->mUnknown4[j + 1];
                    p->mUnknown4[j + 1].mUnknown2 = 0;
                    p->mUnknown4[j + 1].mUnknown8 = 0.0f;
                }
                count--;
            } else {
                i++;
            }
        }
    }
}

void fn_801BDBD4(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, int index,
                 void *pOwner)
{
    fn_801BDA30(pObject->mUnknown2, p->mUnknown4[index].mUnknown0, pOwner, 3, pObject, pRecords);
    fn_801BA398(pObject, pRecords, p->mUnknown4[index].mUnknown0);
    p->mUnknown4[index].mUnknown2 = 0;
}

unsigned short fn_801BDC3C(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, void *pOwner,
                           unsigned short key)
{
    int slot = -1;
    int freed = 0;
    int i;

    fn_801BDAC0(p);
    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 == 0) {
            slot = i;
            break;
        }
    }
    if (i == 4) {
        for (i = 0; i < 4; i++) {
            if (p->mUnknown4[i].mUnknown8 != 0.0f) {
                fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                freed = 1;
                fn_801BDAC0(p);
                break;
            }
        }
        if (!freed) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && p->mUnknown4[i].mUnknown4C.mUnknown0 <= 1e-07f && (p->mUnknown4[i].mUnknown0 & 0x8000) &&
                    p->mUnknown4[i].mUnknown0 != 0xFFFF && fn_801BA568(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                    freed = 1;
                    fn_801BDAC0(p);
                    break;
                }
            }
        }
        if (!freed) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && p->mUnknown4[i].mUnknown0 != 0xFFFF &&
                    fn_801BA568(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                    freed = 1;
                    fn_801BDAC0(p);
                    break;
                }
            }
        }
        if (!freed) {
            float lowest = 1.1f;
            int index = -1;

            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && p->mUnknown4[i].mUnknown0 != 0xFFFF &&
                    p->mUnknown4[i].mUnknown4C.mUnknown0 < lowest) {
                    lowest = p->mUnknown4[i].mUnknown4C.mUnknown0;
                    index = i;
                }
            }
            if (index != -1) {
                fn_801BDBD4(p, pObject, pRecords, index, pOwner);
                freed = 1;
                fn_801BDAC0(p);
            }
        }
        if (freed == 1) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 0) {
                    slot = i;
                    break;
                }
            }
        }
    }
    if (slot == -1) {
        slot = 3;
        fn_801BDBD4(p, pObject, pRecords, 0, pOwner);
        fn_801BDAC0(p);
    }
    return slot;
}

unsigned short fn_801BDF38(Collection_801BE594 *p)
{
    unsigned short key = 0xFFFE;
    int unique;
    int i;

    do {
        unique = 1;
        for (i = 0; i < 4; i++) {
            if (p->mUnknown4[i].mUnknown0 == key) {
                key--;
                unique = 0;
                break;
            }
        }
    } while (!unique);
    return key;
}

int fn_801BDF90(int count)
{
    int result;

    lbl_803EBB98 = fn_801D2B7C(count * 4, 0, 0);
    result = fn_801F7C88();
    lbl_803ECEBC = count;
    if (lbl_803EBB98 != 0) {
        memset(lbl_803EBB98, 0, count * 4);
    }
    return result;
}

int fn_801BDFF8(void)
{
    if (lbl_803EBB98 != 0) {
        fn_801D2BD0(lbl_803EBB98);
        lbl_803EBB98 = 0;
    }
    return 0;
}

void fn_801BE030(int type, Handlers_801BDA30 *pHandlers)
{
    lbl_803EBB98[type] = pHandlers;
}

void fn_801BE040(Collection_801BE594 *p)
{
    int i;

    for (i = 0; i < 4; i++) {
        p->mUnknown4[i].mUnknown0 = 0;
        p->mUnknown4[i].mUnknown6 = -16;
        p->mUnknown4[i].mUnknown2 = 0;
    }
}

int fn_801BE068(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, unsigned short key,
                void *pOwner, float frames)
{
    unsigned short previous = fn_801BE648(p);
    unsigned short slot;
    int add;
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 == 3) {
            p->mUnknown4[i].mUnknown2 = 2;
            fn_801BDA30(pObject->mUnknown2, previous, pOwner, 4, pObject, pRecords);
            if (p->mUnknown4[i].mUnknown8 != 0.0f && i > 0) {
                fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                i--;
                if (p->mUnknown4[i].mUnknown0 == 0xFFFF) {
                    p->mUnknown4[i].mUnknown0 = fn_801BDF38(p);
                    fn_801BF4A8(&p->mUnknown4[i].mUnknown4C, 10, -1.0f, 0.0f);
                    while (fn_801BA568(pObject, pRecords, 0xFFFF)) {
                        pRecords[fn_801BA5A8(pObject, pRecords, 0xFFFF, 0)].mUnknown8 = p->mUnknown4[i].mUnknown0;
                    }
                }
            }
            break;
        }
    }
    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0) {
            unsigned short old = p->mUnknown4[i].mUnknown0;

            if (old == key || old == 0xFFFF) {
                p->mUnknown4[i].mUnknown0 = fn_801BDF38(p);
                p->mUnknown4[i].mUnknown4 &= ~1;
                while (fn_801BA568(pObject, pRecords, old)) {
                    pRecords[fn_801BA5A8(pObject, pRecords, old, 0)].mUnknown8 = p->mUnknown4[i].mUnknown0;
                }
            }
        }
    }
    add = 0;
    if (fn_801BE82C(pObject->mUnknown2, previous)) {
        add = 1;
    }
    if (add == 1) {
        slot = fn_801BDC3C(p, pObject, pRecords, pOwner, 0xFFFF);
        memset(&p->mUnknown4[slot], 0, sizeof(Slot_801BE594));
        p->mUnknown4[slot].mUnknown0 = 0xFFFF;
        p->mUnknown4[slot].mUnknown2 = add;
        p->mUnknown4[slot].mUnknown8 = 0.0f;
        fn_801BF3C8(&p->mUnknown4[slot].mUnknown4C, 0, 0.0f, 0, 0.0f);
    }
    slot = fn_801BDC3C(p, pObject, pRecords, pOwner, key);
    memset(&p->mUnknown4[slot], 0, sizeof(Slot_801BE594));
    p->mUnknown4[slot].mUnknown2 = 3;
    p->mUnknown4[slot].mUnknown0 = key;
    p->mUnknown4[slot].mUnknown8 = 0.0f;
    fn_801BF4A8(&p->mUnknown4[slot].mUnknown4C, 10, 0.0f, frames);
    fn_801BDA30(pObject->mUnknown2, key, pOwner, 0, pObject, pRecords);
    fn_801BE99C(p, pObject, pRecords, key, previous, 2, pOwner);
    return 0;
}

void fn_801BE420(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, void *pOwner, float step)
{
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 == 0) {
            break;
        }
        p->mUnknown4[i].mUnknown8 -= step;
        if (p->mUnknown4[i].mUnknown8 < 0.0f) {
            p->mUnknown4[i].mUnknown8 = 0.0f;
            fn_801BF46C(&p->mUnknown4[i].mUnknown4C, step);
            if (p->mUnknown4[i].mUnknown4C.mUnknown0 > 1e-07f) {
                if (p->mUnknown4[i].mUnknown4 & 1) {
                    fn_801BDA30(pObject->mUnknown2, p->mUnknown4[i].mUnknown0, pOwner, 2, pObject, pRecords);
                }
                if (fn_801BA568(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    if (p->mUnknown4[i].mUnknown2 == 3) {
                        fn_801BDA30(pObject->mUnknown2, p->mUnknown4[i].mUnknown0, pOwner, 1, pObject, pRecords);
                    } else {
                        fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                    }
                }
            } else {
                fn_801BDBD4(p, pObject, pRecords, i, pOwner);
            }
        }
    }
    fn_801BDAC0(p);
}

Slot_801BE594 *fn_801BE594(Collection_801BE594 *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return &p->mUnknown4[i];
        }
    }
    return 0;
}

float fn_801BE5D0(Collection_801BE594 *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return p->mUnknown4[i].mUnknown4C.mUnknown0;
        }
    }
    return 0.0f;
}

struct Block_801BE60C *fn_801BE60C(Collection_801BE594 *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return (struct Block_801BE60C *)p->mUnknown4[i].mUnknownC;
        }
    }
    return 0;
}

unsigned short fn_801BE648(Collection_801BE594 *p)
{
    unsigned short key = 0xFFFF;
    int i;

    for (i = 3; i >= 0; i--) {
        if (p->mUnknown4[i].mUnknown2 == 3) {
            key = p->mUnknown4[i].mUnknown0;
        }
    }
    return key;
}

void fn_801BE67C(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, void *pOwner)
{
    int i;

    for (i = 3; i >= 0; i--) {
        if (p->mUnknown4[i].mUnknown2 != 3 && p->mUnknown4[i].mUnknown2 != 0) {
            fn_801BDBD4(p, pObject, pRecords, i, pOwner);
        }
    }
    fn_801BDAC0(p);
    if (p->mUnknown4[0].mUnknown2 == 3) {
        p->mUnknown4[0].mUnknown8 = 0.0f;
        fn_801BF3C8(&p->mUnknown4[0].mUnknown4C, 0, 1.0f, 0, 1.0f);
    }
}

void *fn_801BE72C(unsigned short type, unsigned short key)
{
    fn_801BBC3C(type, key, &lbl_8037EC7C);
    return &lbl_8037EC7C;
}

void fn_801BE760(Collection_801BE594 *p, unsigned short key, unsigned short flags)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            p->mUnknown4[i].mUnknown4 |= flags;
        }
    }
}

void fn_801BE798(Collection_801BE594 *p, unsigned short key, float value)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            p->mUnknown4[i].mUnknown8 = value;
        }
    }
}

float fn_801BE7C8(Collection_801BE594 *p, unsigned short key)
{
    float value = 0.0f;
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            value = p->mUnknown4[i].mUnknown8;
            break;
        }
    }
    return value;
}
