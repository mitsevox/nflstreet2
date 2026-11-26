/* Controller context: channels of mapped input buffers, processed through dead-zone entry tables into callbacks. */

#include "engine/SysSetLastErrorFunc.h"
#include "engine/SysCriticalSection.h"
#include "game/fn_801D2B7C.h"
#include <string.h>

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

static unsigned char _Context_ModuleActive = 0;

/* The context channels, and the message callback. */
static ConChannel_t *_pCon_Channel = 0;
static ConCallback_t _Con_pMsgFunc = 0;

/* The channel count, the bytes of each channel's current and previous data, and that data. */
static unsigned int _Con_NumChannels;
static unsigned int _Con_DataSize;
static char *_pCon_Data;

static SysCriticalSection_t _Context_CS;

int _Con_CurrentContext;

int MemFill(void *pDest, int size, int value, int width);

static void _ConClearChannel(unsigned int channel)
{
    if (_Context_ModuleActive && _pCon_Channel) {
        memset(_pCon_Channel[channel].mpCur, 0, _Con_DataSize);
        memset(_pCon_Channel[channel].mpPrev, 0, _Con_DataSize);
    }
}

static void _ConUpdateChannel(unsigned int channel)
{
    if ((_pCon_Channel[channel].mFlags & 1) && _pCon_Channel[channel].mpUpdate) {
        _pCon_Channel[channel].mpUpdate(channel, _pCon_Channel[channel].mpPrev, _pCon_Channel[channel].mpCur);
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

    if (!_Context_ModuleActive) {
        SysInitCriticalSectionFunc(&_Context_CS);
        SysEnterCriticalSectionFunc(&_Context_CS);
        _Con_pMsgFunc = 0;
        _Con_NumChannels = count;
        _pCon_Channel = fn_801D2BB0(1, count * sizeof(ConChannel_t), 0, 0);
        if (!_pCon_Channel) {
            error = SysGetLastError();
        } else {
            _Con_DataSize = size * sizeof(float);
            _pCon_Data = fn_801D2BB0(1, count * (_Con_DataSize + _Con_DataSize), 0, 0);
            if (!_pCon_Data) {
                fn_801D2BD0(_pCon_Channel);
                error = SysGetLastError();
            } else {
                MemFill(_pCon_Data, count * (_Con_DataSize + _Con_DataSize), 0, 4);
                MemFill(_pCon_Channel, count * sizeof(ConChannel_t), 0, 4);
                for (i = 0; i < _Con_NumChannels; i++) {
                    _pCon_Channel[i].mpCur = (float *)(_pCon_Data + i * (_Con_DataSize + _Con_DataSize));
                    _pCon_Channel[i].mpPrev = (float *)(_pCon_Data + i * (_Con_DataSize + _Con_DataSize) + _Con_DataSize);
                    _pCon_Channel[i].mFlags = 0;
                    _pCon_Channel[i].mMapping = -1;
                    _pCon_Channel[i].mpEntries = 0;
                    _pCon_Channel[i].mpCallback = 0;
                    _pCon_Channel[i].mpUpdate = 0;
                }
                _Context_ModuleActive = 1;
            }
        }
        SysExitCriticalSectionFunc(&_Context_CS);
    } else {
        error = 0x1A0001;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int ConShutdown(void)
{
    int error = 0;

    if (_Context_ModuleActive) {
        SysEnterCriticalSectionFunc(&_Context_CS);
        fn_801D2BD0(_pCon_Data);
        fn_801D2BD0(_pCon_Channel);
        _pCon_Channel = 0;
        SysExitCriticalSectionFunc(&_Context_CS);
        SysShutdownCriticalSectionFunc(&_Context_CS);
        _Context_ModuleActive = 0;
    } else {
        error = 0x1A0002;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int ConUpdateChannel(unsigned int channel)
{
    int error = 0;

    if (!_Context_ModuleActive) {
        error = 0x1A0002;
    } else if (channel < _Con_NumChannels) {
        _ConUpdateChannel(channel);
    } else if (channel == (unsigned int)-1) {
        for (channel = 0; channel < _Con_NumChannels; channel++) {
            _ConUpdateChannel(channel);
        }
    } else {
        error = 0x1A0003;
    }
    SysSetLastErrorFunc(error);
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

    if (!_Context_ModuleActive) {
        error = 0x1A0002;
    } else if (channel < _Con_NumChannels) {
        pEntry = _pCon_Channel[channel].mpEntries;
        mapping = _pCon_Channel[channel].mMapping;
        pCur = _pCon_Channel[channel].mpCur;
        pPrev = _pCon_Channel[channel].mpPrev;
        callback = _pCon_Channel[channel].mpCallback;
        if (pEntry && (_pCon_Channel[channel].mFlags & 1)) {
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
                        if (_Con_pMsgFunc) {
                            if (pEntry->mFlags) {
                                _Con_pMsgFunc(channel, pEntry->mId, value);
                            } else {
                                _Con_pMsgFunc(-1, pEntry->mId, value);
                            }
                        }
                        callback(channel, pEntry->mId, value);
                    }
                }
                pEntry++;
            }
        }
    } else if (channel == (unsigned int)-1) {
        for (channel = 0; channel < _Con_NumChannels; channel++) {
            if ((error = ConProcessChannel(channel)) != 0) {
                break;
            }
        }
    } else {
        error = 0x1A0003;
    }
    SysSetLastErrorFunc(error);
    return error;
}

int ConSetChannelInfo(unsigned int channel, unsigned int type, unsigned int value)
{
    int error = 0;

    if (!_Context_ModuleActive) {
        error = 0x1A0002;
    } else if (channel < _Con_NumChannels) {
        switch (type) {
        case 0:
            _pCon_Channel[channel].mMapping = value;
            _ConClearChannel(channel);
            break;
        case 1:
            _pCon_Channel[channel].mpCallback = (ConCallback_t)value;
            break;
        case 2:
            _pCon_Channel[channel].mpUpdate = (ConUpdate_t)value;
            break;
        case 4:
            if (!value) {
                _pCon_Channel[channel].mFlags &= ~1;
            } else {
                _pCon_Channel[channel].mFlags |= 1;
            }
            _ConClearChannel(channel);
            break;
        case 3:
            _pCon_Channel[channel].mpEntries = (ConEntry_t *)value;
            _ConPatchInverseDeadZone((ConEntry_t *)value);
            break;
        case 5:
            if (!value) {
                _pCon_Channel[channel].mFlags &= ~0x100;
            } else {
                _pCon_Channel[channel].mFlags |= 0x100;
            }
            break;
        default:
            error = 0x1A0003;
            break;
        }
    } else if (channel == (unsigned int)-1) {
        for (channel = 0; channel < _Con_NumChannels; channel++) {
            if (!(_pCon_Channel[channel].mFlags & 0x100)) {
                if ((error = ConSetChannelInfo(channel, type, value)) != 0) {
                    break;
                }
            }
        }
    } else {
        error = 0x1A0003;
    }
    SysSetLastErrorFunc(error);
    return error;
}

unsigned int ConGetChannelInfo(unsigned int channel, unsigned int type)
{
    unsigned int value = 0;
    int error = 0;

    if (!_Context_ModuleActive) {
        error = 0x1A0002;
    } else if (channel < _Con_NumChannels) {
        switch (type) {
        case 0:
            value = _pCon_Channel[channel].mMapping;
            break;
        case 1:
            value = (unsigned int)_pCon_Channel[channel].mpCallback;
            break;
        case 2:
            value = (unsigned int)_pCon_Channel[channel].mpUpdate;
            break;
        case 4:
            if (_pCon_Channel[channel].mFlags & 1) {
                value = 1;
            }
            break;
        case 3:
            value = (unsigned int)_pCon_Channel[channel].mpEntries;
            break;
        case 5:
            if (_pCon_Channel[channel].mFlags & 0x100) {
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
    SysSetLastErrorFunc(error);
    return value;
}

int ConGetCurrentContext(void)
{
    return _Con_CurrentContext;
}
