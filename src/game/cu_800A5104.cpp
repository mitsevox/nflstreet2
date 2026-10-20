#include "game/Object_80039F5C.h"

/* Per-condition counters passed to the condition callbacks. */
struct Pair_800A554C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
};

extern "C" {
int fn_8009F058(Object_80039F5C *p, Object_80039F5C *pOther, int angle);
float fn_80237260(int stream);
}

extern "C" int fn_800A5104(Object_80039F5C *p, Object_80039F5C *pTarget, Object_80039F5C *pOther,
                           Pair_800A554C *pPair)
{
    int result = 0;

    if (fn_8009F058(p, pTarget, 0x400000) != 0 && fn_8009F058(p, pOther, 0x400000) != 0) {
        result = fn_80237260(0) < 0.33f;
    }
    return result;
}
