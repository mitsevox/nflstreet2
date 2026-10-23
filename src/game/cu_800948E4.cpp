#include "game/Object_8017886C.h"

extern "C" {
int fn_800947C4(Object_8017886C *p);
int fn_8009481C(Object_8017886C *p);
int fn_80093C50(int index);
int fn_80178308(void);
unsigned char fn_80178348(void);
}

/* Situation kind of p, from its +0x1D state and, for state 0, its flags,
   fn_80093C50(1) and the yards fn_8009481C gives; 14 when nothing applies. */
extern "C" int fn_800948E4(Object_8017886C *p)
{
    int kind = 14;

    if (p->mUnknown1D != 0) {
        switch (p->mUnknown1D) {
        case 6:
        case 9:
            kind = 2;
            break;
        case 2:
            kind = 11;
            break;
        case -2:
            kind = 8;
            break;
        case 3:
        case -3:
            kind = 3;
            break;
        }
    } else if (fn_800947C4(p) == 2) {
        kind = 12;
    } else if (p->mUnknown18 & 0x800) {
        kind = 4;
    } else {
        kind = fn_80093C50(1);
        switch (kind) {
        case 6:
        case 7:
        case 9:
        case 10:
            break;
        case 3:
            if (fn_80178348() == fn_80178308()) {
                kind = 14;
            }
            break;
        case 5:
            if (!(p->mUnknown18 & 0x10000)) {
                break;
            }
            /* fall through */
        default:
            if (p->mUnknown18 & 0x40) {
                kind = 14;
                if (fn_80178348() == fn_80178308()) {
                    kind = 1;
                }
            } else {
                float yards = fn_8009481C(p);

                if (yards > 0.0f) {
                    kind = 0;
                } else if (yards < 0.0f) {
                    kind = 13;
                }
            }
            break;
        }
    }
    return kind;
}
