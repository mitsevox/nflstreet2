/* The game-info record ('FNIG'): the one row that describes the game being played, with the
   home and away teams and their offensive and defensive playbooks among its columns. Resets
   it, sets single columns, fills missing values when a game starts, copies the two teams'
   players into the game player table, and runs every database module's start and resume
   hooks in turn. */

#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

typedef struct DbFnigRecord_t {
    int mIsfg;
    int mDotg;
    int mHtwg;
    int mGpwg;
    int mGtwg;
    int mGfwg;
    int mGwwg;
    int mHomeTeam;
    int mHomeOffPlaybook;
    int mHomeDefPlaybook;
    int mOthg;
    int mHchg;
    int mCshg;
    int mAwayTeam;
    int mAwayOffPlaybook;
    int mAwayDefPlaybook;
    int mOtag;
    int mHcag;
    int mCsag;
    int unk_0x4C;
    int mMitg;
    int mRtqg;
    int mElqg;
    int mWodg;
    int unk_0x60;
    float mGtyg;
    int mPnig;
    int unk_0x6C;
} DbFnigRecord_t;

int DbYalpBeginGame(int home, int away, int mode, int arg);
int DbYalpResumeGame(int home, int away, int homeCshg, int awayCsag);
int DbMttsBeginGame(int home, int away, int mode, int arg);
int DbMttsResumeGame(int home, int away, int homeCshg, int awayCsag);
int DbSrptBeginGame(int home, int away, int mode, int arg);
int DbSrptResumeGame(int home, int away, int homeCshg, int awayCsag);
int DbThcdBeginGame(int home, int away, int mode, int arg);
int DbThcdResumeGame(int home, int away, int homeCshg, int awayCsag);
int DbThcdSetLineups(int home, int *pHomePlayers, int away, int *pAwayPlayers, int table);

static int _DbFnig_iState = 0;
static int (*_DbFnig_pStartCheck)(int home, int away, unsigned char *pStart) = 0;
static int (*_DbFnig_pStartGame)(int home, int away, int mode, int arg) = 0;
static int (*_DbFnig_pResumeGame)(int home, int away, int homeCshg, int awayCsag) = 0;
static unsigned char _DbFnig_bCheckStart = 1;
static int _DbFnig_iHomeTeam = 1023;
static int _DbFnig_iAwayTeam = 1023;

int DbResetGameInfo(void);

int DbFnigModuleInit(void **ppHooks)
{
    unsigned char found;
    int result = TDbCompilePerformOp(0, "select 'PNIG' into \x83 from 'FNIG'\n", &found);
    if (found == 0) {
        result = DbResetGameInfo();
    }
    if (result == 0 && ppHooks != 0) {
        _DbFnig_pStartCheck = ppHooks[0];
        _DbFnig_pStartGame = ppHooks[1];
        _DbFnig_pResumeGame = ppHooks[2];
    }
    return result;
}

void DbFnigModuleShutdown(void)
{
    _DbFnig_iState = 0;
    _DbFnig_pStartCheck = 0;
    _DbFnig_pStartGame = 0;
    _DbFnig_pResumeGame = 0;
}

int DbResetGameInfo(void)
{
    int result;
    void *pResult = 0;

    result = TDbCompilePerformOp(pResult, "update 'FNIG' set 'RCSG' = \x86 and 'GTYG' = \x86 and 'ISFG' = \x82 and 'DOTG' = \x82 and 'HTWG' = \x82 and 'GPWG' = \x82 and 'GTWG' = \x82 and 'GFWG' = \x82 and 'GWWG' = \x82 and 'GTHG' = \x82 and 'IPHG' = \x82 and 'PDHG' = \x82 and 'OTHG' = \x82 and 'HCHG' = \x82 and 'CSHG' = \x82 and 'GTAG' = \x82 and 'IPAG' = \x82 and 'PDAG' = \x82 and 'OTAG' = \x82 and 'HCAG' = \x82 and 'CSAG' = \x82 and 'GTPG' = \x82 and 'MITG' = \x82 and 'RTQG' = \x82 and 'ELQG' = \x82 and 'WODG' = \x82 and 'PNIG' = \x82 and 'TOFG' = \x82\n",
                                 999.99f, 999.99f, 15, 2047, 15, 127, 127, 127, -1, 1023, 63, 63, 4, 3, 255, 1023, 63, 63, 4, 3,
                                 255, 1023, -1, 15, 1023, 15, 0, 0);
    _DbFnig_iHomeTeam = 1023;
    _DbFnig_iAwayTeam = 1023;
    return result;
}

int DbFnigSetHomeTeam(int value)
{
    int err = TDbCompilePerformOp(0, "update 'FNIG' set 'GTHG' = \x82\n", value);

    _DbFnig_iHomeTeam = value;
    return err;
}

int DbFnigSetAwayTeam(int value)
{
    int err = TDbCompilePerformOp(0, "update 'FNIG' set 'GTAG' = \x82\n", value);

    _DbFnig_iAwayTeam = value;
    return err;
}

int DbFnigSetHomeOffPlaybook(int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set 'IPHG' = \x82\n", value);
}

int DbFnigSetHomeDefPlaybook(int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set 'PDHG' = \x82\n", value);
}

int DbFnigSetAwayOffPlaybook(int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set 'IPAG' = \x82\n", value);
}

int DbFnigSetAwayDefPlaybook(int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set 'PDAG' = \x82\n", value);
}

int DbFnigSetDotg(int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set 'DOTG' = \x82\n", value);
}

int DbFnigSetHtwg(int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set 'HTWG' = \x82\n", value);
}

int DbFnigSetColumn(int column, int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set \x8c = \x82\n", column, value);
}

int fn_8022DD4C(int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set 'CSHG' = \x82\n", value);
}

int fn_8022DD80(int value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set 'CSAG' = \x82\n", value);
}

int DbFnigDecOthg(void)
{
    int value;
    int err = TDbCompilePerformOp(0, "select 'OTHG' into \x82 from 'FNIG'\n", &value);

    if (err == 0 && value != 0) {
        err = TDbCompilePerformOp(0, "update 'FNIG' set 'OTHG' = \x82\n", value - 1);
    }
    return err;
}

int DbFnigDecOtag(void)
{
    int value;
    int err = TDbCompilePerformOp(0, "select 'OTAG' into \x82 from 'FNIG'\n", &value);

    if (err == 0 && value != 0) {
        err = TDbCompilePerformOp(0, "update 'FNIG' set 'OTAG' = \x82\n", value - 1);
    }
    return err;
}

int DbFnigAddHchg(int add)
{
    int value;
    int err = TDbCompilePerformOp(0, "select 'HCHG' into \x82 from 'FNIG'\n", &value);

    if (err == 0) {
        err = TDbCompilePerformOp(0, "update 'FNIG' set 'HCHG' = \x82\n", value + add);
    }
    return err;
}

int DbFnigAddHcag(int add)
{
    int value;
    int err = TDbCompilePerformOp(0, "select 'HCAG' into \x82 from 'FNIG'\n", &value);

    if (err == 0) {
        err = TDbCompilePerformOp(0, "update 'FNIG' set 'HCAG' = \x82\n", value + add);
    }
    return err;
}

int DbFnigSetFloatColumn(int column, float value)
{
    return TDbCompilePerformOp(0, "update 'FNIG' set \x8c = \x86\n", column, value);
}

int DbFnigWriteBlock(int tag, void *p)
{
    return 0;
}

int DbUpdateSettingsRecord(int inProgress, int *pHome, int *pAway)
{
    DbFnigRecord_t rec;
    int v200;
    int v204;
    int err;

    *pHome = 1023;
    *pAway = 1023;
    err = TDbCompilePerformOp(0, "select 'GTYG' into \x86 and 'ISFG' into \x82 and 'DOTG' into \x82 and 'HTWG' into \x82 and 'GPWG' into \x82 and 'GTWG' into \x82 and 'GFWG' into \x82 and 'GWWG' into \x82 and 'GTHG' into \x82 and 'IPHG' into \x82 and 'PDHG' into \x82 and 'OTHG' into \x82 and 'HCHG' into \x82 and 'CSHG' into \x82 and 'GTAG' into \x82 and 'IPAG' into \x82 and 'PDAG' into \x82 and 'OTAG' into \x82 and 'HCAG' into \x82 and 'CSAG' into \x82 and 'MITG' into \x82 and 'RTQG' into \x82 and 'ELQG' into \x82 and 'WODG' into \x82 and 'PNIG' into \x82 from 'FNIG'\n",
                              &rec.mGtyg, &rec.mIsfg, &rec.mDotg, &rec.mHtwg, &rec.mGpwg, &rec.mGtwg,
                              &rec.mGfwg, &rec.mGwwg, &rec.mHomeTeam, &rec.mHomeOffPlaybook, &rec.mHomeDefPlaybook,
                              &rec.mOthg, &rec.mHchg, &rec.mCshg, &rec.mAwayTeam, &rec.mAwayOffPlaybook,
                              &rec.mAwayDefPlaybook, &rec.mOtag, &rec.mHcag, &rec.mCsag, &rec.mMitg,
                              &rec.mRtqg, &rec.mElqg, &rec.mWodg, &rec.mPnig);
    rec.mIsfg = inProgress;
    if (err == 0) {
        if (inProgress == 0) {
            if (rec.mDotg == 2047) {
                rec.mDotg = 780;
            }
            if (rec.mHtwg == 15) {
                rec.mHtwg = 0;
            }
            if (rec.mGpwg == 127) {
                rec.mGpwg = 0;
            }
            if (rec.mGtwg == 127) {
                rec.mGtwg = 78;
            }
            if (rec.mGfwg == 127) {
                rec.mGfwg = 0;
            }
            if (rec.mGwwg == -1) {
                rec.mGwwg = 0x1680000;
            }
            if (rec.mOthg == 4) {
                rec.mOthg = 3;
            }
            if (rec.mOtag == 4) {
                rec.mOtag = 3;
            }
            if (rec.mHchg == 3) {
                rec.mHchg = 2;
            }
            if (rec.mHcag == 3) {
                rec.mHcag = 2;
            }
            if (err == 0) {
                if (rec.mCshg == 255) {
                    rec.mCshg = 0;
                }
                if (rec.mCsag == 255) {
                    rec.mCsag = 0;
                }
                if (rec.mMitg == -1) {
                    rec.mMitg = 0;
                }
                if (rec.mRtqg == 15) {
                    rec.mRtqg = 0;
                }
                if (rec.mRtqg == 1023) {
                    err = TDbCompilePerformOp(0, "select 'NLQO' into \x82 from 'TPOG'\n", &rec.mRtqg);
                }
                if (err == 0) {
                    if (rec.mWodg == 15) {
                        rec.mWodg = 0;
                    }
                    if (rec.mGtyg == 999.99f) {
                        rec.mGtyg = 10.0f;
                    }
                    if (rec.mPnig == 255) {
                        rec.mPnig = 0;
                    }
                }
            }
        }
        if (err == 0) {
            if (rec.mHomeOffPlaybook == 63 || rec.mHomeDefPlaybook == 63) {
                err = TDbCompilePerformOp(0, "select COL_TEAM_OFFPLAYBOOK into \x82 and COL_TEAM_DEFPLAYBOOK into \x82 from 'MAET' where ('DIGT' = \x82)\n",
                                          &v200, &v204, rec.mHomeTeam);
                if (err == 0) {
                    if (rec.mHomeOffPlaybook == 63) {
                        rec.mHomeOffPlaybook = v200;
                    }
                    if (rec.mHomeDefPlaybook == 63) {
                        rec.mHomeDefPlaybook = v204;
                    }
                }
            }
            if (err == 0) {
                if (rec.mAwayOffPlaybook == 63 || rec.mAwayDefPlaybook == 63) {
                    err = TDbCompilePerformOp(0, "select COL_TEAM_OFFPLAYBOOK into \x82 and COL_TEAM_DEFPLAYBOOK into \x82 from 'MAET' where ('DIGT' = \x82)\n",
                                              &v200, &v204, rec.mAwayTeam);
                    if (err == 0) {
                        if (rec.mAwayOffPlaybook == 63) {
                            rec.mAwayOffPlaybook = v200;
                        }
                        if (rec.mAwayDefPlaybook == 63) {
                            rec.mAwayDefPlaybook = v204;
                        }
                    }
                }
                if (err == 0) {
                    err = TDbCompilePerformOp(0, "update 'FNIG' set 'GTYG' = \x86 and 'ISFG' = \x82 and 'DOTG' = \x82 and 'HTWG' = \x82 and 'GPWG' = \x82 and 'GTWG' = \x82 and 'GFWG' = \x82 and 'GWWG' = \x82 and 'GTHG' = \x82 and 'IPHG' = \x82 and 'PDHG' = \x82 and 'OTHG' = \x82 and 'HCHG' = \x82 and 'CSHG' = \x82 and 'GTAG' = \x82 and 'IPAG' = \x82 and 'PDAG' = \x82 and 'OTAG' = \x82 and 'HCAG' = \x82 and 'CSAG' = \x82 and 'MITG' = \x82 and 'RTQG' = \x82 and 'ELQG' = \x82 and 'WODG' = \x82 and 'PNIG' = \x82\n",
                                              rec.mGtyg, rec.mIsfg, rec.mDotg, rec.mHtwg, rec.mGpwg,
                                              rec.mGtwg, rec.mGfwg, rec.mGwwg, rec.mHomeTeam, rec.mHomeOffPlaybook,
                                              rec.mHomeDefPlaybook, rec.mOthg, rec.mHchg, rec.mCshg,
                                              rec.mAwayTeam, rec.mAwayOffPlaybook, rec.mAwayDefPlaybook, rec.mOtag,
                                              rec.mHcag, rec.mCsag, rec.mMitg, rec.mRtqg, rec.mElqg,
                                              rec.mWodg, rec.mPnig);
                    _DbFnig_iHomeTeam = rec.mHomeTeam;
                    _DbFnig_iAwayTeam = rec.mAwayTeam;
                    if (err == 0) {
                        if (pHome != 0) {
                            *pHome = rec.mHomeTeam;
                        }
                        if (pAway != 0) {
                            *pAway = rec.mAwayTeam;
                        }
                    }
                }
            }
        }
    }
    return err;
}

int DbFnigCopyGamePlayers(int home, int away)
{
    if (home != 1023 && away != 1023) {
        return TDbCompilePerformOp(0, "insert into 'AGLP' * select * from 'YALP' where ('DIGT' = \x82) or ('DIGT' = \x82)\n",
                                   home, away);
    } else {
        int value = away;
        if (home != 1023) {
            value = home;
        }
        return TDbCompilePerformOp(0, "insert into 'AGLP' * select * from 'YALP' where ('DIGT' = \x82)\n", value);
    }
}

int DbFnigCopyGameDepthCharts(int home, int away, int side)
{
    int err;

    if (side == 1) {
        err = TDbCompilePerformOp(0, "insert into 'AGCD' 'THCD'.'DIGP' and 'THCD'.'SOPP' and 'THCD'.'pedd' and 'THCD'.'DIGT' select * from 'THCD' inner join 'YALP' on 'THCD'.'DIGP' = 'YALP'.'DIGP' where ('YALP'.'DIGT' = \x85) and ('YALP'.'GILP' = 1 or 'YALP'.'GILP' = 3)\n",
                                  home);
    } else if (side == 2) {
        err = TDbCompilePerformOp(0, "insert into 'AGCD' 'THCD'.'DIGP' and 'THCD'.'SOPP' and 'THCD'.'pedd' and 'THCD'.'DIGT' select * from 'THCD' inner join 'YALP' on 'THCD'.'DIGP' = 'YALP'.'DIGP' where ('YALP'.'DIGT' = \x85) and ('YALP'.'GILP' = 2 or 'YALP'.'GILP' = 3)\n",
                                  home);
    } else {
        err = TDbCompilePerformOp(0, "insert into 'AGCD' * select * from 'THCD' where ('DIGT' = \x82)\n", home);
        if (err == 0) {
            err = TDbCompilePerformOp(0, "insert into 'AGCD' * select * from 'THCD' where ('DIGT' = \x82)\n", away);
        }
    }
    return err;
}

int DbRunUpdateChain(int inProgress, int arg, unsigned char *pDone, int *pHomePlayers, int *pAwayPlayers)
{
    int home;
    int away;
    unsigned char flag;
    int err;

    home = 0;
    away = 0;
    err = 0;
    flag = 1;
    if (inProgress == 0) {
        err = DbUpdateSettingsRecord(arg, &home, &away);
        if (err == 0 && _DbFnig_bCheckStart == 1 && _DbFnig_pStartCheck != 0) {
            err = _DbFnig_pStartCheck(home, away, &flag);
        }
        if (err == 0 && flag == 1) {
            err = TDbCompilePerformOp(0, "delete from 'AGCD'\n");
            if (err == 0) {
                err = TDbCompilePerformOp(0, "delete from 'AGLP'\n");
                if (err == 0) {
                    err = DbFnigCopyGamePlayers(home, away);
                }
            }
            DbThcdSetLineups(home, pHomePlayers, away, pAwayPlayers, 0x41474344);
            _DbFnig_bCheckStart = 1;
        }
        if (err != 0) {
            flag = 0;
        }
    }
    if (err == 0 && flag == 1) {
        if (_DbFnig_pStartGame != 0) {
            err = _DbFnig_pStartGame(home, away, inProgress, arg);
        }
        if (err == 0) {
            err = DbMttsBeginGame(home, away, inProgress, arg);
            if (err == 0) {
                err = DbYalpBeginGame(home, away, inProgress, arg);
                if (err == 0) {
                    err = DbSrptBeginGame(home, away, inProgress, arg);
                    if (err == 0) {
                        err = DbThcdBeginGame(home, away, inProgress, arg);
                    }
                }
            }
        }
    }
    *pDone = (err == 0) ? flag : 0;
    return err;
}

int DbFnigGetTeams(int *pHome, int *pAway)
{
    return TDbCompilePerformOp(0, "select 'GTHG' into \x82 and 'GTAG' into \x82 from 'FNIG'\n", pHome, pAway);
}

int DbRunLoadChain(void)
{
    int home;
    int away;
    int homeCshg;
    int awayCsag;
    int err;

    err = TDbCompilePerformOp(0, "select 'GTHG' into \x82 and 'GTAG' into \x82 and 'CSHG' into \x82 and 'CSAG' into \x82 from 'FNIG'\n",
                              &home, &away, &homeCshg, &awayCsag);
    if (_DbFnig_pResumeGame != 0) {
        err = _DbFnig_pResumeGame(home, away, homeCshg, awayCsag);
    }
    if (err == 0) {
        err = DbThcdResumeGame(home, away, homeCshg, awayCsag);
        if (err == 0) {
            err = DbSrptResumeGame(home, away, homeCshg, awayCsag);
            if (err == 0) {
                err = DbYalpResumeGame(home, away, homeCshg, awayCsag);
                if (err == 0) {
                    err = DbMttsResumeGame(home, away, homeCshg, awayCsag);
                }
            }
        }
    }
    return err;
}

int fn_8022E558(void)
{
    return _DbFnig_iHomeTeam;
}

int fn_8022E560(void)
{
    return _DbFnig_iAwayTeam;
}
