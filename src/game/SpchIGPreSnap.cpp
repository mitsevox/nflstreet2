/* In-game player speech before the snap: a line about the down and distance when the play is set
   up, trash talk when the offense is set at the line (referring to the last play, the score and
   gamebreakers) followed by a reply from the other team after a short pause, and one-off lines when
   an offensive player goes in motion or a defender shifts. */

#include "game/Object_8017886C.h"
#include "engine/spchevnt.h"

extern "C" {
int SndgSpchGetPlayFlags(void);
int SpchIGGetTeamPlayer(int side);
void SpchIGGetScoreSituation(int *pResult);
void SpchIGGetScoreMargin(int *pResult);
void SpchIGGetPlayerCategory(int *pResult, int value);
void SpchIGGetGamebreakerState(int *pResult);
int fn_80177F70(void);
int fn_80177F7C(void);
int fn_80178194(void);
int fn_80178308(void);
int fn_80178360(void);
int fn_801F7ABC(void);
float fn_80237260(int stream);
void SpchIGSayPreSnap(int side);
}

static unsigned int _SpchIG_uPreSnapStartTime = 0;
static float _SpchIG_fPreSnapDelay = 0.0f;

extern "C" void SpchIGGetDownFlags(int *pResult)
{
    *pResult = 16;
    switch (fn_80177F70()) {
    case 1:
        *pResult |= 1;
        break;
    case 2:
        *pResult |= 2;
        break;
    case 3:
        *pResult |= 4;
        break;
    case 4:
        *pResult |= 8;
        break;
    case 6:
        *pResult |= 32;
        break;
    }
}

extern "C" void SpchIGGetDistanceFlags(int *pResult)
{
    int value;

    *pResult = 8;
    value = fn_80178194();
    if (value == -1) {
        *pResult |= 4;
    } else if (value <= 5) {
        *pResult |= 1;
    } else if (value > 14) {
        *pResult |= 2;
    }
}

extern "C" void SpchIGGetLastPlayFlags(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if (!(p->mUnknown18 & 8)) {
        if (SndgSpchGetPlayFlags() & 1) {
            *pResult |= 1;
        }
        if (p->mUnknown14 < 0.0f) {
            *pResult |= 2;
        } else if (p->mUnknown14 > 0.0f) {
            *pResult |= 256;
            if (p->mUnknown14 >= 20.0f) {
                if (p->mUnknown18 & 0x10000) {
                    *pResult |= 64;
                } else {
                    *pResult |= 128;
                }
            }
        }
        if ((p->mUnknown18 & 0x1000) && p->mUnknown1D == 0) {
            *pResult |= 8;
        }
        if (p->mUnknown1D == 6 || p->mUnknown1D == 9) {
            *pResult |= 32;
        }
    } else if (fn_80177F7C() != 6) {
        *pResult |= 4;
    }
    if (p->mUnknown1D == -2) {
        *pResult |= 16;
    }
}

extern "C" void SpchIGResetPreSnap(void)
{
    _SpchIG_uPreSnapStartTime = 0;
    _SpchIG_fPreSnapDelay = 0.0f;
}

extern "C" void SpchIGEndPreSnap(void) {}

extern "C" void SpchIGUpdatePreSnap(void)
{
    if (_SpchIG_uPreSnapStartTime != 0) {
        if ((float)(fn_801F7ABC() - _SpchIG_uPreSnapStartTime) >= _SpchIG_fPreSnapDelay * 60.0f) {
            SpchIGSayPreSnap(fn_80178360());
            _SpchIG_uPreSnapStartTime = 0;
        }
    }
}

extern "C" void SpchIGSayDownAndDistance(void)
{
    int result1;
    int result2;
    int result3;

    SpchIGGetDownFlags(&result1);
    SpchIGGetDistanceFlags(&result2);
    if (fn_80178360() == 0) {
        SpchIGGetPlayerCategory(&result3, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2002), 3, result1, result2, result3);
    } else {
        SpchIGGetPlayerCategory(&result3, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4002), 3, result1, result2, result3);
    }
}

extern "C" void SpchIGSayPreSnap(int side)
{
    int result1;
    int result2;
    int result3;
    int result4;
    int result5;

    if (_SpchIG_uPreSnapStartTime == 0) {
        _SpchIG_uPreSnapStartTime = fn_801F7ABC();
        _SpchIG_fPreSnapDelay = fn_80237260(1) + 1.0f;
    }
    SpchIGGetLastPlayFlags(&result1);
    SpchIGGetScoreSituation(&result2);
    SpchIGGetPlayerCategory(&result3, SpchIGGetTeamPlayer(side));
    SpchIGGetGamebreakerState(&result4);
    SpchIGGetScoreMargin(&result5);
    if (side == 0) {
        if (fn_80178360() == 0) {
            gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2012), 3, result1, result2, result3);
        } else {
            gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2003), 5, result1, result2, result3, result4, result5);
        }
    } else if (fn_80178360() == 0) {
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4003), 5, result1, result2, result3, result4, result5);
    } else {
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4012), 3, result1, result2, result3);
    }
}

extern "C" void SpchIGSayDefenseShift(void)
{
    int result;

    if (fn_80178360() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x200C), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x400C), 1, result);
    }
}

extern "C" void SpchIGSayOffenseMotion(void)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x201A), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x401A), 1, result);
    }
}
