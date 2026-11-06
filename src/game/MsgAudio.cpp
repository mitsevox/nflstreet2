/* Audio part of the options screen: answers the screen's open, close, select, get and
   set messages for the sound settings, plays a preview sample from uisound.dat while one
   of the sound options is highlighted, pauses or resumes the music to match, and applies a
   changed widescreen setting when the screen closes. */
#include "game/FELoop.h"
#include "game/Object_80039F5C.h"
#include "engine/viewporttypes.h"
#include "game/OptionsScreen.h"
#include "game/fn_80072AA8.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801F40F4.h"
#include "game/fn_8021D7B8.h"

struct OptAudioArgs_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
int fn_8006D65C(int idx);
void fn_8006D670(int idx, int handle);
void fn_8006D6F4(int idx, int a, int volume);
void fn_8006D758(int idx, Vector_80039F5C *pos);
void fn_8006D8DC(int idx);
unsigned char fn_80072ACC(void);
void fn_80072B84(int a, int b, int c);
void fn_80072E84(void);
void fn_80072F04(void);
unsigned char fn_80072F84(void);
void fn_80073094(void);
void SpchIGPauseChannel(int index);
void SpchIGResumeChannel(int index);
void SpchIGPurgeChannel(int a);
int SpchIGIsChannelIdle(int index);
int SpchIGGetChannelStream(unsigned int index);
void fn_8013CF98(void);
void UISGameSetAspect(Viewport_t *pObject, int mode);
Viewport_t *UISGameGetMainViewport(void);
int fn_801F48B8(int handle);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);

extern void *gUISMainInfo;
extern char lbl_802EBFCC[];

void OptAudioOnOptionChanged(int mode, int flag);
}

static unsigned char _OptAudio_bMusicOn = 1;
static void *_OptAudio_hSoundRes = (void *)-1;
static int _OptAudio_iPreviewSample = -1;
static unsigned char _OptAudio_uPreviewChannel = 9;
static int _OptAudio_iSavedOption6 = 3;
static int _OptAudio_iStreamSet = 0;
static int _OptAudio_iSelOption = -1;
static unsigned char _OptAudio_bHasTracks;

extern "C" {
void OptAudioStartPreview(int mode)
{
    if (mode != 10) {
        if (_OptAudio_bMusicOn != 0) {
            fn_80072E84();
            _OptAudio_bMusicOn = 0;
        }
        switch (mode) {
        case 8:
            _OptAudio_iPreviewSample = 2;
            if (_OptAudio_iStreamSet == 0) {
                _OptAudio_uPreviewChannel = 4;
            } else {
                _OptAudio_uPreviewChannel = 5;
            }
            break;
        case 9:
            _OptAudio_iPreviewSample = 3;
            _OptAudio_uPreviewChannel = 1;
            break;
        default:
            return;
        }
        fn_8006D8DC(_OptAudio_uPreviewChannel);
        fn_8006D758(_OptAudio_uPreviewChannel, 0);
        fn_8006D6F4(_OptAudio_uPreviewChannel, 0, 127);
    }
}

void OptAudioStopPreview(void)
{
    if (_OptAudio_bMusicOn == 0) {
        if (_OptAudio_iPreviewSample != -1) {
            _OptAudio_iPreviewSample = -1;
            fn_8006D8DC(_OptAudio_uPreviewChannel);
        }
        if (FELoopIsMainFEActive() != 0 || _OptAudio_iSelOption == 10) {
            if (fn_8007F828(OptionsScreenGetOptionId(10)) > 0) {
                fn_80072F04();
                _OptAudio_bMusicOn = 1;
            }
        }
    }
}

void OptAudioSetOption(int mode, int value, int notify)
{
    int flag = 0;
    int index = OptionsScreenGetOptionId(mode);

    if (index != 24) {
        if (fn_8007F828(index) == 0 && value != 0) {
            flag = 1;
        }
        fn_8007F6F8(index, value);
        if (notify == 1) {
            OptAudioOnOptionChanged(mode, flag);
        }
    }
}

int OptAudioGetOption(int mode)
{
    int result = 0;
    int index = OptionsScreenGetOptionId(mode);

    if (index != 24) {
        result = fn_8007F828(index);
    }
    return result;
}

void OptAudioSelectOption(int mode)
{
    if (OptionsScreenGetOptionId(mode) != 24) {
        _OptAudio_iSelOption = mode;
        if (mode >= 8 && mode <= 10) {
            if (mode == 10) {
                OptAudioStopPreview();
                if (_OptAudio_bHasTracks == 0) {
                    fn_80072B84(1, 0, 1);
                }
            } else {
                OptAudioStartPreview(mode);
            }
        } else {
            OptAudioStopPreview();
            if (FELoopIsMainFEActive() == 0) {
                fn_80072E84();
                _OptAudio_bMusicOn = 0;
            }
            if (_OptAudio_bHasTracks == 0) {
                fn_80073094();
            }
        }
    } else {
        if (_OptAudio_iPreviewSample != -1) {
            _OptAudio_iPreviewSample = -1;
            fn_8006D8DC(_OptAudio_uPreviewChannel);
        }
        fn_80072E84();
        _OptAudio_bMusicOn = 0;
    }
}

void OptAudioClose(void)
{
    int value;

    OptAudioStopPreview();
    if (_OptAudio_iSavedOption6 != fn_8007F828(6)) {
        if (fn_8007F828(6) == 0) {
            value = 0;
        } else {
            value = 1;
        }
        fn_8021D7B8(gUISMainInfo, 0x8000000F, 1, &value);
        if (fn_8007F828(6) == 1) {
            UISGameSetAspect(UISGameGetMainViewport(), 0);
        } else {
            UISGameSetAspect(UISGameGetMainViewport(), fn_8007F828(6));
        }
        fn_8013CF98();
    }
    if (_OptAudio_bHasTracks == 0) {
        fn_80073094();
    }
    fn_8006D670(1, 0);
    if (FELoopIsMainFEActive() == 0) {
        SpchIGPauseChannel(_OptAudio_iStreamSet);
        fn_80072E84();
    } else if (_OptAudio_bHasTracks != 0) {
        fn_80072F04();
    }
    fn_801EEFAC(_OptAudio_hSoundRes);
    _OptAudio_hSoundRes = (void *)-1;
    _OptAudio_iPreviewSample = -1;
}

void OptAudioOpen(void)
{
    int result;

    _OptAudio_iPreviewSample = -1;
    result = FELoopIsMainFEActive();
    _OptAudio_bMusicOn = 0;
    fn_80072E84();
    _OptAudio_iSavedOption6 = fn_8007F828(6);
    _OptAudio_hSoundRes = fn_801EEB44(lbl_802EBFCC, 44);
    if (result != 0 || SpchIGIsChannelIdle(0) != 0) {
        _OptAudio_iStreamSet = 0;
    } else {
        _OptAudio_iStreamSet = 1;
    }
    SpchIGPurgeChannel(_OptAudio_iStreamSet);
    SpchIGResumeChannel(_OptAudio_iStreamSet);
    fn_8006D670(1, SpchIGGetChannelStream(_OptAudio_iStreamSet));
    _OptAudio_bHasTracks = fn_80072ACC() != 0;
}

void OptAudioOnOptionChanged(int mode, int flag)
{
    if (mode >= 8 && mode <= 10) {
        if (flag != 0) {
            if (mode == 10) {
                if (_OptAudio_bHasTracks != 0) {
                    if (fn_80072F84() != 0) {
                        fn_80072F04();
                    } else {
                        fn_80072F90();
                    }
                } else {
                    fn_80072B84(1, 0, 1);
                }
            }
            _OptAudio_bMusicOn = 1;
            OptAudioStartPreview(mode);
        } else if (fn_8007F828(OptionsScreenGetOptionId(mode)) == 0 && mode == 10) {
            if (_OptAudio_bHasTracks == 0) {
                fn_80073094();
            } else {
                fn_80072E84();
            }
        }
    }
}

int OptAudioHandleMessage(unsigned int id, OptAudioArgs_t *pParams, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        OptAudioOpen();
        break;
    case 0x80000002:
        OptAudioClose();
        break;
    case 0x80000003:
        OptAudioSelectOption(pParams->mUnknown0);
        break;
    case 0x80000004:
        *pResult = OptAudioGetOption(pParams->mUnknown0);
        break;
    case 0x80000005:
        OptAudioSetOption(pParams->mUnknown0, pParams->mUnknown4, pParams->mUnknown8);
        break;
    default:
        return 0;
    }
    return 1;
}

void OptAudioUpdate(int unknown)
{
    Status_801F4834 status;
    unsigned short a;
    unsigned short b;
    SndStreamFile_t pair;

    if (_OptAudio_iPreviewSample != -1) {
        fn_80219650(gUISMainInfo, &a, &b);
        if ((a == 5 && b == 5) || (a == 3 && b == 11)) {
            fn_8006D6F4(_OptAudio_uPreviewChannel, 0, 127);
            fn_801F4834(fn_8006D65C(_OptAudio_uPreviewChannel), &status);
            if (status.mUnknown0 <= 0 && fn_801F48B8(fn_8006D65C(_OptAudio_uPreviewChannel)) != 0) {
                pair.mpUnknown0 = _OptAudio_hSoundRes;
                pair.mUnknown4 = _OptAudio_iPreviewSample;
                fn_801F4580(fn_8006D65C(_OptAudio_uPreviewChannel), &pair, 0, 0);
            }
        } else {
            fn_8006D6F4(_OptAudio_uPreviewChannel, 0, 0);
        }
    }
}
}
