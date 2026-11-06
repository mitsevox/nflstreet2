/* Controller context: channels of mapped input buffers, processed through dead-zone entry tables into callbacks. */

#include "engine/fn_801F7BD4.h"
#include "engine/fn_801F8014.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"

typedef struct ConEntry_t {
    unsigned int mId;
    unsigned short mFlags;
    unsigned short mIndex;
    float mDeadZone;
    float mScale;
    float mInvDeadZone;
} ConEntry_t;

typedef void (*ConCallback_t)(unsigned int channel, unsigned int id, float value);
typedef void (*ConUpdate_t)(unsigned int channel, float *pPrev, float *pCur);

typedef struct ConChannel_t {
    unsigned int mFlags;
    int mMapping;
    ConEntry_t *mpEntries;
    ConCallback_t mpCallback;
    ConUpdate_t mpUpdate;
    float *mpCur;
    float *mpPrev;
} ConChannel_t;

extern unsigned char lbl_803EBBEC;
extern ConChannel_t *lbl_803EBBF0;
extern ConCallback_t lbl_803EBBF4;
extern unsigned int lbl_803ECED8;
extern unsigned int lbl_803ECEDC;
extern char *lbl_803ECEE0;
extern int lbl_803ED624;
extern Lock_801F8014 lbl_8037F860;

int MemFill(void *pDest, int size, int value, int width);

static void _ConClearChannel(unsigned int channel)
{
    if (lbl_803EBBEC && lbl_803EBBF0) {
        fn_801C1F94(lbl_803EBBF0[channel].mpCur, 0, lbl_803ECEDC);
        fn_801C1F94(lbl_803EBBF0[channel].mpPrev, 0, lbl_803ECEDC);
    }
}

static void _ConUpdateChannel(unsigned int channel)
{
    if ((lbl_803EBBF0[channel].mFlags & 1) && lbl_803EBBF0[channel].mpUpdate) {
        lbl_803EBBF0[channel].mpUpdate(channel, lbl_803EBBF0[channel].mpPrev, lbl_803EBBF0[channel].mpCur);
    }
}

static void _ConPatchInverseDeadZone(ConEntry_t *pEntry)
{
    while (pEntry->mFlags != 0x8000) {
        pEntry->mInvDeadZone = pEntry->mDeadZone != 0.0f ? 1.0f / (1.0f - pEntry->mDeadZone) : 0.0f;
        pEntry++;
    }
}

static inline float _ConAbs(float x)
{
    return __builtin_fabs(x);
}

static float _ConProcessContextEntry(ConEntry_t *pEntry, int mapping, float *pValues, unsigned char *pActive)
{
    float value;
    float deadZone;
    float offset;

    *pActive = 1;
    deadZone = pEntry->mDeadZone;
    value = pValues[pEntry->mIndex];
    if (!(deadZone <= 0.0f)) {
        if (!(_ConAbs(value) > deadZone)) {
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

int ConInit(unsigned int count, int size)
{
    int error = 0;
    unsigned int i;

    if (!lbl_803EBBEC) {
        fn_801F7FA8(&lbl_8037F860);
        fn_801F8014(&lbl_8037F860);
        lbl_803EBBF4 = 0;
        lbl_803ECED8 = count;
        lbl_803EBBF0 = fn_801D2BB0(1, count * sizeof(ConChannel_t), 0, 0);
        if (!lbl_803EBBF0) {
            error = fn_801F7C88();
        } else {
            lbl_803ECEDC = size * sizeof(float);
            lbl_803ECEE0 = fn_801D2BB0(1, count * (lbl_803ECEDC + lbl_803ECEDC), 0, 0);
            if (!lbl_803ECEE0) {
                fn_801D2BD0(lbl_803EBBF0);
                error = fn_801F7C88();
            } else {
                MemFill(lbl_803ECEE0, count * (lbl_803ECEDC + lbl_803ECEDC), 0, 4);
                MemFill(lbl_803EBBF0, count * sizeof(ConChannel_t), 0, 4);
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

int ConShutdown(void)
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

int ConUpdateChannel(unsigned int channel)
{
    int error = 0;

    if (!lbl_803EBBEC) {
        error = 0x1A0002;
    } else if (channel < lbl_803ECED8) {
        _ConUpdateChannel(channel);
    } else if (channel == (unsigned int)-1) {
        for (channel = 0; channel < lbl_803ECED8; channel++) {
            _ConUpdateChannel(channel);
        }
    } else {
        error = 0x1A0003;
    }
    fn_801F7BD4(error);
    return error;
}

int ConProcessChannel(unsigned int channel)
{
    int error = 0;
    unsigned char active = 0;
    unsigned char prevActive = 0;
    ConEntry_t *pEntry;
    ConCallback_t callback;
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
                value = _ConProcessContextEntry(pEntry, mapping, pCur, &active);
                if (active == 1) {
                    if (pEntry->mFlags & 8) {
                        prevValue = _ConProcessContextEntry(pEntry, mapping, pPrev, &prevActive);
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
            if ((error = ConProcessChannel(channel)) != 0) {
                break;
            }
        }
    } else {
        error = 0x1A0003;
    }
    fn_801F7BD4(error);
    return error;
}

int ConSetChannelInfo(unsigned int channel, unsigned int type, unsigned int value)
{
    int error = 0;

    if (!lbl_803EBBEC) {
        error = 0x1A0002;
    } else if (channel < lbl_803ECED8) {
        switch (type) {
        case 0:
            lbl_803EBBF0[channel].mMapping = value;
            _ConClearChannel(channel);
            break;
        case 1:
            lbl_803EBBF0[channel].mpCallback = (ConCallback_t)value;
            break;
        case 2:
            lbl_803EBBF0[channel].mpUpdate = (ConUpdate_t)value;
            break;
        case 4:
            if (!value) {
                lbl_803EBBF0[channel].mFlags &= ~1;
            } else {
                lbl_803EBBF0[channel].mFlags |= 1;
            }
            _ConClearChannel(channel);
            break;
        case 3:
            lbl_803EBBF0[channel].mpEntries = (ConEntry_t *)value;
            _ConPatchInverseDeadZone((ConEntry_t *)value);
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
                if ((error = ConSetChannelInfo(channel, type, value)) != 0) {
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

unsigned int ConGetChannelInfo(unsigned int channel, unsigned int type)
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

int ConGetCurrentContext(void)
{
    return lbl_803ED624;
}
