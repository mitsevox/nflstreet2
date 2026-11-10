/* In-game HUD event wrappers: each function posts one UI event (0x800000xx) to the in-game UI instance, driving the two GameBreaker meter halves and level, the Player/Points score table, per-player text popups in team colour, and two per-side on/off indicators. */
#include <string.h>
#include "game/Entry_80219044.h"
#include "game/HudEvents.h"
#include "game/fn_8021D7B8.h"

/* Only +8 is read here. */
struct HudPopupPlayer_t {
    char mUnknown0[8];
    unsigned char mUnknown8;
};

extern "C" {
extern void *lbl_803EB688;
extern const float lbl_803ED6A4;
extern const float lbl_803ED6A8;

int fn_800A83E0(int a);
unsigned char fn_800C1E48(void);
int fn_80162E40(int a);
int fn_80188030(int a);

unsigned char HudIsEvent31Shown(int index);
unsigned char HudIsEvent3DShown(int index);
int HudLookupColor(int key, unsigned char *pRed, unsigned char *pGreen, unsigned char *pBlue);
}

static unsigned char _Hud_abEvent31Shown[4] = { 0 };
static unsigned char _Hud_abEvent3DShown[4] = { 0 };

static Entry_80219044 _Hud_aScoreHeaderEntry[2];
static char _Hud_aScoreHeaderText[2][32];
static Entry_80219044 _Hud_aScoreNameEntry[6];
static char _Hud_aScoreNameText[6][32];
static Entry_80219044 _Hud_aScoreValueEntry[6];
static char _Hud_aScoreValueText[6][32];
static Entry_80219044 _Hud_aScoreExtraEntry[6];
static char _Hud_aScoreExtraText[6][32];
static Entry_80219044 _Hud_PopupEntry;
static char _Hud_aPopupText[80];

static const int _Hud_aiTeamColorIndex[4] = { 0, 1, 7, 3 };

extern "C" void HudShowEvent31(int index)
{
    unsigned char on = 1;
    Arg_8021D7B8 args[2];

    if (!HudIsEvent31Shown(index)) {
        _Hud_abEvent31Shown[index] = on;
        if (index == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        args[1].i = 1;
        fn_8021D7B8(lbl_803EB688, 0x80000031, 2, args);
    }
}

extern "C" void HudHideEvent31(int index)
{
    Arg_8021D7B8 args[2];

    if (HudIsEvent31Shown(index)) {
        _Hud_abEvent31Shown[index] = 0;
        if (index == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        args[1].i = 0;
        fn_8021D7B8(lbl_803EB688, 0x80000031, 2, args);
    }
}

extern "C" void HudSetGameBreakerMeter(int a, float t, int b, int direct)
{
    Arg_8021D7B8 args[3];
    float first;
    float second;

    args[0].i = a;
    if (t <= lbl_803ED6A4) {
        first = t / lbl_803ED6A4;
        second = 0.0f;
    } else {
        first = 1.0f;
        second = (t - lbl_803ED6A4) / (lbl_803ED6A8 - lbl_803ED6A4);
    }

    args[1].f = first;
    if (direct) {
        args[2].i = b;
        fn_8021D7B8(lbl_803EB688, 0x8000002F, 3, args);
    } else {
        args[2].i = fn_800A83E0(a);
        fn_8021D7B8(lbl_803EB688, 0x80000012, 3, args);
    }

    args[1].f = second;
    if (direct) {
        args[2].i = b;
        fn_8021D7B8(lbl_803EB688, 0x80000069, 3, args);
    } else {
        args[2].i = fn_800A83E0(a);
        fn_8021D7B8(lbl_803EB688, 0x80000068, 3, args);
    }
}

extern "C" void HudSetGameBreakerLevel(int a, int b)
{
    Arg_8021D7B8 args[2];

    args[0].i = a;
    args[1].i = b;
    fn_8021D7B8(lbl_803EB688, 0x8000006A, 2, args);
}

extern "C" void HudShowEvent3D(int index)
{
    unsigned char on = 1;
    Arg_8021D7B8 args[2];

    if (!HudIsEvent3DShown(index)) {
        _Hud_abEvent3DShown[index] = on;
        if (index == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        args[1].i = 1;
        fn_8021D7B8(lbl_803EB688, 0x8000003D, 2, args);
    }
}

extern "C" void HudHideEvent3D(int index)
{
    Arg_8021D7B8 args[2];

    if (HudIsEvent3DShown(index)) {
        _Hud_abEvent3DShown[index] = 0;
        if (index == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        args[1].i = 0;
        fn_8021D7B8(lbl_803EB688, 0x8000003D, 2, args);
    }
}

extern "C" void HudSetScoreTableRows(int a)
{
    Arg_8021D7B8 args[1];

    args[0].i = a;
    fn_8021D7B8(lbl_803EB688, 0x80000076, 1, args);
}

extern "C" void HudSetScoreTableHeaders(const char *pText0, const char *pText1)
{
    Arg_8021D7B8 args[2];

    strncpy(_Hud_aScoreHeaderText[0], pText0, 32);
    _Hud_aScoreHeaderEntry[0].mLength = strlen(pText0) + 1;
    _Hud_aScoreHeaderEntry[0].mpText = _Hud_aScoreHeaderText[0];
    args[0].p = &_Hud_aScoreHeaderEntry[0];
    strncpy(_Hud_aScoreHeaderText[1], pText1, 32);
    _Hud_aScoreHeaderEntry[1].mLength = strlen(pText1) + 1;
    _Hud_aScoreHeaderEntry[1].mpText = _Hud_aScoreHeaderText[1];
    args[1].p = &_Hud_aScoreHeaderEntry[1];
    fn_8021D7B8(lbl_803EB688, 0x80000077, 2, args);
}

extern "C" void HudSetScoreTableRow(int slot, const char *pText0, const char *pText1, const char *pText2, int key)
{
    Arg_8021D7B8 args[4];
    Arg_8021D7B8 colour[5];
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    strncpy(_Hud_aScoreNameText[slot - 1], pText0, 32);
    strncpy(_Hud_aScoreValueText[slot - 1], pText1, 32);
    strncpy(_Hud_aScoreExtraText[slot - 1], pText2, 32);
    _Hud_aScoreNameEntry[slot - 1].mLength = strlen(_Hud_aScoreNameText[slot - 1]) + 1;
    _Hud_aScoreNameEntry[slot - 1].mpText = _Hud_aScoreNameText[slot - 1];
    _Hud_aScoreValueEntry[slot - 1].mLength = strlen(_Hud_aScoreValueText[slot - 1]) + 1;
    _Hud_aScoreValueEntry[slot - 1].mpText = _Hud_aScoreValueText[slot - 1];
    _Hud_aScoreExtraEntry[slot - 1].mLength = strlen(_Hud_aScoreExtraText[slot - 1]) + 1;
    _Hud_aScoreExtraEntry[slot - 1].mpText = _Hud_aScoreExtraText[slot - 1];
    args[0].i = slot;
    args[1].p = &_Hud_aScoreNameEntry[slot - 1];
    args[2].p = &_Hud_aScoreValueEntry[slot - 1];
    args[3].p = &_Hud_aScoreExtraEntry[slot - 1];
    fn_8021D7B8(lbl_803EB688, 0x80000078, 4, args);

    colour[0].i = slot;
    if (HudLookupColor(key, &red, &green, &blue)) {
        colour[1].i = red;
        colour[2].i = green;
        colour[3].i = blue;
        colour[4].i = 0xFF;
    } else {
        colour[1].i = 0;
        colour[2].i = 0;
        colour[3].i = 0;
        colour[4].i = 0;
    }
    fn_8021D7B8(lbl_803EB688, 0x80000079, 5, colour);
}

extern "C" void HudSetGameBreakerHalf(int a, int b)
{
    Arg_8021D7B8 args[2];

    if (a == 0) {
        args[0].i = 0;
    } else {
        args[0].i = 1;
    }
    args[1].i = b;
    fn_8021D7B8(lbl_803EB688, 0x8000006F, 2, args);
}

extern "C" void HudResetGameBreaker(int a)
{
    Arg_8021D7B8 args[1];

    if (a == 0) {
        args[0].i = 0;
    } else {
        args[0].i = 1;
    }
    fn_8021D7B8(lbl_803EB688, 0x80000070, 1, args);
}

extern "C" void HudShowPlayLeader(int a)
{
    Arg_8021D7B8 args[1];

    if (!fn_800C1E48()) {
        if (a == 0) {
            args[0].i = 0;
        } else {
            args[0].i = 1;
        }
        fn_8021D7B8(lbl_803EB688, 0x8000006B, 1, args);
    }
}

extern "C" void HudClearEvent71(void)
{
    Arg_8021D7B8 args[1];

    args[0].i = 0;
    fn_8021D7B8(lbl_803EB688, 0x80000071, 1, args);
}

extern "C" void HudShowPlayerPopup(HudPopupPlayer_t *pObject, int a, const char *pText, int c, int d)
{
    Arg_8021D7B8 args[7];
    int red;
    int green;
    int blue;
    int rgb;

    strncpy(_Hud_aPopupText, pText, 79);
    if (pObject != 0) {
        rgb = fn_80162E40(8);
        red = (rgb & 0xFF0000) >> 16;
        green = (rgb & 0xFF00) >> 8;
        blue = rgb & 0xFF;
        if (pObject->mUnknown8 != 0xFF) {
            int index = fn_80188030(pObject->mUnknown8);
            if (index != -1) {
                rgb = fn_80162E40(_Hud_aiTeamColorIndex[index]);
                red = (rgb & 0xFF0000) >> 16;
                green = (rgb & 0xFF00) >> 8;
                blue = rgb & 0xFF;
            }
        }
    } else {
        red = 30;
        green = 150;
        blue = 200;
    }
    args[0].i = a;
    args[1].p = &_Hud_PopupEntry;
    _Hud_PopupEntry.mpText = _Hud_aPopupText;
    _Hud_PopupEntry.mLength = strlen(_Hud_aPopupText);
    args[2].i = c;
    args[3].i = d;
    args[4].i = red;
    args[5].i = green;
    args[6].i = blue;
    fn_8021D7B8(lbl_803EB688, 0x8000007D, 7, args);
}

extern "C" int HudLookupColor(int key, unsigned char *pRed, unsigned char *pGreen, unsigned char *pBlue)
{
    int found = 0;
    int rgb;

    *pRed = 0;
    *pGreen = 0;
    *pBlue = 0;
    if (key == 0xFE) {
        found = 1;
        rgb = fn_80162E40(8);
        *pRed = (rgb & 0xFF0000) >> 16;
        *pGreen = (rgb & 0xFF00) >> 8;
        *pBlue = rgb & 0xFF;
    } else if (key != 0xFF) {
        int index = fn_80188030(key);
        if (index != -1) {
            found = 1;
            rgb = fn_80162E40(_Hud_aiTeamColorIndex[index]);
            *pRed = (rgb & 0xFF0000) >> 16;
            *pGreen = (rgb & 0xFF00) >> 8;
            *pBlue = rgb & 0xFF;
        }
    }
    return found;
}

extern "C" unsigned char HudIsEvent31Shown(int index)
{
    return _Hud_abEvent31Shown[index];
}

extern "C" unsigned char HudIsEvent3DShown(int index)
{
    return _Hud_abEvent3DShown[index];
}

extern "C" void HudSetEvent1A(int a, int b)
{
    Arg_8021D7B8 args[2];

    args[0].i = a;
    args[1].i = b;
    fn_8021D7B8(lbl_803EB688, 0x8000001A, 2, args);
}
