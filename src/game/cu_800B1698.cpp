#include "game/Object_80039F5C.h"
#include "game/Record_800B15FC.h"

extern "C" {
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
float fn_8016FAB4(void);
unsigned char fn_80178794(void);
}

extern "C" void fn_800B1698(Object_80039F5C *pA, Object_80039F5C *pB)
{
    Record_800B15FC *pRecord = fn_800B15FC();

    fn_8009BD2C(pA, &pRecord->mUnknown0);
    pRecord->mUnknownC = pA->mMotion.mPos.mX;
    pRecord->mUnknown10 = fn_8016FAB4();
    pRecord->mUnknown16 = 0;
    pRecord->mUnknown8 = 0;
    fn_8009BD2C(pB, &pRecord->mUnknown4);
    if (pRecord->mUnknown10 == 400.0f) {
        pRecord->mUnknown10 = pA->mMotion.mPos.mY;
    }
    if (pB != 0) {
        pRecord->mUnknown8 = (pB->mFlags >> 10) & 1;
        if (pRecord->mUnknown8 != 0) {
            pRecord->mUnknown16 = fn_80178794();
        } else {
            pRecord->mUnknown16 = 0;
        }
    }
    pRecord->mUnknown14 = sizeof(Record_800B15FC);
    fn_800B1508();
}
