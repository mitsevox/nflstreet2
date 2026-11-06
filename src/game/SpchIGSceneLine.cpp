/* Plays the spoken line of a scripted character scene through the speech system, positioned on the
   speaking player, and stops it when the scene ends; also turns a tutorial lesson and drill into a
   single drill number for the narrator. */

#include "engine/spchevnt.h"

extern "C" {
void SpchIGStopChannel(int index);
void SpchIGPurgeChannel(int index);
void SpchIGGetPlayerCategory(int *pResult, int value);
void SpchIGGetTargetCategory(int *pResult, int value);
}

static int _SpchIG_iSceneSpeaker = 0;
static unsigned char _SpchIG_bSceneLineActive = 0;

extern "C" void SpchIGSaySceneLine(int a, int b, int c)
{
    int result1;
    int result2;

    _SpchIG_iSceneSpeaker = b;
    if (a == 999) {
        _SpchIG_bSceneLineActive = 0;
    } else {
        _SpchIG_bSceneLineActive = 1;
    }
    if (_SpchIG_bSceneLineActive) {
        SpchIGGetPlayerCategory(&result1, b);
        SpchIGGetTargetCategory(&result2, c);
        if ((unsigned char)(b >> 8) == 0) {
            SpchIGPurgeChannel(1);
            lbl_803EBB10(fn_801AE5D4(1, 0, 0x201E), 3, a, result1, result2);
            fn_801AF2CC(1);
        } else {
            SpchIGPurgeChannel(0);
            lbl_803EBB10(fn_801AE5D4(2, 0, 0x401E), 3, a, result1, result2);
            fn_801AF2CC(0);
        }
    }
}

extern "C" void SpchIGStopSceneLine(void)
{
    if (_SpchIG_bSceneLineActive) {
        if ((unsigned char)(_SpchIG_iSceneSpeaker >> 8) == 0) {
            SpchIGStopChannel(1);
        } else {
            SpchIGStopChannel(0);
        }
    }
}

extern "C" void SpchIGEndSceneLine(void)
{
    if (_SpchIG_bSceneLineActive) {
        if ((unsigned char)(_SpchIG_iSceneSpeaker >> 8) == 0) {
            SpchIGPurgeChannel(1);
        } else {
            SpchIGPurgeChannel(0);
        }
    }
    _SpchIG_iSceneSpeaker = 0;
    _SpchIG_bSceneLineActive = 0;
}

extern "C" int SpchIGGetSceneSpeaker(void)
{
    return _SpchIG_iSceneSpeaker;
}

extern "C" unsigned char SpchIGIsSceneLineActive(void)
{
    return _SpchIG_bSceneLineActive;
}

extern "C" int SpchIGGetTutorialDrillIndex(unsigned int a, int b)
{
    switch (a) {
    case 0:
        return b;
    case 1:
        return b + 7;
    case 2:
        return b + 16;
    case 3:
        return b + 24;
    case 4:
        return b + 30;
    }
    return 0;
}
