/* The in-game speech system: loads the commentary data and banks, decides which player a line is
   about, streams spoken lines on two commentary channels and a narrator channel, places them on the
   speaking player and pauses, stops or purges them on request. */

#include "game/AudmonEvent.h"
#include "game/fn_8007F828.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_80178D18.h"
#include "game/GameModeType.h"
#include "game/ResOpenDevice.h"
#include "game/fn_801F40F4.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include "game/Object_80039F5C.h"
#include "engine/spchevnt.h"

/* Block passed to fn_801F5B30; its first word holds SpchIGSampleRequest. */
struct SpchIGInitParams_t {
    int (*mpUnknown0)(struct SpchIGSampleRequest_t *);
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
};

/* Record passed to SpchIGSampleRequest. */
struct SpchIGSampleRequest_t {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[4];
    unsigned short mUnknownC;
    char mUnknownE[2];
    int mUnknown10;
};

struct SpchIGEventInfo_t {
    unsigned short mId;
    char mUnknown2[1];
    unsigned char mUnknown3;
};

struct SpchIGChannel_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

struct SpchIGState_t {
    int mUnknown0;
    void *mpUnknown4;
    void *mpUnknown8;
    int mUnknownC;
    SpchIGChannel_t mSlots[3];
};

extern "C" {
extern char lbl_802EBE04[];

int SndgChannelGetStream(int a);
void SndgChannelSetVolume(int idx, unsigned char percent);
void SndgChannelFadeStream(int a, int b, int c);
void SndgChannelSetPosition(int a, Vector_80039F5C *pPos);
void SndgSetVolumeOption(int a, unsigned char b);
void SndgSpchHandleEvent(AudmonEvent_t *pRecord);
void SndgSpchClearPlayFlags(int a);
int SpchIGGetSceneSpeaker(void);
unsigned char SpchIGIsSceneLineActive(void);
int SpchIGGetWallTacklePlayer(void);
int SpchIGGetReceiverOpenPlayer(void);
int SpchIGGetStylingPlayer(void);
int SpchIGGetMissedCatchPlayer(void);
int SpchIGGetStruggleCarrier(void);
int SpchIGGetStruggleTackler(void);
int SpchIGGetTackler(void);
int SpchIGGetPassTarget(void);
int SpchIGGetPassCatcher(void);
int SpchIGGetBallCarrier(void);
int SpchIGGetTurnoverPlayer(void);
int SpchIGGetScorer(void);
int SpchIGGetTeamSceneSpeaker(int index);
void *ResOpenRam(void *pData, int a, int b, int c);
void fn_801F4638(int handle);
void fn_801F46F8(int handle, int a);
void fn_801F4AB0(int a, int b);
void fn_801F5B30(SpchIGInitParams_t *pParams);
void fn_801F5C34(void);
void fn_801F5C6C(void *a, int b, void *c, int d);
void fn_801F5C94(void *pData, int a, int b);
void fn_801F5CCC(int (*pA)(void), void (*pB)(void));
void fn_801F5CEC(int (*pFunc)(SpchIGEventInfo_t *));
void fn_801F5D0C(void);

int SpchIGSampleRequest(SpchIGSampleRequest_t *pRecord);
int SpchIGGetNearestOpponent(int side);
int SpchIGGetTeamPlayer(int side);
void SpchIGSetUseSpeakerPos(unsigned char value);
void SpchIGSetChannelSpeaker(int index, int value);
int SpchIGGetChannelSpeaker(int index);
int SpchIGIsChannelIdle(int index);
int SpchIGGetChannelStream(unsigned int index);
}

static unsigned char _SpchIG_bActive = 0;
static unsigned char _SpchIG_bEnabled = 1;
static unsigned char _SpchIG_bTutorial = 0;
static unsigned char _SpchIG_bCommentaryOn = 1;
static int _SpchIG_iLastSpeakerEvent = 0;
static unsigned char _SpchIG_bUseSpeakerPos = 1;
static int _SpchIG_iNearestOpponent1 = 0;
static int _SpchIG_iNearestOpponent0 = 0;
static int _SpchIG_iTeamPlayer1 = 0;
static int _SpchIG_iTeamPlayer0 = 0;

static int _SpchIG_iBankCount;

static SpchIGState_t _SpchIG_sState;
static unsigned short _SpchIG_aBankRemap[386];

static SpchIGInitParams_t _SpchIG_sInitParams = { SpchIGSampleRequest, 0, 24000, 16, 1, 4084, 0, 0, 0 };

extern "C" void SpchIGLoadBank(void *a, int b, void *c, int d)
{
    fn_801F5C6C(a, b, c, d);
}

extern "C" int SpchIGGetEventSpeaker(int side, unsigned int id)
{
    int result;

    switch (id) {
    case 0x201C:
    case 0x401C:
        result = SpchIGGetWallTacklePlayer();
        break;
    case 0x201D:
    case 0x401D:
        result = SpchIGGetStylingPlayer();
        break;
    case 0x2006:
    case 0x4006:
        result = SpchIGGetPassTarget();
        break;
    case 0x2014:
    case 0x2019:
    case 0x4014:
    case 0x4019:
        result = SpchIGGetNearestOpponent(side);
        break;
    case 0x2020:
    case 0x4020:
        result = SpchIGGetMissedCatchPlayer();
        break;
    case 0x2021:
    case 0x4021:
        result = SpchIGGetStruggleCarrier();
        break;
    case 0x2022:
    case 0x4022:
        result = SpchIGGetStruggleTackler();
        break;
    case 0x2004:
    case 0x4004:
        result = SpchIGGetReceiverOpenPlayer();
        break;
    case 0x2005:
    case 0x4005:
        result = SpchIGGetPassCatcher();
        break;
    case 0x2007:
    case 0x4007:
        result = SpchIGGetBallCarrier();
        break;
    case 0x2008:
    case 0x4008:
        result = SpchIGGetScorer();
        if (result != 0) {
            break;
        }
        result = SpchIGGetTeamPlayer(side);
        break;
    case 0x200F:
    case 0x2010:
    case 0x2013:
    case 0x2015:
    case 0x400F:
    case 0x4010:
    case 0x4013:
    case 0x4015:
        result = SpchIGGetTackler();
        if (result != 0) {
            break;
        }
        result = SpchIGGetTeamPlayer(side);
        break;
    case 0x2017:
    case 0x4017:
        result = SpchIGGetTurnoverPlayer();
        if (result != 0) {
            break;
        }
        result = SpchIGGetTeamPlayer(side);
        break;
    case 0x2002:
    case 0x2003:
    case 0x2009:
    case 0x200B:
    case 0x200C:
    case 0x2012:
    case 0x2016:
    case 0x2018:
    case 0x201A:
    case 0x201B:
    case 0x2023:
    case 0x2024:
    case 0x2025:
    case 0x2026:
    case 0x2027:
    case 0x2028:
    case 0x2029:
    case 0x202A:
    case 0x202B:
    case 0x202C:
    case 0x202D:
    case 0x202E:
    case 0x4002:
    case 0x4003:
    case 0x4009:
    case 0x400B:
    case 0x400C:
    case 0x4012:
    case 0x4016:
    case 0x4018:
    case 0x401A:
    case 0x401B:
    case 0x4023:
    case 0x4024:
    case 0x4025:
    case 0x4026:
    case 0x4027:
    case 0x4028:
    case 0x4029:
    case 0x402A:
    case 0x402B:
    case 0x402C:
    case 0x402D:
    case 0x402E:
        result = SpchIGGetTeamPlayer(side);
        break;
    case 0x201E:
    case 0x401E:
        if (fn_800AD9B4() == 1) {
            if (id == 0x401E) {
                result = SpchIGGetTeamSceneSpeaker(0);
            } else {
                result = SpchIGGetTeamSceneSpeaker(1);
            }
        } else {
            result = SpchIGGetSceneSpeaker();
        }
        break;
    default:
        result = SpchIGGetTeamPlayer(side);
        break;
    }
    return result;
}

extern "C" void SpchIGAssignChannelSpeaker(unsigned int index, int id)
{
    int side;
    int value;

    if (index <= 1) {
        side = 1;
        if (index == 1) {
            side = 0;
        }
        if (id != _SpchIG_iLastSpeakerEvent) {
            value = SpchIGGetEventSpeaker(side, id);
            if (value == 0) {
                value = SpchIGGetTeamPlayer(side);
            }
            SpchIGSetChannelSpeaker(index, value);
            _SpchIG_iLastSpeakerEvent = id;
        }
        if (id == 0x201E || id == 0x401E) {
            SpchIGSetUseSpeakerPos(0);
        } else {
            SpchIGSetUseSpeakerPos(1);
        }
    }
}

extern "C" int SpchIGGetStreamFlags(int id)
{
    int result = 0;

    if (id == 0x201E || id == 0x401E) {
        result = -1;
    }
    return result;
}

extern "C" int SpchIGCanPlayEvent(SpchIGEventInfo_t *pEvent)
{
    int current;
    int side;

    if (pEvent->mUnknown3 != 3) {
        current = SpchIGGetSceneSpeaker();
        side = 1;
        if (pEvent->mUnknown3 == 1) {
            side = 0;
        }
        if (SpchIGIsSceneLineActive() != 0 || current == SpchIGGetEventSpeaker(side, pEvent->mId)) {
            if (pEvent->mId != 0x401E && pEvent->mId != 0x201E) {
                return 0;
            }
        }
    }
    return 1;
}

extern "C" int SpchIGSampleRequest(SpchIGSampleRequest_t *pRecord)
{
    SndStreamFile_t pair;
    int handle;
    int value;

    SpchIGAssignChannelSpeaker((unsigned char)pRecord->mUnknown10, pRecord->mUnknownC);
    pair.mpUnknown0 = _SpchIG_sState.mpUnknown4;
    if (pRecord->mUnknown0 >= _SpchIG_iBankCount) {
        pair.mUnknown4 = _SpchIG_aBankRemap[pRecord->mUnknown0 - _SpchIG_iBankCount];
    } else {
        pair.mUnknown4 = _SpchIG_sState.mUnknownC + pRecord->mUnknown0;
    }
    handle = SpchIGGetChannelStream(pRecord->mUnknown10);
    value = SpchIGGetStreamFlags(pRecord->mUnknownC);
    _SpchIG_sState.mSlots[pRecord->mUnknown10].mUnknown8 = value;
    _SpchIG_sState.mSlots[pRecord->mUnknown10].mUnknown4 = fn_801F4580(handle, &pair, value, pRecord->mUnknown4);
    return _SpchIG_sState.mSlots[pRecord->mUnknown10].mUnknown4;
}

extern "C" int SpchIGStubQuery(void)
{
    return 0;
}

extern "C" void SpchIGStubNotify(void)
{
}

extern "C" void SpchIGLoadChatData(SpchIGInitParams_t *pParams, int unused)
{
    int i;

    _SpchIG_bTutorial = GameModeTypeGet() == 11;
    _SpchIG_bUseSpeakerPos = 1;
    _SpchIG_sState.mpUnknown4 = ResOpenDevice(lbl_802EBE04, 44);
    _SpchIG_sState.mpUnknown8 = ResOpenRam(_SpchIG_sState.mpUnknown4, 0, 1, 1);
    fn_801F5B30(pParams);
    fn_801F5CEC(SpchIGCanPlayEvent);
    _SpchIG_sState.mUnknown0 = pParams->mUnknown14;
    fn_801F5C94(_SpchIG_sState.mpUnknown4, 1, 0);
    fn_801F5C94(_SpchIG_sState.mpUnknown4, 2, 1);
    fn_801F5C94(_SpchIG_sState.mpUnknown4, 3, 2);
    for (i = 0; i < 895; i++) {
        SpchIGLoadBank(_SpchIG_sState.mpUnknown8, i, _SpchIG_sState.mpUnknown4, i + 4);
    }
    _SpchIG_iBankCount = i;
    _SpchIG_sState.mUnknownC = 4;
    for (i = 0; i < 3; i++) {
        _SpchIG_sState.mSlots[i].mUnknown0 = 0;
        _SpchIG_sState.mSlots[i].mUnknown4 = -1;
        _SpchIG_sState.mSlots[i].mUnknown8 = 0;
    }
    _SpchIG_iNearestOpponent1 = 0;
    _SpchIG_iNearestOpponent0 = 0;
    _SpchIG_iTeamPlayer1 = 0;
    _SpchIG_iTeamPlayer0 = 0;
}

extern "C" void SpchIGStart(void)
{
    _SpchIG_sInitParams.mUnknown4 = (_SpchIG_sInitParams.mUnknown4 + 1) & 0x7FFFFFFF;
    SpchIGLoadChatData(&_SpchIG_sInitParams, 1);
    fn_801F5CCC(SpchIGStubQuery, SpchIGStubNotify);
    SndgSpchClearPlayFlags(127);
    AudmonEventAddListener(SndgSpchHandleEvent);
    _SpchIG_bActive = 1;
    _SpchIG_bEnabled = 1;
}

extern "C" void SpchIGInitFrontEnd(void)
{
}

extern "C" void SpchIGUpdate(void)
{
    Status_801F4834 status;
    Vector_80039F5C pos;
    int handle;
    int first;
    int second;
    int id;

    if (_SpchIG_bEnabled == 0) {
        return;
    }
    first = 0;
    second = 0;
    if (fn_800AD9B4() == 1) {
        first = SpchIGGetTeamSceneSpeaker(0);
        second = SpchIGGetTeamSceneSpeaker(1);
    } else if (SpchIGIsSceneLineActive() != 0) {
        id = SpchIGGetSceneSpeaker();
        if (id != 0) {
            if (((id >> 8) & 0xFF) == 0) {
                second = id;
                first = 0;
            } else {
                first = id;
            }
        }
    }
    SndgSetVolumeOption(3, fn_8007F828(3) * 10);
    if (first != 0) {
        SndgChannelSetVolume(4, 95);
    }
    if (second != 0) {
        SndgChannelSetVolume(5, 95);
    }

    fn_801F4834(SpchIGGetChannelStream(0), &status);
    SndgChannelSetPosition(4, 0);
    if (_SpchIG_bUseSpeakerPos != 0) {
        handle = SpchIGGetChannelSpeaker(0);
        if (handle != 0) {
            fn_8009BF5C(fn_8009BCE8(&handle), 13, &pos, 0);
            SndgChannelSetPosition(4, &pos);
        }
    }
    SndgChannelFadeStream(4, 0, 127);
    if (status.mUnknown0 == 0) {
        fn_801AF364(0);
    }

    fn_801F4834(SpchIGGetChannelStream(1), &status);
    SndgChannelSetPosition(5, 0);
    if (_SpchIG_bUseSpeakerPos != 0) {
        handle = SpchIGGetChannelSpeaker(1);
        if (handle != 0) {
            fn_8009BF5C(fn_8009BCE8(&handle), 13, &pos, 0);
            SndgChannelSetPosition(5, &pos);
        }
    }
    SndgChannelFadeStream(5, 0, 127);
    if (status.mUnknown0 == 0) {
        fn_801AF364(1);
    }

    if (_SpchIG_bTutorial != 0) {
        fn_801F4834(SpchIGGetChannelStream(2), &status);
        SndgChannelSetPosition(6, 0);
        SndgChannelFadeStream(6, 0, 127);
        if (status.mUnknown0 == 0) {
            fn_801AF364(2);
        }
    }
}

extern "C" void SpchIGUpdateFrontEnd(void)
{
}

extern "C" void SpchIGStop(void)
{
    _SpchIG_bActive = 0;
    _SpchIG_bTutorial = 0;
    AudmonEventRemoveListener(SndgSpchHandleEvent);
    fn_801F5D0C();
    fn_801F5C34();
    if (_SpchIG_sState.mpUnknown8 != 0) {
        ResClose(_SpchIG_sState.mpUnknown8);
        _SpchIG_sState.mpUnknown8 = 0;
    }
    if (_SpchIG_sState.mpUnknown4 != 0) {
        ResClose(_SpchIG_sState.mpUnknown4);
        _SpchIG_sState.mpUnknown4 = 0;
    }
}

extern "C" void SpchIGPauseChannel(int index)
{
    if (SpchIGGetChannelStream(index) != 0) {
        fn_801F46F8(SpchIGGetChannelStream(index), 0);
    }
}

extern "C" void SpchIGResumeChannel(int index)
{
    Info_801F40F4 info;

    fn_801F40F4(&info);
    if (SpchIGGetChannelStream(index) != 0) {
        fn_801F46F8(SpchIGGetChannelStream(index), info.mUnknownC);
    }
}

extern "C" void SpchIGStopChannel(int index)
{
    Status_801F4834 status;

    if (SpchIGGetChannelStream(index) != 0) {
        fn_801F4834(SpchIGGetChannelStream(index), &status);
        if (status.mUnknown0 > 0) {
            _SpchIG_sState.mSlots[index].mUnknown8 = 0;
            fn_801F4AB0(status.mUnknown4, 0);
            _SpchIG_sState.mSlots[index].mUnknown4 = -1;
        }
    }
}

extern "C" void SpchIGSetUseSpeakerPos(unsigned char value)
{
    _SpchIG_bUseSpeakerPos = value;
}

extern "C" void SpchIGSetChannelSpeaker(int index, int value)
{
    _SpchIG_sState.mSlots[index].mUnknown0 = value;
}

extern "C" int SpchIGGetChannelSpeaker(int index)
{
    return _SpchIG_sState.mSlots[index].mUnknown0;
}

extern "C" void SpchIGPurgeChannel(int index)
{
    if (SpchIGGetChannelStream(index) != 0) {
        fn_801F4638(SpchIGGetChannelStream(index));
    }
}

extern "C" void SpchIGFindNearestOpponent(int handle)
{
    Vector_80039F5C delta;
    Object_80039F5C *pObject;
    Object_80039F5C *pOther;
    int *pNearest;
    int team;
    unsigned short i;
    unsigned int count;
    float best;
    float distance;

    pObject = fn_8009BCE8(&handle);
    if (pObject != 0) {
        team = ((handle >> 8) & 0xFF) ^ 1;
        pNearest = &_SpchIG_iNearestOpponent1;
        if (team == 0) {
            pNearest = &_SpchIG_iNearestOpponent0;
        }
        pOther = PlyrGet(team, 0);
        *pNearest = pOther->mId;
        fn_802276B4(&delta, &pObject->mMotion.mPos, &pOther->mMotion.mPos);
        best = fn_802270D4(&delta);
        count = fn_80178D18(team);
        for (i = 1; i < count; i++) {
            pOther = PlyrGet(team, i);
            fn_802276B4(&delta, &pObject->mMotion.mPos, &pOther->mMotion.mPos);
            distance = fn_802270D4(&delta);
            if (distance < best) {
                best = distance;
                *pNearest = pOther->mId;
            }
        }
    }
}

extern "C" int SpchIGGetNearestOpponent(int side)
{
    return side ? _SpchIG_iNearestOpponent1 : _SpchIG_iNearestOpponent0;
}

extern "C" unsigned char SpchIGIsEnabled(void)
{
    return _SpchIG_bEnabled;
}

extern "C" void SpchIGSetEnabled(unsigned char value)
{
    _SpchIG_bEnabled = value;
}

extern "C" unsigned char SpchIGIsCommentaryOn(void)
{
    return _SpchIG_bCommentaryOn;
}

extern "C" void SpchIGSetCommentaryOn(unsigned char value)
{
    _SpchIG_bCommentaryOn = value;
}

extern "C" int SpchIGIsChannelIdle(int index)
{
    Status_801F4834 status;

    fn_801F4834(SpchIGGetChannelStream(index), &status);
    return status.mUnknown0 == 0;
}

extern "C" int SpchIGAreChannelsIdle(void)
{
    unsigned int i;

    for (i = 0; i < 3; i++) {
        if (SpchIGIsChannelIdle(i) == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" void SpchIGPickTeamPlayer(int side)
{
    int stream = fn_80178D70(side);

    if (side == 0) {
        _SpchIG_iTeamPlayer0 = 1 | (fn_802372EC(1, stream) & 0xFF) << 16;
    } else {
        _SpchIG_iTeamPlayer1 = side << 8 | 1 | (fn_802372EC(1, stream) & 0xFF) << 16;
    }
}

extern "C" int SpchIGGetTeamPlayer(int side)
{
    return side ? _SpchIG_iTeamPlayer1 : _SpchIG_iTeamPlayer0;
}

extern "C" int SpchIGGetChannelStream(unsigned int index)
{
    int result;

    switch (index) {
    case 0:
        result = SndgChannelGetStream(4);
        break;
    case 1:
        result = SndgChannelGetStream(5);
        break;
    case 2:
        result = SndgChannelGetStream(6);
        break;
    default:
        result = SndgChannelGetStream(4);
        break;
    }
    return result;
}

extern "C" int SpchIGIsNarratorIdle(void)
{
    int result = 1;

    if (_SpchIG_bEnabled != 0 && SpchIGIsChannelIdle(2) == 0) {
        result = 0;
    }
    return result;
}
