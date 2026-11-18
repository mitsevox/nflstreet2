/* In-game player speech after each play: classifies the finished play (score, turnover, failed
   fourth down, sack, tackle for loss, completed or incomplete pass, ordinary gain) and has one
   team's player react, then after a short random pause lets the other team answer. Gameplay code
   records here which players took part in the play (tackler, pass target, catcher, ball carrier,
   turnover player, scorer) so the right player speaks. */

#include "game/fn_80178D18.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "engine/spchevnt.h"

extern "C" {
int SndgSpchGetPlayFlags(void);
void SpchIGFindNearestOpponent(int handle);
int SpchIGGetNearestOpponent(int side);
int SpchIGGetTeamPlayer(int side);
void SpchIGGetScoreSituation(int *pResult);
void SpchIGGetScoreMargin(int *pResult);
void SpchIGGetPlayerCategory(int *pResult, int value);
int fn_800A21A8(int bit);
int fn_80177F7C(void);
Point_8017886C fn_80177FE0(void);
float fn_801782A4(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_80178360(void);
int fn_801783AC(int bit);
int fn_80179138(void);
int fn_801F7ABC(void);
float fn_80237260(int stream);

void SpchIGSayPlayResult(void);
int SpchIGGetTackler(void);
void SpchIGSetPassTarget(int id);
int SpchIGGetPassTarget(void);
int SpchIGGetScorer(void);
}

static unsigned int _SpchIG_uResultStartTime = 0;
static float _SpchIG_fResultDelay = 0.0f;
static unsigned char _SpchIG_bResultSide = 0;
static int _SpchIG_iTackler = 0;
static int _SpchIG_iPassTarget = 0;
static int _SpchIG_iPassCatcher = 0;
static int _SpchIG_iBallCarrier = 0;
static int _SpchIG_iTurnoverPlayer = 0;
static int _SpchIG_iScorer = 0;
static int _SpchIG_iDownedCarrier = 0;

extern "C" int SpchIGGetResultFirstSide(void)
{
    int result = fn_80178320();
    Object_8017886C *p = fn_8017886C();

    if (p->mUnknown18 & 8) {
        if (fn_80177F7C() == 6) {
            if (p->mUnknown1D == 0) {
                result = fn_80178360();
            } else {
                result = ((_SpchIG_iScorer >> 8) & 0xFF) ^ 1;
            }
        } else if (p->mUnknown18 & 0x400) {
            result = fn_80178348();
        } else if (p->mUnknown18 & 0x200) {
            result = fn_80178348();
        } else if (p->mUnknown1D == -2) {
            result = fn_80178360();
        } else if (p->mUnknown18 & 0x800) {
            result = fn_80178360();
        }
    }
    return result;
}

extern "C" int SpchIGClassifyPlayResult(void)
{
    Object_8017886C *p = fn_8017886C();

    if (p->mUnknown1D != 0) {
        SpchIGFindNearestOpponent(SpchIGGetScorer());
        return 1;
    }
    if (fn_80177F7C() == 6) {
        return 2;
    }
    if ((p->mUnknown18 & 8) && fn_80177F7C() != 6) {
        return 3;
    }
    if (fn_80177F7C() == 4 && (p->mUnknown18 & 0x1000)) {
        return 4;
    }
    if (SndgSpchGetPlayFlags() & 1) {
        return 5;
    }
    if (SndgSpchGetPlayFlags() & 2) {
        return 6;
    }
    if (fn_800A21A8(2)) {
        return 14;
    }
    if (fn_800A21A8(0)) {
        if (p->mUnknown18 & 0x10000) {
            return 13;
        }
        SpchIGFindNearestOpponent(SpchIGGetPassTarget());
        return 12;
    }
    if (p->mUnknown18 & 0x8000) {
        if (fn_800A21A8(1)) {
            SpchIGFindNearestOpponent(SpchIGGetPassTarget());
            if (p->mUnknown18 & 0x10000) {
                return 11;
            }
            return 12;
        }
        SpchIGFindNearestOpponent(SpchIGGetPassTarget());
        if (p->mUnknown18 & 0x10000) {
            return 7;
        }
        return 8;
    }
    if (SndgSpchGetPlayFlags() & 0x40) {
        SpchIGFindNearestOpponent(_SpchIG_iDownedCarrier);
        return 10;
    }
    return 9;
}

extern "C" void SpchIGGetGainFlags(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if (p->mUnknown1D == 6 || p->mUnknown1D == 9) {
        *pResult = 1;
    }
    if (p->mUnknown14 > 0.0f) {
        if (p->mUnknown18 & 0x10000) {
            if (p->mUnknown14 >= 20.0f) {
                *pResult |= 64;
            } else if (p->mUnknown14 >= 10.0f) {
                *pResult |= 32;
            } else {
                *pResult |= 16;
            }
        } else {
            if (p->mUnknown14 >= 20.0f) {
                *pResult |= 8;
            } else if (p->mUnknown14 >= 10.0f) {
                *pResult |= 4;
            } else {
                *pResult |= 2;
            }
        }
    }
}

extern "C" void SpchIGGetScorerSideFlags(int *pResult)
{
    Object_8017886C *p;
    int team;
    int side;

    *pResult = 0;
    p = fn_8017886C();
    team = fn_80178348();
    side = (_SpchIG_iScorer >> 8) & 0xFF;
    if (p->mUnknown1D == -2) {
        *pResult = 2;
    } else if (p->mUnknown1D == 6 || p->mUnknown1D == 9) {
        if (team == side) {
            *pResult = 1;
        } else {
            *pResult = 2;
        }
    } else if (p->mUnknown1D == 2) {
        if (team == side) {
            *pResult = 1;
        } else {
            *pResult = 2;
        }
    }
}

extern "C" void SpchIGGetTurnoverFlags(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if ((p->mUnknown18 & 8) && fn_80177F7C() != 6) {
        *pResult = 16;
        if (p->mUnknown18 & 0x400) {
            *pResult = 17;
        }
        if (p->mUnknown18 & 0x200) {
            *pResult |= 2;
        }
        if (p->mUnknown1D == -2) {
            *pResult |= 4;
        }
        if (p->mUnknown18 & 0x800) {
            *pResult |= 8;
        }
    }
}

extern "C" void SpchIGGetFourthDownFlags(int *pResult)
{
    float value;

    if (fn_8017886C()->mUnknown18 & 0x10000) {
        *pResult = 1;
    } else {
        *pResult = 2;
    }
    value = fn_801782A4();
    if (fn_80177FE0().mY - value < 2.0f) {
        *pResult |= 4;
    }
}

extern "C" void SpchIGGetTackleForLossFlags(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 8;
    if (p->mUnknown14 < 0.0f) {
        *pResult = 9;
    }
    if (SndgSpchGetPlayFlags() & 4) {
        *pResult |= 2;
    }
    if (SndgSpchGetPlayFlags() & 8) {
        *pResult |= 4;
    }
}

extern "C" void SpchIGGetIncompletionFlags(int *pResult)
{
    *pResult = 4;
    if (fn_801783AC(12)) {
        *pResult |= 1;
    }
    if (fn_801783AC(11)) {
        *pResult |= 2;
    }
    if (fn_801783AC(23)) {
        *pResult |= 8;
    }
    if (SndgSpchGetPlayFlags() & 0x10) {
        *pResult |= 16;
    }
    if (SndgSpchGetPlayFlags() & 0x20) {
        *pResult |= 32;
    }
}

extern "C" void SpchIGGetScoreTypeFlags(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if (p->mUnknown1D == 6 || p->mUnknown1D == 9) {
        if (fn_80178308() == fn_80178348()) {
            *pResult |= 1;
        } else {
            *pResult |= 2;
        }
    } else if (p->mUnknown1D == -2) {
        *pResult |= 4;
    } else if (p->mUnknown1D == 2) {
        if (fn_80179138() == 2) {
            *pResult |= 8;
        } else {
            *pResult |= 32;
        }
    } else if (p->mUnknown1D == 1) {
        *pResult |= 32;
    }
    if (*pResult != 0) {
        *pResult |= 16;
    }
}

extern "C" void SpchIGGetPlayTypeFlags(int *pResult)
{
    if (fn_8017886C()->mUnknown18 & 0x8000) {
        *pResult |= 1;
    } else {
        *pResult |= 2;
    }
}

extern "C" void SpchIGGetScoredFlags(int *pResult)
{
    Object_8017886C *p = fn_8017886C();

    *pResult = 0;
    if (p->mUnknown1D != 0) {
        *pResult = 2;
    } else {
        *pResult = 1;
    }
}

extern "C" void SpchIGSayHighlightCatch(void)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402B), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402B), 1, result);
    }
}

extern "C" void SpchIGSayHighlightNoCatch(void)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402C), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402C), 1, result);
    }
}

extern "C" void SpchIGSayHighlightHitCatch(void)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402D), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402D), 1, result);
    }
}

extern "C" void SpchIGSayHighlightPass(void)
{
    int result;

    if (fn_80178308() == 0) {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(0));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402E), 1, result);
    } else {
        SpchIGGetPlayerCategory(&result, SpchIGGetTeamPlayer(1));
        gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x402E), 1, result);
    }
}

extern "C" void SpchIGResetPlayResult(void)
{
    _SpchIG_uResultStartTime = 0;
    _SpchIG_fResultDelay = 0.0f;
    _SpchIG_bResultSide = 0;
}

extern "C" void SpchIGFlushPlayResult(void)
{
    if (_SpchIG_uResultStartTime != 0) {
        SpchIGSayPlayResult();
        _SpchIG_uResultStartTime = 0;
    }
}

extern "C" void SpchIGUpdatePlayResult(void)
{
    if (_SpchIG_uResultStartTime != 0) {
        if ((float)(fn_801F7ABC() - _SpchIG_uResultStartTime) >= _SpchIG_fResultDelay * 60.0f) {
            SpchIGSayPlayResult();
            _SpchIG_uResultStartTime = 0;
        }
    }
}

extern "C" void SpchIGSayPlayResult(void)
{
    if (_SpchIG_uResultStartTime == 0) {
        _SpchIG_uResultStartTime = fn_801F7ABC();
        _SpchIG_fResultDelay = fn_80237260(1) + 1.0f;
        _SpchIG_bResultSide = SpchIGGetResultFirstSide();
    }

    switch (SpchIGClassifyPlayResult()) {
    case 0:
        break;
    case 1:
    case 2: {
        int result1;
        int result2;
        int result3;
        int result4;
        int result5;
        int result6;
        int result7;

        SpchIGGetScoreSituation(&result1);
        SpchIGGetScoreMargin(&result2);
        SpchIGGetScorerSideFlags(&result3);
        SpchIGGetScoreTypeFlags(&result4);
        SpchIGGetPlayTypeFlags(&result5);
        SpchIGGetScoredFlags(&result6);
        if (_SpchIG_bResultSide == 0) {
            if ((result3 & 1) && fn_80178348() == 0) {
                if (_SpchIG_iScorer != 0) {
                    SpchIGGetPlayerCategory(&result7, _SpchIG_iScorer);
                } else {
                    SpchIGGetPlayerCategory(&result7, SpchIGGetTeamPlayer(0));
                }
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2008), 7, result1, result2, result3, result4, result7, result5, result6);
            } else {
                SpchIGGetPlayerCategory(&result7, SpchIGGetTeamPlayer(0));
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2016), 4, result1, result3, result4, result7);
            }
        } else {
            if ((result3 & 1) && fn_80178348() == 0) {
                SpchIGGetPlayerCategory(&result7, SpchIGGetTeamPlayer(1));
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4016), 4, result1, result3, result4, result7);
            } else {
                if (_SpchIG_iScorer != 0) {
                    SpchIGGetPlayerCategory(&result7, _SpchIG_iScorer);
                } else {
                    SpchIGGetPlayerCategory(&result7, SpchIGGetTeamPlayer(1));
                }
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4008), 7, result1, result2, result3, result4, result7, result5, result6);
            }
        }
        break;
    }
    case 3: {
        int result1;
        int result2;
        int result3;
        int result4;

        SpchIGGetScoreSituation(&result1);
        SpchIGGetTurnoverFlags(&result2);
        SpchIGGetScoreMargin(&result3);
        if (_SpchIG_bResultSide == 0) {
            if (fn_80178348() == 0) {
                SpchIGGetPlayerCategory(&result4, SpchIGGetTeamPlayer(_SpchIG_bResultSide));
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x200B), 3, result2, result1, result4);
            } else {
                if (_SpchIG_iTurnoverPlayer != 0) {
                    SpchIGGetPlayerCategory(&result4, _SpchIG_iTurnoverPlayer);
                } else {
                    SpchIGGetPlayerCategory(&result4, SpchIGGetTeamPlayer(0));
                }
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2017), 4, result2, result1, result3, result4);
            }
        } else {
            if (fn_80178348() == 0) {
                if (_SpchIG_iTurnoverPlayer != 0) {
                    SpchIGGetPlayerCategory(&result4, _SpchIG_iTurnoverPlayer);
                } else {
                    SpchIGGetPlayerCategory(&result4, SpchIGGetTeamPlayer(1));
                }
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4017), 4, result2, result1, result3, result4);
            } else {
                SpchIGGetPlayerCategory(&result4, SpchIGGetTeamPlayer(_SpchIG_bResultSide));
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x400B), 3, result2, result1, result4);
            }
        }
        break;
    }
    case 4: {
        int result1;
        int result2;

        SpchIGGetFourthDownFlags(&result1);
        SpchIGGetPlayerCategory(&result2, SpchIGGetTeamPlayer(_SpchIG_bResultSide));
        if (_SpchIG_bResultSide == 0) {
            if (fn_80178348() == 0) {
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2009), 2, result1, result2);
            } else {
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2018), 2, result1, result2);
            }
        } else {
            if (fn_80178348() == 0) {
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4018), 2, result1, result2);
            } else {
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4009), 2, result1, result2);
            }
        }
        break;
    }
    case 5: {
        int result;

        SpchIGGetPlayerCategory(&result, SpchIGGetTackler());
        if (_SpchIG_bResultSide == 0) {
            if (fn_80178360() == 0) {
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2010), 1, result);
            }
        } else {
            if (fn_80178360() == 1) {
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4010), 1, result);
            }
        }
        break;
    }
    case 6: {
        int result1;
        int result2;

        SpchIGGetTackleForLossFlags(&result1);
        if (_SpchIG_iTackler != 0) {
            SpchIGGetPlayerCategory(&result2, _SpchIG_iTackler);
        } else {
            SpchIGGetPlayerCategory(&result2, SpchIGGetTeamPlayer(fn_80178360()));
        }
        if (_SpchIG_bResultSide == 0) {
            if (fn_80178360() == 0) {
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x200F), 2, result1, result2);
            }
        } else {
            if (fn_80178360() == 1) {
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x400F), 2, result1, result2);
            }
        }
        break;
    }
    case 14:
        if (fn_80178348() == _SpchIG_bResultSide) {
            SpchIGSayHighlightPass();
        }
        break;
    case 13:
        if (fn_80178348() == _SpchIG_bResultSide) {
            SpchIGSayHighlightHitCatch();
        }
        break;
    case 11:
        if (fn_80178348() == _SpchIG_bResultSide) {
            SpchIGSayHighlightCatch();
        }
        break;
    case 12:
        if (fn_80178348() == _SpchIG_bResultSide) {
            SpchIGSayHighlightNoCatch();
        }
        break;
    case 7: {
        int result1;
        int result2;

        SpchIGGetGainFlags(&result1);
        if (_SpchIG_bResultSide == 0) {
            if (fn_80178348() == 0) {
                SpchIGGetPlayerCategory(&result2, _SpchIG_iPassCatcher);
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2005), 2, result1, result2);
            } else {
                if (_SpchIG_iTackler != 0) {
                    SpchIGGetPlayerCategory(&result2, _SpchIG_iTackler);
                } else {
                    SpchIGGetPlayerCategory(&result2, SpchIGGetTeamPlayer(0));
                }
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2013), 2, result1, result2);
            }
        } else {
            if (fn_80178348() == 0) {
                if (_SpchIG_iTackler != 0) {
                    SpchIGGetPlayerCategory(&result2, _SpchIG_iTackler);
                } else {
                    SpchIGGetPlayerCategory(&result2, SpchIGGetTeamPlayer(1));
                }
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4013), 2, result1, result2);
            } else {
                SpchIGGetPlayerCategory(&result2, _SpchIG_iPassCatcher);
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4005), 2, result1, result2);
            }
        }
        break;
    }
    case 8: {
        int result1;
        int result2;

        SpchIGGetIncompletionFlags(&result1);
        if (_SpchIG_bResultSide == 0) {
            if (fn_80178348() == 0) {
                if (result1 & 0x20) {
                    unsigned short i;
                    unsigned int count = fn_80178D18(0);

                    for (i = 0; i < count; i++) {
                        Object_80039F5C *player = PlyrGet(0, i);

                        if (player->mFlags & 0x10000000) {
                            SpchIGSetPassTarget(player->mId);
                            break;
                        }
                    }
                }
                if (_SpchIG_iPassTarget != 0) {
                    SpchIGGetPlayerCategory(&result2, _SpchIG_iPassTarget);
                    gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2006), 2, result1, result2);
                }
            } else {
                if (_SpchIG_iPassTarget != 0 && SpchIGGetNearestOpponent(0) != 0) {
                    SpchIGGetPlayerCategory(&result2, SpchIGGetNearestOpponent(0));
                } else {
                    SpchIGGetPlayerCategory(&result2, SpchIGGetTeamPlayer(0));
                }
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2014), 2, result1, result2);
            }
        } else {
            if (fn_80178348() == 0) {
                if (_SpchIG_iPassTarget != 0 && SpchIGGetNearestOpponent(1) != 0) {
                    SpchIGGetPlayerCategory(&result2, SpchIGGetNearestOpponent(1));
                } else {
                    SpchIGGetPlayerCategory(&result2, SpchIGGetTeamPlayer(1));
                }
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4014), 2, result1, result2);
            } else {
                if (result1 & 0x20) {
                    unsigned short i;
                    unsigned int count = fn_80178D18(1);

                    for (i = 0; i < count; i++) {
                        Object_80039F5C *player = PlyrGet(1, i);

                        if (player->mFlags & 0x10000000) {
                            SpchIGSetPassTarget(player->mId);
                            break;
                        }
                    }
                }
                if (_SpchIG_iPassTarget != 0) {
                    SpchIGGetPlayerCategory(&result2, _SpchIG_iPassTarget);
                    gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4006), 2, result1, result2);
                }
            }
        }
        break;
    }
    case 10: {
        int team = fn_80178360();

        if (_SpchIG_bResultSide == team) {
            int result;

            if (fn_80178360() == 0) {
                SpchIGGetPlayerCategory(&result, SpchIGGetNearestOpponent(0));
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2019), 1, result);
            } else {
                SpchIGGetPlayerCategory(&result, SpchIGGetNearestOpponent(1));
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4019), 1, result);
            }
            break;
        }
        /* Otherwise handled as case 9. */
    }
    case 9: {
        int result1;
        int result2;

        SpchIGGetGainFlags(&result1);
        if (_SpchIG_bResultSide == 0) {
            if (fn_80178348() == 0) {
                SpchIGGetPlayerCategory(&result2, _SpchIG_iBallCarrier);
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2007), 2, result1, result2);
            } else {
                if (_SpchIG_iTackler != 0) {
                    SpchIGGetPlayerCategory(&result2, _SpchIG_iTackler);
                } else {
                    SpchIGGetPlayerCategory(&result2, SpchIGGetTeamPlayer(0));
                }
                gSPCH_AddEvent(fn_801AE5D4(1, 0, 0x2015), 2, result1, result2);
            }
        } else {
            if (fn_80178348() == 0) {
                if (_SpchIG_iTackler != 0) {
                    SpchIGGetPlayerCategory(&result2, _SpchIG_iTackler);
                } else {
                    SpchIGGetPlayerCategory(&result2, SpchIGGetTeamPlayer(1));
                }
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4015), 2, result1, result2);
            } else {
                if (_SpchIG_iBallCarrier != 0) {
                    SpchIGGetPlayerCategory(&result2, _SpchIG_iBallCarrier);
                }
                gSPCH_AddEvent(fn_801AE5D4(2, 0, 0x4007), 2, result1, result2);
            }
        }
        break;
    }
    }
    _SpchIG_bResultSide = !_SpchIG_bResultSide;
}

extern "C" void SpchIGSetTackler(int id)
{
    _SpchIG_iTackler = id;
}

extern "C" int SpchIGGetTackler(void)
{
    return _SpchIG_iTackler;
}

extern "C" void SpchIGSetPassTarget(int id)
{
    _SpchIG_iPassTarget = id;
}

extern "C" int SpchIGGetPassTarget(void)
{
    return _SpchIG_iPassTarget;
}

extern "C" void SpchIGSetPassCatcher(int id)
{
    _SpchIG_iPassCatcher = id;
}

extern "C" int SpchIGGetPassCatcher(void)
{
    return _SpchIG_iPassCatcher;
}

extern "C" void SpchIGSetBallCarrier(int id)
{
    _SpchIG_iBallCarrier = id;
}

extern "C" int SpchIGGetBallCarrier(void)
{
    return _SpchIG_iBallCarrier;
}

extern "C" void SpchIGSetTurnoverPlayer(int id)
{
    _SpchIG_iTurnoverPlayer = id;
}

extern "C" int SpchIGGetTurnoverPlayer(void)
{
    return _SpchIG_iTurnoverPlayer;
}

extern "C" void SpchIGSetScorer(int id)
{
    _SpchIG_iScorer = id;
}

extern "C" int SpchIGGetScorer(void)
{
    return _SpchIG_iScorer;
}

extern "C" void SpchIGSetDownedCarrier(int id)
{
    _SpchIG_iDownedCarrier = id;
}
