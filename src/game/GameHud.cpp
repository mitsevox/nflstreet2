/* In-game HUD messages: posts the score and down displays, the per-controller "Mash" and "Press" button prompts, short alert and callout texts, and the HUD show/hide toggles to the UI object. */
#include <string.h>
#include "game/Object_80039F5C.h"
#include "game/Entry_80219044.h"
#include "game/Challenge.h"
#include "game/AudmonEvent.h"
#include "game/HudEvents.h"
#include "game/GameOptions.h"
#include "game/fn_80218FC4.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_800B65A0.h"

extern "C" {
extern void *gUISMainInfo;

int ChallengeIsActive(void);
int VptManagerGetPassIcons(void);
int fn_800A8444(int team);
int fn_800A8488(int team);
Object_80039F5C *fn_800B6544(int index);
int fn_800B6644(int index);
int fn_801486A0(void);
int fn_80156704(void);
int fn_80177F70(void);
int fn_80178308(void);
int fn_80179138(void);
int GameTextFindPlayerPad(int index);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
void fn_8021956C(void *p, int a, int b, int c);

unsigned char HudGetPadSlot(int id);
void HudEnableMashCycle(unsigned char value);
void HudCycleMashPrompt(void);
void HudSetScore(int a, int b);
}

static unsigned char _Hud_bMashCycle = 0;
static char _Hud_szMash[] = "Mash";
static char _Hud_szPress[] = "Press";
static int _Hud_iMashOffenseId = 0;
static int _Hud_iMashDefenseId = 0;
static unsigned char _Hud_uMashOffensePad = 4;
static unsigned char _Hud_uMashDefensePad = 4;
static unsigned char _Hud_uMashArg = 0;
static unsigned char _Hud_uMashNextPad = 0;
static unsigned char _Hud_bHidden = 0;

static char _Hud_szMessage[0x52];
static Entry_80219044 _Hud_ScoreText;
static Entry_80219044 _Hud_MessageText;
static Entry_80219044 _Hud_MashText;
static Entry_80219044 _Hud_PressText;
static char _Hud_szScore[4];

extern "C" {

/* Returns the slot of controller id: in modes above 1, controllers whose
   fn_800B6644 value is 1 fill the slots from the front and those with 0 from
   the back; otherwise each controller keeps its own index. */
unsigned char HudGetPadSlot(int id)
{
    char order[4];
    int first = 0;
    int last = 3;
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        order[i] = -1;
    }
    for (i = 0; i <= 3; i++) {
        int index = GameTextFindPlayerPad(i);

        if (index != -1) {
            int side = fn_800B6644(index);
            int mode = fn_801486A0();

            if (mode != 0 && mode != 1) {
                if (side == 1) {
                    order[first++] = i;
                } else if (side == 0) {
                    order[last--] = i;
                }
            } else if (side == 1 || side == 0) {
                order[i] = i;
            }
        }
    }
    for (i = 0; i <= 3; i++) {
        if ((unsigned char)order[i] == id) {
            return i;
        }
    }
    return 0;
}

int HudIsPadPromptAllowed(unsigned char id)
{
    return 1;
}

void HudUpdateMashPrompt(unsigned char id)
{
    int args[4];
    Object_80039F5C *p;
    unsigned char own;

    if (fn_80156704()) {
        return;
    }
    p = 0;
    {
        int index = GameTextFindPlayerPad(id);

        if (index != -1) {
            p = fn_800B6544(index);
        }
    }
    if (p == 0) {
        return;
    }
    own = (p->mId >> 8 & 0xFF) == fn_80178308();
    args[2] = _Hud_uMashArg;
    _Hud_MashText.mpText = _Hud_szMash;
    args[3] = (int)&_Hud_MashText;
    _Hud_MashText.mLength = strlen(_Hud_MashText.mpText);
    if (p->mUnknown8 != 0xFF) {
        if (!own) {
            if (_Hud_iMashDefenseId == p->mId && _Hud_uMashDefensePad != id) {
                if (_Hud_uMashDefensePad != 4) {
                    args[0] = HudGetPadSlot(_Hud_uMashDefensePad);
                    args[1] = 0;
                    if (VptManagerGetPassIcons()) {
                        fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
                    }
                }
                args[0] = HudGetPadSlot(id);
                args[1] = 1;
                if (VptManagerGetPassIcons() && HudIsPadPromptAllowed(id)) {
                    fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
                }
                _Hud_uMashDefensePad = id;
            }
        }
        if (own) {
            if (_Hud_iMashOffenseId == p->mId && _Hud_uMashOffensePad != id) {
                if (_Hud_uMashOffensePad != 4) {
                    args[0] = HudGetPadSlot(_Hud_uMashOffensePad);
                    args[1] = 0;
                    if (VptManagerGetPassIcons()) {
                        fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
                    }
                }
                args[0] = HudGetPadSlot(id);
                args[1] = 1;
                if (VptManagerGetPassIcons() && HudIsPadPromptAllowed(id)) {
                    fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
                }
                _Hud_uMashOffensePad = id;
            }
        }
    }
    if (!own) {
        if (_Hud_uMashDefensePad == id && (_Hud_iMashDefenseId == 0 || _Hud_iMashDefenseId != p->mId)) {
            args[0] = HudGetPadSlot(id);
            args[1] = 0;
            if (VptManagerGetPassIcons()) {
                fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
            }
            _Hud_uMashDefensePad = 4;
        }
    }
    if (own) {
        if (_Hud_uMashOffensePad == id && (_Hud_iMashOffenseId == 0 || _Hud_iMashOffenseId != p->mId)) {
            args[0] = HudGetPadSlot(id);
            args[1] = 0;
            if (VptManagerGetPassIcons()) {
                fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
            }
            _Hud_uMashOffensePad = 4;
        }
    }
}

void HudReset(void)
{
    _Hud_bMashCycle = 1;
    _Hud_iMashOffenseId = 0;
    _Hud_iMashDefenseId = 0;
    _Hud_uMashOffensePad = 4;
    _Hud_uMashDefensePad = 4;
    _Hud_uMashNextPad = 0;
    _Hud_bHidden = 0;
    HudSetGameBreakerMeter(0, 0.0f, 0, 0);
    HudSetGameBreakerMeter(1, 0.0f, 0, 0);
    HudSetEvent1A(0, 0);
    HudSetEvent1A(1, 0);
    if (ChallengeIsActive()) {
        HudSetScore(0, ChalGetCurrent()->mUnknown1AC);
        HudSetScore(1, ChalGetCurrent()->mUnknown1A8);
    } else {
        HudSetScore(0, 0);
        HudSetScore(1, 0);
    }
    HudSetGameBreakerMeter(1, 0.0f, 0, 0);
    HudSetGameBreakerMeter(0, 0.0f, 0, 0);
    HudSetGameBreakerLevel(0, 0);
    HudSetGameBreakerLevel(1, 0);
    HudResetGameBreaker(0);
    HudResetGameBreaker(1);
}

void HudStart(void)
{
    HudReset();
    switch (fn_801486A0()) {
    case 0:
    case 1:
    case 2:
        fn_80218FC4(gUISMainInfo, 3, 0x10, 0, 0);
        break;
    default:
        fn_80218FC4(gUISMainInfo, 3, 3, 0, 0);
        if (fn_80156704()) {
            fn_80218FC4(gUISMainInfo, 7, 0x10, 0, 0);
        }
        break;
    }
    HudCycleMashPrompt();
    HudEnableMashCycle(1);
}

void HudEnableMashCycle(unsigned char value)
{
    _Hud_bMashCycle = value;
}

void HudCycleMashPrompt(void)
{
    if (_Hud_bMashCycle) {
        HudUpdateMashPrompt(_Hud_uMashNextPad);
        _Hud_uMashNextPad++;
        _Hud_uMashNextPad %= 4;
    }
}

void HudSetScore(int a, int b)
{
    int args[2];

    switch (GameOptionsGet(14)) {
    case 1:
    case 2:
        break;
    default:
        args[0] = a != 0;
        fn_801C2E18(_Hud_szScore, "%d", b);
        _Hud_ScoreText.mpText = _Hud_szScore;
        args[1] = (int)&_Hud_ScoreText;
        _Hud_ScoreText.mLength = strlen(_Hud_ScoreText.mpText);
        fn_8021D7B8(gUISMainInfo, 0x8000000B, 2, args);
        break;
    }
}

void HudSetDown(void)
{
    int args[1];
    int count = fn_80177F70();

    if (count > 4) {
        count = fn_80177F70() + fn_80179138();
    }
    args[0] = count;
    fn_8021D7B8(gUISMainInfo, 0x80000010, 1, args);
}

void HudShowAlert(const char *pText)
{
    Entry_80219044 *args[1];

    strncpy(_Hud_szMessage, pText, 0x1D);
    args[0] = &_Hud_MessageText;
    args[0]->mpText = _Hud_szMessage;
    args[0]->mLength = strlen(args[0]->mpText);
    fn_8021D7B8(gUISMainInfo, 0x8000000C, 1, args);
    AudmonEventPost(0x13, 0);
}

void HudShowCallout(const char *pText)
{
    Entry_80219044 *args[1];

    strncpy(_Hud_szMessage, pText, sizeof(_Hud_szMessage));
    args[0] = &_Hud_MessageText;
    args[0]->mpText = _Hud_szMessage;
    args[0]->mLength = strlen(args[0]->mpText);
    fn_8021D7B8(gUISMainInfo, 0x80000018, 1, args);
    AudmonEventPost(0x13, 0);
}

void HudSetMashPlayers(int a, int b, unsigned char c)
{
    _Hud_iMashOffenseId = a;
    _Hud_iMashDefenseId = b;
    _Hud_uMashArg = c;
}

void HudHideMashPrompts(void)
{
    int args[4];

    args[2] = 0;
    _Hud_MashText.mpText = _Hud_szMash;
    args[3] = (int)&_Hud_MashText;
    _Hud_MashText.mLength = strlen(_Hud_MashText.mpText);
    if (_Hud_uMashDefensePad != 4) {
        args[0] = HudGetPadSlot(_Hud_uMashDefensePad);
        args[1] = 0;
        if (VptManagerGetPassIcons()) {
            fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
        }
        _Hud_uMashDefensePad = 4;
    }
    if (_Hud_uMashOffensePad != 4) {
        args[0] = HudGetPadSlot(_Hud_uMashOffensePad);
        args[1] = 0;
        if (VptManagerGetPassIcons()) {
            fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
        }
        _Hud_uMashOffensePad = 4;
    }
}

void HudClearMashPlayers(int a, int b)
{
    if (_Hud_iMashOffenseId == a && _Hud_iMashDefenseId == b) {
        _Hud_iMashOffenseId = 0;
        _Hud_iMashDefenseId = 0;
    }
}

void HudShowPressPrompt(int team)
{
    int args[4];

    if (fn_800B65A0(team) == 0xFF || !fn_800A8488(team) || fn_800A8444(team)) {
        return;
    }
    if (team == 0) {
        args[0] = 3;
    } else if (team == 1) {
        args[0] = 0;
    }
    args[1] = 1;
    args[2] = 1;
    _Hud_PressText.mpText = _Hud_szPress;
    args[3] = (int)&_Hud_PressText;
    _Hud_PressText.mLength = strlen(_Hud_PressText.mpText);
    if (VptManagerGetPassIcons()) {
        fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
    }
}

void HudHidePressPrompt(int team)
{
    int args[4];

    if (fn_800B65A0(team) == 0xFF) {
        return;
    }
    if (team == 0) {
        args[0] = 3;
    } else if (team == 1) {
        args[0] = 0;
    }
    args[1] = 0;
    args[2] = 1;
    _Hud_PressText.mpText = _Hud_szPress;
    args[3] = (int)&_Hud_PressText;
    _Hud_PressText.mLength = strlen(_Hud_PressText.mpText);
    if (VptManagerGetPassIcons()) {
        fn_8021D7B8(gUISMainInfo, 0x80000019, 4, args);
    }
}

void HudStop(void)
{
    HudReset();
    switch (fn_801486A0()) {
    case 0:
    case 1:
    case 2:
        fn_8021956C(gUISMainInfo, 3, 0x10, 1);
        break;
    default:
        fn_8021956C(gUISMainInfo, 3, 3, 1);
        if (fn_80156704()) {
            fn_8021956C(gUISMainInfo, 7, 0x10, 1);
        }
        break;
    }
    HudEnableMashCycle(0);
}

void HudPost3AOn(void)
{
    int args[1];

    args[0] = 1;
    fn_8021D7B8(gUISMainInfo, 0x8000003A, 1, args);
}

void HudPost3AOff(void)
{
    int args[1];

    args[0] = 0;
    fn_8021D7B8(gUISMainInfo, 0x8000003A, 1, args);
}

void HudHide(void)
{
    int args[1];

    _Hud_bHidden = 1;
    args[0] = 0;
    fn_8021D7B8(gUISMainInfo, 0x8000001B, 1, args);
}

void HudUnhide(void)
{
    int args[1];

    _Hud_bHidden = 0;
    args[0] = 1;
    fn_8021D7B8(gUISMainInfo, 0x8000001B, 1, args);
}

void HudHideOverlay(void)
{
    int args[1];

    _Hud_bHidden = 1;
    args[0] = 1;
    if (!fn_80156704()) {
        fn_8021D7B8(gUISMainInfo, 0x80000067, 1, args);
    }
}

void HudShowOverlay(void)
{
    int args[1];

    _Hud_bHidden = 0;
    args[0] = 0;
    fn_8021D7B8(gUISMainInfo, 0x80000067, 1, args);
}

unsigned char HudIsHidden(void)
{
    return _Hud_bHidden;
}

}
