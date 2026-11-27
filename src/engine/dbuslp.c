/* Picks the players for the seven field slots of a team. The caller gives each slot a
   position and a starting depth; the module reads the team's depth chart ('THCD', or the
   game copy 'AGCD') and the stored slot choices ('USLP'), then fills every slot with a free
   player, sorting the open slots and falling back to other depths and positions through the
   depth-chart tables when the wanted player is taken or refused by the caller's filters. */

#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

typedef struct DbUslpNode_t {
    unsigned char mDepth;
    unsigned char mPosition;
    unsigned char mSlot;
    unsigned char mStartDepth;
    unsigned char mBasePosition;
    unsigned char mStage;
    short mFallback;
    unsigned short mPlayerId;
    char unk_0xA[2];
    struct DbUslpNode_t *mpPrev;
    struct DbUslpNode_t *mpNext;
} DbUslpNode_t;

typedef struct DbUslpEntry_t {
    unsigned short mPlayerId;
    unsigned char mPosition;
    unsigned char mDepth;
} DbUslpEntry_t;

int DbThcdGetFallbackPosition(int position, int index);
unsigned short DbThcdGetMaxDepth(int position);

static int (*_DbUslp_pFilter1)(int player) = 0;
static int (*_DbUslp_pFilter2)(int player) = 0;
static DbUslpNode_t *_DbUslp_pNodes = 0;
static DbUslpNode_t *_DbUslp_pOpen = 0;
static DbUslpNode_t *_DbUslp_pFilled = 0;
static DbUslpEntry_t *_DbUslp_pEntries = 0;
static unsigned short _DbUslp_iNumEntries = 0;

static struct QueryCursor _DbUslp_DepthCursor = {0, 0, -1, 0};
static DbUslpNode_t _DbUslp_aNodes[7];
static DbUslpEntry_t _DbUslp_aEntries[91];
static struct QueryCursor _DbUslp_SlotCursor;

void DbUslpSortOpen(DbUslpNode_t **ppHead);
DbUslpNode_t *DbUslpFindSlot(DbUslpNode_t **ppHead, unsigned char slot);
int DbUslpSetFilter1(int (*pCallback)(int player));
int DbUslpSetFilter2(int (*pCallback)(int player));
int DbLoadTeamDepthChart(int team, int mode);

void *DbUslpAllocNodes(void)
{
    return _DbUslp_aNodes;
}

void DbUslpFreeNodes(void *p)
{
}

void DbBuildPendingNodeList(void *pPairs)
{
    unsigned char (*pValues)[2] = pPairs;
    unsigned char i;
    for (i = 0; i <= 6; i++) {
        if (pValues[i][0] > 25) {
            pValues[i][0] = 2;
        }
        _DbUslp_pNodes[i].mDepth = pValues[i][1];
        _DbUslp_pNodes[i].mPosition = pValues[i][0];
        _DbUslp_pNodes[i].mSlot = i;
        _DbUslp_pNodes[i].mStartDepth = pValues[i][1];
        _DbUslp_pNodes[i].mBasePosition = pValues[i][0];
        _DbUslp_pNodes[i].mStage = _DbUslp_pNodes[i].mFallback = 0;
        _DbUslp_pNodes[i].mPlayerId = 32767;
        _DbUslp_pNodes[i].mpPrev = (i != 0) ? &_DbUslp_pNodes[i - 1] : 0;
        _DbUslp_pNodes[i].mpNext = (i != 6) ? &_DbUslp_pNodes[i + 1] : 0;
    }
    _DbUslp_pFilled = 0;
    _DbUslp_pOpen = _DbUslp_pNodes;
    DbUslpSortOpen(&_DbUslp_pOpen);
}

void DbUslpClearLists(void)
{
    _DbUslp_pOpen = 0;
    _DbUslp_pFilled = 0;
}

void DbUslpSortOpen(DbUslpNode_t **ppHead)
{
    DbUslpNode_t *pA;
    DbUslpNode_t *pB;
    DbUslpNode_t *pTmp;
    int swapped;
    int diff;
    int remA;
    int remB;

    if ((*ppHead)->mpNext == 0) {
        return;
    }
    do {
        pA = *ppHead;
        swapped = 0;
        for (pB = pA->mpNext; pB != 0; pB = pB->mpNext, pA = pA->mpNext) {
            if (pB->mFallback != pA->mFallback) {
                diff = pB->mFallback - pA->mFallback;
            } else if (pB->mDepth >= pB->mStartDepth && pA->mDepth >= pA->mStartDepth) {
                if (pB->mDepth != pA->mDepth) {
                    diff = pB->mDepth - pA->mDepth;
                } else if (pA->mBasePosition >= 21 && pA->mBasePosition <= 25) {
                    if (pB->mBasePosition >= 21 && pB->mBasePosition <= 25) {
                        diff = pB->mSlot - pA->mSlot;
                    } else {
                        diff = 1;
                    }
                } else if (pB->mBasePosition >= 21 && pB->mBasePosition <= 25) {
                    diff = -1;
                } else {
                    diff = pB->mSlot - pA->mSlot;
                }
            } else {
                remB = pB->mDepth - pB->mStartDepth;
                remA = pA->mDepth - pA->mStartDepth;
                if (remB == remA) {
                    if (pB->mDepth != pA->mDepth) {
                        diff = pB->mDepth - pA->mDepth;
                    } else {
                        diff = pB->mSlot - pA->mSlot;
                    }
                } else {
                    diff = (remB > remA) ? -1 : 1;
                }
            }
            if (diff < 0) {
                if (pB->mpPrev != 0) {
                    pB->mpPrev->mpNext = pB->mpNext;
                }
                if (pB->mpNext != 0) {
                    pB->mpNext->mpPrev = pB->mpPrev;
                }
                if (pA->mpPrev != 0) {
                    pA->mpPrev->mpNext = pB;
                } else {
                    *ppHead = pB;
                }
                pB->mpPrev = pA->mpPrev;
                pA->mpPrev = pB;
                pB->mpNext = pA;
                swapped = 1;
                pTmp = pA;
                pA = pB;
                pB = pTmp;
            }
        }
    } while (swapped == 1);
}

DbUslpNode_t *DbUslpFindSlot(DbUslpNode_t **ppHead, unsigned char slot)
{
    DbUslpNode_t *p;

    for (p = *ppHead; p != 0; p = p->mpNext) {
        if (p->mSlot == slot) {
            return p;
        }
    }
    return 0;
}

DbUslpNode_t *DbUslpFindPlayer(DbUslpNode_t **ppHead, unsigned short player)
{
    DbUslpNode_t *p;

    for (p = *ppHead; p != 0; p = p->mpNext) {
        if (p->mPlayerId == player) {
            return p;
        }
    }
    return 0;
}

void DbUslpListRemove(DbUslpNode_t **ppHead, DbUslpNode_t *p)
{
    if (*ppHead == p) {
        *ppHead = p->mpNext;
    }
    if (p->mpPrev != 0) {
        p->mpPrev->mpNext = p->mpNext;
    }
    if (p->mpNext != 0) {
        p->mpNext->mpPrev = p->mpPrev;
    }
    p->mpPrev = p;
    p->mpNext = p;
}

void DbUslpListPush(DbUslpNode_t **ppHead, DbUslpNode_t *p)
{
    p->mpPrev = 0;
    p->mpNext = *ppHead;
    if (p->mpNext != 0) {
        p->mpNext->mpPrev = p;
    }
    *ppHead = p;
}

void *DbUslpAllocEntries(void)
{
    return _DbUslp_aEntries;
}

void DbUslpFreeEntries(void *p)
{
}

int DbUslpOpenSlotCursor(int team, int plfo, int pfio)
{
    _DbUslp_SlotCursor.mUnknown0 = 0;
    _DbUslp_SlotCursor.mUnknown4 = 0;
    _DbUslp_SlotCursor.mUnknown8 = -1;
    _DbUslp_SlotCursor.mUnknown12 = 0;
    return TDbCompilePerformOp(0, "declare \x8a cursor for select * from 'USLP' where ('DIGT' = \x82) and ('OIFP' = \x82) and ('OFLP' = \x82)\n",
                               &_DbUslp_SlotCursor, team, pfio, plfo);
}

void DbUslpCloseSlotCursor(void)
{
    if (_DbUslp_SlotCursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&_DbUslp_SlotCursor);
        _DbUslp_SlotCursor.mUnknown0 = 0;
        _DbUslp_SlotCursor.mUnknown4 = 0;
        _DbUslp_SlotCursor.mUnknown8 = -1;
        _DbUslp_SlotCursor.mUnknown12 = 0;
    }
}

void DbUslpApplyStoredSlots(void)
{
    int value;
    unsigned char key;
    int err;
    int resultA;
    int resultB;
    DbUslpNode_t *p;

    do {
        err = TDbCompilePerformOp(0, "fetch from \x8a 'DIGP' into \x82 and 'IPFP' into \x80\n", &_DbUslp_SlotCursor,
                                  &value, &key);
        if (err != 0) {
            break;
        }
        resultA = 0;
        resultB = 0;
        if (_DbUslp_pFilter1 != 0) {
            resultA = _DbUslp_pFilter1(value);
        }
        if (_DbUslp_pFilter2 != 0) {
            resultB = _DbUslp_pFilter2(value);
        }
        if (resultA == 0 && resultB == 0) {
            p = DbUslpFindSlot(&_DbUslp_pOpen, key);
            if (p != 0) {
                DbUslpListRemove(&_DbUslp_pOpen, p);
                p->mPlayerId = value;
                DbUslpListPush(&_DbUslp_pFilled, p);
            }
        }
    } while (err == 0);
}

void DbAssignPendingNodeIds(void)
{
    DbUslpNode_t *p;
    int found;
    unsigned short i;
    int resultA;
    int resultB;
    int done;
    unsigned short count;
    int next;

    while (_DbUslp_pOpen != 0) {
        p = _DbUslp_pOpen;
        found = 0;
        for (i = 0; i < _DbUslp_iNumEntries && found == 0; i++) {
            if (p->mPosition == _DbUslp_pEntries[i].mPosition || p->mStage != 0) {
                if (p->mDepth == _DbUslp_pEntries[i].mDepth || p->mStage != 0) {
                    resultA = 0;
                    resultB = 0;
                    if (_DbUslp_pFilter1 != 0 && p->mStage != 3) {
                        resultA = _DbUslp_pFilter1(_DbUslp_pEntries[i].mPlayerId);
                    }
                    if (_DbUslp_pFilter2 != 0 && p->mStage != 2) {
                        resultB = _DbUslp_pFilter2(_DbUslp_pEntries[i].mPlayerId);
                    }
                    if (DbUslpFindPlayer(&_DbUslp_pFilled, _DbUslp_pEntries[i].mPlayerId) == 0 && resultA == 0
                        && resultB == 0) {
                        DbUslpListRemove(&_DbUslp_pOpen, p);
                        found = 1;
                        p->mPlayerId = _DbUslp_pEntries[i].mPlayerId;
                        DbUslpListPush(&_DbUslp_pFilled, p);
                    }
                }
            }
        }
        if (found == 0) {
            done = 0;
            count = DbThcdGetMaxDepth(p->mPosition);
            if (p->mDepth < p->mStartDepth) {
                if (p->mDepth != 0) {
                    p->mDepth--;
                    DbUslpSortOpen(&_DbUslp_pOpen);
                } else {
                    done = 1;
                }
            } else {
                p->mDepth++;
                if (p->mDepth >= count) {
                    if (p->mStartDepth != 0) {
                        p->mDepth = p->mStartDepth - 1;
                    } else {
                        done = 1;
                    }
                }
                DbUslpSortOpen(&_DbUslp_pOpen);
            }
            if (done == 1) {
                p->mFallback++;
                next = DbThcdGetFallbackPosition(p->mBasePosition, p->mFallback);
                if (next == 31) {
                    if (p->mStartDepth != 0) {
                        p->mDepth = p->mStartDepth - 1;
                        p->mPosition = p->mBasePosition;
                        p->mFallback = 0;
                        p->mStartDepth--;
                    } else if (p->mStage == 0) {
                        p->mStage = done;
                    } else if (p->mStage == 1) {
                        p->mStage = 2;
                    } else {
                        return;
                    }
                } else {
                    p->mPosition = next;
                    p->mDepth = p->mStartDepth;
                    DbUslpSortOpen(&_DbUslp_pOpen);
                }
            }
        }
    }
}

int DbUslpFilterNone(int player)
{
    return 0;
}

int DbUslpModuleInit(void)
{
    _DbUslp_pNodes = DbUslpAllocNodes();
    _DbUslp_pEntries = DbUslpAllocEntries();
    _DbUslp_SlotCursor.mUnknown0 = 0;
    _DbUslp_SlotCursor.mUnknown4 = 0;
    _DbUslp_SlotCursor.mUnknown8 = -1;
    _DbUslp_SlotCursor.mUnknown12 = 0;
    DbUslpSetFilter1(DbUslpFilterNone);
    DbUslpSetFilter2(0);
    return 0;
}

int DbUslpModuleShutdown(void)
{
    if (_DbUslp_pNodes != 0) {
        DbUslpFreeNodes(_DbUslp_pNodes);
        _DbUslp_pNodes = 0;
    }
    if (_DbUslp_pEntries != 0) {
        DbUslpFreeEntries(_DbUslp_pEntries);
        _DbUslp_pEntries = 0;
        _DbUslp_iNumEntries = 0;
    }
    DbUslpSetFilter1(0);
    DbUslpSetFilter2(0);
    _DbUslp_SlotCursor.mUnknown0 = 0;
    _DbUslp_SlotCursor.mUnknown4 = 0;
    _DbUslp_SlotCursor.mUnknown8 = -1;
    _DbUslp_SlotCursor.mUnknown12 = 0;
    return 0;
}

int DbUslpResetFilter1(void)
{
    _DbUslp_pFilter1 = DbUslpFilterNone;
    return 0;
}

int DbUslpSetFilter1(int (*pCallback)(int player))
{
    _DbUslp_pFilter1 = pCallback;
    return 0;
}

int DbUslpSetFilter2(int (*pCallback)(int player))
{
    _DbUslp_pFilter2 = pCallback;
    return 0;
}

int DbUslpRunStep(int team, int plfo, int pfio, void *pPairs, int step, int mode)
{
    switch (step) {
    case 0:
        DbBuildPendingNodeList(pPairs);
        break;
    case 1:
        DbLoadTeamDepthChart(team, mode);
        break;
    case 2:
        DbUslpOpenSlotCursor(team, plfo, pfio);
        break;
    case 3:
        DbUslpApplyStoredSlots();
        break;
    case 4:
        DbAssignPendingNodeIds();
        break;
    }
    return 0;
}

int DbUslpFillSlots(int team, int plfo, int pfio, void *pPairs, int mode)
{
    DbUslpRunStep(team, plfo, pfio, pPairs, 0, mode);
    DbUslpRunStep(team, plfo, pfio, pPairs, 1, mode);
    DbUslpRunStep(team, plfo, pfio, pPairs, 2, mode);
    DbUslpRunStep(team, plfo, pfio, pPairs, 3, mode);
    DbUslpRunStep(team, plfo, pfio, pPairs, 4, mode);
    return 0;
}

int DbUslpFinish(void)
{
    DbUslpClearLists();
    DbUslpCloseSlotCursor();
    return 0;
}

unsigned short DbUslpGetSlotPlayer(unsigned char slot)
{
    unsigned short value = 32767;
    DbUslpNode_t *p = DbUslpFindSlot(&_DbUslp_pFilled, slot);

    if (p != 0) {
        value = p->mPlayerId;
    }
    return value;
}

int DbUslpDeleteSlot(int table, int team, int plfo, int pfio, int slot)
{
    return TDbCompilePerformOp(0, "delete from \x8c where ('DIGT' = \x82) and ('OFLP' = \x82) and ('OIFP' = \x82) and ('IPFP' = \x82)\n",
                               table, team, plfo, pfio, slot);
}

int DbUslpInsertSlot(int table, int pfio, int plfo, int slot, int player, int team)
{
    return TDbCompilePerformOp(0, "insert into \x8c set 'OIFP' = \x82 and 'OFLP' = \x82 and 'IPFP' = \x82 and 'DIGP' = \x82 and 'DIGT' = \x82\n",
                               table, pfio, plfo, slot, player, team);
}

int DbUslpDeletePlayerSlots(int table, int player, int pfio, int plfo)
{
    return TDbCompilePerformOp(0, "delete from \x8c where ('DIGP' = \x82) and ('OIFP' = \x82) and ('OFLP' = \x82)\n", table,
                               player, pfio, plfo);
}

int DbUslpDeletePlayer(int table, int player)
{
    return TDbCompilePerformOp(0, "delete from \x8c where ('DIGP' = \x82)\n", table, player);
}

int DbOpenDepthChartCursor(int team1, int team2, int mode)
{
    int tblA;
    int tblB;
    int status;
    int key;

    if (mode == 1) {
        tblA = 0x41474C50;
        tblB = 0x41474344;
    } else {
        tblA = 0x59414C50;
        tblB = 0x54484344;
    }
    _DbUslp_DepthCursor.mUnknown0 = 0;
    _DbUslp_DepthCursor.mUnknown4 = 0;
    _DbUslp_DepthCursor.mUnknown8 = -1;
    _DbUslp_DepthCursor.mUnknown12 = 0;
    if (team1 != 1023 && team2 != 1023) {
        status = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c inner join \x8c on (\x8c.'DIGP' = \x8c.'DIGP') where (\x8c.'OHFP' = \x82) order by \x8c.'pedd' asc and \x8c.'SOPP' desc\n",
                                     &_DbUslp_DepthCursor, tblA, tblB, tblB, tblA, tblA, 0, tblB, tblB);
    } else {
        key = (team1 == 1023) ? team2 : team1;
        status = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c inner join \x8c on (\x8c.'DIGP' = \x8c.'DIGP') where (\x8c.'DIGT' = \x82) and (\x8c.'OHFP' = \x82) order by \x8c.'pedd' asc and \x8c.'SOPP' desc\n",
                                     &_DbUslp_DepthCursor, tblA, tblB, tblB, tblA, tblA, key, tblA, 0, tblB, tblB);
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        status = 0;
    }
    return status;
}

int DbCloseDepthChartCursor(void)
{
    int result;
    if (_DbUslp_DepthCursor.mUnknown0 != 0) {
        result = TDbSQLDestroyCursor(&_DbUslp_DepthCursor);
    } else {
        result = 0;
    }
    if (result == 0) {
        _DbUslp_DepthCursor.mUnknown0 = 0;
        _DbUslp_DepthCursor.mUnknown4 = 0;
        _DbUslp_DepthCursor.mUnknown8 = -1;
        _DbUslp_DepthCursor.mUnknown12 = 0;
        _DbUslp_iNumEntries = 0;
    }
    return result;
}

int DbLoadTeamDepthChart(int team, int mode)
{
    int result = 0;
    int tag = 0x54484344;
    int a, b, c, d;
    unsigned int count;
    if (mode == 1) {
        tag = 0x41474344;
    }
    _DbUslp_DepthCursor.mUnknown4 = 0;
    count = 0;
    do {
        result = TDbCompilePerformOp(0, "fetch from \x8a \x8c.'DIGT' into \x82 and \x8c.'DIGP' into \x82 and \x8c.'SOPP' into \x82 and \x8c.'pedd' into \x82\n",
                                     &_DbUslp_DepthCursor, tag, &a, tag, &b, tag, &c, tag, &d);
        if (result == 0) {
            if (a == team && (unsigned int)d < DbThcdGetMaxDepth(c) && count <= 90) {
                _DbUslp_pEntries[count].mPlayerId = b;
                _DbUslp_pEntries[count].mPosition = c;
                _DbUslp_pEntries[count].mDepth = d;
                count++;
            }
        }
    } while (result == 0);
    if (QUERY_STATUS_ACCEPTED(result) == 1) {
        _DbUslp_iNumEntries = count;
        result = 0;
    }
    return result;
}
