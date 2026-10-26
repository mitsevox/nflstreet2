#include "engine/cu_801B9F00.h"
#include "game/Object_80039F5C.h"

extern "C" unsigned char fn_800D78C4(Object_80039F5C *p, unsigned short id)
{
    float best = -1.0f;
    int search = 1;
    unsigned char result = 0;
    unsigned int count = fn_801BA568(p->mpUnknown796, p->mpUnknown800, id);

    switch (id) {
    case 30:
    case 31:
    case 74:
    case 77:
    case 164:
    case 181:
    case 186:
    case 247:
        if (p->mUnknown776) {
            search = 0;
        }
        break;
    }
    if (!search) {
        result = p->mUnknown776;
    } else {
        for (unsigned short i = 0; i < count; i++) {
            int index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, id, i);
            if (p->mpUnknown800[index].mUnknown30.mUnknown0 > best) {
                best = p->mpUnknown800[index].mUnknown30.mUnknown0;
                if (p->mpUnknown800[index].mUnknown7 & 0x10) {
                    result = 1;
                } else if (p->mpUnknown800[index].mUnknown7 & 0x20) {
                    result = 2;
                } else if (p->mpUnknown800[index].mUnknown7 & 1) {
                    result = 1;
                } else {
                    result = 2;
                }
            }
        }
    }
    return result;
}
