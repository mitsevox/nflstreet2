/* Controller context: channels of mapped input buffers, processed through dead-zone entry tables into callbacks. */

#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"

typedef struct ConEntry_801C5B9C {
    unsigned int mId;
    unsigned short mFlags;
    unsigned short mIndex;
    float mDeadZone;
    float mScale;
    float mInvDeadZone;
} ConEntry_801C5B9C;

typedef void (*ConCallback_801C5B9C)(unsigned int channel, unsigned int id, float value);
typedef void (*ConUpdate_801C5B9C)(unsigned int channel, float *pPrev, float *pCur);

typedef struct ConChannel_801C5B9C {
    unsigned int mFlags;
    int mMapping;
    ConEntry_801C5B9C *mpEntries;
    ConCallback_801C5B9C mpCallback;
    ConUpdate_801C5B9C mpUpdate;
    float *mpCur;
    float *mpPrev;
} ConChannel_801C5B9C;

extern unsigned char lbl_803EBBEC;
extern ConChannel_801C5B9C *lbl_803EBBF0;
extern ConCallback_801C5B9C lbl_803EBBF4;
extern unsigned int lbl_803ECED8;
extern unsigned int lbl_803ECEDC;
extern char *lbl_803ECEE0;
extern int lbl_803ED624;
extern Lock_801F8014 lbl_8037F860;

void *fn_801C1F94(void *pDst, int value, int size);
int fn_801D34D0(void *pDest, int size, int value, int width);

static void fn_801C5B9C(unsigned int channel)
{
    if (lbl_803EBBEC && lbl_803EBBF0) {
        fn_801C1F94(lbl_803EBBF0[channel].mpCur, 0, lbl_803ECEDC);
        fn_801C1F94(lbl_803EBBF0[channel].mpPrev, 0, lbl_803ECEDC);
    }
}

static void fn_801C5C08(unsigned int channel)
{
    if ((lbl_803EBBF0[channel].mFlags & 1) && lbl_803EBBF0[channel].mpUpdate) {
        lbl_803EBBF0[channel].mpUpdate(channel, lbl_803EBBF0[channel].mpPrev, lbl_803EBBF0[channel].mpCur);
    }
}

static void fn_801C5C58(ConEntry_801C5B9C *pEntry)
{
    while (pEntry->mFlags != 0x8000) {
        pEntry->mInvDeadZone = pEntry->mDeadZone != 0.0f ? 1.0f / (1.0f - pEntry->mDeadZone) : 0.0f;
        pEntry++;
    }
}

static inline float fn_801C5B9C_Abs(float x)
{
    return __builtin_fabs(x);
}

static float fn_801C5CB8(ConEntry_801C5B9C *pEntry, int mapping, float *pValues, unsigned char *pActive)
{
    float value;
    float deadZone;
    float offset;

    *pActive = 1;
    deadZone = pEntry->mDeadZone;
    value = pValues[pEntry->mIndex];
    if (!(deadZone <= 0.0f)) {
        if (!(fn_801C5B9C_Abs(value) > deadZone)) {
            value = 0.0f;
        } else {
            offset = deadZone;
            if (!(value >= 0.0f)) {
                offset = -offset;
            }
            value = (value - offset) * pEntry->mInvDeadZone;
            if (!(value <= 0.99f)) {
                value = 1.0f;
            } else if (!(value >= -0.99f)) {
                value = -1.0f;
            }
        }
    }
    if (pEntry->mFlags & 0x10) {
        if (!(value >= 0.0f)) {
            *pActive = 0;
        }
    } else if (pEntry->mFlags & 0x20) {
        if (!(value <= 0.0f)) {
            *pActive = 0;
        }
    }
    if ((pEntry->mFlags & 1) && value != 0.0f) {
        value = 1.0f;
    }
    if (pEntry->mScale != 1.0f) {
        value *= pEntry->mScale;
    }
    if (pEntry->mFlags & 2) {
        if (value == 0.0f) {
            *pActive = 0;
        }
    } else if (pEntry->mFlags & 4) {
        if (value != 0.0f) {
            *pActive = 0;
        }
    }
    return value;
}

int fn_801C5E24(unsigned int count, int size)
{
    int error = 0;
    unsigned int i;

    if (!lbl_803EBBEC) {
        fn_801F7FA8(&lbl_8037F860);
        fn_801F8014(&lbl_8037F860);
        lbl_803EBBF4 = 0;
        lbl_803ECED8 = count;
        lbl_803EBBF0 = fn_801D2BB0(1, count * sizeof(ConChannel_801C5B9C), 0, 0);
        if (!lbl_803EBBF0) {
            error = fn_801F7C88();
        } else {
            lbl_803ECEDC = size * sizeof(float);
            lbl_803ECEE0 = fn_801D2BB0(1, count * (lbl_803ECEDC + lbl_803ECEDC), 0, 0);
            if (!lbl_803ECEE0) {
                fn_801D2BD0(lbl_803EBBF0);
                error = fn_801F7C88();
            } else {
                fn_801D34D0(lbl_803ECEE0, count * (lbl_803ECEDC + lbl_803ECEDC), 0, 4);
                fn_801D34D0(lbl_803EBBF0, count * sizeof(ConChannel_801C5B9C), 0, 4);
                for (i = 0; i < lbl_803ECED8; i++) {
                    lbl_803EBBF0[i].mpCur = (float *)(lbl_803ECEE0 + i * (lbl_803ECEDC + lbl_803ECEDC));
                    lbl_803EBBF0[i].mpPrev = (float *)(lbl_803ECEE0 + i * (lbl_803ECEDC + lbl_803ECEDC) + lbl_803ECEDC);
                    lbl_803EBBF0[i].mFlags = 0;
                    lbl_803EBBF0[i].mMapping = -1;
                    lbl_803EBBF0[i].mpEntries = 0;
                    lbl_803EBBF0[i].mpCallback = 0;
                    lbl_803EBBF0[i].mpUpdate = 0;
                }
                lbl_803EBBEC = 1;
            }
        }
        fn_801F809C(&lbl_8037F860);
    } else {
        error = 0x1A0001;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C5F9C(void)
{
    int error = 0;

    if (lbl_803EBBEC) {
        fn_801F8014(&lbl_8037F860);
        fn_801D2BD0(lbl_803ECEE0);
        fn_801D2BD0(lbl_803EBBF0);
        lbl_803EBBF0 = 0;
        fn_801F809C(&lbl_8037F860);
        fn_801F80D0(&lbl_8037F860);
        lbl_803EBBEC = 0;
    } else {
        error = 0x1A0002;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C601C(unsigned int channel)
{
    int error = 0;

    if (!lbl_803EBBEC) {
        error = 0x1A0002;
    } else if (channel < lbl_803ECED8) {
        fn_801C5C08(channel);
    } else if (channel == (unsigned int)-1) {
        for (channel = 0; channel < lbl_803ECED8; channel++) {
            fn_801C5C08(channel);
        }
    } else {
        error = 0x1A0003;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C60BC(unsigned int channel)
{
    int error = 0;
    unsigned char active = 0;
    unsigned char prevActive = 0;
    ConEntry_801C5B9C *pEntry;
    ConCallback_801C5B9C callback;
    int mapping;
    float *pCur;
    float *pPrev;
    float value;
    float prevValue;

    if (!lbl_803EBBEC) {
        error = 0x1A0002;
    } else if (channel < lbl_803ECED8) {
        pEntry = lbl_803EBBF0[channel].mpEntries;
        mapping = lbl_803EBBF0[channel].mMapping;
        pCur = lbl_803EBBF0[channel].mpCur;
        pPrev = lbl_803EBBF0[channel].mpPrev;
        callback = lbl_803EBBF0[channel].mpCallback;
        if (pEntry && (lbl_803EBBF0[channel].mFlags & 1)) {
            while (!(pEntry->mFlags & 0x8000)) {
                value = fn_801C5CB8(pEntry, mapping, pCur, &active);
                if (active == 1) {
                    if (pEntry->mFlags & 8) {
                        prevValue = fn_801C5CB8(pEntry, mapping, pPrev, &prevActive);
                        if (prevActive == 1 && prevValue == value) {
                            active = 0;
                        }
                    }
                    if (active == 1) {
                        if (lbl_803EBBF4) {
                            if (pEntry->mFlags) {
                                lbl_803EBBF4(channel, pEntry->mId, value);
                            } else {
                                lbl_803EBBF4(-1, pEntry->mId, value);
                            }
                        }
                        callback(channel, pEntry->mId, value);
                    }
                }
                pEntry++;
            }
        }
    } else if (channel == (unsigned int)-1) {
        for (channel = 0; channel < lbl_803ECED8; channel++) {
            if ((error = fn_801C60BC(channel)) != 0) {
                break;
            }
        }
    } else {
        error = 0x1A0003;
    }
    fn_801F7BD4(error);
    return error;
}

int fn_801C6280(unsigned int channel, unsigned int type, unsigned int value)
{
    int error = 0;

    if (!lbl_803EBBEC) {
        error = 0x1A0002;
    } else if (channel < lbl_803ECED8) {
        switch (type) {
        case 0:
            lbl_803EBBF0[channel].mMapping = value;
            fn_801C5B9C(channel);
            break;
        case 1:
            lbl_803EBBF0[channel].mpCallback = (ConCallback_801C5B9C)value;
            break;
        case 2:
            lbl_803EBBF0[channel].mpUpdate = (ConUpdate_801C5B9C)value;
            break;
        case 4:
            if (!value) {
                lbl_803EBBF0[channel].mFlags &= ~1;
            } else {
                lbl_803EBBF0[channel].mFlags |= 1;
            }
            fn_801C5B9C(channel);
            break;
        case 3:
            lbl_803EBBF0[channel].mpEntries = (ConEntry_801C5B9C *)value;
            fn_801C5C58((ConEntry_801C5B9C *)value);
            break;
        case 5:
            if (!value) {
                lbl_803EBBF0[channel].mFlags &= ~0x100;
            } else {
                lbl_803EBBF0[channel].mFlags |= 0x100;
            }
            break;
        default:
            error = 0x1A0003;
            break;
        }
    } else if (channel == (unsigned int)-1) {
        for (channel = 0; channel < lbl_803ECED8; channel++) {
            if (!(lbl_803EBBF0[channel].mFlags & 0x100)) {
                if ((error = fn_801C6280(channel, type, value)) != 0) {
                    break;
                }
            }
        }
    } else {
        error = 0x1A0003;
    }
    fn_801F7BD4(error);
    return error;
}

unsigned int fn_801C6458(unsigned int channel, unsigned int type)
{
    unsigned int value = 0;
    int error = 0;

    if (!lbl_803EBBEC) {
        error = 0x1A0002;
    } else if (channel < lbl_803ECED8) {
        switch (type) {
        case 0:
            value = lbl_803EBBF0[channel].mMapping;
            break;
        case 1:
            value = (unsigned int)lbl_803EBBF0[channel].mpCallback;
            break;
        case 2:
            value = (unsigned int)lbl_803EBBF0[channel].mpUpdate;
            break;
        case 4:
            if (lbl_803EBBF0[channel].mFlags & 1) {
                value = 1;
            }
            break;
        case 3:
            value = (unsigned int)lbl_803EBBF0[channel].mpEntries;
            break;
        case 5:
            if (lbl_803EBBF0[channel].mFlags & 0x100) {
                value = 1;
            }
            break;
        default:
            error = 0x1A0003;
            break;
        }
    } else {
        error = 0x1A0003;
    }
    fn_801F7BD4(error);
    return value;
}

int fn_801C657C(void)
{
    return lbl_803ED624;
}
